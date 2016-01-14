#ifndef PLAYER_H
#define PLAYER_H

#define NEAR_DISTANCE 200
#define FAR_DISTANCE 700

#include "Vertex.h"

class Library;
class ServerModeManager;
class ServerCollisionChecker;
class ServerPlayerUI;
class ServerGameTimeManager;
class ServerDrawPositionSetter;
enum GAMEANIMA_ID;
enum GAMEMODE_NUM;
enum PADSTATE;

enum PLAYER_DIRECTION
{
	PLAYER_BACK,
	PLAYER_FRONT,
	PLAYER_LEFT,
	PLAYER_RIGHT,
	PLAYER_MAX
};

class ServerPlayer
{
private:

protected:
	Library*					m_pLibrary;				//ライブラリクラス
	ServerModeManager*			m_pModeManager;			//Modeを管理するクラス、現在のモードを取得するときに使う
	ServerCollisionChecker*		m_pCollisionChecker;	//あたり判定をとる時に使う
	ServerDrawPositionSetter*	m_pDrawPositionSetter;	//プレイヤー座標の設定
	ServerGameTimeManager*		m_pGameTimeManager;		//現在の時間を取得する
	ServerPlayerUI*				m_pPlayerUI;			//playerUIを描画するときに使う
	GAMEANIMA_ID				m_CurrentAnima;			//現在のアニメーションを指す
	GAMEMODE_NUM				m_CurrentMode;			//現在のモードを指す
	bool*						m_pPadState;			//現在のスティック状態
	bool*						m_pPadOldState;			//ひとつ前のスティック状態
	PADSTATE*					m_pButtonState;			//現在のボタン状態

	int							m_Hp;					//PlayerのHp

public:
	ServerPlayer(Library* pLibrary, bool* pPadState, bool* pPadOldState, PADSTATE* pButtonState, ServerCollisionChecker* pCollisionChecker, ServerDrawPositionSetter* pDrawPositionSetter, ServerGameTimeManager* pGameTimeManager);
	virtual ~ServerPlayer();
	virtual void Control() = 0;
	virtual void Draw()    = 0;
	virtual void Move()    = 0;
	virtual void Action()  = 0;
	virtual void Update()  = 0;
	virtual void Init()    = 0;
	inline int GetHp(){ return m_Hp; };
	inline float GetPositionX(){ return m_Ppos.x; };
	inline float GetPositionY(){ return m_Ppos.y; };
	inline float GetMapPositionX(){ return m_Ppos.x + m_PlayerX; };
	inline float GetMapPositionY(){ return m_Ppos.y + m_PlayerY; };
	PLAYER_DIRECTION m_Direction;
	Position m_Ppos;
	float m_PlayerX;
	float m_PlayerY;
};

#endif