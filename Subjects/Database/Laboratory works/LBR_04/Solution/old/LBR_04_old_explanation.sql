--------------------Task_1--------------------
select tablespace_name, contents, status
from dba_tablespaces;
--------------------Task_2--------------------
select file_name, tablespace_name, bytes, status from dba_data_files;
select file_name, tablespace_name, bytes, status from dba_temp_files;
//DBA_DATA_FILES � DBA_TEMP_FILES � �������������, ������� �������� ���������� 
//� ���������� ������ ���� ������ ��� ������������ � ��������� ��������� ����������� ��������������.
--------------------Task_3--------------------
select group#, thread#, sequence#, bytes, members, archived, status from v$log;
select group#, thread#, sequence# from v$log where status = 'CURRENT';
//group# -- ����� ������
//thread# -- ����� ������ (������������ � real application clusters)
//sequence# -- ����� ������������������ �������
//bytes -- ������ ������� � ������
//members -- ���������� ������ � ������ (������� ������ ����������� ������)
//archived -- ��� �� ������ ������������� (��/���)
//status -- ������ ������� (current, innactive, active)
//v$log -- ���������� ���������� ����� ������� �� ������������ �����.
--------------------Task_4--------------------
select group#, member from v$logfile;
//v$logfile � �������������, ������� �������� ���������� � ���������� ������ ��� ������ ������ �������� �������.
--------------------Task_5--------------------
SELECT GROUP#, SEQUENCE#, STATUS FROM V$LOG WHERE STATUS = 'CURRENT';
SELECT CURRENT_SCN FROM V$DATABASE; 
ALTER SYSTEM SWITCH LOGFILE;
//SCN -- (System Change Number) ���������� ������������� � Oracle Database, 
//������� ������������ ������������������ ��������� � ���� ������. 
//SCN ������������� ������ ���, ����� ���������� ��������, ���������� ������ (��������, �������, ����������, �������� ��� ������ ����������).
--------------------Task_6--------------------
select group#, thread#, sequence#, status from v$log;

alter database add logfile group 4
('D:\User\Desktop\StudyAtBSTU\Course_3\Semester5\Subjects\Database\Laboratory works\LBR_04\Solution\redo01.log',
 'D:\User\Desktop\StudyAtBSTU\Course_3\Semester5\Subjects\Database\Laboratory works\LBR_04\Solution\redo02.log',
 'D:\User\Desktop\StudyAtBSTU\Course_3\Semester5\Subjects\Database\Laboratory works\LBR_04\Solution\redo03.log') size 50m;
 
select group#, member from v$logfile; -- ����������, ��� ����� ������� ������������� �������
alter system switch logfile; -- ������������ ������� �������
select group#, thread#, sequence#, status from v$log; -- �������� ������� ������ ��������
select current_scn from v$database; -- �������� SCN
--------------------Task_7--------------------
alter system checkpoint global;

alter database drop logfile group 4;

//����� ������� � cmd ����� ���������:
//del "D:\User\Desktop\StudyAtBSTU\Course_3\Semester5\Subjects\Database\Laboratory works\LBR_04\Solution\redo01.log"
//del "D:\User\Desktop\StudyAtBSTU\Course_3\Semester5\Subjects\Database\Laboratory works\LBR_04\Solution\redo02.log"
//del "D:\User\Desktop\StudyAtBSTU\Course_3\Semester5\Subjects\Database\Laboratory works\LBR_04\Solution\redo03.log"
--------------------Task_8--------------------
select log_mode from v$database; //���� ����������� ����� ARCHIVELOG, �� ������������� ��������, ���� �� NOARCHIVELOG � ������������� ���������
--------------------Task_9--------------------
select max(sequence#) from v$archived_log; //������� ����� ���������� ���������� ��������� ����
-------------------Task_10--------------------
//������� ���� ������ � ����� MOUNT
shutdown immediate;
startup mount;

alter database archivelog; //��������� �������������

alter database open;
-------------------Task_11--------------------
-------------------Task_12--------------------
-------------------Task_13--------------------
-------------------Task_14--------------------