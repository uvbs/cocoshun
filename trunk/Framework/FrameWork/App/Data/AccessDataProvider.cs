/********************************************************************************
     File:																
            AccessDataProvider.cs                         
     Description:
            Access数据库操作类
     Author:									
            DDBuildTools
            http://FrameWork.supesoft.com
     Finish DateTime:
            2011/1/5 9:15:01
     History:
*********************************************************************************/
using System;
using System.Web;
using System.Data;
using System.Data.OleDb;
using System.Collections;
using System.Configuration;
using System.Collections.Generic;
using System.Text;
using FrameWork.web.Manager.Module.App.Components;
using FrameWork.Components;

namespace FrameWork.web.Manager.Module.App.Data
{
    /// <summary>
    /// Access数据库访问类
    /// </summary>
    public partial class AccessDataProvider : DataProvider
    {
        #region "AccessDataProvider"
        /// <summary>
        /// 数据库连接字符串
        /// </summary>
        private string ConnString = string.Empty;
        /// <summary>
        /// 构造函数
        /// </summary>
        public AccessDataProvider()
        {
            //
            // TODO: 在此处添加构造函数逻辑
            //
            ConnString = string.Format("Provider=Microsoft.Jet.OleDb.4.0;Data Source={0}{1};Persist Security Info=True;", AppDomain.CurrentDomain.BaseDirectory, ConfigurationManager.AppSettings["Access"]);
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
                throw new Exception("没有提供数据庫连接字符串Access！");
            }
        }
        #endregion

        #region "app_News () - AccessDataProvider"

        /// <summary>
        /// 新增/删除/修改 app_News ()
        /// </summary>
        /// <param name="fam">app_NewsEntity实体类实体类()</param>
        /// <returns>-1:存储过程执行失败,-2:存在相同的主键,Insert:返回插入自动ID,Update:返回更新记录数,Delete:返回删除记录数</returns>
        public override Int32 app_NewsInsertUpdateDelete(app_NewsEntity fam)
        {
            Int32 rInt = -1;
            using (OleDbConnection Conn = GetSqlConnection())
            {
                string CommTxt;
                OleDbCommand cmd = new OleDbCommand();
                cmd.Connection = Conn;
                Conn.Open();
                if (fam.DataTable_Action_.ToString() == "Insert")
                {

                    CommTxt = "Insert into 	app_News(Title,Author,AddTime,Content,ImagePath,ImageComment,ReCommand)VALUES(@Title,@Author,@AddTime,@Content,@ImagePath,@ImageComment,@ReCommand)";
                    cmd.CommandText = CommTxt;


                    cmd.Parameters.Add("@Title", OleDbType.VarWChar).Value = fam.Title; //标题
                    cmd.Parameters.Add("@Author", OleDbType.VarWChar).Value = fam.Author; //作者
                    if (fam.AddTime.HasValue)
                        cmd.Parameters.Add("@AddTime", OleDbType.Date).Value = fam.AddTime; //加入时间
                    else
                        cmd.Parameters.Add("@AddTime", OleDbType.Date).Value = DBNull.Value; //加入时间
                    cmd.Parameters.Add("@Content", OleDbType.VarWChar).Value = fam.Content; //内容
                    cmd.Parameters.Add("@ImagePath", OleDbType.VarWChar).Value = fam.ImagePath; //图片路径
                    cmd.Parameters.Add("@ImageComment", OleDbType.VarWChar).Value = fam.ImageComment; //图片注释

                    cmd.Parameters.Add("@ReCommand", OleDbType.Boolean).Value = fam.ReCommand; //是否为推荐新闻
                }
                else if (fam.DataTable_Action_.ToString() == "Update")
                {

                    CommTxt = "UPDATE app_News SET Title = @Title,Author = @Author,AddTime = @AddTime,Content = @Content,ImagePath = @ImagePath,ImageComment = @ImageComment,ReCommand = @ReCommand WHERE (ID = @ID)";
                    cmd.CommandText = CommTxt;

                    cmd.Parameters.Add("@Title", OleDbType.VarWChar).Value = fam.Title; //标题
                    cmd.Parameters.Add("@Author", OleDbType.VarWChar).Value = fam.Author; //作者
                    if (fam.AddTime.HasValue)
                        cmd.Parameters.Add("@AddTime", OleDbType.Date).Value = fam.AddTime; //加入时间
                    else
                        cmd.Parameters.Add("@AddTime", OleDbType.Date).Value = DBNull.Value; //加入时间
                    cmd.Parameters.Add("@Content", OleDbType.VarWChar).Value = fam.Content; //内容
                    cmd.Parameters.Add("@ImagePath", OleDbType.VarWChar).Value = fam.ImagePath; //图片路径
                    cmd.Parameters.Add("@ImageComment", OleDbType.VarWChar).Value = fam.ImageComment; //图片注释
                    cmd.Parameters.Add("@ReCommand", OleDbType.Boolean).Value = fam.ReCommand; //是否为推荐新闻
                    cmd.Parameters.Add("@", OleDbType.Integer).Value = fam.ID; //
                }
                else if (fam.DataTable_Action_.ToString() == "Delete")
                {
                    CommTxt = "Delete from  app_News  WHERE (ID = @ID)";
                    cmd.CommandText = CommTxt;
                    cmd.Parameters.Add("@ID", OleDbType.Integer).Value = fam.ID; //
                }
                else
                    throw new ApplicationException("无法识别的操作命令!");
                
                rInt = cmd.ExecuteNonQuery();
                if (fam.DataTable_Action_.ToString() == "Insert")
                {
                    cmd.CommandText = "SELECT @@identity";
                    rInt = Convert.ToInt32(cmd.ExecuteScalar());
                }
                cmd.Dispose();
                Conn.Dispose();
                Conn.Close();
            }
            return rInt;
        }

