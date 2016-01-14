#include "ClientGameScene.h"
#include "ClientSwitch.h"
#include "ClientMapGimmick.h"
#include "ClientGate.h"
#include "Library.h"



ClientMapGimmick::ClientMapGimmick(Library* pLibrary) :m_pLibrary(pLibrary)
{
	CsvRead("Stage1_Gimmick.csv");
}

ClientMapGimmick::~ClientMapGimmick()
{

}

bool ClientMapGimmick::CsvRead(const char* filename)
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
void ClientMapGimmick::Init()
{
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			switch (m_GimmickData[i][j] / 10000)
			{
			case GATE_01:
				m_Gate.push_back(ClientGate(m_pLibrary));
				break;
			case SWITCH_RED_01:
				int Id = m_GimmickData[i][j] % 10000;
				m_Switch.push_back(ClientSwitch(m_pLibrary, Id, m_GimmickData, SWITCH_RED_01));
				break;

			}
		}
	}
}


void ClientMapGimmick::Control()
{

}


void ClientMapGimmick::Draw(float DrawPosX, float DrawPosY)
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


int ClientMapGimmick::GimmickCheck(float x, float y)
{
	int arrayx = 0, arrayy = 0;
	arrayx = int(x / 64);
	arrayy = int(y / 64);

	return m_GimmickData[arrayy][arrayx] / 10000;
}


