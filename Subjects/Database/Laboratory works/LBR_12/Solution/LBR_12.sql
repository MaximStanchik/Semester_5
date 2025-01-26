--Создание необходимых таблиц:
create table AUDITORIUM_TYPE (
  AUDITORIUM_TYPE varchar(20) primary key,
  AUDIOTRIUM_TYPENAME varchar(100) unique
);

select * from AUDITORIUM_TYPE;

create table AUDITORIUM (
  AUDITORIUM varchar(20) primary key,
  AUDITORIUM_NAME varchar(100) unique,
  AUDITORIUM_CAPACITY int,
  AUDITORIUM_TYPE varchar(20),
  foreign key (AUDITORIUM_TYPE) references AUDITORIUM_TYPE(AUDITORIUM_TYPE)
);

select * from AUDITORIUM;

create table FACULTY (
  FACULTY varchar(20) primary key,
  FACULTY_NAME varchar(100) unique
);

select * from FACULTY;

create table PULPIT (
  PULPIT varchar(20) primary key,
  PULPIT_NAME varchar(100) unique,
  FACULTY varchar(20),
  foreign key (FACULTY) references FACULTY(FACULTY)
);

select * from PULPIT;

create table TEACHER (
  TEACHER varchar(20) primary key,
  TEACHER_NAME varchar(100) unique,
  PULPIT varchar(20),
  foreign key (PULPIT) references PULPIT(PULPIT)
);

select * from TEACHER;

create table SUBJECT (
  SUBJECT varchar(20) primary key,
  SUBJECT_NAME varchar(100) unique,
  PULPIT varchar(20),
  foreign key (PULPIT) references PULPIT(PULPIT)
);

select * from SUBJECT;

insert into AUDITORIUM_TYPE (AUDITORIUM_TYPE, AUDIOTRIUM_TYPENAME)
values ('Lecture', 'Lecture hall');
insert into AUDITORIUM_TYPE (AUDITORIUM_TYPE, AUDIOTRIUM_TYPENAME)
values ('Laboratory', 'Laboratory');
insert into AUDITORIUM_TYPE (AUDITORIUM_TYPE, AUDIOTRIUM_TYPENAME)
values ('Auditorium', 'Audience');
insert into AUDITORIUM_TYPE (AUDITORIUM_TYPE, AUDIOTRIUM_TYPENAME)
values ('Seminar', 'Seminar room');
insert into AUDITORIUM_TYPE (AUDITORIUM_TYPE, AUDIOTRIUM_TYPENAME)
values ('Conference', 'Conference room');

insert into AUDITORIUM (AUDITORIUM, AUDITORIUM_NAME, AUDITORIUM_CAPACITY, AUDITORIUM_TYPE)
values ('A101', 'Аудитория 101', 100, 'Auditorium');
insert into AUDITORIUM (AUDITORIUM, AUDITORIUM_NAME, AUDITORIUM_CAPACITY, AUDITORIUM_TYPE)
values ('A102', 'Аудитория 102', 50, 'Auditorium');
insert into AUDITORIUM (AUDITORIUM, AUDITORIUM_NAME, AUDITORIUM_CAPACITY, AUDITORIUM_TYPE)
values ('A103', 'Аудитория 103', 70, 'Auditorium');

insert into faculty (FACULTY, FACULTY_NAME)
values ('F001', 'Faculty of Computer Science');
insert into faculty (FACULTY, FACULTY_NAME)
values ('F002', 'Faculty of Science');
insert into faculty (FACULTY, FACULTY_NAME)
values ('F003', 'Faculty of Arts');
insert into faculty (FACULTY, FACULTY_NAME)
values ('F004', 'Faculty of Economics');
insert into faculty (FACULTY, FACULTY_NAME)
values ('F005', 'Faculty of Medicine');

insert into pulpit (PULPIT, PULPIT_NAME, FACULTY)
values ('P001', 'Department of Information Technologies', 'F001');
insert into pulpit (PULPIT, PULPIT_NAME, FACULTY)
values ('P004', 'Department of Economics', 'F004');
insert into pulpit (PULPIT, PULPIT_NAME, FACULTY)
values ('P005', 'Department of Arts', 'F005');

insert into teacher (TEACHER, TEACHER_NAME, PULPIT)
values ('T001', 'Ivan Ivanov', 'P001');
insert into teacher (TEACHER, TEACHER_NAME, PULPIT)
values ('T002', 'Petr Petrov', 'P001');
insert into teacher (TEACHER, TEACHER_NAME, PULPIT)
values ('T003', 'Maria Ivanovna', 'P001');
insert into teacher (TEACHER, TEACHER_NAME, PULPIT) 
values ('T004', 'Olga Valentinovna', 'P001');

