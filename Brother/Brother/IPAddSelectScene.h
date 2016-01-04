#include "Library.h"
#include "ConnectingScene.h"
#define IPADDSIZE 16

class IPAddSelectScene
{
private:
	Library*	m_pLibrary;
	LPD3DXFONT	m_pFont;
	Position	m_IPAddPanel;

	char* m_IPadd[16];
	int IPpos;
	KEYSTATE Key[KEYKIND_MAX];
public:
	IPAddSelectScene(Library* pLibrary, char* IPadd);
	~IPAddSelectScene();
	void Draw();
	bool Control();

};

