#include "ServerGameScene.h"
#include "MapGimmick.h"
#include "Library.h"


/**
 * MapGimmickクラスのコンストラクタ
 * @param[in] pLibrary ライブラリクラスのポインタ
 */
MapGimmick::MapGimmick(Library* pLibrary) :
m_pLibrary(pLibrary)
{
	CsvRead("Stage1_Gimmick.csv");
}

/**
 * MapGimmickクラスのデストラクタ
 */
MapGimmick::~MapGimmick()
{

}

/**
 * CSVのマップ情報を読み込む関数
 * @param[in] filename 読み込むファイルの名前
 * @return 成功したかどうか
 */
bool MapGimmick::CsvRead(const char* filename)
{
	FILE*  fp = NULL;
	fopen_s(&fp, filename, "r");

	if (fp == NULL)
	{
		return false;
	}

	for (int i = FOR_DEFAULT_INIT; i < MAP_HEIGHT; i++)
	{
		for (int j = FOR_DEFAULT_INIT; j < MAP_WIDTH; j++)
		{
			fscanf_s(fp, "%d,", &m_GimmickData[i][j], _countof(m_GimmickData));
		}
	}
	fclose(fp);

	return true;
}


/**
 * MapGimmickの描画関数
 * @param[in] DrawPosX x座標の描画位置
 * @param[in] DrawPosY y座標の描画位置
 */
