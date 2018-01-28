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

#include "AP_[CLASS_PREFIX].h"
#include "AP_[CLASS_PREFIX]_Backend.h"
#include "AP_[CLASS_PREFIX]_Dummy.h"

extern const AP_HAL::HAL& hal;

AP_[CLASS_PREFIX]::AP_[CLASS_PREFIX]()
{}

void AP_[CLASS_PREFIX]::configure(ProcessMode process_mode)
{
    _configure_backends(process_mode);
}

void AP_[CLASS_PREFIX]::update()
{
    if (!_backends) {
        return;
    }

    for (uint8_t i = 0; i < _backend_count; i++) {
        _backends[i]->update();
    }
}

void AP_[CLASS_PREFIX]::_configure_backends()
{
    if (_backends_configuring) {
        return;
    }

    _backends_configuring = true;
#if defined([SHAL_COREDEF])
    _add_backend(AP_[CLASS_PREFIX]_Dummy::configure(*this));
#endif
    _backends_configuring = false;
}

void AP_[CLASS_PREFIX]::_configure_backends(ProcessMode process_mode)
{
    _configure_backends();

    for (uint8_t i = 0; i < _backend_count; i++) {
        _backends[i]->process(process_mode);
    }
}

bool AP_[CLASS_PREFIX]::_add_backend(AP_[CLASS_PREFIX]_Backend *backend)
{
    if (!backend) {
        return false;
    }

    if (_backend_count == [CLASS_PREFIX_DEF]_MAX_BACKENDS) {
        hal.console->printf("[CLASS_PREFIX]: MAX BACKEND REACHED!\n");
    }

    _backends[_backend_count++] = backend;

    return true;
}

#endif

