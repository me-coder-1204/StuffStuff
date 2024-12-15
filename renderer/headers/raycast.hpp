#pragma once

#include<fstream>
#include<iostream>
#include<vector>
#include<array>
#include "graph.hpp"

class Map
{   
    public:
        Map();
        ~Map()=default;

        int width;
        int height;
        int** mapArray;

        int textureCount;
        Coords textureSize;

        std::vector<std::vector<ColorRGB>> textureSet;

        void importMapFromTxt(std::string file_name);
        std::vector<ColorRGB> readBMP(const std::string &file);
        void addTexture(const std::string& file);
};