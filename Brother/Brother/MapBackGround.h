#ifndef _MAPBACKGROUND_H_
#define _MAPBACKGROUND_H_
class Library;



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