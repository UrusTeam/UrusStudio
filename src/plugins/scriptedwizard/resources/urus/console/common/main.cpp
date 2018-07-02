#include <AP_HAL/AP_HAL.h>
#include "[APP_CLASS_PREFIX].h"

const AP_HAL::HAL& hal = AP_HAL::get_HAL();

static CL[APP_CLASS_PREFIX] [APP_CLASS_PREFIX_VARS]_app;

void CL[APP_CLASS_PREFIX]::setup(void)
{
    hal.console->printf("\nStarting [APP_CLASS_PREFIX_VARS]_app...\n");
}

void CL[APP_CLASS_PREFIX]::loop(void)
{
	cnt++;
    hal.console->printf("\nhello URUS! cnt: %u\n", cnt);
    hal.scheduler->delay(1000);
}

void setup(void);
void loop(void);

void setup(void)
{
    [APP_CLASS_PREFIX_VARS]_app.setup();
}

void loop(void)
{
    [APP_CLASS_PREFIX_VARS]_app.loop();
}

AP_HAL_MAIN();

