#include "ClientPlayerUI.h"
#include "Library.h"
#include "ClientGameScene.h"


ClientPlayerUI::ClientPlayerUI(Library* pLibrary, const int& Hp, int frameTexId, int barTexId, int face1id, int face2id, int face3id, float x, float y, float face_x, float face_y) :
m_pLibrary(pLibrary),
m_PlayerHp(Hp),
m_FrameTexId(frameTexId),
m_BarTexId(barTexId),
m_face1Id(face1id),
m_face2Id(face2id),
m_face3Id(face3id)
{
	m_FrameUiPos.x = x;
	m_FrameUiPos.y = y;

	m_BarUiPos.x = x;
	m_BarUiPos.y = y;

	m_FacialExpression.x = face_x;
	m_FacialExpression.y = face_y;
}

ClientPlayerUI::~ClientPlayerUI()
{
	
}

void ClientPlayerUI::Control()
{

}

void ClientPlayerUI::Draw()
{
	int Damage = int(240 - (m_PlayerHp * 2.4));
	CustomVertex frameUi[4];
	CustomVertex barUi[4];
	CustomVertex faceUi[4];

	//体力バーの座標設定
	m_pLibrary->MakePosition(m_BarTexId, &m_BarUiPos);
	m_pLibrary->MakeVertex(m_BarTexId, barUi);
	m_pLibrary->xySet(m_BarUiPos, barUi);

	//フレームの座標設定
	m_pLibrary->MakePosition(m_FrameTexId, &m_FrameUiPos);
	m_pLibrary->MakeVertex(m_FrameTexId, frameUi);
	m_pLibrary->xySet(m_FrameUiPos, frameUi);


	//体力の減少分バーを短くする
	barUi[1].x -= Damage;
	barUi[2].x -= Damage;

	//体力の減少分バーを短くするPART２
	barUi[1].tu = barUi[2].tu = barUi[0].tu + (barUi[1].tu - barUi[0].tu)*m_PlayerHp / 100;


	//ライフバーとフレームの描画
	m_pLibrary->DrawTexture(TEX_GAME, frameUi);
	m_pLibrary->DrawTexture(TEX_GAME, barUi);

	//体力が多い時
	if (m_PlayerHp >= 75)
	{
		m_pLibrary->MakePosition(m_face1Id, &m_FacialExpression);
		m_pLibrary->MakeVertex(m_face1Id, faceUi);
		m_pLibrary->xySet(m_FacialExpression, faceUi);
		m_pLibrary->DrawTexture(TEX_GAME, faceUi);
	}
	//体力が中量の時
	else if (m_PlayerHp >= 25)
	{
		m_pLibrary->MakePosition(m_face2Id, &m_FacialExpression);
		m_pLibrary->MakeVertex(m_face2Id, faceUi);
		m_pLibrary->xySet(m_FacialExpression, faceUi);
		m_pLibrary->DrawTexture(TEX_GAME, faceUi);
	}
	//体力が少ない時
	else
	{
		m_pLibrary->MakePosition(m_face3Id, &m_FacialExpression);
		m_pLibrary->MakeVertex(m_face3Id, faceUi);
		m_pLibrary->xySet(m_FacialExpression, faceUi);
		m_pLibrary->DrawTexture(TEX_GAME, faceUi);
	}

}
