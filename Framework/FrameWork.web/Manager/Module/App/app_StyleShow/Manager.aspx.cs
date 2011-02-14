/********************************************************************************
     File:																
            Manager.aspx.cs                         
     Description:
            管理
     Author:									
            DDBuildTools
            http://DDBuildTools.supesoft.com
     Finish DateTime:
            2011/1/5 9:15:01
     History:
*********************************************************************************/
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

using FrameWork.web.Manager.Module.App;
using FrameWork.web.Manager.Module.App.Components;
using FrameWork;
using FrameWork.Components;
using FrameWork.WebControls;
using System.Data.OleDb;
using FrameWork.web.Manager.Module.App.Data;

namespace FrameWork.web.Manager.Module.App.app_StyleShow
{
    public partial class Manager : System.Web.UI.Page
    {
        /// <summary>
        /// 数据库连接字符串
        /// </summary>
        private string ConnString = string.Empty;

        public Manager()
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

        int IDX = (int)Common.sink("IDX", MethodType.Get, 4, 0, DataType.Int);
        string CMD = (string)Common.sink("CMD", MethodType.Get, 10, 1, DataType.Str);
        protected void Page_Load(object sender, EventArgs e)
        {
            FrameWorkPermission.CheckPagePermission(CMD);
            if (!Page.IsPostBack)
            {
                OnStart();
            }
        }
        
        /// <summary>
        /// 开始操作
        /// </summary>
        private void OnStart()
        {
            app_StyleShowEntity ut = BusinessFacadeFrameWork.app_StyleShowDisp(IDX);
            OnStartData(ut);
            switch (CMD)
            { 
                case "New":
                    TabOptionItem1.Tab_Name = HeadMenuWebControls1.HeadOPTxt = "增加";
                    Hidden_Disp();
                    break;
                case "List":
                    TabOptionItem1.Tab_Name = HeadMenuWebControls1.HeadOPTxt = "查看";
                    Hidden_Input();
                    ButtonOption.Visible = false;
                    AddEditButton();
                    break;
                case "Edit":
                    TabOptionItem1.Tab_Name = HeadMenuWebControls1.HeadOPTxt = "修改";
                    Hidden_Disp();
                    AddDeleteButton();
                    break;
                case "Delete":
                    ut.DataTable_Action_ = DataTable_Action.Delete;
                    if (BusinessFacadeFrameWork.app_StyleShowInsertUpdateDelete(ut) > 0)
                    {
                        EventMessage.MessageBox(1, "删除成功", string.Format("删除ID:{0}成功!", IDX), Icon_Type.OK, Common.GetHomeBaseUrl("Default.aspx"));
                    }
                    else {
                        EventMessage.MessageBox(1, "删除失败", string.Format("删除ID:{0}失败!", IDX), Icon_Type.Error, Common.GetHomeBaseUrl("Default.aspx"));
                    }
                    break;
                default :
                    EventMessage.MessageBox(2, "不存在操作字符串!", "不存在操作字符串!", Icon_Type.Error, Common.GetHomeBaseUrl("Default.aspx"));
                    break;
            }
        }

        /// <summary>
        /// 增加修改按钮
        /// </summary>
        private void AddEditButton()
        {
            HeadMenuButtonItem bi = new HeadMenuButtonItem();
            bi.ButtonPopedom = PopedomType.Edit;
            bi.ButtonName = "";
            bi.ButtonUrl = string.Format("?CMD=Edit&IDX={0}", IDX);
            HeadMenuWebControls1.ButtonList.Add(bi);
        }


        /// <summary>
        /// 增加删除按钮
        /// </summary>
        private void AddDeleteButton()
        {
            HeadMenuButtonItem bi = new HeadMenuButtonItem();
            bi.ButtonPopedom = PopedomType.Delete;
            bi.ButtonName = "";
            bi.ButtonUrlType = UrlType.JavaScript;
            bi.ButtonUrl = string.Format("DelData('?CMD=Delete&IDX={0}')", IDX);
            HeadMenuWebControls1.ButtonList.Add(bi);

            HeadMenuButtonItem bi1 = new HeadMenuButtonItem();
            bi1.ButtonPopedom = PopedomType.List;
            bi1.ButtonIcon = "back.gif";
            bi1.ButtonName = "返回";
            bi1.ButtonUrl = string.Format("?CMD=List&IDX={0}", IDX);
            HeadMenuWebControls1.ButtonList.Add(bi1);
        }

