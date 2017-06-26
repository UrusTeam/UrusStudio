@echo off
md   ..\..\..\devel                                           > nul 2>&1
md   ..\..\..\output                                          > nul 2>&1
md   ..\..\..\devel\share                                     > nul 2>&1
md   ..\..\..\output\share                                    > nul 2>&1
md   ..\..\..\devel\share\urusstudio                          > nul 2>&1
md   ..\..\..\output\share\urusstudio                         > nul 2>&1
md   ..\..\..\devel\share\urusstudio\images                   > nul 2>&1
md   ..\..\..\output\share\urusstudio\images                  > nul 2>&1
md   ..\..\..\devel\share\urusstudio\images\fortranproject    > nul 2>&1
md   ..\..\..\output\share\urusstudio\images\fortranproject   > nul 2>&1

copy images\fortranproject\*.*       ..\..\..\devel\share\urusstudio\images\fortranproject\     > nul 2>&1
copy images\fortranproject\*.*       ..\..\..\output\share\urusstudio\images\fortranproject\    > nul 2>&1

exit 0
