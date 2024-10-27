--ex1. Определите общий размер области SGA.
    select * from V$SGA;
    select SUM(value) from v$sga;

--ex2. Определите текущие размеры основных пулов SGA.
    select * from v$sga_dynamic_components where current_size > 0;

--ex3. Определите размеры гранулы для каждого пула.
    select component, granule_size from v$sga_dynamic_components where current_size > 0;

--ex4. Определите объем доступной свободной памяти в SGA.
    select current_size from v$sga_dynamic_free_memory;

--ex5. Определите максимальный и целевой размер области SGA.
    SELECT value FROM v$parameter WHERE name = 'sga_target';
    SELECT value FROM v$parameter WHERE name = 'sga_max_size';
    --OR show parameter sga in sql plus

--ex6. Определите размеры пулов КЕЕP, DEFAULT и RECYCLE буферного кэша.
    select component, current_size, min_size, MAX_SIZE from v$sga_dynamic_components
    where component='KEEP buffer cache' or component='DEFAULT buffer cache' or component='RECYCLE buffer cache';

--ex7. Создайте таблицу, которая будет помещаться в пул КЕЕP.
-- Продемонстрируйте сегмент таблицы.
    CREATE TABLE TableLab5 (
        id NUMBER,
        name VARCHAR2(50)
    ) storage (buffer_pool keep) tablespace users;

    SELECT segment_name, segment_type, tablespace_name, buffer_pool
    FROM user_segments
    WHERE segment_name = 'TABLELAB5';

    drop table TableLab5;

--ex8. Создайте таблицу, которая будет кэшироваться в пуле DEFAULT.
-- Продемонстрируйте сегмент таблицы.
    CREATE TABLE cachedTableLab5 (
      id NUMBER,
      name VARCHAR2(50),
      age NUMBER
    ) CACHE;

    SELECT segment_name, segment_type, tablespace_name, buffer_pool
    FROM user_segments
    WHERE segment_name = 'CACHEDTABLELAB5';

drop table cachedTableLab5;

--ex9. Найдите размер буфера журналов повтора.
    --in SQL PLUS:
    --show parameter log_buffer;

--ex10. Найдите размер свободной памяти в большом пуле.
    select POOL, sum(BYTES)
    from v$sgastat where pool = 'large pool' AND name = 'free memory'
    group by POOL;

    --mb
    SELECT POOL, bytes/1024/1024 AS "Free Memory (MB)"
    FROM V$SGASTAT
    WHERE POOL = 'large pool' AND name = 'free memory';

--ex11. Определите режимы текущих соединений с инстансом
-- (dedicated, shared).
    select username, service_name, server, osuser, machine, program, STATE
    from v$session
    where username is not null;

--ex12. Получите полный список работающих в настоящее время
-- фоновых процессов.
    SELECT name, description FROM v$bgprocess;

--ex13. Получите список работающих в настоящее время серверных процессов.
    select * from v$process where addr != '00';

--ex14. Определите, сколько процессов DBWn работает в настоящий момент.
    select count(*) from v$process where addr!= '00' and pname like 'DBW%';

--ex15. Определите сервисы (точки подключения экземпляра).
    select * from v$active_services;
    --select * from v$services;

--ex16. Получите известные вам параметры диспетчеров.
    select * from v$dispatcher;
    --OR SQL PLUS:
    --show parameter dispatchers;

--ex17. Укажите в списке Windows-сервисов сервис,
-- реализующий процесс LISTENER.
    select * from v$services;
    --services.msc->%listener%

--ex18. Продемонстрируйте и поясните содержимофайла LISTENER.ORA.
    --path: WINDOWS.x64...(this is db_home)/network/admin/listener.ora
    --Screen: Screen_1.png

--ex19. Запустите утилиту lsnrctl и поясните ее основные команды.
    --Screen: screen_2
    --commands:
    /*
        1. start - Запускает слушатель баз данных Oracle.
        2. servacls - Отображает список сервисов и их доступа для подключений через слушателя.
        3. trace - Включает или отключает функцию трассировки для слушателя.
        4. show - Отображает текущие настройки слушателя или информацию о подключенных клиентах.
        5. stop - Останавливает слушатель баз данных Oracle.
        6. version - Отображает версию слушателя.
        7. quit или exit - Выходит из lsnrctl.
        8. status - Отображает текущий статус слушателя.
        9. reload - Перезагружает конфигурацию слушателя без его остановки.
        10. services - Отображает список доступных сервисов, которые могут быть запущены через слушателя.
        11. save_config - Сохраняет текущую конфигурацию слушателя в файл.
    */

--ex20. Получите список служб инстанса, обслуживаемых процессом LISTENER.
    --Screen: Screen_3
    --command: services