        /// <summary>
        /// 初始化数据
        /// </summary>
        /// <param name="ut"></param>
        private void OnStartData(app_StyleShowEntity ut)
        {
            Title_Input.Text = Title_Disp.Text = ut.Title.ToString();
            AddTime_Input.Text = AddTime_Disp.Text = ut.AddTime.ToString();
            Author_Input.Text = Author_Disp.Text = ut.Author.ToString();
          //  ImagePath_Input.Text = ImagePath_Disp.Text = ut.ImagePath.ToString();

            Comment_Input.Text = Comment_Disp.Text = ut.Comment.ToString();
                
        }

        /// <summary>
        /// 隐藏输入框
        /// </summary>
        private void Hidden_Input()
        {
            Title_Input.Visible = false;
            AddTime_Input.Visible = false;
            Author_Input.Visible = false;
            ImagePath_Input.Visible = false;
            Comment_Input.Visible = false;       
        }

        /// <summary>
        /// 隐藏显示框
        /// </summary>
        private void Hidden_Disp()
        {
        Title_Disp.Visible = false;
        AddTime_Disp.Visible = false;
        Author_Disp.Visible = false;
        ImagePath_Disp.Visible = false;
        Comment_Disp.Visible = false;
        
        }

        /// <summary>
        /// 增加/修改事件
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        protected void Button1_Click(object sender, EventArgs e)
        {
        
            DateTime? AddTime_Value = (DateTime?)Common.sink(AddTime_Input.UniqueID, MethodType.Post, 50, 0, DataType.Dat);
       
            app_StyleShowEntity ut = BusinessFacadeFrameWork.app_StyleShowDisp(IDX);
            
            ut.Title = Title_Input.Text;
            ut.AddTime = Convert.ToDateTime(AddTime_Input.Text);
            ut.Author = Author_Input.Text;
           // ut.ImagePath = ImagePath_Input.Text;
            ut.Comment = Comment_Input.Text;
            
            if (CMD == "New")
            {
                ut.DataTable_Action_ = DataTable_Action.Insert;
            }
            else if (CMD == "Edit")
            {
                ut.DataTable_Action_ = DataTable_Action.Update;
            }
            else
            {
                EventMessage.MessageBox(2, "不存在操作字符串!", "不存在操作字符串!", Icon_Type.Error, Common.GetHomeBaseUrl("Default.aspx"));
            }
            Int32 rInt = BusinessFacadeFrameWork.app_StyleShowInsertUpdateDelete(ut);
            if ( rInt> 0)
            {
                string OpTxt = string.Format("增加成功!(ID:{0})", rInt);
                if (ut.DataTable_Action_ == DataTable_Action.Update)
                    OpTxt = string.Format("修改成功!(ID:{0})",IDX);
                EventMessage.MessageBox(1, "操作成功", OpTxt, Icon_Type.OK, Common.GetHomeBaseUrl("Default.aspx"));
            }
            else if (rInt == -2)
            {
                EventMessage.MessageBox(1, "操作失败", "操作失败,存在相同的键值(用户名/数据)!", Icon_Type.Alert, Common.GetHomeBaseUrl("Default.aspx"));
            }
            else
            {
                EventMessage.MessageBox(1, "操作失败", string.Format("操作失败,返回值:{0}!", rInt), Icon_Type.Error, Common.GetHomeBaseUrl("Default.aspx"));
            }
        }

        protected void BtnItemDown_Click(object sender, EventArgs e)
        {

            if(ImageItemList.SelectedIndex != -1)
            {
                ListItem item = new ListItem();
                int nextIndex;
                item.Value = ImageItemList.SelectedValue;
                item.Text = ImageItemList.SelectedItem.ToString();
                nextIndex = (ImageItemList.SelectedIndex) + 1;
                if (nextIndex == ImageItemList.Items.Count)
                    return;
                ImageItemList.Items.Remove(ImageItemList.SelectedItem);
                ImageItemList.Items.Insert(nextIndex, item.Text);
                ImageItemList.Items[nextIndex].Value = item.Value;
                ImageItemList.SelectedIndex = nextIndex;

            }
        }

        protected void BtnItemUp_Click(object sender, EventArgs e)
        {
            if (ImageItemList.SelectedIndex != -1)
            {
                ListItem item = new ListItem();
                int nextIndex;
                item.Value = ImageItemList.SelectedValue;
                item.Text = ImageItemList.SelectedItem.ToString();
                nextIndex = (ImageItemList.SelectedIndex) - 1;
                if (nextIndex == -1)
                    return;
                ImageItemList.Items.Remove(ImageItemList.SelectedItem);
                ImageItemList.Items.Insert(nextIndex, item.Text);
                ImageItemList.Items[nextIndex].Value = item.Value;
                ImageItemList.SelectedIndex = nextIndex;

            }
        }

