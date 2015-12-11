#include "Shadow.h"
#include "GameScene.h"
#include "Library.h"
#include "GameTimeManager.h"

Shadow::Shadow(Library* pLibrary, GameTimeManager* pGameTimeManager) :m_pLibrary(pLibrary), m_GameTimeManager(pGameTimeManager)
{
	m_Pos.x = 600;
	m_Pos.y = 350;
	m_Pos.h = 2000;
	m_Pos.w = 2000;

}

Shadow::~Shadow()
{

}

void Shadow::Control()
{
	int time = m_GameTimeManager->GetGameTime();
	if (time % 60 == 0)
	{
		m_Pos.h -= 50;
		m_Pos.w -= 50;
	}

	if (m_Pos.h <= 0 || m_Pos.w <= 0)
	{
		m_Pos.h = 0;
		m_Pos.w = 0;
	}
}

void Shadow::Draw()
{
	CustomVertex stencilVertex[4] =
	{
		{ 0.0, 0.0, 0.5, 1.0, 0xFFFFFFFF, 0.0, 0.0 },
		{ 0.0, 0.0, 0.5, 1.0, 0xFFFFFFFF, 1.0, 0.0 },
		{ 0.0, 0.0, 0.5, 1.0, 0xFFFFFFFF, 1.0, 1.0 },
		{ 0.0, 0.0, 0.5, 1.0, 0xFFFFFFFF, 0.0, 1.0 }
	};

	m_pLibrary->xySet(m_Pos,stencilVertex);

	m_pLibrary->AlphaTestReady(0x00);

	m_pLibrary->StencilRefSet(0x02);
	m_pLibrary->StencilDrawReady();

	

	m_pLibrary->DrawTexture(STENCIL, stencilVertex);

	m_pLibrary->StencilRefSet(0x02);
	m_pLibrary->StencilDrawEnd();

	m_pLibrary->AlphaTestEnd();
}

void Shadow::ModeManagerSet(ModeManager* pModeManager)
{
	m_pModeManager = pModeManager;
}

bool Shadow::ShadowCheck()
{
	if (m_Pos.w <= 0)
	{
		return true;
	}

	return false;
}
