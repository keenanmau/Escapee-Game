
#include "npcHandler.h"
#include "DrawUtils.h"
#include "CharacterDef.h"


npcHandler::npcHandler(BackgroundDef * bgRef){
	lose = false;
	win = false;
	player = CharacterData();
	player.box.x = 32;
	player.box.y = 32;
	player.x = 32.0;
	player.y = 32.0;
	player.speed = 100;
	player.ai = 0;
	player.act = 0;
	player.definedChar.name= "Player";
	player.definedChar.walkAnimDef = "dragon";
	player.definedChar.attackAnimDef = "dragon";
	player.curAnimation.curFrame = 0;
	player.curAnimation.secsUntilNextFrame = 300;
	player.curAnimation.def.maxFrames = 2;
	player.curAnimation.def.name = "Player.tar";
	player.curAnimation.setup(8);
	player.curAnimation.def.frames[0].image = 
		glTexImageTGAFile("DragonUp1.tga", 
		&player.curAnimation.def.frames[0].w, 
		&player.curAnimation.def.frames[0].h);
	player.curAnimation.def.frames[0].frameTimeSecs = 500;
	player.curAnimation.def.frames[1].image = 
		glTexImageTGAFile("DragonUp2.tga", 
		&player.curAnimation.def.frames[1].w, 
		&player.curAnimation.def.frames[1].h);
	player.curAnimation.def.frames[1].frameTimeSecs = 500;
	player.curAnimation.def.frames[2].image = 
		glTexImageTGAFile("DragonRight1.tga", 
		&player.curAnimation.def.frames[2].w, 
		&player.curAnimation.def.frames[2].h);
	player.curAnimation.def.frames[2].frameTimeSecs = 500;
	player.curAnimation.def.frames[3].image = 
		glTexImageTGAFile("DragonRight2.tga", 
		&player.curAnimation.def.frames[3].w, 
		&player.curAnimation.def.frames[3].h);
	player.curAnimation.def.frames[3].frameTimeSecs = 500;
	player.curAnimation.def.frames[4].image = 
		glTexImageTGAFile("DragonDown1.tga", 
		&player.curAnimation.def.frames[4].w, 
		&player.curAnimation.def.frames[4].h);
	player.curAnimation.def.frames[4].frameTimeSecs = 500;
	player.curAnimation.def.frames[5].image = 
		glTexImageTGAFile("DragonDown2.tga", 
		&player.curAnimation.def.frames[5].w, 
		&player.curAnimation.def.frames[5].h);
	player.curAnimation.def.frames[5].frameTimeSecs = 500;
	player.curAnimation.def.frames[6].image = 
		glTexImageTGAFile("DragonLeft1.tga", 
		&player.curAnimation.def.frames[6].w, 
		&player.curAnimation.def.frames[6].h);
	player.curAnimation.def.frames[6].frameTimeSecs = 500;
	player.curAnimation.def.frames[7].image = 
		glTexImageTGAFile("DragonLeft2.tga", 
		&player.curAnimation.def.frames[7].w, 
		&player.curAnimation.def.frames[7].h);
	player.curAnimation.def.frames[7].frameTimeSecs = 500;
	player.box.w = player.curAnimation.def.frames[0].w;
	player.box.h = player.curAnimation.def.frames[0].h;
	//-----------------------

	bg = bgRef;
	charStack.reserve(20);
	CharacterData scout;
	scout.box.x = 30 * 32;
	scout.box.y = 10 * 32;
	scout.x = 30 * 32.0;
	scout.y = 10 * 32.0;
	scout.speed = 100;
	scout.ai = 0;
	scout.definedChar.name = "Scout";
	scout.definedChar.walkAnimDef = "Rabbit.tar";
	scout.definedChar.attackAnimDef = "Rabbit.tar";
	scout.curAnimation.curFrame = 0;
	scout.curAnimation.secsUntilNextFrame = 300;
	scout.curAnimation.def.maxFrames = 2;
	scout.curAnimation.def.name = "Rabbit.tar";
	scout.curAnimation.setup(8);
	scout.curAnimation.def.frames[0].image = 
		glTexImageTGAFile("RabbitUp1.tga", //RabbitUp1
		&scout.curAnimation.def.frames[0].w, 
		&scout.curAnimation.def.frames[0].h);
	scout.curAnimation.def.frames[0].frameTimeSecs = 500;
	scout.curAnimation.def.frames[1].image = 
		glTexImageTGAFile("RabbitUp2.tga", //RabbitUp2
		&scout.curAnimation.def.frames[1].w, 
		&scout.curAnimation.def.frames[1].h);
	scout.curAnimation.def.frames[1].frameTimeSecs = 500;
	scout.curAnimation.def.frames[2].image = 
		glTexImageTGAFile("RabbitRight1.tga", //RabbitRight1
		&scout.curAnimation.def.frames[2].w, 
		&scout.curAnimation.def.frames[2].h);
	scout.curAnimation.def.frames[2].frameTimeSecs = 500;
	scout.curAnimation.def.frames[3].image = 
		glTexImageTGAFile("RabbitRight2.tga", //RabbitRight2
		&scout.curAnimation.def.frames[3].w, 
		&scout.curAnimation.def.frames[3].h);
	scout.curAnimation.def.frames[3].frameTimeSecs = 500;
	scout.curAnimation.def.frames[4].image = 
		glTexImageTGAFile("RabbitDown1.tga", //RabbitDown1
		&scout.curAnimation.def.frames[4].w, 
		&scout.curAnimation.def.frames[4].h);
	scout.curAnimation.def.frames[4].frameTimeSecs = 500;
	scout.curAnimation.def.frames[5].image = 
		glTexImageTGAFile("RabbitDown2.tga", //RabbitDown2
		&scout.curAnimation.def.frames[5].w, 
		&scout.curAnimation.def.frames[5].h);
	scout.curAnimation.def.frames[5].frameTimeSecs = 500;
	scout.curAnimation.def.frames[6].image = 
		glTexImageTGAFile("RabbitLeft1.tga", //RabbitLeft1
		&scout.curAnimation.def.frames[6].w, 
		&scout.curAnimation.def.frames[6].h);
	scout.curAnimation.def.frames[6].frameTimeSecs = 500;
	scout.curAnimation.def.frames[7].image = 
		glTexImageTGAFile("RabbitLeft2.tga", //RabbitLeft2
		&scout.curAnimation.def.frames[7].w, 
		&scout.curAnimation.def.frames[7].h);
	scout.curAnimation.def.frames[7].frameTimeSecs = 500;
	scout.box.w = scout.curAnimation.def.frames[0].w;
	scout.box.h = scout.curAnimation.def.frames[0].h;
	scout.curAnimation.curFrame = 0;
	charStack.push_back(scout);
	locNode a =  locNode(34, 4);
	locNode b =  locNode( 34, 9);
	locNode c =  locNode( 38, 9);
	locNode d =  locNode( 38, 2);
	locNode e =  locNode( 34, 2);	
	charStack[0].defaultList.push_back(a);
	charStack[0].defaultList.push_back(b);
	charStack[0].defaultList.push_back(c);
	charStack[0].defaultList.push_back(d);
	charStack[0].defaultList.push_back(e);
	charStack[0].it = charStack[0].defaultList.begin();

	CharacterData s2;
	s2.box.x = 19 * 32;
	s2.box.y = 9 * 32;
	s2.x = 19 * 32.0;
	s2.y = 9 * 32.0;
	s2.speed = 100;
	s2.ai = 0;
	s2.act = 0;
	s2.definedChar.name = "Scout";
	s2.definedChar.walkAnimDef = "Rabbit.tar";
	s2.definedChar.attackAnimDef = "Rabbit.tar";
	s2.curAnimation.curFrame = 0;
	s2.curAnimation.secsUntilNextFrame = 300;
	s2.curAnimation.def.maxFrames = 2;
	s2.curAnimation.def.name = "Rabbit.tar";
	s2.curAnimation.setup(8);
	s2.curAnimation.curFrame = 0;
	s2.curAnimation.def.frames[0].image = 
		glTexImageTGAFile("RabbitUp1.tga", //RabbitUp1
		&s2.curAnimation.def.frames[0].w, 
		&s2.curAnimation.def.frames[0].h);
	s2.curAnimation.def.frames[0].frameTimeSecs = 500;
	s2.curAnimation.def.frames[1].image = 
		glTexImageTGAFile("RabbitUp2.tga", //RabbitUp2
		&s2.curAnimation.def.frames[1].w, 
		&s2.curAnimation.def.frames[1].h);
	s2.curAnimation.def.frames[1].frameTimeSecs = 500;
	s2.curAnimation.def.frames[2].image = 
		glTexImageTGAFile("RabbitRight1.tga", //RabbitRight1
		&s2.curAnimation.def.frames[2].w, 
		&s2.curAnimation.def.frames[2].h);
	s2.curAnimation.def.frames[2].frameTimeSecs = 500;
	s2.curAnimation.def.frames[3].image = 
		glTexImageTGAFile("RabbitRight2.tga", //RabbitRight2
		&s2.curAnimation.def.frames[3].w, 
		&s2.curAnimation.def.frames[3].h);
	s2.curAnimation.def.frames[3].frameTimeSecs = 500;
	s2.curAnimation.def.frames[4].image = 
		glTexImageTGAFile("RabbitDown1.tga", //RabbitDown1
		&s2.curAnimation.def.frames[4].w, 
		&s2.curAnimation.def.frames[4].h);
	s2.curAnimation.def.frames[4].frameTimeSecs = 500;
	s2.curAnimation.def.frames[5].image = 
		glTexImageTGAFile("RabbitDown2.tga", //RabbitDown2
		&s2.curAnimation.def.frames[5].w, 
		&s2.curAnimation.def.frames[5].h);
	s2.curAnimation.def.frames[5].frameTimeSecs = 500;
	s2.curAnimation.def.frames[6].image = 
		glTexImageTGAFile("RabbitLeft1.tga", //RabbitLeft1
		&s2.curAnimation.def.frames[6].w, 
		&s2.curAnimation.def.frames[6].h);
	s2.curAnimation.def.frames[6].frameTimeSecs = 500;
	s2.curAnimation.def.frames[7].image = 
		glTexImageTGAFile("RabbitLeft2.tga", //RabbitLeft2
		&s2.curAnimation.def.frames[7].w, 
		&s2.curAnimation.def.frames[7].h);
	s2.curAnimation.def.frames[7].frameTimeSecs = 500;
	s2.box.w = s2.curAnimation.def.frames[0].w;
	s2.box.h = s2.curAnimation.def.frames[0].h;
	charStack.push_back(s2);
	locNode a2 =  locNode(27, 9);
	locNode b2 =  locNode(27, 18);
	locNode c2 =  locNode(20, 18);
	locNode d2 =  locNode( 20, 22);
	locNode e2 =  locNode( 20, 16);
	locNode f2 =  locNode( 19, 9);	
	charStack[1].defaultList.push_back(a2);
	charStack[1].defaultList.push_back(b2);
	charStack[1].defaultList.push_back(c2);
	charStack[1].defaultList.push_back(d2);
	charStack[1].defaultList.push_back(e2);
	charStack[1].defaultList.push_back(f2);
	charStack[1].it = charStack[1].defaultList.begin();

	CharacterData s3;
	s3.box.x = 2 * 32;
	s3.box.y = 38 * 32;
	s3.x = 2 * 32.0;
	s3.y = 38 * 32.0;
	s3.speed = 100;
	s3.ai = 0;
	s3.act = 0;
	s3.definedChar.name = "Scout";
	s3.definedChar.walkAnimDef = "Rabbit.tar";
	s3.definedChar.attackAnimDef = "Rabbit.tar";
	s3.curAnimation.curFrame = 0;
	s3.curAnimation.secsUntilNextFrame = 300;
	s3.curAnimation.def.maxFrames = 2;
	s3.curAnimation.def.name = "Rabbit.tar";
	s3.curAnimation.setup(8);
	s3.curAnimation.def.frames[0].image = 
		glTexImageTGAFile("RabbitUp1.tga", //RabbitUp1
		&s3.curAnimation.def.frames[0].w, 
		&s3.curAnimation.def.frames[0].h);
	s3.curAnimation.def.frames[0].frameTimeSecs = 500;
	s3.curAnimation.def.frames[1].image = 
		glTexImageTGAFile("RabbitUp2.tga", //RabbitUp2
		&s3.curAnimation.def.frames[1].w, 
		&s3.curAnimation.def.frames[1].h);
	s3.curAnimation.def.frames[1].frameTimeSecs = 500;
	s3.curAnimation.def.frames[2].image = 
		glTexImageTGAFile("RabbitRight1.tga", //RabbitRight1
		&s3.curAnimation.def.frames[2].w, 
		&s3.curAnimation.def.frames[2].h);
	s3.curAnimation.def.frames[2].frameTimeSecs = 500;
	s3.curAnimation.def.frames[3].image = 
		glTexImageTGAFile("RabbitRight2.tga", //RabbitRight2
		&s3.curAnimation.def.frames[3].w, 
		&s3.curAnimation.def.frames[3].h);
	s3.curAnimation.def.frames[3].frameTimeSecs = 500;
	s3.curAnimation.def.frames[4].image = 
		glTexImageTGAFile("RabbitDown1.tga", //RabbitDown1
		&s3.curAnimation.def.frames[4].w, 
		&s3.curAnimation.def.frames[4].h);
	s3.curAnimation.def.frames[4].frameTimeSecs = 500;
	s3.curAnimation.def.frames[5].image = 
		glTexImageTGAFile("RabbitDown2.tga", //RabbitDown2
		&s3.curAnimation.def.frames[5].w, 
		&s3.curAnimation.def.frames[5].h);
	s3.curAnimation.def.frames[5].frameTimeSecs = 500;
	s3.curAnimation.def.frames[6].image = 
		glTexImageTGAFile("RabbitLeft1.tga", //RabbitLeft1
		&s3.curAnimation.def.frames[6].w, 
		&s3.curAnimation.def.frames[6].h);
	s3.curAnimation.def.frames[6].frameTimeSecs = 500;
	s3.curAnimation.def.frames[7].image = 
		glTexImageTGAFile("RabbitLeft2.tga", //RabbitLeft2
		&s3.curAnimation.def.frames[7].w, 
		&s3.curAnimation.def.frames[7].h);
	s3.curAnimation.def.frames[7].frameTimeSecs = 500;
	s3.box.w = s3.curAnimation.def.frames[0].w;
	s3.box.h = s3.curAnimation.def.frames[0].h;
	
	charStack.push_back(s3);
	locNode a3 =  locNode( 4, 25);
	locNode b3 =  locNode( 17, 25);
	locNode c3 =  locNode( 17, 25);
	locNode d3 =  locNode( 17, 36);
	locNode e3 =  locNode( 17, 36);
	locNode f3 =  locNode( 4, 36);	
	charStack[2].defaultList.push_back(a3);
	charStack[2].defaultList.push_back(b3);
	charStack[2].defaultList.push_back(c3);
	charStack[2].defaultList.push_back(d3);
	charStack[2].defaultList.push_back(e3);
	charStack[2].defaultList.push_back(f3);
	charStack[2].it = charStack[2].defaultList.begin();


/*
	createNPC(3,3);
	createNPCpath(2,2);
	createNPCpath(10,3);
	*/
}

