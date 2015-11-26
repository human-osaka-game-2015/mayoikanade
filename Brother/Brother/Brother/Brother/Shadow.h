#ifndef SHADOW_H
#define SHADOW_H


class Library;
class ModeManager;
enum GAMEMODE_NUM;


class Shadow
{
private:
	Library*			m_pLibrary;
	ModeManager*		m_pModeManager;
	GAMEMODE_NUM		m_CurrentMode;

public:
	Shadow(Library* pLibrary);
	~Shadow();
	void Control();
	void Draw();
	void ModeManagerSet(ModeManager* pModeManager);

};



#endif