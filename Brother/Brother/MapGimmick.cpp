#include "ServerGameScene.h"
#include "MapGimmick.h"
#include "Library.h"


/**
 * MapGimmick�N���X�̃R���X�g���N�^
 * @param[in] pLibrary ���C�u�����N���X�̃|�C���^
 */
MapGimmick::MapGimmick(Library* pLibrary) :
m_pLibrary(pLibrary)
{
	CsvRead("Stage1_Gimmick.csv");
}

/**
 * MapGimmick�N���X�̃f�X�g���N�^
 */
MapGimmick::~MapGimmick()
{

}

/**
 * CSV�̃}�b�v����ǂݍ��ފ֐�
 * @param[in] filename �ǂݍ��ރt�@�C���̖��O
 * @return �����������ǂ���
 */
bool MapGimmick::CsvRead(const char* filename)
{
	FILE*  fp = NULL;
	fopen_s(&fp, filename, "r");

	if (fp == NULL)
	{
		return false;
	}

	for (int i = FOR_DEFAULT_INIT; i < MAP_HEIGHT; i++)
	{
		for (int j = FOR_DEFAULT_INIT; j < MAP_WIDTH; j++)
		{
			fscanf_s(fp, "%d,", &m_GimmickData[i][j], _countof(m_GimmickData));
		}
	}
	fclose(fp);

	return true;
}


/**
 * MapGimmick�̕`��֐�
 * @param[in] DrawPosX x���W�̕`��ʒu
 * @param[in] DrawPosY y���W�̕`��ʒu
 */
void MapGimmick::Draw(float DrawPosX, float DrawPosY)
{
	int count_x = static_cast<int>((DrawPosX - MAPCHIP_SIZE) / MAPCHIP_SIZE);
	int count_y = static_cast<int>((DrawPosY - MAPCHIP_SIZE) / MAPCHIP_SIZE);

	if (count_x < MAP_LEFT)
	{
		count_x = MAP_LEFT;
	}
	if (count_y < MAP_TOP)
	{
		count_y = MAP_TOP;
	}


	//�`��̈�����߂đ�� �]���Ɉ����ǂ�ł�̂�64�����Ă���
	int ScreenRight  = static_cast<int>((DrawPosX + SCREEN_SIZEX + MAPCHIP_SIZE) / MAPCHIP_SIZE);
	int ScreenBottom = static_cast<int>((DrawPosY + SCREEN_SIZEY + MAPCHIP_SIZE) / MAPCHIP_SIZE);

	if (ScreenRight > MAP_WIDTH)
	{
		ScreenRight = MAP_WIDTH;
	}
	if (ScreenBottom > MAP_HEIGHT)
	{
		ScreenBottom = MAP_HEIGHT;
	}

	for (int i = count_y; i < ScreenBottom; i++)
	{
		for (int j = count_x; j < ScreenRight; j++)
		{
			m_pLibrary->DrawTexture(TEX_GAME, m_MapGimmick_Tex[i][j]);
		}
	}
}


/**
 * �w�肵�����W�ɂ���M�~�b�N���Ȃ�ł��邩��Ԃ��܂�
 * @param[in] x �`�F�b�N����x���W
 * @param[in] y �`�F�b�N����y���W
 * @return �M�~�b�N��enum
 */
int MapGimmick::GimmickCheck(float x, float y)
{
	int arrayx = ARRAY_DEFAULT_INIT, arrayy = ARRAY_DEFAULT_INIT;
	arrayx = int(x / MAPCHIP_SIZE);
	arrayy = int(y / MAPCHIP_SIZE);

	return m_GimmickData[arrayy][arrayx] / GIMMICK_DATA;
}


/**
 * �X�C�b�`�������֐� �w�肵�����W�ɂ���X�C�b�`�������B �����Ȃ���΃X���[
 * @param[in] x �X�C�b�`������x���W
 * @param[in] y �X�C�b�`������y���W
 */
