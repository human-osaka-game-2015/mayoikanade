#ifndef _COLLISIONCHECKER_H_
#define _COLLISIONCHECKER_H_
#include "Map.h"

class CollisionChecker
{
private:
	Map* m_pMap;

public:
	CollisionChecker(Map* pMap);
	~CollisionChecker();
	bool HitCheck(float x, float y);
	//bool WoodBoxCheck(float x, float y);
	//Ç›ÇΩÇ¢Ç»ÇÃçÏÇÈÇ¬Ç‡ÇË

};


#endif