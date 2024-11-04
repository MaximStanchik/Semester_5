--------------------Task_1-------------------- ���������� ����� ������ ������� SGA
select * from V$SGA;
select SUM(value) from v$sga;
--------------------Task_2-------------------- ���������� ������� ������� �������� ����� SGA
select * from v$sga_dynamic_components where current_size > 0;
--------------------Task_3-------------------- ���������� ������� ������� ��� ������� ����
select component, granule_size from v$sga_dynamic_components where current_size > 0;
--------------------Task_4-------------------- ���������� ����� ��������� ��������� ������ � SGA
select current_size from v$sga_dynamic_free_memory;
--------------------Task_5-------------------- ���������� ������������ � ������� ������ ������� SGA
 SELECT value FROM v$parameter WHERE name = 'sga_target';
 SELECT value FROM v$parameter WHERE name = 'sga_max_size';
--------------------Task_6-------------------- ���������� ������� ����� ���P, DEFAULT � RECYCLE ��������� ����
select component, current_size, min_size, MAX_SIZE from v$sga_dynamic_components
where component='KEEP buffer cache' or component='DEFAULT buffer cache' or component='RECYCLE buffer cache';
--------------------Task_7-------------------- �������� �������, ������� ����� ���������� � ��� ���P
create table TableLab5 (
        id number,
        name varchar2(50)
    ) storage (buffer_pool keep) tablespace users;

    select segment_name, segment_type, tablespace_name, buffer_pool
    from user_segments
    where segment_name = 'TABLELAB5';

    drop table TableLab5;
--------------------Task_8-------------------- �������� �������, ������� ����� ������������ � ���� DEFAULT
create table cachedTableLab5 (
      id number,
      name varchar2(50),
      age number
    ) cache;

    select segment_name, segment_type, tablespace_name, buffer_pool
    from user_segments
    where segment_name = 'CACHEDTABLELAB5';

drop table cachedTableLab5;
--------------------Task_9-------------------- ������� ������ ������ �������� �������
select value from v$parameter where name = 'log_buffer';
--------------------Task_10-------------------- ������� ������ ��������� ������ � ������� ����
select POOL, bytes/1024/1024 AS "Free Memory (MB)"
from V$SGASTAT
where POOL = 'large pool' AND name = 'free memory';
--------------------Task_11-------------------- ���������� ������ ������� ���������� � ���������
select username, service_name, server, osuser, machine, program, STATE
    from v$session
    where username is not null;
--------------------Task_12-------------------- �������� ������ ������ ���������� � ��������� ����� ������� ���������
select name, description FROM v$bgprocess;
--------------------Task_13-------------------- �������� ������ ���������� � ��������� ����� ��������� ���������
select * from v$process where addr != '00';
--------------------Task_14-------------------- ����������, ������� ��������� DBWn �������� � ��������� ������
select count(*) from v$process where addr!= '00' and pname like 'DBW%';
--------------------Task_15-------------------- ���������� ������� (����� ����������� ����������)
select * from v$active_services;
--------------------Task_16-------------------- �������� ��������� ��� ��������� �����������
select * from v$dispatcher;
--------------------Task_17-------------------- ������� � ������ Windows-�������� ������, ����������� ������� LISTENER
select * from v$services;
--------------------Task_18-------------------- ����������������� � �������� ���������� ����� LISTENER.ORA
----�������� � report.docx
--------------------Task_19-------------------- ��������� ������� lsnrctl � �������� �� �������� �������
----�������� � report.docx
--------------------Task_20-------------------- �������� ������ ����� ��������, ������������� ��������� LISTENER
----�������� � report.docx