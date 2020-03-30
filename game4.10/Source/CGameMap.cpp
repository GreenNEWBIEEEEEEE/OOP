#include <mmsystem.h>
<<<<<<< HEAD
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <regex>
#include <ddraw.h>
#include "gamelib.h"
#include "CMapManager.h"
#include "CMapInfo.h"
#include "CMapEvent.h"
#include "CPlayer.h"



namespace game_framework {
	CGameMap::CGameMap(string mapinfo_path) : row(0), col(0)
	{
		CreateMapInfos(mapinfo_path);
		sx = sy = 0;
		gndW = 80; gndH = 60;
=======
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

>>>>>>> e2e1e32b2e3fbb9303805f93de1773125d6ea93e
		gndWater01.SetDelayCount(15);
	}



	CGameMap::~CGameMap()
	{
		for (int i = 0; i < row; ++i)
			delete[] map[i];
		delete[] map;
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
		gndHouseFloor01.LoadBitmap(IDB_HOUSE_FLOOR_02);	
		//
		gndHouseWall01.LoadBitmap(IDB_House_Wall_01);
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
		for (int i = 0; i < row; ++i)
		{
			for (int j = 0; j < col; ++j)
			{
				int x = (j * gndW) - sx, y = (i * gndH) - sy;
<<<<<<< HEAD
				switch (map[i][j].GetElemID())
=======
				int elementID = map[i][j].GetElementID();
				switch (elementID)
>>>>>>> e2e1e32b2e3fbb9303805f93de1773125d6ea93e
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
				case 4:
					gndHouseFloor01.SetTopLeft(x, y);
					gndHouseFloor01.ShowBitmap();
					break;
				case -1:
					gndWater01.SetTopLeft(x, y);
					gndWater01.OnMove();
					gndWater01.OnShow();
					break;
				case -2:
					gndHouseWall01.SetTopLeft(x, y);
					gndHouseWall01.ShowBitmap();
					break;
				default:
					break;
				}
			}
		}
	}

	bool CGameMap::IsEmpty(int x, int y) const
	{
		int gx = x / gndW, gy = y / gndH;
<<<<<<< HEAD
		return (map[gy][gx]).IsEmpty();
=======
		int elementID = map[gy][gx].GetElementID();
		return elementID > 0;
>>>>>>> e2e1e32b2e3fbb9303805f93de1773125d6ea93e
	}


	// 觸發事件
	// key
	// x, y : 傳入player的位置
	// 地圖管理器
	void CGameMap::triggerMapEvents(UINT key, CPlayer *p, CMapManager *mm, CGameDialog *gd)
	{
		int px = p->GetX(), py = p->GetY() + 90; // MAYBE FIXME
		int gx = px / gndW, gy = py / gndH; // 求出格座標
		map[gy][gx].triggerEventByKeyCode(key, p, mm, gd);
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

<<<<<<< HEAD
	void CGameMap::CreateMapInfos(string& mapinfo_path)
	{
		ifstream is;
		is.open(mapinfo_path);
		if (is)
		{
			// 先讀取row跟col才能初始化map的大小
			string line;
			is >> line; row = stoi(line);
			is >> line; col = stoi(line);

			// 初始化map空間大小
			map = new CMapInfo*[row];
			for (int i = 0; i < row; ++i) map[i] = new CMapInfo[col];
			
			// 分解並設定資料到每個格子
			int i = -1; // row 的 index
			while (i < row && getline(is, line))
			{
				int j = 0; // col 的 index

				// 再從資料行(line)分解成一個個的cell
				stringstream ss(line); string cell;
				while (j < col && ss >> cell)
				{
					// 處理cell中的分隔符號 取代為空
					CString csCell(cell.c_str());
					csCell.Replace('|', ' ');
					cell = (LPCTSTR)csCell;

					// cell 繼續分解成各項資料 elemID eventID
					stringstream sss(cell); string data;
					sss >> data;				     // 先導出elemID
					map[i][j].SetElemID(stoi(data)); // 設定每格elemID
					
					// 加入eventID
					
					while (sss >> data) map[i][j].AddEvent(stoi(data));
					j++;
				}
				i++;
			}
		}
		is.close();
	}
}
=======
	void CGameMap::Trigger(int x, int y)
	{

		int gx = x / gndW, gy = y / gndH;
		if (map[gx][gy].IsTriggerPoint())
		{
			
		}
	}
}
>>>>>>> e2e1e32b2e3fbb9303805f93de1773125d6ea93e
