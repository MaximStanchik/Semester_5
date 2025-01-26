ALTER SESSION SET CONTAINER = XEPDB1;

create table AUDITORIUM_TYPE (
  AUDITORIUM_TYPE varchar(20) primary key,
  AUDIOTRIUM_TYPENAME varchar(100) unique
);

SELECT * FROM AUDITORIUM_TYPE;

create table AUDITORIUM (
  AUDITORIUM varchar(20) primary key,
  AUDITORIUM_NAME varchar(100) unique,
  AUDITORIUM_CAPACITY int,
  AUDITORIUM_TYPE varchar(20),
  foreign key (AUDITORIUM_TYPE) references AUDITORIUM_TYPE(AUDITORIUM_TYPE)
);

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

SELECT * FROM AUDITORIUM_TYPE;
----------------------------------------Неявные курсоры----------------------------------------
-- 1. Разработайте АБ, демонстрирующий работу оператора SELECT с точной выборкой 
    select * from FACULTY where FACULTY.FACULTY = 'F001';
  
    declare 
        AUDITORIUM_TYPE_var AUDITORIUM_TYPE.AUDITORIUM_TYPE%TYPE;
        AUDIOTRIUM_TYPENAME_var AUDITORIUM_TYPE.AUDIOTRIUM_TYPENAME%TYPE; 
    begin
        select AUDITORIUM_TYPE, AUDIOTRIUM_TYPENAME 
        into AUDITORIUM_TYPE_var, AUDIOTRIUM_TYPENAME_var 
        from AUDITORIUM_TYPE 
        where AUDITORIUM_TYPE = 'Lecture';

    DBMS_OUTPUT.PUT_LINE('Тип аудитории: ' || AUDITORIUM_TYPE_var);
    DBMS_OUTPUT.PUT_LINE('Название типа аудитории: ' || AUDIOTRIUM_TYPENAME_var);
  
    exception
        when NO_DATA_FOUND then
            dbms_output.put_line('Нет данных, удовлетворяющих условию.');
        when TOO_MANY_ROWS then
            dbms_output.put_line('Ошибка: найдено слишком много строк.');
    end;
   
-- 2. Разработайте АБ, демонстрирующий работу оператора SELECT с неточной точной выборкой. �?спользуйте конструкцию WHEN OTHERS секции исключений и встроенную функции SQLERRM, SQLCODE для диагностирования неточной выборки 
    declare
        facultyID FACULTY.FACULTY%TYPE;
        facultyName FACULTY.FACULTY_NAME%TYPE;
    begin

        select FACULTY, FACULTY_NAME into facultyID, facultyName from FACULTY where FACULTY like 'F001';

        dbms_output.put_line('ID FACULTY: ' || facultyID || ', NAME FACULTY: ' || facultyName);

        exception
            when others then
                dbms_output.put_line('Ошибка: ' || SQLCODE || ' ' || SQLERRM);
    end;
-- 3. Разработайте АБ, демонстрирующий работу конструкции WHEN TO_MANY_ROWS секции исключений для диагностирования неточной выборки 
set serveroutput on;
declare 
        AUDITORIUM_TYPE_var AUDITORIUM_TYPE.AUDITORIUM_TYPE%TYPE;
        AUDIOTRIUM_TYPENAME_var AUDITORIUM_TYPE.AUDIOTRIUM_TYPENAME%TYPE; 
    begin
        select AUDITORIUM_TYPE, AUDIOTRIUM_TYPENAME 
        into AUDITORIUM_TYPE_var, AUDIOTRIUM_TYPENAME_var 
        from AUDITORIUM_TYPE 
        where AUDITORIUM_TYPE != 'Lecture';

    DBMS_OUTPUT.PUT_LINE('Тип аудитории: ' || AUDITORIUM_TYPE_var);
    DBMS_OUTPUT.PUT_LINE('Название типа аудитории: ' || AUDIOTRIUM_TYPENAME_var);
  
    exception
        when NO_DATA_FOUND then
            dbms_output.put_line('Ошибка: данные не найдены.');
        when TOO_MANY_ROWS then
            dbms_output.put_line('Ошибка: найдено слишком много строк.');
    end;
