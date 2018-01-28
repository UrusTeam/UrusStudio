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

class AP_[CLASS_PREFIX]_Backend {
public:

    AP_[CLASS_PREFIX]_Backend(AP_[CLASS_PREFIX] &[CLASS_PREFIX_VARS]);

    // we declare a virtual destructor so that drivers can
    // override with a custom destructor if need be.
    virtual ~AP_[CLASS_PREFIX]_Backend(void) {}

    /** Process the backend.
      * @param  process_mode:
      *         [AutoProcess] - Update process run in the scheduled
      *         callback. This is the default mode.
      *         [LoopProcess] - Update process run not in scheduled
      *         callback. udpate() need to be called in somewhere
      *         to see the action, otherwise nothing happen.
      * @return None.
      */
    virtual void process(AP_[CLASS_PREFIX]::ProcessMode process_mode);

    /** See update function on top class.
      */
    virtual void update();

protected:
    // access to frontend
    AP_[CLASS_PREFIX] &_[CLASS_PREFIX_VARS];
};

#endif
