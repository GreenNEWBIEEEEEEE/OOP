#pragma once
#include "CTimer.h"

namespace game_framework
{
	class CMapInfo;
	class CMapEvent;
	class CMapManager;
	class CPlayer;
	class CGameDialog;
	class CWeather;
	class CShopMenu;
	class CGameMap
	{
	public:
		CGameMap(string mapinfo_path, bool hasWeather);
		~CGameMap();
		void LoadBitmap();
		void OnMove(CTimer* timer);
		void OnShow(CTimer* timer);
		void OnShow_Weather();
		void OnShow_Timer(CTimer* timer);
		CWeather* GetWeather();
		// 提供玩家或角色判斷即將移動的位置是否能夠行走, 也就是是否有障礙物
		// 因此, 玩家或角色的Class中需要做移動(OnMove)的，請將CGameMap當作參數傳入(詳見老師的講義MapIntroduction)
		bool IsEmpty(int x, int y) const;

		// 觸發事件
		void triggerMapEvents(UINT key, CPlayer *p, CMapManager *mm, CGameDialog *gd, CShopMenu *sm);
		
		// 取得與設定CGameMap在screen的(left, top)點座標
		int GetSX() const;
		int GetSY() const;
		void SetSX(int nx);
		void SetSY(int ny);
		void SetSXSY(int nx, int ny);

		// 平滑移動指定的視角處
		// 主要用於事件
		void SmoothMoveViewTo(int sx, int sy);

		// 為玩家或角色計算轉換在screen上的點座標
		// 此工作應當由CGameMap完成
		// 因此, 玩家或角色的Class中需要做繪圖(OnShow)的，請將CGameMap當作參數傳入(詳見老師的講義MapIntroduction)
		int ScreenX(int x) const;
		int ScreenY(int y) const;

		// 使用格座標取得單格MapInfo的資料
		// 如若gx,gy超過邊界 則回傳nullptr
		// **取得值後必須檢查是否為nullptr!**
		CMapInfo * GetMapInfo(int gx, int gy) const;
		void SetSpecifiedElementID(int gx, int gy, int elemID);
		int GetSpecifiedElementID(int gx, int gy);

	private:
		// 地圖格元素
		// gnd
		CMovingBitmap sand;
		CMovingBitmap plantSoil;
		CMovingBitmap grass;
		CMovingBitmap soil;
		CMovingBitmap tileFloor;
		CMovingBitmap redFlower;

		// obstacle
		CMovingBitmap fence;
		CAnimation river;
		CMovingBitmap bush;
		CMovingBitmap stone;
		CMovingBitmap wood;
		CMovingBitmap houseOutside_01;
		CMovingBitmap houseOutside_02;
		CMovingBitmap houseOutside_03;
		CMovingBitmap houseOutside_04;
		CMovingBitmap houseOutside_05;
		CMovingBitmap houseOutside_06;
		CMovingBitmap houseOutside_07;
		CMovingBitmap houseOutside_08;
		CMovingBitmap houseOutside_09;
		CMovingBitmap houseOutside_10;
		CMovingBitmap houseOutside_11;
		CMovingBitmap houseOutside_12;
		CMovingBitmap houseOutside_13;
		CMovingBitmap houseOutside_14;
		CMovingBitmap houseOutside_15;
		CMovingBitmap noticeBoard;
		CMovingBitmap houseFloor;
		CMovingBitmap houseWall;
		CMovingBitmap houseWall_02;
		CMovingBitmap houseWall_03;
		CMovingBitmap houseWall_04;
		CMovingBitmap bed_01;
		CMovingBitmap bed_02;
		CMovingBitmap bed_03;
		CMovingBitmap bed_04;
		CMovingBitmap bed_05;
		CMovingBitmap bed_06;
		CMovingBitmap desk_01;
		CMovingBitmap desk_02;
		CMovingBitmap desk_03;
		CMovingBitmap desk_04;
		CMovingBitmap sideTable_01;
		CMovingBitmap sideTable_02;
		CMovingBitmap fireplace_01;
		CMovingBitmap fireplace_02;
		CMovingBitmap fireplace_03;
		CMovingBitmap fireplace_04;
		CMovingBitmap fireplace_05;
		CMovingBitmap fireplace_06;
		CMovingBitmap fireplace_07;
		CMovingBitmap fireplace_08;
		CMovingBitmap clockCalendar_01;
		CMovingBitmap clockCalendar_02;
		CMovingBitmap clockCalendar_03;
		CMovingBitmap kitchenStove_01;
		CMovingBitmap kitchenStove_02;
		CMovingBitmap kitchenStove_03;
		CMovingBitmap TV_01;
		CMovingBitmap TV_02;
		CMovingBitmap TV_03;
		CMovingBitmap TV_04;
		CMovingBitmap TV_05;
		CMovingBitmap TV_06;

		// Shops
		CMovingBitmap PlantShop_01;
		CMovingBitmap PlantShop_02;
		CMovingBitmap PlantShop_03;
		CMovingBitmap PlantShop_04;
		CMovingBitmap PlantShop_05;
		CMovingBitmap PlantShop_06;
		CMovingBitmap PlantShop_07;
		CMovingBitmap PlantShop_08;
		CMovingBitmap PlantShop_09;
		CMovingBitmap PlantShop_010;
		CMovingBitmap PlantShop_011;
		CMovingBitmap PlantShop_012;
		CMovingBitmap PlantShop_013;
		CMovingBitmap PlantShop_014;
		CMovingBitmap PlantShop_015;
		CMovingBitmap PlantShop_016;
		CMovingBitmap PlantShop_017;
		CMovingBitmap PlantShop_018;
		CMovingBitmap PlantShop_019;
		CMovingBitmap PlantShop_020;