-- 4. Разработайте АБ, демонстрирующий возникновение и обработку исключения NO_DATA_FOUND. Разработайте АБ, демонстрирующий применение атрибутов неявного курсора

DECLARE
    v_AUDITORIUM          AUDITORIUM.AUDITORIUM%TYPE; 
    v_AUDITORIUM_NAME     AUDITORIUM.AUDITORIUM_NAME%TYPE; 
    v_AUDITORIUM_CAPACITY AUDITORIUM.AUDITORIUM_CAPACITY%TYPE; 
BEGIN
    SELECT AUDITORIUM, AUDITORIUM_NAME, AUDITORIUM_CAPACITY 
    INTO v_AUDITORIUM, v_AUDITORIUM_NAME, v_AUDITORIUM_CAPACITY 
    FROM AUDITORIUM 
    WHERE AUDITORIUM_TYPE = 'ACDSCSDCSDCSDCSDDDDDDDDDDDDDDDDDDDDDDDDDDDD';

    DBMS_OUTPUT.PUT_LINE('AUDITORIUM: ' || v_AUDITORIUM || 
                         ', AUDITORIUM_NAME: ' || v_AUDITORIUM_NAME || 
                         ', AUDITORIUM_CAPACITY: ' || v_AUDITORIUM_CAPACITY);

    DBMS_OUTPUT.PUT_LINE('Количество затронутых строк: ' || SQL%ROWCOUNT);

EXCEPTION
    WHEN NO_DATA_FOUND THEN
        DBMS_OUTPUT.PUT_LINE('Ошибка: NO_DATA_FOUND. Данные не найдены.');

    WHEN OTHERS THEN
        DBMS_OUTPUT.PUT_LINE('Ошибка: ' || SQLCODE || ' ' || SQLERRM);
END;

-- 5. Разработайте АБ, демонстрирующий применение оператора UPDATE совместно с операторами COMMIT/ROLLBACK
DECLARE
  v_CAPACITY AUDITORIUM.AUDITORIUM_CAPACITY%TYPE;
BEGIN
  UPDATE AUDITORIUM
  SET AUDITORIUM_NAME = 'Auditory 1'
  WHERE AUDITORIUM = 'A1'
  RETURNING AUDITORIUM_CAPACITY INTO v_CAPACITY;

  IF v_CAPACITY <> 100 THEN
    DBMS_OUTPUT.PUT_LINE('Обновление прошло успешно. Вместимость: ' || v_CAPACITY);
    COMMIT;
  ELSE
    DBMS_OUTPUT.PUT_LINE('Обновление не выполнено, так как вместимость равна 100.');
    ROLLBACK;
  END IF;
END;

-- 6. Продемонстрируйте оператор UPDATE, вызывающий нарушение целостности в базе данных. Обработайте возникшее исключение
set serveroutput on;
declare
begin
  update AUDITORIUM
  set AUDITORIUM = 'Обновленная аудитория с очень длинным названием, превышающим допустимую длину'
  where AUDITORIUM = 'A101';

exception
  when others then
    dbms_output.put_line('Ошибка: ' || SQLCODE || ' ' || SQLERRM);
    rollback;
end;

-- 7. Разработайте АБ, демонстрирующий применение оператора INSERT совместно с операторами COMMIT/ROLLBACK
DECLARE
  v_AUDITORIUM          AUDITORIUM.AUDITORIUM%TYPE;
  v_AUDITORIUM_NAME     AUDITORIUM.AUDITORIUM_NAME%TYPE;
  v_AUDITORIUM_CAPACITY AUDITORIUM.AUDITORIUM_CAPACITY%TYPE;
