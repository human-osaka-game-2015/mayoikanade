#ifndef GATE_H
#define GATE_H

#include "Map.h"

class Library;


class Gate
{
private:
	Library* m_pLibrary;

public:
	Gate(Library* pLibrary);
	~Gate();



};


#endif