void npcHandler::createNPC(int x, int y){
	CharacterData qw;
	qw.box.x = x * 32;
	qw.box.y = y * 32;
	qw.x = x * 32.0;
	qw.y = y * 32.0;
	qw.speed = 100;
	qw.ai = 0;
	qw.act = 0;
	qw.definedChar.name = "Scout";
	qw.definedChar.walkAnimDef = "Rabbit.tar";
	qw.definedChar.attackAnimDef = "Rabbit.tar";
	qw.curAnimation.curFrame = 0;
	qw.curAnimation.secsUntilNextFrame = 300;
	qw.curAnimation.def.maxFrames = 2;
	qw.curAnimation.def.name = "Rabbit.tar";
	qw.curAnimation.setup(8);
	qw.curAnimation.def.frames[0].image = 
		glTexImageTGAFile("RabbitUp1.tga", //RabbitUp1
		&qw.curAnimation.def.frames[0].w, 
		&qw.curAnimation.def.frames[0].h);
	qw.curAnimation.def.frames[0].frameTimeSecs = 500;
	qw.curAnimation.def.frames[1].image = 
		glTexImageTGAFile("RabbitUp2.tga", //RabbitUp2
		&qw.curAnimation.def.frames[1].w, 
		&qw.curAnimation.def.frames[1].h);
	qw.curAnimation.def.frames[1].frameTimeSecs = 500;
	qw.curAnimation.def.frames[2].image = 
		glTexImageTGAFile("RabbitRight1.tga", //RabbitRight1
		&qw.curAnimation.def.frames[2].w, 
		&qw.curAnimation.def.frames[2].h);
	qw.curAnimation.def.frames[2].frameTimeSecs = 500;
	qw.curAnimation.def.frames[3].image = 
		glTexImageTGAFile("RabbitRight2.tga", //RabbitRight2
		&qw.curAnimation.def.frames[3].w, 
		&qw.curAnimation.def.frames[3].h);
	qw.curAnimation.def.frames[3].frameTimeSecs = 500;
	qw.curAnimation.def.frames[4].image = 
		glTexImageTGAFile("RabbitDown1.tga", //RabbitDown1
		&qw.curAnimation.def.frames[4].w, 
		&qw.curAnimation.def.frames[4].h);
	qw.curAnimation.def.frames[4].frameTimeSecs = 500;
	qw.curAnimation.def.frames[5].image = 
		glTexImageTGAFile("RabbitDown2.tga", //RabbitDown2
		&qw.curAnimation.def.frames[5].w, 
		&qw.curAnimation.def.frames[5].h);
	qw.curAnimation.def.frames[5].frameTimeSecs = 500;
	qw.curAnimation.def.frames[6].image = 
		glTexImageTGAFile("RabbitLeft1.tga", //RabbitLeft1
		&qw.curAnimation.def.frames[6].w, 
		&qw.curAnimation.def.frames[6].h);
	qw.curAnimation.def.frames[6].frameTimeSecs = 500;
	qw.curAnimation.def.frames[7].image = 
		glTexImageTGAFile("RabbitLeft2.tga", //RabbitLeft2
		&qw.curAnimation.def.frames[7].w, 
		&qw.curAnimation.def.frames[7].h);
	qw.curAnimation.def.frames[7].frameTimeSecs = 500;
	qw.box.w = qw.curAnimation.def.frames[0].w;
	qw.box.h = qw.curAnimation.def.frames[0].h;
	charStack.push_back(qw);
	createNPCpath(x,y);
	charStack.back().it = charStack.back().defaultList.begin();
}