void MapGimmick::SwitchOn(float x, float y)
{
	int arrayx = ARRAY_DEFAULT_INIT, arrayy = ARRAY_DEFAULT_INIT;
	int switchCount = SWITCH_COUNT_INIT;
	arrayx = static_cast<int>(x / MAPCHIP_SIZE);
	arrayy = static_cast<int>(y / MAPCHIP_SIZE);


	//�X�C�b�`�������ꂽ���̏���
	switch (m_GimmickData[arrayy][arrayx] / GIMMICK_DATA)
	{
	case SWITCH_RED_01:
		m_GimmickData[arrayy][arrayx] = (m_GimmickData[arrayy][arrayx] % GIMMICK_DATA + SWITCH_RED_02 * GIMMICK_DATA);
		switchCount = SWITCH_COUNT_INIT;

		for (int i = FOR_DEFAULT_INIT; i < MAP_HEIGHT; i++)
		{
			for (int j = FOR_DEFAULT_INIT; j < MAP_WIDTH; j++)
			{
				if (m_GimmickData[i][j] == m_GimmickData[arrayy][arrayx] % GIMMICK_DATA + SWITCH_RED_01 * GIMMICK_DATA)
				{
					switchCount++;
				}
			}
		}

		if (switchCount == SWITCH_COUNT_INIT)
		{

			for (int i = FOR_DEFAULT_INIT; i < MAP_HEIGHT; i++)
			{
				for (int j = FOR_DEFAULT_INIT; j < MAP_WIDTH; j++)
				{
					if (m_GimmickData[i][j] / GIMMICK_DATA == GATE_01 && m_GimmickData[i][j] % GIMMICK_DATA == m_GimmickData[arrayy][arrayx] % GIMMICK_DATA)
					{
						m_GimmickData[i][j] = (LOSTGATE_01 * GIMMICK_DATA) + (m_GimmickData[i][j] % GIMMICK_DATA);
					}
					else if (m_GimmickData[i][j] / GIMMICK_DATA == GATE_02 && m_GimmickData[i][j] % GIMMICK_DATA == m_GimmickData[arrayy][arrayx] % GIMMICK_DATA)
					{
						m_GimmickData[i][j] = (LOSTGATE_02 * GIMMICK_DATA) + (m_GimmickData[i][j] % GIMMICK_DATA);
					}
					else if (m_GimmickData[i][j] / GIMMICK_DATA == GATE_PORTRAIT_01 && m_GimmickData[i][j] % GIMMICK_DATA == m_GimmickData[arrayy][arrayx] % GIMMICK_DATA)
					{
						m_GimmickData[i][j] = (LOSTGATE_03 * GIMMICK_DATA) + (m_GimmickData[i][j] % GIMMICK_DATA);
					}
					else if (m_GimmickData[i][j] / GIMMICK_DATA == GATE_PORTRAIT_02 && m_GimmickData[i][j] % GIMMICK_DATA == m_GimmickData[arrayy][arrayx] % GIMMICK_DATA)
					{
						m_GimmickData[i][j] = (LOSTGATE_04 * GIMMICK_DATA) + (m_GimmickData[i][j] % GIMMICK_DATA);
					}
				}
			}
		}

		break;
	case SWITCH_BLUE_01:
		m_GimmickData[arrayy][arrayx] = (m_GimmickData[arrayy][arrayx] % GIMMICK_DATA + SWITCH_BLUE_02 * GIMMICK_DATA);
		switchCount = SWITCH_COUNT_INIT;

		for (int i = FOR_DEFAULT_INIT; i < MAP_HEIGHT; i++)
		{
			for (int j = FOR_DEFAULT_INIT; j < MAP_WIDTH; j++)
			{
				if (m_GimmickData[i][j] == m_GimmickData[arrayy][arrayx] % GIMMICK_DATA + SWITCH_BLUE_01 * GIMMICK_DATA)
				{
					switchCount++;
				}
			}
		}

		if (switchCount == SWITCH_COUNT_INIT)
		{
			for (int i = FOR_DEFAULT_INIT; i < MAP_HEIGHT; i++)
			{
				for (int j = FOR_DEFAULT_INIT; j < MAP_WIDTH; j++)
				{
					if (m_GimmickData[i][j] / GIMMICK_DATA == GATE_01 && m_GimmickData[i][j] % GIMMICK_DATA == m_GimmickData[arrayy][arrayx] % GIMMICK_DATA)
					{
						m_GimmickData[i][j] = (LOSTGATE_01 * GIMMICK_DATA) + (m_GimmickData[i][j] % GIMMICK_DATA);
					}
					else if (m_GimmickData[i][j] / GIMMICK_DATA == GATE_02 && m_GimmickData[i][j] % GIMMICK_DATA == m_GimmickData[arrayy][arrayx] % GIMMICK_DATA)
					{
						m_GimmickData[i][j] = (LOSTGATE_02 * GIMMICK_DATA) + (m_GimmickData[i][j] % GIMMICK_DATA);
					}
					else if (m_GimmickData[i][j] / GIMMICK_DATA == GATE_PORTRAIT_01 && m_GimmickData[i][j] % GIMMICK_DATA == m_GimmickData[arrayy][arrayx] % GIMMICK_DATA)
					{
						m_GimmickData[i][j] = (LOSTGATE_03 * GIMMICK_DATA) + (m_GimmickData[i][j] % GIMMICK_DATA);
					}
					else if (m_GimmickData[i][j] / GIMMICK_DATA == GATE_PORTRAIT_02 && m_GimmickData[i][j] % GIMMICK_DATA == m_GimmickData[arrayy][arrayx] % GIMMICK_DATA)
					{
						m_GimmickData[i][j] = (LOSTGATE_04 * GIMMICK_DATA) + (m_GimmickData[i][j] % GIMMICK_DATA);
					}
				}
			}
		}

		break;
	case SWITCH_YELLOW_01:
		m_GimmickData[arrayy][arrayx] = (m_GimmickData[arrayy][arrayx] % GIMMICK_DATA + SWITCH_YELLOW_02 * GIMMICK_DATA);
		switchCount = SWITCH_COUNT_INIT;

		for (int i = FOR_DEFAULT_INIT; i < MAP_HEIGHT; i++)
		{
			for (int j = FOR_DEFAULT_INIT; j < MAP_WIDTH; j++)
			{
				if (m_GimmickData[i][j] == m_GimmickData[arrayy][arrayx] % GIMMICK_DATA + SWITCH_YELLOW_01 * GIMMICK_DATA)
				{
					switchCount++;
				}
			}
		}

		if (switchCount == SWITCH_COUNT_INIT)
		{

			for (int i = FOR_DEFAULT_INIT; i < MAP_HEIGHT; i++)
			{
				for (int j = FOR_DEFAULT_INIT; j < MAP_WIDTH; j++)
				{
					if (m_GimmickData[i][j] / GIMMICK_DATA == GATE_01 && m_GimmickData[i][j] % GIMMICK_DATA == m_GimmickData[arrayy][arrayx] % GIMMICK_DATA)
					{
						m_GimmickData[i][j] = (LOSTGATE_01 * GIMMICK_DATA) + (m_GimmickData[i][j] % GIMMICK_DATA);
					}
					else if (m_GimmickData[i][j] / GIMMICK_DATA == GATE_02 && m_GimmickData[i][j] % GIMMICK_DATA == m_GimmickData[arrayy][arrayx] % GIMMICK_DATA)
					{
						m_GimmickData[i][j] = (LOSTGATE_02 * GIMMICK_DATA) + (m_GimmickData[i][j] % GIMMICK_DATA);
					}
					else if (m_GimmickData[i][j] / GIMMICK_DATA == GATE_PORTRAIT_01 && m_GimmickData[i][j] % GIMMICK_DATA == m_GimmickData[arrayy][arrayx] % GIMMICK_DATA)
					{
						m_GimmickData[i][j] = (LOSTGATE_03 * GIMMICK_DATA) + (m_GimmickData[i][j] % GIMMICK_DATA);
					}
					else if (m_GimmickData[i][j] / GIMMICK_DATA == GATE_PORTRAIT_02 && m_GimmickData[i][j] % GIMMICK_DATA == m_GimmickData[arrayy][arrayx] % GIMMICK_DATA)
					{
						m_GimmickData[i][j] = (LOSTGATE_04 * GIMMICK_DATA) + (m_GimmickData[i][j] % GIMMICK_DATA);
					}
				}
			}
		}

		break;
	default:
		break;
	}

}