        /// <summary>
        /// 返回app_NewsEntity实体类的List对象 ()
        /// </summary>
        /// <param name="qp">查询类(非安全函数,传入参数请进行Sql字符串过滤)</param>
        /// <param name="RecordCount">返回记录总数</param>
        /// <returns>app_NewsEntity实体类的List对象()</returns>
        public override List<app_NewsEntity> app_NewsList(QueryParam qp, out int RecordCount)
        {
            PopulateDelegate<app_NewsEntity> mypd = new PopulateDelegate<app_NewsEntity>(base.Populateapp_NewsEntity);
            return this.GetRecordList(mypd, qp, out RecordCount);
        }
        #endregion

        #region "app_Notify () - AccessDataProvider"

        /// <summary>
        /// 新增/删除/修改 app_Notify ()
        /// </summary>
        /// <param name="fam">app_NotifyEntity实体类实体类()</param>
        /// <returns>-1:存储过程执行失败,-2:存在相同的主键,Insert:返回插入自动ID,Update:返回更新记录数,Delete:返回删除记录数</returns>
        public override Int32 app_NotifyInsertUpdateDelete(app_NotifyEntity fam)
        {
            Int32 rInt = -1;
            using (OleDbConnection Conn = GetSqlConnection())
            {
                string CommTxt;
                OleDbCommand cmd = new OleDbCommand();
                cmd.Connection = Conn;
                Conn.Open();
                if (fam.DataTable_Action_.ToString() == "Insert")
                {
                    
                    CommTxt = "Insert into 	app_Notify(Title,Notifier,AddTime,Content)VALUES(@Title,@Notifier,@AddTime,@Content)";
                    cmd.CommandText = CommTxt;

                    cmd.Parameters.Add("@Title", OleDbType.VarWChar).Value = fam.Title; //标题
                    cmd.Parameters.Add("@Notifier", OleDbType.VarWChar).Value = fam.Notifier; //通知部门
                    if (fam.AddTime.HasValue)
                        cmd.Parameters.Add("@AddTime", OleDbType.Date).Value = fam.AddTime; //通知时间
                    else
                        cmd.Parameters.Add("@AddTime", OleDbType.Date).Value = DBNull.Value; //通知时间
                    cmd.Parameters.Add("@Content", OleDbType.VarWChar).Value = fam.Content; //通知内容
                }
                else if (fam.DataTable_Action_.ToString() == "Update")
                {
                    
                    CommTxt = "UPDATE app_Notify SET Title = @Title,Notifier = @Notifier,AddTime = @AddTime,Content = @Content WHERE (ID = @ID)";
                    cmd.CommandText = CommTxt;

                    cmd.Parameters.Add("@Title", OleDbType.VarWChar).Value = fam.Title; //标题
                    cmd.Parameters.Add("@Notifier", OleDbType.VarWChar).Value = fam.Notifier; //通知部门
                    if (fam.AddTime.HasValue)
                        cmd.Parameters.Add("@AddTime", OleDbType.Date).Value = fam.AddTime; //通知时间
                    else
                        cmd.Parameters.Add("@AddTime", OleDbType.Date).Value = DBNull.Value; //通知时间
                    cmd.Parameters.Add("@Content", OleDbType.VarWChar).Value = fam.Content; //通知内容
                    cmd.Parameters.Add("@", OleDbType.Integer).Value = fam.ID; //
                }
                else if (fam.DataTable_Action_.ToString() == "Delete")
                {
                    CommTxt = "Delete from  app_Notify  WHERE (ID = @ID)";
                    cmd.CommandText = CommTxt;
                    cmd.Parameters.Add("@ID", OleDbType.Integer).Value = fam.ID; //
                }
                else
                    throw new ApplicationException("无法识别的操作命令!");
                
                rInt = cmd.ExecuteNonQuery();
                if (fam.DataTable_Action_.ToString() == "Insert")
                {
                    cmd.CommandText = "SELECT @@identity";
                    rInt = Convert.ToInt32(cmd.ExecuteScalar());
                }
                cmd.Dispose();
                Conn.Dispose();
                Conn.Close();
            }
            return rInt;
        }

