<%@ Page Language="C#" MasterPageFile="~/Manager/MasterPage/PageTemplate.Master" AutoEventWireup="True"
    Codebehind="Manager.aspx.cs" Inherits="FrameWork.web.Manager.Module.App.app_Notify.Manager"
    Title="通知管理" %>

<asp:Content ID="Content1" ContentPlaceHolderID="PageBody" runat="server">
    <FrameWorkWebControls:HeadMenuWebControls ID="HeadMenuWebControls1" runat="server"  HeadTitleTxt="">
        <FrameWorkWebControls:HeadMenuButtonItem ButtonPopedom="List" ButtonUrl="Default.aspx"
            ButtonUrlType="Href" ButtonVisible="True" ButtonName="" />
    </FrameWorkWebControls:HeadMenuWebControls>
    <FrameWorkWebControls:TabOptionWebControls ID="TabOptionWebControls1" runat="server">
        <FrameWorkWebControls:TabOptionItem ID="TabOptionItem1" runat="server" Tab_Name="查看/修改/增加">
            <table width="100%" border="0" cellspacing="1" cellpadding="3" align="center">

                <tr>
                    <td class="table_body">
                        标题</td>
                    <td class="table_none">
                     
                        <asp:TextBox ID="Title_Input"  runat="server" CssClass="text_input"></asp:TextBox>
                    
                        <asp:Label ID="Title_Disp" runat="server"></asp:Label></td>
                </tr>

                <tr>
                    <td class="table_body">
                        通知部门</td>
                    <td class="table_none">
                     
                        <asp:TextBox ID="Notifier_Input"  runat="server" CssClass="text_input"></asp:TextBox>
                    
                        <asp:Label ID="Notifier_Disp" runat="server"></asp:Label></td>
                </tr>

                <tr>
                    <td class="table_body">
                        通知时间</td>
                    <td class="table_none">
                     
                        <asp:TextBox ID="AddTime_Input"  runat="server" CssClass="text_input" onfocus="javascript:HS_setDate(this);"></asp:TextBox>
                    
                        <asp:Label ID="AddTime_Disp" runat="server"></asp:Label></td>
                </tr>

                <tr>
                
                    <td class="table_body table_body_NoWidth">
                        通知内容</td>
                    <td class="table_none table_none_NoWidth">
                     
                        <asp:TextBox ID="Content_Input" title="请输入内容:" runat="server"  Rows="10" TextMode="MultiLine" CssClass="tex_input"></asp:TextBox>
                    
                        <asp:Label ID="Content_Disp" runat="server"></asp:Label></td>
                </tr>
                              
                <tr id="ButtonOption" runat="server">
                    <td align="right" colspan="2">
                        <asp:Button ID="Button1" runat="server" CssClass="button_bak" Text="确定" OnClick="Button1_Click" />
                        <input id="Reset1" class="button_bak" type="reset" value="重填" />
                    </td>
                </tr>
            </table>
        </FrameWorkWebControls:TabOptionItem>
    </FrameWorkWebControls:TabOptionWebControls>
</asp:Content>
