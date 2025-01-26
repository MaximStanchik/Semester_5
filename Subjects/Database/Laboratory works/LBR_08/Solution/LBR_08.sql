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
	VALUES ('P005', 'Department of Arts', 'F005');

	insert into teacher (TEACHER, TEACHER_NAME, PULPIT)
	values ('T001', 'Ivan Ivanov', 'P001');
	insert into teacher (TEACHER, TEACHER_NAME, PULPIT)
	values ('T002', 'Petr Petrov', 'P001');
	insert into teacher (TEACHER, TEACHER_NAME, PULPIT)
	values ('T003', 'Maria Ivanovna', 'P001');


	insert into subject (SUBJECT, SUBJECT_NAME, PULPIT)
	values ('S001', 'Programming', 'P001');
	insert into subject (SUBJECT, SUBJECT_NAME, PULPIT)
	values ('S002', 'Biology', 'P001');
	insert into subject (SUBJECT, SUBJECT_NAME, PULPIT)
	values ('S003', 'Art history', 'P001');

-- 1.	Разработайте простейший анонимный блок PL/SQL (АБ), не содержащий операторов. 
        begin
        null;
    end;
-- 2.	Разработайте АБ, выводящий «Hello World!». Выполните его в SQLDev и SQL+.
    set serveroutput on;
    begin
        dbms_output.put_line('Hello World!');
    end;
-- 3.	Продемонстрируйте работу исключения и встроенных функций sqlerrm, sqlcode.
    declare
        new_number number;
    begin
        new_number := 1/0;
    exception
        when others then
            dbms_output.put_line('Error: ' || sqlerrm);
            dbms_output.put_line('Error code: ' || sqlcode);
        end;
-- 4.	Разработайте вложенный блок. Продемонстрируйте принцип обработки исключений во вложенных блоках.
    set serveroutput on;
    declare
    outer_number number;
begin
    begin
        -- Попытка деления на ноль
        declare
            inner_number number;
        begin
            inner_number := 1 / 0; -- Это вызовет исключение ZERO_DIVIDE
        exception
            when ZERO_DIVIDE then
                dbms_output.put_line('Inner Block Error: ' || sqlerrm);
                dbms_output.put_line('Inner Block Error Code: ' || sqlcode);
                raise;
        end;
    exception
        when others then
            dbms_output.put_line('Outer Block Error: ' || sqlerrm);
            dbms_output.put_line('Outer Block Error Code: ' || sqlcode);
    end;
end;
-- 5.	Выясните, какие типы предупреждения компилятора поддерживаются в данный момент.
    select value, type from v$parameter where name = 'plsql_warnings'; 
    select * from ALL_ERRORS where type in ('PACKAGE', 'PACKAGE BODY', 'PROCEDURE', 'FUNCTION');
    select * from USER_ERRORS where type in ('PACKAGE', 'PACKAGE BODY', 'PROCEDURE', 'FUNCTION');
-- 6.	Разработайте скрипт, позволяющий просмотреть все спецсимволы PL/SQL.
    select * from v_$reserved_words where length = 1;
-- 7.	Разработайте скрипт, позволяющий просмотреть все ключевые слова  PL/SQL.
    select * from v_$reserved_words;
-- 8.	Разработайте скрипт, позволяющий просмотреть все параметры Oracle Server, связанные с PL/SQL. Просмотрите эти же параметры с помощью SQL+-команды show.
    select * from v_$parameter where name like '%plsql%';
-- 9.	Разработайте анонимный блок, демонстрирующий (выводящий в выходной серверный поток результаты):
-- 10.	объявление и инициализацию целых number-переменных;
    set serveroutput on;
    declare 
        first_number number := 10;
        second_number number := 30;
    begin
        dbms_output.put_line('Первая целочисленная перменная: ' || first_number);
        dbms_output.put_line('Вторая целочисленная переменная: ' || second_number);
    end;
-- 11.	арифметические действия над двумя целыми number-переменных, включая деление с остатком;
    set serveroutput on;
    declare 
        first_number number := 20;
        second_number number := 11;
    begin
        dbms_output.put_line(first_number + second_number);
        dbms_output.put_line(first_number - second_number);
        dbms_output.put_line(first_number * second_number);
        dbms_output.put_line(first_number / second_number);
        dbms_output.put_line(first_number mod second_number);
    end;
-- 12.	объявление и инициализацию number-переменных с фиксированной точкой;
    set serveroutput on;
    declare
        first_number number := 1.1;
        second_number number(3,1) := 99.1; ---!!!!!!!!!!!!!!!!!!
    begin
        dbms_output.put_line('Первая переменная: ' || first_number);
        dbms_output.put_line('Вторая переменная: ' || second_number);
    end;
-- 13.	объявление и инициализацию number-переменных с фиксированной точкой и отрицательным масштабом (округление);
    set serveroutput on;
    declare
        first_number number := 1.1;
        second_number number (15, -5) := 2456782.6;  
    begin
        dbms_output.put_line('Первая переменная: ' || first_number);
        dbms_output.put_line('Вторая переменная: ' || second_number);
    end;
-- 14.	объявление и инициализацию BINARY_FLOAT-переменной;
    declare
        numberVar binary_float := 1.1;
    begin
        dbms_output.put_line(numberVar);
    end;
-- 15.	объявление и инициализацию BINARY_DOUBLE-переменной;
    declare
        numberVar binary_double := 1.1;
    begin
        dbms_output.put_line(numberVar);
    end;
