/*****************************************************************************
FROM "Simple Color Conversions between RGB and HSL/HSV" by Marukrap on github
*****************************************************************************/

#ifndef HSV_H
#define HSV_H

#include <SFML/Graphics/Color.hpp>

#include <tuple>
#include <algorithm> // min, max
#include <cmath>

// HSL/HSV
// H Hue component, range: [0.f, 360.f)
// S Saturation component, range: [0.f, 1.f)
// V Value component, range: [0.f, 1.f)

// sf::Color
// r Red component, range: [0, 255]
// g Green component, range: [0, 255]
// b Blue component, range: [0, 255]

std::tuple<float, float, float> RGBtoHSV(const sf::Color& color);

sf::Color HSVtoRGB(float H, float S, float V);

#endif