#include "IPAddSelectScene.h"
#include "Library.h"
#include <stdio.h>

#define IPADDPANELPOSX 400
#define IPADDPANELPOSY 312

//文字コード define
#define ID0 48
#define ID1 49
#define ID2 50
#define ID3 51
#define ID4 52
#define ID5 53
#define ID6 54
#define ID7 55
#define ID8 56
#define ID9 57
#define IDCOMMA 46
IPAddSelectScene::IPAddSelectScene(Library* pLibrary,char* IPadd) :m_pLibrary(pLibrary)
{
	m_pLibrary->Init_Key();
	D3DXCreateFont(m_pLibrary->GetDevice(), 30, 15, FW_REGULAR, NULL, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, PROOF_QUALITY, FIXED_PITCH | FF_MODERN, "Consolas", &m_pFont);
	memset(IPadd,0,sizeof(IPadd));
	for (int i = 0; i < 16; i++)
	{
		m_IPadd[i] = &IPadd[i];
	}
	//m_pIPadd = IPadd;

	//m_pIPadd = new char*[16] ;
	IPpos = 0;
	m_IPAddPanel.x = IPADDPANELPOSX;
	m_IPAddPanel.y = IPADDPANELPOSY;

	//m_pLibrary->FileInfo_Set("file.csv", FILE_INFO);
	//m_pLibrary->VertexInfo_Set("ConnectingTex.csv", CONNECT_VERTEXINFO_MAX);
	//m_pLibrary->LoadTextureEx("ConnectingScene.png", TEX_CONNECT, 255, 0, 255, 0);


}

IPAddSelectScene::~IPAddSelectScene()
{
	m_pFont->Release();
}

bool IPAddSelectScene::Control()
{
	m_pLibrary->m_pInputDevice->Key_Check(&Key[KEY_1], DIK_1);
	m_pLibrary->m_pInputDevice->Key_Check(&Key[KEY_2], DIK_2);
	m_pLibrary->m_pInputDevice->Key_Check(&Key[KEY_3], DIK_3);
	m_pLibrary->m_pInputDevice->Key_Check(&Key[KEY_4], DIK_4);
	m_pLibrary->m_pInputDevice->Key_Check(&Key[KEY_5], DIK_5);
	m_pLibrary->m_pInputDevice->Key_Check(&Key[KEY_6], DIK_6);
	m_pLibrary->m_pInputDevice->Key_Check(&Key[KEY_7], DIK_7);
	m_pLibrary->m_pInputDevice->Key_Check(&Key[KEY_8], DIK_8);
	m_pLibrary->m_pInputDevice->Key_Check(&Key[KEY_9], DIK_9);
	m_pLibrary->m_pInputDevice->Key_Check(&Key[KEY_0], DIK_0);
	m_pLibrary->m_pInputDevice->Key_Check(&Key[KEY_BACKSPACE], DIK_BACK);
	m_pLibrary->m_pInputDevice->Key_Check(&Key[KEY_FIRE], DIK_RETURN);
	m_pLibrary->m_pInputDevice->Key_Check(&Key[KEY_COMMA], DIK_PERIOD);
	if (Key[KEY_COMMA] == PUSH && IPpos < IPADDSIZE - 1)
	{
		*m_IPadd[IPpos] = IDCOMMA;
		if (IPpos <= IPADDSIZE)
		{
			IPpos++;
		}
	}

	if (Key[KEY_0] == PUSH && IPpos < IPADDSIZE - 1)
	{
		*m_IPadd[IPpos] = ID0;
		if (IPpos <= IPADDSIZE)
		{
			IPpos++;
		}
	}
	if (Key[KEY_1] == PUSH && IPpos < IPADDSIZE - 1)
	{
		*m_IPadd[IPpos] = ID1;
		if (IPpos <= IPADDSIZE)
		{
			IPpos++;
		}
	}
	if (Key[KEY_2] == PUSH && IPpos < IPADDSIZE - 1)
	{
		*m_IPadd[IPpos] = ID2;
		if (IPpos <= IPADDSIZE)
		{
			IPpos++;
		}
	}
	if (Key[KEY_3] == PUSH && IPpos < IPADDSIZE - 1)
	{
		*m_IPadd[IPpos] = ID3;
		if (IPpos <= IPADDSIZE)
		{
			IPpos++;
		}
	}
	if (Key[KEY_4] == PUSH && IPpos < IPADDSIZE - 1)
	{
		*m_IPadd[IPpos] = ID4;
		if (IPpos <= IPADDSIZE)
		{
			IPpos++;
		}
	}
	if (Key[KEY_5] == PUSH && IPpos < IPADDSIZE - 1)
	{
		*m_IPadd[IPpos] = ID5;
		if (IPpos <= IPADDSIZE)
		{
			IPpos++;
		}
	}
	if (Key[KEY_6] == PUSH && IPpos < IPADDSIZE - 1)
	{
		*m_IPadd[IPpos] = ID6;
		if (IPpos <= IPADDSIZE)
		{
			IPpos++;
		}
	}
	if (Key[KEY_7] == PUSH && IPpos < IPADDSIZE - 1)
	{
		*m_IPadd[IPpos] = ID7;
		if (IPpos <= IPADDSIZE)
		{
			IPpos++;
		}
	}
	if (Key[KEY_8] == PUSH && IPpos < IPADDSIZE - 1)
	{
		*m_IPadd[IPpos] = ID8;
		if (IPpos <= IPADDSIZE)
		{
			IPpos++;
		}
	}
	if (Key[KEY_9] == PUSH && IPpos < IPADDSIZE - 1)
	{
		*m_IPadd[IPpos] = ID9;
		if (IPpos <= IPADDSIZE)
		{
			IPpos++;
		}
	}
	if (Key[KEY_BACKSPACE] == PUSH)
	{
		if (IPpos != 0)
		{
			IPpos--;
			*m_IPadd[IPpos] = '\n';
		}
	}
	if (Key[KEY_FIRE] == PUSH)
	{
		return true;
	}
	return false;
}

void IPAddSelectScene::Draw()
{
	CustomVertex IPaddPanel[4];
	//positionの幅高さ設定
	m_pLibrary->MakePosition(CONNECT_IPADD, &m_IPAddPanel);
	//tu　tvの設定
	m_pLibrary->MakeVertex(CONNECT_IPADD, IPaddPanel);

	//X yの設定
	m_pLibrary->xySet(m_IPAddPanel, IPaddPanel);

	m_pLibrary->DrawTexture(TEX_CONNECT, IPaddPanel);

	RECT rect = { IPADDPANELPOSX - 120, IPADDPANELPOSY - 10, 0, 0 };
	RECT Description = { IPADDPANELPOSX - 290, IPADDPANELPOSY - 85, 0, 0 };

	m_pFont->DrawText(NULL, "サーバー側のIPアドレスを入力して下さい", -1, &Description, DT_CALCRECT, NULL);
	m_pFont->DrawText(NULL, "サーバー側のIPアドレスを入力して下さい", -1, &Description, DT_LEFT | DT_BOTTOM, 0xff000000);

	m_pFont->DrawText(NULL, *m_IPadd, -1, &rect, DT_CALCRECT, NULL);
	m_pFont->DrawText(NULL, *m_IPadd, -1, &rect, DT_LEFT | DT_BOTTOM, 0xff000000);

}