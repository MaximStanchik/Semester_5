@echo off
chcp 65001 > nul

if "%1"=="" (
    set /p extension=Введите расширение файла: 
) else (
    set extension=%1
)

if "%extension%"=="" (
    echo Не указано расширение файла.
    pause
    exit /b
)

echo Создан новый каталог с именем, соответствующим переданному расширению
mkdir %extension% 2>nul

echo Все файлы с указанным расширением перемещены в созданный каталог
move *.%extension% %extension%

pause