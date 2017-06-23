@echo off
cls
md ..\..\..\devel31\share\urusstudio\images\wxsmith > nul 2>&1
md ..\..\..\output31\share\urusstudio\images\wxsmith > nul 2>&1
zip ..\..\..\devel31\share\urusstudio\wxsmith.zip .\manifest.xml
zip ..\..\..\output31\share\urusstudio\wxsmith.zip .\manifest.xml
copy /y wxwidgets\icons\*.png ..\..\..\devel31\share\urusstudio\images\wxsmith\ > nul 2>&1
copy /y wxwidgets\icons\*.png ..\..\..\output31\share\urusstudio\images\wxsmith\ > nul 2>&1
exit 0
