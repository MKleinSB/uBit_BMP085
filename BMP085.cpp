/**
* Andres Sabas @ The Inventor's House
* https://github.com/sabas1080
* January 12, 2018
* https://github.com/
*
* Development environment specifics:
* Written in Microsoft PXT
* Tested with a BMP085:bit for micro:bit
*
* This code is released under the [MIT License](http://opensource.org/licenses/MIT).
* Please review the LICENSE.md file included with this example. If you have any questions
* or concerns with licensing, please contact techsupport@sparkfun.com.
* Distributed as-is; no warranty is given.
*/


#include "pxt.h"

namespace bmp085 {

/*
* Compensates the pressure value read from the register.  This done in C++ because
* it requires the use of 64-bit signed integers which isn't provided in TypeScript
*/
//%
uint32_t compensatePressure(int32_t b5, int32_t up, int32_t b2Val, int32_t ac2Val, int32_t ac1Val, int32_t ac3Val, int32_t b1Val, int32_t ac4Val, int8_t bmpMode) {
    int32_t  x1, x2, b6, x3, b3, p;
    uint32_t b4, b7;

    /* Pressure compensation */
    b6 = b5 - 4000;
    x1 = (b2Val * ((b6 * b6) >> 12)) >> 11;
    x2 = (ac2Val * b6) >> 11;
    x3 = x1 + x2;
    b3 = (((((int32_t) ac1Val) * 4 + x3) << bmpMode) + 2) >> 2;
    x1 = (ac3Val * b6) >> 13;
    x2 = (b1Val * ((b6 * b6) >> 12)) >> 16;
    x3 = ((x1 + x2) + 2) >> 2;
    b4 = (ac4Val * (uint32_t) (x3 + 32768)) >> 15;
    b7 = ((uint32_t) (up - b3) * (50000 >> bmpMode));

    if (b7 < 0x80000000)
    {
      p = (b7 << 1) / b4;
    }
    else
    {
      p = (b7 / b4) << 1;
    }

    return p;
}

}
