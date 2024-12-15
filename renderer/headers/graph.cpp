#include "./graph.hpp"

ColorRGB::ColorRGB(Uint8 r, Uint8 g, Uint8 b){
    this->r = r;
    this->g = g;
    this->b = b;
}

ColorRGB operator+(const ColorRGB& color, const ColorRGB& color2){
    ColorRGB c;
    c.r = color.r + color2.r;
    c.g = color.g + color2.g;
    c.b = color.b + color2.b;
    return c;
}

ColorRGB operator-(const ColorRGB& color, const ColorRGB& color2){
    ColorRGB c;
    c.r = color.r - color2.r;
    c.g = color.g - color2.g;
    c.b = color.b - color2.b;
    return c;
}

ColorRGB operator*(const int a, const ColorRGB& color){
    ColorRGB c;
    c.r = color.r * a;
    c.g = color.g * a;
    c.b = color.b * a;
    return c;
}

ColorRGB operator*(const ColorRGB& color, const int a){
    ColorRGB c;
    c.r = color.r * a;
    c.g = color.g * a;
    c.b = color.b * a;
    return c;
}

ColorRGB operator/(const ColorRGB& color, int a){
    ColorRGB c;
    c.r = color.r / a;
    c.g = color.g / a;
    c.b = color.b / a;
    return c;
}

bool operator==(const ColorRGB& color, const ColorRGB& color2){
    if(color.r == color2.r && color.g == color2.g && color.b == color2.b) return true;
    else return false;
}
bool operator!=(const ColorRGB& color, const ColorRGB& color2){
    if(color.r == color2.r && color.g == color2.g && color.b == color2.b) return false;
    else return true;
}

Coords operator+(const Coords& coord, const Coords& coord2){
    Coords c;
    c.x  = coord.x + coord2.x;
    c.y = coord.y + coord2.y;
    return c;
}

Coords operator-(const Coords& coord, const Coords& coord2){
    Coords c;
    c.x  = coord.x - coord2.x;
    c.y = coord.y - coord2.y;
    return c;
}

Coords operator*(const double a, const Coords& coord){
    Coords c;
    c.x  = coord.x * a;
    c.y = coord.y * a;
    return c;
}

Coords operator*(const Coords& coord, const double a){
    Coords c;
    c.x  = coord.x * a;
    c.y = coord.y * a;
    return c;
}

Coords operator/(const Coords& coord, const double a){
    Coords c;
    c.x  = coord.x / a;
    c.y = coord.y / a;
    return c;
}

Coords floorCoords(const Coords& coords){
    Coords c;
    c.x = floor(coords.x);
    c.y = floor(coords.y);
    return c;
}

bool operator==(const Coords& coord, const Coords& coord2){
    if(coord.x == coord2.x && coord.y == coord2.y) return true;
    else return false;
}

bool operator!=(const Coords& coord, const Coords& coord2){
    if(coord.x == coord2.x && coord.y == coord2.y) return false;
    else return true;
}

double CoordsDot(Coords& coord, Coords& coord2){
    double s;
    s = coord.x * coord2.x + coord.y * coord.y;
    return s;
}

double CoordsMagnitude(Coords& coord){
    double s;
    s = sqrt(CoordsDot(coord, coord));
    return s;
}
