@echo off
chcp 65001 > nul
echo Создан новый каталог с именем "TXT"
mkdir TXT
echo Перемещены все файлы с расширением .txt в каталог "TXT"
move *.txt TXT
pause