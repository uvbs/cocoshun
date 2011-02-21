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
    public partial class NewsTemplate : System.Web.UI.Page
    {
         /// <summary>
        /// 数据库连接字符串
        /// </summary>
        private string ConnString = string.Empty;

        public NewsTemplate()
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


        private int ID = (int)Common.sink("ID", MethodType.Get, 4, 0, DataType.Int);
        private static string SQL = "SELECT * FROM app_News where ID=@ID";


        private void OnStart()
        {
            
            using (OleDbConnection Conn = GetSqlConnection())
            {
                OleDbCommand cmd = new OleDbCommand();
                Conn.Open();
                cmd.Connection = Conn;
                cmd.CommandText = SQL;

                cmd.Parameters.Add("@ID", OleDbType.Integer).Value = ID;
                OleDbDataReader reader = cmd.ExecuteReader();

                if(reader.HasRows)
                {
                    reader.Read();

                    NewsTitle.Text = reader["Title"].ToString();

                    NewsAuthorTime.Text = reader["Author"].ToString() + "    " + Common.ConvertDate((DateTime)reader["AddTime"]);

                    string ImagePath = reader["ImagePath"].ToString();
                    if(ImagePath.Length == 0)
                    {
                        NewsImage.Visible = false;
                    }else
                    {
                        NewsImage.ImageUrl = Common.UpLoadDir + "NewsImages/" + ImagePath;
                    }
                    ImageComment.Text = reader["ImageComment"].ToString();

                    string content =  reader["Content"].ToString();
                    if(content.Length > 0)
                    {
                        NewsContent.Text = content.Replace(" ", "&nbsp;&nbsp;");
                        NewsContent.Text = NewsContent.Text.Replace("\r\n", "</br>");
                        
                    }
                    
                }
  

                cmd.Dispose();
                Conn.Dispose();
                Conn.Close();
            }

        }
    }
}
