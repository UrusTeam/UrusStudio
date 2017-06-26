@echo off
md   ..\..\..\devel30                                           > nul 2>&1
md   ..\..\..\output30                                          > nul 2>&1
md   ..\..\..\devel30\share                                     > nul 2>&1
md   ..\..\..\output30\share                                    > nul 2>&1
md   ..\..\..\devel30\share\urusstudio                          > nul 2>&1
md   ..\..\..\output30\share\urusstudio                         > nul 2>&1
md   ..\..\..\devel30\share\urusstudio\images                   > nul 2>&1
md   ..\..\..\output30\share\urusstudio\images                  > nul 2>&1
md   ..\..\..\devel30\share\urusstudio\images\settings          > nul 2>&1
md   ..\..\..\output30\share\urusstudio\images\settings         > nul 2>&1
md   ..\..\..\devel30\share\urusstudio\images\DoxyBlocks        > nul 2>&1
md   ..\..\..\output30\share\urusstudio\images\DoxyBlocks       > nul 2>&1
md   ..\..\..\devel30\share\urusstudio\images\DoxyBlocks\16x16  > nul 2>&1
md   ..\..\..\output30\share\urusstudio\images\DoxyBlocks\16x16 > nul 2>&1

copy images\*.png       ..\..\..\devel30\share\urusstudio\images\DoxyBlocks\        > nul 2>&1
copy images\16x16\*.png ..\..\..\devel30\share\urusstudio\images\DoxyBlocks\16x16\  > nul 2>&1
copy *.png              ..\..\..\devel30\share\urusstudio\images\settings\          > nul 2>&1

copy images\*.png       ..\..\..\output30\share\urusstudio\images\DoxyBlocks\       > nul 2>&1
copy images\16x16\*.png ..\..\..\output30\share\urusstudio\images\DoxyBlocks\16x16\ > nul 2>&1
copy *.png              ..\..\..\output30\share\urusstudio\images\settings\         > nul 2>&1

exit 0