insert into subject (SUBJECT, SUBJECT_NAME, PULPIT)
values ('S001', 'Programming', 'P001');
insert into subject (SUBJECT, SUBJECT_NAME, PULPIT)
values ('S002', 'Biology', 'P001');
insert into subject (SUBJECT, SUBJECT_NAME, PULPIT)
values ('S003', 'Art history', 'P001');

-- Создание роли, пользователя:

create pluggable database BANK_APP_PDB
  admin user admin identified by test1111
  roles = (dba)
  file_name_convert = (
      '/opt/oracle/oradata/XE/pdbseed',  
      '/opt/oracle/oradata/XE/BANK_APP_PDB'
  );

create bigfile tablespace users_tbs 
datafile 'users_tbs' size 100m autoextend on maxsize unlimited;

create temporary tablespace temp_tbs
tempfile 'temp_tbs' size 100m autoextend on maxsize unlimited;
DROP TABLESPACE temp_tbs INCLUDING CONTENTS AND DATAFILES;
ALTER SESSION SET CONTAINER = BANK_APP_PDB;
ALTER SESSION SET CONTAINER = CDB$ROOT;
ALTER pluggable DATABASE BANK_APP_PDB OPEN;

create profile admin_profile limit 
  sessions_per_user   unlimited 
  cpu_per_session     unlimited 
  cpu_per_call        unlimited 
  connect_time        unlimited 
  idle_time           unlimited 
  logical_reads_per_session default 
  logical_reads_per_call    default 
  private_sga        unlimited 
  composite_limit    unlimited; 
  
create role admin_role; 

create user admin_user identified by admin_password
    default tablespace users_tbs
    temporary tablespace temp_tbs
    profile admin_profile;

grant connect, resource, dba, admin_role to admin_user;

-- 1.	Создайте таблицу, имеющую несколько атрибутов, один из которых первичный ключ.

CREATE TABLE STUDENT (
	STUDENT varchar(20) PRIMARY KEY,
	STUDENT_NAME varchar (100) UNIQUE,
	PULPIT varchar(20),
	FOREIGN KEY (PULPIT) REFERENCES PULPIT (PULPIT) 
); 

SELECT * FROM STUDENT;

-- 2.	Заполните таблицу строками (10 шт.).
INSERT INTO STUDENT (STUDENT, STUDENT_NAME, PULPIT) values ('N001', 'Maxim Stanchik', 'P001'); 
INSERT INTO STUDENT (STUDENT, STUDENT_NAME, PULPIT) values ('N002', 'Ivan Ivanov', 'P001'); 
INSERT INTO STUDENT (STUDENT, STUDENT_NAME, PULPIT) values ('N003', 'Natasha Smirnova', 'P001'); 
INSERT INTO STUDENT (STUDENT, STUDENT_NAME, PULPIT) values ('N004', 'Denis Redis', 'P004'); 
INSERT INTO STUDENT (STUDENT, STUDENT_NAME, PULPIT) values ('N005', 'Alexey Sidorov', 'P004'); 
INSERT INTO STUDENT (STUDENT, STUDENT_NAME, PULPIT) values ('N006', 'Alexander Pavlov', 'P004'); 
INSERT INTO STUDENT (STUDENT, STUDENT_NAME, PULPIT) values ('N007', 'Sergey Kuznetsov', 'P005'); 
INSERT INTO STUDENT (STUDENT, STUDENT_NAME, PULPIT) values ('N008', 'Igor Ignatov', 'P005'); 
INSERT INTO STUDENT (STUDENT, STUDENT_NAME, PULPIT) values ('N009', 'Olga Morozova', 'P005'); 
INSERT INTO STUDENT (STUDENT, STUDENT_NAME, PULPIT) values ('N010', 'Petr Petrov', 'P005'); 

SELECT * FROM STUDENT;

-- 3.	Создайте BEFORE – триггер уровня оператора на события INSERT, DELETE и UPDATE. 

CREATE OR REPLACE TRIGGER trigger_task_3
	BEFORE INSERT OR DELETE OR UPDATE ON STUDENT
BEGIN
	dbms_output.put_line('Сработал триггер trigger_task_3 уровня оператора на события INSERT, DELETE и UPDATE ');		
END;
	