/**
 * �X�C�b�`�������֐�(��p) �w�肵�����W�ɂ���X�C�b�`�������B �����Ȃ���΃X���[
 * @param[in] x �X�C�b�`������x���W
 * @param[in] y �X�C�b�`������y���W
 */
void MapGimmick::SwitchOnYoung(float x, float y)
{
	int arrayx = ARRAY_DEFAULT_INIT, arrayy = ARRAY_DEFAULT_INIT;
	int switchCount = SWITCH_COUNT_INIT;
	arrayx = static_cast<int>(x / MAPCHIP_SIZE);
	arrayy = static_cast<int>(y / MAPCHIP_SIZE);


	//�X�C�b�`�������ꂽ���̏���
	switch (m_GimmickData[arrayy][arrayx] / GIMMICK_DATA)
	{
	case SWITCH_RED_01:
		break;
	case SWITCH_BLUE_01:
		m_GimmickData[arrayy][arrayx] = (m_GimmickData[arrayy][arrayx] % GIMMICK_DATA + SWITCH_BLUE_02 * GIMMICK_DATA);
		switchCount = SWITCH_COUNT_INIT;

		for (int i = FOR_DEFAULT_INIT; i < MAP_HEIGHT; i++)
		{
			for (int j = FOR_DEFAULT_INIT; j < MAP_WIDTH; j++)
			{
				if (m_GimmickData[i][j] == m_GimmickData[arrayy][arrayx] % GIMMICK_DATA + SWITCH_BLUE_01 * GIMMICK_DATA)
				{
					switchCount++;
				}
			}
		}

		if (switchCount == SWITCH_COUNT_INIT)
		{
			for (int i = FOR_DEFAULT_INIT; i < MAP_HEIGHT; i++)
			{
				for (int j = FOR_DEFAULT_INIT; j < MAP_WIDTH; j++)
				{
					if (m_GimmickData[i][j] / GIMMICK_DATA == GATE_01 && m_GimmickData[i][j] % GIMMICK_DATA == m_GimmickData[arrayy][arrayx] % GIMMICK_DATA)
					{
						m_GimmickData[i][j] = (LOSTGATE_01 * GIMMICK_DATA) + (m_GimmickData[i][j] % GIMMICK_DATA);
					}
					else if (m_GimmickData[i][j] / GIMMICK_DATA == GATE_02 && m_GimmickData[i][j] % GIMMICK_DATA == m_GimmickData[arrayy][arrayx] % GIMMICK_DATA)
					{
						m_GimmickData[i][j] = (LOSTGATE_02 * GIMMICK_DATA) + (m_GimmickData[i][j] % GIMMICK_DATA);
					}
					else if (m_GimmickData[i][j] / GIMMICK_DATA == GATE_PORTRAIT_01 && m_GimmickData[i][j] % GIMMICK_DATA == m_GimmickData[arrayy][arrayx] % GIMMICK_DATA)
					{
						m_GimmickData[i][j] = (LOSTGATE_03 * GIMMICK_DATA) + (m_GimmickData[i][j] % GIMMICK_DATA);
					}
					else if (m_GimmickData[i][j] / GIMMICK_DATA == GATE_PORTRAIT_02 && m_GimmickData[i][j] % GIMMICK_DATA == m_GimmickData[arrayy][arrayx] % GIMMICK_DATA)
					{
						m_GimmickData[i][j] = (LOSTGATE_04 * GIMMICK_DATA) + (m_GimmickData[i][j] % GIMMICK_DATA);
					}
				}
			}
		}

		break;
	case SWITCH_YELLOW_01:
		m_GimmickData[arrayy][arrayx] = (m_GimmickData[arrayy][arrayx] % GIMMICK_DATA + SWITCH_YELLOW_02 * GIMMICK_DATA);
		switchCount = SWITCH_COUNT_INIT;

		for (int i = FOR_DEFAULT_INIT; i < MAP_HEIGHT; i++)
		{
			for (int j = FOR_DEFAULT_INIT; j < MAP_WIDTH; j++)
			{
				if (m_GimmickData[i][j] == m_GimmickData[arrayy][arrayx] % GIMMICK_DATA + SWITCH_YELLOW_01 * GIMMICK_DATA)
				{
					switchCount++;
				}
			}
		}

		if (switchCount == SWITCH_COUNT_INIT)
		{

			for (int i = FOR_DEFAULT_INIT; i < MAP_HEIGHT; i++)
			{
				for (int j = FOR_DEFAULT_INIT; j < MAP_WIDTH; j++)
				{
					if (m_GimmickData[i][j] / GIMMICK_DATA == GATE_01 && m_GimmickData[i][j] % GIMMICK_DATA == m_GimmickData[arrayy][arrayx] % GIMMICK_DATA)
					{
						m_GimmickData[i][j] = (LOSTGATE_01 * GIMMICK_DATA) + (m_GimmickData[i][j] % GIMMICK_DATA);
					}
					else if (m_GimmickData[i][j] / GIMMICK_DATA == GATE_02 && m_GimmickData[i][j] % GIMMICK_DATA == m_GimmickData[arrayy][arrayx] % GIMMICK_DATA)
					{
						m_GimmickData[i][j] = (LOSTGATE_02 * GIMMICK_DATA) + (m_GimmickData[i][j] % GIMMICK_DATA);
					}
					else if (m_GimmickData[i][j] / GIMMICK_DATA == GATE_PORTRAIT_01 && m_GimmickData[i][j] % GIMMICK_DATA == m_GimmickData[arrayy][arrayx] % GIMMICK_DATA)
					{
						m_GimmickData[i][j] = (LOSTGATE_03 * GIMMICK_DATA) + (m_GimmickData[i][j] % GIMMICK_DATA);
					}
					else if (m_GimmickData[i][j] / GIMMICK_DATA == GATE_PORTRAIT_02 && m_GimmickData[i][j] % GIMMICK_DATA == m_GimmickData[arrayy][arrayx] % GIMMICK_DATA)
					{
						m_GimmickData[i][j] = (LOSTGATE_04 * GIMMICK_DATA) + (m_GimmickData[i][j] % GIMMICK_DATA);
					}
				}
			}
		}

		break;
	default:
		break;
	}
}


