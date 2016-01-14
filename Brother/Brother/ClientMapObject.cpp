#include"ClientMapObject.h"
#include "ClientGameScene.h"
#include "Library.h"



ClientMapObject::ClientMapObject(Library* pLibrary) :m_pLibrary(pLibrary)
{
	CsvRead("Stage1_Object.csv");
}

ClientMapObject::~ClientMapObject()
{

}

bool ClientMapObject::CsvRead(const char* filename)
{
	FILE*  fp = NULL;
	fopen_s(&fp, filename, "r");

	if (fp == NULL)
	{
		return false;
	}

	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			fscanf_s(fp, "%d,", &m_ObjectData[i][j], _countof(m_ObjectData));
		}
	}
	fclose(fp);

	return true;
}


void ClientMapObject::MapTex_UV_Set(float Posx, float Posy)
{
	int count_x = int((Posx - 64) / MAPTIP_SIZE);
	int count_y = int((Posy - 64) / MAPTIP_SIZE);


	if (count_x < 0)
	{
		count_x = 0;
	}
	if (count_y < 0)
	{
		count_y = 0;
	}

	//•`‰æ—Ìˆæ‚ð‹‚ß‚Ä‘ã“ü —]•ª‚Éˆê‚Âæ‚à“Ç‚ñ‚Å‚é‚Ì‚Å64‘«‚µ‚Ä‚¢‚é
	int ScreenRight = int((Posx + SCREEN_SIZEX + 64) / MAPTIP_SIZE);
	int ScreenBottom = int((Posy + SCREEN_SIZEY + 64) / MAPTIP_SIZE);

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
			default:
				for (int x = 0; x < VERTEXNUM; x++)
				{
					m_MapObject_Tex[i][j][x].color = DEFAULTCOLOR;
					m_MapObject_Tex[i][j][x].rhw = DEFAULTRHW;
					m_MapObject_Tex[i][j][x].z = DEFAULTZ;
					m_MapObject_Tex[i][j][x].tu = 0;
					m_MapObject_Tex[i][j][x].tv = 0;
				}
				break;
			}
		}
	}
}


int ClientMapObject::ObjectCheck(float x, float y)
{
	int arrayx = 0, arrayy = 0;

	arrayx = int(x / 64);
	arrayy = int(y / 64);

	return m_ObjectData[arrayy][arrayx];
}


void ClientMapObject::MapTex_XY_Set(float Posx, float Posy)
{
	int count_x = static_cast<int>((Posx - 64) / MAPTIP_SIZE);
	int count_y = static_cast<int>((Posy - 64) / MAPTIP_SIZE);

	if (count_x < 1)
	{
		count_x = 1;
	}
	if (count_y < 1)
	{
		count_y = 1;
	}

	//•`‰æ—Ìˆæ‚ð‹‚ß‚Ä‘ã“ü —]•ª‚Éˆê‚Âæ‚à“Ç‚ñ‚Å‚é‚Ì‚Å64‘«‚µ‚Ä‚¢‚é
	int ScreenRight  = static_cast<int>((Posx + SCREEN_SIZEX + 64) / MAPTIP_SIZE);
	int ScreenBottom = static_cast<int>((Posy + SCREEN_SIZEY + 64) / MAPTIP_SIZE);

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
			//“–‚½‚è”»’è—p‚ÌXY‚ð“ü‚ê‚é
			m_MapObject_Pos[i - 1][j - 1].x  = static_cast<float>((MAPTIP_SIZE * j) - MAPTIP_DEFAULT_POSX);
			m_MapObject_Pos[i - 1][j - 1].y  = static_cast<float>((MAPTIP_SIZE * i) - MAPTIP_DEFAULT_POSY);
			m_MapObject_Pos[i - 1][j - 1].w  = static_cast<float>(MAPTIP_SIZE);
			m_MapObject_Pos[i - 1][j - 1].h  = static_cast<float>(MAPTIP_SIZE);
			m_MapObject_Pos[i - 1][j - 1].x -= Posx;
			m_MapObject_Pos[i - 1][j - 1].y -= Posy;

			m_pLibrary->xySet(m_MapObject_Pos[i - 1][j - 1], m_MapObject_Tex[i - 1][j - 1]);
		}
	}
}


void ClientMapObject::Control()
{

}


void ClientMapObject::Draw(float DrawPosX, float DrawPosY)
{
	int count_x = int((DrawPosX - 64) / MAPTIP_SIZE);
	int count_y = int((DrawPosY - 64) / MAPTIP_SIZE);

	if (count_x < 0)
	{
		count_x = 0;
	}
	if (count_y < 0)
	{
		count_y = 0;
	}

	//•`‰æ—Ìˆæ‚ð‹‚ß‚Ä‘ã“ü —]•ª‚Éˆê‚Âæ‚à“Ç‚ñ‚Å‚é‚Ì‚Å64‘«‚µ‚Ä‚¢‚é
	int ScreenRight  = static_cast<int>((DrawPosX + SCREEN_SIZEX + 64) / MAPTIP_SIZE);
	int ScreenBottom = static_cast<int>((DrawPosY + SCREEN_SIZEY + 64) / MAPTIP_SIZE);

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


bool ClientMapObject::WoodBoxCheck(float x, float y)
{
	int arrayx = 0, arrayy = 0;

	arrayx = int(x / 64);
	arrayy = int(y / 64);

	if (m_ObjectData[arrayy][arrayx] == WOODBOX)
	{
		m_ObjectData[arrayy][arrayx] = 0;
		return true;
	}

	return false;
}


bool ClientMapObject::WoodBoxSet(float x, float y)
{
	int arrayx = 0, arrayy = 0;

	arrayx = int(x / 64);
	arrayy = int(y / 64);

	if (m_ObjectData[arrayy][arrayx] == 0)
	{
		m_ObjectData[arrayy][arrayx] = WOODBOX;
		return true;
	}

	return false;
}




