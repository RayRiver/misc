@echo off

set PROJECT_HOME=%~dp0\..

bin\compile_scripts.bat -i %PROJECT_HOME%\src -o %PROJECT_HOME%\resource\game.zip -m zip -e xxtea_zip -ek MYKEY -es XXTEA

