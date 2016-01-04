#ifndef SDRAWPOSITIONSETTER_H
#define SDRAWPOSITIONSETTER_H

class ServerMap;

class ServerDrawPositionSetter
{
private:
	ServerMap* m_pMap;

public:
	ServerDrawPositionSetter(ServerMap* pMap);
	~ServerDrawPositionSetter();
	void DrawPositionXSet(float x);
	void DrawPositionYSet(float y);

};

#endif