#ifndef COLLISIONCHECKER_H
#define COLLISIONCHECKER_H

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
	//�݂����Ȃ̍�����

};


#endif