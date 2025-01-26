-- 1.	Определите размеры областей памяти SGA. 
SELECT * FROM V$SGA;
SELECT * FROM V$SGA_DYNAMIC_COMPONENTS;

-- 2.	Получите список всех параметров экземпляра. 
SELECT * FROM V$PARAMETER;

-- 3.	Получите список управляющих файлов. 
SELECT NAME FROM V$DATABASE;
SELECT NAME FROM V$CONTROLFILE;
SELECT * FROM V$PARAMETER WHERE NAME = 'control_files';

-- 4.	Сформируйте PFILE.
CREATE PFILE='/opt/oracle/product/19c/dbhome_1/dbs/init.ora' FROM SPFILE;

-- 5.	Создайте таблицу из двух столбцов, один из которых первичный ключ. Получите перечень всех сегментов. Вставьте данные в таблицу. Определите, сколько в сегменте таблицы экстентов, их размер в блоках и байтах. 
CREATE TABLE testTable (
	id NUMBER PRIMARY KEY,
	name varchar2(100)
);

SELECT * FROM testTable;

INSERT INTO testTable (id, name) VALUES (1, 'Alice');
INSERT INTO testTable (id, name) VALUES (2, 'Tom');
INSERT INTO testTable (id, name) VALUES (3, 'Max');

SELECT * FROM dba_segments;
SELECT * FROM dba_segments WHERE SEGMENT_NAME = 'TESTTABLE';

-- 6.	Получите перечень всех процессов СУБД Oracle. Для серверных процессов укажите режим подключения. Для фоновых укажите работающие в настоящий момент.
SELECT * FROM V$SESSION;
SELECT * FROM V$PROCESS;

SELECT SID, SERIAL#, USERNAME, STATUS, MACHINE, PROGRAM, TYPE FROM V$SESSION WHERE TYPE = 'USER';

SELECT PROCESS, SPID, STATUS, MACHINE
FROM V$PROCESS 
LEFT JOIN V$SESSION ON V$PROCESS.ADDR = V$SESSION.PADDR
WHERE SID IS NULL OR STATUS = 'ACTIVE';

-- 7.	Получите перечень всех табличных пространств и их файлов. 
SELECT * FROM dba_tablespaces;
SELECT * FROM dba_data_files;

-- 8.	Получите перечень всех ролей.
SELECT * FROM dba_roles;
SELECT * FROM user_roles; -- почему-то не работает, а должно, это странно
SELECT * FROM all_roles; -- почему-то не работает, а должно, это странно

-- 9.	Получите перечень привилегий для определенной роли. 
SELECT * FROM DBA_SYS_PRIVS WHERE GRANTEE = 'DBA';
SELECT * FROM DBA_TAB_PRIVS WHERE GRANTEE = 'DBA';

-- 10.	Получите перечень всех пользователей.
SELECT * FROM dba_users;
SELECT * FROM all_users;

-- 11.	Создайте роль.
CREATE ROLE myRole;
GRANT CREATE SESSION TO myRole;
GRANT CREATE TABLE TO myRole;
GRANT CREATE VIEW TO my_role;
GRANT CREATE PROCEDURE TO my_role;
GRANT CREATE SEQUENCE TO my_role;
GRANT CREATE TRIGGER TO my_role;
GRANT CREATE TYPE TO my_role;
GRANT CREATE INDEX TO my_role;
GRANT ALTER ANY TABLE TO my_role;
GRANT DROP ANY TABLE TO my_role;
GRANT SELECT ANY TABLE TO my_role;
GRANT INSERT ANY TABLE TO my_role;
GRANT UPDATE ANY TABLE TO my_role;
GRANT DELETE ANY TABLE TO my_role;
GRANT EXECUTE ANY PROCEDURE TO my_role;
GRANT GRANT ANY PRIVILEGE TO my_role;

-- 12.	Создайте пользователя.
CREATE USER miniUser IDENTIFIED BY password p1337;

-- 13.	Получите перечень всех профилей безопасности.
SELECT * FROM dba_profiles;

-- 14.	Получите перечень всех параметров профиля безопасности.
SELECT * FROM dba_profiles;
SELECT * FROM dba_profiles WHERE profile = 'DEFAULT';

-- 15.	Создайте профиль безопасности.

CREATE profile myProfile LIMIT
	SESSIONS_PER_USER 5
	CPU_PER_SESSION 100000
	CPU_PER_CALL 100000
	CONNECT_TIME 60
	IDLE_TIME 10
	PRIVATE_SGA 15M;

ALTER USER username PROFILE myProfile;

-- 16.	Создайте последовательность S1, со следующими характеристиками: 
--		начальное значение 1000; 
--		приращение 10; 
--		минимальное значение 0; 
--		максимальное значение 10000; 
--		циклическую; 
--		кэширующую 30 значений в памяти; 
--		гарантирующую хронологию значений. 

CREATE SEQUENCE S1 START WITH 1000 increment BY 10 MINVALUE 0 MAXVALUE 10000 CYCLE cache 30 ORDER;
		
--		Создайте таблицу T1 с тремя столбцами и введите (INSERT) 10 строк, со значениями из S1.

CREATE TABLE supertable (
	id NUMBER PRIMARY KEY,
	name varchar2(50),
	age integer
);

SELECT * FROM supertable;

INSERT INTO supertable (id, name, age) VALUES (S1.nextval, 'Max', 1);
INSERT INTO supertable (id, name, age) VALUES (S1.nextval, 'Alex', 2);
INSERT INTO supertable (id, name, age) VALUES (S1.nextval, 'Steve', 3);
INSERT INTO supertable (id, name, age) VALUES (S1.nextval, 'Nick', 4);
INSERT INTO supertable (id, name, age) VALUES (S1.nextval, 'Angela', 5);

