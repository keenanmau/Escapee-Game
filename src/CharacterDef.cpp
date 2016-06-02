#include <GL/glew.h>
#include <SDL.h>
#include "DrawUtils.h"
#include "CharacterDef.h"
/*Keenan Mau

*/


void AnimationData::update(float deltaTime, int dir){
	printf("Animation Begin");
	secsUntilNextFrame -= deltaTime;
	//if(dir > 8 || dir < 0){
		//curFrame = 0; dir = 0;
	//}
	if(curFrame / 2 != dir){//direction changes
		curFrame = (dir%8) * 2;
		secsUntilNextFrame = def.frames[curFrame].frameTimeSecs; //reset time
	}else if(secsUntilNextFrame <= 0){//animation change time
		if(curFrame % 2 == 0){//curframe = 0
			curFrame++;
		}else{//curframe = 1
			curFrame--;
		}
		printf("curFrame: %d", curFrame);
		secsUntilNextFrame += def.frames[curFrame].frameTimeSecs;//continue time through animation change
	}
}

void AnimationData::draw(int x, int y){
	glDrawSprite(def.frames[curFrame].image, x, y, 
		def.frames[curFrame].w, 
		def.frames[curFrame].h);
}

void AnimationData::setup(int a){
	def.frames = new FrameDef[a];
	def.maxFrames = a;
	curFrame = 0;
	secsUntilNextFrame = def.frames[curFrame].frameTimeSecs;
}

Action::Action(int a, int x, int y){
	act = a;
	px = x;
	py = y;
	tiem = 0;
}



bool CharacterData::moveX(int targetX, float dist){
	if(x < targetX){
		act = 1;
		if(x + dist < targetX){
			x += dist;
			return false;
		}else{
			x = targetX;
			return true;
		}
	}else{//(x > targetX)
		act = 3;
		if(x - dist > targetX){
			x -= dist;
			return false;
		}else{
			x = targetX;
			return true;
		}
	}
}
bool CharacterData::moveY(int targetY, float dist){
	if(y < targetY){
		act = 2;
		if(y + dist < targetY){
			y += dist;
			return false;
		}else{
			y = targetY;
			return true;
		}
	}else{ //(y > targetY)
		act = 0;
		if(y - dist > targetY){
			y -= dist;
			return false;
		}else{
			y = targetY;
			return true;
		}
	}
}

//return true if complete, false if incomplete
bool CharacterData::move(Action a, unsigned int deltaTime){
	//printf("Move (%d, %d) \n", a.px, a.py);
	float dist = (speed * deltaTime) / 1000.0;
	if(!(x == a.px)){
		if(!(y == a.py)){
			bool g = moveX(a.px, dist / 2.0);
			bool h = moveY(a.py, dist / 2.0);
			return (g && h);
		}else{
			return moveX(a.px, dist);
		}
	}else if(!(y == a.py)){
		return moveY(a.py, dist);
	}else{
		return true;
	}
}

int CharacterData::update(unsigned int deltaTime){
	printf("not vision\n");
	setVisionTriangle();
	box.x = x;
	box.y = y;
	float distance = speed / (float)deltaTime;
	int currentAction;//0 is idle, 1 is moving
	if(!actionList.empty()){
		printf("ActionList not empty\n");
		currentAction = 1;
		
		bool tf = executeAction(&actionList.front(), deltaTime);
		if(tf){
			actionList.erase(actionList.begin());
			//printf("Erased action \n");
		}
	}else{
		printf("actionList empty\n");
		ai = 0;
		it++;
		if(it == (defaultList.end())){//this line is total bullshit
			printf("defaultList\n");
			it = defaultList.begin();
		}
		currentAction = -1;
	}
	printf("after lists\n");
	curAnimation.update(deltaTime, act);
	printf("animation?\n");
	return currentAction;
	//printf("DeltaTime: %u \n", deltaTime);
}

bool CharacterData::executeAction(Action * a, unsigned int deltaTime){
	//if statements
	if(a->act == 10){
		a->tiem -= deltaTime;
		//printf("Tiem: %d \n", a->tiem);
		if(a->tiem <= 0){
			ai = 1;
			return true;
		}
		return false;
	}
	return move(*a, deltaTime);
}

