/********************************************************************************
    File:
          app_NotifyEntity.cs
    Description:
          实体类
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
using FrameWork;

namespace FrameWork.web.Manager.Module.App.Components
{
    ///<summary>
    ///app_NotifyEntity实体类()
    ///</summary>
    [Serializable]
    public partial class app_NotifyEntity
    {
        #region "Private Variables"
        private DataTable_Action _DataTable_Action_;  // 操作方法 Insert:增加 Update:修改 Delete:删除
        private Int32 _ID; // 
        private string _Title=""; // 标题
        private string _Notifier=""; // 通知部门
        private DateTime? _AddTime; // 通知时间
        private string _Content=""; // 通知内容
        #endregion

        #region "Public Variables"
        ///<summary>
        /// 操作方法 Insert:增加 Update:修改 Delete:删除
        ///</summary>
        public DataTable_Action DataTable_Action_
        {
            set { this._DataTable_Action_ = value; }
            get { return this._DataTable_Action_; }
        }
        /// <summary>
        /// 
        /// </summary>
        public Int32  ID
        {
            set { this._ID = value; }
            get { return this._ID; }
        }
            
        /// <summary>
        /// 标题
        /// </summary>
        public string  Title
        {
            set { this._Title = value; }
            get { return this._Title; }
        }
            
        /// <summary>
        /// 通知部门
        /// </summary>
        public string  Notifier
        {
            set { this._Notifier = value; }
            get { return this._Notifier; }
        }
            
        /// <summary>
        /// 通知时间
        /// </summary>
        public DateTime?  AddTime
        {
            set { this._AddTime = value; }
            get { return this._AddTime; }
        }
            
        /// <summary>
        /// 通知内容
        /// </summary>
        public string  Content
        {
            set { this._Content = value; }
            get { return this._Content; }
        }
            
        #endregion
    }
}
  