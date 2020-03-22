#include <mmsystem.h>
#include <vector>
#include <string>
#include <fstream>
#include <ddraw.h>
#include "gamelib.h"
#include "CGameMap.h"
#include "CMapInfo.h"
#include "stdafx.h"
#include "resource.h"
namespace game_framework {

	CGameMap::CGameMap(string filePath) : COL(9), ROW(8)
	{
		fstream mapFile;
		string data = "";

		mapFile.open(filePath, ios::in);
		getline(mapFile, data);
		ROW = stoi(data);

		getline(mapFile, data);
		COL = stoi(data);
		

		for (int i = 0; i < ROW; i++)
		{
			getline(mapFile, data);
			
			for (int j = 0; j < COL; j++)
			{
				vector<string> grid = SplitString(data, ", ");

				for (vector<string>::iterator k = grid.begin(); k != grid.end(); k++)
				{
					vector<string> mapInfo = SplitString(*k, " ");
					map[i][j].SetElementID(stoi(mapInfo[0]));
					map[i][j].AddEvent(mapInfo);
				}
			}
		}

		sx = sy = 10;
		gndW = 80; gndH = 60;

		gndWater01.SetDelayCount(15);
	}



	CGameMap::~CGameMap()
	{
		for (int i = 0; i < ROW; ++i)
			delete [] map[i];
		delete [] map;
		map = nullptr;
	}

	vector<string> CGameMap::SplitString(string& data, string delimiter)
	{
		vector<string> mapInfo;
		size_t pos = 0;
		string token = "";
		while ((pos = data.find(delimiter)) != string::npos)
		{
			token = data.substr(0, pos);
			mapInfo.push_back(token);
			data.erase(0, pos + delimiter.length());
		}
		return mapInfo;
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
				int elementID = map[i][j].GetElementID();
				switch (elementID)
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
		int elementID = map[gy][gx].GetElementID();
		return elementID > 0;
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

	void CGameMap::Trigger(int x, int y)
	{

		int gx = x / gndW, gy = y / gndH;
		if (map[gx][gy].IsTriggerPoint())
		{
			
		}
	}
}