void npcHandler::createNPCpath(int x, int y){
	charStack.back().defaultList.push_back(locNode(x,y));
}

void npcHandler::update(unsigned int deltaTime){
	int playerX = player.box.x + (player.box.w / 2);
	int playerY = player.box.y + (player.box.h / 2);
	for (int i = 0; i < charStack.size(); ++i){
		//printf("update\n");
		int q = charStack[i].update(deltaTime);
		//printf("second \n");
		if(q < 0){
			locNode npc = locNode(charStack[i].box.x/32, charStack[i].box.y/32);
			std::vector<Action> v = createPath(npc, *charStack[i].it);
			for(int j = 0; j < v.size(); ++j){
				charStack[i].actionList.push_back(v[j]);
			}
		}
	}
	for (int i = 0; i < charStack.size(); ++i){

		if(charStack[i].ai == 0){
			if(charStack[i].scanForPlayer(playerX, playerY)){//scan inputs players current plocation
				charStack[i].ai = 1;
				locNode player = locNode(playerX / 32, playerY / 32);//input player tlocation
				player.distanceToGoal = 0;
				locNode npc = locNode(charStack[i].box.x/32, charStack[i].box.y/32);
				npc.distanceToGoal = distance(player, npc);
				std::vector<Action> v = createPath(npc, player);
				charStack[i].actionList.clear();
				Action pause = Action(10, 0, 0);
				pause.tiem = 500;
				charStack[i].actionList.push_back(pause);
				for (int j = 0; j < v.size(); ++j){
					charStack[i].actionList.push_back(v[j]);
				}
			}
		}
	}
	player.update(deltaTime);
	for (int i = 0; i < charStack.size(); ++i)
	{	
		if(AABBIntersect(&player.box, &charStack[i].box)){
			lose = true;
		}
	}
	if(bg->getTile(player.box.x / 32, player.box.y / 32) == 6){
		win = true;
	}
}