/**
 * �X�C�b�`���I�t�ɂ���֐�
 * @param[in] �I�t�ɂ���X�C�b�`��x���W
 * @param[in] �I�t�ɂ���X�C�b�`��y���W
 */
void MapGimmick::SwitchOff(float x, float y)
{
	int arrayx = ARRAY_DEFAULT_INIT, arrayy = ARRAY_DEFAULT_INIT;
	arrayx = static_cast<int>(x / MAPCHIP_SIZE);
	arrayy = static_cast<int>(y / MAPCHIP_SIZE);


	//�X�C�b�`�������ꂽ���̏���
	switch (m_GimmickData[arrayy][arrayx] / GIMMICK_DATA)
	{
	case SWITCH_RED_02:
		m_GimmickData[arrayy][arrayx] = (m_GimmickData[arrayy][arrayx] % GIMMICK_DATA + SWITCH_RED_01 * GIMMICK_DATA);

		for (int i = FOR_DEFAULT_INIT; i < MAP_HEIGHT; i++)
		{
			for (int j = FOR_DEFAULT_INIT; j < MAP_WIDTH; j++)
			{
				if (m_GimmickData[i][j] / GIMMICK_DATA == LOSTGATE_01 && m_GimmickData[i][j] % GIMMICK_DATA == m_GimmickData[arrayy][arrayx] % GIMMICK_DATA)
				{
					m_GimmickData[i][j] = (GATE_01 * GIMMICK_DATA) + (m_GimmickData[i][j] % GIMMICK_DATA);
				}
				else if (m_GimmickData[i][j] / GIMMICK_DATA == LOSTGATE_02 && m_GimmickData[i][j] % GIMMICK_DATA == m_GimmickData[arrayy][arrayx] % GIMMICK_DATA)
				{
					m_GimmickData[i][j] = (GATE_02 * GIMMICK_DATA) + (m_GimmickData[i][j] % GIMMICK_DATA);
				}
				else if (m_GimmickData[i][j] / GIMMICK_DATA == LOSTGATE_03 && m_GimmickData[i][j] % GIMMICK_DATA == m_GimmickData[arrayy][arrayx] % GIMMICK_DATA)
				{
					m_GimmickData[i][j] = (GATE_PORTRAIT_01 * GIMMICK_DATA) + (m_GimmickData[i][j] % GIMMICK_DATA);
				}
				else if (m_GimmickData[i][j] / GIMMICK_DATA == LOSTGATE_04 && m_GimmickData[i][j] % GIMMICK_DATA == m_GimmickData[arrayy][arrayx] % GIMMICK_DATA)
				{
					m_GimmickData[i][j] = (GATE_PORTRAIT_02 * GIMMICK_DATA) + (m_GimmickData[i][j] % GIMMICK_DATA);
				}
			}
		}

		break;
	case SWITCH_BLUE_02:
		m_GimmickData[arrayy][arrayx] = (m_GimmickData[arrayy][arrayx] % GIMMICK_DATA + SWITCH_BLUE_01 * GIMMICK_DATA);

		for (int i = FOR_DEFAULT_INIT; i < MAP_HEIGHT; i++)
		{
			for (int j = FOR_DEFAULT_INIT; j < MAP_WIDTH; j++)
			{
				if (m_GimmickData[i][j] / GIMMICK_DATA == LOSTGATE_01 && m_GimmickData[i][j] % GIMMICK_DATA == m_GimmickData[arrayy][arrayx] % GIMMICK_DATA)
				{
					m_GimmickData[i][j] = (GATE_01 * GIMMICK_DATA) + (m_GimmickData[i][j] % GIMMICK_DATA);
				}
				else if (m_GimmickData[i][j] / GIMMICK_DATA == LOSTGATE_02 && m_GimmickData[i][j] % GIMMICK_DATA == m_GimmickData[arrayy][arrayx] % GIMMICK_DATA)
				{
					m_GimmickData[i][j] = (GATE_02 * GIMMICK_DATA) + (m_GimmickData[i][j] % GIMMICK_DATA);
				}
				else if (m_GimmickData[i][j] / GIMMICK_DATA == LOSTGATE_03 && m_GimmickData[i][j] % GIMMICK_DATA == m_GimmickData[arrayy][arrayx] % GIMMICK_DATA)
				{
					m_GimmickData[i][j] = (GATE_PORTRAIT_01 * GIMMICK_DATA) + (m_GimmickData[i][j] % GIMMICK_DATA);
				}
				else if (m_GimmickData[i][j] / GIMMICK_DATA == LOSTGATE_04 && m_GimmickData[i][j] % GIMMICK_DATA == m_GimmickData[arrayy][arrayx] % GIMMICK_DATA)
				{
					m_GimmickData[i][j] = (GATE_PORTRAIT_02 * GIMMICK_DATA) + (m_GimmickData[i][j] % GIMMICK_DATA);
				}
			}
		}

		break;
	case SWITCH_YELLOW_02:
		m_GimmickData[arrayy][arrayx] = (m_GimmickData[arrayy][arrayx] % GIMMICK_DATA + SWITCH_YELLOW_01 * GIMMICK_DATA);

		for (int i = FOR_DEFAULT_INIT; i < MAP_HEIGHT; i++)
		{
			for (int j = FOR_DEFAULT_INIT; j < MAP_WIDTH; j++)
			{
				if (m_GimmickData[i][j] / GIMMICK_DATA == LOSTGATE_01 && m_GimmickData[i][j] % GIMMICK_DATA == m_GimmickData[arrayy][arrayx] % GIMMICK_DATA)
				{
					m_GimmickData[i][j] = (GATE_01 * GIMMICK_DATA) + (m_GimmickData[i][j] % GIMMICK_DATA);
				}
				else if (m_GimmickData[i][j] / GIMMICK_DATA == LOSTGATE_02 && m_GimmickData[i][j] % GIMMICK_DATA == m_GimmickData[arrayy][arrayx] % GIMMICK_DATA)
				{
					m_GimmickData[i][j] = (GATE_02 * GIMMICK_DATA) + (m_GimmickData[i][j] % GIMMICK_DATA);
				}
				else if (m_GimmickData[i][j] / GIMMICK_DATA == LOSTGATE_03 && m_GimmickData[i][j] % GIMMICK_DATA == m_GimmickData[arrayy][arrayx] % GIMMICK_DATA)
				{
					m_GimmickData[i][j] = (GATE_PORTRAIT_01 * GIMMICK_DATA) + (m_GimmickData[i][j] % GIMMICK_DATA);
				}
				else if (m_GimmickData[i][j] / GIMMICK_DATA == LOSTGATE_04 && m_GimmickData[i][j] % GIMMICK_DATA == m_GimmickData[arrayy][arrayx] % GIMMICK_DATA)
				{
					m_GimmickData[i][j] = (GATE_PORTRAIT_02 * GIMMICK_DATA) + (m_GimmickData[i][j] % GIMMICK_DATA);
				}
			}
		}

		break;
	default:
		break;
	}
}



