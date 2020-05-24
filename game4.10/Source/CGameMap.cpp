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
#include "CWeather.h"
#include "CShopMenu.h"
#include "CPlantShopMenu.h"
#include "CTimer.h"



namespace game_framework {
	CGameMap::CGameMap(string mapinfo_path, bool hasWeather) : row(0), col(0)
	{
		CreateMapInfos(mapinfo_path);
		sx = 400, sy = 150;
		gndW = 64; gndH = 53;

		// Create weather
		if (hasWeather)
		{
			this->weather = new CWeather();
		}
	}

	CGameMap::~CGameMap()
	{
		for (int i = 0; i < row; ++i)
			delete[] map[i];
		delete[] map;
		map = nullptr;

		if (weather != nullptr)
		{
			delete weather;
			weather = nullptr;
		}
	}

	void CGameMap::SetSpecifiedElementID(int gx, int gy, int elemID)
	{
		map[gy][gx].SetElemID(elemID);
	}

	int CGameMap::GetSpecifiedElementID(int gx, int gy) // 格座標
	{
		return map[gy][gx].GetElemID();
	}

	CWeather* CGameMap::GetWeather()
	{
		return weather;
	}

	void CGameMap::LoadBitmap()
	{
		sand.LoadBitmap(IDB_Sand);
		plantSoil.LoadBitmap(IDB_PlantSoil);
		grass.LoadBitmap(IDB_Grass);
		soil.LoadBitmap(IDB_Soil);
		tileFloor.LoadBitmap(IDB_TileFloor01);
		redFlower.LoadBitmap(IDB_RedFlower);

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
		houseWall_04.LoadBitmap(IDB_HouseWall04);

		// Bed: -46~-51
		{
			bed_01.LoadBitmap(IDB_Bed01);
			bed_02.LoadBitmap(IDB_Bed02);
			bed_03.LoadBitmap(IDB_Bed03);
			bed_04.LoadBitmap(IDB_Bed04);
			bed_05.LoadBitmap(IDB_Bed05);
			bed_06.LoadBitmap(IDB_Bed06);
		}

		// Desk
		{
			desk_01.LoadBitmap(IDB_Desk01);
			desk_02.LoadBitmap(IDB_Desk02);
			desk_03.LoadBitmap(IDB_Desk03);
			desk_04.LoadBitmap(IDB_Desk04);
		}

		// Side Table
		{
			sideTable_01.LoadBitmap(IDB_SideTable01);
			sideTable_02.LoadBitmap(IDB_SideTable02);
		}

		// Fire place
		{
			fireplace_01.LoadBitmap(IDB_Fireplace01);
			fireplace_02.LoadBitmap(IDB_Fireplace02);
			fireplace_03.LoadBitmap(IDB_Fireplace03);
			fireplace_04.LoadBitmap(IDB_Fireplace04);
			fireplace_05.LoadBitmap(IDB_Fireplace05);
			fireplace_06.LoadBitmap(IDB_Fireplace06);
			fireplace_07.LoadBitmap(IDB_Fireplace07);
			fireplace_08.LoadBitmap(IDB_Fireplace08);
		}

		// Clock Calendar
		{
			clockCalendar_01.LoadBitmap(IDB_ClockCalendar01);
			clockCalendar_02.LoadBitmap(IDB_ClockCalendar02);
			clockCalendar_03.LoadBitmap(IDB_ClockCalendar03);
		}

		// Kitchen stove
		{
			kitchenStove_01.LoadBitmap(IDB_KitchenStove01);
			kitchenStove_02.LoadBitmap(IDB_KitchenStove02);
			kitchenStove_03.LoadBitmap(IDB_KitchenStove03);
		}

		// TV
		{
			TV_01.LoadBitmap(IDB_TV01);
			TV_02.LoadBitmap(IDB_TV02);
			TV_03.LoadBitmap(IDB_TV03);
			TV_04.LoadBitmap(IDB_TV04);
			TV_05.LoadBitmap(IDB_TV05);
			TV_06.LoadBitmap(IDB_TV06);
		}

		radish_Seed_D.LoadBitmap(IDB_Radish_Seed_D);
		radish_Seed_W.LoadBitmap(IDB_Radish_Seed_W);
		radish_Grow01_D.LoadBitmap(IDB_Radish_Grow01_D);
		radish_Grow01_W.LoadBitmap(IDB_Radish_Grow01_W);
		radish_Mature.LoadBitmap(IDB_Radish_Mature);

		// PlantShop	
		{
			PlantShop_01.LoadBitmap(IDB_PlantShopHouse_Morning_s01);
			PlantShop_02.LoadBitmap(IDB_PlantShopHouse_Morning_s02);
			PlantShop_03.LoadBitmap(IDB_PlantShopHouse_Morning_s03);
			PlantShop_04.LoadBitmap(IDB_PlantShopHouse_Morning_s04);
			PlantShop_05.LoadBitmap(IDB_PlantShopHouse_Morning_s05);
			PlantShop_06.LoadBitmap(IDB_PlantShopHouse_Morning_s06);
			PlantShop_07.LoadBitmap(IDB_PlantShopHouse_Morning_s07);
			PlantShop_08.LoadBitmap(IDB_PlantShopHouse_Morning_s08);
			PlantShop_09.LoadBitmap(IDB_PlantShopHouse_Morning_s09);
			PlantShop_010.LoadBitmap(IDB_PlantShopHouse_Morning_s010);
			PlantShop_011.LoadBitmap(IDB_PlantShopHouse_Morning_s011);
			PlantShop_012.LoadBitmap(IDB_PlantShopHouse_Morning_s012);
			PlantShop_013.LoadBitmap(IDB_PlantShopHouse_Morning_s013);
			PlantShop_014.LoadBitmap(IDB_PlantShopHouse_Morning_s014);
			PlantShop_015.LoadBitmap(IDB_PlantShopHouse_Morning_s015);
			PlantShop_016.LoadBitmap(IDB_PlantShopHouse_Morning_s016);
			PlantShop_017.LoadBitmap(IDB_PlantShopHouse_Morning_s017);
			PlantShop_018.LoadBitmap(IDB_PlantShopHouse_Morning_s018);
			PlantShop_019.LoadBitmap(IDB_PlantShopHouse_Morning_s019);
			PlantShop_020.LoadBitmap(IDB_PlantShopHouse_Morning_s020);
		}

		// Chicken house(outdoor)
		{
			chickenHouse_01.LoadBitmap(IDB_ChickenHouse01);
			chickenHouse_02.LoadBitmap(IDB_ChickenHouse02);
			chickenHouse_03.LoadBitmap(IDB_ChickenHouse03);
			chickenHouse_04.LoadBitmap(IDB_ChickenHouse04);
			chickenHouse_05.LoadBitmap(IDB_ChickenHouse05);
			chickenHouse_06.LoadBitmap(IDB_ChickenHouse06);
			chickenHouse_07.LoadBitmap(IDB_ChickenHouse07);
			chickenHouse_08.LoadBitmap(IDB_ChickenHouse08);
			chickenHouse_09.LoadBitmap(IDB_ChickenHouse09);
			chickenHouse_10.LoadBitmap(IDB_ChickenHouse10);
			chickenHouse_11.LoadBitmap(IDB_ChickenHouse11);
			chickenHouse_12.LoadBitmap(IDB_ChickenHouse12);
			chickenHouse_13.LoadBitmap(IDB_ChickenHouse13);
			chickenHouse_14.LoadBitmap(IDB_ChickenHouse14);
		}

		// Chicken house(indoor) Walls
		{
			chickenHouse_Wall01.LoadBitmap(IDB_ChickenHouse_Wall01);
			chickenHouse_Wall02.LoadBitmap(IDB_ChickenHouse_Wall02);
			chickenHouse_Wall03.LoadBitmap(IDB_ChickenHouse_Wall03);
		}

		// Chicken house(indoor) NoticeBoard
		{
			chickenHouse_NoticeBoard.LoadBitmap(IDB_ChickenHouse_NoticeBoard);
		}

		// Chicken house(indoor) CropBox
		{
			chickenHouse_CropBox01.LoadBitmap(IDB_ChickenHouse_CropBox01);
			chickenHouse_CropBox02.LoadBitmap(IDB_ChickenHouse_CropBox02);
			chickenHouse_CropBox03.LoadBitmap(IDB_ChickenHouse_CropBox03);
			chickenHouse_CropBox04.LoadBitmap(IDB_ChickenHouse_CropBox04);
		}

		// Chicken house(indoor) StoreBox
		{
			chickenHouse_StoreBox01.LoadBitmap(IDB_ChickenHouse_StoreBox01);
			chickenHouse_StoreBox02.LoadBitmap(IDB_ChickenHouse_StoreBox02);
			chickenHouse_StoreBox03.LoadBitmap(IDB_ChickenHouse_StoreBox03);
			chickenHouse_StoreBox04.LoadBitmap(IDB_ChickenHouse_StoreBox04);
		}

		// Chicken house(indoor) FoodBox
		{
			chickenHouse_FoodBox01.LoadBitmap(IDB_ChickenHouse_FoodBox01);
			chickenHouse_FoodBox02.LoadBitmap(IDB_ChickenHouse_FoodBox02);
			chickenHouse_FoodBox03.LoadBitmap(IDB_ChickenHouse_FoodBox03);
			chickenHouse_FoodBox04.LoadBitmap(IDB_ChickenHouse_FoodBox04);
			chickenHouse_FoodBox05.LoadBitmap(IDB_ChickenHouse_FoodBox05);
			chickenHouse_FoodBox06.LoadBitmap(IDB_ChickenHouse_FoodBox06);
			chickenHouse_FoodBox07.LoadBitmap(IDB_ChickenHouse_FoodBox07);
			chickenHouse_FoodBox08.LoadBitmap(IDB_ChickenHouse_FoodBox08);
			chickenHouse_FoodBox09.LoadBitmap(IDB_ChickenHouse_FoodBox09);
		}

		// Chicken house(indoor) EggBox
		{
			chickenHouse_EggBox01.LoadBitmap(IDB_ChickenHouse_EggBox01);
			chickenHouse_EggBox02.LoadBitmap(IDB_ChickenHouse_EggBox02);
		}

		// Chicken house(indoor) Floors
		{
			chickenHouse_Floor01.LoadBitmap(IDB_ChickenHouse_Floor01);

			chickenHouse_Floor02_01.LoadBitmap(IDB_ChickenHouse_Floor02_01);
			chickenHouse_Floor02_02.LoadBitmap(IDB_ChickenHouse_Floor02_02);

			chickenHouse_Floor03_01.LoadBitmap(IDB_ChickenHouse_Floor03_01);
			chickenHouse_Floor03_02.LoadBitmap(IDB_ChickenHouse_Floor03_02);
			chickenHouse_Floor03_03.LoadBitmap(IDB_ChickenHouse_Floor03_03);
			chickenHouse_Floor03_04.LoadBitmap(IDB_ChickenHouse_Floor03_04);
			chickenHouse_Floor03_05.LoadBitmap(IDB_ChickenHouse_Floor03_05);

			chickenHouse_Floor04_01.LoadBitmap(IDB_ChickenHouse_Floor04_01);
			chickenHouse_Floor04_02.LoadBitmap(IDB_ChickenHouse_Floor04_02);
			chickenHouse_Floor04_03.LoadBitmap(IDB_ChickenHouse_Floor04_03);
			chickenHouse_Floor04_04.LoadBitmap(IDB_ChickenHouse_Floor04_04);
			chickenHouse_Floor04_05.LoadBitmap(IDB_ChickenHouse_Floor04_05);
			chickenHouse_Floor04_06.LoadBitmap(IDB_ChickenHouse_Floor04_06);

			chickenHouse_Floor05_01.LoadBitmap(IDB_ChickenHouse_Floor05_01);
			chickenHouse_Floor05_02.LoadBitmap(IDB_ChickenHouse_Floor05_02);
			chickenHouse_Floor05_03.LoadBitmap(IDB_ChickenHouse_Floor05_03);
			chickenHouse_Floor05_04.LoadBitmap(IDB_ChickenHouse_Floor05_04);
			chickenHouse_Floor05_05.LoadBitmap(IDB_ChickenHouse_Floor05_05);
			chickenHouse_Floor05_06.LoadBitmap(IDB_ChickenHouse_Floor05_06);

			chickenHouse_Floor06_01.LoadBitmap(IDB_ChickenHouse_Floor06_01);
			chickenHouse_Floor06_02.LoadBitmap(IDB_ChickenHouse_Floor06_02);
			chickenHouse_Floor06_03.LoadBitmap(IDB_ChickenHouse_Floor06_03);
			chickenHouse_Floor06_04.LoadBitmap(IDB_ChickenHouse_Floor06_04);
			chickenHouse_Floor06_05.LoadBitmap(IDB_ChickenHouse_Floor06_05);

			animalShop_01.LoadBitmap(IDB_AnimalShop01);
			animalShop_02.LoadBitmap(IDB_AnimalShop02);
			animalShop_03.LoadBitmap(IDB_AnimalShop03);
			animalShop_04.LoadBitmap(IDB_AnimalShop04);
			animalShop_05.LoadBitmap(IDB_AnimalShop05);
			animalShop_06.LoadBitmap(IDB_AnimalShop06);
			animalShop_07.LoadBitmap(IDB_AnimalShop07);
			animalShop_08.LoadBitmap(IDB_AnimalShop08);
			animalShop_09.LoadBitmap(IDB_AnimalShop09);
			animalShop_10.LoadBitmap(IDB_AnimalShop10);
			animalShop_11.LoadBitmap(IDB_AnimalShop11);
			animalShop_12.LoadBitmap(IDB_AnimalShop12);
			animalShop_13.LoadBitmap(IDB_AnimalShop13);
			animalShop_14.LoadBitmap(IDB_AnimalShop14);
			animalShop_15.LoadBitmap(IDB_AnimalShop15);
			animalShop_16.LoadBitmap(IDB_AnimalShop16);
			animalShop_17.LoadBitmap(IDB_AnimalShop17);
			animalShop_18.LoadBitmap(IDB_AnimalShop18);
			animalShop_19.LoadBitmap(IDB_AnimalShop19);
			animalShop_20.LoadBitmap(IDB_AnimalShop20);
		}
		
		{
			egg.LoadBitmap(IDB_Egg);
			animalGrass.LoadBitmap(IDB_AnimalGrass);
		}

		if (weather != nullptr)
		{
			weather->LoadBitmap();
		}
	}

