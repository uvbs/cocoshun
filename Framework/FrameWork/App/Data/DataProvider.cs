/********************************************************************************
     File:																
            DataProvider.cs                         
     Description:
            抽象数据操作类
     Author:									
            DDBuildTools
            http://FrameWork.supesoft.com
     Finish DateTime:
			2011/1/5 9:15:01
     History:
*********************************************************************************/
using System;
using System.Collections.Generic;
using System.Text;
using System.Data;
using System.Collections;
using FrameWork.Components;
using FrameWork.web.Manager.Module.App.Components;

namespace FrameWork.web.Manager.Module.App.Data
{
    /// <summary>
    /// 委托将DataReader转为实体类
    /// </summary>
    /// <param name="dr">记录集</param>
    /// <param name="Fileds">字段名列表</param>
    /// <returns></returns>
    public delegate T PopulateDelegate<T>(IDataReader dr,Dictionary<string,string> Fileds);

    /// <summary>
    /// 数据抽象类
    /// </summary>
    public abstract partial class DataProvider
    {
        
        #region "DataProvider Instance"
        private static DataProvider _defaultInstance = null;
        static DataProvider()
        {
            DataProvider dataProvider;
            if (FrameWork.Common.GetDBType == "MsSql")
                dataProvider = new SqlDataProvider();
            else if (FrameWork.Common.GetDBType == "Access")
                dataProvider = new AccessDataProvider();
            else
                throw new ApplicationException("数据库配置不对！");
            _defaultInstance = dataProvider;
        }

        /// <summary>
        /// 数据访问抽象层实例
        /// </summary>
        /// <returns></returns>
        public static DataProvider Instance()
        {

            return _defaultInstance;
        }

        /// <summary>
        /// 数据访问抽象层实例
        /// </summary>
        /// <param name="strConn">数据库连接字符串</param>
        /// <returns></returns>
        public static DataProvider Instance(string strConn)
        {
            return new SqlDataProvider(strConn);
        }
        #endregion
        

        #region "app_News() - DataProvider"
 
        /// <summary>
        /// 新增/删除/修改 app_NewsEntity ()
        /// </summary>
        /// <param name="fam">app_News实体类</param>
        /// <returns>-1:存储过程执行失败,-2:存在相同的主键,Insert:返回插入自动ID,Update:返回更新记录数,Delete:返回删除记录数</returns>
        public abstract Int32 app_NewsInsertUpdateDelete(app_NewsEntity fam);

        /// <summary>
        /// 返回app_NewsEntity实体类的List对象 ()
        /// </summary>
        /// <param name="qp">查询类(非安全函数,传入参数请进行Sql字符串过滤)</param>
        /// <param name="RecordCount">返回记录总数</param>
        /// <returns>app_NewsEntity实体类的List对象()</returns>
        public abstract List<app_NewsEntity> app_NewsList(QueryParam qp, out int RecordCount);

        /// <summary>
        /// 将记录集转为app_NewsEntity实体类 ()
        /// </summary>
        /// <param name="dr">记录集</param>
        /// <param name="Fileds">字段名列表</param>
        /// <returns>app_NewsEntity</returns>
        protected app_NewsEntity Populateapp_NewsEntity(IDataReader dr,Dictionary<string,string> Fileds)
        {
            app_NewsEntity nc = new app_NewsEntity();

            if (Fileds.ContainsKey("ID") && !Convert.IsDBNull(dr["ID"])) nc.ID = Convert.ToInt32(dr["ID"]); // 
            if (Fileds.ContainsKey("Title") && !Convert.IsDBNull(dr["Title"])) nc.Title = Convert.ToString(dr["Title"]); // 标题
            if (Fileds.ContainsKey("Author") && !Convert.IsDBNull(dr["Author"])) nc.Author = Convert.ToString(dr["Author"]); // 作者
            if (Fileds.ContainsKey("AddTime") && !Convert.IsDBNull(dr["AddTime"])) nc.AddTime = Convert.ToDateTime(dr["AddTime"]); // 加入时间
            if (Fileds.ContainsKey("Content") && !Convert.IsDBNull(dr["Content"])) nc.Content = Convert.ToString(dr["Content"]); // 内容
            if (Fileds.ContainsKey("ImagePath") && !Convert.IsDBNull(dr["ImagePath"])) nc.ImagePath = Convert.ToString(dr["ImagePath"]); // 图片路径
            if (Fileds.ContainsKey("ImageComment") && !Convert.IsDBNull(dr["ImageComment"])) nc.ImageComment = Convert.ToString(dr["ImageComment"]); // 图片注释
            if (Fileds.ContainsKey("ReCommand") && !Convert.IsDBNull(dr["ReCommand"])) nc.ReCommand = Convert.ToBoolean(dr["ReCommand"]); // 是否为推荐新闻
            return nc;
        }
        #endregion

        #region "app_Notify() - DataProvider"
 
        /// <summary>
        /// 新增/删除/修改 app_NotifyEntity ()
        /// </summary>
        /// <param name="fam">app_Notify实体类</param>
        /// <returns>-1:存储过程执行失败,-2:存在相同的主键,Insert:返回插入自动ID,Update:返回更新记录数,Delete:返回删除记录数</returns>
        public abstract Int32 app_NotifyInsertUpdateDelete(app_NotifyEntity fam);