		// Chicken house(outdoor)
		CMovingBitmap chickenHouse_01;
		CMovingBitmap chickenHouse_02;
		CMovingBitmap chickenHouse_03;
		CMovingBitmap chickenHouse_04;
		CMovingBitmap chickenHouse_05;
		CMovingBitmap chickenHouse_06;
		CMovingBitmap chickenHouse_07;
		CMovingBitmap chickenHouse_08;
		CMovingBitmap chickenHouse_09;
		CMovingBitmap chickenHouse_10;
		CMovingBitmap chickenHouse_11;
		CMovingBitmap chickenHouse_12;
		CMovingBitmap chickenHouse_13;
		CMovingBitmap chickenHouse_14;
		// Chicken house(indoor) Walls
		CMovingBitmap chickenHouse_Wall01;
		CMovingBitmap chickenHouse_Wall02;
		CMovingBitmap chickenHouse_Wall03;
		// Chicken house(indoor) NoticeBoard
		CMovingBitmap chickenHouse_NoticeBoard;
		// Chicken house(indoor) CropBox
		CMovingBitmap chickenHouse_CropBox01;
		CMovingBitmap chickenHouse_CropBox02;
		CMovingBitmap chickenHouse_CropBox03;
		CMovingBitmap chickenHouse_CropBox04;
		// Chicken house(indoor) StoreBox
		CMovingBitmap chickenHouse_StoreBox01;
		CMovingBitmap chickenHouse_StoreBox02;
		CMovingBitmap chickenHouse_StoreBox03;
		CMovingBitmap chickenHouse_StoreBox04;
		// Chicken house(indoor) FoodBox
		CMovingBitmap chickenHouse_FoodBox01;
		CMovingBitmap chickenHouse_FoodBox02;
		CMovingBitmap chickenHouse_FoodBox03;
		CMovingBitmap chickenHouse_FoodBox04;
		CMovingBitmap chickenHouse_FoodBox05;
		CMovingBitmap chickenHouse_FoodBox06;
		CMovingBitmap chickenHouse_FoodBox07;
		CMovingBitmap chickenHouse_FoodBox08;
		CMovingBitmap chickenHouse_FoodBox09;
		// Chicken house(indoor) EggBox
		CMovingBitmap chickenHouse_EggBox01;
		CMovingBitmap chickenHouse_EggBox02;
		// Chicken house(indoor) Floors
		CMovingBitmap chickenHouse_Floor01;
		CMovingBitmap chickenHouse_Floor02_01;
		CMovingBitmap chickenHouse_Floor02_02;
		CMovingBitmap chickenHouse_Floor03_01;
		CMovingBitmap chickenHouse_Floor03_02;
		CMovingBitmap chickenHouse_Floor03_03;
		CMovingBitmap chickenHouse_Floor03_04;
		CMovingBitmap chickenHouse_Floor03_05;
		CMovingBitmap chickenHouse_Floor04_01;
		CMovingBitmap chickenHouse_Floor04_02;
		CMovingBitmap chickenHouse_Floor04_03;
		CMovingBitmap chickenHouse_Floor04_04;
		CMovingBitmap chickenHouse_Floor04_05;
		CMovingBitmap chickenHouse_Floor04_06;
		CMovingBitmap chickenHouse_Floor05_01;
		CMovingBitmap chickenHouse_Floor05_02;
		CMovingBitmap chickenHouse_Floor05_03;
		CMovingBitmap chickenHouse_Floor05_04;
		CMovingBitmap chickenHouse_Floor05_05;
		CMovingBitmap chickenHouse_Floor05_06;
		CMovingBitmap chickenHouse_Floor06_01;
		CMovingBitmap chickenHouse_Floor06_02;
		CMovingBitmap chickenHouse_Floor06_03;
		CMovingBitmap chickenHouse_Floor06_04;
		CMovingBitmap chickenHouse_Floor06_05;
		
		// plant: Radish
		CMovingBitmap radish_Seed_D;
		CMovingBitmap radish_Seed_W;
		CMovingBitmap radish_Grow01_D;
		CMovingBitmap radish_Grow01_W;
		CMovingBitmap radish_Mature;

		
		CMovingBitmap animalGrass;
		CMovingBitmap egg;
		


		// 二維資料陣列
		int row, col;
		CMapInfo **map = nullptr;

		
		int sx, sy; // CGameMap在screen上的(left, top)
		int gndW, gndH; // 單格大小

		// 平滑移動所需參數
		bool isSmoothMoving = false;
		const int smoothMovingCountMax = 90;
		// Delta x 與 Delta y : 變化量，在OnMove中做改變(如果現在是SmoothMoving)
		// Map上所有元素要畫時，也要加上這兩個
		// 若不是SmoothingMoving狀態，就都會是0
		int smxDiff = 0, smyDiff = 0;
		int smdx = 0, smdy = 0;
		// 儲存smooth moving的目標座標
		// 目前，如果指定了SmoothMove, 到達目的地之後並不會自動彈回來，需要再指定一次回至原先的位置
		int smx, smy;


		// 天氣物件指標(地圖腳本的weather=true才有實體化)
		CWeather *weather = nullptr;

		//
		void CreateMapInfos(string& mapinfo_path);



	};
}