/**
 * �M�~�b�N��UV���Z�b�g����֐�
 * @param[in] Posx x���W�̕`��ʒu
 * @param[in] Posy y���W�̕`��ʒu
 */
void MapGimmick::MapTex_UV_Set(float Posx, float Posy)
{
	int count_x = int((Posx - MAPCHIP_SIZE) / MAPCHIP_SIZE);
	int count_y = int((Posy - MAPCHIP_SIZE) / MAPCHIP_SIZE);


	if (count_x < MAP_LEFT)
	{
		count_x = MAP_LEFT;
	}
	if (count_y < MAP_TOP)
	{
		count_y = MAP_TOP;
	}


	//�`��̈�����߂đ�� �]���Ɉ����ǂ�ł�̂�64�����Ă���
	int ScreenRight = int((Posx + SCREEN_SIZEX + MAPCHIP_SIZE) / MAPCHIP_SIZE);
	int ScreenBottom = int((Posy + SCREEN_SIZEY + MAPCHIP_SIZE) / MAPCHIP_SIZE);

	if (ScreenRight > MAP_WIDTH)
	{
		ScreenRight = MAP_WIDTH;
	}
	if (ScreenBottom > MAP_HEIGHT)
	{
		ScreenBottom = MAP_HEIGHT;
	}


	for (int i = count_y; i <= ScreenBottom; i++)
	{
		for (int j = count_x; j <= ScreenRight; j++)
		{
			switch (m_GimmickData[i][j] / GIMMICK_DATA)
			{
			case SWITCH_RED_01:
				m_pLibrary->MakeVertex(SWITCH_RED_01, m_MapGimmick_Tex[i][j]);
				break;
			case SWITCH_RED_02:
				m_pLibrary->MakeVertex(SWITCH_RED_02, m_MapGimmick_Tex[i][j]);
				break;
			case SWITCH_BLUE_01:
				m_pLibrary->MakeVertex(SWITCH_BLUE_01, m_MapGimmick_Tex[i][j]);
				break;
			case SWITCH_BLUE_02:
				m_pLibrary->MakeVertex(SWITCH_BLUE_02, m_MapGimmick_Tex[i][j]);
				break;
			case SWITCH_YELLOW_01:
				m_pLibrary->MakeVertex(SWITCH_YELLOW_01, m_MapGimmick_Tex[i][j]);
				break;
			case SWITCH_YELLOW_02:
				m_pLibrary->MakeVertex(SWITCH_YELLOW_02, m_MapGimmick_Tex[i][j]);
				break;
			case GATEPOST_01:
				m_pLibrary->MakeVertex(GATEPOST_01, m_MapGimmick_Tex[i][j]);
				break;
			case GATEPOST_02:
				m_pLibrary->MakeVertex(GATEPOST_02, m_MapGimmick_Tex[i][j]);
				m_pLibrary->UVReversal(m_MapGimmick_Tex[i][j], LEFT_AND_RIGHT);
				break;
			case GATE_01:
				m_pLibrary->MakeVertex(GATE_01, m_MapGimmick_Tex[i][j]);
				break;
			case GATE_02:
				m_pLibrary->MakeVertex(GATE_02, m_MapGimmick_Tex[i][j]);
				m_pLibrary->UVReversal(m_MapGimmick_Tex[i][j], LEFT_AND_RIGHT);
				break;
			case GATEPOST_PORTRAIT_01:
				m_pLibrary->MakeVertex(GATEPOST_PORTRAIT_01, m_MapGimmick_Tex[i][j]);
				break;
			case GATEPOST_PORTRAIT_02:
				m_pLibrary->MakeVertex(GATEPOST_PORTRAIT_02, m_MapGimmick_Tex[i][j]);
				break;
			case GATE_PORTRAIT_01:
				m_pLibrary->MakeVertex(GATE_PORTRAIT_01, m_MapGimmick_Tex[i][j]);
				break;
			case GATE_PORTRAIT_02:
				m_pLibrary->MakeVertex(GATE_PORTRAIT_02, m_MapGimmick_Tex[i][j]);
				break;
			case HOLE_01:
				m_pLibrary->MakeVertex(HOLE_01, m_MapGimmick_Tex[i][j]);
				break;
			case HOLE_02:
				m_pLibrary->MakeVertex(HOLE_02, m_MapGimmick_Tex[i][j]);
				break;
			case GRASS_KNOT:
				m_pLibrary->MakeVertex(GRASS_KNOT, m_MapGimmick_Tex[i][j]);
				break;
			case GRASS_KNOT_PORTRAIT:
				m_pLibrary->MakeVertex(GRASS_KNOT_PORTRAIT, m_MapGimmick_Tex[i][j]);
				break;
			case APPLE:
				m_pLibrary->MakeVertex(APPLE, m_MapGimmick_Tex[i][j]);
				break;
			default:
				for (int x = 0; x < VERTEXNUM; x++)
				{
					m_MapGimmick_Tex[i][j][x].color = DEFAULT_COLOR;
					m_MapGimmick_Tex[i][j][x].rhw = DEFAULT_RHW;
					m_MapGimmick_Tex[i][j][x].z = DEFAULT_Z;
					m_MapGimmick_Tex[i][j][x].tu = DEFAULT_TU;
					m_MapGimmick_Tex[i][j][x].tv = DEFAULT_TV;
				}
				break;
			}
		}
	}
}