        /// <summary>
        /// 返回app_NotifyEntity实体类的List对象 ()
        /// </summary>
        /// <param name="qp">查询类(非安全函数,传入参数请进行Sql字符串过滤)</param>
        /// <param name="RecordCount">返回记录总数</param>
        /// <returns>app_NotifyEntity实体类的List对象()</returns>
        public abstract List<app_NotifyEntity> app_NotifyList(QueryParam qp, out int RecordCount);

        /// <summary>
        /// 将记录集转为app_NotifyEntity实体类 ()
        /// </summary>
        /// <param name="dr">记录集</param>
        /// <param name="Fileds">字段名列表</param>
        /// <returns>app_NotifyEntity</returns>
        protected app_NotifyEntity Populateapp_NotifyEntity(IDataReader dr,Dictionary<string,string> Fileds)
        {
            app_NotifyEntity nc = new app_NotifyEntity();

            if (Fileds.ContainsKey("ID") && !Convert.IsDBNull(dr["ID"])) nc.ID = Convert.ToInt32(dr["ID"]); // 
            if (Fileds.ContainsKey("Title") && !Convert.IsDBNull(dr["Title"])) nc.Title = Convert.ToString(dr["Title"]); // 标题
            if (Fileds.ContainsKey("Notifier") && !Convert.IsDBNull(dr["Notifier"])) nc.Notifier = Convert.ToString(dr["Notifier"]); // 通知部门
            if (Fileds.ContainsKey("AddTime") && !Convert.IsDBNull(dr["AddTime"])) nc.AddTime = Convert.ToDateTime(dr["AddTime"]); // 通知时间
            if (Fileds.ContainsKey("Content") && !Convert.IsDBNull(dr["Content"])) nc.Content = Convert.ToString(dr["Content"]); // 通知内容
            return nc;
        }
        #endregion

        #region "app_StyleShow() - DataProvider"
 
        /// <summary>
        /// 新增/删除/修改 app_StyleShowEntity ()
        /// </summary>
        /// <param name="fam">app_StyleShow实体类</param>
        /// <returns>-1:存储过程执行失败,-2:存在相同的主键,Insert:返回插入自动ID,Update:返回更新记录数,Delete:返回删除记录数</returns>
        public abstract Int32 app_StyleShowInsertUpdateDelete(app_StyleShowEntity fam);

        /// <summary>
        /// 返回app_StyleShowEntity实体类的List对象 ()
        /// </summary>
        /// <param name="qp">查询类(非安全函数,传入参数请进行Sql字符串过滤)</param>
        /// <param name="RecordCount">返回记录总数</param>
        /// <returns>app_StyleShowEntity实体类的List对象()</returns>
        public abstract List<app_StyleShowEntity> app_StyleShowList(QueryParam qp, out int RecordCount);

        /// <summary>
        /// 将记录集转为app_StyleShowEntity实体类 ()
        /// </summary>
        /// <param name="dr">记录集</param>
        /// <param name="Fileds">字段名列表</param>
        /// <returns>app_StyleShowEntity</returns>
        protected app_StyleShowEntity Populateapp_StyleShowEntity(IDataReader dr,Dictionary<string,string> Fileds)
        {
            app_StyleShowEntity nc = new app_StyleShowEntity();

            if (Fileds.ContainsKey("ID") && !Convert.IsDBNull(dr["ID"])) nc.ID = Convert.ToInt32(dr["ID"]); // 
            if (Fileds.ContainsKey("Title") && !Convert.IsDBNull(dr["Title"])) nc.Title = Convert.ToString(dr["Title"]); // 标题
            if (Fileds.ContainsKey("AddTime") && !Convert.IsDBNull(dr["AddTime"])) nc.AddTime = Convert.ToDateTime(dr["AddTime"]); // 图片加入时间
            if (Fileds.ContainsKey("Author") && !Convert.IsDBNull(dr["Author"])) nc.Author = Convert.ToString(dr["Author"]); // 作者
            if (Fileds.ContainsKey("ImagePath") && !Convert.IsDBNull(dr["ImagePath"])) nc.ImagePath = Convert.ToString(dr["ImagePath"]); // 图片路径
            if (Fileds.ContainsKey("Comment") && !Convert.IsDBNull(dr["Comment"])) nc.Comment = Convert.ToString(dr["Comment"]); // 图片注释
            return nc;
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
        /// <returns></returns>
        public abstract string get_table_fileds(string table_name, string table_fileds, string where_fileds, string where_value);
        #endregion

        #region "列新表中字段值"
        /// <summary>
        /// 更新表中字段值(非安全函数,传入参数请进行Sql字符串过滤)
        /// </summary>
        /// <param name="Table">表名</param>
        /// <param name="Table_FiledsValue">需要更新值(不用带Set)</param>
        /// <param name="Wheres">更新条件(不用带Where)</param>
        /// <returns></returns>
        public abstract int Update_Table_Fileds(string Table, string Table_FiledsValue, string Wheres);
        #endregion
    }
}
