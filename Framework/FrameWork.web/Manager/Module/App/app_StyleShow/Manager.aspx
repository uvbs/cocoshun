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
                    <td width="8%" rowspan="5" class="table_body" style="width: 19%"><p>图片列表</p>
                        <p >
          <%--                  <asp:ListBox ID="ImageList" SelectionMode="Multiple" Rows="10" runat="server" Width="73%">
                                <asp:ListItem>Text</asp:ListItem>
                                <asp:ListItem>Text</asp:ListItem>
                            </asp:ListBox>--%>
                            <SELECT id="ImageList" style="WIDTH: 100%;" size="10">
                                <OPTION value=1>1</OPTION>
                                <OPTION value=2>2</OPTION>
                                <OPTION value=3>3</OPTION>
                                <OPTION value=4>4</OPTION>
                                <OPTION value=5>5</OPTION>
                                <OPTION value=6>6</OPTION>
                                <OPTION value=7>7</OPTION>
                                <OPTION value=8>8</OPTION>
                                <OPTION value=9>9</OPTION>
                            </SELECT>
                    </p></td>
                  <td width="24%" rowspan="5" class="table_body" style="width: 19%"><p>&nbsp;</p>
                    <p>
                        <INPUT class="upBtn" type="button" value="向上↑" onMouseDown="setTimeStart('up');" onMouseUp="clearTimeout(x);"
                        onclick="upListItem();clearTimeout(x);" ID="Button3" NAME="Button1">
                                                <INPUT style="WIDTH: 48px; HEIGHT: 22px" type="button" value="↓向下" class="downBtn" onMouseDown="setTimeStart('down');"
                        onmouseup="clearTimeout(x);" onClick="downListItem();clearTimeout(x);" ID="Button4" NAME="Button2">                    
                    </p>
                  </td>
                    <td width="20%" class="table_body">
                        标题</td>
                    <td width="48%" class="table_none">
                     
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
                    <td align="right" colspan="4">
                        <asp:Button ID="Button1" runat="server" CssClass="button_bak" Text="添加" OnClick="Button1_Click" />
                        <asp:Button ID="Button2" runat="server" CssClass="button_bak" Text="删除" OnClick="Button1_Click" />
                        <input id="Reset1" class="button_bak" type="reset" value="重填" />
                    </td>
                </tr>
            </table>
        </FrameWorkWebControls:TabOptionItem>
    </FrameWorkWebControls:TabOptionWebControls>
    
<script language="javascript" type="text/javascript">
    var x=null;
    var listObj=null;
    //鼠标按下不放时的操作
    function setTimeStart(type)
    {
        listObj=document.getElementById('ImageList');
        //超过0.3秒启动连续的向上(下)的操作
        if(type=="up")
        {
        x=setTimeout(upListItem,300);
        }else
        {
        x=setTimeout(downListItem,300);
        }
    }
    //将选中item向上
    function upListItem()
    {
        var selIndex=listObj.selectedIndex;
        if(selIndex<0)
        {
            if(x!=null){clearTimeout(x);}
            alert("请先选中一项！");
            return;
            }
            if(selIndex==0)
            {
            if(x!=null){clearTimeout(x);}
            //alert("已经移到第一位！");
            return;
        }
        var selValue=listObj.options[selIndex].value;
        var selText=listObj.options[selIndex].text;
        listObj.options[selIndex].value=listObj.options[selIndex-1].value;
        listObj.options[selIndex].text=listObj.options[selIndex-1].text;
        listObj.options[selIndex-1].value=selValue;
        listObj.options[selIndex-1].text=selText;
        listObj.selectedIndex=selIndex-1;
        if(selIndex+1>0)
        {
         x=setTimeout(upListItem,200)
        }
    }
    //将选中item向下
    function downListItem()
    {
         var selIndex=listObj.selectedIndex;
        if(selIndex<0)
        {
            if(x!=null){clearTimeout(x);}
            alert("请先选中一项！");
            return;
        }
        if(selIndex==listObj.options.length-1)
        {
         if(x!=null){clearTimeout(x);}
         //alert("已经移到最后一位！");
        return;
        }
        
        var selValue=listObj.options[selIndex].value;
        var selText=listObj.options[selIndex].text;
        listObj.options[selIndex].value=listObj.options[selIndex+1].value;
        listObj.options[selIndex].text=listObj.options[selIndex+1].text;
        listObj.options[selIndex+1].value=selValue;
        listObj.options[selIndex+1].text=selText;
        listObj.selectedIndex=selIndex+1;
        if(selIndex+1<listObj.options.length-1)
        {
            x=setTimeout(downListItem,200)
        }
    }
</script>    
</asp:Content>
