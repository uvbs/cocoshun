<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="NewsPic.aspx.cs" Inherits="FrameWork.web.Home.NewsPic" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" >
<head runat="server">
    <title>新闻图片</title>
    <script src="js/jquery-1.4a2.min.js" type="text/javascript"></script>
    <script src="js/jquery.KinSlideshow-1.2.1.min.js" type="text/javascript"></script>
    <script type="text/javascript">
    $(function(){
	    $("#KinSlideshow").KinSlideshow();
    })
    </script>
    <style type="text/css">
    .code{ height:auto; padding:20px; border:1px solid #9EC9FE; background:#ECF3FD;}
    .code pre{ font-family:"Courier New";font-size:14px;}
    .info{ font-size:12px; color:#666666; font-family:Verdana; margin:20px 0 50px 0;}
    .info p{ margin:0; padding:0; line-height:22px; text-indent:40px;}
    h2.title{ margin:0; padding:0; margin-top:50px; font-size:18px; font-family:"微软雅黑",Verdana;}
    h3.title{ font-size:16px; font-family:"微软雅黑",Verdana;}
    .importInfo{ font-family:Verdana; font-size:14px;}
    </style>    
</head>
<body>
<%--    <form id="form1" runat="server">
    <div>
        &nbsp;</div>
    </form>--%>
    <%=Html %>
</body>
</html>
