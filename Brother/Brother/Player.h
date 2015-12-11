#ifndef PLAYER_H
#define PLAYER_H

#include "Vertex.h"

class Library;
class ModeManager;
class CollisionChecker;
class PlayerUI;
class GameTimeManager;
class DrawPositionSetter;
enum GAMEANIMA_ID;
enum GAMEMODE_NUM;

enum PLAYER_DIRECTION
{
	PLAYER_BACK,
	PLAYER_FRONT,
	PLAYER_LEFT,
	PLAYER_RIGHT,
	PLAYER_MAX
};

class Player
{
private:

protected:
	Library*			m_pLibrary;				//ライブラリクラス
	ModeManager*		m_pModeManager;			//Modeを管理するクラス、現在のモードを取得するときに使う
	CollisionChecker*	m_pCollisionChecker;	//あたり判定をとる時に使う
	DrawPositionSetter*	m_pDrawPositionSetter;	//プレイヤー座標の設定
	GameTimeManager*	m_pGameTimeManager;		//現在の時間を取得する
	PlayerUI*			m_pPlayerUI;			//playerUIを描画するときに使う
	GAMEANIMA_ID		m_CurrentAnima;			//現在のアニメーションを指す
	GAMEMODE_NUM		m_CurrentMode;			//現在のモードを指す
	bool*				m_pPadState;			//現在のキー状態
	bool*				m_pPadOldState;			//ひとつ前のキー状態
	int					m_Hp;					//PlayerのHp

public:
	Player(Library* pLibrary, bool* pPadState, bool* pPadOldState, CollisionChecker* pCollisionChecker, DrawPositionSetter* pDrawPositionSetter,GameTimeManager* pGameTimeManager);
	virtual ~Player();
	virtual void Control() = 0;
	virtual void Draw()    = 0;
	virtual void Move()    = 0;
	virtual void Action()  = 0;
	virtual void Init()    = 0;
	inline int GetHp(){ return m_Hp; };
	PLAYER_DIRECTION m_Direction;
	Position m_Ppos;
	float m_PlayerX;
	float m_PlayerY;
};

#endif