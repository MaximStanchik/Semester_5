-- Создание пользователя SMA:

alter pluggable database XEPDB1 close;
alter pluggable database XEPDB1 open read only;

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

create user U1_SMA_PDB identified by aaaa 
default tablespace U1_SMA_permanentTablespace quota unlimited on U1_SMA_permanentTablespace  
temporary tablespace U1_SMA_tempoTablespace
profile SMAProfile
account unlock;
commit;
grant RL_NewSMARole to U1_SMA_PDB; 

--с пользователями сложно, нужно будет разобраться

grant create session to SMA;
grant restricted session to SMA;
grant create any table to SMA;
grant create any view to SMA;
grant create sequence to SMA;
grant unlimited tablespace to SMA;
grant create cluster to SMA;
grant create synonym to SMA;
grant create public synonym to SMA;
grant create materialized view to SMA;
grant create any procedure to SMA;



--Создание и открытие PDB 

CREATE PLUGGABLE DATABASE SMA_PDB from XEPDB1
FILE_NAME_CONVERT = ('/opt/oracle/oradata/XE/XEPDB1', '/opt/oracle/oradata/XE/XEPDB1/SES_PDB');

alter pluggable database all except pdb$seed open read write force; 
SELECT name, open_mode FROM v$pdbs;
alter pluggable database SMA_PDB open;

SELECT * FROM dba_role_privs WHERE grantee = 'U1_SMA_PDB';
SET ROLE RL_NewSMARole;

grant connect to U1_SMA_PDB;

SELECT username, account_status FROM dba_users WHERE username = 'U1_SMA_PDB';
ALTER USER U1_SMA_PDB ACCOUNT UNLOCK;