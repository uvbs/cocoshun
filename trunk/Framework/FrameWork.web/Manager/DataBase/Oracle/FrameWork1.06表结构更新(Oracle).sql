--FrameWork1.06表结构更新.sql by supesoft.com 2008/04/29
--sys_FieldValueTable 表 增加 V_Code 列
alter table SYS_FIELDVALUE add  V_CODE VARCHAR2(100 BYTE);
--update SYS_FIELDVALUE set V_CODE=V_TEXT;