void ClientMapGimmick::SwitchOn(float x, float y)
{
	int arrayx = 0, arrayy = 0;
	int switchCount = 0;
	arrayx = int(x / 64);
	arrayy = int(y / 64);


	//スイッチが押された時の処理
	//現状はここでやっているが、できればswitchクラスに乗せたい
	switch (m_GimmickData[arrayy][arrayx] / 10000)
	{
	case SWITCH_RED_01:

		m_GimmickData[arrayy][arrayx] = (m_GimmickData[arrayy][arrayx] % 10000 + SWITCH_RED_02 * 10000);
		switchCount = 0;

		for (int i = 0; i < MAP_HEIGHT; i++)
		{
			for (int j = 0; j < MAP_WIDTH; j++)
			{
				if (m_GimmickData[i][j] == m_GimmickData[arrayy][arrayx] % 10000 + SWITCH_RED_01 * 10000)
				{
					switchCount++;
				}
			}
		}

		if (switchCount == 0)
		{

			for (int i = 0; i < MAP_HEIGHT; i++)
			{
				for (int j = 0; j < MAP_WIDTH; j++)
				{
					if (m_GimmickData[i][j] / 10000 == GATE_01 && m_GimmickData[i][j] % 10000 == m_GimmickData[arrayy][arrayx] % 10000)
					{
						m_GimmickData[i][j] = (LOSTGATE_01 * 10000) + (m_GimmickData[i][j] % 10000);
					}
					else if (m_GimmickData[i][j] / 10000 == GATE_02 && m_GimmickData[i][j] % 10000 == m_GimmickData[arrayy][arrayx] % 10000)
					{
						m_GimmickData[i][j] = (LOSTGATE_02 * 10000) + (m_GimmickData[i][j] % 10000);
					}
					else if (m_GimmickData[i][j] / 10000 == GATE_PORTRAIT_01 && m_GimmickData[i][j] % 10000 == m_GimmickData[arrayy][arrayx] % 10000)
					{
						m_GimmickData[i][j] = (LOSTGATE_03 * 10000) + (m_GimmickData[i][j] % 10000);
					}
					else if (m_GimmickData[i][j] / 10000 == GATE_PORTRAIT_02 && m_GimmickData[i][j] % 10000 == m_GimmickData[arrayy][arrayx] % 10000)
					{
						m_GimmickData[i][j] = (LOSTGATE_04 * 10000) + (m_GimmickData[i][j] % 10000);
					}
				}
			}
		}

		
		break;
	case SWITCH_BLUE_01:
		m_GimmickData[arrayy][arrayx] = (m_GimmickData[arrayy][arrayx] % 10000 + SWITCH_BLUE_02 * 10000);
		switchCount = 0;

		for (int i = 0; i < MAP_HEIGHT; i++)
		{
			for (int j = 0; j < MAP_WIDTH; j++)
			{
				if (m_GimmickData[i][j] == m_GimmickData[arrayy][arrayx] % 10000 + SWITCH_BLUE_01 * 10000)
				{
					switchCount++;
				}
			}
		}

		if (switchCount == 0)
		{
			for (int i = 0; i < MAP_HEIGHT; i++)
			{
				for (int j = 0; j < MAP_WIDTH; j++)
				{
					if (m_GimmickData[i][j] / 10000 == GATE_01 && m_GimmickData[i][j] % 10000 == m_GimmickData[arrayy][arrayx] % 10000)
					{
						m_GimmickData[i][j] = (LOSTGATE_01 * 10000) + (m_GimmickData[i][j] % 10000);
					}
					else if (m_GimmickData[i][j] / 10000 == GATE_02 && m_GimmickData[i][j] % 10000 == m_GimmickData[arrayy][arrayx] % 10000)
					{
						m_GimmickData[i][j] = (LOSTGATE_02 * 10000) + (m_GimmickData[i][j] % 10000);
					}
					else if (m_GimmickData[i][j] / 10000 == GATE_PORTRAIT_01 && m_GimmickData[i][j] % 10000 == m_GimmickData[arrayy][arrayx] % 10000)
					{
						m_GimmickData[i][j] = (LOSTGATE_03 * 10000) + (m_GimmickData[i][j] % 10000);
					}
					else if (m_GimmickData[i][j] / 10000 == GATE_PORTRAIT_02 && m_GimmickData[i][j] % 10000 == m_GimmickData[arrayy][arrayx] % 10000)
					{
						m_GimmickData[i][j] = (LOSTGATE_04 * 10000) + (m_GimmickData[i][j] % 10000);
					}
				}
			}
		}

		break;
	case SWITCH_YELLOW_01:
		m_GimmickData[arrayy][arrayx] = (m_GimmickData[arrayy][arrayx] % 10000 + SWITCH_YELLOW_02 * 10000);
		switchCount = 0;

		for (int i = 0; i < MAP_HEIGHT; i++)
		{
			for (int j = 0; j < MAP_WIDTH; j++)
			{
				if (m_GimmickData[i][j] == m_GimmickData[arrayy][arrayx] % 10000 + SWITCH_YELLOW_01 * 10000)
				{
					switchCount++;
				}
			}
		}

		if (switchCount == 0)
		{

			for (int i = 0; i < MAP_HEIGHT; i++)
			{
				for (int j = 0; j < MAP_WIDTH; j++)
				{
					if (m_GimmickData[i][j] / 10000 == GATE_01 && m_GimmickData[i][j] % 10000 == m_GimmickData[arrayy][arrayx] % 10000)
					{
						m_GimmickData[i][j] = (LOSTGATE_01 * 10000) + (m_GimmickData[i][j] % 10000);
					}
					else if (m_GimmickData[i][j] / 10000 == GATE_02 && m_GimmickData[i][j] % 10000 == m_GimmickData[arrayy][arrayx] % 10000)
					{
						m_GimmickData[i][j] = (LOSTGATE_02 * 10000) + (m_GimmickData[i][j] % 10000);
					}
					else if (m_GimmickData[i][j] / 10000 == GATE_PORTRAIT_01 && m_GimmickData[i][j] % 10000 == m_GimmickData[arrayy][arrayx] % 10000)
					{
						m_GimmickData[i][j] = (LOSTGATE_03 * 10000) + (m_GimmickData[i][j] % 10000);
					}
					else if (m_GimmickData[i][j] / 10000 == GATE_PORTRAIT_02 && m_GimmickData[i][j] % 10000 == m_GimmickData[arrayy][arrayx] % 10000)
					{
						m_GimmickData[i][j] = (LOSTGATE_04 * 10000) + (m_GimmickData[i][j] % 10000);
					}
				}
			}
		}

		break;
	default:
		break;
	}

}



