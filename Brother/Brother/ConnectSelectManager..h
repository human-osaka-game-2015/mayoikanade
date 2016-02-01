
#ifndef CONNECTSELECTMANAGER_H
#define CONNECTSELECTMANAGER_H
#include "Library.h"

enum CONNECT_TYPE
{
	CLIENT_TYPE,
	SERVER_TYPE,
	CONNECTSELECT_NONE
};

enum CONNECTANIMA_ID
{
	CONNECTCURSOL_ANIMA,
	CONNECTANIMA_ID_MAX
};

class ConnectSelectManager
{
private:
	Library*	m_pLibrary;

	bool*		m_PadState;
	bool*		m_PadOldState;
	Position	m_CursolPos;
	Position	m_ServerPos;
	Position	m_ClientPos;
	CONNECT_TYPE m_ConnectType;
	CONNECTANIMA_ID m_CursolCurrentAnima;
	KEYSTATE Key[KEYKIND_MAX];

public:
	ConnectSelectManager(Library* pLibrary, bool* pPadState, bool* pPadOldState);
	~ConnectSelectManager();
	CONNECT_TYPE Control();
	void Draw();
};

#endif
