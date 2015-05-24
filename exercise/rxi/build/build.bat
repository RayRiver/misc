@echo off

set DIR=%~dp0

if "%LOVE2D_ROOT%" NEQ "" goto BUILD_GAME

echo please set LOVE2D_ROOT enviornment
goto END_SCRIPT

:BUILD_GAME
echo ================================ creating temp directory...
del /F /S /Q "%DIR%\temp\*"
rd /Q /S "%DIR%\temp"
md "%DIR%\temp"

echo ================================ zipping resources...
"%DIR%\7z.exe" a "%DIR%\temp\game.love" "%DIR%\..\project\*" -tzip

echo ================================ creating publish directory...
del /F /S /Q "%DIR%\..\publish\*"
rd /Q /S "%DIR%\..\publish"
md "%DIR%\..\publish"

echo ================================ combining executable file...
copy /b "%LOVE2D_ROOT%\love.exe"+"%DIR%temp\game.love" "%DIR%\..\publish\game.exe"

echo ================================ copying dlls...
copy "%LOVE2D_ROOT%\DevIL.dll" "%DIR%\..\publish\"
copy "%LOVE2D_ROOT%\love.dll" "%DIR%\..\publish\"
copy "%LOVE2D_ROOT%\lua51.dll" "%DIR%\..\publish\"
copy "%LOVE2D_ROOT%\mpg123.dll" "%DIR%\..\publish\"
copy "%LOVE2D_ROOT%\msvcp120.dll" "%DIR%\..\publish\"
copy "%LOVE2D_ROOT%\msvcr120.dll" "%DIR%\..\publish\"
copy "%LOVE2D_ROOT%\OpenAL32.dll" "%DIR%\..\publish\"
copy "%LOVE2D_ROOT%\SDL2.dll" "%DIR%\..\publish\"
copy "%LOVE2D_ROOT%\license.txt" "%DIR%\..\publish\"

goto END_SCRIPT

:END_SCRIPT
