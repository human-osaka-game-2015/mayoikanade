#ifndef _MAPGIMMICK_H_
#define _MAPGIMMICK_H_
class Library;

class MapGimmick
{
private:
	Library*	m_pLibrary;

public:
	MapGimmick(Library* pLibrary);
	~MapGimmick();
	void Control();
	void Draw();

};

#endif