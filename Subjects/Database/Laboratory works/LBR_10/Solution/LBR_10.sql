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

create table PULPIT (
  PULPIT varchar(20) primary key,
  PULPIT_NAME varchar(100) unique,
  FACULTY varchar(20),
  foreign key (FACULTY) references FACULTY(FACULTY)
);

create table TEACHER (
  TEACHER varchar(20) primary key,
  TEACHER_NAME varchar(100) unique,
  PULPIT varchar(20),
  foreign key (PULPIT) references PULPIT(PULPIT)
);

create table SUBJECT (
  SUBJECT varchar(20) primary key,
  SUBJECT_NAME varchar(100) unique,
  PULPIT varchar(20),
  foreign key (PULPIT) references PULPIT(PULPIT)
);

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

-- 1. Добавьте в таблицу TEACHERS два столбца BIRTHDAYи SALARY, заполните их значениями.
alter table teacher add (BIRTHDAY date, SALARY number);

update teacher
set 
    BIRTHDAY = trunc(SYSDATE) - rownum * 365, 
    SALARY = 30000 + rownum * 1000;

alter table teacher drop column BIRTHDAY;
alter table teacher drop column SALARY;

select * from teacher;

-- 2. Получите список преподавателей в виде Фамилия И.О.
create or replace function GET_FIO(TEACHER_NAME varchar2)
	return varchar2
is
    fio varchar2(200);
begin
    fio := substr(TEACHER_NAME, 1, instr(TEACHER_NAME, ' ') - 1) || ' ' ||
                substr(TEACHER_NAME, instr(TEACHER_NAME, ' ') + 1, 1) || '.' ||
                substr(TEACHER_NAME, instr(TEACHER_NAME, ' ', 1, 2) + 1, 1) || '.';

    return fio;
end;

select GET_FIO(TEACHER_NAME) from TEACHER;

-- 3. Получите список преподавателей, родившихся в понедельник.
update TEACHER set BIRTHDAY = '30.12.2024' where SALARY = 33000;

select TEACHER_NAME, BIRTHDAY from TEACHER where to_char(BIRTHDAY, 'D') = '1';

SELECT * FROM teacher;

-- 4. Создайте представление, в котором поместите список преподавателей, которые родились в следующем месяце.

CREATE OR REPLACE VIEW TEACHERS_NEXT_MONTH AS
SELECT GET_FIO(TEACHER_NAME) AS TEACHER_NAME,
       TO_CHAR(BIRTHDAY, 'DD.MM.YYYY') AS BIRTHDAY
FROM teacher
WHERE EXTRACT(MONTH FROM BIRTHDAY) = MOD(EXTRACT(MONTH FROM SYSDATE), 12) + 1;

select * from TEACHERS_NEXT_MONTH;
select * from TEACHER;

-- 5. Создайте представление, в котором поместите количество преподавателей, которые родились в каждом месяце.
drop table MONTHS;

create table MONTHS
(
  month_name   varchar(20),
  month_number varchar(2)
);

insert into MONTHS (month_name, month_number)
values ('Январь', '01');
insert into MONTHS (month_name, month_number)
values ('Февраль', '02');
insert into MONTHS (month_name, month_number)
values ('Март', '03');
insert into MONTHS (month_name, month_number)
values ('Апрель', '04');
insert into MONTHS (month_name, month_number)
values ('Май', '05');
insert into MONTHS (month_name, month_number)
values ('Июнь', '06');
insert into MONTHS (month_name, month_number)
values ('Июль', '07');
insert into MONTHS (month_name, month_number)
values ('Август', '08');
insert into MONTHS (month_name, month_number)
values ('Сентябрь', '09');
insert into MONTHS (month_name, month_number)
values ('Октябрь', '10');
insert into MONTHS (month_name, month_number)
values ('Ноябрь', '11');
insert into MONTHS (month_name, month_number)
values ('Декабрь', '12');

create or replace view TEACHER_COUNT_BY_MONTH as
select month_name,
       (select count(*) from TEACHER where to_char(birthday, 'MM') = month_number) as count
from MONTHS;

select * from TEACHER_COUNT_BY_MONTH;
select SUM(COUNT) from TEACHER_COUNT_BY_MONTH;
select COUNT(*) from TEACHER;

-- 6. Создать курсор и вывести список преподавателей, у которых в следующем году юбилей.
SELECT GET_FIO(TEACHER_NAME) AS teacher_name, 
       TO_CHAR(BIRTHDAY, 'DD.MM.YYYY') AS birthday
FROM TEACHER;

