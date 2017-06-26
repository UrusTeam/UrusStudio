@echo off
md   ..\..\..\devel                                           > nul 2>&1
md   ..\..\..\output                                          > nul 2>&1
md   ..\..\..\devel\share                                     > nul 2>&1
md   ..\..\..\output\share                                    > nul 2>&1
md   ..\..\..\devel\share\urusstudio                          > nul 2>&1
md   ..\..\..\output\share\urusstudio                         > nul 2>&1
md   ..\..\..\devel\share\urusstudio\images                   > nul 2>&1
md   ..\..\..\output\share\urusstudio\images                  > nul 2>&1
md   ..\..\..\devel\share\urusstudio\images\settings          > nul 2>&1
md   ..\..\..\output\share\urusstudio\images\settings         > nul 2>&1
md   ..\..\..\devel\share\urusstudio\images\DoxyBlocks        > nul 2>&1
md   ..\..\..\output\share\urusstudio\images\DoxyBlocks       > nul 2>&1
md   ..\..\..\devel\share\urusstudio\images\DoxyBlocks\16x16  > nul 2>&1
md   ..\..\..\output\share\urusstudio\images\DoxyBlocks\16x16 > nul 2>&1

copy images\*.png       ..\..\..\devel\share\urusstudio\images\DoxyBlocks\        > nul 2>&1
copy images\16x16\*.png ..\..\..\devel\share\urusstudio\images\DoxyBlocks\16x16\  > nul 2>&1
copy *.png              ..\..\..\devel\share\urusstudio\images\settings\          > nul 2>&1

copy images\*.png       ..\..\..\output\share\urusstudio\images\DoxyBlocks\       > nul 2>&1
copy images\16x16\*.png ..\..\..\output\share\urusstudio\images\DoxyBlocks\16x16\ > nul 2>&1
copy *.png              ..\..\..\output\share\urusstudio\images\settings\         > nul 2>&1

exit 0