DROP TRIGGER trigger_task_3;

SELECT * FROM user_errors WHERE name = 'trigger_task_3' AND TYPE = 'TRIGGER';

-- Демонстрация 0:
INSERT INTO STUDENT (STUDENT, STUDENT_NAME, PULPIT)
VALUES ('S011', 'Super Student', 'P005');

UPDATE STUDENT SET STUDENT_NAME = 'Ne Student' WHERE STUDENT_NAME = 'Super Student';
UPDATE STUDENT SET STUDENT_NAME = 'Super Student' WHERE STUDENT_NAME = 'Ne Student';

DELETE FROM STUDENT WHERE PULPIT = 'Super Student';

-- Демонстрация 1:
INSERT INTO STUDENT (STUDENT, STUDENT_NAME, PULPIT)
VALUES ('S012', 'Super Student 1', 'P005');
INSERT INTO STUDENT (STUDENT, STUDENT_NAME, PULPIT)
VALUES ('S012', 'Super Student 2', 'P005');

UPDATE STUDENT SET STUDENT_NAME = 'Ne Student 1' WHERE STUDENT_NAME = 'Super Student 1';
UPDATE STUDENT SET STUDENT_NAME = 'Ne Student 2' WHERE STUDENT_NAME = 'Super Student 2';
UPDATE STUDENT SET STUDENT_NAME = 'Super Student 1' WHERE STUDENT_NAME = 'Ne Student 1';
UPDATE STUDENT SET STUDENT_NAME = 'Super Student 2' WHERE STUDENT_NAME = 'Ne Student 2';

DELETE FROM STUDENT WHERE PULPIT = 'Super Student 1';
DELETE FROM STUDENT WHERE PULPIT = 'Super Student 2';

-- 4.	Этот и все последующие триггеры должны выдавать сообщение на серверную консоль (DMS_OUTPUT) со своим собственным именем. 

-- 5.	Создайте BEFORE-триггер уровня строки на события INSERT, DELETE и UPDATE.

CREATE OR REPLACE TRIGGER trigger_task_5 
	BEFORE INSERT OR delete OR update 
	ON STUDENT
	FOR EACH ROW 
BEGIN 
	dbms_output.put_line('Сработал BEFORE-триггер trigger_task_5  уровня строки на события INSERT, DELETE и UPDATE');
END;

DROP TRIGGER trigger_task_5;

SELECT * 
FROM user_errors 
WHERE name = 'trigger_task_5' AND type = 'TRIGGER';

-- Демонстрация 1:
INSERT INTO STUDENT (STUDENT, STUDENT_NAME, PULPIT)
VALUES ('S012', 'Super Student 1', 'P005');
INSERT INTO STUDENT (STUDENT, STUDENT_NAME, PULPIT)
VALUES ('S014', 'Super Student 2', 'P005');

SELECT * FROM STUDENT;

UPDATE STUDENT SET STUDENT_NAME = 'Ne Student 1' WHERE STUDENT_NAME = 'Super Student 1';
UPDATE STUDENT SET STUDENT_NAME = 'Ne Student 2' WHERE STUDENT_NAME = 'Super Student 2';
UPDATE STUDENT SET STUDENT_NAME = 'Super Student 1' WHERE STUDENT_NAME = 'Ne Student 1';
UPDATE STUDENT SET STUDENT_NAME = 'Super Student 2' WHERE STUDENT_NAME = 'Ne Student 2';

DELETE FROM STUDENT WHERE STUDENT_NAME = 'Super Student 1';
DELETE FROM STUDENT WHERE STUDENT_NAME = 'Super Student 2';

-- 6.	Примените предикаты INSERTING, UPDATING и DELETING.

CREATE OR REPLACE TRIGGER trigger_task_6 
	BEFORE INSERT OR delete OR update 
	ON STUDENT
	FOR EACH ROW 
BEGIN 
	dbms_output.put_line('Сработал BEFORE-триггер trigger_task_6 уровня строки на события INSERT, DELETE и UPDATE');
IF inserting THEN
	dbms_output.put_line('Вставка данных');
elsif updating THEN
	dbms_output.put_line('Обновление данных');
ELSIF deleting THEN
	dbms_output.put_line('Удаление данных');
END IF;
END;

DROP TRIGGER trigger_task_6;

SELECT * 
FROM user_errors 
WHERE name = 'trigger_task_6' AND type = 'TRIGGER';

