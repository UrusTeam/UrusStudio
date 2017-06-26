@echo off
mkdir ..\..\..\devel\share\urusstudio\lib_finder > nul 2>&1
mkdir ..\..\..\output\share\urusstudio\lib_finder > nul 2>&1
copy /Y lib_finder\*.xml ..\..\..\devel\share\urusstudio\lib_finder > nul 2>&1
copy /Y lib_finder\*.xml ..\..\..\output\share\urusstudio\lib_finder > nul 2>&1
zip -j9 ..\..\..\devel\share\urusstudio\lib_finder.zip manifest.xml
