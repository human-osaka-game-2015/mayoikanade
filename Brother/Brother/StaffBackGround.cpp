#include "StaffBackGround.h"
#include "StaffScene.h"


/**
 * StaffBackGroundクラスのコンストラクタ
 * @param[in] pLibrary	ライブラリクラス
 */
StaffBackGround::StaffBackGround(Library* pLibrary) :
m_pLibrary(pLibrary)
{
	//中央に来るように初期値設定
	m_Pos.x = STAFFBACKGROUNDPOS_X;
	m_Pos.y = STAFFBACKGROUNDPOS_Y;
}

/**
 * StaffBackGroundクラスのデストラクタ
 */
StaffBackGround::~StaffBackGround()
{

}

/**
 * StaffBackGroundの描画関数
 */
void StaffBackGround::Draw()
{
	CustomVertex background[SQUARE_VERTEX];

	m_pLibrary->MakePosition(STAFF, &m_Pos);

	m_pLibrary->MakeVertex(STAFF, background);
	
	m_pLibrary->xySet(m_Pos, background);

	m_pLibrary->DrawTexture(TEX_STAFF, background);
}
