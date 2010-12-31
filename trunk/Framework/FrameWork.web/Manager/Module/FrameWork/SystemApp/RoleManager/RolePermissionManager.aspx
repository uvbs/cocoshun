<%@ Page Language="C#" MasterPageFile="~/Manager/MasterPage/PageTemplate.Master" AutoEventWireup="true" CodeBehind="RolePermissionManager.aspx.cs" Inherits="FrameWork.web.Module.FrameWork.RoleManager.RolePermissionManager"  %>
<asp:Content ID="Content1" ContentPlaceHolderID="PageBody" runat="server">
    <FrameWorkWebControls:HeadMenuWebControls ID="HeadMenuWebControls1" runat="server"
        HeadOPTxt="角色应用权限管理" HeadTitleTxt="角色资料管理">
    </FrameWorkWebControls:HeadMenuWebControls>
    <FrameWorkWebControls:TabOptionWebControls ID="TabOptionWebControls1" runat="server">
        <FrameWorkWebControls:TabOptionItem ID="TabOptionItem1" runat="server" Tab_Name="角色应用权限管理">
        <table width="100%" border="0" cellspacing="1" cellpadding="3" align="center">
		<tr>
			<td class="table_body">
                角色名称</td>
			<td class="table_none">
                <asp:Label ID="RoleName_Txt" runat="server"></asp:Label></td>
		</tr>
		<tr>
			<td class="table_body">
                应用名称</td>
			<td class="table_none">
                <asp:Label ID="AppName_Txt" runat="server"></asp:Label></td>
		</tr>
		</table>
        <DIV ID="rightsTable" ondblclick="javascript:Check_CheckBox(this);">
		<table width="100%" border="0" cellspacing="1" cellpadding="3" align="center">
	    <asp:Repeater ID="Module_Main" runat="server" OnItemDataBound="Module_Main_ItemDataBound">
		<ItemTemplate>
		<tr class = "table_title">
		    <td colspan="9"><%# Eval("M_CName")%></td>
		</tr>
		<tr class = "table_body" align="center"><td width = "25%" align="left">栏目名称</td><td>查看</td><td>新增</td><td>修改</td><td>删除</td><td>排序</td><td>打印</td><td>备用A</td><td>备用B</td></tr>
            <asp:Repeater ID="Module_Sub" Runat="server" OnItemDataBound="Module_Sub_ItemDataBound">
            <ItemTemplate>
            <tr class="table_none" align="center">
                <td align="left">
                    <%# Eval("M_CName")%></td>
                <td>
                    <asp:Literal runat=server ID=Lab2_Txt></asp:Literal>
                </td>                
                <td>
                    <asp:Literal runat=server ID=Lab4_Txt></asp:Literal>
                </td>
                <td>
                    <asp:Literal runat=server ID=Lab8_Txt></asp:Literal>
                </td>
                <td>
                    <asp:Literal runat=server ID=Lab16_Txt></asp:Literal>
                </td>
                <td>
                    <asp:Literal runat=server ID=Lab32_Txt></asp:Literal>
                </td>
                <td>
                    <asp:Literal runat=server ID=Lab64_Txt></asp:Literal>
                </td>
                <td>
                    <asp:Literal runat=server ID=Lab128_Txt></asp:Literal>
                </td>
                <td>
                    <asp:Literal runat=server ID=Lab256_Txt></asp:Literal>
                </td>
            </tr>
            </ItemTemplate>
            </asp:Repeater>
        </ItemTemplate>
        </asp:Repeater>	
        <tr id="ButtonTr_End" visible="false" runat="server"><td colspan="9" align="right">
            <asp:Button ID="Button1" runat="server" CssClass="button_bak" Text="确定" OnClick="Button1_Click" />
            <input id="Reset1" class="button_bak" type="reset" value="重填" /></td></tr>
		</table>	
		</DIV>
        </FrameWorkWebControls:TabOptionItem>
    </FrameWorkWebControls:TabOptionWebControls>
</asp:Content>