/**
 * �M�~�b�N��XY���Z�b�g����֐�
 * @param[in] Posx x���W�̕`��ʒu
 * @param[in] Posy y���W�̕`��ʒu
 */
void MapGimmick::MapTex_XY_Set(float Posx, float Posy)
{
	int count_x = int((Posx - MAPCHIP_SIZE) / MAPCHIP_SIZE);
	int count_y = int((Posy - MAPCHIP_SIZE) / MAPCHIP_SIZE);


	if (count_x < 1)
	{
		count_x = 1;
	}
	if (count_y < 1)
	{
		count_y = 1;
	}


	//�`��̈�����߂đ�� �]���Ɉ����ǂ�ł�̂�64�����Ă���
	int ScreenRight = int((Posx + SCREEN_SIZEX + MAPCHIP_SIZE) / MAPCHIP_SIZE);
	int ScreenBottom = int((Posy + SCREEN_SIZEY + MAPCHIP_SIZE) / MAPCHIP_SIZE);

	if (ScreenRight > MAP_WIDTH)
	{
		ScreenRight = MAP_WIDTH;
	}
	if (ScreenBottom > MAP_HEIGHT)
	{
		ScreenBottom = MAP_HEIGHT;
	}


	for (int i = count_y; i <= ScreenBottom; i++)
	{
		for (int j = count_x; j <= ScreenRight; j++)
		{
			{
				//�����蔻��p��XY������
				m_MapGimmick_Pos[i - 1][j - 1].x = (float)(MAPCHIP_SIZE * j) - MAPCHIP_DEFAULT_POSX;
				m_MapGimmick_Pos[i - 1][j - 1].y = (float)(MAPCHIP_SIZE * i) - MAPCHIP_DEFAULT_POSY;
				m_MapGimmick_Pos[i - 1][j - 1].w = (float)MAPCHIP_SIZE;
				m_MapGimmick_Pos[i - 1][j - 1].h = (float)MAPCHIP_SIZE;
				m_MapGimmick_Pos[i - 1][j - 1].x -= Posx;
				m_MapGimmick_Pos[i - 1][j - 1].y -= Posy;

				m_pLibrary->xySet(m_MapGimmick_Pos[i - 1][j - 1], m_MapGimmick_Tex[i - 1][j - 1]);
			}
		}
	}
}


