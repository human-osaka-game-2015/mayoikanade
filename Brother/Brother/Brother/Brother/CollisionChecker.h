#ifndef COLLISIONCHECKER_H
#define COLLISIONCHECKER_H

class Map;

class CollisionChecker
{
private:
	Map* m_pMap;

public:
	CollisionChecker(Map* pMap);
	~CollisionChecker();
	bool HitCheck(float x, float y);

};


#endif