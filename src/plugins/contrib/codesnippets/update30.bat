@echo off
del ..\..\..\output30\share\urusstudio\plugins\codesnippets.exe > nul 2>&1
zip -j9 ..\..\..\devel30\share\urusstudio\codesnippets.zip manifest.xml > nul 2>&1
md ..\..\..\devel30\share\urusstudio\images\codesnippets > nul 2>&1
copy .\resources\*.png ..\..\..\devel30\share\urusstudio\images\codesnippets\ > nul 2>&1
md ..\..\..\output30\share\urusstudio\images\codesnippets > nul 2>&1
copy .\resources\*.png ..\..\..\output30\share\urusstudio\images\codesnippets\ > nul 2>&1
