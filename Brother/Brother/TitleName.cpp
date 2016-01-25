#include "TitleName.h"
#include "TitleScene.h"


/**
 * TitleTimeManagerクラスのコンストラクタ
 * param[in] pLibrary ライブラリクラス
 */
TitleName::TitleName(Library* pLibrary) :
m_pLibrary(pLibrary)
{
	//中央に来るように初期値設定
	m_Pos.x = TITLENAMEPOS_X;
	m_Pos.y = TITLENAMEPOS_Y;
}


/**
 * TitleNameクラスのデストラクタ
 */
TitleName::~TitleName()
{

}

/**
 * TitleNameのコントロール関数
 */
void TitleName::Control()
{

}

/**
 * TitleNameの描画関数
 */
void TitleName::Draw()
{
	CustomVertex titlename[SQUARE_VERTEX];

	m_pLibrary->MakePosition(TITLE_NAME, &m_Pos);

	m_pLibrary->MakeVertex(TITLE_NAME, titlename);
	m_pLibrary->xySet(m_Pos, titlename);

	m_pLibrary->DrawTexture(TEX_TITLE, titlename);
}
