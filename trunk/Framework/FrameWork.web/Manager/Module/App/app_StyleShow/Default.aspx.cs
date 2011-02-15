/********************************************************************************
     File:																
            Default.aspx.cs                         
     Description:
            列表
     Author:									
            DDBuildTools
            http://FrameWork.supesoft.com
     Finish DateTime:
            2011/1/5 9:15:01
     History:
*********************************************************************************/
using System;
using System.Data;
using System.Configuration;
using System.Collections;
using System.Collections.Generic;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Web.UI.HtmlControls;
using System.Text;

using FrameWork.web.Manager.Module.App;
using FrameWork.web.Manager.Module.App.Components;
using FrameWork;
using FrameWork.Components;
using System.Data.OleDb;

namespace FrameWork.web.Manager.Module.App.app_StyleShow
{
    public partial class Default : System.Web.UI.Page
    {
         /// <summary>
        /// 数据库连接字符串
        /// </summary>
        private string ConnString = string.Empty;

        public Default()
        {
            ConnString = string.Format("Provider=Microsoft.Jet.OleDb.4.0;Data Source={0}{1};Persist Security Info=True;",
                AppDomain.CurrentDomain.BaseDirectory, ConfigurationManager.AppSettings["Access"]);
        }

        protected void Page_Load(object sender, EventArgs e)
        {
            if (!Page.IsPostBack)
            {
                BindDataList();
            }
        }

                /// <summary>
        /// 获取数据连接
        /// </summary>
        /// <returns></returns>
        public OleDbConnection GetSqlConnection()
        {
            try
            {
                return new OleDbConnection(ConnString);
            }
            catch
            {
                throw new Exception("没有提供数据库连接字符串Access！");
            }
        }

        /// <summary>
        /// 绑定数据
        /// </summary>
        private void BindDataList()
        {
            QueryParam qp = new QueryParam();
            qp.Where = SearchTerms;
            qp.PageIndex = AspNetPager1.CurrentPageIndex;
            qp.PageSize = AspNetPager1.PageSize;
            qp.Orderfld = Orderfld;
            qp.OrderType = OrderType;
            int RecordCount = 0;
            List<app_StyleShowEntity> lst = BusinessFacadeFrameWork.app_StyleShowList(qp, out RecordCount);
            GridView1.DataSource = lst;
            GridView1.DataBind();
            this.AspNetPager1.RecordCount = RecordCount;
        }
        
        /// <summary>
        /// 点击分页事件
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        protected void AspNetPager1_PageChanged(object sender, EventArgs e)
        {
            BindDataList();
        }

        /// <summary>
        /// 查询条件
        /// </summary>
        private string SearchTerms
        {
            get
            {
                if (ViewState["SearchTerms"] == null)
                    ViewState["SearchTerms"] = " Where 1=1 ";
                return (string)ViewState["SearchTerms"];
            }
            set { ViewState["SearchTerms"] = value; }
        }

        /// <summary>
        /// 查询数据
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        protected void Button1_Click(object sender, EventArgs e)
        {
            
            
            
            
                        
            StringBuilder sb = new StringBuilder();
            sb.Append(" Where 1=1 ");
                    
                    
                    
                    
                    
            ViewState["SearchTerms"] = sb.ToString();
            BindDataList();
            TabOptionWebControls1.SelectIndex = 0;
        }
        
        #region "排序"
        protected void GridView1_Sorting(object sender, GridViewSortEventArgs e)
        {
            if (Orderfld == e.SortExpression)
            {
                if (OrderType == 0)
                {
                    OrderType = 1;
                }
                else
                {
                    OrderType = 0;
                }
            }
            Orderfld = e.SortExpression;
            BindDataList();
        }

        /// <summary>
        /// 排序字段
        /// </summary>
        public string Orderfld
        {
            get
            {
                if (ViewState["sortOrderfld"] == null)

                    ViewState["sortOrderfld"] = "ID";

                return (string)ViewState["sortOrderfld"];
            }
            set
            {
                ViewState["sortOrderfld"] = value;
            }
        }

