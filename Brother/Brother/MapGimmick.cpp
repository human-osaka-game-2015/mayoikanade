#include "GameScene.h"
#include "Switch.h"
#include "Gate.h"
#include "MapGimmick.h"
#include "Library.h"


MapGimmick::MapGimmick(Library* pLibrary) :m_pLibrary(pLibrary)
{
	CsvRead("gimmick.csv");
}

MapGimmick::~MapGimmick()
{

}

bool MapGimmick::CsvRead(const char* filename)
{
	FILE*  fp = NULL;
	fopen_s(&fp, filename, "r");

	if (fp == NULL)
	{
		return false;
	}

	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			fscanf_s(fp, "%d,", &m_GimmickData[i][j], _countof(m_GimmickData));
		}
	}
	fclose(fp);

	return true;
}


//今のところ使っていない、SwitchクラスとGateクラスを実装することになったら使う
void MapGimmick::Init()
{
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			switch (m_GimmickData[i][j]/10000)
			{
			case GATE_01:
				m_Gate.push_back(Gate(m_pLibrary));
				break;
			case SWITCH_RED_01:
				int Id = m_GimmickData[i][j] % 10000;
				m_Switch.push_back(Switch(m_pLibrary,Id, m_GimmickData, SWITCH_RED_01));
				break;

			}
		}
	}
}


void MapGimmick::Control()
{

}


void MapGimmick::Draw(float DrawPosX, float DrawPosY)
{
	int count_x = int((DrawPosX - 64) / MAPTIP_SIZE);
	int count_y = int((DrawPosY - 64) / MAPTIP_SIZE);

	if (count_x < 0)
	{
		count_x = 0;
	}
	if (count_y < 0)
	{
		count_y = 0;
	}


	//描画領域を求めて代入 余分に一つ先も読んでるので64足している
	int ScreenRight = int((DrawPosX + SCREEN_SIZEX + 64) / MAPTIP_SIZE);
	int ScreenBottom = int((DrawPosY + SCREEN_SIZEY + 64) / MAPTIP_SIZE);

	if (ScreenRight > MAP_WIDTH)
	{
		ScreenRight = MAP_WIDTH;
	}
	if (ScreenBottom > MAP_HEIGHT)
	{
		ScreenBottom = MAP_HEIGHT;
	}

	for (int i = count_y; i < ScreenBottom; i++)
	{
		for (int j = count_x; j < ScreenRight; j++)
		{
			m_pLibrary->DrawTexture(TEX_GAME, m_MapGimmick_Tex[i][j]);
		}
	}
}


int MapGimmick::GimmickCheck(float x, float y)
{
	int arrayx = 0, arrayy = 0;
	arrayx = int(x / 64);
	arrayy = int(y / 64);


	//スイッチが押された時の処理
	//現状はここでやっているが、できればswitchクラスに乗せたい
	switch (m_GimmickData[arrayy][arrayx] / 10000)
	{
	case SWITCH_RED_01:
		m_GimmickData[arrayy][arrayx] = (m_GimmickData[arrayy][arrayx] % 10000 + SWITCH_RED_02 *10000);
		
		for (int i = 0; i < MAP_HEIGHT; i++)
		{
			for (int j = 0; j < MAP_WIDTH; j++)
			{
				if (m_GimmickData[i][j] / 10000 == GATE_01 || m_GimmickData[i][j] / 10000 == GATE_02)
				{
					m_GimmickData[i][j] = 0;

				}
			}
		}
		
		break;
	case SWITCH_BLUE_01:

		break;
	case SWITCH_YELLOW_01:

		break;
	default:
		break;
	}

	return m_GimmickData[arrayy][arrayx]/10000;
}




