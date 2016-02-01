#include "MapObject.h"
#include "ServerGameScene.h"
#include "Library.h"


/**
 * MapObject�N���X�̃R���X�g���N�^
 * @param[in] pLibrary ���C�u�����N���X�̃|�C���^
 */
MapObject::MapObject(Library* pLibrary) :
m_pLibrary(pLibrary)
{
	CsvRead("Stage1_Object.csv");
}

/**
 * MapObject�N���X�̃f�X�g���N�^
 */
MapObject::~MapObject()
{

}

/**
 * CSV��ǂݍ��ފ֐�
 * @param[in] filename �ǂݍ��ރt�@�C���̖��O
 */
bool MapObject::CsvRead(const char* filename)
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
			fscanf_s(fp, "%d,", &m_ObjectData[i][j], _countof(m_ObjectData));
		}
	}
	fclose(fp);

	return true;
}

/**
 * �I�u�W�F�N�g��UV���Z�b�g����֐�
 * @param[in] Posx	x�`��ʒu
 * @param[in] Posy	y�`��ʒu 
 */
void MapObject::MapTex_UV_Set(float Posx, float Posy)
{
	int count_x = static_cast<int>((Posx - MAPCHIP_SIZE) / MAPCHIP_SIZE);
	int count_y = static_cast<int>((Posy - MAPCHIP_SIZE) / MAPCHIP_SIZE);


	if (count_x < MAP_TOP)
	{
		count_x = MAP_TOP;
	}
	if (count_y < MAP_LEFT)
	{
		count_y = MAP_LEFT;
	}


	//�`��̈�����߂đ�� �]���Ɉ����ǂ�ł�̂�64�����Ă���
	int ScreenRight  = static_cast<int>((Posx + SCREEN_SIZEX + MAPCHIP_SIZE) / MAPCHIP_SIZE);
	int ScreenBottom = static_cast<int>((Posy + SCREEN_SIZEY + MAPCHIP_SIZE) / MAPCHIP_SIZE);

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
			switch (m_ObjectData[i][j])
			{
			case WOOD_01:
				m_pLibrary->MakeVertex(WOOD_01, m_MapObject_Tex[i][j]);
				break;

			case WOOD_02:
				m_pLibrary->MakeVertex(WOOD_02, m_MapObject_Tex[i][j]);
				break;

			case WOOD_03:
				m_pLibrary->MakeVertex(WOOD_03, m_MapObject_Tex[i][j]);
				break;

			case WOOD_04:
				m_pLibrary->MakeVertex(WOOD_04, m_MapObject_Tex[i][j]);
				break;
			case WOODBOX:
				m_pLibrary->MakeVertex(WOODBOX, m_MapObject_Tex[i][j]);

				break;
			case WOOD_YELLOW_01:
				m_pLibrary->MakeVertex(WOOD_YELLOW_01, m_MapObject_Tex[i][j]);
				break;
			case WOOD_YELLOW_02:
				m_pLibrary->MakeVertex(WOOD_YELLOW_02, m_MapObject_Tex[i][j]);
				break;
			case WOOD_YELLOW_03:
				m_pLibrary->MakeVertex(WOOD_YELLOW_03, m_MapObject_Tex[i][j]);
				break;
			case WOOD_YELLOW_04:
				m_pLibrary->MakeVertex(WOOD_YELLOW_04, m_MapObject_Tex[i][j]);
				break;
			default :
				for (int x = FOR_DEFAULT_INIT; x < VERTEXNUM; x++)
				{
					m_MapObject_Tex[i][j][x].color = DEFAULT_COLOR;
					m_MapObject_Tex[i][j][x].rhw = DEFAULT_RHW;
					m_MapObject_Tex[i][j][x].z = DEFAULT_Z;
					m_MapObject_Tex[i][j][x].tu = DEFAULT_TU;
					m_MapObject_Tex[i][j][x].tv = DEFAULT_TV;
				}
				break;
			}
		}
	}
}




/**
 * �I�u�W�F�N�g��XY���Z�b�g����֐�
 * @param[in] Posx	x�`��ʒu
 * @param[in] Posy	y�`��ʒu
 */
