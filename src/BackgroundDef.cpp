#include <string.h>
#include <GL/glew.h>
#include <stdio.h>
#include "DrawUtils.h"
#include "BackgroundDef.h"



BackgroundDef::BackgroundDef(float mul) {
    cameraDim.x = 0;
    cameraDim.y = 0;
    cameraDim.w = 640;
    cameraDim.h = 480;
    //cameraSpeed = 2;
    camDeadZone.x = 128;
    camDeadZone.y = 96;
    camDeadZone.w = 384;
    camDeadZone.h = 288;
    int q = 0, w = 0;
    tileList[0] = glTexImageTGAFile("Grass32.tga",  &tileDim[0], &tileDim[1]);
    tileList[1] = glTexImageTGAFile("Dirt32.tga",  &tileDim[0], &tileDim[1]);
    tileList[2] = glTexImageTGAFile("Dirt32_2.tga",  &tileDim[0], &tileDim[1]);
    tileList[3] = glTexImageTGAFile("Sand32.tga",  &tileDim[0], &tileDim[1]);
    tileList[4] = glTexImageTGAFile("Cliff32.tga",  &tileDim[0], &tileDim[1]);
    tileList[5] = glTexImageTGAFile("Cliff32_2.tga",  &tileDim[0], &tileDim[1]);
    tileList[6] = glTexImageTGAFile("End.tga",  &tileDim[0], &tileDim[1]); 
    tileList[7] = glTexImageTGAFile("Rock32.tga",  &tileDim[0], &tileDim[1]); 
    multiplier = mul;
    tileDim[0] *= multiplier;
    tileDim[1] *= multiplier;
    mapBorder[0] = ((40 * tileDim[0]) * multiplier) - cameraDim.w;
    mapBorder[1] = ((40 * tileDim[1]) * multiplier) - cameraDim.h;

    int a[40][40] = {//[y][x]
        {7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7},
        {7,0,0,2,3,3,3,3,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,1,0,0,7},
        {7,0,0,2,2,5,5,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,7},
        {7,2,2,2,2,5,5,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,1,0,0,7},
        {7,7,7,7,7,7,7,7,7,7,7,7,7,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,3,0,0,1,0,0,7},
        {7,0,2,7,7,7,7,7,7,2,2,2,2,1,7,0,0,0,0,0,0,0,0,0,2,2,2,2,0,0,0,1,0,3,0,0,1,0,0,7},
        {7,0,0,0,0,0,0,0,0,0,0,0,0,1,7,0,0,0,0,0,0,0,0,0,2,2,2,2,0,0,0,1,0,3,0,0,1,0,0,7},
        {7,0,0,0,0,0,0,0,1,1,1,0,0,1,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,0,1,0,3,0,0,1,0,0,7},
        {7,0,1,0,0,0,0,3,1,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,3,0,0,0,0,0,7},
        {7,0,1,0,0,0,0,3,1,0,0,0,0,2,0,0,1,3,1,0,0,0,0,0,0,0,0,0,0,0,0,2,0,3,0,0,0,0,0,7},
        {7,0,1,0,0,0,0,3,1,0,2,2,2,2,0,0,1,3,1,0,0,7,0,7,0,0,0,0,0,0,0,3,0,3,0,0,0,0,0,7},
        {7,0,1,0,0,0,0,3,1,0,2,2,0,0,0,0,1,3,1,0,0,7,0,7,0,0,0,0,0,0,0,3,0,3,0,0,0,0,0,7},
        {7,0,1,0,0,0,0,3,1,0,2,0,7,0,0,1,0,3,1,0,0,0,0,7,0,0,1,0,7,7,7,7,7,7,7,7,7,7,7,7},
        {7,0,1,0,0,0,0,3,1,1,1,1,7,1,1,0,0,0,1,0,0,0,0,7,0,0,1,0,7,0,0,3,0,3,0,0,0,0,0,7},
        {7,0,0,0,0,0,0,3,0,0,0,0,7,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,7,0,0,3,0,3,0,0,0,0,0,7},
        {7,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,1,0,3,3,0,0,0,0,1,0,7,0,0,3,0,3,0,0,1,0,0,7},
        {7,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,1,1,3,0,0,0,0,1,0,7,0,0,3,0,3,0,0,0,0,0,7},
        {7,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,0,1,3,0,0,0,0,1,0,7,0,0,3,0,3,0,0,1,0,0,7},
        {7,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,0,1,0,2,2,2,2,1,0,7,0,0,3,0,3,0,0,1,0,0,7},
        {7,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,7,0,0,3,0,3,0,0,0,0,0,7},
        {7,0,0,0,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,7,0,0,0,0,3,0,0,0,0,0,7},
        {7,1,0,0,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,7,0,3,0,0,3,0,6,0,0,0,7},
        {7,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,7,0,0,0,0,3,6,6,6,0,0,7},
        {7,2,0,1,0,0,0,0,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,0,3,0,0,3,0,6,0,0,0,7},
        {7,2,2,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,7,0,3,0,0,3,0,0,0,2,0,7},
        {7,0,2,2,2,2,2,2,2,2,2,2,2,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,7,0,3,0,0,3,0,0,0,2,0,7},
        {7,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,7,0,3,0,0,0,0,0,0,2,0,7},
        {7,0,0,0,0,0,0,0,1,1,1,0,0,1,0,0,0,1,1,0,0,0,0,0,0,0,1,0,7,0,3,0,0,0,0,0,0,2,0,7},
        {7,0,0,0,0,0,0,3,1,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,1,0,7,0,3,0,0,0,0,0,2,2,0,7},
        {7,0,0,0,0,0,0,3,1,0,0,0,0,7,0,0,1,3,1,0,0,0,0,0,0,0,1,0,7,0,3,0,0,0,0,0,2,2,0,7},
        {7,0,0,0,0,0,0,3,1,7,2,2,2,7,7,7,7,3,1,0,0,0,0,0,0,0,1,0,7,0,3,0,0,0,0,0,2,2,0,7},
        {7,0,0,0,0,0,0,3,1,7,2,2,0,7,7,7,7,3,1,0,0,0,0,0,0,0,1,0,0,0,3,0,0,0,0,0,2,2,0,7},
        {7,0,0,0,0,0,0,3,1,7,7,7,0,7,7,7,7,3,1,0,0,0,0,0,0,0,1,0,0,0,3,0,1,0,0,0,2,2,0,7},
        {7,0,0,0,0,0,0,3,1,7,7,7,1,7,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,3,0,1,0,0,0,2,2,0,7},
        {7,0,0,0,0,0,0,3,0,0,7,7,0,7,0,0,0,0,1,0,0,0,0,0,0,0,1,0,7,0,3,0,1,0,0,0,2,2,0,7},
        {7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,3,3,0,0,0,0,1,0,0,0,3,0,1,0,0,0,2,2,0,7},
        {7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,3,0,0,0,0,1,0,0,0,3,0,0,0,0,0,1,0,0,7},
        {7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,3,0,0,0,0,1,0,0,0,3,0,3,3,0,0,1,0,0,7},
        {7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,2,2,2,2,1,0,0,0,3,3,1,3,0,0,1,0,0,7},
        {7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7}
    };
    memcpy(&tilesMap, &a, sizeof(a));

    for (int i = 0; i < 40; ++i){
        for (int j = 0; j < 40; ++j){
            if(tilesMap[i][j] == 4){
                terrainMap[j][i] = 1;
            }else if(tilesMap[i][j] == 5){
                terrainMap[j][i] = 2;
            }else if(tilesMap[i][j] == 6){
                terrainMap[j][i] = 3;
            }else{
                terrainMap[j][i] = 0;
            }
        }
    }
}

