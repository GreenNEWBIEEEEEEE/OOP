#include "stdafx.h"
#include "resource.h"
#include <mmsystem.h>
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
		gndW = 64; gndH = 53;
		//gndWater01.SetDelayCount(15);
	}

	CGameMap::~CGameMap()
	{
		for (int i = 0; i < row; ++i)
			delete[] map[i];
		delete[] map;
		map = nullptr;
	}

	void CGameMap::LoadBitmap()
	{
		sand.LoadBitmap(IDB_Sand);
		plantSoil.LoadBitmap(IDB_PlantSoil);
		grass.LoadBitmap(IDB_Grass);
		soil.LoadBitmap(IDB_Soil);

		fence.LoadBitmap(IDB_Fence);
		bush.LoadBitmap(IDB_Bush);
		stone.LoadBitmap(IDB_Stone);
		wood.LoadBitmap(IDB_Wood);
		river.AddBitmap(IDB_River01);
		river.AddBitmap(IDB_River02);
		river.AddBitmap(IDB_River03);
		river.AddBitmap(IDB_River04);
		river.AddBitmap(IDB_River05);
		houseOutside_01.LoadBitmap(IDB_HouseOutside00);
		houseOutside_02.LoadBitmap(IDB_HouseOutside01);
		houseOutside_03.LoadBitmap(IDB_HouseOutside02);
		houseOutside_04.LoadBitmap(IDB_HouseOutside03);
		houseOutside_05.LoadBitmap(IDB_HouseOutside04);
		houseOutside_06.LoadBitmap(IDB_HouseOutside05);
		houseOutside_07.LoadBitmap(IDB_HouseOutside06);
		houseOutside_08.LoadBitmap(IDB_HouseOutside07);
		houseOutside_09.LoadBitmap(IDB_HouseOutside08);
		houseOutside_10.LoadBitmap(IDB_HouseOutside09);
		houseOutside_11.LoadBitmap(IDB_HouseOutside10);
		houseOutside_12.LoadBitmap(IDB_HouseOutside11);
		houseOutside_13.LoadBitmap(IDB_HouseOutside12);
		houseOutside_14.LoadBitmap(IDB_HouseOutside13);
		houseOutside_15.LoadBitmap(IDB_HouseOutside14);
		noticeBoard.LoadBitmap(IDB_NoticeBoard);
		houseFloor.LoadBitmap(IDB_HouseFloor);
		houseWall.LoadBitmap(IDB_HouseWall);
		houseWall_02.LoadBitmap(IDB_HouseWall02);
		houseWall_03.LoadBitmap(IDB_HouseWall03);

	}

	void CGameMap::OnShow()
	{
		// 先畫地板圖
		for (int i = 0; i < row; ++i)
		{
			for (int j = 0; j < col; ++j)
			{
				int x = (j * gndW) - sx, y = (i * gndH) - sy;
				switch (map[i][j].GetElemID())
				{
				case 0:
					sand.SetTopLeft(x, y);
					sand.ShowBitmap();
					break;
				case 1:
					plantSoil.SetTopLeft(x, y);
					plantSoil.ShowBitmap();
					break;
				case 2:
					grass.SetTopLeft(x, y);
					grass.ShowBitmap();
					break;
				case 3:
					soil.SetTopLeft(x, y);
					soil.ShowBitmap();
					break;
				case 4:
					houseFloor.SetTopLeft(x, y);
					houseFloor.ShowBitmap();
					break;
				case -1:
					fence.SetTopLeft(x, y);
					fence.ShowBitmap();
					break;
				case -2:
					river.SetTopLeft(x, y);
					river.OnMove();
					river.OnShow();
					break;
				case -3:
					bush.SetTopLeft(x, y);
					bush.ShowBitmap();
					break;
				case -4:
					stone.SetTopLeft(x, y);
					stone.ShowBitmap();
					break;
				case -5:
					wood.SetTopLeft(x, y);
					wood.ShowBitmap();
					break;
				case -6:
					houseOutside_01.SetTopLeft(x, y);
					houseOutside_01.ShowBitmap();
					break;
				case -7:
					houseOutside_02.SetTopLeft(x, y);
					houseOutside_02.ShowBitmap();
					break;
				case -8:
					houseOutside_03.SetTopLeft(x, y);
					houseOutside_03.ShowBitmap();
					break;
				case -9:
					houseOutside_04.SetTopLeft(x, y);
					houseOutside_04.ShowBitmap();
					break;
				case -10:
					houseOutside_05.SetTopLeft(x, y);
					houseOutside_05.ShowBitmap();
					break;
				case -11:
					houseOutside_06.SetTopLeft(x, y);
					houseOutside_06.ShowBitmap();
					break;
				case -12:
					houseOutside_07.SetTopLeft(x, y);
					houseOutside_07.ShowBitmap();
					break;
				case -13:
					houseOutside_08.SetTopLeft(x, y);
					houseOutside_08.ShowBitmap();
					break;
				case -14:
					houseOutside_09.SetTopLeft(x, y);
					houseOutside_09.ShowBitmap();
					break;
				case -15:
					houseOutside_10.SetTopLeft(x, y);
					houseOutside_10.ShowBitmap();
					break;
				case -16:
					houseOutside_11.SetTopLeft(x, y);
					houseOutside_11.ShowBitmap();
					break;
				case -17:
					houseOutside_12.SetTopLeft(x, y);
					houseOutside_12.ShowBitmap();
					break;
				case -18:
					houseOutside_13.SetTopLeft(x, y);
					houseOutside_13.ShowBitmap();
					break;
				case -19:
					houseOutside_14.SetTopLeft(x, y);
					houseOutside_14.ShowBitmap();
					break;
				case -20:
					houseOutside_15.SetTopLeft(x, y);
					houseOutside_15.ShowBitmap();
					break;
				case -21:
					noticeBoard.SetTopLeft(x, y);
					noticeBoard.ShowBitmap();
					break;
				case -22:
					houseWall.SetTopLeft(x, y);
					houseWall.ShowBitmap();
					break;
				case -23:
					houseWall_02.SetTopLeft(x, y);
					houseWall_02.ShowBitmap();
					break;
				case -24:
					houseWall_03.SetTopLeft(x, y);
					houseWall_03.ShowBitmap();
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
		return (map[gy][gx]).IsEmpty();
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