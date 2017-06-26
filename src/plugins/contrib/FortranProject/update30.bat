@echo off
md   ..\..\..\devel30                                           > nul 2>&1
md   ..\..\..\output30                                          > nul 2>&1
md   ..\..\..\devel30\share                                     > nul 2>&1
md   ..\..\..\output30\share                                    > nul 2>&1
md   ..\..\..\devel30\share\urusstudio                          > nul 2>&1
md   ..\..\..\output30\share\urusstudio                         > nul 2>&1
md   ..\..\..\devel30\share\urusstudio\images                   > nul 2>&1
md   ..\..\..\output30\share\urusstudio\images                  > nul 2>&1
md   ..\..\..\devel30\share\urusstudio\images\fortranproject    > nul 2>&1
md   ..\..\..\output30\share\urusstudio\images\fortranproject   > nul 2>&1

copy images\fortranproject\*.*       ..\..\..\devel30\share\urusstudio\images\fortranproject\     > nul 2>&1
copy images\fortranproject\*.*       ..\..\..\output30\share\urusstudio\images\fortranproject\    > nul 2>&1

exit 0
