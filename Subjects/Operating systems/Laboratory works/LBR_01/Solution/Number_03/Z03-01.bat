@echo off
chcp 65001 > nul
echo Имя компьютера (COMPUTERNAME): %COMPUTERNAME%
echo Операционная система (OS): %OS%
echo Идентификатор процессора (PROCESSOR_IDENTIFIER): %PROCESSOR_IDENTIFIER%
echo Количество процессоров (NUMBER_OF_PROCESSORS): %NUMBER_OF_PROCESSORS%
echo Имя пользователя (USERNAME): %USERNAME%
pause