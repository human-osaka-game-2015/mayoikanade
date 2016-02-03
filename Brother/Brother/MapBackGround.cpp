#include "MapBackGround.h"
#include "ServerGameScene.h"
#include "Library.h"


/**
 * MapBackGroundクラスのコンストラクタ
 * @param[in] pLibrary セットするライブラリクラスへのポインタ
 */
MapBackGround::MapBackGround(Library* pLibrary) :
m_pLibrary(pLibrary)
{
	//CsvRead("stage1/Stage1_Background.csv");
}

/**
 * MapBackGroundクラスのデストラクタ
 */
MapBackGround::~MapBackGround()
{

}

/**
 * CSVのマップ情報を読み込む関数
 * @param[in] filename 読み込むファイルの名前
 * @return 成功しかが返る
 */
bool MapBackGround::CsvRead(const char* filename)
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
			fscanf_s(fp, "%d,", &m_BackGroundData[i][j], _countof(m_BackGroundData));
		}
	}
	fclose(fp);

	return true;
}


/**
 * マップオブジェクトのUV値をセットする関数
 * @param[in] Posx 描画するX座標の中心位置
 * @param[in] Posy 描画するY座標の中心位置
 */
void MapBackGround::MapTex_UV_Set(float Posx, float Posy)
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
			switch (m_BackGroundData[i][j])
			{
			case GRASS_01:
				m_pLibrary->MakeVertex(GRASS_01, m_MapBackGround_Tex[i][j]);
				break;
			case GRASS_02:
				m_pLibrary->MakeVertex(GRASS_02, m_MapBackGround_Tex[i][j]);
				break;
			case GRASS_03:
				m_pLibrary->MakeVertex(GRASS_03, m_MapBackGround_Tex[i][j]);
				break;
			case GRASS_04:
				m_pLibrary->MakeVertex(GRASS_04, m_MapBackGround_Tex[i][j]);
				break;
			case GRASS_05:
				m_pLibrary->MakeVertex(GRASS_05, m_MapBackGround_Tex[i][j]);
				break;
			case GRASS_06:
				m_pLibrary->MakeVertex(GRASS_06, m_MapBackGround_Tex[i][j]);
				break;
			case GRASS_07:
				m_pLibrary->MakeVertex(GRASS_07, m_MapBackGround_Tex[i][j]);
				break;
			case GRASS_08:
				m_pLibrary->MakeVertex(GRASS_08, m_MapBackGround_Tex[i][j]);
				break;
			case GRASS_09:
				m_pLibrary->MakeVertex(GRASS_09, m_MapBackGround_Tex[i][j]);
				break;
			case GRASS_10:
				m_pLibrary->MakeVertex(GRASS_10, m_MapBackGround_Tex[i][j]);
				break;
			case GRASS_11:
				m_pLibrary->MakeVertex(GRASS_11, m_MapBackGround_Tex[i][j]);
				break;
			case GRASS_12:
				m_pLibrary->MakeVertex(GRASS_12, m_MapBackGround_Tex[i][j]);
				break;
			case GRASS_13:
				m_pLibrary->MakeVertex(GRASS_13, m_MapBackGround_Tex[i][j]);
				break;
			case GROUND_01:
				m_pLibrary->MakeVertex(GROUND_01, m_MapBackGround_Tex[i][j]);
				break;
			default:
				for (int z = FOR_DEFAULT_INIT; z < VERTEXNUM; z++)
				{
					m_MapBackGround_Tex[i][j][z].color = DEFAULT_COLOR;
					m_MapBackGround_Tex[i][j][z].rhw = DEFAULT_RHW;
					m_MapBackGround_Tex[i][j][z].z = DEFAULT_Z;
					m_MapBackGround_Tex[i][j][z].tu = DEFAULT_TU;
					m_MapBackGround_Tex[i][j][z].tv = DEFAULT_TV;
				}
				break;
			}
		}
	}
}


/**
 * マップオブジェクトのXY座標をセットする関数
 * @param[in] Posx 描画するX座標の中心位置
 * @param[in] Posy 描画するY座標の中心位置
 */
void MapBackGround::MapTex_XY_Set(float Posx, float Posy)
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
	int ScreenRight  = int((Posx + SCREEN_SIZEX + MAPCHIP_SIZE) / MAPCHIP_SIZE);
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
			//背景のXYを入れる
			m_MapBackGround_Pos[i - 1][j - 1].x = (float)(MAPCHIP_SIZE * j) - MAPCHIP_DEFAULT_POSX;
			m_MapBackGround_Pos[i - 1][j - 1].y = (float)(MAPCHIP_SIZE * i) - MAPCHIP_DEFAULT_POSY;
			m_MapBackGround_Pos[i - 1][j - 1].w = (float)MAPCHIP_SIZE;
			m_MapBackGround_Pos[i - 1][j - 1].h = (float)MAPCHIP_SIZE;
			m_MapBackGround_Pos[i - 1][j - 1].x -= Posx;
			m_MapBackGround_Pos[i - 1][j - 1].y -= Posy;

			m_pLibrary->xySet(m_MapBackGround_Pos[i - 1][j - 1], m_MapBackGround_Tex[i - 1][j - 1]);
		}
	}
}



/**
 * MapBackGroundの描画関数
 */
void MapBackGround::Draw(float DrawPosX, float DrawPosY)
{
	int count_x = int((DrawPosX - MAPCHIP_SIZE) / MAPCHIP_SIZE);
	int count_y = int((DrawPosY - MAPCHIP_SIZE) / MAPCHIP_SIZE);

	if (count_x < MAP_LEFT)
	{
		count_x = MAP_LEFT;
	}
	if (count_y < MAP_TOP)
	{
		count_y = MAP_TOP;
	}


	//描画領域を求めて代入 余分に一つ先も読んでるので64足している
	int ScreenRight = int((DrawPosX + SCREEN_SIZEX + MAPCHIP_SIZE) / MAPCHIP_SIZE);
	int ScreenBottom = int((DrawPosY + SCREEN_SIZEY + MAPCHIP_SIZE) / MAPCHIP_SIZE);

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
			m_pLibrary->DrawTexture(TEX_GAME, m_MapBackGround_Tex[i][j]);
		}
	}
}

int MapBackGround::BackGroundCheck(float x, float y)
{
	int arrayx = ARRAY_DEFAULT_INIT, arrayy = ARRAY_DEFAULT_INIT;
	arrayx = static_cast<int>(x / MAPCHIP_SIZE);
	arrayy = static_cast<int>(y / MAPCHIP_SIZE);

	return m_BackGroundData[arrayy][arrayx];
}
