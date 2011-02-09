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

                <tr>
                  <td rowspan="5" class="table_body" style="width: 14%"><p>图片列表</p>
                    <p>
                        <asp:ListBox ID="ImageItemList" SelectionMode="Multiple" Rows="10" runat="server" Width="73%" OnSelectedIndexChanged="ImageItemList_SelectedIndexChanged">
   <%--                         <asp:ListItem Value="1">1</asp:ListItem>
                            <asp:ListItem Value="2">2</asp:ListItem>
                            <asp:ListItem Value="3">3</asp:ListItem>--%>
                        </asp:ListBox>
                          </p>
                      <p>
                          &nbsp;</p>
                  </td>
                  <td rowspan="5" class="table_body" style="width: 6%"><p></p>
                    <p><asp:Button ID="BtnItemUp" runat="server" OnClick="BtnItemUp_Click" Text="上移" />&nbsp;</p>
                      <p>
                          <asp:Button ID="BtnItemDown" runat="server" OnClick="BtnItemDown_Click" Text="下移" />
                      </p>
                  </td>
                    <td width="18%" class="table_body">
                        标题</td>
                    <td width="68%" class="table_none">
                     
                        <asp:TextBox ID="Title_Input"  runat="server" CssClass="text_input"></asp:TextBox>
                    
                        <asp:Label ID="Title_Disp" runat="server"></asp:Label></td>
                </tr>

                <tr>
                  <td class="table_body" style="height: 31px">
                      图片加入时间</td>
                    <td class="table_none" style="height: 31px">
                     
                        <asp:TextBox ID="AddTime_Input"  runat="server" CssClass="text_input"></asp:TextBox>
                    
                        <asp:Label ID="AddTime_Disp" runat="server"></asp:Label></td>
                </tr>

                <tr>
                  <td class="table_body">
                      作者</td>
                    <td class="table_none">
                     
                        <asp:TextBox ID="Author_Input"  runat="server" CssClass="text_input"></asp:TextBox>
                    
                        <asp:Label ID="Author_Disp" runat="server"></asp:Label></td>
                </tr>

                <tr>
                  <td class="table_body">
                      图片路径</td>
                    <td class="table_none">
                     
                        <asp:TextBox ID="ImagePath_Input"  runat="server" CssClass="text_input"></asp:TextBox>
                    
                        <asp:Label ID="ImagePath_Disp" runat="server"></asp:Label></td>
                </tr>

                <tr>
                  <td class="table_body">
                      图片注释</td>
                    <td class="table_none">
                     
                        <asp:TextBox ID="Comment_Input"  runat="server" CssClass="text_input"></asp:TextBox>
                    
                        <asp:Label ID="Comment_Disp" runat="server"></asp:Label></td>
                </tr>
                              
                <tr id="ButtonOption" runat="server">
                    <td align="right" colspan="3">
                        <asp:Button ID="Button1" runat="server" CssClass="button_bak" Text="添加" OnClick="Button1_Click" />
                        <asp:Button ID="Button2" runat="server" CssClass="button_bak" Text="删除" OnClick="Button1_Click" />
                        <input id="Reset1" class="button_bak" type="reset" value="重填" />
                    </td>
                </tr>
            </table>
        </FrameWorkWebControls:TabOptionItem>
    </FrameWorkWebControls:TabOptionWebControls>
</asp:Content>
