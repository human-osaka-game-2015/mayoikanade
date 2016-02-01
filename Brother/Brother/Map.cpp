#include "Map.h"
#include "Library.h"
#include "ServerGameScene.h"
#include "MapGimmick.h"
#include "MapBackGround.h"
#include "MapObject.h"
#include <stdio.h>


/**
 * Map�N���X�̃R���X�g���N�^
 * @param[in] pLibrary ���C�u�����N���X�̃|�C���^
 */
Map::Map(Library* pLibrary) : 
m_pLibrary(pLibrary)
{
	//�I�u�W�F�N�g�̐���
	m_pMapObject = new MapObject(m_pLibrary);
	m_pMapGimmick = new MapGimmick(m_pLibrary);
	m_pMapBackGround = new MapBackGround(m_pLibrary);
}

/**
 * MAp�N���X�̃f�X�g���N�^
 */
Map::~Map()
{
	//�I�u�W�F�N�g�̔j��
	delete m_pMapObject;
	delete m_pMapGimmick;
	delete m_pMapBackGround;
}


/**
 * Map�̃R���g���[���֐�
 */
void Map::Control()
{
	for (int i = FOR_DEFAULT_INIT; i < MAP_HEIGHT; i++)
	{
		for (int j = FOR_DEFAULT_INIT; j < MAP_WIDTH; j++)
		{
			if ((m_pMapGimmick->m_GimmickData[i][j]/GIMMICK_DATA) == SWITCH_BLUE_02)
			{
				if (m_pMapObject->m_ObjectData[i][j] == WOODBOX)
				{
					SwitchOn(j * static_cast<float>(MAPCHIP_SIZE), i * static_cast<float>(MAPCHIP_SIZE));
				}
				else
				{
					SwitchOff(j * static_cast<float>(MAPCHIP_SIZE), i * static_cast<float>(MAPCHIP_SIZE));
				}
			}
		}
	}
}

/**
 * Map�̕`��֐�
 */
void Map::Draw()
{
	//UV�̃Z�b�g
	m_pMapBackGround->MapTex_UV_Set(m_DrawPositionX, m_DrawPositionY);
	m_pMapGimmick->MapTex_UV_Set(m_DrawPositionX, m_DrawPositionY);
	m_pMapObject->MapTex_UV_Set(m_DrawPositionX, m_DrawPositionY);

	//XY�̃Z�b�g
	m_pMapBackGround->MapTex_XY_Set(m_DrawPositionX, m_DrawPositionY);
	m_pMapGimmick->MapTex_XY_Set(m_DrawPositionX, m_DrawPositionY);
	m_pMapObject->MapTex_XY_Set(m_DrawPositionX, m_DrawPositionY);

	//�`��
	m_pMapBackGround->Draw(m_DrawPositionX, m_DrawPositionY);
	m_pMapGimmick->Draw(m_DrawPositionX, m_DrawPositionY);
	m_pMapObject->Draw(m_DrawPositionX, m_DrawPositionY);
}


/**
 * �M�~�b�N�̃`�F�b�N�֐�
 * @param x �`�F�b�N����x���W
 * @param y �`�F�b�N����y���W
 * @return �`�F�b�N�������W�̃M�~�b�N�f�[�^
 */
int Map::GimmickCheck(float x, float y)
{
	return m_pMapGimmick->GimmickCheck(x, y);
}

/**
 * �X�C�b�`�������֐�
 * @param x �X�C�b�`������x���W
 * @param y �X�C�b�`������y���W
 */
void Map::SwitchOn(float x, float y)
{
	return m_pMapGimmick->SwitchOn(x, y);
}

/**
 * �X�C�b�`�������֐�(��p)
 * @param x �X�C�b�`������x���W
 * @param y �X�C�b�`������y���W
 */
void Map::SwitchOnYoung(float x, float y)
{
	return m_pMapGimmick->SwitchOnYoung(x, y);
}

/**
 * �X�C�b�`���I�t�ɂ���֐�(��p)
 * @param x �X�C�b�`���I�t�ɂ���x���W
 * @param y �X�C�b�`���I�t�ɂ���y���W
 */
void Map::SwitchOff(float x, float y)
{
	return m_pMapGimmick->SwitchOff(x, y);
}



/**
 * �I�u�W�F�N�g�̃`�F�b�N�֐�
 * @param[in] x �`�F�b�N����x���W 
 * @param[in] y �`�F�b�N����y���W
 * @return �`�F�b�N�������W�̃I�u�W�F�N�g���
 */
int Map::ObjectCheck(float x, float y)
{
	return m_pMapObject->ObjectCheck(x, y);
}

/**
 * �ؔ��̃`�F�b�N�֐�
 * @param[in] x �`�F�b�N����x���W
 * @param[in] y �`�F�b�N����y���W
 * @return �ؔ������������ǂ���
 */
