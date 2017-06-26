@echo off
cls
md ..\..\..\devel30\share\urusstudio\images\wxsmith > nul 2>&1
md ..\..\..\output30\share\urusstudio\images\wxsmith > nul 2>&1
zip ..\..\..\devel30\share\urusstudio\wxsmith.zip manifest.xml
zip ..\..\..\output30\share\urusstudio\wxsmith.zip manifest.xml
copy wxwidgets\icons\*.png ..\..\..\devel30\share\urusstudio\images\wxsmith\ > nul 2>&1
copy wxwidgets\icons\*.png ..\..\..\output30\share\urusstudio\images\wxsmith\ > nul 2>&1
exit 0
