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
using System.Data.OleDb;
using System.Text;

namespace FrameWork.web.Home
{
    public partial class NewsPic : System.Web.UI.Page
    {
         /// <summary>
        /// 数据库连接字符串
        /// </summary>
        private string ConnString = string.Empty;

        public NewsPic()
        {
            ConnString = string.Format("Provider=Microsoft.Jet.OleDb.4.0;Data Source={0}{1};Persist Security Info=True;",
                AppDomain.CurrentDomain.BaseDirectory, ConfigurationManager.AppSettings["Access"]);
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

        protected void Page_Load(object sender, EventArgs e)
        {
            if (!Page.IsPostBack)
            {
                OnStart();
            }
        }

        public string Html;

        private void OnStart()
        {
            string SQL = "SELECT TOP 5 [ID], [Title], [ImagePath] FROM [app_News] ORDER BY [AddTime] DESC";

            using (OleDbConnection Conn = GetSqlConnection())
            {
                OleDbCommand cmd = new OleDbCommand();
                cmd.CommandText = SQL;
                cmd.Connection = Conn;
                Conn.Open();
                OleDbDataReader reader = cmd.ExecuteReader();

                // 图片
                StringBuilder sb = new StringBuilder("<div id='KinSlideshow' style='visibility:hidden;'>\n");
                for (int i = 0; i < 5 && reader.Read();i++ )
                {
                    string ID = reader["ID"].ToString();
                    string Title = reader["Title"].ToString();
                    string ImagePath = reader["ImagePath"].ToString();

                    sb.Append("<a target='_blank' href='/template/news1.aspx?ID=");
                    sb.Append(ID);
                    sb.Append("' ><img src='");
                    sb.Append(Common.UpLoadDir + "NewsImages/");
                    sb.Append("s_" + ImagePath);
                    sb.Append("' alt='");
                    sb.Append(Title);
                    sb.Append("'");
                    sb.Append("width='255' height='180' /></a>");
                    sb.AppendLine();
                }
                sb.AppendLine("</div>");

                Html = sb.ToString();

                cmd.Dispose();
                Conn.Dispose();
                Conn.Close();
            }

        }
    }
}
