--------------------Task_1-------------------- Определите общий размер области SGA
select * from V$SGA;
select SUM(value) from v$sga;
--------------------Task_2-------------------- Определите текущие размеры основных пулов SGA
select * from v$sga_dynamic_components where current_size > 0;
--------------------Task_3-------------------- Определите размеры гранулы для каждого пула
select component, granule_size from v$sga_dynamic_components where current_size > 0;
--------------------Task_4-------------------- Определите объем доступной свободной памяти в SGA
select current_size from v$sga_dynamic_free_memory;
--------------------Task_5-------------------- Определите максимальный и целевой размер области SGA
 SELECT value FROM v$parameter WHERE name = 'sga_target';
 SELECT value FROM v$parameter WHERE name = 'sga_max_size';
--------------------Task_6-------------------- Определите размеры пулов КЕЕP, DEFAULT и RECYCLE буферного кэша
select component, current_size, min_size, MAX_SIZE from v$sga_dynamic_components
where component='KEEP buffer cache' or component='DEFAULT buffer cache' or component='RECYCLE buffer cache';
--------------------Task_7-------------------- Создайте таблицу, которая будет помещаться в пул КЕЕP
create table TableLab5 (
        id number,
        name varchar2(50)
    ) storage (buffer_pool keep) tablespace users;

    select segment_name, segment_type, tablespace_name, buffer_pool
    from user_segments
    where segment_name = 'TABLELAB5';

    drop table TableLab5;
--------------------Task_8-------------------- Создайте таблицу, которая будет кэшироваться в пуле DEFAULT
create table cachedTableLab5 (
      id number,
      name varchar2(50),
      age number
    ) cache;

    select segment_name, segment_type, tablespace_name, buffer_pool
    from user_segments
    where segment_name = 'CACHEDTABLELAB5';

drop table cachedTableLab5;
--------------------Task_9-------------------- Найдите размер буфера журналов повтора
select value from v$parameter where name = 'log_buffer';
--------------------Task_10-------------------- Найдите размер свободной памяти в большом пуле
select POOL, bytes/1024/1024 AS "Free Memory (MB)"
from V$SGASTAT
where POOL = 'large pool' AND name = 'free memory';
--------------------Task_11-------------------- Определите режимы текущих соединений с инстансом
select username, service_name, server, osuser, machine, program, STATE
    from v$session
    where username is not null;
--------------------Task_12-------------------- Получите полный список работающих в настоящее время фоновых процессов
select name, description FROM v$bgprocess;
--------------------Task_13-------------------- Получите список работающих в настоящее время серверных процессов
select * from v$process where addr != '00';
--------------------Task_14-------------------- Определите, сколько процессов DBWn работает в настоящий момент
select count(*) from v$process where addr!= '00' and pname like 'DBW%';
--------------------Task_15-------------------- Определите сервисы (точки подключения экземпляра)
select * from v$active_services;
--------------------Task_16-------------------- Получите известные вам параметры диспетчеров
select * from v$dispatcher;
--------------------Task_17-------------------- Укажите в списке Windows-сервисов сервис, реализующий процесс LISTENER
select * from v$services;
--------------------Task_18-------------------- Продемонстрируйте и поясните содержимое файла LISTENER.ORA
----смотреть в report.docx
--------------------Task_19-------------------- Запустите утилиту lsnrctl и поясните ее основные команды
----смотреть в report.docx
--------------------Task_20-------------------- Получите список служб инстанса, обслуживаемых процессом LISTENER
----смотреть в report.docx