BEGIN
  INSERT INTO AUDITORIUM (AUDITORIUM, AUDITORIUM_NAME, AUDITORIUM_CAPACITY, AUDITORIUM_TYPE)
  VALUES ('A1', 'Аудитория 1', 100, 'Auditorium')
  RETURNING AUDITORIUM, AUDITORIUM_NAME, AUDITORIUM_CAPACITY
      INTO v_AUDITORIUM, v_AUDITORIUM_NAME, v_AUDITORIUM_CAPACITY;

  DBMS_OUTPUT.PUT_LINE('AUDITORIUM: ' || v_AUDITORIUM || ', AUDITORIUM_NAME: ' || v_AUDITORIUM_NAME ||
                       ', AUDITORIUM_CAPACITY: ' || v_AUDITORIUM_CAPACITY);
  COMMIT;

  INSERT INTO AUDITORIUM (AUDITORIUM, AUDITORIUM_NAME, AUDITORIUM_CAPACITY, AUDITORIUM_TYPE)
  VALUES ('A2', 'Аудитория 2', 100, 'Auditorium')
  RETURNING AUDITORIUM, AUDITORIUM_NAME, AUDITORIUM_CAPACITY INTO v_AUDITORIUM, v_AUDITORIUM_NAME, v_AUDITORIUM_CAPACITY;

  DBMS_OUTPUT.PUT_LINE('AUDITORIUM: ' || v_AUDITORIUM || ', AUDITORIUM_NAME: ' || v_AUDITORIUM_NAME ||
                       ', AUDITORIUM_CAPACITY: ' || v_AUDITORIUM_CAPACITY);

  ROLLBACK;

EXCEPTION
  WHEN OTHERS THEN
    DBMS_OUTPUT.PUT_LINE('Ошибка: ' || SQLCODE || ' ' || SQLERRM);
    ROLLBACK;
end;

select * from AUDITORIUM;

-- 8. Продемонстрируйте оператор INSERT, вызывающий нарушение целостности в базе данных. Обработайте возникшее исключение
DECLARE
BEGIN
  INSERT INTO AUDITORIUM (AUDITORIUM, AUDITORIUM_NAME, AUDITORIUM_CAPACITY, AUDITORIUM_TYPE)
  VALUES ('A1', 'Аудитория 1', 100, 'Auditorium');
EXCEPTION
  WHEN OTHERS THEN
    DBMS_OUTPUT.PUT_LINE('Ошибка: ' || SQLCODE || ' ' || SQLERRM);
    ROLLBACK;
end;

-- 9. Разработайте АБ, демонстрирующий применение оператора DELETE совместно с операторами COMMIT/ROLLBACK
DECLARE
  v_AUDITORIUM          AUDITORIUM.AUDITORIUM%TYPE;
  v_AUDITORIUM_NAME     AUDITORIUM.AUDITORIUM_NAME%TYPE;
  v_AUDITORIUM_CAPACITY AUDITORIUM.AUDITORIUM_CAPACITY%TYPE;
BEGIN
  DELETE
  FROM AUDITORIUM
  WHERE AUDITORIUM = 'A1'
  RETURNING AUDITORIUM, AUDITORIUM_NAME, AUDITORIUM_CAPACITY
  INTO v_AUDITORIUM, v_AUDITORIUM_NAME, v_AUDITORIUM_CAPACITY;

  DBMS_OUTPUT.PUT_LINE('AUDITORIUM: ' || v_AUDITORIUM || ', AUDITORIUM_NAME: ' || v_AUDITORIUM_NAME ||
                       ', AUDITORIUM_CAPACITY: ' || v_AUDITORIUM_CAPACITY);
  COMMIT;

  DELETE
  FROM AUDITORIUM
  WHERE AUDITORIUM = 'A2'
  RETURNING AUDITORIUM, AUDITORIUM_NAME, AUDITORIUM_CAPACITY INTO v_AUDITORIUM, v_AUDITORIUM_NAME, v_AUDITORIUM_CAPACITY;

  DBMS_OUTPUT.PUT_LINE('AUDITORIUM: ' || v_AUDITORIUM || ', AUDITORIUM_NAME: ' || v_AUDITORIUM_NAME ||
                       ', AUDITORIUM_CAPACITY: ' || v_AUDITORIUM_CAPACITY);
  ROLLBACK;
end;

select *
from AUDITORIUM;
-- 10. Продемонстрируйте оператор DELETE, вызывающий нарушение целостности в базе данных. Обработайте возникшее исключение

