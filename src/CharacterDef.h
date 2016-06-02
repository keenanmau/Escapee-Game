#ifndef CharacterDef_h
#define CharacterDef_h

#include <GL/glew.h>
#include <SDL.h>
#include <vector>
#include <string>
#include "DrawUtils.h"
#include "AABB.h"


using namespace std;

class locNode{
public:
	int x, y;
	int gCost;//optimization value. 
	float distanceToGoal; //direction value
	locNode* parent;
	locNode(int xx, int yy);
	void setG(locNode target);
};

class FrameDef {
public:
	int w, h;
	GLuint image;
	float frameTimeSecs;
};

class AnimationDef {
public:
	int maxFrames;
	string name;
	FrameDef * frames;
};

class AnimationData {
public:
	AnimationDef def;
	int curFrame;
	float secsUntilNextFrame;
	void setup(int a);
	void update(float deltaTime, int dir);
	void draw(int x, int y);
};

struct CharacterDef { //
	string name;
	string walkAnimDef;
	string attackAnimDef;
};

class Action{
public:
	int act; /*what action, 1-4: move*/
	int px;//target location
	int py;
	int tiem;
	Action(int a, int x, int y);
};

class CharacterData { //character animation metadata
public:
	bool moveX(int targetX, float dist);
	bool moveY(int targetY, float dist);
	bool move(Action a, unsigned int deltaTime);
	AABB box;
	int act, ai;//act=direction, 0u,1r,2d,3l
	float x, y;
	float speed;
	int * triAr;
	std::vector<Action> actionList;
	std::vector<locNode> defaultList;
	std::vector<locNode>::iterator it;
	CharacterDef definedChar;
	AnimationData curAnimation;
	int update(unsigned int deltaTime);
	void draw(int difx, int dify);
	bool executeAction(Action * a, unsigned int deltaTime);
	bool scanForPlayer(int x, int y);
	void drawVision(int difx, int dify);
	int * vectorize(int x1, int y1, int x2, int y2);
	int dotProduct(int x1, int y1, int x2, int y2);
	void setVisionTriangle();
};




//---------------
/*
class CharacterDef{
	int speed;
	GLuint sprite[4];
	AABB stat;
	int dir;
	int health;
public:
	int killPriority;
// TODO: edit so that it'll take in multiple sides
	CharacterDef(const char* up, const char* down, const char* left, const char* right, int kill){ 
		sprite[0] = glTexImageTGAFile(up,  &stat.w, &stat.h);
		sprite[1] = glTexImageTGAFile(down,  &stat.w, &stat.h);
		sprite[2] = glTexImageTGAFile(left,  &stat.w, &stat.h);
		sprite[3] = glTexImageTGAFile(right,  &stat.w, &stat.h);
		dir= 3;
		speed = 4;
		killPriority = kill;
		health = 300;
	} 

	

	bool takeDamage(int damage){
		health -= damage;
		if(health <= 0){
			return true;
		}
		return false;
	}

	int getHealth(){
		return health;
	}

	GLuint getSprite(){
		return sprite[dir];
	}

	int setLocation(int ex, int ey){
		stat.x = ex;
		stat.y = ey;
	}

	int getX(){
		return stat.x;
	}
	int getY(){
		return stat.y;
	}
	int getW(){
		return stat.w;
	}
	int getH(){
		return stat.h;
	}

	AABB * getBox(){
		return &stat;
	}

	int getDir(){
		return dir;
	}


// --------------- Mobility Section -----------
	int moveUp(){
		stat.y -= speed;
		dir = 0;
	}
	int moveDown(){
		stat.y += speed;
		dir = 1;
	}
	int moveLeft(){
		stat.x -= speed;
		dir = 2;
	}
	int moveRight(){
		stat.x += speed;
		dir = 3;
	}
	void setSpeed(int s){
		speed = s;
	}
//-----------------------------------------------
};
*/
#endif