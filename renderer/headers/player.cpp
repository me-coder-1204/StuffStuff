#include "player.hpp"
#include<typeinfo>

Player::Player(){
    // m_x = x;
    // m_y = y;
    // // m_direction = {0.0, -1.0};
    // m_direction[0] = -1; m_direction[1] = 0;
    // m_cameraPlane[0] = 0; m_cameraPlane[1] = SDL_tan(33 * 3.1415926 / 180);
    playerPos.x = 12;
    playerPos.y = 12;

    playerDirection.x = -1.0;
    playerDirection.y = 0.0;

    cameraPlane.x = 0.0;
    cameraPlane.y = SDL_tan(33 * 3.1415926 / 180);

    moveSpeed = 5.0;
    rotateSpeed = 2.0;
}

void Player::movePlayer(double delTime){
    const Uint8 * keys = SDL_GetKeyboardState(NULL);

    if(keys[SDL_SCANCODE_UP]){
        playerPos.x += moveSpeed * playerDirection.x * delTime;
        playerPos.y += moveSpeed * playerDirection.y * delTime;
    }

    if(keys[SDL_SCANCODE_DOWN]){
        playerPos.x -= moveSpeed * playerDirection.x * delTime;
        playerPos.y -= moveSpeed * playerDirection.y * delTime;
    }

    if(keys[SDL_SCANCODE_LEFT]){
        Coords dirOld = playerDirection;
        playerDirection.x = dirOld.x * cos(rotateSpeed * delTime) - dirOld.y * sin(rotateSpeed * delTime);
        playerDirection.y = dirOld.x * sin(rotateSpeed * delTime) + dirOld.y * cos(rotateSpeed * delTime);

        Coords planeOld  = cameraPlane;
        cameraPlane.x = planeOld.x * cos(rotateSpeed * delTime) - planeOld.y * sin(rotateSpeed * delTime);
        cameraPlane.y = planeOld.x * sin(rotateSpeed * delTime) + planeOld.y * cos(rotateSpeed * delTime);
    }

    if(keys[SDL_SCANCODE_RIGHT]){
        Coords dirOld = playerDirection;
        playerDirection.x = dirOld.x * cos(-rotateSpeed * delTime) - dirOld.y * sin(-rotateSpeed * delTime);
        playerDirection.y = dirOld.x * sin(-rotateSpeed * delTime) + dirOld.y * cos(-rotateSpeed * delTime);

        Coords planeOld  = cameraPlane;
        cameraPlane.x = planeOld.x * cos(-rotateSpeed * delTime) - planeOld.y * sin(-rotateSpeed * delTime);
        cameraPlane.y = planeOld.x * sin(-rotateSpeed * delTime) + planeOld.y * cos(-rotateSpeed * delTime);
    }
}

void Player::cameraRender(Map map, SDL_Renderer* renderer, int width, int height){
    // int wid = display.w;

    for(int x=0;x<width;x++){
        double cameraX = (2 * x/ (double) width) - 1;
        Coords rayDirection = playerDirection + (cameraPlane * cameraX); 
        // std::cout << rayDirection.x << " " << rayDirection.y<< std::endl;
        Coords mapPos = floorCoords(playerPos);

        Coords sideDist;
        Coords deltaDist = {std::abs(1/rayDirection.x), std::abs(1/rayDirection.y)};
        double perpWallDistance;

        Coords stepDirection;
        int hit = 0;
        int side;

        if(rayDirection.x < 0){
            stepDirection.x = -1;
            sideDist.x = (playerPos.x - mapPos.x) * deltaDist.x;
        }

        if(rayDirection.x > 0){
            stepDirection.x = 1;
            sideDist.x = (1.0 - playerPos.x + mapPos.x) * deltaDist.x;
        }

        if(rayDirection.y < 0){
            stepDirection.y = -1;
            sideDist.y = (playerPos.y - mapPos.y) * deltaDist.y;
        }

        if(rayDirection.y > 0){
            stepDirection.y = 1;
            sideDist.y = (1.0 - playerPos.y + mapPos.y) * deltaDist.y;
        }

        while(!hit){
            if(sideDist.x > sideDist.y){
                sideDist.y += deltaDist.y;
                mapPos.y += stepDirection.y;
                side = 1;
            }
            else{
                sideDist.x += deltaDist.x;
                mapPos.x += stepDirection.x;
                side = 0;
            }
            if(map.mapArray[(int) mapPos.y][(int) mapPos.x]) hit=1;
        }
        // std::cout << "Hit!\n";
        if(!side) perpWallDistance = sideDist.x - deltaDist.x;
        else perpWallDistance = sideDist.y - deltaDist.y;

        int lineHeight = (int) height / perpWallDistance;
        int drawStart = -lineHeight / 2 + height / 2;
        // if(drawStart < 0)drawStart = 0;
        int drawEnd = lineHeight / 2 + height / 2;
        // if(drawEnd >= height)drawEnd = height - 1;

        double wallX;
        if(!side) wallX = playerPos.y + perpWallDistance * rayDirection.y;
        else wallX = playerPos.x + perpWallDistance * rayDirection.x;

        wallX -= floor(wallX);

        int pixelCol = floor(map.textureSize.x * wallX);

        // ColorRGB color;
        // switch (map.mapArray[(int)mapPos.y][(int) mapPos.x])
        // {
        // case 1:
        //     color = RGB_RED;
        //     break;
        
        // case 2:
        //     color = RGB_BLUE;
        //     break;
        // case 3:
        //     color = RGB_GREEN;
        //     break;

        // case 4:
        //     color = RGB_NAVY;
        //     break;

        // case 5:
        //     color = RGB_GRAY;
        //     break;
        
        // default:
        //     color = RGB_WHITE;
        //     break;
        // }

        // if(side==1) color = color/2;
        // SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);

        int textureNum = map.mapArray[(int)mapPos.y][(int)mapPos.x] - 1;
        std::vector texture = map.textureSet.at(textureNum);

        for(int y = drawStart; y<drawEnd; y++){
            if(y < 0 || y > height) continue;
            int pixelRow = floor(((double)(y-drawStart)/lineHeight) * map.textureSize.y);
            // std::cout << pixelRow <<std::endl;
            ColorRGB pixelColor = texture.at(map.textureSize.x * pixelRow + pixelCol);
            // std::cout << typeid(pixelColor.r).name() <<std::endl;
            if(side==1) pixelColor = pixelColor / 2;
            // std::cout << pixelCol << " " << pixelRow << std::endl;
            // std::cout << pixelColor.r << " " << pixelColor.g << " " << pixelColor.b << std::endl;
            SDL_SetRenderDrawColor(renderer, pixelColor.r, pixelColor.g, pixelColor.b, 255);
            SDL_RenderDrawPoint(renderer, x, y);
        }

        // SDL_RenderDrawLine(renderer, x, drawStart, x, drawEnd);
    }
}