/**
 * �������邩���`�F�b�N����֐�
 * @param[in] x �`�F�b�N����x���W
 * @param[in] y �`�F�b�N����y���W
 * @return �������������ǂ���
 */
bool MapGimmick::HoleCheck(float x, float y)
{
	int arrayx = ARRAY_DEFAULT_INIT, arrayy = ARRAY_DEFAULT_INIT;
	arrayx = static_cast<int>(x / MAPCHIP_SIZE);
	arrayy = static_cast<int>(y / MAPCHIP_SIZE);

	if (m_GimmickData[arrayy][arrayx] / GIMMICK_DATA == HOLE_01)
	{
		m_GimmickData[arrayy][arrayx] = HOLE_02 * GIMMICK_DATA;
		return true;
	}

	return false;

}


/**
 * �ؔ����������������邩���`�F�b�N����֐�
 * @param[in] x �`�F�b�N����x���W
 * @param[in] y �`�F�b�N����y���W
 * @return �ؔ����������������������ǂ���
 */
bool MapGimmick::WoodBoxHoleCheck(float x, float y)
{
	int arrayx = ARRAY_DEFAULT_INIT, arrayy = ARRAY_DEFAULT_INIT;
	arrayx = static_cast<int>(x / MAPCHIP_SIZE);
	arrayy = static_cast<int>(y / MAPCHIP_SIZE);

	if (m_GimmickData[arrayy][arrayx] / GIMMICK_DATA == HOLE_02)
	{
		m_GimmickData[arrayy][arrayx] = HOLE_01 * GIMMICK_DATA;
		return true;

	}

	return false;

}


