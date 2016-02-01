#include "Library.h"
#include "ConnectingScene.h"

class ListenServer
{
private:
	Library*	m_pLibrary;
	LPD3DXFONT	m_pFont;
	bool m_connectOK;
public:
	ListenServer(Library* pLibrary);
	~ListenServer();
	void Draw();
	bool Control();

};