void MapGimmick::Draw(float DrawPosX, float DrawPosY)
{
	int count_x = static_cast<int>((DrawPosX - MAPCHIP_SIZE) / MAPCHIP_SIZE);
	int count_y = static_cast<int>((DrawPosY - MAPCHIP_SIZE) / MAPCHIP_SIZE);

	if (count_x < MAP_LEFT)
	{
		count_x = MAP_LEFT;
	}
	if (count_y < MAP_TOP)
	{
		count_y = MAP_TOP;
	}


	//描画領域を求めて代入 余分に一つ先も読んでるので64足している
	int ScreenRight  = static_cast<int>((DrawPosX + SCREEN_SIZEX + MAPCHIP_SIZE) / MAPCHIP_SIZE);
	int ScreenBottom = static_cast<int>((DrawPosY + SCREEN_SIZEY + MAPCHIP_SIZE) / MAPCHIP_SIZE);

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


/**
 * 指定した座標にあるギミックがなんであるかを返します
 * @param[in] x チェックするx座標
 * @param[in] y チェックするy座標
 * @return ギミックのenum
 */
int MapGimmick::GimmickCheck(float x, float y)
{
	int arrayx = ARRAY_DEFAULT_INIT, arrayy = ARRAY_DEFAULT_INIT;
	arrayx = int(x / MAPCHIP_SIZE);
	arrayy = int(y / MAPCHIP_SIZE);

	return m_GimmickData[arrayy][arrayx] / GIMMICK_DATA;
}


/**
 * スイッチを押す関数 指定した座標にあるスイッチを押す。 何もなければスルー
 * @param[in] x スイッチを押すx座標
 * @param[in] y スイッチを押すy座標
 */
void MapGimmick::SwitchOn(float x, float y)
{
	int arrayx = ARRAY_DEFAULT_INIT, arrayy = ARRAY_DEFAULT_INIT;
	int switchCount = SWITCH_COUNT_INIT;
	arrayx = static_cast<int>(x / MAPCHIP_SIZE);
	arrayy = static_cast<int>(y / MAPCHIP_SIZE);


	//スイッチが押された時の処理
	switch (m_GimmickData[arrayy][arrayx] / GIMMICK_DATA)
	{
	case SWITCH_RED_01:
		m_GimmickData[arrayy][arrayx] = (m_GimmickData[arrayy][arrayx] % GIMMICK_DATA + SWITCH_RED_02 * GIMMICK_DATA);
		switchCount = SWITCH_COUNT_INIT;

		for (int i = FOR_DEFAULT_INIT; i < MAP_HEIGHT; i++)
		{
			for (int j = FOR_DEFAULT_INIT; j < MAP_WIDTH; j++)
			{
				if (m_GimmickData[i][j] == m_GimmickData[arrayy][arrayx] % GIMMICK_DATA + SWITCH_RED_01 * GIMMICK_DATA)
				{
					switchCount++;
				}
			}
		}

		if (switchCount == SWITCH_COUNT_INIT)
		{

			for (int i = FOR_DEFAULT_INIT; i < MAP_HEIGHT; i++)
			{
				for (int j = FOR_DEFAULT_INIT; j < MAP_WIDTH; j++)
				{
					if (m_GimmickData[i][j] / GIMMICK_DATA == GATE_01 && m_GimmickData[i][j] % GIMMICK_DATA == m_GimmickData[arrayy][arrayx] % GIMMICK_DATA)
					{
						m_GimmickData[i][j] = (LOSTGATE_01 * GIMMICK_DATA) + (m_GimmickData[i][j] % GIMMICK_DATA);
					}
					else if (m_GimmickData[i][j] / GIMMICK_DATA == GATE_02 && m_GimmickData[i][j] % GIMMICK_DATA == m_GimmickData[arrayy][arrayx] % GIMMICK_DATA)
					{
						m_GimmickData[i][j] = (LOSTGATE_02 * GIMMICK_DATA) + (m_GimmickData[i][j] % GIMMICK_DATA);
					}
					else if (m_GimmickData[i][j] / GIMMICK_DATA == GATE_PORTRAIT_01 && m_GimmickData[i][j] % GIMMICK_DATA == m_GimmickData[arrayy][arrayx] % GIMMICK_DATA)
					{
						m_GimmickData[i][j] = (LOSTGATE_03 * GIMMICK_DATA) + (m_GimmickData[i][j] % GIMMICK_DATA);
					}
					else if (m_GimmickData[i][j] / GIMMICK_DATA == GATE_PORTRAIT_02 && m_GimmickData[i][j] % GIMMICK_DATA == m_GimmickData[arrayy][arrayx] % GIMMICK_DATA)
					{
						m_GimmickData[i][j] = (LOSTGATE_04 * GIMMICK_DATA) + (m_GimmickData[i][j] % GIMMICK_DATA);
					}
				}
			}
		}

		break;
	case SWITCH_BLUE_01:
		m_GimmickData[arrayy][arrayx] = (m_GimmickData[arrayy][arrayx] % GIMMICK_DATA + SWITCH_BLUE_02 * GIMMICK_DATA);
		switchCount = SWITCH_COUNT_INIT;

		for (int i = FOR_DEFAULT_INIT; i < MAP_HEIGHT; i++)
		{
			for (int j = FOR_DEFAULT_INIT; j < MAP_WIDTH; j++)
			{
				if (m_GimmickData[i][j] == m_GimmickData[arrayy][arrayx] % GIMMICK_DATA + SWITCH_BLUE_01 * GIMMICK_DATA)
				{
					switchCount++;
				}
			}
		}

		if (switchCount == SWITCH_COUNT_INIT)
		{
			for (int i = FOR_DEFAULT_INIT; i < MAP_HEIGHT; i++)
			{
				for (int j = FOR_DEFAULT_INIT; j < MAP_WIDTH; j++)
				{
					if (m_GimmickData[i][j] / GIMMICK_DATA == GATE_01 && m_GimmickData[i][j] % GIMMICK_DATA == m_GimmickData[arrayy][arrayx] % GIMMICK_DATA)
					{
						m_GimmickData[i][j] = (LOSTGATE_01 * GIMMICK_DATA) + (m_GimmickData[i][j] % GIMMICK_DATA);
					}
					else if (m_GimmickData[i][j] / GIMMICK_DATA == GATE_02 && m_GimmickData[i][j] % GIMMICK_DATA == m_GimmickData[arrayy][arrayx] % GIMMICK_DATA)
					{
						m_GimmickData[i][j] = (LOSTGATE_02 * GIMMICK_DATA) + (m_GimmickData[i][j] % GIMMICK_DATA);
					}
					else if (m_GimmickData[i][j] / GIMMICK_DATA == GATE_PORTRAIT_01 && m_GimmickData[i][j] % GIMMICK_DATA == m_GimmickData[arrayy][arrayx] % GIMMICK_DATA)
					{
						m_GimmickData[i][j] = (LOSTGATE_03 * GIMMICK_DATA) + (m_GimmickData[i][j] % GIMMICK_DATA);
					}
					else if (m_GimmickData[i][j] / GIMMICK_DATA == GATE_PORTRAIT_02 && m_GimmickData[i][j] % GIMMICK_DATA == m_GimmickData[arrayy][arrayx] % GIMMICK_DATA)
					{
						m_GimmickData[i][j] = (LOSTGATE_04 * GIMMICK_DATA) + (m_GimmickData[i][j] % GIMMICK_DATA);
					}
				}
			}
		}

		break;
	case SWITCH_YELLOW_01:
		m_GimmickData[arrayy][arrayx] = (m_GimmickData[arrayy][arrayx] % GIMMICK_DATA + SWITCH_YELLOW_02 * GIMMICK_DATA);
		switchCount = SWITCH_COUNT_INIT;

		for (int i = FOR_DEFAULT_INIT; i < MAP_HEIGHT; i++)
		{
			for (int j = FOR_DEFAULT_INIT; j < MAP_WIDTH; j++)
			{
				if (m_GimmickData[i][j] == m_GimmickData[arrayy][arrayx] % GIMMICK_DATA + SWITCH_YELLOW_01 * GIMMICK_DATA)
				{
					switchCount++;
				}
			}
		}

		if (switchCount == SWITCH_COUNT_INIT)
		{

			for (int i = FOR_DEFAULT_INIT; i < MAP_HEIGHT; i++)
			{
				for (int j = FOR_DEFAULT_INIT; j < MAP_WIDTH; j++)
				{
					if (m_GimmickData[i][j] / GIMMICK_DATA == GATE_01 && m_GimmickData[i][j] % GIMMICK_DATA == m_GimmickData[arrayy][arrayx] % GIMMICK_DATA)
					{
						m_GimmickData[i][j] = (LOSTGATE_01 * GIMMICK_DATA) + (m_GimmickData[i][j] % GIMMICK_DATA);
					}
					else if (m_GimmickData[i][j] / GIMMICK_DATA == GATE_02 && m_GimmickData[i][j] % GIMMICK_DATA == m_GimmickData[arrayy][arrayx] % GIMMICK_DATA)
					{
						m_GimmickData[i][j] = (LOSTGATE_02 * GIMMICK_DATA) + (m_GimmickData[i][j] % GIMMICK_DATA);
					}
					else if (m_GimmickData[i][j] / GIMMICK_DATA == GATE_PORTRAIT_01 && m_GimmickData[i][j] % GIMMICK_DATA == m_GimmickData[arrayy][arrayx] % GIMMICK_DATA)
					{
						m_GimmickData[i][j] = (LOSTGATE_03 * GIMMICK_DATA) + (m_GimmickData[i][j] % GIMMICK_DATA);
					}
					else if (m_GimmickData[i][j] / GIMMICK_DATA == GATE_PORTRAIT_02 && m_GimmickData[i][j] % GIMMICK_DATA == m_GimmickData[arrayy][arrayx] % GIMMICK_DATA)
					{
						m_GimmickData[i][j] = (LOSTGATE_04 * GIMMICK_DATA) + (m_GimmickData[i][j] % GIMMICK_DATA);
					}
				}
			}
		}

		break;
	default:
		break;
	}

}


/**
 * スイッチを押す関数(弟用) 指定した座標にあるスイッチを押す。 何もなければスルー
 * @param[in] x スイッチを押すx座標
 * @param[in] y スイッチを押すy座標
 */
void MapGimmick::SwitchOnYoung(float x, float y)
{
	int arrayx = ARRAY_DEFAULT_INIT, arrayy = ARRAY_DEFAULT_INIT;
	int switchCount = SWITCH_COUNT_INIT;
	arrayx = static_cast<int>(x / MAPCHIP_SIZE);
	arrayy = static_cast<int>(y / MAPCHIP_SIZE);


	//スイッチが押された時の処理
	switch (m_GimmickData[arrayy][arrayx] / GIMMICK_DATA)
	{
	case SWITCH_RED_01:
		break;
	case SWITCH_BLUE_01:
		m_GimmickData[arrayy][arrayx] = (m_GimmickData[arrayy][arrayx] % GIMMICK_DATA + SWITCH_BLUE_02 * GIMMICK_DATA);
		switchCount = SWITCH_COUNT_INIT;

		for (int i = FOR_DEFAULT_INIT; i < MAP_HEIGHT; i++)
		{
			for (int j = FOR_DEFAULT_INIT; j < MAP_WIDTH; j++)
			{
				if (m_GimmickData[i][j] == m_GimmickData[arrayy][arrayx] % GIMMICK_DATA + SWITCH_BLUE_01 * GIMMICK_DATA)
				{
					switchCount++;
				}
			}
		}

		if (switchCount == SWITCH_COUNT_INIT)
		{
			for (int i = FOR_DEFAULT_INIT; i < MAP_HEIGHT; i++)
			{
				for (int j = FOR_DEFAULT_INIT; j < MAP_WIDTH; j++)
				{
					if (m_GimmickData[i][j] / GIMMICK_DATA == GATE_01 && m_GimmickData[i][j] % GIMMICK_DATA == m_GimmickData[arrayy][arrayx] % GIMMICK_DATA)
					{
						m_GimmickData[i][j] = (LOSTGATE_01 * GIMMICK_DATA) + (m_GimmickData[i][j] % GIMMICK_DATA);
					}
					else if (m_GimmickData[i][j] / GIMMICK_DATA == GATE_02 && m_GimmickData[i][j] % GIMMICK_DATA == m_GimmickData[arrayy][arrayx] % GIMMICK_DATA)
					{
						m_GimmickData[i][j] = (LOSTGATE_02 * GIMMICK_DATA) + (m_GimmickData[i][j] % GIMMICK_DATA);
					}
					else if (m_GimmickData[i][j] / GIMMICK_DATA == GATE_PORTRAIT_01 && m_GimmickData[i][j] % GIMMICK_DATA == m_GimmickData[arrayy][arrayx] % GIMMICK_DATA)
					{
						m_GimmickData[i][j] = (LOSTGATE_03 * GIMMICK_DATA) + (m_GimmickData[i][j] % GIMMICK_DATA);
					}
					else if (m_GimmickData[i][j] / GIMMICK_DATA == GATE_PORTRAIT_02 && m_GimmickData[i][j] % GIMMICK_DATA == m_GimmickData[arrayy][arrayx] % GIMMICK_DATA)
					{
						m_GimmickData[i][j] = (LOSTGATE_04 * GIMMICK_DATA) + (m_GimmickData[i][j] % GIMMICK_DATA);
					}
				}
			}
		}

		break;
	case SWITCH_YELLOW_01:
		m_GimmickData[arrayy][arrayx] = (m_GimmickData[arrayy][arrayx] % GIMMICK_DATA + SWITCH_YELLOW_02 * GIMMICK_DATA);
		switchCount = SWITCH_COUNT_INIT;

		for (int i = FOR_DEFAULT_INIT; i < MAP_HEIGHT; i++)
		{
			for (int j = FOR_DEFAULT_INIT; j < MAP_WIDTH; j++)
			{
				if (m_GimmickData[i][j] == m_GimmickData[arrayy][arrayx] % GIMMICK_DATA + SWITCH_YELLOW_01 * GIMMICK_DATA)
				{
					switchCount++;
				}
			}
		}

		if (switchCount == SWITCH_COUNT_INIT)
		{

			for (int i = FOR_DEFAULT_INIT; i < MAP_HEIGHT; i++)
			{
				for (int j = FOR_DEFAULT_INIT; j < MAP_WIDTH; j++)
				{
					if (m_GimmickData[i][j] / GIMMICK_DATA == GATE_01 && m_GimmickData[i][j] % GIMMICK_DATA == m_GimmickData[arrayy][arrayx] % GIMMICK_DATA)
					{
						m_GimmickData[i][j] = (LOSTGATE_01 * GIMMICK_DATA) + (m_GimmickData[i][j] % GIMMICK_DATA);
					}
					else if (m_GimmickData[i][j] / GIMMICK_DATA == GATE_02 && m_GimmickData[i][j] % GIMMICK_DATA == m_GimmickData[arrayy][arrayx] % GIMMICK_DATA)
					{
						m_GimmickData[i][j] = (LOSTGATE_02 * GIMMICK_DATA) + (m_GimmickData[i][j] % GIMMICK_DATA);
					}
					else if (m_GimmickData[i][j] / GIMMICK_DATA == GATE_PORTRAIT_01 && m_GimmickData[i][j] % GIMMICK_DATA == m_GimmickData[arrayy][arrayx] % GIMMICK_DATA)
					{
						m_GimmickData[i][j] = (LOSTGATE_03 * GIMMICK_DATA) + (m_GimmickData[i][j] % GIMMICK_DATA);
					}
					else if (m_GimmickData[i][j] / GIMMICK_DATA == GATE_PORTRAIT_02 && m_GimmickData[i][j] % GIMMICK_DATA == m_GimmickData[arrayy][arrayx] % GIMMICK_DATA)
					{
						m_GimmickData[i][j] = (LOSTGATE_04 * GIMMICK_DATA) + (m_GimmickData[i][j] % GIMMICK_DATA);
					}
				}
			}
		}

		break;
	default:
		break;
	}
}


/**
 * スイッチをオフにする関数
 * @param[in] オフにするスイッチのx座標
 * @param[in] オフにするスイッチのy座標
 */
void MapGimmick::SwitchOff(float x, float y)
{
	int arrayx = ARRAY_DEFAULT_INIT, arrayy = ARRAY_DEFAULT_INIT;
	arrayx = static_cast<int>(x / MAPCHIP_SIZE);
	arrayy = static_cast<int>(y / MAPCHIP_SIZE);


	//スイッチが押された時の処理
	switch (m_GimmickData[arrayy][arrayx] / GIMMICK_DATA)
	{
	case SWITCH_RED_02:
		m_GimmickData[arrayy][arrayx] = (m_GimmickData[arrayy][arrayx] % GIMMICK_DATA + SWITCH_RED_01 * GIMMICK_DATA);

		for (int i = FOR_DEFAULT_INIT; i < MAP_HEIGHT; i++)
		{
			for (int j = FOR_DEFAULT_INIT; j < MAP_WIDTH; j++)
			{
				if (m_GimmickData[i][j] / GIMMICK_DATA == LOSTGATE_01 && m_GimmickData[i][j] % GIMMICK_DATA == m_GimmickData[arrayy][arrayx] % GIMMICK_DATA)
				{
					m_GimmickData[i][j] = (GATE_01 * GIMMICK_DATA) + (m_GimmickData[i][j] % GIMMICK_DATA);
				}
				else if (m_GimmickData[i][j] / GIMMICK_DATA == LOSTGATE_02 && m_GimmickData[i][j] % GIMMICK_DATA == m_GimmickData[arrayy][arrayx] % GIMMICK_DATA)
				{
					m_GimmickData[i][j] = (GATE_02 * GIMMICK_DATA) + (m_GimmickData[i][j] % GIMMICK_DATA);
				}
				else if (m_GimmickData[i][j] / GIMMICK_DATA == LOSTGATE_03 && m_GimmickData[i][j] % GIMMICK_DATA == m_GimmickData[arrayy][arrayx] % GIMMICK_DATA)
				{
					m_GimmickData[i][j] = (GATE_PORTRAIT_01 * GIMMICK_DATA) + (m_GimmickData[i][j] % GIMMICK_DATA);
				}
				else if (m_GimmickData[i][j] / GIMMICK_DATA == LOSTGATE_04 && m_GimmickData[i][j] % GIMMICK_DATA == m_GimmickData[arrayy][arrayx] % GIMMICK_DATA)
				{
					m_GimmickData[i][j] = (GATE_PORTRAIT_02 * GIMMICK_DATA) + (m_GimmickData[i][j] % GIMMICK_DATA);
				}
			}
		}

		break;
	case SWITCH_BLUE_02:
		m_GimmickData[arrayy][arrayx] = (m_GimmickData[arrayy][arrayx] % GIMMICK_DATA + SWITCH_BLUE_01 * GIMMICK_DATA);

		for (int i = FOR_DEFAULT_INIT; i < MAP_HEIGHT; i++)
		{
			for (int j = FOR_DEFAULT_INIT; j < MAP_WIDTH; j++)
			{
				if (m_GimmickData[i][j] / GIMMICK_DATA == LOSTGATE_01 && m_GimmickData[i][j] % GIMMICK_DATA == m_GimmickData[arrayy][arrayx] % GIMMICK_DATA)
				{
					m_GimmickData[i][j] = (GATE_01 * GIMMICK_DATA) + (m_GimmickData[i][j] % GIMMICK_DATA);
				}
				else if (m_GimmickData[i][j] / GIMMICK_DATA == LOSTGATE_02 && m_GimmickData[i][j] % GIMMICK_DATA == m_GimmickData[arrayy][arrayx] % GIMMICK_DATA)
				{
					m_GimmickData[i][j] = (GATE_02 * GIMMICK_DATA) + (m_GimmickData[i][j] % GIMMICK_DATA);
				}
				else if (m_GimmickData[i][j] / GIMMICK_DATA == LOSTGATE_03 && m_GimmickData[i][j] % GIMMICK_DATA == m_GimmickData[arrayy][arrayx] % GIMMICK_DATA)
				{
					m_GimmickData[i][j] = (GATE_PORTRAIT_01 * GIMMICK_DATA) + (m_GimmickData[i][j] % GIMMICK_DATA);
				}
				else if (m_GimmickData[i][j] / GIMMICK_DATA == LOSTGATE_04 && m_GimmickData[i][j] % GIMMICK_DATA == m_GimmickData[arrayy][arrayx] % GIMMICK_DATA)
				{
					m_GimmickData[i][j] = (GATE_PORTRAIT_02 * GIMMICK_DATA) + (m_GimmickData[i][j] % GIMMICK_DATA);
				}
			}
		}

		break;
	case SWITCH_YELLOW_02:
		m_GimmickData[arrayy][arrayx] = (m_GimmickData[arrayy][arrayx] % GIMMICK_DATA + SWITCH_YELLOW_01 * GIMMICK_DATA);

		for (int i = FOR_DEFAULT_INIT; i < MAP_HEIGHT; i++)
		{
			for (int j = FOR_DEFAULT_INIT; j < MAP_WIDTH; j++)
			{
				if (m_GimmickData[i][j] / GIMMICK_DATA == LOSTGATE_01 && m_GimmickData[i][j] % GIMMICK_DATA == m_GimmickData[arrayy][arrayx] % GIMMICK_DATA)
				{
					m_GimmickData[i][j] = (GATE_01 * GIMMICK_DATA) + (m_GimmickData[i][j] % GIMMICK_DATA);
				}
				else if (m_GimmickData[i][j] / GIMMICK_DATA == LOSTGATE_02 && m_GimmickData[i][j] % GIMMICK_DATA == m_GimmickData[arrayy][arrayx] % GIMMICK_DATA)
				{
					m_GimmickData[i][j] = (GATE_02 * GIMMICK_DATA) + (m_GimmickData[i][j] % GIMMICK_DATA);
				}
				else if (m_GimmickData[i][j] / GIMMICK_DATA == LOSTGATE_03 && m_GimmickData[i][j] % GIMMICK_DATA == m_GimmickData[arrayy][arrayx] % GIMMICK_DATA)
				{
					m_GimmickData[i][j] = (GATE_PORTRAIT_01 * GIMMICK_DATA) + (m_GimmickData[i][j] % GIMMICK_DATA);
				}
				else if (m_GimmickData[i][j] / GIMMICK_DATA == LOSTGATE_04 && m_GimmickData[i][j] % GIMMICK_DATA == m_GimmickData[arrayy][arrayx] % GIMMICK_DATA)
				{
					m_GimmickData[i][j] = (GATE_PORTRAIT_02 * GIMMICK_DATA) + (m_GimmickData[i][j] % GIMMICK_DATA);
				}
			}
		}

		break;
	default:
		break;
	}
}



/**
 * ギミックのUVをセットする関数
 * @param[in] Posx x座標の描画位置
 * @param[in] Posy y座標の描画位置
 */
void MapGimmick::MapTex_UV_Set(float Posx, float Posy)
{
	int count_x = int((Posx - MAPCHIP_SIZE) / MAPCHIP_SIZE);
	int count_y = int((Posy - MAPCHIP_SIZE) / MAPCHIP_SIZE);


	if (count_x < MAP_LEFT)
	{
		count_x = MAP_LEFT;
	}
	if (count_y < MAP_TOP)
	{
		count_y = MAP_TOP;
	}


	//描画領域を求めて代入 余分に一つ先も読んでるので64足している
	int ScreenRight = int((Posx + SCREEN_SIZEX + MAPCHIP_SIZE) / MAPCHIP_SIZE);
	int ScreenBottom = int((Posy + SCREEN_SIZEY + MAPCHIP_SIZE) / MAPCHIP_SIZE);

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
			switch (m_GimmickData[i][j] / GIMMICK_DATA)
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
			case APPLE:
				m_pLibrary->MakeVertex(APPLE, m_MapGimmick_Tex[i][j]);
				break;
			default:
				for (int x = 0; x < VERTEXNUM; x++)
				{
					m_MapGimmick_Tex[i][j][x].color = DEFAULT_COLOR;
					m_MapGimmick_Tex[i][j][x].rhw = DEFAULT_RHW;
					m_MapGimmick_Tex[i][j][x].z = DEFAULT_Z;
					m_MapGimmick_Tex[i][j][x].tu = DEFAULT_TU;
					m_MapGimmick_Tex[i][j][x].tv = DEFAULT_TV;
				}
				break;
			}
		}
	}
}