INSERT INTO AUDITORIUM_TYPE (AUDITORIUM_TYPE) VALUES ('Lecture');

INSERT INTO AUDITORIUM (AUDITORIUM, AUDITORIUM_NAME, AUDITORIUM_CAPACITY, AUDITORIUM_TYPE)
VALUES ('A1_3', 'Аудитория 1', 100, 'Lecture');

SET SERVEROUTPUT ON;
DECLARE
BEGIN
  DELETE FROM AUDITORIUM_TYPE
  WHERE AUDITORIUM_TYPE = 'Lecture';

  COMMIT;  
EXCEPTION
  WHEN OTHERS THEN
    DBMS_OUTPUT.PUT_LINE('Ошибка: ' || SQLCODE || ' ' || SQLERRM);
    ROLLBACK;  
END;

SELECT * FROM AUDITORIUM;
----------------------------------------Явные курсоры----------------------------------------
-- 11. Создайте анонимный блок, распечатывающий таблицу TEACHER с применением явного курсора LOOP-цикла. Считанные данные должны быть записаны в переменные, объявленные с применением опции %TYPE
DECLARE
  v_TEACHER      TEACHER.TEACHER%TYPE;
  v_TEACHER_NAME TEACHER.TEACHER_NAME%TYPE;
  v_PULPIT       TEACHER.PULPIT%TYPE;

  CURSOR c_TEACHER IS
    SELECT TEACHER,
           TEACHER_NAME,
           PULPIT
    FROM TEACHER;

BEGIN
  FOR i IN c_TEACHER
    LOOP
      v_TEACHER := i.TEACHER;
      v_TEACHER_NAME := i.TEACHER_NAME;
      v_PULPIT := i.PULPIT;
      DBMS_OUTPUT.PUT_LINE('TEACHER: ' || v_TEACHER || ', TEACHER_NAME: ' || v_TEACHER_NAME || ', PULPIT: ' ||
                           v_PULPIT);
    END LOOP;
end;

-- 12. Создайте АБ, распечатывающий таблицу SUBJECT с применением явного курсора иWHILE-цикла. Считанные данные должны быть записаны в запись (RECORD), объявленную с применением опции %ROWTYPE
declare
    v_SUBJECT SUBJECT%ROWTYPE;

    cursor cur is
        select * from SUBJECT;
BEGIN
    open cur;
    while true
        loop
            FETCH CUR INTO v_SUBJECT;
            EXIT WHEN cur%NOTFOUND;
      DBMS_OUTPUT.PUT_LINE('SUBJECT: ' || v_SUBJECT.SUBJECT || ', SUBJECT_NAME: ' || v_SUBJECT.SUBJECT_NAME ||
                           ', PULPIT: ' || v_SUBJECT.PULPIT);
        end loop;
end;

-- 13. Создайте АБ, распечатывающий все кафедры (таблица PULPIT) и фамилии всех преподавателей (TEACHER) использовав, соединение (JOIN) PULPIT и TEACHER и с применением явного курсора и FOR-цикла
DECLARE
  v_PULPIT         PULPIT.PULPIT%TYPE;
  v_PULPIT_NAME    PULPIT.PULPIT_NAME%TYPE;
  v_FACULTY        PULPIT.FACULTY%TYPE;
  v_TEACHER        TEACHER.TEACHER%TYPE;
  v_TEACHER_NAME   TEACHER.TEACHER_NAME%TYPE;
  v_PULPIT_TEACHER PULPIT.PULPIT%TYPE;
  CURSOR c_PULPIT_TEACHER IS
    SELECT PULPIT.PULPIT,
           PULPIT.PULPIT_NAME,
           PULPIT.FACULTY,
           TEACHER.TEACHER,
           TEACHER.TEACHER_NAME
    FROM PULPIT
           JOIN TEACHER ON PULPIT.PULPIT = TEACHER.PULPIT;