void ClientMapGimmick::SwitchOnYoung(float x, float y)
{
	int arrayx = 0, arrayy = 0;
	int switchCount = 0;
	arrayx = int(x / 64);
	arrayy = int(y / 64);


	//スイッチが押された時の処理
	//現状はここでやっているが、できればswitchクラスに乗せたい
	switch (m_GimmickData[arrayy][arrayx] / 10000)
	{
	case SWITCH_RED_01:
		break;
	case SWITCH_BLUE_01:
		m_GimmickData[arrayy][arrayx] = (m_GimmickData[arrayy][arrayx] % 10000 + SWITCH_BLUE_02 * 10000);
		switchCount = 0;

		for (int i = 0; i < MAP_HEIGHT; i++)
		{
			for (int j = 0; j < MAP_WIDTH; j++)
			{
				if (m_GimmickData[i][j] == m_GimmickData[arrayy][arrayx] % 10000 + SWITCH_BLUE_01 * 10000)
				{
					switchCount++;
				}
			}
		}

		if (switchCount == 0)
		{
			for (int i = 0; i < MAP_HEIGHT; i++)
			{
				for (int j = 0; j < MAP_WIDTH; j++)
				{
					if (m_GimmickData[i][j] / 10000 == GATE_01 && m_GimmickData[i][j] % 10000 == m_GimmickData[arrayy][arrayx] % 10000)
					{
						m_GimmickData[i][j] = (LOSTGATE_01 * 10000) + (m_GimmickData[i][j] % 10000);
					}
					else if (m_GimmickData[i][j] / 10000 == GATE_02 && m_GimmickData[i][j] % 10000 == m_GimmickData[arrayy][arrayx] % 10000)
					{
						m_GimmickData[i][j] = (LOSTGATE_02 * 10000) + (m_GimmickData[i][j] % 10000);
					}
					else if (m_GimmickData[i][j] / 10000 == GATE_PORTRAIT_01 && m_GimmickData[i][j] % 10000 == m_GimmickData[arrayy][arrayx] % 10000)
					{
						m_GimmickData[i][j] = (LOSTGATE_03 * 10000) + (m_GimmickData[i][j] % 10000);
					}
					else if (m_GimmickData[i][j] / 10000 == GATE_PORTRAIT_02 && m_GimmickData[i][j] % 10000 == m_GimmickData[arrayy][arrayx] % 10000)
					{
						m_GimmickData[i][j] = (LOSTGATE_04 * 10000) + (m_GimmickData[i][j] % 10000);
					}
				}
			}
		}

		break;
	case SWITCH_YELLOW_01:
		m_GimmickData[arrayy][arrayx] = (m_GimmickData[arrayy][arrayx] % 10000 + SWITCH_YELLOW_02 * 10000);
		switchCount = 0;

		for (int i = 0; i < MAP_HEIGHT; i++)
		{
			for (int j = 0; j < MAP_WIDTH; j++)
			{
				if (m_GimmickData[i][j] == m_GimmickData[arrayy][arrayx] % 10000 + SWITCH_YELLOW_01 * 10000)
				{
					switchCount++;
				}
			}
		}

		if (switchCount == 0)
		{

			for (int i = 0; i < MAP_HEIGHT; i++)
			{
				for (int j = 0; j < MAP_WIDTH; j++)
				{
					if (m_GimmickData[i][j] / 10000 == GATE_01 && m_GimmickData[i][j] % 10000 == m_GimmickData[arrayy][arrayx] % 10000)
					{
						m_GimmickData[i][j] = (LOSTGATE_01 * 10000) + (m_GimmickData[i][j] % 10000);
					}
					else if (m_GimmickData[i][j] / 10000 == GATE_02 && m_GimmickData[i][j] % 10000 == m_GimmickData[arrayy][arrayx] % 10000)
					{
						m_GimmickData[i][j] = (LOSTGATE_02 * 10000) + (m_GimmickData[i][j] % 10000);
					}
					else if (m_GimmickData[i][j] / 10000 == GATE_PORTRAIT_01 && m_GimmickData[i][j] % 10000 == m_GimmickData[arrayy][arrayx] % 10000)
					{
						m_GimmickData[i][j] = (LOSTGATE_03 * 10000) + (m_GimmickData[i][j] % 10000);
					}
					else if (m_GimmickData[i][j] / 10000 == GATE_PORTRAIT_02 && m_GimmickData[i][j] % 10000 == m_GimmickData[arrayy][arrayx] % 10000)
					{
						m_GimmickData[i][j] = (LOSTGATE_04 * 10000) + (m_GimmickData[i][j] % 10000);
					}
				}
			}
		}

		break;
	default:
		break;
	}

}



