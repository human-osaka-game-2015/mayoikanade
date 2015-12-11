#ifndef STENCILMANAGER_H
#define STENCILMANAGER_H

#include <Windows.h>
#include "Vertex.h"

class StencilManager
{
private:
	BYTE m_StencilRef;

public:
	StencilManager();
	~StencilManager();
	void StencilDrawReady();
	void StencilDrawEnd();
	void StencilRefSet(BYTE ref);
	void StencilDraw(CustomVertex* vertex);
	void AlphaTestReady(BYTE ref);
	void AlphaTestEnd();
	void StencilTestEnd();

};


#endif