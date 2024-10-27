--------------------Task_1--------------------
select * from dba_tablespaces;

select tablespace_name, file_name from sys.dba_data_files;
select tablespace_name, file_name from sys.dba_temp_files;
--------------------Task_2--------------------
create tablespace SMA_QDATA
    datafile 'SMA_QDATA.dbf'
    size 10M
    autoextend on
    next 5M
    maxsize 20M
    offline;
    DROP TABLESPACE SMA_QDATA INCLUDING CONTENTS AND DATAFILES;
alter tablespace SMA_QDATA online;
select tablespace_name, status, contents logging from SYS.DBA_TABLESPACES;
DROP TABLESPACE SMA_QDATA INCLUDING CONTENTS AND DATAFILES;
ALTER SESSION SET CONTAINER=CDB$ROOT;
ALTER SESSION SET CONTAINER=XEPDB1;  
create user SMA identified by a111
default tablespace SMA_QDATA quota 2m on SMA_QDATA;  
grant connect, create session, alter session, create any table, drop any table to SMA;
grant create session to SMA;

select * from dba_users where username = 'SMA';

alter user SMA quota 2m on SMA_QDATA;

select tablespace_name, bytes, max_bytes from dba_ts_quotas where tablespace_name = 'SMA_QDATA' and username = 'SMA';

----подключаемся как SMA

create table SMA_T2 (
    x integer primary key,
    y integer
) tablespace SMA_QDATA;

insert into SMA_T2(x, y) values (1, 2);
insert into SMA_T2(x, y) values (2, 3);
insert into SMA_T2(x, y) values (3, 4);

select * from SMA_T2;

--------------------Task_3--------------------

SELECT * FROM dba_segments WHERE tablespace_name = 'SMA_QDATA';
--------------------Task_4--------------------
drop table SMA_T2;
select * from dba_segments where tablespace_name = 'SMA_QDATA';
select * from USER_RECYCLEBIN;
--------------------Task_5--------------------
flashback table SMA_T2 to before drop;
select * from SMA_T2;
--------------------Task_6--------------------
declare
    i integer := 4;
begin
    while i < 10004 loop
        insert into SMA_T2(x, y) values (i, i);
        i := i + 1;
    end loop;
    commit;
end;

select count(*) from SMA_T2;
--------------------Task_7--------------------
select extents, bytes, blocks from dba_segments where segment_name = 'SMA_T2';
select * from dba_extents where segment_name = 'SMA_T2';
--------------------Task_8--------------------
----подключаемся как SYS
drop tablespace SMA_QDATA including contents and datafiles;
--------------------Task_9--------------------
select group# from v$logfile;
select group# from v$log where status = 'CURRENT';
--------------------Task_10-------------------
select member from v$logfile;
--------------------Task_11-------------------
select group#, status from v$log;
ALTER SESSION SET CONTAINER=CDB$ROOT; 
alter system switch logfile; 
select TO_CHAR(SYSDATE, 'HH24:MI DD MONTH YYYY') as current_date from DUAL;
--13:41 22 ОКТЯБРЯ  2024
select group# from v$log where status = 'CURRENT';
--------------------Task_12-------------------
alter database add logfile 
    group 4 
    'D:\User\Desktop\StudyAtBSTU\Course_3\Semester5\Subjects\Database\Laboratory works\LBR_04\Solution\new\REDO04.LOG'
    size 50m 
    blocksize 512;

-- Проверка
select group# from v$logfile;

alter database add logfile 
    member 
    'D:\User\Desktop\StudyAtBSTU\Course_3\Semester5\Subjects\Database\Laboratory works\LBR_04\Solution\new\REDO04_1.LOG' 
    to group 4;
    
alter database add logfile 
    member 
    'D:\User\Desktop\StudyAtBSTU\Course_3\Semester5\Subjects\Database\Laboratory works\LBR_04\Solution\new\REDO04_2.LOG' 
    to group 4;
    
alter database add logfile 
    member 
    'D:\User\Desktop\StudyAtBSTU\Course_3\Semester5\Subjects\Database\Laboratory works\LBR_04\Solution\new\REDO04_3.LOG' 
    to group 4;
    
select * from V$LOG order by GROUP#;
select * from V$LOGFILE order by GROUP#;
alter system switch logfile;
select group#, status from V$LOG;
select group# from V$LOG where status = 'CURRENT';
--------------------Task_13-------------------
ALTER SYSTEM SWITCH LOGFILE;
ALTER DATABASE OPEN;
alter database drop logfile member 'D:\User\Desktop\StudyAtBSTU\Course_3\Semester5\Subjects\Database\Laboratory works\LBR_04\Solution\new\REDO04_1.LOG';
alter database drop logfile member 'D:\User\Desktop\StudyAtBSTU\Course_3\Semester5\Subjects\Database\Laboratory works\LBR_04\Solution\new\REDO04_2.LOG';
alter database drop logfile member 'D:\User\Desktop\StudyAtBSTU\Course_3\Semester5\Subjects\Database\Laboratory works\LBR_04\Solution\new\REDO04_3.LOG';
alter database drop logfile group 4;

--------------------Task_14-------------------
select DBID, NAME, LOG_MODE from V$DATABASE;
select INSTANCE_NAME, ARCHIVER, ACTIVE_STATE from V$INSTANCE;

--------------------Task_15-------------------
select * from V$ARCHIVED_LOG;
--------------------Task_16-------------------
-- Включить архивирование
-- Заходим в SQLPLUS:
-- connect /as sysdba (или sys /as sysdba);
-- shutdown immediate;
-- startup mount;
-- alter database archivelog;
-- alter database open;

SHUTDOWN IMMEDIATE;
STARTUP MOUNT;
ALTER DATABASE ARCHIVELOG;
ALTER DATABASE OPEN;

-- Теперь будут значения: LOG_MODE = ARCHIVELOG; ARCHIVER = STARTED
select DBID, NAME, LOG_MODE from V$DATABASE;
select INSTANCE_NAME, ARCHIVER, ACTIVE_STATE from V$INSTANCE;
--------------------Task_17-------------------
alter system switch logfile;
select group# from V$LOG where status = 'CURRENT';
select * from V$ARCHIVED_LOG;
--------------------Task_18-------------------
-- Выключить архивирование
-- Заходим в SQLPLUS:
-- connect /as sysdba (или sys /as sysdba);
-- shutdown immediate;
-- startup mount;
-- alter database noarchivelog;
-- alter database open;

shutdown immediate;
startup mount;
alter database noarchivelog;
alter database open;

-- Теперь опять будут значения: LOG_MODE = NOARCHIVELOG; ARCHIVER = STOPPED
select DBID, name, LOG_MODE from V$DATABASE;
select INSTANCE_NAME, ARCHIVER, ACTIVE_STATE from V$INSTANCE;
--------------------Task_19-------------------
select * from V$CONTROLFILE;
--------------------Task_20-------------------
show parameter control_files; 
select * from V$CONTROLFILE_RECORD_SECTION;
--------------------Task_21-------------------
show parameter pfile;
--------------------Task_22-------------------
create pfile = 'SMA_PFILE.ora' from spfile;
--------------------Task_23-------------------
select * from V$PWFILE_USERS;    
show parameter remote_login_passwordfile; --на доккере, в папке с бд
--------------------Task_24-------------------
select * from V$DIAG_INFO;

--------------------Task_25-------------------
SELECT GROUP#, MEMBER 
FROM V$LOGFILE;
