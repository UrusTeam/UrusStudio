@echo off
md   ..\..\..\devel30_64                                           > nul 2>&1
md   ..\..\..\output30_64                                          > nul 2>&1
md   ..\..\..\devel30_64\share                                     > nul 2>&1
md   ..\..\..\output30_64\share                                    > nul 2>&1
md   ..\..\..\devel30_64\share\urusstudio                          > nul 2>&1
md   ..\..\..\output30_64\share\urusstudio                         > nul 2>&1
md   ..\..\..\devel30_64\share\urusstudio\images                   > nul 2>&1
md   ..\..\..\output30_64\share\urusstudio\images                  > nul 2>&1
md   ..\..\..\devel30_64\share\urusstudio\images\settings          > nul 2>&1
md   ..\..\..\output30_64\share\urusstudio\images\settings         > nul 2>&1
md   ..\..\..\devel30_64\share\urusstudio\images\DoxyBlocks        > nul 2>&1
md   ..\..\..\output30_64\share\urusstudio\images\DoxyBlocks       > nul 2>&1
md   ..\..\..\devel30_64\share\urusstudio\images\DoxyBlocks\16x16  > nul 2>&1
md   ..\..\..\output30_64\share\urusstudio\images\DoxyBlocks\16x16 > nul 2>&1

copy images\*.png       ..\..\..\devel30_64\share\urusstudio\images\DoxyBlocks\        > nul 2>&1
copy images\16x16\*.png ..\..\..\devel30_64\share\urusstudio\images\DoxyBlocks\16x16\  > nul 2>&1
copy *.png              ..\..\..\devel30_64\share\urusstudio\images\settings\          > nul 2>&1

copy images\*.png       ..\..\..\output30_64\share\urusstudio\images\DoxyBlocks\       > nul 2>&1
copy images\16x16\*.png ..\..\..\output30_64\share\urusstudio\images\DoxyBlocks\16x16\ > nul 2>&1
copy *.png              ..\..\..\output30_64\share\urusstudio\images\settings\         > nul 2>&1

exit 0