bool Map::WoodBoxCheck(float x, float y)
{
	if (m_pMapObject->WoodBoxCheck(x, y) == true)
	{
		return true;
	}
	else if (m_pMapGimmick->WoodBoxHoleCheck(x, y) == true)
	{
		return true;
	}

	return false;
}

/**
 * �ؔ��̃Z�b�g����֐�
 * @param[in] x �Z�b�g����x���W
 * @param[in] y �Z�b�g����y���W
 * @return �ؔ����Z�b�g�ł�����
 */
bool Map::WoodBoxSet(float x, float y)
{
	switch (m_pMapGimmick->GimmickCheck(x, y))
	{
	case GATEPOST_01:
		return false;
		break;
	case GATEPOST_02:
		return false;
		break;
	case GATE_01:
		return false;
		break;
	case GATE_02:
		return false;
		break;
	case GATEPOST_PORTRAIT_01:
		return false;
		break;
	case GATEPOST_PORTRAIT_02:
		return false;
		break;
	case GATE_PORTRAIT_01:
		return false;
		break;
	case GATE_PORTRAIT_02:
		return false;
		break;
	
	}

	bool isBoxSet;

	if (m_pMapObject->WoodBoxSet(x, y))
	{
		isBoxSet = true;
	}
	if (m_pMapGimmick->HoleCheck(x, y))
	{
		m_pMapObject->WoodBoxCheck(x,y);
		isBoxSet = true;
	}

	if (isBoxSet)
	{
		m_pMapGimmick->SwitchOn(x, y);
	}

	return isBoxSet;
}


/**
 * �o�b�N�O���E���h���`�F�b�N����֐�
 * @param[in] x �`�F�b�N����x���W
 * @param[in] y �`�F�b�N����y���W
 * @return �o�b�N�O���E���h�̏�� 
 */
int Map::BackGroundCheck(float x, float y)
{
	return m_pMapBackGround->BackGroundCheck(x, y);
}


/**
 * ������(�c����)���`�F�b�N����֐�
 * @param[in] x �`�F�b�N����x���W
 * @param[in] y �`�F�b�N����y���W
 * @return ������(�c����)�����������ǂ���
 */
bool Map::GrassPortRaitCheck(float x, float y)
{
	return m_pMapGimmick->GrassPortRaitCheck(x, y);
}

/**
 * �����т��`�F�b�N����֐�
 * @param[in] x �`�F�b�N����x���W
 * @param[in] y �`�F�b�N����y���W
 * @return �����т����������ǂ���
 */
bool Map::GrassCheck(float x, float y)
{
	return m_pMapGimmick->GrassCheck(x, y);
}


/**
 * �����S���`�F�b�N����֐�
 * @param[in] x �`�F�b�N����x���W
 * @param[in] y �`�F�b�N����y���W
 * @return �����S�����������ǂ���
 */
bool Map::AppleCheck(float x, float y)
{
	return m_pMapGimmick->AppleCheck(x, y);
}

/**
 * �X�e�[�W��؂�ւ���֐�
 */
void Map::MapChange(float* x, float* y)
{
	switch (m_mapstage)
	{
	case STAGE1:
		m_pMapBackGround->CsvRead("Stage1_Background.csv");
		m_pMapObject->CsvRead("Stage1_Object.csv");
		m_pMapGimmick->CsvRead("Stage1_Gimmick.csv");
		MapStartPos(x, y);
		break;
	case STAGE2:
		m_pMapBackGround->CsvRead("Stage1_Background.csv");
		m_pMapObject->CsvRead("Stage1_Object.csv");
		m_pMapGimmick->CsvRead("Stage1_Gimmick.csv");
		MapStartPos(x, y);
		break;
	case STAGE3:
		m_pMapBackGround->CsvRead("Stage1_Background.csv");
		m_pMapObject->CsvRead("Stage1_Object.csv");
		m_pMapGimmick->CsvRead("Stage1_Gimmick.csv");
		MapStartPos(x, y);
		break;
	case STAGE4:
		m_pMapBackGround->CsvRead("Stage1_Background.csv");
		m_pMapObject->CsvRead("Stage1_Object.csv");
		m_pMapGimmick->CsvRead("Stage1_Gimmick.csv");
		MapStartPos(x, y);
		break;
	}
}

/**
 * �N���A���������`�F�b�N����֐�
 * @param[in] x �`�F�b�N����x���W
 * @param[in] y �`�F�b�N����y���W
 * @return �N���A������true���Ԃ�
 */
bool Map::ClearCheck(float x,float y)
{
	return m_pMapGimmick->ClearCheck(x,y);
}

void Map::MapStartPos(float* x, float* y)
{
	m_pMapGimmick->MapStartPos(x, y);
}
