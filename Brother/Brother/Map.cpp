#include "Map.h"
#include "Library.h"
#include "ServerGameScene.h"
#include "MapGimmick.h"
#include "MapBackGround.h"
#include "MapObject.h"
#include <stdio.h>


/**
 * Mapクラスのコンストラクタ
 * @param[in] pLibrary ライブラリクラスのポインタ
 */
Map::Map(Library* pLibrary) : 
m_pLibrary(pLibrary)
{
	//オブジェクトの生成
	m_pMapObject = new MapObject(m_pLibrary);
	m_pMapGimmick = new MapGimmick(m_pLibrary);
	m_pMapBackGround = new MapBackGround(m_pLibrary);
}

/**
 * MApクラスのデストラクタ
 */
Map::~Map()
{
	//オブジェクトの破棄
	delete m_pMapObject;
	delete m_pMapGimmick;
	delete m_pMapBackGround;
}


/**
 * Mapのコントロール関数
 */
void Map::Control()
{
	for (int i = FOR_DEFAULT_INIT; i < MAP_HEIGHT; i++)
	{
		for (int j = FOR_DEFAULT_INIT; j < MAP_WIDTH; j++)
		{
			if ((m_pMapGimmick->m_GimmickData[i][j]/GIMMICK_DATA) == SWITCH_BLUE_02)
			{
				if (m_pMapObject->m_ObjectData[i][j] == WOODBOX)
				{
					SwitchOn(j * static_cast<float>(MAPCHIP_SIZE), i * static_cast<float>(MAPCHIP_SIZE));
				}
				else
				{
					SwitchOff(j * static_cast<float>(MAPCHIP_SIZE), i * static_cast<float>(MAPCHIP_SIZE));
				}
			}
		}
	}
}

/**
 * Mapの描画関数
 */
void Map::Draw()
{
	//UVのセット
	m_pMapBackGround->MapTex_UV_Set(m_DrawPositionX, m_DrawPositionY);
	m_pMapGimmick->MapTex_UV_Set(m_DrawPositionX, m_DrawPositionY);
	m_pMapObject->MapTex_UV_Set(m_DrawPositionX, m_DrawPositionY);

	//XYのセット
	m_pMapBackGround->MapTex_XY_Set(m_DrawPositionX, m_DrawPositionY);
	m_pMapGimmick->MapTex_XY_Set(m_DrawPositionX, m_DrawPositionY);
	m_pMapObject->MapTex_XY_Set(m_DrawPositionX, m_DrawPositionY);

	//描画
	m_pMapBackGround->Draw(m_DrawPositionX, m_DrawPositionY);
	m_pMapGimmick->Draw(m_DrawPositionX, m_DrawPositionY);
	m_pMapObject->Draw(m_DrawPositionX, m_DrawPositionY);
}


/**
 * ギミックのチェック関数
 * @param x チェックするx座標
 * @param y チェックするy座標
 * @return チェックした座標のギミックデータ
 */
int Map::GimmickCheck(float x, float y)
{
	return m_pMapGimmick->GimmickCheck(x, y);
}

/**
 * スイッチを押す関数
 * @param x スイッチを押すx座標
 * @param y スイッチを押すy座標
 */
void Map::SwitchOn(float x, float y)
{
	return m_pMapGimmick->SwitchOn(x, y);
}

/**
 * スイッチを押す関数(弟用)
 * @param x スイッチを押すx座標
 * @param y スイッチを押すy座標
 */
void Map::SwitchOnYoung(float x, float y)
{
	return m_pMapGimmick->SwitchOnYoung(x, y);
}

/**
 * スイッチをオフにする関数(弟用)
 * @param x スイッチをオフにするx座標
 * @param y スイッチをオフにするy座標
 */
void Map::SwitchOff(float x, float y)
{
	return m_pMapGimmick->SwitchOff(x, y);
}



/**
 * オブジェクトのチェック関数
 * @param[in] x チェックするx座標 
 * @param[in] y チェックするy座標
 * @return チェックした座標のオブジェクト情報
 */
int Map::ObjectCheck(float x, float y)
{
	return m_pMapObject->ObjectCheck(x, y);
}

/**
 * 木箱のチェック関数
 * @param[in] x チェックするx座標
 * @param[in] y チェックするy座標
 * @return 木箱があったかどうか
 */
