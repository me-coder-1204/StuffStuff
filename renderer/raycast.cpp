#include "raycast.hpp"

Map::Map(){
    width = 24;
    height = 24;
    mapArray = (int**) malloc(height * sizeof(int*));
    for(int i=0;i<width;i++){
        mapArray[i] = (int*) malloc(width * sizeof(int));
    }
    std::cout << "Memory for map has been allocated...\n";
}

// Map::~Map(){
//     std::cout << "Freeing Map Memory\n";
//     for(int i=0;i<width;i++){
//         free(mapArray[i]);
//     }
//     free(mapArray);
// }

void Map::importMapFromTxt(std::string file_name){

    std::ifstream fp(file_name);
    if (! fp) {
        std::cout << "Error, file couldn't be opened" << std::endl; 
        return; 
    }

    for(int row = 0; row < height; row++) {  // stop loops if nothing to read
        for(int column = 0; column < width; column++){
            if ( ! fp ) {
            std::cout << "Error reading file for element " << row << "," << column << std::endl; 
            return; 
            }
            fp >> mapArray[row][column];
        }
    }
}

// std::vector<char> readBMP(const std::string &file)
// {
//     static constexpr size_t HEADER_SIZE = 54;

//     std::ifstream bmp(file, std::ios::binary);

//     std::array<char, HEADER_SIZE> header;
//     bmp.read(header.data(), header.size());

//     auto fileSize = *reinterpret_cast<uint32_t *>(&header[2]);
//     auto dataOffset = *reinterpret_cast<uint32_t *>(&header[10]);
//     auto width = *reinterpret_cast<uint32_t *>(&header[18]);
//     auto height = *reinterpret_cast<uint32_t *>(&header[22]);
//     auto depth = *reinterpret_cast<uint16_t *>(&header[28]);

//     std::cout << "fileSize: " << fileSize << std::endl;
//     std::cout << "dataOffset: " << dataOffset << std::endl;
//     std::cout << "width: " << width << std::endl;
//     std::cout << "height: " << height << std::endl;
//     std::cout << "depth: " << depth << "-bit" << std::endl;

//     std::vector<char> img(dataOffset - HEADER_SIZE);
//     bmp.read(img.data(), img.size());

//     auto dataSize = ((width * 3 + 3) & (~3)) * height;
//     img.resize(dataSize);
//     bmp.read(img.data(), img.size());

//     char temp = 0;

//     for (auto i = dataSize - 4; i >= 0; i -= 3)
//     {
//         temp = img[i];
//         img[i] = img[i+2];
//         img[i+2] = temp;

//         std::cout << "R: " << int(img[i] & 0xff) << " G: " << int(img[i+1] & 0xff) << " B: " << int(img[i+2] & 0xff) << std::endl;
//     }

//     return img;
// }