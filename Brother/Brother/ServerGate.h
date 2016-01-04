#ifndef GATE_H
#define GATE_H

#include "ServerMap.h"

class Library;


class ServerGate
{
private:
	Library* m_pLibrary;

public:
	ServerGate(Library* pLibrary);
	~ServerGate();



};


#endif