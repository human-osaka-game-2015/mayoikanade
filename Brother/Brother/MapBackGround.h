#ifndef _MAPBACKGROUND_H_
#define _MAPBACKGROUND_H_
class Library;

enum BACKGROUND_ID
{
	GRASS_23 = 23,
	GROUND_24,
	BACKGROUND_MAX
};

class MapBackGround
{
private:
	Library*	m_pLibrary;

public:
	MapBackGround(Library* pLibrary);
	~MapBackGround();
	void Draw();

};


#endif