INSERT INTO supertable (id, name, age) VALUES (S1.nextval, 'Michael', 6);
INSERT INTO supertable (id, name, age) VALUES (S1.nextval, 'Keven', 7);
INSERT INTO supertable (id, name, age) VALUES (S1.nextval, 'Lue', 8);
INSERT INTO supertable (id, name, age) VALUES (S1.nextval, 'Harris', 9);
INSERT INTO supertable (id, name, age) VALUES (S1.nextval, 'Jacob', 10);

-- 17.	Создайте частный и публичный синоним для одной из таблиц и продемонстрируйте его область видимости. Найдите созданные синонимы в представлениях словаря Oracle.
CREATE PUBLIC SYNONYM public_newTable FOR newTable;
CREATE SYNONYM private_newTable FOR newTable;

-- 18.	Разработайте анонимный блок, демонстрирующий возникновение и обработку исключений WHEN TO_MANY_ROWS и NO_DATA_FOUND.
CREATE TABLE tempTable (
    id NUMBER,
    name VARCHAR2(50)
);

SELECT * FROM tempTable;

INSERT INTO tempTable (id, name) VALUES (1, 'John Doe');
INSERT INTO tempTable (id, name) VALUES (1, 'Jane Smith');

DECLARE
    v_name VARCHAR2(50);
    v_id NUMBER := 1; 

BEGIN
    SELECT name INTO v_name FROM tempTable WHERE id = v_id;

    DBMS_OUTPUT.PUT_LINE('Имя: ' || v_name);

EXCEPTION
    WHEN NO_DATA_FOUND THEN -- делаем v_id := 0
        DBMS_OUTPUT.PUT_LINE('Запись с ID ' || v_id || ' не найдена.');

    WHEN TOO_MANY_ROWS THEN
        DBMS_OUTPUT.PUT_LINE('Найдено слишком много записей с ID ' || v_id || '.');

    WHEN OTHERS THEN
        DBMS_OUTPUT.PUT_LINE('Произошла ошибка: ' || SQLERRM);
END;

-- 19.	Получите перечень всех файлов групп журналов повтора. 
SELECT * FROM V$LOGFILE;

-- 20.	Определите текущую группу журналов повтора. 
SELECT * FROM v$log WHERE status = 'CURRENT';

-- 21.	Получите перечень контрольных файлов.
SELECT * FROM v$controlfile;

-- 22.	Создайте таблицу и вставьте в нее 100 записей. Найдите таблицу и ее свойства в представлениях словаря.

CREATE TABLE newTable (
	id NUMBER GENERATED BY DEFAULT AS IDENTITY PRIMARY KEY,
	name varchar2(50)
);

SELECT * FROM newTable;

BEGIN
	FOR i IN 1..100 LOOP
		INSERT INTO newTable (name) VALUES ('Name ' || i);
	END LOOP;
END;

SELECT * FROM dba_tables WHERE table_name = 'NEWTABLE';

-- 23.	Получите список сегментов табличного пространства. 
SELECT * FROM dba_segments WHERE TABLESPACE_NAME = 'SYSTEM';
SELECT * FROM dba_segments WHERE TABLESPACE_NAME = 'USERS';
SELECT * FROM dba_segments WHERE TABLESPACE_NAME = 'TEMP';
SELECT * FROM dba_segments WHERE TABLESPACE_NAME = 'UNDOTBS1';
SELECT * FROM dba_segments WHERE TABLESPACE_NAME = 'SYSAUX';

-- 24.	Выведите список всех объектов, доступных пользователю. 
SELECT * FROM all_objects WHERE owner = USER;
SELECT * FROM all_objects WHERE owner = 'SYS';

-- 25.	Вычислите количество блоков, занятых таблицей.
SELECT sum(blocks) FROM dba_segments WHERE SEGMENT_NAME = 'TESTTABLE' AND SEGMENT_TYPE = 'TABLE';

-- 26.	Выведите список текущих сессий. 
SELECT * FROM v$session;

-- 27.	Выведите, производится ли архивирование журналов повтора.
SELECT log_mode FROM v$database;
SELECT * FROM v$database;

-- 28.	Создайте представление с определенными параметрами.
CREATE VIEW newView AS SELECT * FROM newTable WHERE id > 50;
SELECT * FROM newView;

-- 29.	Создайте database link с определенными параметрами.
CREATE DATABASE LINK my_db_link CONNECT TO remote_user IDENTIFIED BY remote_password USING 'remote_database';

-- 30.	Продемонстрируйте эскалацию исключения.

CREATE TABLE demo_table (
    id NUMBER PRIMARY KEY,
    value VARCHAR2(50)
);

CREATE OR REPLACE PROCEDURE insert_into_demo (p_id NUMBER, p_value VARCHAR2) IS
BEGIN
    INSERT INTO demo_table (id, value) VALUES (p_id, p_value);
EXCEPTION
    WHEN DUP_VAL_ON_INDEX THEN
        RAISE;  
END;

BEGIN
    insert_into_demo(1, 'Value 1');
    insert_into_demo(1, 'Value 2');  
EXCEPTION
    WHEN DUP_VAL_ON_INDEX THEN
        DBMS_OUTPUT.PUT_LINE('Ошибка: Значение дублируется!');
    WHEN OTHERS THEN
        DBMS_OUTPUT.PUT_LINE('Произошла другая ошибка: ' || SQLERRM);
END;

