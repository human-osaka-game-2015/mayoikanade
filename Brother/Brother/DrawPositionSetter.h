#ifndef SDRAWPOSITIONSETTER_H
#define SDRAWPOSITIONSETTER_H

class Map;

class DrawPositionSetter
{
private:
	Map* m_pMap;

public:
	DrawPositionSetter(Map* pMap);
	~DrawPositionSetter();
	void DrawPositionXSet(float x);
	void DrawPositionYSet(float y);

};

#endif