BEGIN
  FOR i IN c_PULPIT_TEACHER
    LOOP
      v_PULPIT := i.PULPIT;
      v_PULPIT_NAME := i.PULPIT_NAME;
      v_FACULTY := i.FACULTY;
      v_TEACHER := i.TEACHER;
      v_TEACHER_NAME := i.TEACHER_NAME;
      DBMS_OUTPUT.PUT_LINE('PULPIT: ' || v_PULPIT || ', PULPIT_NAME: ' || v_PULPIT_NAME || ', FACULTY: ' || v_FACULTY ||
                           ', TEACHER: ' || v_TEACHER || ', TEACHER_NAME: ' || v_TEACHER_NAME);
    END LOOP;
end;

-- 14. Создайте АБ, распечатывающий следующие списки аудиторий: все аудитории (таблица AUDITORIUM) с вместимостью меньше 20, от 21-30, от 31-60, от 61 до 80, от 81 и выше. Примените курсор с параметрами и три способа организации цикла по строкам курсора
DECLARE
BEGIN
  FOR i IN 0..100
  LOOP
    INSERT INTO AUDITORIUM (AUDITORIUM, AUDITORIUM_NAME, AUDITORIUM_CAPACITY, AUDITORIUM_TYPE)
    VALUES ('A' || (i + 1000), 'Аудитория ' || (i + 1000), ROUND(DBMS_RANDOM.VALUE(1, 100)), 'Auditorium');
  END LOOP;
END;

SELECT * FROM AUDITORIUM;

DECLARE
  v_AUDITORIUM          AUDITORIUM.AUDITORIUM%TYPE; 
  v_AUDITORIUM_NAME     AUDITORIUM.AUDITORIUM_NAME%TYPE; 
  v_AUDITORIUM_CAPACITY AUDITORIUM.AUDITORIUM_CAPACITY%TYPE;

  CURSOR c_AUDITORIUM (min_capacity INT, max_capacity INT) IS
    SELECT AUDITORIUM,
           AUDITORIUM_NAME,
           AUDITORIUM_CAPACITY
    FROM AUDITORIUM
    WHERE AUDITORIUM_CAPACITY BETWEEN min_capacity AND max_capacity
    ORDER BY AUDITORIUM_CAPACITY;

BEGIN
  FOR capacity_range IN 1..5 LOOP
    CASE capacity_range
      WHEN 1 THEN
        OPEN c_AUDITORIUM(0, 20);
        DBMS_OUTPUT.PUT_LINE('------------------ 0 > 20 ----------------');
      WHEN 2 THEN
        OPEN c_AUDITORIUM(21, 30);
        DBMS_OUTPUT.PUT_LINE('------------------ 21 > 30 ----------------');
      WHEN 3 THEN
        OPEN c_AUDITORIUM(31, 60);
        DBMS_OUTPUT.PUT_LINE('------------------ 31 > 60 ----------------');
      WHEN 4 THEN
        OPEN c_AUDITORIUM(61, 80);
        DBMS_OUTPUT.PUT_LINE('------------------ 61 > 80 ----------------');
      WHEN 5 THEN
        OPEN c_AUDITORIUM(81, 100);
        DBMS_OUTPUT.PUT_LINE('------------------ > 81 ----------------');
    END CASE;

    LOOP
      FETCH c_AUDITORIUM INTO v_AUDITORIUM, v_AUDITORIUM_NAME, v_AUDITORIUM_CAPACITY;
      EXIT WHEN c_AUDITORIUM%NOTFOUND;

      DBMS_OUTPUT.PUT_LINE('AUDITORIUM: ' || v_AUDITORIUM || 
                           ', AUDITORIUM_NAME: ' || v_AUDITORIUM_NAME ||
                           ', AUDITORIUM_CAPACITY: ' || v_AUDITORIUM_CAPACITY);
    END LOOP;

    CLOSE c_AUDITORIUM; 
  END LOOP;
END;

-- 15. Создайте AБ. Объявите курсорную переменную с помощью системного типа refcursor. Продемонстрируйте ее применение для курсора c параметрами 
DECLARE
  v_AUDITORIUM          AUDITORIUM.AUDITORIUM%TYPE;
  v_AUDITORIUM_NAME     AUDITORIUM.AUDITORIUM_NAME%TYPE;
  v_AUDITORIUM_CAPACITY AUDITORIUM.AUDITORIUM_CAPACITY%TYPE;

  TYPE ref_cursor IS REF CURSOR;
  c_AUDITORIUM          ref_cursor;  

  v_min_capacity INT := 0;
  v_max_capacity INT := 100;

