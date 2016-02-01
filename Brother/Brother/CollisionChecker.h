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
	bool WoodBoxCheck(float x, float y);
	bool WoodBoxSet(float x, float y);
	void SwitchOn(float x, float y);
	void SwitchOnYoung(float x, float y);

	bool GrassPortRaitCheck(float x, float y);
	bool GrassCheck(float x, float y);
	bool AppleCheck(float x, float y);
};


#endif