void CharacterData::draw(int difx, int dify){
	curAnimation.draw(box.x - difx, box.y - dify);
}


//.866*p
void CharacterData::drawVision(int difx, int dify){
	glBegin(GL_TRIANGLES);
	//glEnable(GL_BLEND);
	//fucking done for now. 
	glColor4d(1.0, 0.5, 0.5, 0.5);
	glVertex2i(triAr[0] - difx, triAr[1] - dify);
	glVertex2i(triAr[2] - difx, triAr[3] - dify);
	glVertex2i(triAr[4] - difx, triAr[5] - dify);
	glEnd();
}

void CharacterData::setVisionTriangle(){
	int a = 120;
	int b = a * 0.866;
	triAr = new int[6];

	if(act == 0){
		triAr[0] = box.x + (box.w / 2);
		triAr[1] = box.y;
		triAr[2] = triAr[0] - b;
		triAr[3] = triAr[1] - a;
		triAr[4] = triAr[0] + b;
		triAr[5] = triAr[1] - a;
	}else if(act == 1){
		triAr[0] = box.x + box.w;
		triAr[1] = box.y + (box.h/2);
		triAr[2] = triAr[0] + a;
		triAr[3] = triAr[1] - b;
		triAr[4] = triAr[0] + a;
		triAr[5] = triAr[1] + b;
	}else if(act == 2){
		triAr[0] = box.x + (box.w / 2);
		triAr[1] = box.y + box.h;
		triAr[2] = triAr[0] + b;
		triAr[3] = triAr[1] + a;
		triAr[4] = triAr[0] - b;
		triAr[5] = triAr[1] + a;
	}else if(act == 3){
		triAr[0] = box.x;
		triAr[1] = box.y + (box.h/2);
		triAr[2] = triAr[0] - a;
		triAr[3] = triAr[1] + b;
		triAr[4] = triAr[0] - a;
		triAr[5] = triAr[1] - b;
	}

}

bool CharacterData::scanForPlayer(int x, int y){
	int * normal, *pline;
	int result;
	normal = vectorize(triAr[0], triAr[1], triAr[2], triAr[3]);//(p1, p2)
	int temp = normal[0];//creating normal vector
	normal[0] = normal[1] * -1;;
	normal[1] = temp;
	pline = vectorize(triAr[0], triAr[1], x, y);// player to point vector
	result = dotProduct(normal[0], normal[1], pline[0], pline[1]);
	if(result < 0){
		return false;
	}
	normal = vectorize(triAr[2], triAr[3], triAr[4], triAr[5]);//(p1, p2)
	temp = normal[0];//creating normal vector
	normal[0] = normal[1] * -1;;
	normal[1] = temp;
	pline = vectorize(triAr[2], triAr[3], x, y);// player to point vector
	result = dotProduct(normal[0], normal[1], pline[0], pline[1]);
	if(result < 0){
		return false;
	}
	normal = vectorize(triAr[4], triAr[5], triAr[0], triAr[1]);//(p1, p2)
	temp = normal[0];//creating normal vector
	normal[0] = normal[1] * -1;;
	normal[1] = temp;
	pline = vectorize(triAr[4], triAr[5], x, y);// player to point vector
	result = dotProduct(normal[0], normal[1], pline[0], pline[1]);
	if(result < 0){
		return false;
	}
	printf("Player Found\n");
	return true;
}

int* CharacterData::vectorize(int x1, int y1, int x2, int y2){
	int* vec = new int[2];
	vec[0] = x2 - x1;
	vec[1] = y2 - y1;
	return vec;
}

int CharacterData::dotProduct(int x1, int y1, int x2, int y2){
	return ((x1 * x2) + (y1 * y2));
}
locNode::locNode(int xx, int yy){
	x = xx;
	y = yy;
}

void locNode::setG(locNode target){
	float xx = x - target.x;
	float yy = y - target.y;
	distanceToGoal = sqrtf(xx * xx + yy * yy);
}