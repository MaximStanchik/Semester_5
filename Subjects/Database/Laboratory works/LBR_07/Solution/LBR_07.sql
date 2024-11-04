--------------------Task_1--------------------
alter session set "_ORACLE_SCRIPT" = true;

select username from all_users where username = 'SMA';

create smallfile tablespace TS_SMA 
datafile 'TS_SMA' size 7m autoextend on next 5m maxsize 30m;

create temporary tablespace TS_SMA_TEMP
tempfile 'TS_SMA_TEMP' size 5m autoextend on next 3m maxsize 30m;

create role RL_SMA;

grant create session to RL_SMA;
grant create table to RL_SMA; 
grant create procedure to RL_SMA;
grant create view to RL_SMA;  

grant create sequence to RL_SMA;
grant create cluster to RL_SMA;
grant create synonym to RL_SMA;
grant create materialized view to RL_SMA;

grant drop any table to RL_SMA;
grant drop any procedure to RL_SMA; 
grant drop any view to RL_SMA;

create profile PF_SMACORE limit
password_life_time 180
sessions_per_user 3
failed_login_attempts 7
password_lock_time 1
password_reuse_time 10
password_grace_time default
connect_time 180
idle_time 30;

create user SMA identified by bbbb 
default tablespace TS_SMA quota unlimited on TS_SMA  
temporary tablespace TS_SMA_TEMP
profile PF_SMACORE
account unlock
password expire;
commit;
grant RL_SMA to SMA;

SELECT name FROM v$database;
--------------------Task_2--------------------
create sequence S1 
    start with 1000 
    increment by 10 
    nocycle 
    nocache;
    
select S1.nextval from dual;
select S1.currval from dual;
--------------------Task_3--------------------
create sequence S2
    start with 10
    increment by 10
    maxvalue 100
    nocycle;
    
select S2.nextval from dual;
select S2.currval from dual;
--------------------Task_4--------------------
--------------------Task_5--------------------
--------------------Task_6--------------------
--------------------Task_7--------------------
--------------------Task_8--------------------
--------------------Task_9--------------------
--------------------Task_10--------------------
--------------------Task_11--------------------
--------------------Task_12--------------------
--------------------Task_13--------------------
--------------------Task_14--------------------
--------------------Task_15--------------------
--------------------Task_16--------------------
--------------------Task_17--------------------
