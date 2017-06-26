@echo off
md ..\..\..\devel\share\urusstudio\images\ThreadSearch > nul 2>&1
md ..\..\..\output\share\urusstudio\images\ThreadSearch > nul 2>&1
md ..\..\..\devel\share\urusstudio\images\ThreadSearch\16x16 > nul 2>&1
md ..\..\..\output\share\urusstudio\images\ThreadSearch\16x16 > nul 2>&1
md ..\..\..\devel\share\urusstudio\images\ThreadSearch\22x22 > nul 2>&1
md ..\..\..\output\share\urusstudio\images\ThreadSearch\22x22 > nul 2>&1
md ..\..\..\devel\share\urusstudio\images\settings > nul 2>&1
md ..\..\..\output\share\urusstudio\images\settings > nul 2>&1
copy .\resources\images\*.png ..\..\..\devel\share\urusstudio\images\ThreadSearch\ > nul 2>&1
copy .\resources\images\16x16\*.png ..\..\..\devel\share\urusstudio\images\ThreadSearch\16x16\ > nul 2>&1
copy .\resources\images\22x22\*.png ..\..\..\devel\share\urusstudio\images\ThreadSearch\22x22\ > nul 2>&1
copy .\resources\images\*.png ..\..\..\output\share\urusstudio\images\ThreadSearch\ > nul 2>&1
copy .\resources\images\16x16\*.png ..\..\..\output\share\urusstudio\images\ThreadSearch\16x16\ > nul 2>&1
copy .\resources\images\22x22\*.png ..\..\..\output\share\urusstudio\images\ThreadSearch\22x22\ > nul 2>&1
copy .\resources\*.png ..\..\..\devel\share\urusstudio\images\settings\ > nul 2>&1
copy .\resources\*.png ..\..\..\output\share\urusstudio\images\settings\ > nul 2>&1
exit 0

