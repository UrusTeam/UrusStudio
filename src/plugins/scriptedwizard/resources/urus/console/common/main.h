#pragma once

/**
    This is the [APP_CLASS_PREFIX] header main object class
    and it's the standard urus's app initialization structure
    model.
    Only setup() and loop() is required to run your app.
*/

#include <AP_HAL/AP_HAL.h>

class CL[APP_CLASS_PREFIX] {
public:

    /** This setup is called only one time at startup
      * on the frontend.
      * you can configure or setup the IO environments.
      * After setup loop is called forever.
      */
    void setup(void);

    /** This loop is called everytime on the main loop
      * frontend.
      */
    void loop(void);

private:

	/** This private variable is used on the frontend
      * as an example test.
      */
    uint16_t cnt;

};