-- 16.	объявление number-переменных с точкой и применением символа E (степень 10) при инициализации/присвоении;
    declare
        firstNumber number := 1.1E1;
        secondNumber number := 1.1E-1;
        thirdNumber number := firstNumber + secondNumber;
    begin
        DBMS_OUTPUT.PUT_LINE(firstNumber);
        DBMS_OUTPUT.PUT_LINE(secondNumber);
        DBMS_OUTPUT.PUT_LINE(thirdNumber);
    end;
-- 17.	объявление и инициализацию BOOLEAN-переменных. 
    declare
        v_bool BOOLEAN := TRUE;
    begin
        IF v_bool THEN
            dbms_output.put_line('true');
        ELSE
            dbms_output.put_line('false');
        END IF;
    end;
-- 18.	Разработайте анонимный блок PL/SQL содержащий объявление констант (VARCHAR2, CHAR, NUMBER). Продемонстрируйте  возможные операции константами.  
    set serveroutput on;
    declare
        vchar_const constant varchar2(20) := 'VCHAR_CONST';
        char_const constant char(20) := 'CHAR_CONST';
        number_const constant number := 10;  
    begin   
        dbms_output.put_line('vchar_const: ' || vchar_const);
        dbms_output.put_line('char_const: ' || char_const);
        dbms_output.put_line('number_const: ' || number_const);
    
        dbms_output.put_line('number_const * 2 = ' || number_const * 2);
        dbms_output.put_line('Конкатенация VCHAR_CONST и CHAR_CONST: ' || (vchar_const || ' ' || char_const));
    
        dbms_output.put_line('Длина vchar_const: ' || length(vchar_const));
        dbms_output.put_line('Длина char_const: ' || length(char_const));
    end;
-- 19.	Разработайте АБ, содержащий объявления с опцией %TYPE. Продемонстрируйте действие опции.
    set serveroutput on;
    declare
        vchar_const constant varchar2(20) := 'vchar_const';
        char_const constant char(20) := 'char_const';
        number_const constant number := 1;
        vchar_const2 vchar_const%type := 'vchar_const2';
        char_const2 char_const%type := 'char_const2';
        number_const2 number_const%type := 2;
    begin
        dbms_output.put_line(vchar_const2);
        dbms_output.put_line(char_const2);
        dbms_output.put_line(number_const2);
    end;
-- 20.	Разработайте АБ, содержащий объявления с опцией %ROWTYPE. Продемонстрируйте действие опции.

set serveroutput on;
declare
    auditorium_type_row auditorium_type%rowtype;
begin
    auditorium_type_row.audiotrium_typename := 'auditorium';
    auditorium_type_row.auditorium_type := 'auditorium';

    dbms_output.put_line(AUDITORIUM_TYPE_ROW.AUDITORIUM_TYPE);
    dbms_output.put_line(AUDITORIUM_TYPE_ROW.AUDIOTRIUM_TYPENAME);
end;
-- 21.	Разработайте АБ, демонстрирующий все возможные конструкции оператора IF .
declare
		v_num number := 1;
		begin
		if v_num = 1 then
		dbms_output.put_line('v_num = 1');
		elsif v_num = 2 then
		dbms_output.put_line('v_num = 2');
		elsif v_num is null then
		dbms_output.put_line('v_num is null');
		else
		dbms_output.put_line('v_num = 3');
		end if;
		end;
-- 22.	Разработайте АБ, демонстрирующий все возможные конструкции оператора IF .
    set serveroutput on;
    declare
        var_number number := 10;
        var_message varchar2(100);
    begin
        if v_number > 0 then
            v_message := 'Число положительное';
        end if;
        
        if v_number < 0 THEN
            v_message := 'Число отрицательное';
        else
            v_message := 'Число не отрицательное';
        end if;
        
        if v_number > 0 then
            v_message := 'Число положительное';
        elsif v_number = 0 then
            v_message := 'Число равно нулю';
        else
            v_message := 'Число отрицательное';
        end if;
        
        if v_number is not null then
        if v_number > 0 then
            v_message := 'Число положительное и не NULL';
        else
            v_message := 'Число не положительное и не NULL';
        end if;
    else
        v_message := 'Число равно NULL';
    end if;
        dbms_output.put_line(v_message);
    end;
-- 23.	Разработайте АБ, демонстрирующий работу оператора CASE.

    set serveroutput on;
    declare
        numValue number := 1;
    begin
        case numValue
            when 1 then
                dbms_output.put_line('numValue = 1');
            when 2 then
                dbms_output.put_line('numValue = 2');
            when 3 then
                dbms_output.put_line('numValue = 3');
            else
                dbms_output.put_line('numValue is null');
        end case;
    end;
    
-- 24.	Разработайте АБ, демонстрирующий работу оператора LOOP.

    set serveroutput on;
    declare
		v_num number := 1;
    begin
		loop
            dbms_output.put_line(v_num);
            v_num := v_num + 1;
            exit when v_num > 10;
		end loop;
    end;
    
-- 25.	Разработайте АБ, демонстрирующий работу оператора WHILE.

    set serveroutput on;
    declare 
        numValue number := 1;
    begin
        while numValue <= 10 loop
            dbms_output.put_line(numValue);
            numValue := numValue + 1;
        end loop;
    end;
        
-- 26.	Разработайте АБ, демонстрирующий работу оператора FOR.

    set serveroutput on;
    begin
        for i in 1..10 loop
            dbms_output.put_line(i);
        end loop;
    end;


    number (9, -2) = xxxxxxx,xx 0,00999999999
    number (9, 11) = 0,00xxxxxxxxx 
    number (9, -11) = 99999999900000000000,
    
    