/**
 * ギミックのXYをセットする関数
 * @param[in] Posx x座標の描画位置
 * @param[in] Posy y座標の描画位置
 */
void MapGimmick::MapTex_XY_Set(float Posx, float Posy)
{
	int count_x = int((Posx - MAPCHIP_SIZE) / MAPCHIP_SIZE);
	int count_y = int((Posy - MAPCHIP_SIZE) / MAPCHIP_SIZE);


	if (count_x < 1)
	{
		count_x = 1;
	}
	if (count_y < 1)
	{
		count_y = 1;
	}


	//描画領域を求めて代入 余分に一つ先も読んでるので64足している
	int ScreenRight = int((Posx + SCREEN_SIZEX + MAPCHIP_SIZE) / MAPCHIP_SIZE);
	int ScreenBottom = int((Posy + SCREEN_SIZEY + MAPCHIP_SIZE) / MAPCHIP_SIZE);

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
				m_MapGimmick_Pos[i - 1][j - 1].x = (float)(MAPCHIP_SIZE * j) - MAPCHIP_DEFAULT_POSX;
				m_MapGimmick_Pos[i - 1][j - 1].y = (float)(MAPCHIP_SIZE * i) - MAPCHIP_DEFAULT_POSY;
				m_MapGimmick_Pos[i - 1][j - 1].w = (float)MAPCHIP_SIZE;
				m_MapGimmick_Pos[i - 1][j - 1].h = (float)MAPCHIP_SIZE;
				m_MapGimmick_Pos[i - 1][j - 1].x -= Posx;
				m_MapGimmick_Pos[i - 1][j - 1].y -= Posy;

				m_pLibrary->xySet(m_MapGimmick_Pos[i - 1][j - 1], m_MapGimmick_Tex[i - 1][j - 1]);
			}
		}
	}
}