/**
 * ������(�c����)�����邩���`�F�b�N����֐�
 * @param[in] x �`�F�b�N����x���W
 * @param[in] y �`�F�b�N����y���W
 * @return ���������ǂ���
 */
bool MapGimmick::GrassPortRaitCheck(float x, float y)
{
	int arrayx = ARRAY_DEFAULT_INIT, arrayy = ARRAY_DEFAULT_INIT;
	arrayx = static_cast<int>(x / MAPCHIP_SIZE);
	arrayy = static_cast<int>(y / MAPCHIP_SIZE);

	if (m_GimmickData[arrayy][arrayx] / GIMMICK_DATA == GRASS_KNOT_PORTRAIT)
	{
		return true;
	}

	return false;

}


/**
 * ������(������)�����邩���`�F�b�N����֐�
 * @param[in] x �`�F�b�N����x���W
 * @param[in] y �`�F�b�N����y���W
 * @return ���������ǂ���
 */
bool MapGimmick::GrassCheck(float x, float y)
{
	int arrayx = ARRAY_DEFAULT_INIT, arrayy = ARRAY_DEFAULT_INIT;
	arrayx = static_cast<int>(x / MAPCHIP_SIZE);
	arrayy = static_cast<int>(y / MAPCHIP_SIZE);

	if (m_GimmickData[arrayy][arrayx] / GIMMICK_DATA == GRASS_KNOT)
	{
		return true;
	}

	return false;

}

/**
 * �����S�����邩���`�F�b�N����֐�
 * @param[in] x �`�F�b�N����x���W
 * @param[in] y �`�F�b�N����y���W
 * @return ���������ǂ���
 */
bool MapGimmick::AppleCheck(float x, float y)
{
	int arrayx = ARRAY_DEFAULT_INIT, arrayy = ARRAY_DEFAULT_INIT;
	arrayx = static_cast<int>(x / MAPCHIP_SIZE);
	arrayy = static_cast<int>(y / MAPCHIP_SIZE);

	if (m_GimmickData[arrayy][arrayx] / GIMMICK_DATA == APPLE)
	{
		m_GimmickData[arrayy][arrayx] = MAP_GIMMICK_NONE;
		return true;
	}

	return false;

}

/**
 * �N���A�ꏊ�����邩���`�F�b�N����֐�
 * @param[in] x �`�F�b�N����x���W
 * @param[in] y �`�F�b�N����y���W
 * @return ���������ǂ���
 */
bool MapGimmick::ClearCheck(float x, float y)
{
	int arrayx = ARRAY_DEFAULT_INIT, arrayy = ARRAY_DEFAULT_INIT;
	arrayx = static_cast<int>(x / MAPCHIP_SIZE);
	arrayy = static_cast<int>(y / MAPCHIP_SIZE);

	if (m_GimmickData[arrayy][arrayx] / 10000 == GOALZONE)
	{
		return true;
	}
	return false;
}

void MapGimmick::MapStartPos(float* posx, float* posy)
{
	for (int y = 0; y < MAP_HEIGHT; y++)
	{
		for (int x = 0; x < MAP_WIDTH; x++)
		{
			if (m_GimmickData[y][x] / 10000 == STARTZONE)
			{
				*posx = m_MapGimmick_Pos[y][x].x;
				*posy = m_MapGimmick_Pos[y][x].y;
				return;
			}
		}
	}
}