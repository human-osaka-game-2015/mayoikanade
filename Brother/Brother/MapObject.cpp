#include "MapObject.h"
#include "ServerGameScene.h"
#include "Library.h"


/**
 * MapObjectクラスのコンストラクタ
 * @param[in] pLibrary ライブラリクラスのポインタ
 */
MapObject::MapObject(Library* pLibrary) :
m_pLibrary(pLibrary)
{
	CsvRead("Stage1_Object.csv");
}

/**
 * MapObjectクラスのデストラクタ
 */
MapObject::~MapObject()
{

}

/**
 * CSVを読み込む関数
 * @param[in] filename 読み込むファイルの名前
 */
bool MapObject::CsvRead(const char* filename)
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
			fscanf_s(fp, "%d,", &m_ObjectData[i][j], _countof(m_ObjectData));
		}
	}
	fclose(fp);

	return true;
}

/**
 * オブジェクトのUVをセットする関数
 * @param[in] Posx	x描画位置
 * @param[in] Posy	y描画位置 
 */
void MapObject::MapTex_UV_Set(float Posx, float Posy)
{
	int count_x = static_cast<int>((Posx - MAPCHIP_SIZE) / MAPCHIP_SIZE);
	int count_y = static_cast<int>((Posy - MAPCHIP_SIZE) / MAPCHIP_SIZE);


	if (count_x < MAP_TOP)
	{
		count_x = MAP_TOP;
	}
	if (count_y < MAP_LEFT)
	{
		count_y = MAP_LEFT;
	}


	//描画領域を求めて代入 余分に一つ先も読んでるので64足している
	int ScreenRight  = static_cast<int>((Posx + SCREEN_SIZEX + MAPCHIP_SIZE) / MAPCHIP_SIZE);
	int ScreenBottom = static_cast<int>((Posy + SCREEN_SIZEY + MAPCHIP_SIZE) / MAPCHIP_SIZE);

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
			switch (m_ObjectData[i][j])
			{
			case WOOD_01:
				m_pLibrary->MakeVertex(WOOD_01, m_MapObject_Tex[i][j]);
				break;

			case WOOD_02:
				m_pLibrary->MakeVertex(WOOD_02, m_MapObject_Tex[i][j]);
				break;

			case WOOD_03:
				m_pLibrary->MakeVertex(WOOD_03, m_MapObject_Tex[i][j]);
				break;

			case WOOD_04:
				m_pLibrary->MakeVertex(WOOD_04, m_MapObject_Tex[i][j]);
				break;
			case WOODBOX:
				m_pLibrary->MakeVertex(WOODBOX, m_MapObject_Tex[i][j]);

				break;
			case WOOD_YELLOW_01:
				m_pLibrary->MakeVertex(WOOD_YELLOW_01, m_MapObject_Tex[i][j]);
				break;
			case WOOD_YELLOW_02:
				m_pLibrary->MakeVertex(WOOD_YELLOW_02, m_MapObject_Tex[i][j]);
				break;
			case WOOD_YELLOW_03:
				m_pLibrary->MakeVertex(WOOD_YELLOW_03, m_MapObject_Tex[i][j]);
				break;
			case WOOD_YELLOW_04:
				m_pLibrary->MakeVertex(WOOD_YELLOW_04, m_MapObject_Tex[i][j]);
				break;
			default :
				for (int x = FOR_DEFAULT_INIT; x < VERTEXNUM; x++)
				{
					m_MapObject_Tex[i][j][x].color = DEFAULT_COLOR;
					m_MapObject_Tex[i][j][x].rhw = DEFAULT_RHW;
					m_MapObject_Tex[i][j][x].z = DEFAULT_Z;
					m_MapObject_Tex[i][j][x].tu = DEFAULT_TU;
					m_MapObject_Tex[i][j][x].tv = DEFAULT_TV;
				}
				break;
			}
		}
	}
}




/**
 * オブジェクトのXYをセットする関数
 * @param[in] Posx	x描画位置
 * @param[in] Posy	y描画位置
 */
void MapObject::MapTex_XY_Set(float Posx, float Posy)
{
	int count_x = static_cast<int>((Posx - MAPCHIP_SIZE) / MAPCHIP_SIZE);
	int count_y = static_cast<int>((Posy - MAPCHIP_SIZE) / MAPCHIP_SIZE);


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
			//当たり判定用のXYを入れる
			m_MapObject_Pos[i - 1][j - 1].x = (float)(MAPCHIP_SIZE * j) - MAPCHIP_DEFAULT_POSX;
			m_MapObject_Pos[i - 1][j - 1].y = (float)(MAPCHIP_SIZE * i) - MAPCHIP_DEFAULT_POSY;
			m_MapObject_Pos[i - 1][j - 1].w = (float)MAPCHIP_SIZE;
			m_MapObject_Pos[i - 1][j - 1].h = (float)MAPCHIP_SIZE;
			m_MapObject_Pos[i - 1][j - 1].x -= Posx;
			m_MapObject_Pos[i - 1][j - 1].y -= Posy;

			m_pLibrary->xySet(m_MapObject_Pos[i - 1][j - 1], m_MapObject_Tex[i - 1][j - 1]);
		}
	}
}


/**
 * オブジェクトの描画関数
 * @param[in] DrawPosX x座標の描画位置
 * @param[in] DrawPosY y座標の描画位置
 */
void MapObject::Draw(float DrawPosX, float DrawPosY)
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
			m_pLibrary->DrawTexture(TEX_GAME, m_MapObject_Tex[i][j]);
		}
	}
}


/**
* オブジェクトをチェックする関数
* @param[in] x チェックするx座標
* @param[in] y チェックするy座標
* @return オブジェクトデータ
*/
int MapObject::ObjectCheck(float x, float y)
{
	int arrayx = ARRAY_DEFAULT_INIT, arrayy = ARRAY_DEFAULT_INIT;

	arrayx = static_cast<int>(x / MAPCHIP_SIZE);
	arrayy = static_cast<int>(y / MAPCHIP_SIZE);


	return m_ObjectData[arrayy][arrayx];
}


/**
 * 木箱があるかをチェックする関数
 * @param[in] x チェックするx座標
 * @param[in] y チェックするy座標
 * @return あったかどうか
 */
bool MapObject::WoodBoxCheck(float x, float y)
{
	int arrayx = ARRAY_DEFAULT_INIT, arrayy = ARRAY_DEFAULT_INIT;

	arrayx = static_cast<int>(x / MAPCHIP_SIZE);
	arrayy = static_cast<int>(y / MAPCHIP_SIZE);


	if (m_ObjectData[arrayy][arrayx] == WOODBOX)
	{
		m_ObjectData[arrayy][arrayx] = OBJECT_NONE;
		return true;
	}


	return false;
}


/**
 * 木箱をセットする関数
 * @param[in] x セットするx座標
 * @param[in] y セットするy座標
 * @return 成功したかどうか
 */
bool MapObject::WoodBoxSet(float x, float y)
{
	int arrayx = ARRAY_DEFAULT_INIT, arrayy = ARRAY_DEFAULT_INIT;

	arrayx = static_cast<int>(x / MAPCHIP_SIZE);
	arrayy = static_cast<int>(y / MAPCHIP_SIZE);


	if (m_ObjectData[arrayy][arrayx] == OBJECT_NONE)
	{
		m_ObjectData[arrayy][arrayx] = WOODBOX;
		return true;
	}

	return false;
}