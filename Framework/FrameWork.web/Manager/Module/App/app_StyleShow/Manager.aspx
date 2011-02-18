<%@ Page Language="C#" MasterPageFile="~/Manager/MasterPage/PageTemplate.Master" AutoEventWireup="True"
    Codebehind="Manager.aspx.cs" Inherits="FrameWork.web.Manager.Module.App.app_StyleShow.Manager"
    Title="无标题页" %>

<asp:Content ID="Content1" ContentPlaceHolderID="PageBody" runat="server">
  <FrameWorkWebControls:HeadMenuWebControls ID="HeadMenuWebControls1" runat="server"  HeadTitleTxt="">
    <FrameWorkWebControls:HeadMenuButtonItem ButtonPopedom="List" ButtonUrl="Default.aspx"
            ButtonUrlType="Href" ButtonVisible="True" ButtonName="" />
  </FrameWorkWebControls:HeadMenuWebControls>
  <FrameWorkWebControls:TabOptionWebControls ID="TabOptionWebControls1" runat="server">
    <FrameWorkWebControls:TabOptionItem ID="TabOptionItem1" runat="server" Tab_Name="查看/修改/增加">
      <table width="100%" border="0" cellspacing="1" cellpadding="3" align="center">
        <tr class="table_body">
          <td colspan="3" align="right" valign="middle"><span class="table_body">
            <asp:Label id="MainID" runat="server" Text="MainID" __designer:wfdid="w1" Width="25px" Visible="False"></asp:Label>
            标 题</span></td>
          <td width="66%" align="left" valign="middle"><span class="table_body"><asp:TextBox id="Title_Input" runat="server" CssClass="text_input"></asp:TextBox> <asp:Label id="Title_Disp" runat="server" Width="169px"></asp:Label> </span></td>
        </tr>
        <tr class="table_body">
          <td colspan="3" align="right" valign="middle"><span class="table_body" style="height: 31px">时 间</span></td>
          <td align="left" valign="middle"><span class="table_body" style="height: 31px"><asp:TextBox id="AddTime_Input" runat="server" CssClass="text_input"></asp:TextBox> <asp:Label id="AddTime_Disp" runat="server" Width="169px"></asp:Label> </span></td>
        </tr>
        <tr class="table_body">
          <td colspan="3" align="right" valign="middle"><span class="table_body">作 者</span></td>
          <td align="left" valign="middle"><span class="table_body"><asp:TextBox id="Author_Input" runat="server" CssClass="text_input"></asp:TextBox> <asp:Label id="Author_Disp" runat="server" Width="168px"></asp:Label> </span></td>
        </tr>
        <tr>
          <td width="11%" rowspan="3" align="center" valign="middle" class="table_body" style="width: 14%"><p> 图片顺序</p>
            <p>
              <asp:ListBox ID="ImageItemList" SelectionMode="Single" Rows="10" runat="server"  OnSelectedIndexChanged="ImageItemList_SelectedIndexChanged" onClick="selectImageItem();">

              </asp:ListBox>
            </p>
            <p>&nbsp; </p></td>
          <td rowspan="3" valign="middle" class="table_body" style="width: 6%"><p></p>
            <p>
              <asp:Button ID="BtnItemUp2" runat="server" OnClick="BtnItemUp_Click" Text="上移" />
            &nbsp;</p>
            <p>
              <asp:Button ID="BtnItemDown2" runat="server" OnClick="BtnItemDown_Click" Text="下移" />
            </p></td>
          <td height="45" align="right" valign="middle" class="table_body" style="width: 323px">图片名称</td>
          <td align="left" class="table_body"><asp:TextBox ID="ImageName_Input" runat="server" CssClass="text_input"></asp:TextBox>
              <asp:Label ID="Imagename_Disp" runat="server" Width="168px"></asp:Label></td>
        </tr>
        <tr>
          <td  height="40" align="right" valign="middle" class="table_body" style="width: 323px"> 图 &nbsp;&nbsp; 片</td>
          <td  align="left" class="table_body"><asp:FileUpload ID="ImagePath_Input"  runat="server" CssClass="text_input"></asp:FileUpload>
            <asp:Label ID="ImagePath_Disp" runat="server"></asp:Label>
              <asp:Image ID="Image_show" Width="400" Height="300" runat="server" /></td>
        </tr>
        <tr>
          <td align="right" valign="middle" class="table_body" style="width: 323px"> 图片注释</td>
          <td align="left" class="table_body"><asp:TextBox ID="Comment_Input"  runat="server" CssClass="text_input"></asp:TextBox>
            <asp:Label ID="Comment_Disp" runat="server"></asp:Label></td>
        </tr>
        <tr id="ButtonOption" runat="server"  class="table_body">
          <td align="center" colspan="5" style="height: 30px"><asp:Button ID="Button1" runat="server" CssClass="button_bak" Text="保存" OnClick="Button1_Click" />
            <asp:Button ID="Btn_Image_Add" runat="server" CssClass="button_bak" Text="添加图片" OnClick="Btn_Image_Add_Click" />
            <asp:Button ID="Btn_ImageDelete" runat="server" CssClass="button_bak" Text="删除图片" OnClick="Btn_ImageDelete_Click" />
            <input id="Reset1" class="button_bak" type="reset" value="重填" /></td>
        </tr>
      </table>
    </FrameWorkWebControls:TabOptionItem>
  </FrameWorkWebControls:TabOptionWebControls>
  <script language="javascript">
      function selectImageItem()
      {
            document.forms[0].submit();
      }
  </script>
</asp:Content>
