alter session set "_ORACLE_SCRIPT" = true;

select * from dba_tablespaces;

--------------------Task_1--------------------

create smallfile tablespace TS_SMA 
datafile 'TS_SMA' size 7m autoextend on next 5m maxsize 30m;
drop tablespace TS_SMA including contents and datafiles;

--------------------Task_2--------------------

create temporary tablespace TS_SMA_TEMP
tempfile 'TS_SMA_TEMP' size 5m autoextend on next 3m maxsize 30m;
drop tablespace TS_SMA_TEMP including contents and datafiles;

--------------------Task_3--------------------

select * from dba_tablespaces; //помимо имен получаем и другую информацию
select tablespace_name from dba_tablespaces;

--------------------Task_4--------------------

CREATE ROLE C##RL_SMACORE;
drop role C##RL_SMACORE;

grant create session to C##RL_SMACORE;
grant create table to C##RL_SMACORE; 
grant create procedure to C##RL_SMACORE;
grant create view to C##RL_SMACORE;  
grant drop any table to C##RL_SMACORE;
grant drop any procedure to C##RL_SMACORE; 
grant drop any view to C##RL_SMACORE;

--------------------Task_5--------------------

select * from dba_roles where role like 'C##RL_SMACORE';
select * from ROLE_SYS_PRIVS where role = 'C##RL_SMACORE';

--------------------Task_6--------------------

create profile C##PF_SMACORE limit
password_life_time 180
sessions_per_user 3
failed_login_attempts 7
password_lock_time 1
password_reuse_time 10
password_grace_time default
connect_time 180
idle_time 30;

--------------------Task_7--------------------

select profile from dba_profiles;
select * from dba_profiles where profile = 'C##PF_SMACORE';
select * from dba_profiles where profile = 'DEFAULT';

--------------------Task_8--------------------
create user SMACORE identified by password1337 
default tablespace TS_SMA quota unlimited on TS_SMA  
temporary tablespace TS_SMA_TEMP
profile C##PF_SMACORE
account unlock
password expire;
commit;
GRANT C##RL_SMACORE TO SMACORE; 

drop user SMACORE;

select * from dba_users;

--------------------Task_9--------------------

//Результат выполнения задания продемонстрирован в отчете

--------------------Task_10--------------------

//Таблицы и представление созданы пользователем SMACORE. Сначала подключился к SMACORE_Connection, а потом все посоздавал

create table Employees (
    EmployeeID int,
    FirstName varchar(50),
    LastName varchar(50),
    Department varchar(50)
);

insert into Employees (EmployeeID, FirstName, LastName, Department) values (1, 'John', 'Doe', 'IT');
insert into Employees (EmployeeID, FirstName, LastName, Department) values (2, 'Jane', 'Smith', 'HR');
insert into Employees (EmployeeID, FirstName, LastName, Department) values (3, 'Alice', 'Johnson', 'Finance');

create view EmployeeView as
select FirstName, LastName
from Employees;

drop view EmployeeView;


select * from Employees;

--------------------Task_11--------------------

create tablespace SMA_QDATA 
datafile'XXX_QDATA.dbf' size 10m offline; 

alter tablespace SMA_QDATA online;

alter user SMACORE quota 2m on SMA_QDATA;

//Создана SMACORE-ом
create table SMA_T1 ( 
    column1 varchar(50),
    column2 number
);

insert into SMA_T1 (column1, column2) values ('Значение1', 10);
insert into SMA_T1 (column1, column2) values ('Значение2', 20);
insert into SMA_T1 (column1, column2) values ('Значение3', 30);

select * from SMA_T1;








