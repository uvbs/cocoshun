/********************************************************************************
    File:
          app_StyleShowImageEntity.cs
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
    ///app_StyleShowImageEntity实体类()
    ///</summary>
    [Serializable]
    public partial class app_StyleShowImageEntity
    {
        #region "Private Variables"
        private DataTable_Action _DataTable_Action_;  // 操作方法 Insert:增加 Update:修改 Delete:删除
        private Int32 _ID; // 
        private string _Title=""; // 标题
        private DateTime? _AddTime; // 图片加入时间
        private string _Author=""; // 作者
        private string _Path=""; // 图片路径
        private string _Comment=""; // 图片注释
        private Int32 _ImageOrder = 0;
        private Int32 _ImageID;
        private string _ImageName;
        private string _ImagePath;
        private string _ImageComment;
        private DateTime _ImageUploadTime;
        
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
        /// 图片加入时间
        /// </summary>
        public DateTime?  AddTime
        {
            set { this._AddTime = value; }
            get { return this._AddTime; }
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
        /// 图片路径
        /// </summary>
        public string  Path
        {
            set { this._Path = value; }
            get { return this._Path; }
        }
            
        /// <summary>
        /// 图片注释
        /// </summary>
        public string  Comment
        {
            set { this._Comment = value; }
            get { return this._Comment; }
        }

        public Int32 ImageOrder
        {
            get { return _ImageOrder; }
            set { _ImageOrder = value; }
        }


        public Int32 ImageID
        {
            get { return _ImageID; }
            set { _ImageID = value; }
        }

        public string ImageName
        {
            get { return _ImageName; }
            set { _ImageName = value; }
        }

        public string ImagePath
        {
            get { return _ImagePath; }
            set { _ImagePath = value; }
        }

        public string ImageComment
        {
            get { return _ImageComment; }
            set { _ImageComment = value; }
        }


        public DateTime ImageUploadTime
        {
            get { return _ImageUploadTime; }
            set { _ImageUploadTime = value; }
        }

        public override string ToString()
        {
            return _ImageName;
        }
            
        #endregion
    }
}
  