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

namespace FrameWork.web.Module.FrameWork.ModuleManager
{
    public partial class moduleManager : System.Web.UI.Page
    {
        private int S_ID;
        private string S_ID_Name;
        private int ModuleID;
        private string CMD;
        public string OrderByListItems_UniqueID;
        protected void Page_Load(object sender, EventArgs e)
        {

            S_ID = (int)Common.sink("S_ID", MethodType.Get, 255, 1, DataType.Int);
            ModuleID = (int)Common.sink("ModuleID", MethodType.Get, 255, 1, DataType.Int);
            S_ID_Name = BusinessFacade.sys_ApplicationsDisp(S_ID).A_AppName;
            CMD = (string)Common.sink("CMD", MethodType.Get, 255, 0, DataType.Str);
            OrderByListItems_UniqueID = OrderByListItems.UniqueID.Replace("$","_");
            Button2.OnClientClick = string.Format("selectAll({0})", OrderByListItems_UniqueID);
            SetMenu();
            if (!Page.IsPostBack)
            {
                FrameWorkPermission.CheckPagePermission(CMD);
                OnStart();
                //判断是否有排序权限
                if (!FrameWorkPermission.CheckButtonPermission(PopedomType.Orderby))
                    TabOptionItem3.Visible = false;
            }


        }

        private void SetMenu()
        {
            Title_Txt.Text = string.Format("{0}><a href='ModuleList.aspx?S_ID={3}&AppName={1}'>{1}</a>{2}", "<a href='List.aspx'>应用列表</a>", S_ID_Name, BusinessFacade.GetModuleTitle(ModuleID), S_ID);
            TabOptionItem1.Tab_Name = "应用模块管理-" + S_ID_Name +"->分类管理";
            HeadMenuWebControls1.HeadOPTxt = S_ID_Name;

            HeadMenuButtonItem m1 = new HeadMenuButtonItem();
            m1.ButtonPopedom = PopedomType.List;
            m1.ButtonName = S_ID_Name + "模块分类列表";
            m1.ButtonIcon = "list.gif";
            m1.ButtonUrl = string.Format("ModuleList.aspx?S_ID={0}&AppName={1}", S_ID, S_ID_Name);
            HeadMenuWebControls1.ButtonList.Add(m1);
        }