void npcHandler::draw(){

	for (int i = 0; i < charStack.size(); ++i)
	{
		charStack[i].drawVision(bg->cameraDim.x, bg->cameraDim.y);
	}
	for (int i = 0; i < charStack.size(); ++i)
	{
		charStack[i].draw(bg->cameraDim.x, bg->cameraDim.y);
	}
	player.draw(bg->cameraDim.x, bg->cameraDim.y);
}



float npcHandler::distance(locNode a, locNode b){
	float x = a.x - b.x;
	float y = a.y - b.y;
	return sqrtf(x * x + y * y);
}

//goes by tile
std::vector<Action> npcHandler::createPath(locNode start, locNode end){
	Astar a = Astar(bg);
	std::vector<locNode> v = a.findPath(&start, &end);
	std::vector<Action> t;
	/*
	printf("Astar.FindPath(): \n");
	for (int i = 0; i < v.size(); ++i)
	{
		printf("(%d, %d) \n", v[i].x, v[i].y);
	}
	*/
	for (int i = v.size()-1; i >= 0 ; --i)
	{
		Action p = Action(1, v[i].x * 32, v[i].y * 32);
		t.push_back(p);
	}
	return t;
}

void npcHandler::movePlayer(int x, int y, unsigned int deltaTime){
	if(x > 0){
		player.x += (player.speed * deltaTime)/1000.0;
		if(player.box.x - bg->cameraDim.x + player.box.w> bg->camDeadZone.x + bg->camDeadZone.w){
			bg->scrollRight(2);
		}
		player.act = 1;
	}else if(x < 0){
		player.x -= (player.speed * deltaTime)/1000.0;
		if(player.box.x - bg->cameraDim.x < bg->camDeadZone.x){
			bg->scrollLeft(2);
		}
		player.act = 3;
	}else if(y > 0){
		player.y += (player.speed * deltaTime)/1000.0;
		if(player.box.y - bg->cameraDim.y + player.box.h > bg->camDeadZone.y + bg->camDeadZone.h){
			bg->scrollDown(2);
		}
		player.act = 2;
	}else if(y < 0){
		player.y -= (player.speed * deltaTime)/1000.0;
		if(player.box.y - bg->cameraDim.y < bg->camDeadZone.y){
			bg->scrollUp(2);
		}
		player.act = 0;
	}
	player.box.x = player.x;
	player.box.y = player.y;
	int px = player.x / 32;
	int py = player.y / 32;
	if(bg->collisionDetect(&player.box)){
		//printf("Rock, coords: (%d, %d)\n",px, py );
		movePlayer(-x, -y, deltaTime);
	}
}

