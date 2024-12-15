#pragma once

#include<SDL2/SDL.h>
#include<math.h>
#include<vector>
#include<iostream>

// struct ColorRGB8bit;


struct ColorRGB
{
    int r;
    int g;
    int b;

    ColorRGB(Uint8 r, Uint8 g, Uint8 b);

    ColorRGB() = default;
};

ColorRGB operator+(const ColorRGB& color, const ColorRGB& color2);
ColorRGB operator-(const ColorRGB& color, const ColorRGB& color2);
ColorRGB operator*(const int a, const ColorRGB& color);
ColorRGB operator*(const ColorRGB& color, const int a);
ColorRGB operator/(const ColorRGB& color, const int a);

bool operator==(const ColorRGB& color, const ColorRGB& color2);
bool operator!=(const ColorRGB& color, const ColorRGB& color2);

static const ColorRGB RGB_BLACK (0, 0, 0);
static const ColorRGB RGB_WHITE (255, 255, 255);
static const ColorRGB RGB_RED (255, 0, 0);
static const ColorRGB RGB_GREEN (0, 255, 0);
static const ColorRGB RGB_BLUE (0, 0, 255);
static const ColorRGB RGB_CYAN (0, 255, 255);
static const ColorRGB RGB_YELLOW (255, 255, 0);
static const ColorRGB RGB_GRAY (128, 128, 128);
static const ColorRGB RGB_MAROON (128, 0, 0);
static const ColorRGB RGB_DARKGREEN (0, 128, 0);
static const ColorRGB RGB_NAVY (0, 0, 128);
static const ColorRGB RGB_OLIVE (128, 128, 0);
static const ColorRGB RGB_TEAL (0, 128, 128);
static const ColorRGB RGB_PURPLE (0, 0, 128);

// void drawVertLine_(SDL_Renderer* renderer, int x, int y1, int y2);
struct Coords{
    double x;
    double y;
};

Coords operator+(const Coords& coord, const Coords& coord2);
Coords operator-(const Coords& coord, const Coords& coord2);
Coords operator*(const double a, const Coords& coord);
Coords operator*(const Coords& coord, const double a);
Coords operator/(const Coords& coord, const double a);

Coords floorCoords(const Coords& coord);

bool operator==(const Coords& coord, const Coords& coord2);
bool operator!=(const Coords& coord, const Coords& coord2);

double CoordsDot(Coords& coord, Coords& coord2);
double CoordsMagnitude(Coords& coord);