	void CGameMap::OnMove(CTimer* timer)
	{
		// 如果這個Map是有天氣現象，則需要呼叫weather的OnMove, 主要做天氣視覺動畫的更新
		if (weather != nullptr)
			weather->OnMove(timer);

		// 單格Mapinfo的OnMove主要用於農作物計數
		for (int i = 0; i < row; ++i)
			for (int j = 0; j < col; ++j)
				map[i][j].OnMove(timer, weather);
	}

	void CGameMap::OnShow(CTimer* timer)
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
				case 5:
					radish_Seed_D.SetTopLeft(x, y);
					radish_Seed_D.ShowBitmap();
					break;
				case 6:
					radish_Seed_W.SetTopLeft(x, y);
					radish_Seed_W.ShowBitmap();
					break;
				case 7:
					radish_Grow01_D.SetTopLeft(x, y);
					radish_Grow01_D.ShowBitmap();
					break;
				case 8:
					radish_Grow01_W.SetTopLeft(x, y);
					radish_Grow01_W.ShowBitmap();
					break;
				case 9:
					radish_Mature.SetTopLeft(x, y);
					radish_Mature.ShowBitmap();
					break;
				case 10:
					tileFloor.SetTopLeft(x, y);
					tileFloor.ShowBitmap();
					break;
				case 11:
					chickenHouse_Floor01.SetTopLeft(x, y);
					chickenHouse_Floor01.ShowBitmap();
					break;
				case 12:
					chickenHouse_Floor02_01.SetTopLeft(x, y);
					chickenHouse_Floor02_01.ShowBitmap();
					break;
				case 13:
					chickenHouse_Floor02_02.SetTopLeft(x, y);
					chickenHouse_Floor02_02.ShowBitmap();
					break;
				case 14:
					chickenHouse_Floor03_01.SetTopLeft(x, y);
					chickenHouse_Floor03_01.ShowBitmap();
					break;
				case 15:
					chickenHouse_Floor03_02.SetTopLeft(x, y);
					chickenHouse_Floor03_02.ShowBitmap();
					break;
				case 16:
					chickenHouse_Floor03_03.SetTopLeft(x, y);
					chickenHouse_Floor03_03.ShowBitmap();
					break;
				case 17:
					chickenHouse_Floor03_04.SetTopLeft(x, y);
					chickenHouse_Floor03_04.ShowBitmap();
					break;
				case 18:
					chickenHouse_Floor03_05.SetTopLeft(x, y);
					chickenHouse_Floor03_05.ShowBitmap();
					break;
				case 19:
					chickenHouse_Floor04_01.SetTopLeft(x, y);
					chickenHouse_Floor04_01.ShowBitmap();
					break;
				case 20:
					chickenHouse_Floor04_02.SetTopLeft(x, y);
					chickenHouse_Floor04_02.ShowBitmap();
					break;
				case 21:
					chickenHouse_Floor04_03.SetTopLeft(x, y);
					chickenHouse_Floor04_03.ShowBitmap();
					break;
				case 22:
					chickenHouse_Floor04_04.SetTopLeft(x, y);
					chickenHouse_Floor04_04.ShowBitmap();
					break;
				case 23:
					chickenHouse_Floor04_05.SetTopLeft(x, y);
					chickenHouse_Floor04_05.ShowBitmap();
					break;
				case 24:
					chickenHouse_Floor04_06.SetTopLeft(x, y);
					chickenHouse_Floor04_06.ShowBitmap();
					break;
				case 25:
					chickenHouse_Floor05_01.SetTopLeft(x, y);
					chickenHouse_Floor05_01.ShowBitmap();
					break;
				case 26:
					chickenHouse_Floor05_02.SetTopLeft(x, y);
					chickenHouse_Floor05_02.ShowBitmap();
					break;
				case 27:
					chickenHouse_Floor05_03.SetTopLeft(x, y);
					chickenHouse_Floor05_03.ShowBitmap();
					break;
				case 28:
					chickenHouse_Floor05_04.SetTopLeft(x, y);
					chickenHouse_Floor05_04.ShowBitmap();
					break;
				case 29:
					chickenHouse_Floor05_05.SetTopLeft(x, y);
					chickenHouse_Floor05_05.ShowBitmap();
					break;
				case 30:
					chickenHouse_Floor05_06.SetTopLeft(x, y);
					chickenHouse_Floor05_06.ShowBitmap();
					break;
				case 31:
					chickenHouse_Floor06_01.SetTopLeft(x, y);
					chickenHouse_Floor06_01.ShowBitmap();
					break;
				case 32:
					chickenHouse_Floor06_02.SetTopLeft(x, y);
					chickenHouse_Floor06_02.ShowBitmap();
					break;
				case 33:
					chickenHouse_Floor06_03.SetTopLeft(x, y);
					chickenHouse_Floor06_03.ShowBitmap();
					break;
				case 34:
					chickenHouse_Floor06_04.SetTopLeft(x, y);
					chickenHouse_Floor06_04.ShowBitmap();
					break;
				case 35:
					chickenHouse_Floor06_05.SetTopLeft(x, y);
					chickenHouse_Floor06_05.ShowBitmap();
					break;