        private void OnStart()
        {

            if (CMD == string.Empty)
            {
                TabOptionWebControls1.SelectIndex = 1;
            }

            //填充数据
            sys_ModuleTable SMT = new sys_ModuleTable();
            SMT = BusinessFacade.sys_ModuleDisp(ModuleID);
            this.M_ApplicationID_Txt.Text = S_ID_Name;
            if (ModuleID==0)
                this.M_PageCode.Text = SMT.M_PageCode;
            if (CMD == "New" && ModuleID != 0)
            {
                this.M_ParentID_Txt.Text = SMT.M_CName;
            }
            else
            {
                this.M_ParentID_Txt.Text = SMT.M_ParentID == 0 ? "无" : BusinessFacade.sys_ModuleDisp(SMT.M_ParentID).M_CName;
            }
            this.M_PageCode_Txt.Text = SMT.M_PageCode;
            this.M_CName_Txt.Text = SMT.M_CName;
            this.M_Directory_Txt.Text = SMT.M_Directory;
            this.M_IsSystem_Txt.Text = SMT.M_IsSystem == 0 ? "否" : "是";
            this.M_Close_Txt.Text = SMT.M_Close == 0 ? "否" : "是";

            if (CMD == "Edit")
            {
                this.M_PageCode.Text = SMT.M_PageCode;
                this.M_CName.Text = SMT.M_CName;
                this.M_Directory.Text = SMT.M_Directory;
                ListItem ditem1 = this.M_IsSystem.Items.FindByValue(SMT.M_IsSystem.ToString());
                if (ditem1 != null)
                    ditem1.Selected = true;
                ListItem ditem2 = this.M_Close.Items.FindByValue(SMT.M_Close.ToString());
                if (ditem2 != null)
                    ditem2.Selected = true;
            }

            //绑定子模块
            QueryParam qp = new QueryParam();
            qp.Orderfld = " M_Applicationid,M_OrderLevel ";
            qp.OrderType = 0;
            qp.Where = string.Format("Where M_ParentID={0} and M_Applicationid={1}", ModuleID,S_ID);
            int RecordCount = 0;
            ArrayList lst = BusinessFacade.sys_ModuleList(qp, out RecordCount);
            GridView1.DataSource = lst;
            GridView1.DataBind();

            //绑定排序
            OrderByListItems.DataSource = lst;
            OrderByListItems.DataTextField = "M_CName";
            OrderByListItems.DataValueField = "ModuleID";
            OrderByListItems.DataBind();
            if (lst.Count > 0)
                OrderByListItems.Rows = lst.Count;
            
            //判断是否隐藏数据
            if (CMD == "New" || CMD == "Edit")
                HiddenDisp();
            else
            {
                HiddenInput();
                SubmitTr.Visible = false;
            }

            //判断是否生成增加子模块按钮
            if (CMD!="New" && ModuleID !=0 && SMT.M_OrderLevel.Substring(2, 2) == "00")
            {

                HeadMenuButtonItem m2 = new HeadMenuButtonItem();
                m2.ButtonName = "模块";
                m2.ButtonPopedom = PopedomType.New;
                m2.ButtonUrl = string.Format("?CMD=New&ModuleID={0}&S_ID={1}", ModuleID, S_ID);
                HeadMenuWebControls1.ButtonList.Add(m2);
            }
            if (ModuleID !=0 && SMT.M_OrderLevel.Substring(2, 2) != "00")
            {
                TabOptionWebControls1.SelectIndex = 0;
                TabOptionItem2.Visible = false;
                TabOptionItem3.Visible = false;
                if (CMD == "Edit")
                {
                    HeadMenuButtonItem m5 = new HeadMenuButtonItem();
                    m5.ButtonIcon = "back.gif";
                    m5.ButtonName = "返回";
                    m5.ButtonPopedom = PopedomType.List;
                    m5.ButtonUrl = string.Format("?ModuleID={0}&S_ID={1}", ModuleID, S_ID);
                    HeadMenuWebControls1.ButtonList.Add(m5);
                }
            }




            //生成修改按钮
            if (ModuleID != 0 && CMD=="")
            {
                HeadMenuButtonItem m3 = new HeadMenuButtonItem();
                m3.ButtonName = "";
                m3.ButtonPopedom = PopedomType.Edit;
                m3.ButtonUrl = string.Format("?CMD=Edit&ModuleID={0}&S_ID={1}",ModuleID,S_ID);
                HeadMenuWebControls1.ButtonList.Add(m3);
            }

            //生成删除按钮
            if (CMD == "Edit")
            {
                HeadMenuButtonItem m4 = new HeadMenuButtonItem();
                m4.ButtonPopedom = PopedomType.Delete;
                m4.ButtonUrl = string.Format("DelData('?CMD=Delete&S_ID={0}&ModuleID={1}')", S_ID,ModuleID);
                m4.ButtonUrlType = UrlType.JavaScript;
                HeadMenuWebControls1.ButtonList.Add(m4);
            }

            //判断是否执行删除
            if (CMD == "Delete")
            {
                SMT.DB_Option_Action_ = "Delete";
                if (SMT.M_IsSystem != 1)
                {
                    BusinessFacade.sys_ModuleInsertUpdate(SMT);
                    //删除角色权限表
                    BusinessFacade.sys_RolePermission_DeleteForm(SMT.M_ApplicationID, SMT.M_PageCode);
                    if (lst.Count > 0)
                    {
                        foreach (sys_ModuleTable var in lst)
                        {
                            SMT.ModuleID = var.ModuleID;
                            BusinessFacade.sys_ModuleInsertUpdate(SMT);
                            //删除角色权限表
                            BusinessFacade.sys_RolePermission_DeleteForm(var.M_ApplicationID, var.M_PageCode);
                        }
                    }

                }
                EventMessage.MessageBox(1, "操作成功", "删除记录ID:(" + ModuleID + ")成功！", Icon_Type.OK, Common.GetHomeBaseUrl(string.Format("ModuleList.aspx?S_ID={0}&AppName={1}",S_ID,S_ID_Name)));
            }

            //Button1.Attributes.Add("Onclick", "javascript:return checkForm(aspnetForm);");

        }


        private void HiddenDisp()
        {
            this.M_PageCode_Txt.Visible = false;
            this.M_CName_Txt.Visible = false;
            this.M_Directory_Txt.Visible = false;
            this.M_IsSystem_Txt.Visible = false;
            this.M_Close_Txt.Visible = false;
        }

        private void HiddenInput()
        {
            this.M_PageCode.Visible = false;
            this.M_CName.Visible = false;
            this.M_Directory.Visible = false;
            this.M_IsSystem.Visible = false;
            this.M_Close.Visible = false;
        }