        /// <summary>
        /// 返回app_NotifyEntity实体类的List对象 ()
        /// </summary>
        /// <param name="qp">查询类(非安全函数,传入参数请进行Sql字符串过滤)</param>
        /// <param name="RecordCount">返回记录总数</param>
        /// <returns>app_NotifyEntity实体类的List对象()</returns>
        public override List<app_NotifyEntity> app_NotifyList(QueryParam qp, out int RecordCount)
        {
            PopulateDelegate<app_NotifyEntity> mypd = new PopulateDelegate<app_NotifyEntity>(base.Populateapp_NotifyEntity);
            return this.GetRecordList(mypd, qp, out RecordCount);
        }
        #endregion

        #region "app_StyleShow () - AccessDataProvider"

        /// <summary>
        /// 新增/删除/修改 app_StyleShow ()
        /// </summary>
        /// <param name="fam">app_StyleShowEntity实体类实体类()</param>
        /// <returns>-1:存储过程执行失败,-2:存在相同的主键,Insert:返回插入自动ID,Update:返回更新记录数,Delete:返回删除记录数</returns>
        public override Int32 app_StyleShowInsertUpdateDelete(app_StyleShowEntity fam)
        {
            Int32 rInt = -1;
            using (OleDbConnection Conn = GetSqlConnection())
            {
                string CommTxt;
                OleDbCommand cmd = new OleDbCommand();
                cmd.Connection = Conn;
                Conn.Open();
                if (fam.DataTable_Action_.ToString() == "Insert")
                {
                    
                    CommTxt = "Insert into 	app_StyleShow(Title,AddTime,Author,ImagePath,Comment)VALUES(@Title,@AddTime,@Author,@ImagePath,@Comment)";
                    cmd.CommandText = CommTxt;

                    cmd.Parameters.Add("@Title", OleDbType.VarWChar).Value = fam.Title; //标题
                    if (fam.AddTime.HasValue)
                        cmd.Parameters.Add("@AddTime", OleDbType.Date).Value = fam.AddTime; //图片加入时间
                    else
                        cmd.Parameters.Add("@AddTime", OleDbType.Date).Value = DBNull.Value; //图片加入时间
                    cmd.Parameters.Add("@Author", OleDbType.VarWChar).Value = fam.Author; //作者
                    cmd.Parameters.Add("@ImagePath", OleDbType.VarWChar).Value = fam.ImagePath; //图片路径
                    cmd.Parameters.Add("@Comment", OleDbType.VarWChar).Value = fam.Comment; //图片注释
                }
                else if (fam.DataTable_Action_.ToString() == "Update")
                {
                    
                    CommTxt = "UPDATE app_StyleShow SET Title = @Title,AddTime = @AddTime,Author = @Author,ImagePath = @ImagePath,Comment = @Comment WHERE (ID = @ID)";
                    cmd.CommandText = CommTxt;

                    cmd.Parameters.Add("@Title", OleDbType.VarWChar).Value = fam.Title; //标题
                    if (fam.AddTime.HasValue)
                        cmd.Parameters.Add("@AddTime", OleDbType.Date).Value = fam.AddTime; //图片加入时间
                    else
                        cmd.Parameters.Add("@AddTime", OleDbType.Date).Value = DBNull.Value; //图片加入时间
                    cmd.Parameters.Add("@Author", OleDbType.VarWChar).Value = fam.Author; //作者
                    cmd.Parameters.Add("@ImagePath", OleDbType.VarWChar).Value = fam.ImagePath; //图片路径
                    cmd.Parameters.Add("@Comment", OleDbType.VarWChar).Value = fam.Comment; //图片注释
                    cmd.Parameters.Add("@", OleDbType.Integer).Value = fam.ID; //
                }
                else if (fam.DataTable_Action_.ToString() == "Delete")
                {
                    CommTxt = "Delete from  app_StyleShow  WHERE (ID = @ID)";
                    cmd.CommandText = CommTxt;
                    cmd.Parameters.Add("@ID", OleDbType.Integer).Value = fam.ID; //
                }
                else
                    throw new ApplicationException("无法识别的操作命令!");
                
                rInt = cmd.ExecuteNonQuery();
                if (fam.DataTable_Action_.ToString() == "Insert")
                {
                    cmd.CommandText = "SELECT @@identity";
                    rInt = Convert.ToInt32(cmd.ExecuteScalar());
                }
                cmd.Dispose();
                Conn.Dispose();
                Conn.Close();
            }
            return rInt;
        }

