--FrameWork1.06表结构更新.sql by supesoft.com 2008/04/29
--sys_FieldValueTable 表 增加 V_Code 列
alter table sys_FieldValue add V_Code varchar(100) default('')
--update sys_fieldvalue set v_code=V_text
