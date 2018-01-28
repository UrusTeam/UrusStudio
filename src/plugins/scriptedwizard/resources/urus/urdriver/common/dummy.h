/***************************************************************
 * Name:      [FILENAME_PREFIX]App.h
 * Purpose:   Defines Application Class
 * Author:    [AUTHOR_NAME] ([AUTHOR_EMAIL])
 * Created:   [NOW]
 * Copyright: [AUTHOR_NAME] ([AUTHOR_WWW])
 * License:
 **************************************************************/

#pragma once

#include <AP_HAL/AP_HAL.h>
#if CONFIG_HAL_BOARD == [HAL_BOARD_CONFIGDEF] && \
    CONFIG_SHAL_CORE == [SHAL_COREDEF]

#include "AP_[CLASS_PREFIX].h"
#include "AP_[CLASS_PREFIX]_Backend.h"

class AP_[CLASS_PREFIX]_Dummy : public AP_[CLASS_PREFIX]_Backend
{
public:
    ~AP_[CLASS_PREFIX]_Dummy();

    /** see process function on backend class
      */
    void process(AP_[CLASS_PREFIX]::ProcessMode process_mode) override;

    /** see update function on top class
      */
    void update() override;

    /** see configure function on top class
      */
    static AP_[CLASS_PREFIX]_Backend *configure(AP_[CLASS_PREFIX] &[CLASS_PREFIX_VARS]);

private:
    AP_[CLASS_PREFIX]_Dummy(AP_[CLASS_PREFIX] &[CLASS_PREFIX_VARS]);

    bool _configure();
    void _process_event();

    uint32_t _now;

    bool _auto_process = false;

};

#endif
