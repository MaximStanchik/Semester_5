-- 1. Список всех табличных пространств
SELECT * FROM DBA_TABLESPACES;

-- 2. Список всех файлов данных
SELECT * FROM SYS.DBA_DATA_FILES;

-- 3. Список всех ролей в словаре
SELECT * FROM DBA_ROLES;

-- 4. Все системные привилегии
SELECT * FROM DBA_SYS_PRIVS;

-- 5. Список всех профилей БД
SELECT * FROM DBA_PROFILES;

-- 6. Список существующих PDB
SELECT * FROM DBA_PDBS;

-- 7. Перечень экземпляров
SELECT * FROM V$INSTANCE;

-- 8. Доступные и включенные опции БД
SELECT * FROM V$OPTION;

-- 9. Профили пользователей
SELECT * FROM DBA_PROFILES;

-- 10. Глобальное имя базы данных
SELECT * FROM GLOBAL_NAME;

-- 11. Информация о файлах данных (перманентные)
SELECT * FROM SYS.DBA_DATA_FILES;

-- 12. Информация о временных файлах данных
SELECT * FROM SYS.DBA_TEMP_FILES;

-- 13. Информация о пользователях БД
SELECT * FROM DBA_USERS;

-- 14. Информация о сегментах БД
SELECT * FROM DBA_SEGMENTS;

-- 15. Удаленные объекты в корзине пользователя
SELECT * FROM USER_RECYCLEBIN;

-- 16. Информация о экстентах в БД
SELECT * FROM DBA_EXTENTS;

-- 17. Информация о лог-файлах БД
SELECT * FROM V$LOGFILE;

-- 18. Информация о группах redo логов
SELECT * FROM V$LOG;

-- 19. Информация о базе данных
SELECT * FROM V$DATABASE;

-- 20. Информация о архивированных redo логах
SELECT * FROM V$ARCHIVED_LOG;

-- 21. Информация о контрольных файлах
SELECT * FROM V$CONTROLFILE;

-- 22. Параметры конфигурации БД
SELECT * FROM V$PARAMETER;

-- 23. Пользователи с доступом через файл паролей
SELECT * FROM V$PWFILE_USERS;

-- 24. Диагностическая информация
SELECT * FROM V$DIAG_INFO;

-- 25. Информация о SGA
SELECT * FROM V$SGA;

-- 26. Динамические компоненты SGA
SELECT * FROM V$SGA_DYNAMIC_COMPONENTS;

-- 27. Свободная память в SGA
SELECT * FROM V$SGA_DYNAMIC_FREE_MEMORY;

-- 28. Параметры конфигурации БД
SELECT * FROM V$PARAMETER;

-- 29. Текущие сессии в БД
SELECT * FROM V$SESSION;

-- 30. Фоновые процессы
SELECT * FROM V$BGPROCESS;

-- 31. Диспетчеры
SELECT * FROM V$DISPATCHER;

-- 32. Доступные сервисы
SELECT * FROM V$SERVICES;

-- 33. Роли, назначенные пользователям
SELECT * FROM DBA_ROLE_PRIVS;

-- 34. Пользователи в БД
SELECT * FROM ALL_USERS;

-- 35. Информация о сегментах, доступных пользователю
SELECT * FROM ALL_SEGMENTS;

--------------------------

--------------------Task_1------------------— 
// Условие: вывести все столбцы из представления, которое содержит информацию обо всех объектах базы данных, доступных пользователю. Тип объектов — таблицы 
// Решение: 
select * from all_objects where object_type = 'TABLE'; 
 
--------------------Task_2------------------— 
// Условие: найдите все таблицы с некластеризованными индексами (не кластерными). Выведите имя таблицы и имя индекса 
// Решение: 
select table_name, index_name from dba_indexes where index_type = 'NONCLUSTERED' and owner = 'SCOTT'; 
 
--------------------Task_3------------------— 
// Условие: напишите запрос для поиска всех триггеров, связанных с таблицами пользователя 'SYS'. Выведите имя триггера, имя таблицы и тип события 
// Решение: 
select trigger_name, table_name, triggering_event from dba_triggers where owner = 'SYS'; 
 
--------------------Task_4------------------— 
// Условие: вывести информацию о представлениях, созданных текущим пользователем 
// Решение: 
select view_name from user_views; 
 
--------------------Task_5------------------— 
// Условие: найдите все представления, принадлежащие пользователю 'SCOTT'. Выведите имя представления и SQL-запрос, из которого оно создано 
// Решение: 
select view_name, text from dba_views where owner = 'SCOTT'; 
 
--------------------Task_6------------------— 
// Условие: выведите список всех индексов для каждой таблицы, принадлежащей текущему пользователю 
// Решение: 
select index_name, table_name from user_indexes; 
 
--------------------Task_7------------------— 
// Условие: найти все представления пользователя 
// Решение: 
select view_name from user_views; 
 
--------------------Task_8------------------— 
// Условие: показать все таблицы пользователя 
// Решение: 
select table_name from user_tables; 
 
--------------------Task_9------------------— 
// Условие: написать запрос, который выводит имена и типы всех объектов (таблицы, индексы, представления), принадлежащих текущему пользователю 
// Решение: 
select object_name, object_type from user_objects; 
 
 
-------------------Task_10------------------— 
// Условие: вывести все записи из словаря данных, представляющего собой системное представление, которое содержит информацию о всех представлениях и словарях данных, доступных в базе данных 
// Решение: 
select * from dictionary;