/**
 * 穴があるかをチェックする関数
 * @param[in] x チェックするx座標
 * @param[in] y チェックするy座標
 * @return 穴があったかどうか
 */
bool MapGimmick::HoleCheck(float x, float y)
{
	int arrayx = ARRAY_DEFAULT_INIT, arrayy = ARRAY_DEFAULT_INIT;
	arrayx = static_cast<int>(x / MAPCHIP_SIZE);
	arrayy = static_cast<int>(y / MAPCHIP_SIZE);

	if (m_GimmickData[arrayy][arrayx] / GIMMICK_DATA == HOLE_01)
	{
		m_GimmickData[arrayy][arrayx] = HOLE_02 * GIMMICK_DATA;
		return true;
	}

	return false;

}


/**
 * 木箱が入った穴があるかをチェックする関数
 * @param[in] x チェックするx座標
 * @param[in] y チェックするy座標
 * @return 木箱が入った穴があったかどうか
 */
bool MapGimmick::WoodBoxHoleCheck(float x, float y)
{
	int arrayx = ARRAY_DEFAULT_INIT, arrayy = ARRAY_DEFAULT_INIT;
	arrayx = static_cast<int>(x / MAPCHIP_SIZE);
	arrayy = static_cast<int>(y / MAPCHIP_SIZE);

	if (m_GimmickData[arrayy][arrayx] / GIMMICK_DATA == HOLE_02)
	{
		m_GimmickData[arrayy][arrayx] = HOLE_01 * GIMMICK_DATA;
		return true;

	}

	return false;

}