void ClientMapGimmick::SwitchOff(float x, float y)
{
	int arrayx = 0, arrayy = 0;
	arrayx = int(x / 64);
	arrayy = int(y / 64);


	//スイッチが押された時の処理
	//現状はここでやっているが、できればswitchクラスに乗せたい
	switch (m_GimmickData[arrayy][arrayx] / 10000)
	{
	case SWITCH_RED_02:
		m_GimmickData[arrayy][arrayx] = (m_GimmickData[arrayy][arrayx] % 10000 + SWITCH_RED_01 * 10000);

		for (int i = 0; i < MAP_HEIGHT; i++)
		{
			for (int j = 0; j < MAP_WIDTH; j++)
			{
				if (m_GimmickData[i][j] / 10000 == LOSTGATE_01 && m_GimmickData[i][j] % 10000 == m_GimmickData[arrayy][arrayx] % 10000)
				{
					m_GimmickData[i][j] = (GATE_01 * 10000) + (m_GimmickData[i][j] % 10000);
				}
				else if (m_GimmickData[i][j] / 10000 == LOSTGATE_02 && m_GimmickData[i][j] % 10000 == m_GimmickData[arrayy][arrayx] % 10000)
				{
					m_GimmickData[i][j] = (GATE_02 * 10000) + (m_GimmickData[i][j] % 10000);
				}
				else if (m_GimmickData[i][j] / 10000 == LOSTGATE_03 && m_GimmickData[i][j] % 10000 == m_GimmickData[arrayy][arrayx] % 10000)
				{
					m_GimmickData[i][j] = (GATE_PORTRAIT_01 * 10000) + (m_GimmickData[i][j] % 10000);
				}
				else if (m_GimmickData[i][j] / 10000 == LOSTGATE_04 && m_GimmickData[i][j] % 10000 == m_GimmickData[arrayy][arrayx] % 10000)
				{
					m_GimmickData[i][j] = (GATE_PORTRAIT_02 * 10000) + (m_GimmickData[i][j] % 10000);
				}
			}
		}

		break;
	case SWITCH_BLUE_02:
		m_GimmickData[arrayy][arrayx] = (m_GimmickData[arrayy][arrayx] % 10000 + SWITCH_BLUE_01 * 10000);

		for (int i = 0; i < MAP_HEIGHT; i++)
		{
			for (int j = 0; j < MAP_WIDTH; j++)
			{
				if (m_GimmickData[i][j] / 10000 == LOSTGATE_01 && m_GimmickData[i][j] % 10000 == m_GimmickData[arrayy][arrayx] % 10000)
				{
					m_GimmickData[i][j] = (GATE_01 * 10000) + (m_GimmickData[i][j] % 10000);
				}
				else if (m_GimmickData[i][j] / 10000 == LOSTGATE_02 && m_GimmickData[i][j] % 10000 == m_GimmickData[arrayy][arrayx] % 10000)
				{
					m_GimmickData[i][j] = (GATE_02 * 10000) + (m_GimmickData[i][j] % 10000);
				}
				else if (m_GimmickData[i][j] / 10000 == LOSTGATE_03 && m_GimmickData[i][j] % 10000 == m_GimmickData[arrayy][arrayx] % 10000)
				{
					m_GimmickData[i][j] = (GATE_PORTRAIT_01 * 10000) + (m_GimmickData[i][j] % 10000);
				}
				else if (m_GimmickData[i][j] / 10000 == LOSTGATE_04 && m_GimmickData[i][j] % 10000 == m_GimmickData[arrayy][arrayx] % 10000)
				{
					m_GimmickData[i][j] = (GATE_PORTRAIT_02 * 10000) + (m_GimmickData[i][j] % 10000);
				}
			}
		}

		break;
	case SWITCH_YELLOW_02:
		m_GimmickData[arrayy][arrayx] = (m_GimmickData[arrayy][arrayx] % 10000 + SWITCH_YELLOW_01 * 10000);

		for (int i = 0; i < MAP_HEIGHT; i++)
		{
			for (int j = 0; j < MAP_WIDTH; j++)
			{
				if (m_GimmickData[i][j] / 10000 == LOSTGATE_01 && m_GimmickData[i][j] % 10000 == m_GimmickData[arrayy][arrayx] % 10000)
				{
					m_GimmickData[i][j] = (GATE_01 * 10000) + (m_GimmickData[i][j] % 10000);
				}
				else if (m_GimmickData[i][j] / 10000 == LOSTGATE_02 && m_GimmickData[i][j] % 10000 == m_GimmickData[arrayy][arrayx] % 10000)
				{
					m_GimmickData[i][j] = (GATE_02 * 10000) + (m_GimmickData[i][j] % 10000);
				}
				else if (m_GimmickData[i][j] / 10000 == LOSTGATE_03 && m_GimmickData[i][j] % 10000 == m_GimmickData[arrayy][arrayx] % 10000)
				{
					m_GimmickData[i][j] = (GATE_PORTRAIT_01 * 10000) + (m_GimmickData[i][j] % 10000);
				}
				else if (m_GimmickData[i][j] / 10000 == LOSTGATE_04 && m_GimmickData[i][j] % 10000 == m_GimmickData[arrayy][arrayx] % 10000)
				{
					m_GimmickData[i][j] = (GATE_PORTRAIT_02 * 10000) + (m_GimmickData[i][j] % 10000);
				}
			}
		}

		break;
	default:
		break;
	}
}