SET SERVEROUTPUT ON; 
DECLARE
  CURSOR c1 IS
    SELECT GET_FIO(TEACHER_NAME) AS teacher_name,
           TO_CHAR(BIRTHDAY, 'DD.MM.YYYY') AS birthday
    FROM TEACHER
    WHERE MOD((EXTRACT(YEAR FROM BIRTHDAY) + 1 - EXTRACT(YEAR FROM SYSDATE)), 10) = 0
      AND EXTRACT(MONTH FROM BIRTHDAY) = EXTRACT(MONTH FROM SYSDATE); 
BEGIN
  FOR i IN c1 LOOP
    DBMS_OUTPUT.PUT_LINE(i.teacher_name || ' ' || i.birthday);
  END LOOP;
END;

-- 7. Создать курсор и вывести среднюю заработную плату по кафедрам с округлением вниз до целых, 
-- вывести средние итоговые значения для каждого факультета и для всех факультетов в целом.
select * from TEACHER;
select * from FACULTY;

DECLARE
  CURSOR c_average_salary IS
    SELECT P.FACULTY, AVG(T.SALARY) AS AVERAGE_SALARY
    FROM TEACHER T
    INNER JOIN PULPIT P ON T.PULPIT = P.PULPIT
    GROUP BY P.FACULTY;

  v_faculty CHAR(20);
  v_average_salary NUMBER; 
  v_count_faculty NUMBER;
  v_total_average_salary NUMBER := 0;
  v_average_salary_all_faculty NUMBER;
BEGIN
  OPEN c_average_salary;
  
  DBMS_OUTPUT.PUT_LINE('Average Salary by Faculty:');
  DBMS_OUTPUT.PUT_LINE('---------------------------------------------------------------------------');
  
  LOOP
    FETCH c_average_salary INTO v_faculty, v_average_salary;
    EXIT WHEN c_average_salary%NOTFOUND;
    
    SELECT COUNT(*) INTO v_count_faculty FROM FACULTY;
    v_total_average_salary := v_total_average_salary + v_average_salary;
    v_average_salary_all_faculty := v_total_average_salary / v_count_faculty;
    
    DBMS_OUTPUT.PUT_LINE('Faculty: ' || v_faculty || 'Average Salary: ' || FLOOR(v_average_salary));
  END LOOP;
  
  DBMS_OUTPUT.PUT_LINE('---------------------------------------------------------------------------');
  DBMS_OUTPUT.PUT_LINE('Total: ' || FLOOR(v_total_average_salary));
  DBMS_OUTPUT.PUT_LINE('Total Average Salary: ' || FLOOR(v_average_salary_all_faculty));
  
  CLOSE c_average_salary;
END;

-- 8. Создайте собственный тип PL/SQL-записи (record) и продемонстрируйте работу с ним.
-- Продемонстрируйте работу с вложенными записями. Продемонстрируйте и объясните операцию присвоения.
select * from TEACHER;

DECLARE
  TYPE TEACHER_RECORD IS RECORD (
    teacher VARCHAR2(20),
    teacher_name VARCHAR2(200),
    pulpit CHAR(20)
  );

  TYPE SUBJECT_RECORD IS RECORD (
    subject_name VARCHAR2(100),
    credits NUMBER
    
  );

  TYPE SUBJECT_ARRAY IS TABLE OF SUBJECT_RECORD;

  TYPE MAIN_RECORD IS RECORD (
    teacher_info TEACHER_RECORD,
    subjects SUBJECT_ARRAY
  );

  main_rec MAIN_RECORD;
BEGIN
  main_rec.teacher_info.teacher := 'СМЛВ';
  main_rec.teacher_info.teacher_name := 'Игорев Игорь Игоревич';
  main_rec.teacher_info.pulpit := 'ИСиТ';

  main_rec.subjects := SUBJECT_ARRAY();
  main_rec.subjects.EXTEND(2);

  main_rec.subjects(1) := SUBJECT_RECORD('Программирование', 5);
  main_rec.subjects(2) := SUBJECT_RECORD('Базы данных', 4);

  DBMS_OUTPUT.PUT_LINE('Teacher: ' || main_rec.teacher_info.teacher);
  DBMS_OUTPUT.PUT_LINE('Teacher Name: ' || main_rec.teacher_info.teacher_name);
  DBMS_OUTPUT.PUT_LINE('Pulpit: ' || main_rec.teacher_info.pulpit);

  FOR i IN 1..main_rec.subjects.COUNT LOOP
    DBMS_OUTPUT.PUT_LINE('Subject: ' || main_rec.subjects(i).subject_name || 
                         ', Credits: ' || main_rec.subjects(i).credits);
  END LOOP;
END;