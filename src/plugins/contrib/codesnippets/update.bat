@echo off
del ..\..\..\output\share\urusstudio\plugins\codesnippets.exe > nul 2>&1
zip -j9 ..\..\..\devel\share\urusstudio\codesnippets.zip manifest.xml > nul 2>&1
md ..\..\..\devel\share\urusstudio\images\codesnippets > nul 2>&1
copy .\resources\*.png ..\..\..\devel\share\urusstudio\images\codesnippets\ > nul 2>&1
md ..\..\..\output\share\urusstudio\images\codesnippets > nul 2>&1
copy .\resources\*.png ..\..\..\output\share\urusstudio\images\codesnippets\ > nul 2>&1
