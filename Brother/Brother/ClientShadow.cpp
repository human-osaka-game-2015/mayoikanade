#include "ClientShadow.h"
#include "ClientGameScene.h"
#include "Library.h"
#include "ClientGameTimeManager.h"
#include "ClientModeManager.h"

ClientShadow::ClientShadow(Library* pLibrary, ClientGameTimeManager* pGameTimeManager) :m_pLibrary(pLibrary), m_GameTimeManager(pGameTimeManager)
{
	m_Pos.x = 600;
	m_Pos.y = 350;
	m_Pos.h = 2000;
	m_Pos.w = 2000;

}

ClientShadow::~ClientShadow()
{

}

void ClientShadow::Control()
{
	switch (m_pModeManager->GetMode())
	{
	case NORMAL:											//NormalDrawŠÖ”‚Å‚àì‚é‚×‚«‚©‚à

		if (m_GameTimeManager->GetGameTime() % 60 == 0)
		{
			m_Pos.h -= 10;
			m_Pos.w -= 10;
		}

		if (m_Pos.h <= 0 || m_Pos.w <= 0)
		{
			m_Pos.h = 0;
			m_Pos.w = 0;
		}

		break;
	case TEXT:

		break;
	case GAMEOVEREFFECT:

		m_Pos.h -= 9;
		m_Pos.w -= 9;

		if (m_Pos.h <= 0 || m_Pos.w <= 0)
		{
			m_Pos.h = 0;
			m_Pos.w = 0;
		}

		break;
	case GAMEOVER:

		break;
	}
}

void ClientShadow::Draw()
{
	CustomVertex stencilVertex[4] =
	{
		{ 0.0, 0.0, 0.5, 1.0, 0xFFFFFFFF, 0.0, 0.0 },
		{ 0.0, 0.0, 0.5, 1.0, 0xFFFFFFFF, 1.0, 0.0 },
		{ 0.0, 0.0, 0.5, 1.0, 0xFFFFFFFF, 1.0, 1.0 },
		{ 0.0, 0.0, 0.5, 1.0, 0xFFFFFFFF, 0.0, 1.0 }
	};

	m_pLibrary->xySet(m_Pos, stencilVertex);

	m_pLibrary->AlphaTestReady(0x00);

	m_pLibrary->StencilRefSet(0x02);
	m_pLibrary->StencilDrawReady();



	m_pLibrary->DrawTexture(STENCIL, stencilVertex);

	m_pLibrary->StencilRefSet(0x02);
	m_pLibrary->StencilDrawEnd();

	m_pLibrary->AlphaTestEnd();
}

void ClientShadow::ModeManagerSet(ClientModeManager* pModeManager)
{
	m_pModeManager = pModeManager;
}

bool ClientShadow::ShadowCheck()
{
	if (m_Pos.w <= 0)
	{
		return true;
	}

	return false;
}
