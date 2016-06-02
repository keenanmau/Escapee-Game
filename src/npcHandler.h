#ifndef npcHandler_h
#define npcHandler_h
#include <vector>
#include "CharacterDef.h"
#include "BackgroundDef.h"



class npcHandler{
	BackgroundDef * bg;
	std::vector<CharacterData> charStack;
	std::vector<Action> finalList; // goal is at the top, last is start. 
	float distance(locNode a, locNode b);
	CharacterData player;

public:
	bool lose, win;
	npcHandler(BackgroundDef * bgRef);
	void update(unsigned int deltaTime);
	void draw();
	std::vector<Action> createPath(locNode current, locNode end);
	bool lookAtNeighbor(locNode current, locNode end);
	void test();
	void movePlayer(int x, int y, unsigned int deltaTime);
	void createNPC(int x, int y);
	void createNPCpath(int x, int y);
	
};

class Astar{
	std::vector<locNode*> openSet;
	std::vector<locNode*> closedSet;
	BackgroundDef * bg;
public:
	Astar(BackgroundDef * b);
	std::vector<locNode> findPath(locNode *start, locNode *end);
	int checkClosedSet(locNode * v);
	int checkOpenSet(locNode * v);
	void addToOpenSet(locNode * v);
	std::vector<locNode> reversePath(locNode * end);

};

#endif