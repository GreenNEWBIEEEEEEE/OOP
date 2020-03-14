#include "stdafx.h"
#include "resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include "CGameMap.h"


namespace game_framework {
	CGameMap::CGameMap() : COL(9), ROW(8)
	{
		int map_init[8][9] = {
			{1, -1, 1, 1, 1, 1, 1, 1, 1},
			{1, -1, 1, 1, 1, 1, 1, 1, 1},
			{1, -1, -1, 1, 1, 1, 1, 1, 1},
			{1, 1, -1, 1, 1, 1, 1, 1, 1},
			{1, 1, 3, 1, 1, 2, 2, 2, 1},
			{1, 1, -1, 1, 1, 2, 2, 2, 1},
			{1, 1, -1, 1, 1, 2, 2, 2, 1},
			{1, 1, -1, 1, 1, 1, 1, 1, 1},
		};

		sx = sy = 10;
		gndW = 80; gndH = 60;
		for (int i = 0; i < ROW; ++i)
		{
			map[i] = new int[COL];
			for (int j = 0; j < COL; ++j)
				map[i][j] = map_init[i][j];
		}
		gndWater01.SetDelayCount(15);
	}

	CGameMap::~CGameMap()
	{
		for (int i = 0; i < ROW; ++i)
			delete [] map[i];
		delete [] map;
		map = nullptr;
	}

	void CGameMap::LoadBitmap()
	{
		//
		gndGrass01.LoadBitmap(IDB_GND_GRASS01);
		//
		gndDirt01.LoadBitmap(IDB_GND_DIRT01);
		//
		gndBridge01.LoadBitmap(IDB_GND_BRIDGE01);
		//
		gndWater01.AddBitmap(IDB_GND_WATER01_ANI01);
		gndWater01.AddBitmap(IDB_GND_WATER01_ANI02);
		gndWater01.AddBitmap(IDB_GND_WATER01_ANI03);
		gndWater01.AddBitmap(IDB_GND_WATER01_ANI04);
		gndWater01.AddBitmap(IDB_GND_WATER01_ANI05);
		gndWater01.AddBitmap(IDB_GND_WATER01_ANI05);
		gndWater01.AddBitmap(IDB_GND_WATER01_ANI04);
		gndWater01.AddBitmap(IDB_GND_WATER01_ANI03);
		gndWater01.AddBitmap(IDB_GND_WATER01_ANI02);
		gndWater01.AddBitmap(IDB_GND_WATER01_ANI01);
	}

	void CGameMap::OnShow()
	{
		// 先畫地板圖
		for (int i = 0; i < ROW; ++i)
		{
			for (int j = 0; j < COL; ++j)
			{
				int x = (j * gndW) - sx, y = (i * gndH) - sy;
				switch (map[i][j])
				{
				case 1:
					gndGrass01.SetTopLeft(x, y);
					gndGrass01.ShowBitmap();
					break;
				case 2:
					gndDirt01.SetTopLeft(x, y);
					gndDirt01.ShowBitmap();
					break;
				case 3:
					gndBridge01.SetTopLeft(x, y);
					gndBridge01.ShowBitmap();
					break;
				case -1:
					gndWater01.SetTopLeft(x, y);
					gndWater01.OnMove();
					gndWater01.OnShow();
					break;
				default:
					ASSERT(0);
					break;
				}
			}
		}

		// 再畫建築物
	}

	bool CGameMap::IsEmpty(int x, int y) const
	{
		int gx = x / gndW, gy = y / gndH;
		return map[gy][gx] > 0;
	}


	int CGameMap::GetSX() const
	{
		return sx;
	}
	int CGameMap::GetSY() const
	{
		return sy;
	}
	void CGameMap::SetSX(int nx)
	{
		sx = nx;
	}
	void CGameMap::SetSY(int ny)
	{
		sy = ny;
	}
	
	void CGameMap::SetSXSY(int nx, int ny)
	{
		sx = nx; sy = ny;
	}
	int CGameMap::ScreenX(int x) const
	{
		return x - sx;
	}
	int CGameMap::ScreenY(int y) const
	{
		return y - sy;
	}
}