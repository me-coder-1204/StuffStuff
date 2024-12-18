#include "player.hpp"
#include<typeinfo>
#include<fstream>

Player::Player(){
    playerPos.x = 11.5;
    playerPos.y = 22;

    playerDirection.x = -1.0;
    playerDirection.y = 0.0;

    cameraPlane.x = 0.0;
    cameraPlane.y = SDL_tan(33 * 3.1415926 / 180);

    moveSpeed = 5.0;
    rotateSpeed = 3.0;
}

void Player::movePlayer(double delTime, Map map){
    const Uint8 * keys = SDL_GetKeyboardState(NULL);

    if(keys[SDL_SCANCODE_UP]){
        if(!map.mapArray[(int)floor(playerPos.y)][(int)floor(playerPos.x + moveSpeed * playerDirection.x * delTime + ((0 < playerDirection.x) - (0 > playerDirection.x)) * 0.2)]) playerPos.x += moveSpeed * playerDirection.x * delTime;
        if(!map.mapArray[(int)floor(playerPos.y + moveSpeed * playerDirection.y * delTime + ((0 < playerDirection.y) - (0 > playerDirection.y)) * 0.2)][(int)floor(playerPos.x)]) playerPos.y += moveSpeed * playerDirection.y * delTime;
    }

    if(keys[SDL_SCANCODE_DOWN]){
        if(!map.mapArray[(int)floor(playerPos.y)][(int)floor(playerPos.x - moveSpeed * playerDirection.x * delTime - ((0 < playerDirection.x) - (0 > playerDirection.x)) * 0.2)]) playerPos.x -= moveSpeed * playerDirection.x * delTime;
        if(!map.mapArray[(int)floor(playerPos.y - moveSpeed * playerDirection.y * delTime - ((0 < playerDirection.y) - (0 > playerDirection.y)) * 0.2)][(int)floor(playerPos.x)]) playerPos.y -= moveSpeed * playerDirection.y * delTime;
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

    if(keys[SDL_SCANCODE_K]) std::cout << playerPos.x << " " << playerPos.y << std::endl;
}

void Player::cameraRender(Map map, SDL_Renderer* renderer, int width, int height){
    // int wid = display.w;
    for(int y=0;y<height/2;y++){
        for(int x=0;x<=width;x++){
            Coords roofHit;
            // int l = x - width/2;
            double camX = 2 * x/(double)width - 1;
            int roofHeight = 1;
            double heightVec = 0.66/320;
            Coords rayDir = camX * cameraPlane + playerDirection;
            double p1 =  roofHeight * rayDir.x / (2*(height/2-y) * heightVec);
            double p2 =  roofHeight * rayDir.y / (2*(height/2-y) * heightVec);

            roofHit.x = p1 + playerPos.x;
            roofHit.y = p2 + playerPos.y;

            roofHit = roofHit - floorCoords(roofHit);

            int pixelRow = floor(map.textureSize.x * roofHit.x);
            int pixelCol = floor(map.textureSize.y * roofHit.y);

            ColorRGB pixelColor = map.textureSet.at(2).at(pixelRow * map.textureSize.x + pixelCol);

            SDL_SetRenderDrawColor(renderer, pixelColor.r, pixelColor.g, pixelColor.b, 255);
            SDL_RenderDrawPoint(renderer, x, y);
        }
    }

    for(int y=height;y>height/2;y--){
        for(int x=0;x<=width;x++){
            Coords roofHit;
            // int l = x - width/2;
            double camX = 2 * x/(double)width - 1;
            int roofHeight = 1;
            double heightVec = 0.66/320;
            Coords rayDir = camX * cameraPlane + playerDirection;
            double p1 =  roofHeight * rayDir.x / (2*(y-height/2) * heightVec);
            double p2 =  roofHeight * rayDir.y / (2*(y-height/2) * heightVec);

            roofHit.x = p1 + playerPos.x;
            roofHit.y = p2 + playerPos.y;

            roofHit = roofHit - floorCoords(roofHit);

            int pixelRow = floor(map.textureSize.x * roofHit.x);
            int pixelCol = floor(map.textureSize.y * roofHit.y);

            ColorRGB pixelColor = map.textureSet.at(0).at(pixelRow * map.textureSize.x + pixelCol);

            SDL_SetRenderDrawColor(renderer, pixelColor.r, pixelColor.g, pixelColor.b, 255);
            SDL_RenderDrawPoint(renderer, x, y);
        }
    }
    
    for(int x=0;x<width;x++){
        double cameraX = (2 * x/ (double) width) - 1;
        Coords rayDirection = playerDirection + (cameraPlane * cameraX); 
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

        if(!side) perpWallDistance = sideDist.x - deltaDist.x;
        else perpWallDistance = sideDist.y - deltaDist.y;

        int lineHeight = (int) height / perpWallDistance;
        int drawStart = -lineHeight / 2 + height / 2;
        int drawEnd = lineHeight / 2 + height / 2;

        double wallX;
        if(!side) wallX = playerPos.y + perpWallDistance * rayDirection.y;
        else wallX = playerPos.x + perpWallDistance * rayDirection.x;

        wallX -= floor(wallX);

        int pixelCol = floor(map.textureSize.x * wallX);

        int textureNum = map.mapArray[(int)mapPos.y][(int)mapPos.x] - 1;
        std::vector texture = map.textureSet.at(textureNum);

        for(int y = drawStart; y<drawEnd; y++){
            if(y < 0 || y > height) continue;
            int pixelRow = floor(((double)(y-drawStart)/lineHeight) * map.textureSize.y);
            ColorRGB pixelColor = texture.at(map.textureSize.x * pixelRow + pixelCol);
            if(side==1) pixelColor = pixelColor / 2;
            SDL_SetRenderDrawColor(renderer, pixelColor.r, pixelColor.g, pixelColor.b, 255);
            SDL_RenderDrawPoint(renderer, x, y);
        }

    }
}