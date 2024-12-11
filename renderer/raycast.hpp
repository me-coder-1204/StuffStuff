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

        // std::vector<std::vector<ColorRGB>> texture;

        void importMapFromTxt(std::string file_name);
};