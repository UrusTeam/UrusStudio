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

#include "AP_[CLASS_PREFIX]_Dummy.h"

#define MYLED 13

extern const AP_HAL::HAL& hal;

AP_[CLASS_PREFIX]_Dummy::AP_[CLASS_PREFIX]_Dummy(AP_[CLASS_PREFIX] &[CLASS_PREFIX_VARS]) :
    AP_[CLASS_PREFIX]_Backend([CLASS_PREFIX_VARS])
{
}

AP_[CLASS_PREFIX]_Dummy::~AP_[CLASS_PREFIX]_Dummy()
{}

void AP_[CLASS_PREFIX]_Dummy::process(AP_[CLASS_PREFIX]::ProcessMode process_mode)
{
    hal.gpio->pinMode(MYLED, HAL_GPIO_OUTPUT);
    hal.gpio->write(MYLED, 1);
    _now = AP_HAL::micros();

    switch (process_mode) {
    case AP_[CLASS_PREFIX]::LoopProcess:
        _auto_process = false;
        break;
    case AP_[CLASS_PREFIX]::AutoProcess:
        _auto_process = true;
        hal.scheduler->register_timer_process(FUNCTOR_BIND_MEMBER(&AP_[CLASS_PREFIX]_Dummy::_process_event, void));
        break;
    default:
        break;
    }

    hal.scheduler->delay(100);
}

void AP_[CLASS_PREFIX]_Dummy::update()
{
    if (_auto_process) {
        return;
    }

    _process_event();
}

AP_[CLASS_PREFIX]_Backend *AP_[CLASS_PREFIX]_Dummy::configure(AP_[CLASS_PREFIX] &[CLASS_PREFIX_VARS])
{
    AP_[CLASS_PREFIX]_Dummy *dummy = new AP_[CLASS_PREFIX]_Dummy([CLASS_PREFIX_VARS]);

    if (!dummy || !dummy->_configure()) {
        delete dummy;
        return nullptr;
    }

    return dummy;
}


void AP_[CLASS_PREFIX]_Dummy::_process_event()
{
    if ((AP_HAL::micros() - _now) > 10000LU)
    {
        _now = AP_HAL::micros();
        hal.gpio->toggle(MYLED);
    }
}

bool AP_[CLASS_PREFIX]_Dummy::_configure()
{

    hal.gpio->pinMode(MYLED, HAL_GPIO_OUTPUT);
    hal.gpio->write(MYLED, 1);

    return true;
}

#endif

