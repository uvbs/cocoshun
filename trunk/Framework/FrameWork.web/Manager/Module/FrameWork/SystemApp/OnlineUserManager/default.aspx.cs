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

namespace FrameWork.web.Module.FrameWork.OnlineUserManager
{
    public partial class _default : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            if (!IsPostBack)
            {
                BindData();
            }
        }

        private ArrayList CountOnlineList(ArrayList lst)
        {
            ArrayList lstonline = new ArrayList();
            foreach (sys_OnlineTable var in lst)
            {
                OnlineUser<string> ou = new OnlineUser<string>();
                ou.U_Guid = var.O_SessionID;
                ou.U_LastIP = var.O_Ip;
                ou.U_LastTime = var.O_LastTime;
                ou.U_LastUrl = var.O_LastUrl;
                ou.U_Name = var.O_UserName;
                ou.U_StartTime = var.O_LoginTime;
                TimeSpan ts = ou.U_LastTime - ou.U_StartTime;
                ou.U_OnlineSeconds = ts.TotalSeconds;
                ou.U_Type = true;
                lstonline.Add(ou);
            }
            return lstonline;
        }

        private void BindData()
        {
            if (Common.GetOnlineCountType == OnlineCountType.DataBase)
            {
                QueryParam qp = new QueryParam();
                qp.PageIndex = AspNetPager1.CurrentPageIndex;
                qp.PageSize = AspNetPager1.PageSize;
                int RecordCount = 0;
                ArrayList lst = BusinessFacade.sys_OnlineList(qp, out RecordCount);


                GridView1.DataSource = CountOnlineList(lst);
                GridView1.DataBind();
                this.AspNetPager1.RecordCount = RecordCount;
            }
            else
            {
                AspNetPager1.RecordCount = FrameWorkPermission.UserOnlineList.AllCount;
                ArrayList lst = new ArrayList();
                for (int i = AspNetPager1.StartRecordIndex; i <= AspNetPager1.EndRecordIndex; i++)
                {
                    lst.Add(FrameWorkPermission.UserOnlineList.GetList[i - 1]);
                }
                GridView1.DataSource = lst;
                GridView1.DataBind();
            }

        }

        protected void AspNetPager1_PageChanged(object sender, EventArgs e)
        {
            BindData();
        }

        protected void GridView1_RowCommand(object sender, GridViewCommandEventArgs e)
        {

            if (e.CommandName=="OutOnline")
            {
                FrameWorkPermission.CheckPermissionVoid(PopedomType.Delete);
                //FrameWorkPermission.UserOnlineList.RemoveUserName(e.CommandArgument.ToString().ToLower());
                BusinessFacade.InterfaceOnlineRemove(e.CommandArgument.ToString().ToLower());
                MessageBox MBx = new MessageBox();
                MBx.M_Type = 2;
                MBx.M_Title = "强制用户退出!";
                MBx.M_IconType = Icon_Type.Error;
                MBx.M_Body = string.Format("强制用户({0})退出成功！",e.CommandArgument.ToString());
                MBx.M_ButtonList.Add(new sys_NavigationUrl("返回", Common.GetHomeBaseUrl("default.aspx"), "", UrlType.Href, true));
                EventMessage.MessageBox(MBx);
                
            }
        }
    }
}