void MapGimmick::MapTex_UV_Set(float Posx, float Posy)
{
	int count_x = int((Posx - 64) / MAPTIP_SIZE);
	int count_y = int((Posy - 64) / MAPTIP_SIZE);


	if (count_x < 0)
	{
		count_x = 0;
	}
	if (count_y < 0)
	{
		count_y = 0;
	}


	//描画領域を求めて代入 余分に一つ先も読んでるので64足している
	int ScreenRight = int((Posx + SCREEN_SIZEX + 64) / MAPTIP_SIZE);
	int ScreenBottom = int((Posy + SCREEN_SIZEY + 64) / MAPTIP_SIZE);

	if (ScreenRight > MAP_WIDTH)
	{
		ScreenRight = MAP_WIDTH;
	}
	if (ScreenBottom > MAP_HEIGHT)
	{
		ScreenBottom = MAP_HEIGHT;
	}


	for (int i = count_y; i <= ScreenBottom; i++)
	{
		for (int j = count_x; j <= ScreenRight; j++)
		{
			switch (m_GimmickData[i][j] / 10000)
			{
			case SWITCH_RED_01:
				m_pLibrary->MakeVertex(SWITCH_RED_01, m_MapGimmick_Tex[i][j]);

				break;
			case SWITCH_RED_02:
				m_pLibrary->MakeVertex(SWITCH_RED_02, m_MapGimmick_Tex[i][j]);

				break;
			case GATEPOST_01:
				m_pLibrary->MakeVertex(GATEPOST_01, m_MapGimmick_Tex[i][j]);

				break;
			case GATEPOST_02:
				m_pLibrary->MakeVertex(GATEPOST_02, m_MapGimmick_Tex[i][j]);
				m_pLibrary->UVReversal(m_MapGimmick_Tex[i][j], LEFT_AND_RIGHT);


				break;
			case GATE_01:
				m_pLibrary->MakeVertex(GATE_01, m_MapGimmick_Tex[i][j]);

				break;
			case GATE_02:
				m_pLibrary->MakeVertex(GATE_02, m_MapGimmick_Tex[i][j]);
				m_pLibrary->UVReversal(m_MapGimmick_Tex[i][j], LEFT_AND_RIGHT);
				break;
			default:
				for (int x = 0; x < VERTEXNUM; x++)
				{
					m_MapGimmick_Tex[i][j][x].color = DEFAULTCOLOR;
					m_MapGimmick_Tex[i][j][x].rhw = DEFAULTRHW;
					m_MapGimmick_Tex[i][j][x].z = DEFAULTZ;
					m_MapGimmick_Tex[i][j][x].tu = 0;
					m_MapGimmick_Tex[i][j][x].tv = 0;

				}
				break;
			}
		}
	}
}


void MapGimmick::MapTex_XY_Set(float Posx, float Posy)
{
	int count_x = int((Posx - 64) / MAPTIP_SIZE);
	int count_y = int((Posy - 64) / MAPTIP_SIZE);


	if (count_x < 1)
	{
		count_x = 1;
	}
	if (count_y < 1)
	{
		count_y = 1;
	}


	//描画領域を求めて代入 余分に一つ先も読んでるので64足している
	int ScreenRight =  int((Posx + SCREEN_SIZEX + 64) / MAPTIP_SIZE);
	int ScreenBottom = int((Posy + SCREEN_SIZEY + 64) / MAPTIP_SIZE);

	if (ScreenRight > MAP_WIDTH)
	{
		ScreenRight = MAP_WIDTH;
	}
	if (ScreenBottom > MAP_HEIGHT)
	{
		ScreenBottom = MAP_HEIGHT;
	}


	for (int i = count_y; i <= ScreenBottom; i++)
	{
		for (int j = count_x; j <= ScreenRight; j++)
		{
			{
				//当たり判定用のXYを入れる
				m_MapGimmick_Pos[i - 1][j - 1].x = (float)(MAPTIP_SIZE * j) - MAPTIP_DEFAULT_POSX;
				m_MapGimmick_Pos[i - 1][j - 1].y = (float)(MAPTIP_SIZE * i) - MAPTIP_DEFAULT_POSY;
				m_MapGimmick_Pos[i - 1][j - 1].w = (float)MAPTIP_SIZE;
				m_MapGimmick_Pos[i - 1][j - 1].h = (float)MAPTIP_SIZE;
				m_MapGimmick_Pos[i - 1][j - 1].x -= Posx;
				m_MapGimmick_Pos[i - 1][j - 1].y -= Posy;

				m_pLibrary->xySet(m_MapGimmick_Pos[i - 1][j - 1], m_MapGimmick_Tex[i - 1][j - 1]);
			}
		}
	}
}