void MapObject::MapTex_XY_Set(float Posx, float Posy)
{
	int count_x = static_cast<int>((Posx - MAPCHIP_SIZE) / MAPCHIP_SIZE);
	int count_y = static_cast<int>((Posy - MAPCHIP_SIZE) / MAPCHIP_SIZE);


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
			//�����蔻��p��XY������
			m_MapObject_Pos[i - 1][j - 1].x = (float)(MAPCHIP_SIZE * j) - MAPCHIP_DEFAULT_POSX;
			m_MapObject_Pos[i - 1][j - 1].y = (float)(MAPCHIP_SIZE * i) - MAPCHIP_DEFAULT_POSY;
			m_MapObject_Pos[i - 1][j - 1].w = (float)MAPCHIP_SIZE;
			m_MapObject_Pos[i - 1][j - 1].h = (float)MAPCHIP_SIZE;
			m_MapObject_Pos[i - 1][j - 1].x -= Posx;
			m_MapObject_Pos[i - 1][j - 1].y -= Posy;

			m_pLibrary->xySet(m_MapObject_Pos[i - 1][j - 1], m_MapObject_Tex[i - 1][j - 1]);
		}
	}
}


/**
 * �I�u�W�F�N�g�̕`��֐�
 * @param[in] DrawPosX x���W�̕`��ʒu
 * @param[in] DrawPosY y���W�̕`��ʒu
 */
void MapObject::Draw(float DrawPosX, float DrawPosY)
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
	int ScreenRight = int((DrawPosX + SCREEN_SIZEX + MAPCHIP_SIZE) / MAPCHIP_SIZE);
	int ScreenBottom = int((DrawPosY + SCREEN_SIZEY + MAPCHIP_SIZE) / MAPCHIP_SIZE);

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
			m_pLibrary->DrawTexture(TEX_GAME, m_MapObject_Tex[i][j]);
		}
	}
}


/**
* �I�u�W�F�N�g���`�F�b�N����֐�
* @param[in] x �`�F�b�N����x���W
* @param[in] y �`�F�b�N����y���W
* @return �I�u�W�F�N�g�f�[�^
*/
int MapObject::ObjectCheck(float x, float y)
{
	int arrayx = ARRAY_DEFAULT_INIT, arrayy = ARRAY_DEFAULT_INIT;

	arrayx = static_cast<int>(x / MAPCHIP_SIZE);
	arrayy = static_cast<int>(y / MAPCHIP_SIZE);


	return m_ObjectData[arrayy][arrayx];
}


/**
 * �ؔ������邩���`�F�b�N����֐�
 * @param[in] x �`�F�b�N����x���W
 * @param[in] y �`�F�b�N����y���W
 * @return ���������ǂ���
 */
bool MapObject::WoodBoxCheck(float x, float y)
{
	int arrayx = ARRAY_DEFAULT_INIT, arrayy = ARRAY_DEFAULT_INIT;

	arrayx = static_cast<int>(x / MAPCHIP_SIZE);
	arrayy = static_cast<int>(y / MAPCHIP_SIZE);


	if (m_ObjectData[arrayy][arrayx] == WOODBOX)
	{
		m_ObjectData[arrayy][arrayx] = OBJECT_NONE;
		return true;
	}


	return false;
}


/**
 * �ؔ����Z�b�g����֐�
 * @param[in] x �Z�b�g����x���W
 * @param[in] y �Z�b�g����y���W
 * @return �����������ǂ���
 */
bool MapObject::WoodBoxSet(float x, float y)
{
	int arrayx = ARRAY_DEFAULT_INIT, arrayy = ARRAY_DEFAULT_INIT;

	arrayx = static_cast<int>(x / MAPCHIP_SIZE);
	arrayy = static_cast<int>(y / MAPCHIP_SIZE);


	if (m_ObjectData[arrayy][arrayx] == OBJECT_NONE)
	{
		m_ObjectData[arrayy][arrayx] = WOODBOX;
		return true;
	}

	return false;
}