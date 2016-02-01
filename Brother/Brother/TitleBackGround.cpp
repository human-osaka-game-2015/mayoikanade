#include "TitleBackGround.h"
#include "TitleScene.h"


/**
 * TitleBackGroundクラスのコンストラクタ
 * @param[in] pLibrary ライブラリクラス
 */
TitleBackGround::TitleBackGround(Library* pLibrary) :
m_pLibrary(pLibrary)
{
	//中央に来るように初期値設定
	m_Pos.x = TITLEBACKGROUNDPOS_X;
	m_Pos.y = TITLEBACKGROUNDPOS_Y;
}

/**
 * TitleBackGroundクラスのデストラクタ
 */
TitleBackGround::~TitleBackGround()
{

}

/**
 * TitleBackGroundの描画関数
 */
void TitleBackGround::Draw()
{
	CustomVertex background[SQUARE_VERTEX];

	m_pLibrary->MakePosition(TITLE_BACKGROUND, &m_Pos);

	m_pLibrary->MakeVertex(TITLE_BACKGROUND, background);
	m_pLibrary->xySet(m_Pos, background);

	m_pLibrary->DrawTexture(TEX_TITLE, background);
}