/********************************************************************************
     File:																
            SqlDataProvider.cs                         
     Description:
            Sql数据库操作类
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
using System.Data.SqlClient;
using System.Collections;
using System.Configuration;
using System.Collections.Generic;
using FrameWork.Components;
using FrameWork.web.Manager.Module.App.Components;

namespace FrameWork.web.Manager.Module.App.Data
{
    /// <summary>
    /// Sql数据库操作类
    /// </summary>
    public partial class SqlDataProvider : DataProvider
    {
        
        #region "SqlDataProvider"
        /// <summary>
        /// 数据库连接字符串
        /// </summary>
        private string ConnString = string.Empty;

        /// <summary>
        /// 构造函数
        /// </summary>
        public SqlDataProvider()
        {
            //
            // TODO: 在此处添加构造函数逻辑
            //
            ConnString = ConfigurationManager.AppSettings["MSSql"];
        }

        /// <summary>
        /// 连接数据库字符串
        /// </summary>
        /// <param name="strConn"></param>
        public SqlDataProvider(string strConn)
        {
            //
            // TODO: 在此处添加构造函数逻辑
            //
            ConnString = strConn;
        }

        /// <summary>
        /// 获取数据连接
        /// </summary>
        /// <returns></returns>
        public SqlConnection GetSqlConnection()
        {
            try
            {
                return new SqlConnection(ConnString);
            }
            catch
            {
                throw new Exception("没有提供数据庫连接字符串！");
            }
        }
        #endregion

        #region "app_News () - SQLDataProvider"
 
        /// <summary>
        /// 新增/删除/修改 app_News ()
        /// </summary>
        /// <param name="fam">app_NewsEntity实体类()</param>
        /// <returns>-1:存储过程执行失败,-2:存在相同的主键,Insert:返回插入自动ID,Update:返回更新记录数,Delete:返回删除记录数</returns>
        public override Int32 app_NewsInsertUpdateDelete(app_NewsEntity fam)
        {
            Int32 rInt = -1;
            using (SqlConnection Conn = GetSqlConnection())
            {
                SqlCommand cmd = new SqlCommand("dbo.app_News_InsertUpdateDelete", Conn);
                cmd.CommandType = CommandType.StoredProcedure;
                //设置参数
                cmd.Parameters.Add("@DataTable_Action_", SqlDbType.VarChar).Value = fam.DataTable_Action_.ToString(); //操作方法 Insert:增加 Update:修改 Delete:删除
                
                cmd.Parameters.Add("@ID", SqlDbType.Int).Value = fam.ID;  //
                cmd.Parameters.Add("@Title", SqlDbType.VarChar).Value = fam.Title;  //标题
                cmd.Parameters.Add("@Author", SqlDbType.VarChar).Value = fam.Author;  //作者
                if (fam.AddTime.HasValue)
                    cmd.Parameters.Add("@AddTime", SqlDbType.Date).Value = fam.AddTime;  //加入时间
                else
                    cmd.Parameters.Add("@AddTime", SqlDbType.Date).Value = DBNull.Value;  //加入时间
                cmd.Parameters.Add("@Content", SqlDbType.VarChar).Value = fam.Content;  //内容
                cmd.Parameters.Add("@ImagePath", SqlDbType.VarChar).Value = fam.ImagePath;  //图片路径
                cmd.Parameters.Add("@ReCommand", SqlDbType.Int).Value = fam.ReCommand;  //是否为推荐新闻
                Conn.Open();
                rInt = Convert.ToInt32(cmd.ExecuteScalar());
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

        #region "app_Notify () - SQLDataProvider"
 
        /// <summary>
        /// 新增/删除/修改 app_Notify ()
        /// </summary>
        /// <param name="fam">app_NotifyEntity实体类()</param>
        /// <returns>-1:存储过程执行失败,-2:存在相同的主键,Insert:返回插入自动ID,Update:返回更新记录数,Delete:返回删除记录数</returns>
        public override Int32 app_NotifyInsertUpdateDelete(app_NotifyEntity fam)
        {
            Int32 rInt = -1;
            using (SqlConnection Conn = GetSqlConnection())
            {
                SqlCommand cmd = new SqlCommand("dbo.app_Notify_InsertUpdateDelete", Conn);
                cmd.CommandType = CommandType.StoredProcedure;
                //设置参数
                cmd.Parameters.Add("@DataTable_Action_", SqlDbType.VarChar).Value = fam.DataTable_Action_.ToString(); //操作方法 Insert:增加 Update:修改 Delete:删除
                
                cmd.Parameters.Add("@ID", SqlDbType.Int).Value = fam.ID;  //
                cmd.Parameters.Add("@Title", SqlDbType.VarChar).Value = fam.Title;  //标题
                cmd.Parameters.Add("@Notifier", SqlDbType.VarChar).Value = fam.Notifier;  //通知部门
                if (fam.AddTime.HasValue)
                    cmd.Parameters.Add("@AddTime", SqlDbType.Date).Value = fam.AddTime;  //通知时间
                else
                    cmd.Parameters.Add("@AddTime", SqlDbType.Date).Value = DBNull.Value;  //通知时间
                cmd.Parameters.Add("@Content", SqlDbType.VarChar).Value = fam.Content;  //通知内容
                Conn.Open();
                rInt = Convert.ToInt32(cmd.ExecuteScalar());
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

        #region "app_StyleShow () - SQLDataProvider"
 
        /// <summary>
        /// 新增/删除/修改 app_StyleShow ()
        /// </summary>
        /// <param name="fam">app_StyleShowEntity实体类()</param>
        /// <returns>-1:存储过程执行失败,-2:存在相同的主键,Insert:返回插入自动ID,Update:返回更新记录数,Delete:返回删除记录数</returns>
        public override Int32 app_StyleShowInsertUpdateDelete(app_StyleShowEntity fam)
        {
            Int32 rInt = -1;
            using (SqlConnection Conn = GetSqlConnection())
            {
                SqlCommand cmd = new SqlCommand("dbo.app_StyleShow_InsertUpdateDelete", Conn);
                cmd.CommandType = CommandType.StoredProcedure;
                //设置参数
                cmd.Parameters.Add("@DataTable_Action_", SqlDbType.VarChar).Value = fam.DataTable_Action_.ToString(); //操作方法 Insert:增加 Update:修改 Delete:删除
                
                cmd.Parameters.Add("@ID", SqlDbType.Int).Value = fam.ID;  //
                cmd.Parameters.Add("@Title", SqlDbType.VarChar).Value = fam.Title;  //标题
                if (fam.AddTime.HasValue)
                    cmd.Parameters.Add("@AddTime", SqlDbType.Date).Value = fam.AddTime;  //图片加入时间
                else
                    cmd.Parameters.Add("@AddTime", SqlDbType.Date).Value = DBNull.Value;  //图片加入时间
                cmd.Parameters.Add("@Author", SqlDbType.VarChar).Value = fam.Author;  //作者
                cmd.Parameters.Add("@ImagePath", SqlDbType.VarChar).Value = fam.ImagePath;  //图片路径
                cmd.Parameters.Add("@Comment", SqlDbType.VarChar).Value = fam.Comment;  //图片注释
                Conn.Open();
                rInt = Convert.ToInt32(cmd.ExecuteScalar());
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
            using (SqlConnection Conn = GetSqlConnection())
            {
                string strSql = string.Format("select {0} from {1} where upper({2})='{3}'", table_fileds, table_name, where_fileds, where_value);
                SqlCommand cmd = new SqlCommand(strSql, Conn);
                cmd.CommandType = CommandType.Text;
                Conn.Open();
                SqlDataReader dr = cmd.ExecuteReader();
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
            int rInt = -1;
            using (SqlConnection Conn = GetSqlConnection())
            {
                string strSql = string.Format("Update {0} Set {1}  Where {2}", Table,Table_FiledsValue,Wheres);
                SqlCommand cmd = new SqlCommand(strSql, Conn);
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

        #region 公共查询数据函数Sql存储过程版
        /// <summary>
        /// 公共查询数据函数Sql存储过程版(非安全函数,传入参数请进行Sql字符串过滤)
        /// </summary>
        /// <param name="pd">委托对象</param>
        /// <param name="pp">查询字符串</param>
        /// <param name="RecordCount">返回记录总数</param>
        /// <returns>返回记录集List</returns>
        private List<T> GetRecordList<T>(PopulateDelegate<T> pd, QueryParam pp, out int RecordCount)
        {
            List<T> lst = new List<T>();
            RecordCount = 0;
            using (SqlConnection conn = GetSqlConnection())
            {
                SqlCommand cmd = new SqlCommand("dbo.SupesoftPage", conn);
                cmd.CommandType = CommandType.StoredProcedure;
                // 设置参数
                cmd.Parameters.Add("@TableName", SqlDbType.NVarChar, 500).Value = pp.TableName;
                cmd.Parameters.Add("@ReturnFields", SqlDbType.NVarChar, 500).Value = pp.ReturnFields;
                cmd.Parameters.Add("@Where", SqlDbType.NVarChar, 500).Value = pp.Where;
                cmd.Parameters.Add("@PageIndex", SqlDbType.Int).Value = pp.PageIndex;
                cmd.Parameters.Add("@PageSize", SqlDbType.Int).Value = pp.PageSize;
                cmd.Parameters.Add("@Orderfld", SqlDbType.NVarChar, 200).Value = pp.Orderfld;
                cmd.Parameters.Add("@OrderType", SqlDbType.Int).Value = pp.OrderType;
                // 执行
                conn.Open();
                SqlDataReader dr = cmd.ExecuteReader();
                Dictionary<string, string> Fileds = new Dictionary<string,string>();
                foreach (DataRow var in dr.GetSchemaTable().Select())
                {
                    Fileds.Add(var[0].ToString(), var[0].ToString());
                }
                while (dr.Read())
                {
                    lst.Add(pd(dr,Fileds));
                }
                // 取记录总数 及页数
                if (dr.NextResult())
                {
                    if (dr.Read())
                    {
                        RecordCount = Convert.ToInt32(dr["RecordCount"]);
                    }
                }

                dr.Close();
                cmd.Dispose();
                conn.Close();
            }
            return lst;
        }
        #endregion
    }
}
