#ifndef DRAWPOSITIONSETTER_H
#define DRAWPOSITIONSETTER_H

class Map;

class DrawPositionSetter
{
private:
	Map* m_pMap;

public:
	DrawPositionSetter();
	~DrawPositionSetter();
	void DrawPositionXSet(int x);
	void DrawPositionYSet(int y);

};

#endif