-- 1. ������ ���� ��������� �����������
SELECT * FROM DBA_TABLESPACES;

-- 2. ������ ���� ������ ������
SELECT * FROM SYS.DBA_DATA_FILES;

-- 3. ������ ���� ����� � �������
SELECT * FROM DBA_ROLES;

-- 4. ��� ��������� ����������
SELECT * FROM DBA_SYS_PRIVS;

-- 5. ������ ���� �������� ��
SELECT * FROM DBA_PROFILES;

-- 6. ������ ������������ PDB
SELECT * FROM DBA_PDBS;

-- 7. �������� �����������
SELECT * FROM V$INSTANCE;

-- 8. ��������� � ���������� ����� ��
SELECT * FROM V$OPTION;

-- 9. ������� �������������
SELECT * FROM DBA_PROFILES;

-- 10. ���������� ��� ���� ������
SELECT * FROM GLOBAL_NAME;

-- 11. ���������� � ������ ������ (������������)
SELECT * FROM SYS.DBA_DATA_FILES;

-- 12. ���������� � ��������� ������ ������
SELECT * FROM SYS.DBA_TEMP_FILES;

-- 13. ���������� � ������������� ��
SELECT * FROM DBA_USERS;

-- 14. ���������� � ��������� ��
SELECT * FROM DBA_SEGMENTS;

-- 15. ��������� ������� � ������� ������������
SELECT * FROM USER_RECYCLEBIN;

-- 16. ���������� � ��������� � ��
SELECT * FROM DBA_EXTENTS;

-- 17. ���������� � ���-������ ��
SELECT * FROM V$LOGFILE;

-- 18. ���������� � ������� redo �����
SELECT * FROM V$LOG;

-- 19. ���������� � ���� ������
SELECT * FROM V$DATABASE;

-- 20. ���������� � �������������� redo �����
SELECT * FROM V$ARCHIVED_LOG;

-- 21. ���������� � ����������� ������
SELECT * FROM V$CONTROLFILE;

-- 22. ��������� ������������ ��
SELECT * FROM V$PARAMETER;

-- 23. ������������ � �������� ����� ���� �������
SELECT * FROM V$PWFILE_USERS;

-- 24. ��������������� ����������
SELECT * FROM V$DIAG_INFO;

-- 25. ���������� � SGA
SELECT * FROM V$SGA;

-- 26. ������������ ���������� SGA
SELECT * FROM V$SGA_DYNAMIC_COMPONENTS;

-- 27. ��������� ������ � SGA
SELECT * FROM V$SGA_DYNAMIC_FREE_MEMORY;

-- 28. ��������� ������������ ��
SELECT * FROM V$PARAMETER;

-- 29. ������� ������ � ��
SELECT * FROM V$SESSION;

-- 30. ������� ��������
SELECT * FROM V$BGPROCESS;

-- 31. ����������
SELECT * FROM V$DISPATCHER;

-- 32. ��������� �������
SELECT * FROM V$SERVICES;

-- 33. ����, ����������� �������������
SELECT * FROM DBA_ROLE_PRIVS;

-- 34. ������������ � ��
SELECT * FROM ALL_USERS;

-- 35. ���������� � ���������, ��������� ������������
SELECT * FROM ALL_SEGMENTS;

--------------------------

--------------------Task_1------------------� 
// �������: ������� ��� ������� �� �������������, ������� �������� ���������� ��� ���� �������� ���� ������, ��������� ������������. ��� �������� � ������� 
// �������: 
select * from all_objects where object_type = 'TABLE'; 
 
--------------------Task_2------------------� 
// �������: ������� ��� ������� � ������������������� ��������� (�� �����������). �������� ��� ������� � ��� ������� 
// �������: 
select table_name, index_name from dba_indexes where index_type = 'NONCLUSTERED' and owner = 'SCOTT'; 
 
--------------------Task_3------------------� 
// �������: �������� ������ ��� ������ ���� ���������, ��������� � ��������� ������������ 'SYS'. �������� ��� ��������, ��� ������� � ��� ������� 
// �������: 
select trigger_name, table_name, triggering_event from dba_triggers where owner = 'SYS'; 
 
--------------------Task_4------------------� 
// �������: ������� ���������� � ��������������, ��������� ������� ������������� 
// �������: 
select view_name from user_views; 
 
--------------------Task_5------------------� 
// �������: ������� ��� �������������, ������������� ������������ 'SCOTT'. �������� ��� ������������� � SQL-������, �� �������� ��� ������� 
// �������: 
select view_name, text from dba_views where owner = 'SCOTT'; 
 
--------------------Task_6------------------� 
// �������: �������� ������ ���� �������� ��� ������ �������, ������������� �������� ������������ 
// �������: 
select index_name, table_name from user_indexes; 
 
--------------------Task_7------------------� 
// �������: ����� ��� ������������� ������������ 
// �������: 
select view_name from user_views; 
 
--------------------Task_8------------------� 
// �������: �������� ��� ������� ������������ 
// �������: 
select table_name from user_tables; 
 
--------------------Task_9------------------� 
// �������: �������� ������, ������� ������� ����� � ���� ���� �������� (�������, �������, �������������), ������������� �������� ������������ 
// �������: 
select object_name, object_type from user_objects; 
 
 
-------------------Task_10------------------� 
// �������: ������� ��� ������ �� ������� ������, ��������������� ����� ��������� �������������, ������� �������� ���������� � ���� �������������� � �������� ������, ��������� � ���� ������ 
// �������: 
select * from dictionary;