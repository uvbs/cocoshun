ASP.NET权限管理系统(FrameWork) 1.0.6 Release 说明文档

1.起源
在我们开发软件过程中,经常会需要开发一个后台管理程序.用于管理我们开发的前台软件.
当你开发的软件越来越多的时候,你的管理后台也会越来越多.这时如果有一个统一的管理后台.来进来管理.有统一台帐号,统一的授权来进行多个后台的管理就好了.
FrameWork就是在这样的需求下产生了. 

2.功能
其主要的功能就是,进行后台管理模块整合.
1)其可以支持多个应用,多个模块的权限管理.
2)支持Access和MsSql200/2005及Oracle9i以上.
3)采用角色来进行权限的授权,每个用户可以属于多个角色,享有交差权限.
4)整合方便,权限检测采用httpmodule方式检测.基本不用对原有程序进行修改,便可将原有程序进行整合.
5)可视化编辑,全新的Menu和Tab控件.支持拖拉式编辑.
6)统一的事件日志管理,所有登陆操作都有安全记录.
7)每个模块的每个栏目对应一个目录, 栏目的权限抽象分为(查看/新增/修改/删除/排序/打印/备用A/备用8).目录里有一个web.config来进行目录文件权限配置,可直接将某个文件名设定到相对应的权限上.

3.开发环境
Vs2005 sp1 + win2003 标准版 + Mssql2000/2005

4.初始用户名:admin 密码:admin

5.官方论坛:http://framework.supesoft.com/bbs/

6.帮助文档:http://framework.supesoft.com/help/

7.官方网站:http://framework.supesoft.com/

附:最终用户授权协议

ASP.NET通用权限管理系统(FrameWork) 1.0.6
版权所有 (c) 2008 Supesoft.com 保留所有权力 


BSD许可证的许可条件细目： 

在满足下列条件的前提下，允许再发布经过或未经过修改的、源代码或二进制形式的本软件： 
1．源代码的再发布，必须保留原来代码中的版权声明、这几条许可条件细目，和下面的免责声明。 
2．二进制形式的再发布，必须在随同提供的文档和其它媒介中，复制原来的版权声明、这几条许可条件细目，和下面的免责声明。 
3．如果没有特殊的事前书面许可，Supesoft.com，和贡献者名字，都不能用于支持或宣传从既有软件派生的产品。 


BSD许可证的免责声明： 

此软件由版权所有者和贡献者以“即此”方式提供。无论明示或暗示的，包括但不限于间接的关于基于某种目的的适销性、实用性，在此皆明示不予保证。在任何情况下，由于使用此软件造成的，直接、间接、连带、特别、惩戒或因此而造成的损害（包括但不限于获得替代品及服务，无法使用，丢失数据，损失盈利或业务中断），无论此类损害是如何造成的，基于何种责任推断，是否属于合同范畴，严格赔偿责任或民事侵权行为（包括疏忽和其他原因），即使预先被告知此类损害可能发生，版权所有者和贡献者均不承担任何责任。 


如你需要商业技术支持请购买我们的服务.
具体请参考 http://framework.supesoft.com

1.0.6版更新记录

1.角色管理,可以增加用户 
2.重启应用,跳转路径问题 
3.修改验证码,验证码修改为默认不显示，出错次数到就显示。
4.左侧经典菜单中，点击选中项高亮或变色，在隐藏、开启后仍保留，以记录当前状态 
5.对于 sys_FieldValue表 增加 V_Code 列,增加点文字选择 
6.增加table_body和table_none不带宽度css 
7.实现缓存接口,通过扩展可支持多站点统一权限库布署 
8.当时间字段可以为空的,增加DateTime? 
9.应用及其模块分类和模块后再仅仅删除应用将删除不干净 
10.部门反向获取用户列表 
11.是否自动检测有新版本更新配置 
12.app_HttpGZip,app_AuthMethod,app_Auth 增加是否在manager目录判断 
13.事件日志管理中用户的登陆系统、退出系统操作，用户名无法记录
14.角色,增加用户,没有进行权限判断,搜索日志问题
15.用户管理页,必须是"超级用户"或"备用A"权限才可以修改用户角色和密码.admin帐号密码和状态 不能被修改 
16.增加"日志列表"和"用户列表" 表头排序功能. 
17.登陆login.aspx检测是否登陆.

更新说明:
1.数据库更新:
  a)Access数据库,打开FrameWork.web\Manager\database\access\FrameWork.config,为sys_FieldValue表增加,V_Code字段,类型为字符,长度100.允许空值.
  b)Sql数据库,执行FrameWork.web\Manager\database\mssql\目录中的:FrameWork1.06表结构更新.sql,FrameWork1.0.6存储过程更新.sql二个文件,完成更新.
  c)Oracle数据库,执行FrameWork.web\Manager\database\Oracle\目录中的:FrameWork1.06表结构更新(Oracle).sql文件完成更新.
