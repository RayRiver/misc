@echo off

set DIR=%~dp0

if "%LOVE2D_ROOT%" NEQ "" goto RUN_GAME

echo please set LOVE2D_ROOT enviornment
goto END_SCRIPT

:RUN_GAME
"%LOVE2D_ROOT%\love.exe" "%DIR%\..\sample"
goto END_SCRIPT

:END_SCRIPT