void ClientMapGimmick::MapTex_UV_Set(float Posx, float Posy)
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
			case SWITCH_BLUE_01:
				m_pLibrary->MakeVertex(SWITCH_BLUE_01, m_MapGimmick_Tex[i][j]);

				break;
			case SWITCH_BLUE_02:
				m_pLibrary->MakeVertex(SWITCH_BLUE_02, m_MapGimmick_Tex[i][j]);

				break;
			case SWITCH_YELLOW_01:
				m_pLibrary->MakeVertex(SWITCH_YELLOW_01, m_MapGimmick_Tex[i][j]);

				break;
			case SWITCH_YELLOW_02:
				m_pLibrary->MakeVertex(SWITCH_YELLOW_02, m_MapGimmick_Tex[i][j]);

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
			case GATEPOST_PORTRAIT_01:
				m_pLibrary->MakeVertex(GATEPOST_PORTRAIT_01, m_MapGimmick_Tex[i][j]);

				break;
			case GATEPOST_PORTRAIT_02:
				m_pLibrary->MakeVertex(GATEPOST_PORTRAIT_02, m_MapGimmick_Tex[i][j]);

				break;
			case GATE_PORTRAIT_01:
				m_pLibrary->MakeVertex(GATE_PORTRAIT_01, m_MapGimmick_Tex[i][j]);

				break;
			case GATE_PORTRAIT_02:
				m_pLibrary->MakeVertex(GATE_PORTRAIT_02, m_MapGimmick_Tex[i][j]);

				break;
			case HOLE_01:
				m_pLibrary->MakeVertex(HOLE_01, m_MapGimmick_Tex[i][j]);

				break;
			case HOLE_02:
				m_pLibrary->MakeVertex(HOLE_02, m_MapGimmick_Tex[i][j]);

				break;
			case GRASS_KNOT:
				m_pLibrary->MakeVertex(GRASS_KNOT, m_MapGimmick_Tex[i][j]);

				break;
			case GRASS_KNOT_PORTRAIT:
				m_pLibrary->MakeVertex(GRASS_KNOT_PORTRAIT, m_MapGimmick_Tex[i][j]);

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


void ClientMapGimmick::MapTex_XY_Set(float Posx, float Posy)
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



bool ClientMapGimmick::HoleCheck(float x, float y)
{
	int arrayx = 0, arrayy = 0;
	arrayx = int(x / 64);
	arrayy = int(y / 64);

	if (m_GimmickData[arrayy][arrayx] / 10000 == HOLE_01)
	{
		m_GimmickData[arrayy][arrayx] = HOLE_02 * 10000;
		return true;
	}

	return false;

}


bool ClientMapGimmick::WoodBoxHoleCheck(float x, float y)
{
	int arrayx = 0, arrayy = 0;
	arrayx = int(x / 64);
	arrayy = int(y / 64);

	if (m_GimmickData[arrayy][arrayx] / 10000 == HOLE_02)
	{
		m_GimmickData[arrayy][arrayx] = HOLE_01 * 10000;
		return true;

	}

	return false;

}



bool ClientMapGimmick::GrassCheck(float x, float y)
{
	int arrayx = 0, arrayy = 0;
	arrayx = int(x / 64);
	arrayy = int(y / 64);

	if (m_GimmickData[arrayy][arrayx] / 10000 == GRASS_KNOT)
	{
		return true;
	}

	return false;

}



bool ClientMapGimmick::GrassPortRaitCheck(float x, float y)
{
	int arrayx = 0, arrayy = 0;
	arrayx = int(x / 64);
	arrayy = int(y / 64);

	if (m_GimmickData[arrayy][arrayx] / 10000 == GRASS_KNOT_PORTRAIT)
	{
		return true;
	}

	return false;

}