bool npcHandler::lookAtNeighbor(locNode current, locNode end){
	if(current.x == end.x && current.y == end.y){
		finalList.push_back( Action(0, current.x*32, current.y*32));
		return true;
	}else if(bg->getTile(current.x, current.y) >= 7){
		return false;
	}else{
		locNode up = locNode(current.x, current.y - 1);
		locNode right = locNode(current.x + 1, current.y);
		locNode down = locNode(current.x, current.y + 1);
		locNode left = locNode(current.x - 1, current.y);
		std::vector<locNode> list;
		list.reserve(4);
		list.push_back(up);
		list.push_back(right);
		list.push_back(down);
		list.push_back(left);
		for (int i = 0; i < 4; ++i){
			list[i].setG(end);
		}
		while(!list.empty()){
			int use = 0;
			int distance = 99999;
			for (int i = 0; i < list.size(); ++i){
				if(list[i].distanceToGoal < distance){
					use = i;
					distance = list[i].distanceToGoal;
				}
			}
			locNode nodeUsed = list[use];
			list.erase(list.begin()+use);
			bool truth = lookAtNeighbor(nodeUsed, end);
			if(truth){
				finalList.push_back(Action(0, current.x*32, current.y*32));
				return true;
			}
		}
		return false;
	}

}
void npcHandler::test(){
	printf("Testing: \n");
	locNode start =  locNode(25, 4);
	locNode end =  locNode(25,10);
	Astar a = Astar(bg);
	start.gCost = 0;
	start.distanceToGoal = 9999;
	end.gCost = 99999;
	end.distanceToGoal = 0;
	std::vector<Action> v = createPath(start, end);
	printf("Action Path\n");
	for (int i = 0; i < v.size(); ++i)
	{
		printf("(%d, %d) \n", v[i].px, v[i].py);
	}

}

