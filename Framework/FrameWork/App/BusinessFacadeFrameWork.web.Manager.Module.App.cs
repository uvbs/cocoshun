/********************************************************************************
     File:																
            BusinessFacade.cs                         
     Description:
            业务逻辑类
     Author:									
            DDBuildTools
            http://FrameWork.supesoft.com
     Finish DateTime:
			2011/1/5 9:15:01
     History:
*********************************************************************************/
using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;
using FrameWork.web.Manager.Module.App.Components;
using FrameWork.web.Manager.Module.App.Data;

using FrameWork.Components;

namespace BusinessFacadeFrameWork.web.Manager.Module
{
    /// <summary>
    /// 业务逻辑类
    /// </summary>
    public partial class App
    {

        #region "app_News() - Method"

        /// <summary>
        /// 新增/删除/修改 app_NewsEntity ()
        /// </summary>
        /// <param name="fam">app_NewsEntity实体类</param>
        /// <returns>-1:存储过程执行失败,-2:存在相同的主键,Insert:返回插入自动ID,Update:返回更新记录数,Delete:返回删除记录数</returns>
        public static Int32 app_NewsInsertUpdateDelete(app_NewsEntity fam)
        {
            return DataProvider.Instance().app_NewsInsertUpdateDelete(fam);
        }
        
        /// <summary>
        /// 根据ID返回 app_NewsEntity实体类 单笔资料 ()
        /// </summary>
        /// <param name="ID">ID </param>
        /// <returns>返回 app_NewsEntity实体类 ID为0则无记录</returns>
        public static app_NewsEntity app_NewsDisp(Int32 ID)
        {
            app_NewsEntity fam = new app_NewsEntity();
            QueryParam qp = new QueryParam();
            qp.PageIndex = 1;
            qp.PageSize = 1;
            qp.Where = string.Format(" Where {0}.{1} = {2}","app_News","ID",ID);
            int RecordCount = 0;
            List<app_NewsEntity> lst = app_NewsList(qp, out RecordCount);
            if (RecordCount > 0)
            {
                fam = lst[0];
            }
            return fam;
        }

        /// <summary>
        /// 返回app_NewsEntity实体类的List对象 ()
        /// </summary>
        /// <param name="qp">查询类(非安全函数,传入参数请进行Sql字符串过滤)</param>
        /// <param name="RecordCount">返回记录总数</param>
        /// <returns>app_NewsEntity实体类的List对象()</returns>
        public static List<app_NewsEntity> app_NewsList(QueryParam qp, out int RecordCount)
        {
            qp.TableName = "app_News";
            if (qp.Orderfld == null)
            {
                qp.Orderfld = "ID";
            }
            else if (qp.Orderfld != "ID")
            {
                qp.Orderfld += ",ID";
            }
            
            if (qp.ReturnFields == null)
            {
                qp.ReturnFields = "*";
            }
            else
            {
                qp.ReturnFields += ",";
                qp.ReturnFields += qp.Orderfld;
            }
            return DataProvider.Instance().app_NewsList(qp, out RecordCount);
        }
        #endregion

        #region "app_Notify() - Method"

        /// <summary>
        /// 新增/删除/修改 app_NotifyEntity ()
        /// </summary>
        /// <param name="fam">app_NotifyEntity实体类</param>
        /// <returns>-1:存储过程执行失败,-2:存在相同的主键,Insert:返回插入自动ID,Update:返回更新记录数,Delete:返回删除记录数</returns>
        public static Int32 app_NotifyInsertUpdateDelete(app_NotifyEntity fam)
        {
            return DataProvider.Instance().app_NotifyInsertUpdateDelete(fam);
        }
        
        /// <summary>
        /// 根据ID返回 app_NotifyEntity实体类 单笔资料 ()
        /// </summary>
        /// <param name="ID">ID </param>
        /// <returns>返回 app_NotifyEntity实体类 ID为0则无记录</returns>
        public static app_NotifyEntity app_NotifyDisp(Int32 ID)
        {
            app_NotifyEntity fam = new app_NotifyEntity();
            QueryParam qp = new QueryParam();
            qp.PageIndex = 1;
            qp.PageSize = 1;
            qp.Where = string.Format(" Where {0}.{1} = {2}","app_Notify","ID",ID);
            int RecordCount = 0;
            List<app_NotifyEntity> lst = app_NotifyList(qp, out RecordCount);
            if (RecordCount > 0)
            {
                fam = lst[0];
            }
            return fam;
        }