				////////////////////////////////////////////
				////////////////////////////////////////////
				////////////////////////////////////////////
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
				case -25:
					PlantShop_01.SetTopLeft(x, y);
					PlantShop_01.ShowBitmap();
					break;
				case -26:
					PlantShop_02.SetTopLeft(x, y);
					PlantShop_02.ShowBitmap();
					break;
				case -27:
					PlantShop_03.SetTopLeft(x, y);
					PlantShop_03.ShowBitmap();
					break;
				case -28:
					PlantShop_04.SetTopLeft(x, y);
					PlantShop_04.ShowBitmap();
					break;
				case -29:
					PlantShop_05.SetTopLeft(x, y);
					PlantShop_05.ShowBitmap();
					break;
				case -30:
					PlantShop_06.SetTopLeft(x, y);
					PlantShop_06.ShowBitmap();
					break;
				case -31:
					PlantShop_07.SetTopLeft(x, y);
					PlantShop_07.ShowBitmap();
					break;
				case -32:
					PlantShop_08.SetTopLeft(x, y);
					PlantShop_08.ShowBitmap();
					break;
				case -33:
					PlantShop_09.SetTopLeft(x, y);
					PlantShop_09.ShowBitmap();
					break;
				case -34:
					PlantShop_010.SetTopLeft(x, y);
					PlantShop_010.ShowBitmap();
					break;
				case -35:
					PlantShop_011.SetTopLeft(x, y);
					PlantShop_011.ShowBitmap();
					break;
				case -36:
					PlantShop_012.SetTopLeft(x, y);
					PlantShop_012.ShowBitmap();
					break;
				case -37:
					PlantShop_013.SetTopLeft(x, y);
					PlantShop_013.ShowBitmap();
					break;
				case -38:
					PlantShop_014.SetTopLeft(x, y);
					PlantShop_014.ShowBitmap();
					break;
				case -39:
					PlantShop_015.SetTopLeft(x, y);
					PlantShop_015.ShowBitmap();
					break;
				case -40:
					PlantShop_016.SetTopLeft(x, y);
					PlantShop_016.ShowBitmap();
					break;
				case -41:
					PlantShop_017.SetTopLeft(x, y);
					PlantShop_017.ShowBitmap();
					break;
				case -42:
					PlantShop_018.SetTopLeft(x, y);
					PlantShop_018.ShowBitmap();
					break;
				case -43:
					PlantShop_019.SetTopLeft(x, y);
					PlantShop_019.ShowBitmap();
					break;
				case -44:
					PlantShop_020.SetTopLeft(x, y);
					PlantShop_020.ShowBitmap();
					break;
				case -45:
					redFlower.SetTopLeft(x, y);
					redFlower.ShowBitmap();
					break;
				case -46:
					bed_01.SetTopLeft(x, y);
					bed_01.ShowBitmap();
					break;
				case -47:
					bed_02.SetTopLeft(x, y);
					bed_02.ShowBitmap();
					break;
				case -48:
					bed_03.SetTopLeft(x, y);
					bed_03.ShowBitmap();
					break;
				case -49:
					bed_04.SetTopLeft(x, y);
					bed_04.ShowBitmap();
					break;
				case -50:
					bed_05.SetTopLeft(x, y);
					bed_05.ShowBitmap();
					break;
				case -51:
					bed_06.SetTopLeft(x, y);
					bed_06.ShowBitmap();
					break;
				case -52:
					houseWall_04.SetTopLeft(x, y);
					houseWall_04.ShowBitmap();
					break;
				case -53:
					desk_01.SetTopLeft(x, y);
					desk_01.ShowBitmap();
					break;
				case -54:
					desk_02.SetTopLeft(x, y);
					desk_02.ShowBitmap();
					break;
				case -55:
					desk_03.SetTopLeft(x, y);
					desk_03.ShowBitmap();
					break;
				case -56:
					desk_04.SetTopLeft(x, y);
					desk_04.ShowBitmap();
					break;
				case -57:
					sideTable_01.SetTopLeft(x, y);
					sideTable_01.ShowBitmap();
					break;
				case -58:
					sideTable_02.SetTopLeft(x, y);
					sideTable_02.ShowBitmap();
					break;
				case -59:
					fireplace_01.SetTopLeft(x, y);
					fireplace_01.ShowBitmap();
					break;
				case -60:
					fireplace_02.SetTopLeft(x, y);
					fireplace_02.ShowBitmap();
					break;
				case -61:
					fireplace_03.SetTopLeft(x, y);
					fireplace_03.ShowBitmap();
					break;
				case -62:
					fireplace_04.SetTopLeft(x, y);
					fireplace_04.ShowBitmap();
					break;
				case -63:
					fireplace_05.SetTopLeft(x, y);
					fireplace_05.ShowBitmap();
					break;
				case -64:
					fireplace_06.SetTopLeft(x, y);
					fireplace_06.ShowBitmap();
					break;
				case -65:
					fireplace_07.SetTopLeft(x, y);
					fireplace_07.ShowBitmap();
					break;
				case -66:
					fireplace_08.SetTopLeft(x, y);
					fireplace_08.ShowBitmap();
					break;
				case -67:
					clockCalendar_01.SetTopLeft(x, y);
					clockCalendar_01.ShowBitmap();
					break;
				case -68:
					clockCalendar_02.SetTopLeft(x, y);
					clockCalendar_02.ShowBitmap();
					break;
				case -69:
					clockCalendar_03.SetTopLeft(x, y);
					clockCalendar_03.ShowBitmap();
					break;
				case -70:
					kitchenStove_01.SetTopLeft(x, y);
					kitchenStove_01.ShowBitmap();
					break;
				case -71:
					kitchenStove_02.SetTopLeft(x, y);
					kitchenStove_02.ShowBitmap();
					break;
				case -72:
					kitchenStove_03.SetTopLeft(x, y);
					kitchenStove_03.ShowBitmap();
					break;
				case -73:
					TV_01.SetTopLeft(x, y);
					TV_01.ShowBitmap();
					break;
				case -74:
					TV_02.SetTopLeft(x, y);
					TV_02.ShowBitmap();
					break;
				case -75:
					TV_03.SetTopLeft(x, y);
					TV_03.ShowBitmap();
					break;
				case -76:
					TV_04.SetTopLeft(x, y);
					TV_04.ShowBitmap();
					break;
				case -77:
					TV_05.SetTopLeft(x, y);
					TV_05.ShowBitmap();
					break;
				case -78:
					TV_06.SetTopLeft(x, y);
					TV_06.ShowBitmap();
					break;
				case -79:
					chickenHouse_01.SetTopLeft(x, y);
					chickenHouse_01.ShowBitmap();
					break;
				case -80:
					chickenHouse_02.SetTopLeft(x, y);
					chickenHouse_02.ShowBitmap();
					break;
				case -81:
					chickenHouse_03.SetTopLeft(x, y);
					chickenHouse_03.ShowBitmap();
					break;
				case -82:
					chickenHouse_04.SetTopLeft(x, y);
					chickenHouse_04.ShowBitmap();
					break;
				case -83:
					chickenHouse_05.SetTopLeft(x, y);
					chickenHouse_05.ShowBitmap();
					break;
				case -84:
					chickenHouse_06.SetTopLeft(x, y);
					chickenHouse_06.ShowBitmap();
					break;
				case -85:
					chickenHouse_07.SetTopLeft(x, y);
					chickenHouse_07.ShowBitmap();
					break;
				case -86:
					chickenHouse_08.SetTopLeft(x, y);
					chickenHouse_08.ShowBitmap();
					break;
				case -87:
					chickenHouse_09.SetTopLeft(x, y);
					chickenHouse_09.ShowBitmap();
					break;
				case -88:
					chickenHouse_10.SetTopLeft(x, y);
					chickenHouse_10.ShowBitmap();
					break;
				case -89:
					chickenHouse_11.SetTopLeft(x, y);
					chickenHouse_11.ShowBitmap();
					break;
				case -90:
					chickenHouse_12.SetTopLeft(x, y);
					chickenHouse_12.ShowBitmap();
					break;
				case -91:
					chickenHouse_13.SetTopLeft(x, y);
					chickenHouse_13.ShowBitmap();
					break;
				case -92:
					chickenHouse_14.SetTopLeft(x, y);
					chickenHouse_14.ShowBitmap();
					break;
				case -93:
					chickenHouse_Wall01.SetTopLeft(x, y);
					chickenHouse_Wall01.ShowBitmap();
					break;
				case -94:
					chickenHouse_Wall02.SetTopLeft(x, y);
					chickenHouse_Wall02.ShowBitmap();
					break;
				case -95:
					chickenHouse_Wall03.SetTopLeft(x, y);
					chickenHouse_Wall03.ShowBitmap();
					break;
				case -96:
					chickenHouse_NoticeBoard.SetTopLeft(x, y);
					chickenHouse_NoticeBoard.ShowBitmap();
					break;
				case -97:
					chickenHouse_CropBox01.SetTopLeft(x, y);
					chickenHouse_CropBox01.ShowBitmap();
					break;
				case -98:
					chickenHouse_CropBox02.SetTopLeft(x, y);
					chickenHouse_CropBox02.ShowBitmap();
					break;
				case -99:
					chickenHouse_CropBox03.SetTopLeft(x, y);
					chickenHouse_CropBox03.ShowBitmap();
					break;
				case -100:
					chickenHouse_CropBox04.SetTopLeft(x, y);
					chickenHouse_CropBox04.ShowBitmap();
					break;
				case -101:
					chickenHouse_StoreBox01.SetTopLeft(x, y);
					chickenHouse_StoreBox01.ShowBitmap();
					break;
				case -102:
					chickenHouse_StoreBox02.SetTopLeft(x, y);
					chickenHouse_StoreBox02.ShowBitmap();
					break;
				case -103:
					chickenHouse_StoreBox03.SetTopLeft(x, y);
					chickenHouse_StoreBox03.ShowBitmap();
					break;
				case -104:
					chickenHouse_StoreBox04.SetTopLeft(x, y);
					chickenHouse_StoreBox04.ShowBitmap();
					break;
				case -105:
					chickenHouse_FoodBox01.SetTopLeft(x, y);
					chickenHouse_FoodBox01.ShowBitmap();
					break;
				case -106:
					chickenHouse_FoodBox02.SetTopLeft(x, y);
					chickenHouse_FoodBox02.ShowBitmap();
					break;
				case -107:
					chickenHouse_FoodBox03.SetTopLeft(x, y);
					chickenHouse_FoodBox03.ShowBitmap();
					break;
				case -108:
					chickenHouse_FoodBox04.SetTopLeft(x, y);
					chickenHouse_FoodBox04.ShowBitmap();
					break;
				case -109:
					chickenHouse_FoodBox05.SetTopLeft(x, y);
					chickenHouse_FoodBox05.ShowBitmap();
					break;
				case -110:
					chickenHouse_FoodBox06.SetTopLeft(x, y);
					chickenHouse_FoodBox06.ShowBitmap();
					break;
				case -111:
					chickenHouse_FoodBox07.SetTopLeft(x, y);
					chickenHouse_FoodBox07.ShowBitmap();
					break;
				case -112:
					chickenHouse_FoodBox08.SetTopLeft(x, y);
					chickenHouse_FoodBox08.ShowBitmap();
					break;
				case -113:
					chickenHouse_FoodBox09.SetTopLeft(x, y);
					chickenHouse_FoodBox09.ShowBitmap();
					break;
				case -114:
					chickenHouse_EggBox01.SetTopLeft(x, y);
					chickenHouse_EggBox01.ShowBitmap();
					break;
				case -115:
					chickenHouse_EggBox02.SetTopLeft(x, y);
					chickenHouse_EggBox02.ShowBitmap();
					break;
				case -116:
					animalGrass.SetTopLeft(x, y);
					animalGrass.ShowBitmap();
					break;
				case -117:
					egg.SetTopLeft(x, y);
					egg.ShowBitmap();
					break;
				case -118:
					animalShop_01.SetTopLeft(x, y);
					animalShop_01.ShowBitmap();
					break;
				case -119:
					animalShop_02.SetTopLeft(x, y);
					animalShop_02.ShowBitmap();
					break;
				case -120:
					animalShop_03.SetTopLeft(x, y);
					animalShop_03.ShowBitmap();
					break;
				case -121:
					animalShop_04.SetTopLeft(x, y);
					animalShop_04.ShowBitmap();
					break;
				case -122:
					animalShop_05.SetTopLeft(x, y);
					animalShop_05.ShowBitmap();
					break;
				case -123:
					animalShop_06.SetTopLeft(x, y);
					animalShop_06.ShowBitmap();
					break;
				case -124:
					animalShop_07.SetTopLeft(x, y);
					animalShop_07.ShowBitmap();
					break;
				case -125:
					animalShop_08.SetTopLeft(x, y);
					animalShop_08.ShowBitmap();
					break;
				case -126:
					animalShop_09.SetTopLeft(x, y);
					animalShop_09.ShowBitmap();
					break;
				case -127:
					animalShop_10.SetTopLeft(x, y);
					animalShop_10.ShowBitmap();
					break;
				case -128:
					animalShop_11.SetTopLeft(x, y);
					animalShop_11.ShowBitmap();
					break;
				case -129:
					animalShop_12.SetTopLeft(x, y);
					animalShop_12.ShowBitmap();
					break;
				case -130:
					animalShop_13.SetTopLeft(x, y);
					animalShop_13.ShowBitmap();
					break;
				case -131:
					animalShop_14.SetTopLeft(x, y);
					animalShop_14.ShowBitmap();
					break;
				case -132:
					animalShop_15.SetTopLeft(x, y);
					animalShop_15.ShowBitmap();
					break;
				case -133:
					animalShop_16.SetTopLeft(x, y);
					animalShop_16.ShowBitmap();
					break;
				case -134:
					animalShop_17.SetTopLeft(x, y);
					animalShop_17.ShowBitmap();
					break;
				case -135:
					animalShop_18.SetTopLeft(x, y);
					animalShop_18.ShowBitmap();
					break;
				case -136:
					animalShop_19.SetTopLeft(x, y);
					animalShop_19.ShowBitmap();
					break;
				case -137:
					animalShop_20.SetTopLeft(x, y);
					animalShop_20.ShowBitmap();
					break;
				default:
					break;
				}
			}
		}
	}

	// 天氣視覺動畫不會跟OnShow一起顯示，需獨立出來
	void CGameMap::OnShow_Weather()
	{
		// 顯示天氣視覺動畫
		if (weather != nullptr)
			weather->OnShow();
	}

	void CGameMap::OnShow_Timer(CTimer* timer)
	{
		if (weather != nullptr)		// 因為weather的動畫跟timer的動畫一樣是區分室內室外，所以用weather判斷也行
			timer->OnShow();
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
	void CGameMap::triggerMapEvents(
		UINT key, 
		CPlayer *p, 
		CMapManager *mm, 
		CGameDialog *gd, 
		vector<CShopMenu*> sms
	)
	{
		int px = p->GetBodyX() + 30, py = p->GetBodyY() + 60; // MAYBE FIXME
		int gx = px / gndW, gy = py / gndH; // 求出格座標
		map[gy][gx].triggerEventByKeyCode(key, p, mm, gd, sms);
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
	void CGameMap::SmoothMoveViewTo(int sx, int sy)
	{
		this->sx = sx;
		this->sy = sy;
	}
	int CGameMap::ScreenX(int x) const
	{
		return x - sx;
	}
	int CGameMap::ScreenY(int y) const
	{
		return y - sy;
	}

	CMapInfo * CGameMap::GetMapInfo(int gx, int gy) const
	{
		if (gx >= 0 && gx < col && gy >= 0 && gy < row)
			return &(map[gy][gx]);
		else
			return nullptr;
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
					
					while (sss >> data) {
						map[i][j].AddEvent(stoi(data));
					}
					j++;
				}
				i++;
			}
		}
		is.close();
	}
}