BEGIN
  OPEN c_AUDITORIUM FOR
    SELECT AUDITORIUM,
           AUDITORIUM_NAME,
           AUDITORIUM_CAPACITY
    FROM AUDITORIUM
    WHERE AUDITORIUM_TYPE = 'Auditorium'
      AND AUDITORIUM_CAPACITY BETWEEN v_min_capacity AND v_max_capacity;

  LOOP
    FETCH c_AUDITORIUM INTO v_AUDITORIUM, v_AUDITORIUM_NAME, v_AUDITORIUM_CAPACITY;
    EXIT WHEN c_AUDITORIUM%NOTFOUND;

    DBMS_OUTPUT.PUT_LINE('AUDITORIUM: ' || v_AUDITORIUM || 
                         ', AUDITORIUM_NAME: ' || v_AUDITORIUM_NAME ||
                         ', AUDITORIUM_CAPACITY: ' || v_AUDITORIUM_CAPACITY);
  END LOOP;

  CLOSE c_AUDITORIUM;  

EXCEPTION
  WHEN OTHERS THEN
    DBMS_OUTPUT.PUT_LINE('Ошибка: ' || SQLCODE || ' ' || SQLERRM);
    IF c_AUDITORIUM%ISOPEN THEN
      CLOSE c_AUDITORIUM;  
    END IF;
END;

-- 16. Создайте AБ. Продемонстрируйте понятие курсорный подзапрос
DECLARE
  v_AUDITORIUM          AUDITORIUM.AUDITORIUM%TYPE;
  v_AUDITORIUM_NAME     AUDITORIUM.AUDITORIUM_NAME%TYPE;
  v_AUDITORIUM_CAPACITY AUDITORIUM.AUDITORIUM_CAPACITY%TYPE;

  TYPE ref_cursor IS REF CURSOR;
  c_AUDITORIUM          ref_cursor;  

BEGIN
  OPEN c_AUDITORIUM FOR
    SELECT AUDITORIUM,
           AUDITORIUM_NAME,
           AUDITORIUM_CAPACITY
    FROM AUDITORIUM
    WHERE AUDITORIUM_TYPE IN (
      SELECT AUDITORIUM_TYPE
      FROM AUDITORIUM_TYPE
      WHERE AUDITORIUM_TYPE = 'Auditorium'
    )
    AND AUDITORIUM_CAPACITY BETWEEN 0 AND 100;

  LOOP
    FETCH c_AUDITORIUM INTO v_AUDITORIUM, v_AUDITORIUM_NAME, v_AUDITORIUM_CAPACITY;
    EXIT WHEN c_AUDITORIUM%NOTFOUND;

    DBMS_OUTPUT.PUT_LINE('AUDITORIUM: ' || v_AUDITORIUM || 
                         ', AUDITORIUM_NAME: ' || v_AUDITORIUM_NAME ||
                         ', AUDITORIUM_CAPACITY: ' || v_AUDITORIUM_CAPACITY);
  END LOOP;

  CLOSE c_AUDITORIUM;  

EXCEPTION
  WHEN OTHERS THEN
    DBMS_OUTPUT.PUT_LINE('Ошибка: ' || SQLCODE || ' ' || SQLERRM);
    IF c_AUDITORIUM%ISOPEN THEN
      CLOSE c_AUDITORIUM;  
    END IF;
END;

-- 17. Создайте AБ. Уменьшите вместимость всех аудиторий (таблица AUDITORIUM) вместимостью от 40 до 80 на 10%. �?спользуйте явный курсор с параметрами, цикл FOR, конструкцию UPDATE CURRENT OF
DECLARE
  v_AUDITORIUM          AUDITORIUM.AUDITORIUM%TYPE;    
  v_AUDITORIUM_CAPACITY AUDITORIUM.AUDITORIUM_CAPACITY%TYPE;

  CURSOR c_AUDITORIUM (min_capacity INT, max_capacity INT) IS
    SELECT AUDITORIUM, AUDITORIUM_CAPACITY
    FROM AUDITORIUM
    WHERE AUDITORIUM_CAPACITY >= min_capacity
      AND AUDITORIUM_CAPACITY <= max_capacity
      FOR UPDATE;

