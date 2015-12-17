#ifndef TEXT_H
#define TEXT_H


class Library;
class ModeManager;
enum GAMEMODE_NUM;



class Text
{
private:
	Library*			m_pLibrary;
	ModeManager*		m_pModeManager;
	GAMEMODE_NUM		m_CurrentMode;

public:
	Text(Library* pLibrary);
	~Text();
	void Control();
	void Draw();
	void ModeManagerSet(ModeManager* pModeManager);

};

#endif