        protected void Button1_Click(object sender, EventArgs e)
        {
            sys_ModuleTable smt = new sys_ModuleTable();
            smt = BusinessFacade.sys_ModuleDisp(ModuleID);
            smt.M_ApplicationID = S_ID;
            smt.M_Close = (int) Common.sink(this.M_Close.UniqueID,MethodType.Post,255,1,DataType.Int);
            smt.M_CName = (string)Common.sink(this.M_CName.UniqueID, MethodType.Post, 50, 1, DataType.Str);
            smt.M_Directory = (string) Common.sink(this.M_Directory.UniqueID,MethodType.Post,255,0,DataType.Str);
            //smt.M_IsSystem = (int) Common.sink(this.M_IsSystem.UniqueID,MethodType.Post,255,1,DataType.Int);
            smt.M_PageCode = (string) Common.sink(this.M_PageCode.UniqueID,MethodType.Post,6,1,DataType.CharAndNum);
            if (CMD == "New")
            {
                if (BusinessFacade.sys_Module_CheckPK(smt.M_ApplicationID, smt.M_PageCode,0))
                    EventMessage.MessageBox(1, "数据输入出错", string.Format("存在相同的模块编码({0})", smt.M_PageCode)
                                           , Icon_Type.Error, "history.back()", UrlType.JavaScript);

                QueryParam qp = new QueryParam();
                qp.Orderfld = "M_OrderLevel";
                qp.PageIndex = 1;
                qp.PageSize = 1;
                qp.Where = string.Format("Where M_ParentID={0} and M_Applicationid={1}", ModuleID, S_ID);
                int RecordCount = 0;
                ArrayList lst = BusinessFacade.sys_ModuleList(qp, out RecordCount);
                if (ModuleID == 0)
                {
                    if (RecordCount != 0)
                        RecordCount = Convert.ToInt32(((sys_ModuleTable)lst[0]).M_OrderLevel.Substring(0,2))+1;
                    smt.M_OrderLevel = Common.FillZero(RecordCount.ToString(), 2) + "00";
                }
                else {
                    if (RecordCount !=0)
                        RecordCount = Convert.ToInt32(((sys_ModuleTable)lst[0]).M_OrderLevel.Substring(2, 2));
                    RecordCount++;
                    smt.M_OrderLevel = smt.M_OrderLevel.Substring(0, 2) + Common.FillZero(RecordCount.ToString(), 2);
                }
                smt.M_ParentID = ModuleID;
                smt.DB_Option_Action_ = "Insert";
            }
            else if (CMD == "Edit")
            {
                if (BusinessFacade.sys_Module_CheckPK(smt.M_ApplicationID, smt.M_PageCode,ModuleID))
                    EventMessage.MessageBox(1, "数据输入出错", string.Format("存在相同的模块编码({0})", smt.M_PageCode)
                                           , Icon_Type.Error, "history.back()", UrlType.JavaScript);
                smt.DB_Option_Action_ = "Update";
            }
            smt.ModuleID = ModuleID;
            if (smt.M_IsSystem!=1)
                BusinessFacade.sys_ModuleInsertUpdate(smt);
            EventMessage.MessageBox(1, "操作成功", string.Format("增加/修改模块ID({0})成功!", ModuleID), Icon_Type.OK, Common.GetHomeBaseUrl(string.Format("ModuleList.aspx?S_ID={0}&AppName={1}", S_ID, S_ID_Name)));

        }

        protected void Button2_Click(object sender, EventArgs e)
        {
            FrameWorkPermission.CheckPermissionVoid(PopedomType.Orderby);
            string ItemsList = (string)Common.sink(OrderByListItems.UniqueID, MethodType.Post, 100000, 1, DataType.Str);
            if (ItemsList.Length > 0)
            {
                string[] ItemsLists = ItemsList.Split(',');
                for (int i = 0; i < ItemsLists.Length; i++)
                {
                    
                    if (Common.GetDBType=="Oracle")
                        BusinessFacade.Update_Table_Fileds("sys_Module", string.Format("M_OrderLevel=substr(M_OrderLevel,1,2) || '{0}'", Common.FillZero((i + 1).ToString(), 2)), string.Format("ModuleID={0}", ItemsLists[i]));
                    else
                        BusinessFacade.Update_Table_Fileds("sys_Module", string.Format("M_OrderLevel=left(M_OrderLevel,2)+'{0}'", Common.FillZero((i + 1).ToString(), 2)), string.Format("ModuleID={0}", ItemsLists[i]));
                }
            }

            EventMessage.MessageBox(1, "操作成功", string.Format("排序子模块成功!"), Icon_Type.OK, Common.GetHomeBaseUrl(string.Format("ModuleList.aspx?S_ID={0}&AppName={1}", S_ID, S_ID_Name)));
        }


        public string GetStatus(int ID)
        {
            return BusinessFacade.GetStatus(ID);
        }
    }
}
