/**
 * @file
 * @author Kevin Hayes
 * @brief Defines constants, typedefs, and enums.
*/

#ifndef SUBSTD_CONSTANTS_HPP
#define SUBSTD_CONSTANTS_HPP

namespace ss{

///@typedef trig_t Type used for trigonometric functions.
using trig_t = double;

constexpr trig_t PI = 3.14159265358979323846;
constexpr trig_t TAU = 6.28318530717958647692;
constexpr trig_t PI_DIV_180 = 0.01745329251;
constexpr trig_t _180_DIV_PI = 57.2957795131;

enum CORNER{
    BOTTOM_LEFT = 0,
    BOTTOM_RIGHT = 1,
    TOP_LEFT = 2,
    TOP_RIGHT = 3
};

}

#endif