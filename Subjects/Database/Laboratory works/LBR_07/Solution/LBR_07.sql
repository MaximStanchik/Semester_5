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
    drop sequence S2;
select S2.nextval from dual;
select S2.currval from dual;
--------------------Task_4--------------------
create sequence S3
  start with 10
  increment by -10
  minvalue -100
  maxvalue 10
  nocycle
  order;
  
select S3.nextval from dual connect by level <= 11; 

select S3.nextval from dual; 
select S3.nextval from dual;
--------------------Task_5--------------------
create sequence S4
  start with 1
  increment by 1
  maxvalue 10
  cycle
  cache 5
  noorder;
  
select S4.nextval from DUAL;
--------------------Task_6--------------------
select * from all_sequences where sequence_owner = 'SMA';
drop sequence S1;
drop sequence S2;
drop sequence S3;
drop sequence S4;
--------------------Task_7--------------------
create table T1 (
  N1 number(20),
  N2 number(20),
  N3 number(20),
  N4 number(20)
) cache storage ( buffer_pool keep ) tablespace TS_SMA;

begin
  for i in 1..7 loop
    insert into T1 values (S1.nextval, S2.nextval, S3.nextval, S4.nextval);
  end loop;
end;

select * from T1;
--------------------Task_8--------------------
create cluster ABC (
  X number(10),
  V varchar2(12)
) size 200 hashkeys 200;
--------------------Task_9--------------------
create table A (
  XA number(10),
  VA varchar2(12),
  Y number(10)
) cluster ABC(XA, VA);
--------------------Task_10--------------------
create table B (
  XB number(10),
  VB varchar2(12),
  Z number(10)
) cluster ABC(XB, VB);

insert into B values (1, '1', 1);
--------------------Task_11--------------------
create table C (
  XC number(10),
  VC varchar2(12),
  W number(10)
) cluster ABC(XC, VC);

insert into C values (1, '1', 1);
--------------------Task_12--------------------
select table_name from user_tables where table_name = 'C';
select table_name from user_tables where table_name = 'B';
select table_name from user_tables where table_name = 'A';
select table_name from user_tables where table_name = 'T1';

select table_name from dba_tables where table_name = 'C';
select table_name from dba_tables where table_name = 'B';
select table_name from dba_tables where table_name = 'A';
select table_name from dba_tables where table_name = 'T1';

select cluster_name from user_clusters where cluster_name = 'ABC';
--------------------Task_13--------------------
create synonym SC for SMA.C;
SELECT * FROM C;
--------------------Task_14--------------------
create public synonym SB1 FOR SYS.B;
SELECT * FROM SB1;
--------------------Task_15--------------------
create table A16 (
  XA number(10),
  VA varchar2(12),
  Y number(10),
  constraint PK_A16 primary key (XA)
);

create table B16 (
  XB number(10),
  VB varchar2(12),
  Z number(10),
  constraint FK_B16 foreign key (XB) references A16(XA)
);

insert into A16 values (1, '1', 1);
insert into B16 values (1, '1', 1);

create view V1 AS
  select * from A16
  inner join B16 on A16.XA = B16.XB;

select * from V1;
--------------------Task_16--------------------
create materialized view MV
  refresh force on demand
  next SYSDATE + 2/1440
  as
    select * from A16
    inner join
    B16
    on A16.XA = B16.XB;

select * from MV;
