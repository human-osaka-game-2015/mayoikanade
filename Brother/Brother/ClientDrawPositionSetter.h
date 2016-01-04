#ifndef DRAWPOSITIONSETTER_H
#define DRAWPOSITIONSETTER_H

class ClientMap;

class ClientDrawPositionSetter
{
private:
	ClientMap* m_pMap;

public:
	ClientDrawPositionSetter(ClientMap* pMap);
	~ClientDrawPositionSetter();
	void DrawPositionXSet(float x);
	void DrawPositionYSet(float y);

};

#endif