Astar::Astar(BackgroundDef * b){
	bg = b;
}

std::vector<locNode> Astar::findPath(locNode * start, locNode * end){
	openSet.clear();
	openSet.push_back(start);
	start->gCost = 0;
	start->distanceToGoal = 99999;


	while(!openSet.empty()){
		locNode * current = openSet[0];
		
		if(current->x == end->x && current->y == end->y){
			return reversePath(current); //method for creating list
		}
		openSet.erase(openSet.begin());
		closedSet.push_back(current);

		locNode *up = new locNode(current->x, current->y - 1);
		locNode *right = new locNode(current->x + 1, current->y);
		locNode *down = new locNode(current->x, current->y + 1);
		locNode *left = new locNode(current->x - 1, current->y);
		std::vector<locNode*> list;
		list.reserve(4);
		list.push_back(up);
		list.push_back(right);
		list.push_back(down);
		list.push_back(left);
		for (int i = 0; i < 4; ++i){
			//printf("Checking (%d, %d)\n", list[i]->x, list[i]->y);
			int tempgcost = current->gCost + 1;
			int check1 = checkOpenSet(list[i]);
			if(bg->getTile(list[i]->x, list[i]->y) < 7){
				//printf("Passed\n");
				if(check1 > 0){
					if(tempgcost < openSet[check1]->gCost){
						openSet.erase(openSet.begin()+check1);
						check1 = -1;
					}
				}
				int check2 = checkClosedSet(list[i]);
				if(check2 > 0){
					if(tempgcost < closedSet[check2]->gCost){
						closedSet.erase(closedSet.begin()+check2);
						check2 = -1;
					}
				}
				if(check1 < 0 && check2 < 0){
					list[i]->gCost = tempgcost;
					list[i]->parent = current;
					addToOpenSet(list[i]);
				}
			}
		}
	}
	std::vector<locNode> v;
	return v;
}
int Astar::checkClosedSet(locNode* v){
	for (int i = 0; i < closedSet.size(); ++i){
		if(closedSet[i]->x == v->x && closedSet[i]->y == v->y){
			return i;
		}
	}
	return -1;
}
int Astar::checkOpenSet(locNode* v){
	for (int i = 0; i < openSet.size(); ++i){
		if(openSet[i]->x == v->x && openSet[i]->y == v->y){
			return i;
		}
	}
	return -1;
}
void Astar::addToOpenSet(locNode * v){
	float total = v->gCost + v->distanceToGoal;
	if(openSet.empty()){
		openSet.push_back(v);
		return;
	}else{
		for (int i = 0; i < openSet.size(); ++i){
			float t = openSet[i]->distanceToGoal + openSet[i]->distanceToGoal;
			if( total < t){
				openSet.insert(openSet.begin()+i, v);
				return;
			}
		}
		openSet.push_back(v);
	}
}

std::vector<locNode> Astar::reversePath(locNode * end){
	std::vector<locNode> v;
	locNode * current = end;
	while(current->gCost > 0){
		v.push_back(*current);
		current = current->parent;
	}
	v.push_back(*current);
	return v;
}

