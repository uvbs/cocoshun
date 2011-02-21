<%@ Page Language="C#" AutoEventWireup="true" MasterPageFile="~/template/MasterPage/Template.Master" CodeBehind="news.aspx.cs" Inherits="FrameWork.web.Home.NewsTemplate" %>

<asp:Content ID="Content" ContentPlaceHolderID="Body" runat="server">
    <table height="100%" width="100%" border="0" align=center>
        <tr height="50" align="center">
            <td><h2>
                <asp:Label ID="NewsTitle" runat="server"></asp:Label>&nbsp;</h2></td>
        </tr>
        <tr height="10" align="center">
            <td>
                <asp:Label ID="NewsAuthorTime" runat="server"></asp:Label>
            </td>
        </tr>
       <tr height="10">
            <td>
                &nbsp;
             </td>
        </tr>         
        <tr height="20"  align="center">
            <td> 
                <asp:Image ID="NewsImage" Width="80%" Height="60%" runat="server"/>
            </td>
        </tr>
         <tr height="20"  align="center">
            <td> 
                <asp:Label ID="ImageComment" runat="server"></asp:Label>
            </td>
        </tr> 
         <tr height="20"  align="center">
            <td> 
                &nbsp;
            </td>
        </tr>               
        <tr height="50"  align="left">
            <td>
                <asp:Label ID="NewsContent" runat="server"></asp:Label>
             </td>
        </tr>                        
    </table>
   
</asp:Content>