/**
 * 草結び(縦向き)があるかをチェックする関数
 * @param[in] x チェックするx座標
 * @param[in] y チェックするy座標
 * @return あったかどうか
 */
bool MapGimmick::GrassPortRaitCheck(float x, float y)
{
	int arrayx = ARRAY_DEFAULT_INIT, arrayy = ARRAY_DEFAULT_INIT;
	arrayx = static_cast<int>(x / MAPCHIP_SIZE);
	arrayy = static_cast<int>(y / MAPCHIP_SIZE);

	if (m_GimmickData[arrayy][arrayx] / GIMMICK_DATA == GRASS_KNOT_PORTRAIT)
	{
		return true;
	}

	return false;

}


/**
 * 草結び(横向き)があるかをチェックする関数
 * @param[in] x チェックするx座標
 * @param[in] y チェックするy座標
 * @return あったかどうか
 */
bool MapGimmick::GrassCheck(float x, float y)
{
	int arrayx = ARRAY_DEFAULT_INIT, arrayy = ARRAY_DEFAULT_INIT;
	arrayx = static_cast<int>(x / MAPCHIP_SIZE);
	arrayy = static_cast<int>(y / MAPCHIP_SIZE);

	if (m_GimmickData[arrayy][arrayx] / GIMMICK_DATA == GRASS_KNOT)
	{
		return true;
	}

	return false;

}

