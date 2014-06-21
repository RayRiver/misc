@echo off

set PROJECT_HOME=%~dp0\..

bin\pack_files.bat -i %PROJECT_HOME%\res -o %PROJECT_HOME%\resource -m files -ek MYKEY -es XXTEA