        /************************************************************************/
        /* 选择图片                                                             */
        /************************************************************************/
        protected void ImageItemList_SelectedIndexChanged(object sender, EventArgs e)
        {

        }


        /************************************************************************/
        /* 添加图片                                                             */
        /************************************************************************/
        protected void Btn_Image_Add_Click(object sender, EventArgs e)
        {
            DateTime? AddTime_Value = (DateTime?)Common.sink(AddTime_Input.UniqueID, MethodType.Post, 50, 0, DataType.Dat);

            try
            {            
                app_StyleShowEntity ut = BusinessFacadeFrameWork.app_StyleShowDisp(IDX);

                ut.Title = Title_Input.Text;
                ut.AddTime = Convert.ToDateTime(AddTime_Input.Text);
                ut.Author = Author_Input.Text;
                // ut.ImagePath = ImagePath_Input.Text;
                ut.Comment = Comment_Input.Text;

                Int32 rInt = BusinessFacadeFrameWork.app_StyleShowInsertUpdateDelete(ut);

                // 添加图片
                InsertImage(rInt);


                string url = string.Format(Common.GetHomeBaseUrl("Manager.aspx?CMD=Edit&IDX={0}"), rInt);
                Response.Redirect(url, false);

            }
            catch (System.Exception ex)
            {
                EventMessage.MessageBox(2, "操作失败", "添加图片失败!请检查参数完整性!", Icon_Type.Error, Common.GetHomeBaseUrl("Default.aspx"));
            }


        }

        private void InsertImage(int rInt)
        {
            string imagePath = ImageName_Input.Text;
            string path = UploadPic(ImagePath_Input);
            string comment = Comment_Input.Text;

            using (OleDbConnection Conn = GetSqlConnection())
            {
                string CommTxt;
                OleDbCommand cmd = new OleDbCommand();
                cmd.Connection = Conn;
                Conn.Open();

                // 插入图片表
                CommTxt = "Insert into app_Images(Name,Path,Comment)VALUES(@Name,@Path,@Comment)";
                cmd.CommandText = CommTxt;
                cmd.Parameters.Add("@Title", OleDbType.VarWChar).Value = imagePath; //标题
                cmd.Parameters.Add("@Path", OleDbType.VarWChar).Value = path;
                cmd.Parameters.Add("@Comment", OleDbType.VarWChar).Value = comment;
                int ImageID = cmd.ExecuteNonQuery();
                cmd.Dispose();

                // 插入关联表 
                int nextOrder = 0;
                cmd = new OleDbCommand();
                cmd.Connection = Conn;
                cmd.CommandText = string.Format("select Max(ImageOrder) from app_Styles_Images where StyleID={0} and ImageID={1}", rInt, ImageID);
                OleDbDataReader dr = cmd.ExecuteReader();
                
                if (dr.Read())
                {
                    string value = dr[0].ToString();
                    if (value != null && value.Length>0)
                        nextOrder = int.Parse(value) + 1;
                }
                cmd.Dispose();


                cmd = new OleDbCommand();
                cmd.Connection = Conn;
                CommTxt = "Insert into app_Styles_Images (StyleID,ImageID,ImageOrder)VALUES(@StyleID,@ImageID,@ImageOrder)";
                cmd.CommandText = CommTxt;

                cmd.Parameters.Add("@StyleID", OleDbType.Integer).Value = rInt; //标题
                cmd.Parameters.Add("@ImageID", OleDbType.Integer).Value = ImageID;
                cmd.Parameters.Add("@ImageOrder", OleDbType.Integer).Value = nextOrder;

                cmd.ExecuteNonQuery();
                
                cmd.Dispose();
                Conn.Dispose();
                Conn.Close();

            }

        }


        /************************************************************************/
        /* 删除图片                                                             */
        /************************************************************************/
        protected void Btn_ImageDelete_Click(object sender, EventArgs e)
        {
            
        }

        private static string ImagePath = Common.UpLoadDir + "StyleShowImages/";

        /************************************************************************/
        /* 上传新闻图片                                                         */
        /************************************************************************/
        private string UploadPic(FileUpload fileUpload)
        {
            FileUpLoadCommon fc = new FileUpLoadCommon(ImagePath, true);

            // 如果图片上传成功
            fc.SaveFile(fileUpload, true);
            return ImagePath +　fc.newFileName;
        }

      
    }
}