        /// <summary>
        /// 返回app_StyleShowEntity实体类的List对象 ()
        /// </summary>
        /// <param name="qp">查询类(非安全函数,传入参数请进行Sql字符串过滤)</param>
        /// <param name="RecordCount">返回记录总数</param>
        /// <returns>app_StyleShowEntity实体类的List对象()</returns>
        public override List<app_StyleShowEntity> app_StyleShowList(QueryParam qp, out int RecordCount)
        {
            PopulateDelegate<app_StyleShowEntity> mypd = new PopulateDelegate<app_StyleShowEntity>(base.Populateapp_StyleShowEntity);
            return this.GetRecordList(mypd, qp, out RecordCount);
        }
        #endregion


        #region "获取表中字段值"
        /// <summary>
        /// 获取表中字段值(非安全函数,传入参数请进行Sql字符串过滤)
        /// </summary>
        /// <param name="table_name">表名</param>
        /// <param name="table_fileds">字段</param>
        /// <param name="where_fileds">查询条件字段</param>
        /// <param name="where_value">查询值</param>
        /// <returns>返回字段值</returns>
        public override string get_table_fileds(string table_name, string table_fileds, string where_fileds, string where_value)
        {
            string rStr = "";
            using (OleDbConnection Conn = GetSqlConnection())
            {
                string strSql = string.Format("select {0} from {1} where ucase({2})='{3}'", table_fileds, table_name, where_fileds, where_value);
                OleDbCommand cmd = new OleDbCommand(strSql, Conn);
                cmd.CommandType = CommandType.Text;
                Conn.Open();
                OleDbDataReader dr = cmd.ExecuteReader();
                if (dr.Read())
                {
                    rStr = dr[0].ToString();
                }
                dr.Close();
                dr.Dispose();
                cmd.Dispose();
                Conn.Dispose();
                Conn.Close();
            }
            return rStr;
        }
        #endregion

