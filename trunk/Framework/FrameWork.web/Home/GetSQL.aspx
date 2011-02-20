<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="GetSQL.aspx.cs" Inherits="FrameWork.web.Home.GetSQL" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" >
<head runat="server">
    <title>无标题页</title>
</head>
<body>
    <form id="form1" runat="server">
    <div>
        &nbsp;<asp:GridView ID="GridView1" runat="server" DataSourceID="AccessDataSource1" AutoGenerateColumns="False" DataKeyNames="ID">
            <Columns>
                <asp:BoundField DataField="ID" HeaderText="ID" InsertVisible="False" ReadOnly="True"
                    SortExpression="ID" />
                <asp:BoundField DataField="ImagePath" HeaderText="ImagePath" SortExpression="ImagePath" />
            </Columns>
        </asp:GridView>
        <asp:AccessDataSource ID="AccessDataSource1" runat="server" DataFile="~/App_Data/FrameWork.mdb" OnSelecting="AccessDataSource1_Selecting" SelectCommand="SELECT [ID], [ImagePath] FROM [app_News] ORDER BY [AddTime] DESC"></asp:AccessDataSource>
        &nbsp;
    
    </div>
    </form>
</body>
</html>
