/**
 * @file
 * @author Kevin Hayes
 * @brief Defines constants, typedefs, and enums.
*/

#ifndef SUBSTD_CONSTANTS_HPP
#define SUBSTD_CONSTANTS_HPP

namespace ss{

constexpr double PI = 3.14159265358979323846;
constexpr double TAU = 6.28318530717958647692;
constexpr double PI_DIV_180 = 0.01745329251;
constexpr double _180_DIV_PI = 57.2957795131;

enum CORNER{
    BOTTOM_LEFT = 0,
    BOTTOM_RIGHT = 1,
    TOP_LEFT = 2,
    TOP_RIGHT = 3
};

}

#endif