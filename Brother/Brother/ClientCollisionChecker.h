#ifndef cCOLLISIONCHECKER_H
#define cCOLLISIONCHECKER_H

class ClientMap;

class ClientCollisionChecker
{
private:
	ClientMap* m_pMap;

public:
	ClientCollisionChecker(ClientMap* pMap);
	~ClientCollisionChecker();
	bool HitCheck(float x, float y);
	bool WoodBoxCheck(float x, float y);
	bool WoodBoxSet(float x, float y);
	void SwitchOn(float x, float y);
	void SwitchOnYoung(float x, float y);
};


#endif