        #region "更新表中字段值"
        /// <summary>
        /// 更新表中字段值(非安全函数,传入参数请进行Sql字符串过滤)
        /// </summary>
        /// <param name="Table">表名</param>
        /// <param name="Table_FiledsValue">需要更新值(不用带Set)</param>
        /// <param name="Wheres">更新条件(不用带Where)</param>
        /// <returns>-1:失败,其它值成功</returns>
        public override int Update_Table_Fileds(string Table, string Table_FiledsValue, string Wheres)
        {
            int rInt = 0;
            using (OleDbConnection Conn = GetSqlConnection())
            {
                string strSql = string.Format("Update {0} Set {1}  Where {2}", Table, Table_FiledsValue, Wheres);
                OleDbCommand cmd = new OleDbCommand(strSql, Conn);
                cmd.CommandType = CommandType.Text;
                Conn.Open();
                rInt = Convert.ToInt32(cmd.ExecuteScalar());
                cmd.Dispose();
                Conn.Dispose();
                Conn.Close();
            }
            return rInt;
        }
        #endregion
          
        #region "公共查询数据函数Access版"
        /// <summary>
        /// 公共查询数据函数Access版(非安全函数,传入参数请进行Sql字符串过滤)
        /// </summary>
        /// <param name="pd">委托对象</param>
        /// <param name="pp">查询字符串</param>
        /// <param name="RecordCount">返回记录总数</param>
        /// <returns>返回记录集List</returns>
        private List<T> GetRecordList<T>(PopulateDelegate<T> pd, QueryParam pp, out int RecordCount)
        {
            List<T> lst = new List<T>();
            RecordCount = 0;
            using (OleDbConnection Conn = GetSqlConnection())
            {
                StringBuilder sb = new StringBuilder();
                OleDbCommand cmd = new OleDbCommand();
                OleDbDataReader dr = null;
                cmd.Connection = Conn;

                int TotalRecordForPageIndex = pp.PageIndex * pp.PageSize;
                string OrderBy;
                string CutOrderBy;
                if (pp.OrderType == 1)
                {
                    OrderBy = " Order by " + pp.Orderfld.Replace(","," desc,") + " desc ";
                    CutOrderBy = " Order by " + pp.Orderfld.Replace(","," asc,") + " asc ";
                }
                else
                {
                    OrderBy = " Order by " + pp.Orderfld.Replace(",", " asc,") + " asc ";
                    CutOrderBy = " Order by " + pp.Orderfld.Replace(",", " desc,") + " desc ";
                }
                sb.AppendFormat("SELECT * FROM (SELECT TOP {0} * FROM (SELECT TOP {1} {2}	FROM {3} {4} {5}) TB2	{6}) TB3 {5} ", pp.PageSize, TotalRecordForPageIndex, pp.ReturnFields, pp.TableName, pp.Where, OrderBy, CutOrderBy);
                cmd.CommandText = sb.ToString();
                Conn.Open();
                dr = cmd.ExecuteReader();
                Dictionary<string, string> Fileds = new Dictionary<string,string>();
                foreach (DataRow var in dr.GetSchemaTable().Select())
                {
                    Fileds.Add(var[0].ToString(), var[0].ToString());
                }
                while (dr.Read())
                {
                    lst.Add(pd(dr,Fileds));
                }
                dr.Close();
                cmd.Parameters.Clear();
                // 取记录总数
                cmd.CommandText = string.Format("SELECT Count(1) From {0} {1}", pp.TableName, pp.Where);
                RecordCount = Convert.ToInt32(cmd.ExecuteScalar());
                dr.Dispose();
                dr.Close();
                cmd.Dispose();
                Conn.Dispose();
                Conn.Close();
            }
            return lst;
        }
        #endregion
    }
} 
  