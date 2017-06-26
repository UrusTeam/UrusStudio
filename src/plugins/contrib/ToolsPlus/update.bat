@echo off
md ..\..\..\devel\share\urusstudio\images\settings > nul 2>&1
md ..\..\..\output\share\urusstudio\images\settings > nul 2>&1
copy .\Resources\*.png ..\..\..\devel\share\urusstudio\images\settings\ > nul 2>&1
copy .\Resources\*.png ..\..\..\output\share\urusstudio\images\settings\ > nul 2>&1
exit 0
