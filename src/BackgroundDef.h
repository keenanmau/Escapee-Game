#ifndef BackgroundDef_h
#define BackgroundDef_h

#include "DrawUtils.h"
#include "AABB.h"

class BackgroundDef {
    int tilesMap[40][40];
    int terrainMap[40][40];
    GLuint tileList[10];
    int tileDim[2];
    float multiplier;
    int x, y, r, t;
 


public: 
    AABB cameraDim;
    AABB camDeadZone;
    //int cameraSpeed;
    int mapBorder[2];

    BackgroundDef(float mul);
    void drawBackground();
    //int** getMap();
    bool checkBox(const AABB* box1){
    	return AABBIntersect(box1, &cameraDim);
    }

    bool collisionDetect(AABB * box);
	int getX();
	int getY();
	int getW();
	int getH();

    void scrollRight(int cameraSpeed);
    void scrollLeft(int cameraSpeed);
    void scrollDown(int cameraSpeed);
    void scrollUp(int cameraSpeed);

    int getTile(int x, int y);
};

#endif