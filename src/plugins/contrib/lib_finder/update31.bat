@echo off
mkdir ..\..\..\devel31\share\urusstudio\lib_finder > nul 2>&1
mkdir ..\..\..\output31\share\urusstudio\lib_finder > nul 2>&1
copy /Y lib_finder\*.xml ..\..\..\devel31\share\urusstudio\lib_finder > nul 2>&1
copy /Y lib_finder\*.xml ..\..\..\output31\share\urusstudio\lib_finder > nul 2>&1
zip -j9 ..\..\..\devel31\share\urusstudio\lib_finder.zip manifest.xml
