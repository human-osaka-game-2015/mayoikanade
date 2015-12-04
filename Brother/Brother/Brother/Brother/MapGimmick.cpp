#include"MapGimmick.h"
#include "Library.h"

MapGimmick::MapGimmick(Library* pLibrary) :m_pLibrary(pLibrary)
{

}

MapGimmick::~MapGimmick()
{

}

bool MapGimmick::CsvRead(const char* filename)
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
			fscanf_s(fp, "%d,", &m_GimmickData[i][j], _countof(m_GimmickData));
		}
	}
	fclose(fp);

	return true;
}

void MapGimmick::Control()
{

}

void MapGimmick::Draw()
{

}

int MapGimmick::GimmickCheck(float x, float y)
{
	int arrayx = 0, arrayy = 0;
	arrayx = int(x / 64);
	arrayy = int(y / 64);

	return m_GimmickData[arrayy][arrayx];
}
