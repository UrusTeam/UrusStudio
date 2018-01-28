/***************************************************************
 * Name:      [FILENAME_PREFIX]App.h
 * Purpose:   Defines Application Class
 * Author:    [AUTHOR_NAME] ([AUTHOR_EMAIL])
 * Created:   [NOW]
 * Copyright: [AUTHOR_NAME] ([AUTHOR_WWW])
 * License:
 **************************************************************/

#include <AP_HAL/AP_HAL.h>
#if CONFIG_HAL_BOARD == [HAL_BOARD_CONFIGDEF] && \
    CONFIG_SHAL_CORE == [SHAL_COREDEF]

#include "AP_[CLASS_PREFIX]_Backend.h"

AP_[CLASS_PREFIX]_Backend::AP_[CLASS_PREFIX]_Backend(AP_[CLASS_PREFIX] &[CLASS_PREFIX_VARS]) :
    _[CLASS_PREFIX_VARS]([CLASS_PREFIX_VARS])
{}

void AP_[CLASS_PREFIX]_Backend::process(AP_[CLASS_PREFIX]::ProcessMode process_mode)
{}

void AP_[CLASS_PREFIX]_Backend::update()
{}

#endif