2.打开FrameWork.Web目录中的web.config文件,在<appSettings>节点增加如下节点:
    <!--缓存类配置(命名空间) FrameWorkCache.IloveYou-->
    <add key="Cachenamespace" value="FrameWork"/>
    <!--缓存类配置(类名) FrameWorkCache.IloveYou.FrameWorkCacheRemoting-->
    <add key="CacheclassName" value="FrameWork.HttpWebCache"/>
    <!--Remoting服务器地址-->
    <add key="FrameWorkCacheService" value="tcp://localhost:9742/FrameWorkCache.CacheManager"/>
3.将FrameWork.web\manager目录中所有文件替换原有文件.
4.完成更新.

1.0.5版更新记录
 
1.数据库配置出错,死循环Message.aspx出错
2.分类管理移动分类支持firefox.
3.若上传文件为RAR，打开的话就会报错
4.更新一些js支持firefox
5.将原来根目录文件移到Manager子目录
6.写日志目录配置(在web.config中配置),上传文件目录配置(在后台系统设置中配置)
7.TabOptionWebControls控件在vs2008下设计视图中不能正常显示
8.增加在线用户表,可以设置在线用户是存放于数据库或缓存中
9.修正Access数据库分页最后页显示不正确
10.修正MultiListBox控件,选项重复移除错乱问题
11.提示信息框修改为session保存

更新说明:
1.将你原有FrameWork.Web\module\目录下你自己开发的模块文件(不是FrameWork文件夹)复制到manager\module里面
2.修改刚复制所有的aspx文件中的第一行,找到MasterPageFile="~/MasterPage/PageTemplate.Master"修改为MasterPageFile="~/Manager/MasterPage/PageTemplate.Master".
3.在线用户表更新:
  a)Access数据库,打开FrameWork.web\Manager\database\access\DBBack.mdb,将sys_Online表复制到原有的数据库.
  b)Sql数据库,执行FrameWork.web\Manager\database\mssql\SQL在线用户数据库升级.sql
  c)Oracle数据库,执行FrameWork.web\Manager\database\Oracle\Oracle在线用户数据库升级.sql
4.完成更新.

1.0.4版更新记录
 
1.增加Oracle数据库支持
2.增加网页http压缩功能
3.没有权限按钮下,firefox显示问题
4.数据库无修改，直接替换原有文件即可升级。

1.0.3版更新记录
 
1.修改写日志文件无效
2.修改出错事件先后顺序
3.应用模块管理中,查看模块,默认没有选中
4.修改日期输入出错1999/11/22
5.修改查询分页默认值为10到99999999
6.增加对Firefox浏览器支持
7.自动检测更新出错
8.数据库无修改，直接替换原有文件即可升级。

1.0.2版更新记录
 
1.修改写日志文件方法 
2.修改上传图片缩图效果 
3.应用模块配置,点击模块分类.默认显示模块列表
4.操作日志,显示IP增加查询链接 
5.应用模块管理,增加子分类数 
6.直接关闭ie,出现提示.
7.应用模块列表,增加显示应用ID
8.增加对ASP.NET通用权限管理系统(FrameWork)专用代码生成工具DDBuildTools支持.介绍请访问:http://framework.supesoft.com/help/?DDBuildTools.htm
9.用户资料增加显示最后操作时间及IP
10.数据库无修改，直接替换原有文件即可升级。

1.0.1版 更新说明：
1.管理员信息只能是管理员才能修改和增加.
2.只有管理员才能设定角色,admin帐号信息无法修改或删除
3.登陆增加是否IE浏览器检测提示 
4.增加上传图片类型,大小限制.增加文件读取程序
5.增加Licensed正确检测. 
6.增加同一IP登陆密码出错5次禁止30 分钟登陆
7.删除部门,无法显示出部门
8.权限检测,增加通过方法属性来进行检测
9.用户信息增加删除标识,日志查询可查删除用户
10.数据库无修改，直接替换原有文件即可升级。

1.0.0版 更新说明：
1.一些操作上的小修改。
2.增加IP地址查询链接
3.取消模块名称必需建在Module下的权限检测限制。
4.模块目录未设置的权限的文件全都默认为"查看"权限(目前支持在web.config配置文件权限或在程序中使用FrameWorkPermission.CheckPermissionVoid方法来检测权限)
5.增加内存使用状态查询。
6.增加开发模式下用户在线时间过期无效功能(重新编译文件后不需要再重新登陆，需要些功能请将Web.config中的OnlineMinute设为0)
7.授权修改为BSD协议。
8.数据库无修改，直接替换原有文件即可升级。