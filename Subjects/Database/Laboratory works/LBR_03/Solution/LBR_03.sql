--------------------Task_1--------------------

select * from cdb_pdbs;

--------------------Task_2--------------------

select instance_name, status, host_name, version from v$instance;

--------------------Task_3--------------------

select comp_id, comp_name, version, status from dba_registry;

--------------------Task_4--------------------
alter pluggable database XEPDB1 close;
alter pluggable database XEPDB1 open read only;

CREATE PLUGGABLE DATABASE SMA_PDB from XEPDB1
FILE_NAME_CONVERT = ('/opt/oracle/oradata/XE/XEPDB1', '/opt/oracle/oradata/XE/XEPDB1/SES_PDB');

alter pluggable database all except pdb$seed open read write force; 
SELECT name, open_mode FROM v$pdbs;
--------------------Task_5--------------------

select * from cdb_pdbs;

--------------------Task_6--------------------
ALTER DATABASE OPEN;
alter session set "_ORACLE_SCRIPT" = true;

create tablespace U1_SMA_permanentTablespace datafile 'U1_SMA_permanentTablespace' size 7m autoextend on next 3m maxsize 30m;
create temporary tablespace U1_SMA_tempoTablespace tempfile 'U1_SMA_tempoTableSpace' size 3m autoextend on next 7m maxsize 10m;

select * from dba_tablespaces;

create role RL_NewSMARole;
grant create session to RL_NewSMARole;
grant create table to RL_NewSMARole;
grant create procedure to RL_NewSMARole;
grant drop any table to RL_NewSMARole;
grant drop any procedure to RL_NewSMARole;

select * from dba_roles;

create profile SMAProfile limit
password_life_time 180
sessions_per_user 3
failed_login_attempts 1000
password_lock_time 1
password_reuse_time 10
password_grace_time default
connect_time 180
idle_time 30;

alter session set "_ORACLE_SCRIPT" = true;

create user U1_SMA_PDB identified by a4444 
default tablespace U1_SMA_permanentTablespace quota unlimited on U1_SMA_permanentTablespace  
temporary tablespace U1_SMA_tempoTablespace
profile SMAProfile
account unlock;
commit;
grant RL_NewSMARole to U1_SMA_PDB; 

--------------------Task_7--------------------
//TODO: выполнить подключение к пользователю

create table SMA_table (
    id number,
    name varchar2(50)
);

insert into SMA_table (id, name) values (1, 'Alice');
insert into SMA_table (id, name) values (2, 'Bob');
insert into SMA_table (id, name) values (3, 'Charlie');

select * from SMA_table;

--------------------Task_8--------------------

----выполняется SYS-ом:

select tablespace_name, status, contents 
from dba_tablespaces;

select file_name, tablespace_name, bytes, status 
from dba_data_files;

select *
from dba_roles ;
where role in (select role from dba_roles);

select profile, resource_name, limit 
from dba_profiles;

select username, granted_role 
from dba_role_privs;

--------------------Task_9--------------------
----подключаемся к Conn_to_ultrasuperNEW кав SYS + пароль

create user C##SMA identified by a111;
grant connect, create session, alter session, create any table, drop any table to C##SMA container = all;
grant create session to C##SMA;

select * from dba_users where username = 'C##SMA';
SELECT name, open_mode FROM v$pdbs;
--------------------Task_10--------------------

alter pluggable database SMA_PDB close immediate;
drop pluggable database SMA_PDB including datafiles;
drop user C##SMA;


