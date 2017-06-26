@echo off
del ..\..\..\output31\share\urusstudio\plugins\codesnippets.exe > nul 2>&1
zip -j9 ..\..\..\devel31\share\urusstudio\codesnippets.zip manifest.xml > nul 2>&1
md ..\..\..\devel31\share\urusstudio\images\codesnippets > nul 2>&1
copy .\resources\*.png ..\..\..\devel31\share\urusstudio\images\codesnippets\ > nul 2>&1
md ..\..\..\output31\share\urusstudio\images\codesnippets > nul 2>&1
copy .\resources\*.png ..\..\..\output31\share\urusstudio\images\codesnippets\ > nul 2>&1