void BackgroundDef::drawBackground(){
    for(y = 0 - cameraDim.y % tileDim[1]; y < 480; y += tileDim[1]){
        t = (cameraDim.y + y) / (tileDim[1]);
        for(x = 0 - cameraDim.x % tileDim[0]; x < 640; x += tileDim[0]){
            r = (cameraDim.x + x) / (tileDim[0]);
            glDrawSprite(tileList[tilesMap[t][r]], x, y, tileDim[0], tileDim[1]);
        }
    }
}
/*
int ** BackgroundDef::getMap(){
    return tilesMap;
}
*/
bool BackgroundDef::collisionDetect(AABB * box){
    int x = box->x / 32;
    int y = box->y / 32;
    int cx = (box->x+box->w)/32;
    int cy = (box->y+box->h)/32;
    if(tilesMap[y][x] > 6){// maybe terrain map
        return true;
    }else if(tilesMap[y][cx] > 6){
        return true;
    }else if(tilesMap[cy][x] > 6){
        return true;
    }else if(tilesMap[cy][cx] > 6){
        return true;
    }
    return false;
}


int BackgroundDef::getX(){
    return cameraDim.x;
}
int BackgroundDef::getY(){
    return cameraDim.y;
}
int BackgroundDef::getW(){
    return cameraDim.w;
}
int BackgroundDef::getH(){
    return cameraDim.h;
}

void BackgroundDef::scrollRight(int cameraSpeed){
    if(cameraDim.x < mapBorder[0])
       cameraDim.x += cameraSpeed;
    else 
        cameraDim.x = mapBorder[0];
    //printf("%d\n",cameraDim.x);
}
void BackgroundDef::scrollLeft(int cameraSpeed){
    if(cameraDim.x > 0)
        cameraDim.x-= cameraSpeed;
    else
        cameraDim.x = 0;
   // printf("%d\n",cameraDim.x);
}

void BackgroundDef::scrollDown(int cameraSpeed){
    if(cameraDim.y < mapBorder[1])
        cameraDim.y += cameraSpeed;
    else
        cameraDim.y = mapBorder[1];
    
    //printf("%d\n",cameraDim.y);
}

void BackgroundDef::scrollUp(int cameraSpeed){
    if(cameraDim.y > 0)
        cameraDim.y -= cameraSpeed;
    else 
        cameraDim.y = 0;
    //printf("%d\n",cameraDim.y);
}

int BackgroundDef::getTile(int x, int y){
    return tilesMap[y][x];
}