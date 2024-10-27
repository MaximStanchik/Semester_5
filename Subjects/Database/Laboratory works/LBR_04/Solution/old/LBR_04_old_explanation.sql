--------------------Task_1--------------------
select tablespace_name, contents, status
from dba_tablespaces;
--------------------Task_2--------------------
select file_name, tablespace_name, bytes, status from dba_data_files;
select file_name, tablespace_name, bytes, status from dba_temp_files;
//DBA_DATA_FILES и DBA_TEMP_FILES Ч представлени€, которые содержат информацию 
//о физических файлах базы данных дл€ перманентных и временных табличных пространств соответственно.
--------------------Task_3--------------------
select group#, thread#, sequence#, bytes, members, archived, status from v$log;
select group#, thread#, sequence# from v$log where status = 'CURRENT';
//group# -- номер группы
//thread# -- номер потока (используетс€ в real application clusters)
//sequence# -- номер последовательности журнала
//bytes -- размер журнала в байтах
//members -- количество членов в группе (сколько файлов принадлежит группе)
//archived -- был ли журнал заархивирован (да/нет)
//status -- статус журнала (current, innactive, active)
//v$log -- отображает информацию файла журнала из управл€ющего файла.
--------------------Task_4--------------------
select group#, member from v$logfile;
//v$logfile Ч представление, которое содержит информацию о физических файлах дл€ каждой группы журналов повтора.
--------------------Task_5--------------------
SELECT GROUP#, SEQUENCE#, STATUS FROM V$LOG WHERE STATUS = 'CURRENT';
SELECT CURRENT_SCN FROM V$DATABASE; 
ALTER SYSTEM SWITCH LOGFILE;
//SCN -- (System Change Number) уникальный идентификатор в Oracle Database, 
//который представл€ет последовательность изменений в базе данных. 
//SCN увеличиваетс€ вс€кий раз, когда происходит операци€, измен€юща€ данные (например, вставка, обновление, удаление или коммит транзакции).
--------------------Task_6--------------------
select group#, thread#, sequence#, status from v$log;

alter database add logfile group 4
('D:\User\Desktop\StudyAtBSTU\Course_3\Semester5\Subjects\Database\Laboratory works\LBR_04\Solution\redo01.log',
 'D:\User\Desktop\StudyAtBSTU\Course_3\Semester5\Subjects\Database\Laboratory works\LBR_04\Solution\redo02.log',
 'D:\User\Desktop\StudyAtBSTU\Course_3\Semester5\Subjects\Database\Laboratory works\LBR_04\Solution\redo03.log') size 50m;
 
select group#, member from v$logfile; -- убеждаемс€, что файлы журнала действительно созданы
alter system switch logfile; -- переключение журнала повтора
select group#, thread#, sequence#, status from v$log; -- проверка текущей группы журналов
select current_scn from v$database; -- проверка SCN
--------------------Task_7--------------------
alter system checkpoint global;

alter database drop logfile group 4;

//можно сделать в cmd чтобы поудал€ть:
//del "D:\User\Desktop\StudyAtBSTU\Course_3\Semester5\Subjects\Database\Laboratory works\LBR_04\Solution\redo01.log"
//del "D:\User\Desktop\StudyAtBSTU\Course_3\Semester5\Subjects\Database\Laboratory works\LBR_04\Solution\redo02.log"
//del "D:\User\Desktop\StudyAtBSTU\Course_3\Semester5\Subjects\Database\Laboratory works\LBR_04\Solution\redo03.log"
--------------------Task_8--------------------
select log_mode from v$database; //≈сли результатом будет ARCHIVELOG, то архивирование включено, если же NOARCHIVELOG Ч архивирование отключено
--------------------Task_9--------------------
select max(sequence#) from v$archived_log; //покажет номер последнего созданного архивного лога
-------------------Task_10--------------------
//перевод базы данных в режим MOUNT
shutdown immediate;
startup mount;

alter database archivelog; //включение архивировани€

alter database open;
-------------------Task_11--------------------
-------------------Task_12--------------------
-------------------Task_13--------------------
-------------------Task_14--------------------