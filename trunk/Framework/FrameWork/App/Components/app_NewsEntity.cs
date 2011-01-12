/********************************************************************************
    File:
          app_NewsEntity.cs
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
    ///app_NewsEntity实体类()
    ///</summary>
    [Serializable]
    public partial class app_NewsEntity
    {
        #region "Private Variables"
        private DataTable_Action _DataTable_Action_;  // 操作方法 Insert:增加 Update:修改 Delete:删除
        private Int32 _ID; // 
        private string _Title=""; // 标题
        private string _Author=""; // 作者
        private DateTime? _AddTime; // 加入时间
        private string _Content=""; // 内容
        private string _ImagePath=""; // 图片路径
        private string _ImageComment = ""; //图片注释
        private Boolean _ReCommand; // 是否为推荐新闻
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
        /// 作者
        /// </summary>
        public string  Author
        {
            set { this._Author = value; }
            get { return this._Author; }
        }
            
        /// <summary>
        /// 加入时间
        /// </summary>
        public DateTime?  AddTime
        {
            set { this._AddTime = value; }
            get { return this._AddTime; }
        }
            
        /// <summary>
        /// 内容
        /// </summary>
        public string  Content
        {
            set { this._Content = value; }
            get { return this._Content; }
        }
            
        /// <summary>
        /// 图片路径
        /// </summary>
        public string  ImagePath
        {
            set { this._ImagePath = value; }
            get { return this._ImagePath; }
        }

        public string ImageComment
        {
          get { return _ImageComment; }
          set { _ImageComment = value; }
        }
            
        /// <summary>
        /// 是否为推荐新闻
        /// </summary>
        public Boolean  ReCommand
        {
            set { this._ReCommand = value; }
            get { return this._ReCommand; }
        }
            
        #endregion
    }
}
  