-- Демонстрация 1:
INSERT INTO STUDENT (STUDENT, STUDENT_NAME, PULPIT)
VALUES ('S012', 'Super Student 1', 'P005');
INSERT INTO STUDENT (STUDENT, STUDENT_NAME, PULPIT)
VALUES ('S014', 'Super Student 2', 'P005');

SELECT * FROM STUDENT;

UPDATE STUDENT SET STUDENT_NAME = 'Ne Student 1' WHERE STUDENT_NAME = 'Super Student 1';
UPDATE STUDENT SET STUDENT_NAME = 'Ne Student 2' WHERE STUDENT_NAME = 'Super Student 2';
UPDATE STUDENT SET STUDENT_NAME = 'Super Student 1' WHERE STUDENT_NAME = 'Ne Student 1';
UPDATE STUDENT SET STUDENT_NAME = 'Super Student 2' WHERE STUDENT_NAME = 'Ne Student 2';

DELETE FROM STUDENT WHERE STUDENT_NAME = 'Super Student 1';
DELETE FROM STUDENT WHERE STUDENT_NAME = 'Super Student 2';

-- 7.	Разработайте AFTER-триггеры уровня оператора на события INSERT, DELETE и UPDATE.

CREATE OR REPLACE TRIGGER trigger_task_7 
	AFTER INSERT OR delete OR update 
	ON STUDENT
BEGIN 
	dbms_output.put_line('Сработал AFTER-триггер trigger_task_7  уровня строки на события INSERT, DELETE и UPDATE');
END;

DROP TRIGGER trigger_task_7;

SELECT * 
FROM user_errors 
WHERE name = 'trigger_task_7' AND type = 'TRIGGER';

-- 8.	Разработайте AFTER-триггеры уровня строки на события INSERT, DELETE и UPDATE.

CREATE OR REPLACE TRIGGER trigger_task_8 
	AFTER INSERT OR delete OR update 
	ON STUDENT
	FOR EACH ROW 
BEGIN 
	dbms_output.put_line('Сработал AFTER-триггер  trigger_task_8  уровня строки на события INSERT, DELETE и UPDATE');
END;

DROP TRIGGER trigger_task_8;

SELECT * 
FROM user_errors 
WHERE name = 'trigger_task_8' AND type = 'TRIGGER';

-- 9.	Создайте таблицу с именем AUDIT. Таблица должна содержать поля: OperationDate, 
-- OperationType (операция вставки, обновления и удаления),
-- TriggerName(имя триггера),
-- Data (строка с значениями полей до и после операции).

create table AUDIT_LOG
(
  OperationDate date,
  OperationType varchar(100),
  TriggerName   varchar(100)
);

-- 10.	Измените триггеры таким образом, чтобы они регистрировали все операции с исходной таблицей в таблице AUDIT.

DROP TRIGGER trigger_task_3;
DROP TRIGGER trigger_task_5;
DROP TRIGGER trigger_task_6;
DROP TRIGGER trigger_task_7;
DROP TRIGGER trigger_task_8;

CREATE OR REPLACE TRIGGER trigger_task_3
	BEFORE INSERT OR DELETE OR UPDATE ON STUDENT
BEGIN
	INSERT INTO AUDIT_LOG(OperationDate, OperationType, TriggerName) VALUES (sysdate, 'Вставка/обновление/удаление', 'trigger_task_3');
	dbms_output.put_line('Сработал BEFORE триггер trigger_task_3 уровня оператора на события INSERT, DELETE и UPDATE');		
END;

CREATE OR REPLACE TRIGGER trigger_task_5 
	BEFORE INSERT OR delete OR update 
	ON STUDENT
	FOR EACH ROW 
BEGIN 
	INSERT INTO AUDIT_LOG(OperationDate, OperationType, TriggerName) VALUES (sysdate, 'Вставка/обновление/удаление', 'trigger_task_5');
	dbms_output.put_line('Сработал BEFORE-триггер  trigger_task_5 уровня строки на события INSERT, DELETE и UPDATE');
END;

CREATE OR REPLACE TRIGGER trigger_task_6 
	BEFORE INSERT OR delete OR update 
	ON STUDENT
	FOR EACH ROW 
BEGIN 
	dbms_output.put_line('Сработал BEFORE-триггер  trigger_task_6 уровня строки на события INSERT, DELETE и UPDATE');
IF inserting THEN
	INSERT INTO AUDIT_LOG(OperationDate, OperationType, TriggerName) VALUES (sysdate, 'Вставка', 'trigger_task_6');
	dbms_output.put_line('Вставка данных');
