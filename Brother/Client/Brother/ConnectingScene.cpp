#include "ConnectingScene.h"




ConnectingScene::ConnectingScene(Library* pLibrary) :Scene(pLibrary)
{
	D3DXCreateFont(m_pLibrary->GetDevice(), 0, 8, FW_REGULAR, NULL, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, PROOF_QUALITY, FIXED_PITCH | FF_MODERN, "tahoma", &pFont);

	//time‚Ì‰Šú‰»
	m_time = 0;
	
}

ConnectingScene::~ConnectingScene()
{
	pFont->Release();
}

SCENE_NUM ConnectingScene::Control()
{
	return m_NextScene;
}

void ConnectingScene::Draw()
{

}

void ConnectingScene::PadCheck()
{

}