/**
 * リンゴがあるかをチェックする関数
 * @param[in] x チェックするx座標
 * @param[in] y チェックするy座標
 * @return あったかどうか
 */
bool MapGimmick::AppleCheck(float x, float y)
{
	int arrayx = ARRAY_DEFAULT_INIT, arrayy = ARRAY_DEFAULT_INIT;
	arrayx = static_cast<int>(x / MAPCHIP_SIZE);
	arrayy = static_cast<int>(y / MAPCHIP_SIZE);

	if (m_GimmickData[arrayy][arrayx] / GIMMICK_DATA == APPLE)
	{
		m_GimmickData[arrayy][arrayx] = MAP_GIMMICK_NONE;
		return true;
	}

	return false;

}

/**
 * クリア場所があるかをチェックする関数
 * @param[in] x チェックするx座標
 * @param[in] y チェックするy座標
 * @return あったかどうか
 */
bool MapGimmick::ClearCheck(float x, float y)
{
	int arrayx = ARRAY_DEFAULT_INIT, arrayy = ARRAY_DEFAULT_INIT;
	arrayx = static_cast<int>(x / MAPCHIP_SIZE);
	arrayy = static_cast<int>(y / MAPCHIP_SIZE);

	if (m_GimmickData[arrayy][arrayx] / 10000 == GOALZONE)
	{
		return true;
	}
	return false;
}

void MapGimmick::MapStartPos(float* posx, float* posy)
{
	for (int y = 0; y < MAP_HEIGHT; y++)
	{
		for (int x = 0; x < MAP_WIDTH; x++)
		{
			if (m_GimmickData[y][x] / 10000 == STARTZONE)
			{
				*posx = m_MapGimmick_Pos[y][x].x;
				*posy = m_MapGimmick_Pos[y][x].y;
				return;
			}
		}
	}
}