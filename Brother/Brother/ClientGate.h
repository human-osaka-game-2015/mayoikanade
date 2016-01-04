#ifndef sGATE_H
#define sGATE_H

#include "ClientMap.h"

class Library;


class ClientGate
{
private:
	Library* m_pLibrary;

public:
	ClientGate(Library* pLibrary);
	~ClientGate();



};


#endif