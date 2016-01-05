#ifndef COLLISIONCHECKER_H
#define COLLISIONCHECKER_H

class ServerMap;

class ServerCollisionChecker
{
private:
	ServerMap* m_pMap;

public:
	ServerCollisionChecker(ServerMap* pMap);
	~ServerCollisionChecker();
	bool HitCheck(float x, float y);
	bool WoodBoxCheck(float x, float y);
	bool WoodBoxSet(float x, float y);
	void SwitchOn(float x, float y);
	void SwitchOnYoung(float x, float y);

};


#endif