BEGIN
  FOR i IN 1..1 LOOP
	  
    FOR rec IN c_AUDITORIUM(40, 80) LOOP

      UPDATE AUDITORIUM
      SET AUDITORIUM_CAPACITY = AUDITORIUM_CAPACITY * 0.9
      WHERE CURRENT OF c_AUDITORIUM;

      DBMS_OUTPUT.PUT_LINE('Аудитория: ' || rec.AUDITORIUM || 
                           ', Новая вместимость: ' || (rec.AUDITORIUM_CAPACITY * 0.9));
    END LOOP;

  END LOOP;

  COMMIT;  
END;
-- 18. Создайте AБ. Удалите все аудитории (таблица AUDITORIUM) вместимостью от 0 до 20. �?спользуйте явный курсор с параметрами, цикл WHILE, конструкцию UPDATE CURRENT OF
SET SERVEROUTPUT ON;
DECLARE
  v_AUDITORIUM AUDITORIUM.AUDITORIUM%TYPE;
  CURSOR c_AUDITORIUM(count INT) IS
    SELECT AUDITORIUM
    FROM AUDITORIUM
    WHERE AUDITORIUM_CAPACITY >= 0
      AND AUDITORIUM_CAPACITY <= count
      FOR UPDATE;
BEGIN
  OPEN c_AUDITORIUM(20);
  
  FETCH c_AUDITORIUM INTO v_AUDITORIUM;
  
  WHILE c_AUDITORIUM%FOUND LOOP
    DELETE
    FROM AUDITORIUM
    WHERE CURRENT OF c_AUDITORIUM;
    
    FETCH c_AUDITORIUM INTO v_AUDITORIUM;
  END LOOP;

  CLOSE c_AUDITORIUM;
END;
-- 19. Создайте AБ. Продемонстрируйте применение псевдостолбца ROWID в операторах UPDATE и DELETE
DECLARE
  CURSOR c_AUDITORIUM IS
    SELECT ROWID
    FROM AUDITORIUM
    WHERE AUDITORIUM_CAPACITY >= 0
      and AUDITORIUM_CAPACITY <= 20
      FOR UPDATE;
BEGIN
  FOR i IN c_AUDITORIUM
    LOOP
      UPDATE AUDITORIUM
      SET AUDITORIUM_CAPACITY = AUDITORIUM_CAPACITY * 0.9
      WHERE ROWID = i.ROWID;
      DELETE
      FROM AUDITORIUM
      WHERE ROWID = i.ROWID;
    END LOOP;
end;

-- 20. Распечатайте в одном цикле всех преподавателей (TEACHER), разделив группами по три (отделите группы линией -------------)
DECLARE
  v_TEACHER      TEACHER.TEACHER%TYPE;
  v_TEACHER_NAME TEACHER.TEACHER_NAME%TYPE;
  v_PULPIT       TEACHER.PULPIT%TYPE;
  CURSOR c_TEACHER IS
    SELECT TEACHER,
           TEACHER_NAME,
           PULPIT
    FROM TEACHER;

BEGIN
  OPEN c_TEACHER;
  LOOP
    FETCH c_TEACHER INTO v_TEACHER, v_TEACHER_NAME, v_PULPIT;
    EXIT WHEN c_TEACHER%NOTFOUND;
    DBMS_OUTPUT.PUT_LINE('TEACHER: ' || v_TEACHER || ', TEACHER_NAME: ' || v_TEACHER_NAME || ', PULPIT: ' ||
                         v_PULPIT);
    IF MOD(c_TEACHER%ROWCOUNT, 3) = 0 THEN
      DBMS_OUTPUT.PUT_LINE('-----------------');
    END IF;
  END LOOP;

  CLOSE c_TEACHER;
end;