elsif updating THEN
	INSERT INTO AUDIT_LOG(OperationDate, OperationType, TriggerName) VALUES (sysdate, 'Обновление', 'trigger_task_6');
	dbms_output.put_line('Обновление данных');
ELSIF deleting THEN
	INSERT INTO AUDIT_LOG(OperationDate, OperationType, TriggerName) VALUES (sysdate, 'Удаление', 'trigger_task_6');
	dbms_output.put_line('Удаление данных');
END IF;
END;

CREATE OR REPLACE TRIGGER trigger_task_7 
	AFTER INSERT OR delete OR update 
	ON STUDENT
BEGIN 
	INSERT INTO AUDIT_LOG(OperationDate, OperationType, TriggerName) VALUES (sysdate, 'Вставка/обновление/удаление', 'trigger_task_7');
	dbms_output.put_line('Сработал AFTER-триггер  trigger_task_7 уровня строки на события INSERT, DELETE и UPDATE');
END;

CREATE OR REPLACE TRIGGER trigger_task_8 
	AFTER INSERT OR delete OR update 
	ON STUDENT
	FOR EACH ROW 
BEGIN 
	INSERT INTO AUDIT_LOG(OperationDate, OperationType, TriggerName) VALUES (sysdate, 'Вставка/обновление/удаление', 'trigger_task_8');
	dbms_output.put_line('Сработал AFTER-триггер  trigger_task_8 уровня строки на события INSERT, DELETE и UPDATE');
END;

-- 11.	Выполните операцию, нарушающую целостность таблицы по первичному ключу. Выясните, зарегистрировал ли триггер это событие. Объясните результат.
SELECT * FROM AUDIT_LOG;
INSERT INTO STUDENT (STUDENT, STUDENT_NAME, PULPIT) values ('N090', 'Maxim Stanchik 0', 'P001');
INSERT INTO STUDENT (STUDENT, STUDENT_NAME, PULPIT) values ('N001', 'Maxim Stanchik', 'P001');

 -- триггеры не сработают. Это происходит потому, что при возникновении ошибки операция не завершится успешно, и все действия, включая выполнение триггеров, будут отменены.

-- 12.	Удалите (drop) исходную таблицу. Объясните результат. Добавьте триггер, запрещающий удаление исходной таблицы.

drop table STUDENT;
select * from STUDENT;

create or replace trigger BEFORE_DROP
  before drop ON SYSTEM.SCHEMA
BEGIN
	dbms_output.put_line('Сработал BEFORE-триггер BEFORE_DROP уровня оператора на событие удаления таблицы STUDENT');
  if ORA_DICT_OBJ_NAME <> 'STUDENT' then
    return;
  end if;

  raise_application_error(-20001, 'Нельзя удалять таблицу STUDENT');
end;


-- 13.	Удалите (drop) таблицу AUDIT. Просмотрите состояние триггеров с помощью SQL-DEVELOPER. Объясните результат. Измените триггеры.

DROP TABLE AUDIT_LOG;

SELECT TRIGGER_NAME, TRIGGER_TYPE, TRIGGERING_EVENT, STATUS FROM USER_TRIGGERS;

-- 14.	Создайте представление над исходной таблицей. Разработайте INSTEADOF INSERT-триггер. Триггер должен добавлять строку в таблицу.

INSERT INTO STUDENT_VIEW (STUDENT, STUDENT_NAME, PULPIT) values ('N027', 'Maxim Stanchik 16', 'P001');

create view STUDENT_VIEW AS select * from STUDENT;

CREATE OR REPLACE TRIGGER trigger_task_14
INSTEAD OF INSERT ON STUDENT_VIEW
FOR EACH ROW
BEGIN
    dbms_output.put_line('Сработал INSTEAD OF триггер trigger_task_14 уровня оператора строки');
    INSERT INTO AUDIT_LOG(OperationDate, OperationType, TriggerName) VALUES (SYSDATE, 'Вставка/обновление/удаление', 'trigger_task_14');
    INSERT INTO STUDENT (STUDENT, STUDENT_NAME, PULPIT) VALUES (:new.STUDENT, :new.STUDENT_NAME, :new.PULPIT);
END;

SELECT * FROM USER_ERRORS WHERE NAME = 'TRIGGER_TASK_14';

SELECT * FROM STUDENT_VIEW;

select * from STUDENT;
select * from AUDIT_LOG;

-- 15.	Продемонстрируйте, в каком порядке выполняются триггеры.