bool Map::WoodBoxCheck(float x, float y)
{
	if (m_pMapObject->WoodBoxCheck(x, y) == true)
	{
		return true;
	}
	else if (m_pMapGimmick->WoodBoxHoleCheck(x, y) == true)
	{
		return true;
	}

	return false;
}

/**
 * 木箱のセットする関数
 * @param[in] x セットするx座標
 * @param[in] y セットするy座標
 * @return 木箱をセットできたか
 */
bool Map::WoodBoxSet(float x, float y)
{
	switch (m_pMapGimmick->GimmickCheck(x, y))
	{
	case GATEPOST_01:
		return false;
		break;
	case GATEPOST_02:
		return false;
		break;
	case GATE_01:
		return false;
		break;
	case GATE_02:
		return false;
		break;
	case GATEPOST_PORTRAIT_01:
		return false;
		break;
	case GATEPOST_PORTRAIT_02:
		return false;
		break;
	case GATE_PORTRAIT_01:
		return false;
		break;
	case GATE_PORTRAIT_02:
		return false;
		break;
	
	}

	bool isBoxSet;

	if (m_pMapObject->WoodBoxSet(x, y))
	{
		isBoxSet = true;
	}
	if (m_pMapGimmick->HoleCheck(x, y))
	{
		m_pMapObject->WoodBoxCheck(x,y);
		isBoxSet = true;
	}

	if (isBoxSet)
	{
		m_pMapGimmick->SwitchOn(x, y);
	}

	return isBoxSet;
}


/**
 * バックグラウンドをチェックする関数
 * @param[in] x チェックするx座標
 * @param[in] y チェックするy座標
 * @return バックグラウンドの情報 
 */
int Map::BackGroundCheck(float x, float y)
{
	return m_pMapBackGround->BackGroundCheck(x, y);
}


/**
 * 草結び(縦向き)をチェックする関数
 * @param[in] x チェックするx座標
 * @param[in] y チェックするy座標
 * @return 草結び(縦向き)があったかどうか
 */
bool Map::GrassPortRaitCheck(float x, float y)
{
	return m_pMapGimmick->GrassPortRaitCheck(x, y);
}

/**
 * 草結びをチェックする関数
 * @param[in] x チェックするx座標
 * @param[in] y チェックするy座標
 * @return 草結びがあったかどうか
 */
bool Map::GrassCheck(float x, float y)
{
	return m_pMapGimmick->GrassCheck(x, y);
}


/**
 * リンゴをチェックする関数
 * @param[in] x チェックするx座標
 * @param[in] y チェックするy座標
 * @return リンゴがあったかどうか
 */
bool Map::AppleCheck(float x, float y)
{
	return m_pMapGimmick->AppleCheck(x, y);
}

/**
 * ステージを切り替える関数
 */
void Map::MapChange(float* x, float* y)
{
	switch (m_mapstage)
	{
	case STAGE1:
		m_pMapBackGround->CsvRead("Stage1_Background.csv");
		m_pMapObject->CsvRead("Stage1_Object.csv");
		m_pMapGimmick->CsvRead("Stage1_Gimmick.csv");
		MapStartPos(x, y);
		break;
	case STAGE2:
		m_pMapBackGround->CsvRead("Stage1_Background.csv");
		m_pMapObject->CsvRead("Stage1_Object.csv");
		m_pMapGimmick->CsvRead("Stage1_Gimmick.csv");
		MapStartPos(x, y);
		break;
	case STAGE3:
		m_pMapBackGround->CsvRead("Stage1_Background.csv");
		m_pMapObject->CsvRead("Stage1_Object.csv");
		m_pMapGimmick->CsvRead("Stage1_Gimmick.csv");
		MapStartPos(x, y);
		break;
	case STAGE4:
		m_pMapBackGround->CsvRead("Stage1_Background.csv");
		m_pMapObject->CsvRead("Stage1_Object.csv");
		m_pMapGimmick->CsvRead("Stage1_Gimmick.csv");
		MapStartPos(x, y);
		break;
	}
}

/**
 * クリアしたかをチェックする関数
 * @param[in] x チェックするx座標
 * @param[in] y チェックするy座標
 * @return クリアしたらtrueが返る
 */
bool Map::ClearCheck(float x,float y)
{
	return m_pMapGimmick->ClearCheck(x,y);
}

void Map::MapStartPos(float* x, float* y)
{
	m_pMapGimmick->MapStartPos(x, y);
}
