#include "ListenServer.h"

ListenServer::ListenServer(Library* pLibrary) :m_pLibrary(pLibrary)
{
	//m_pLibrary->FileInfo_Set("file.csv", FILE_INFO);
	//m_pLibrary->VertexInfo_Set("ConnectingTex.csv", CONNECT_VERTEXINFO_MAX);
	//m_pLibrary->LoadTextureEx("ConnectingScene.png", TEX_CONNECT, 255, 0, 255, 0);
	D3DXCreateFont(m_pLibrary->GetDevice(), 30, 15, FW_REGULAR, NULL, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, PROOF_QUALITY, FIXED_PITCH | FF_MODERN, "Consolas", &m_pFont);
}

ListenServer::~ListenServer()
{

	m_pFont->Release();
}

void ListenServer::Draw()
{
	RECT rect = {500,500 , 0, 0 };

	m_pFont->DrawText(NULL, "サーバー待機中", -1, &rect, DT_CALCRECT, NULL);
	m_pFont->DrawText(NULL, "サーバー待機中", -1, &rect, DT_LEFT | DT_BOTTOM, 0xff000000);
}

bool ListenServer::Control()
{
	return false;
}