        /// <summary>
        /// 排序类型 1:降序 0:升序
        /// </summary>
        public int OrderType
        {

            get
            {

                if (ViewState["sortOrderType"] == null)
                    ViewState["sortOrderType"] = 1;

                return (int)ViewState["sortOrderType"];


            }

            set { ViewState["sortOrderType"] = value; }

        }
        /// <summary>
        /// 排序事件
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        protected void GridView1_RowCreated(object sender, GridViewRowEventArgs e)
        {
            Int32 DataIDX = 0;
            if (e.Row.RowType == DataControlRowType.Header)
            {
                if (FrameWorkPermission.CheckButtonPermission(PopedomType.Delete))
                {
                    Button2.Visible = true;
                    //增加check列头全选
                    TableCell cell = new TableCell();
                    cell.Width = Unit.Pixel(5);
                    cell.Text = " <input id='CheckboxAll' value='0' type='checkbox' onclick='SelectAll()'/>";
                    e.Row.Cells.AddAt(0, cell);
                }
                
                foreach (TableCell var in e.Row.Cells)
                {
                    if (var.Controls.Count > 0 && var.Controls[0] is LinkButton)
                    {
                        string Colume = ((LinkButton)var.Controls[0]).CommandArgument;
                        if (Colume == Orderfld)
                        {

                            LinkButton l = (LinkButton)var.Controls[0];
                            l.Text += string.Format("<img src='{0}' border='0'>", (OrderType == 0) ? Page.ResolveUrl("~/Manager/images/sort_asc.gif") : Page.ResolveUrl("~/Manager/images/sort_desc.gif"));
                            //Image Img = new Image();
                            //SortDirection a = GridView1.SortDirection;
                            //Img.ImageUrl = (a == SortDirection.Ascending) ? "i_p_sort_asc.gif" : "i_p_sort_desc.gif";
                            //var.Controls.Add(Img);
                        }
                    }
                }
            }
            else
            {
                if (FrameWorkPermission.CheckButtonPermission(PopedomType.Delete))
                {
                    //增加行选项
                    DataIDX = Convert.ToInt32(DataBinder.Eval(e.Row.DataItem, "ID"));
                    TableCell cell = new TableCell();
                    cell.Width = Unit.Pixel(5);
                    cell.Text = string.Format(" <input name='Checkbox' id='Checkbox' value='{0}' type='checkbox' />", DataIDX);
                    e.Row.Cells.AddAt(0, cell);
                }
            }
        }
        #endregion
        
        /// <summary>
        /// 删除
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        [PopedomTypeAttaible(PopedomType.Delete)]
        [System.Security.Permissions.PrincipalPermission(System.Security.Permissions.SecurityAction.Demand, Role = "OR")]
        protected void Button2_Click(object sender, EventArgs e)
        {
            string Checkbox_Value = (string)Common.sink("Checkbox", MethodType.Post, 2000, 1, DataType.Str);
            string[] Checkbox_Value_Array = Checkbox_Value.Split(',');
            Int32 IDX = 0;
            for (int i = 0; i < Checkbox_Value_Array.Length; i++)
            {
                if (Int32.TryParse(Checkbox_Value_Array[i], out IDX))
                {
                    app_StyleShowEntity et = new app_StyleShowEntity();
                    et.DataTable_Action_ = DataTable_Action.Delete;
                    et.ID = IDX;
                    BusinessFacadeFrameWork.app_StyleShowInsertUpdateDelete(et);
                    removeRelationData(et);
                }
            }

            EventMessage.MessageBox(1, "批量删除成功", string.Format("批量删除({0})成功!", Checkbox_Value), Icon_Type.OK, Common.GetHomeBaseUrl("default.aspx"));
        }


        /// <summary>
        /// 删除图片
        /// </summary>
        private static void removeImage(string ImagePath)
        {
            if (ImagePath.Length > 0)
            {
                FileUpLoadCommon.DeleteFile(string.Format("{0}{1}{2}", Common.UpLoadDir, "StyleShowImages/", ImagePath));
                FileUpLoadCommon.DeleteFile(string.Format("{0}{1}s_{2}", Common.UpLoadDir, "StyleShowImages/", ImagePath));
            }
        }

        protected void removeRelationData(app_StyleShowEntity ut)
        {
            try
            {
                int StyleID = ut.ID;

                using (OleDbConnection Conn = GetSqlConnection())
                {
                    string CommTxt;
                    OleDbCommand cmd = new OleDbCommand();
                    cmd.Connection = Conn;
                    Conn.Open();

                    CommTxt = "SELECT b.Path FROM app_Styles_Images AS a,app_Images AS b WHERE a.ImageID=b.ID and a.StyleID=@StyleID";
                    cmd.CommandText = CommTxt;
                    cmd.Parameters.Add("@StyleID", OleDbType.Integer).Value = StyleID;

                    OleDbDataReader dr = cmd.ExecuteReader();
                    while(dr.Read())
                    {
                        string ImagePath = dr[0].ToString();
                        removeImage(ImagePath);
                    }
                    
                    cmd.Dispose();
                    

                    cmd = new OleDbCommand();
                    cmd.Connection = Conn;
                    CommTxt = "delete from app_Images where ID in (select ImageID from app_Styles_Images where StyleID=@StyleID)";
                    cmd.CommandText = CommTxt;
                    cmd.Parameters.Add("@StyleID", OleDbType.Integer).Value = StyleID; 
                    cmd.ExecuteNonQuery();
                    cmd.Dispose();

                    cmd = new OleDbCommand();
                    cmd.Connection = Conn;
                    CommTxt = "delete from app_Styles_Images where StyleID=@StyleID";
                    cmd.CommandText = CommTxt;
                    cmd.Parameters.Add("@StyleID", OleDbType.Integer).Value = StyleID; 
                    cmd.ExecuteNonQuery();
                    cmd.Dispose();

                    Conn.Dispose();
                    Conn.Close();

                }
            }
            catch (System.Exception e)
            {

            }
        }
    }
}
