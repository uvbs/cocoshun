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
          <td colspan="3" align="right" valign="middle"><span class="table_body">标 题</span></td>
          <td width="66%" align="left" valign="middle"><asp:TextBox id="Title_Input" runat="server" CssClass="text_input"></asp:TextBox> <asp:Label id="Title_Disp" runat="server" Width="169px"></asp:Label> </td>
        </tr>
        <tr class="table_body">
          <td colspan="3" align="right" valign="middle">
              时 间</td>
          <td align="left" valign="middle"><asp:TextBox id="AddTime_Input" runat="server" CssClass="text_input" onfocus="javascript:HS_setDate(this);"></asp:TextBox> <asp:Label id="AddTime_Disp" runat="server" Width="169px"></asp:Label> </td>
        </tr>
        <tr class="table_body">
          <td colspan="3" align="right" valign="middle">作 者</td>
          <td align="left" valign="middle"><asp:TextBox ID="Author_Input" runat="server" CssClass="text_input"></asp:TextBox>
          <asp:Label ID="Author_Disp" runat="server" Width="168px"></asp:Label></td>
        </tr>
        <tr align="center" class="table_body">
          <td colspan="4" valign="middle"><span style="height: 30px"><asp:Button id="BtnSave" runat="server" Text="保存" CssClass="button_bak" OnClick="BtnSave_Click"></asp:Button> </span></td>
        </tr>
        <tr>
          <td width="11%" rowspan="3" align="center" valign="middle" class="table_body" style="width: 14%"><p> 图片列表</p>
            <p>
              <asp:ListBox ID="ImageItemList" SelectionMode="Single" Rows="10" runat="server"  OnSelectedIndexChanged="ImageItemList_SelectedIndexChanged" onClick="selectImageItem();" Width="100px">

              </asp:ListBox>
            </p>
            <p>&nbsp; </p></td>
          <td rowspan="3" valign="middle" class="table_body" style="width: 6%"><asp:Image ID="Image_show" runat="server" /><p></p>
            <p>
              <asp:Button ID="BtnItemUp2" runat="server" OnClick="BtnItemUp_Click" Text="上移" Visible="False" />
            &nbsp;</p>
            <p>
              <asp:Button ID="BtnItemDown2" runat="server" OnClick="BtnItemDown_Click" Text="下移" Visible="False" />
            </p></td>
          <td height="45" align="right" valign="middle" class="table_body" style="width: 323px">图片名称</td>
          <td align="left" class="table_body"><asp:TextBox ID="ImageName_Input" runat="server" CssClass="text_input"></asp:TextBox>
              <asp:Label ID="Imagename_Disp" runat="server" Width="168px"></asp:Label></td>
        </tr>
        <tr>
          <td  height="40" align="right" valign="middle" class="table_body" style="width: 323px"> 上传图片</td>
          <td  align="left" class="table_body"><asp:FileUpload ID="ImagePath_Input"  runat="server" CssClass="text_input"></asp:FileUpload>
            <asp:Label ID="ImagePath_Disp" runat="server"></asp:Label>
              </td>
        </tr>
        <tr>
          <td align="right" valign="middle" class="table_body" style="width: 323px"> 图片注释</td>
          <td align="left" class="table_body"><asp:TextBox ID="Comment_Input"  runat="server" CssClass="text_input"></asp:TextBox>
            <asp:Label ID="Comment_Disp" runat="server"></asp:Label></td>
        </tr>
        <tr id="ButtonOption" runat="server"  class="table_body">
          <td align="center" colspan="5" style="height: 30px">
              &nbsp;
            <asp:Button ID="Btn_Image_Add" runat="server" CssClass="button_bak" Text="上传图片" OnClick="Btn_Image_Add_Click" />
            <asp:Button ID="Btn_ImageDelete" runat="server" CssClass="button_bak" Text="删除图片" OnClick="Btn_ImageDelete_Click" />
            <input id="Reset1" class="button_bak" type="reset" value="重填" /></td>
        </tr>
      </table>
    <asp:Button ID="Button1" runat="server" CssClass="button_bak" Text="保存" OnClick="Button1_Click" Visible="False" /></FrameWorkWebControls:TabOptionItem>
  </FrameWorkWebControls:TabOptionWebControls>
  <script language="javascript">
      function selectImageItem()
      {
          document.forms[0].submit();
      }
  </script>
</asp:Content>
