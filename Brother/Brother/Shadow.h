#ifndef SHADOW_H
#define SHADOW_H

#define SHADOW_POS_X 600		//影のX座標
#define SHADOW_POS_Y 350		//影のY座標
#define SHADOW_POS_W 15000		//影の幅
#define SHADOW_POS_H 15000		//影の高さ

#define SHADOW_REDUCTION 10		//影の縮小量
#define SHADOW_MIN 0			//影の大きさの最小値
#define ONE_SECCOND 60			//1秒のフレーム数
#define ONE_FRAME 0				//比較用の数値
#define STENCIL_X 0.0f			//ステンシルのVertexの初期x座標
#define STENCIL_Y 0.0f			//ステンシルのVertexの初期y座標
#define STENCIL_Z 0.5f			//ステンシルのVertexの初期z座標
#define STENCIL_RHW 1.0f
#define STENCIL_COLOR 0xffffffff
#define STENCIL_TU_MAX 1.0f
#define STENCIL_TV_MAX 1.0f
#define STENCIL_TU_MIN 0.0f
#define STENCIL_TV_MIN 0.0f

#define DEFAULT_REF 0x00		//デフォルトのステンシル参照値
#define SHADOW_REF 0x02			//影部分の参照値



#include "Vertex.h"

class Library;
class ModeManager;
class GameTimeManager;
enum GAMEMODE_NUM;


class Shadow
{
private:
	Library*			m_pLibrary;
	ModeManager*		m_pModeManager;
	GameTimeManager*	m_GameTimeManager;
	GAMEMODE_NUM		m_CurrentMode;
	Position			m_Pos;
	bool				m_isGameOverInit;

public:
	Shadow(Library* pLibrary, GameTimeManager* pGameTimeManager);
	~Shadow();
	void Control();
	void Draw();
	void ModeManagerSet(ModeManager* pModeManager);
	bool ShadowCheck();

};



#endif