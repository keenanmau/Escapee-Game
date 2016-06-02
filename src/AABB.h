#ifndef AABB_h
#define AABB_h

struct AABB {
	int x, y, w, h;
};

inline bool AABBIntersect(const AABB* box1, const AABB* box2 ){
// box1 to the right
	if( box1->x > box2->x + box2->w ) {
		return false;
	}
// box1 to the left
	if( box1->x + box1->w < box2->x ) {
		return false;
	}
// box1 below
	if( box1->y > box2->y + box2->h ) {
		return false;
	}
// box1 above
	if( box1->y + box1->h < box2->y ) {
		return false;
	}
return true;
}


//distance of the corners is the same as distance of their centers

inline bool rayCasting(const AABB* box1, const AABB* box2){
	int xDistance = box1->x - box2->x;
	int yDistance = box1->y - box2->y;
	if( (xDistance * xDistance) + (yDistance*yDistance) > 20 * 20 ) {
		return true;
	}
	return false;
}


#endif