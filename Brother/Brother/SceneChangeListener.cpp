#include "SceneChangeListener.h"

/**
 * SceneChangeListenerクラスのコンストラクタ
 * @param[out] SceneNum 遷移先を格納する変数のポインタ
 * @param[out] isClear ゲームがクリアしたかを格納するポインタ
 */
SceneChangeListener::SceneChangeListener(SCENE_NUM* SceneNum, bool* isClear)
{
	m_pNextScene = SceneNum;
	m_pisGameClear = isClear;
}

/**
 * SceneChangeListenerクラスのデストラクタ
 */
SceneChangeListener::~SceneChangeListener()
{

}

/**
 * シーンを更新する関数
 * @param[in] UpdateId 更新するシーンへのenum
 */
void SceneChangeListener::Update(GAMEUPDATE_NUM UpdateId)
{
	if (UpdateId == GAMEOVER_UPDATE)
	{
		//*m_pisGameClear = false;
		*m_pNextScene = RESULT_SCENE;
	}
}