        /// <summary>
        /// 返回app_NotifyEntity实体类的List对象 ()
        /// </summary>
        /// <param name="qp">查询类(非安全函数,传入参数请进行Sql字符串过滤)</param>
        /// <param name="RecordCount">返回记录总数</param>
        /// <returns>app_NotifyEntity实体类的List对象()</returns>
        public static List<app_NotifyEntity> app_NotifyList(QueryParam qp, out int RecordCount)
        {
            qp.TableName = "app_Notify";
            if (qp.Orderfld == null)
            {
                qp.Orderfld = "ID";
            }
            else if (qp.Orderfld != "ID")
            {
                qp.Orderfld += ",ID";
            }
            
            if (qp.ReturnFields == null)
            {
                qp.ReturnFields = "*";
            }
            else
            {
                qp.ReturnFields += ",";
                qp.ReturnFields += qp.Orderfld;
            }
            return DataProvider.Instance().app_NotifyList(qp, out RecordCount);
        }
        #endregion

        #region "app_StyleShow() - Method"

        /// <summary>
        /// 新增/删除/修改 app_StyleShowEntity ()
        /// </summary>
        /// <param name="fam">app_StyleShowEntity实体类</param>
        /// <returns>-1:存储过程执行失败,-2:存在相同的主键,Insert:返回插入自动ID,Update:返回更新记录数,Delete:返回删除记录数</returns>
        public static Int32 app_StyleShowInsertUpdateDelete(app_StyleShowEntity fam)
        {
            return DataProvider.Instance().app_StyleShowInsertUpdateDelete(fam);
        }
        
        /// <summary>
        /// 根据ID返回 app_StyleShowEntity实体类 单笔资料 ()
        /// </summary>
        /// <param name="ID">ID </param>
        /// <returns>返回 app_StyleShowEntity实体类 ID为0则无记录</returns>
        public static app_StyleShowEntity app_StyleShowDisp(Int32 ID)
        {
            app_StyleShowEntity fam = new app_StyleShowEntity();
            QueryParam qp = new QueryParam();
            qp.PageIndex = 1;
            qp.PageSize = 1;
            qp.Where = string.Format(" Where {0}.{1} = {2}","app_StyleShow","ID",ID);
            int RecordCount = 0;
            List<app_StyleShowEntity> lst = app_StyleShowList(qp, out RecordCount);
            if (RecordCount > 0)
            {
                fam = lst[0];
            }
            return fam;
        }

        /// <summary>
        /// 返回app_StyleShowEntity实体类的List对象 ()
        /// </summary>
        /// <param name="qp">查询类(非安全函数,传入参数请进行Sql字符串过滤)</param>
        /// <param name="RecordCount">返回记录总数</param>
        /// <returns>app_StyleShowEntity实体类的List对象()</returns>
        public static List<app_StyleShowEntity> app_StyleShowList(QueryParam qp, out int RecordCount)
        {
            qp.TableName = "app_StyleShow";
            if (qp.Orderfld == null)
            {
                qp.Orderfld = "ID";
            }
            else if (qp.Orderfld != "ID")
            {
                qp.Orderfld += ",ID";
            }
            
            if (qp.ReturnFields == null)
            {
                qp.ReturnFields = "*";
            }
            else
            {
                qp.ReturnFields += ",";
                qp.ReturnFields += qp.Orderfld;
            }
            return DataProvider.Instance().app_StyleShowList(qp, out RecordCount);
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
        public static string get_table_fileds(string table_name, string table_fileds, string where_fileds, string where_value)
        {
            return DataProvider.Instance().get_table_fileds(table_name, table_fileds, where_fileds, where_value);
        }
        #endregion

        #region "列新表中字段值"
        /// <summary>
        /// 更新表中字段值(非安全函数,传入参数请进行Sql字符串过滤)
        /// </summary>
        /// <param name="Table">表名</param>
        /// <param name="Table_FiledsValue">需要更新值(不用带Set)</param>
        /// <param name="Wheres">更新条件(不用带Where)</param>
        /// <returns></returns>
        public static int Update_Table_Fileds(string Table, string Table_FiledsValue, string Wheres)
        {
            return DataProvider.Instance().Update_Table_Fileds(Table, Table_FiledsValue, Wheres);
        }

        #endregion
    }
}
