@echo off
cls
md ..\..\..\devel\share\urusstudio\images\wxsmith > nul 2>&1
md ..\..\..\output\share\urusstudio\images\wxsmith > nul 2>&1
zip ..\..\..\devel\share\urusstudio\wxsmith.zip manifest.xml
zip ..\..\..\output\share\urusstudio\wxsmith.zip manifest.xml
copy wxwidgets\icons\*.png ..\..\..\devel\share\urusstudio\images\wxsmith\ > nul 2>&1
copy wxwidgets\icons\*.png ..\..\..\output\share\urusstudio\images\wxsmith\ > nul 2>&1
exit 0
