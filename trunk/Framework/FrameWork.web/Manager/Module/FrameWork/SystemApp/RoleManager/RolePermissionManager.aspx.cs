using System;
using System.Data;
using System.Configuration;
using System.Collections;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Web.UI.HtmlControls;

using FrameWork;
using FrameWork.Components;
using FrameWork.WebControls;

namespace FrameWork.web.Module.FrameWork.RoleManager
{
    public partial class RolePermissionManager : System.Web.UI.Page
    {
        int RoleID = (int)Common.sink("RoleID", MethodType.Get, 255, 1, DataType.Int);
        int ApplicationID = (int)Common.sink("ApplicationID", MethodType.Get, 255, 1, DataType.Int);
        string CMD = (string)Common.sink("CMD", MethodType.Get, 255, 1, DataType.Str);
        protected void Page_Load(object sender, EventArgs e)
        {
            FrameWorkPermission.CheckPagePermission(CMD);
            BindButton();
            if (!Page.IsPostBack)
            {
                OnStart();
                OnDisp();
            }
        }

        private void OnStart()
        {
            RoleName_Txt.Text = BusinessFacade.sys_RolesDisp(RoleID).R_RoleName;
            AppName_Txt.Text = BusinessFacade.sys_ApplicationsDisp(ApplicationID).A_AppName;
        }

        /// <summary>
        /// 绑定数据
        /// </summary>
        private void OnDisp()
        {
            QueryParam qp = new QueryParam();
            qp.Orderfld = " M_Applicationid,M_OrderLevel ";
            qp.OrderType = 0;
            qp.Where = string.Format("Where M_Close=0 and M_ParentID=0 and M_ApplicationID ={0}", ApplicationID);
            int RecordCount = 0;
            ArrayList lst = BusinessFacade.sys_ModuleList(qp, out RecordCount);
            Module_Main.DataSource = lst;
            Module_Main.DataBind();
        }

        private void BindButton()
        {
            HeadMenuButtonItem item0 = new HeadMenuButtonItem();
            item0.ButtonName = "角色资料";
            item0.ButtonIcon = "look.gif";
            item0.ButtonPopedom = PopedomType.List;
            item0.ButtonUrl = string.Format("RoleManager.aspx?RoleID={0}&CMD=Look",RoleID);
            HeadMenuWebControls1.ButtonList.Add(item0);
            if (CMD == "Look")
            {
                HeadMenuButtonItem item1 = new HeadMenuButtonItem();
                item1.ButtonName = "角色权限";
                item1.ButtonPopedom = PopedomType.Edit;
                item1.ButtonUrl = string.Format("?RoleID={0}&ApplicationID={1}&CMD=Edit",RoleID,ApplicationID);
                HeadMenuWebControls1.ButtonList.Add(item1);
            }
            if (CMD == "Edit")
            {
                ButtonTr_End.Visible = true;
                HeadMenuButtonItem item2 = new HeadMenuButtonItem();
                item2.ButtonName = "返回";
                item2.ButtonIcon = "back.gif";
                item2.ButtonPopedom = PopedomType.List;
                item2.ButtonUrl = "history.back(-1);";
                item2.ButtonUrlType = UrlType.JavaScript;
                HeadMenuWebControls1.ButtonList.Add(item2);
            }
        }

        #region "绑定数据事件"
        protected void Module_Main_ItemDataBound(object sender, RepeaterItemEventArgs e)
        {
            sys_ModuleTable s_Mt = (sys_ModuleTable)e.Item.DataItem;
            QueryParam qp = new QueryParam();
            qp.Orderfld = " M_OrderLevel ";
            qp.OrderType = 0;
            qp.Where = string.Format("Where M_Close=0 and M_ParentID ={0}", s_Mt.ModuleID);
            int RecordCount = 0;
            ArrayList lst = BusinessFacade.sys_ModuleList(qp, out RecordCount);
            if (lst.Count > 0)
            {
                Repeater Module_Sub = (Repeater)e.Item.FindControl("Module_Sub");
                Module_Sub.DataSource = lst;
                Module_Sub.DataBind();
            }
        }

        protected void Module_Sub_ItemDataBound(object sender, RepeaterItemEventArgs e)
        {
            sys_ModuleTable s_Mt = (sys_ModuleTable)e.Item.DataItem;
            sys_RolePermissionTable s_Rp = BusinessFacade.sys_RolePermissionDisp(RoleID, ApplicationID, s_Mt.M_PageCode);
            
            string rightString = string.Format("<img src='{0}'>",ResolveClientUrl("~/Manager/images/right.gif"));
            string wrongString = string.Format("<img src='{0}'>",ResolveClientUrl("~/Manager/images/wrong.gif"));
            string dispString = "";
            string SelectTxt = "";
            int TempStep = 1;
            for (int i = 0; i < 8; i++)
            {
                TempStep = TempStep + TempStep;
                Literal li = (Literal)e.Item.FindControl(string.Format("Lab{0}_Txt",TempStep));
                if (li != null)
                {
                    if ((s_Rp.P_Value & TempStep) == TempStep)
                    {
                        dispString = rightString;
                        SelectTxt = "checked";
                    }
                    else
                    {
                        dispString = wrongString;
                        SelectTxt = "";
                    }
                    if (CMD == "Edit")
                    {
                        dispString = string.Format("<input type=checkbox id='PageCode{0}' name='PageCode{0}' value={1}  {2}>", s_Mt.M_PageCode, TempStep, SelectTxt);
                    }
                    li.Text = dispString;
                }
            }
        }
        #endregion

        protected void Button1_Click(object sender, EventArgs e)
        {

            BusinessFacade.sys_RolePermission_Move(RoleID, ApplicationID);
            string TempPageCodeString = "";
            string[] ArrayInt;
            int PageCodeValue = 0;
            sys_RolePermissionTable s_Rt = new sys_RolePermissionTable();
            s_Rt.DB_Option_Action_ = "Insert";
            s_Rt.P_ApplicationID = ApplicationID;
            s_Rt.P_RoleID = RoleID;
            foreach (string var in Request.Form)
            {
                if (var.Length > 8)
                {

                    TempPageCodeString = var.Substring(0, 8);
                    if (TempPageCodeString == "PageCode")
                    {
                        PageCodeValue = 0;
                        TempPageCodeString = var.Substring(8, var.Length - 8);
                        ArrayInt = Request.Form[var].Split(',');
                        for (int i = 0; i < ArrayInt.Length; i++)
                        {
                            PageCodeValue = PageCodeValue + Convert.ToInt32(ArrayInt[i]);
                        }
                        s_Rt.P_PageCode = TempPageCodeString;
                        s_Rt.P_Value = PageCodeValue;
                        BusinessFacade.sys_RolePermissionInsertUpdate(s_Rt);
                        
                    }

                }
            }
            UserData.Move_RoleUserPermissionCache(RoleID);
            EventMessage.MessageBox(1, "操作成功", string.Format("修改角色({0})应用({1})权限成功！", RoleID, ApplicationID), Icon_Type.OK, Common.GetHomeBaseUrl(string.Format("RolePermissionManager.aspx?RoleID={0}&ApplicationID={1}&CMD=Look",RoleID,ApplicationID)));

        }
    }
}
