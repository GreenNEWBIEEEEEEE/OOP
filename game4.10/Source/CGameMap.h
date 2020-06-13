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
		void triggerMapEvents(
			UINT key, 
			CPlayer *p, 
			CMapManager *mm, 
			CGameDialog *gd, 
			vector<CShopMenu*> sms
		);
		
		// 取得與設定CGameMap在screen的(left, top)點座標
		int GetSX() const;
		int GetSY() const;
		void SetSX(int nx);
		void SetSY(int ny);
		void SetSXSY(int nx, int ny);

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
		// plant: Corn
		CMovingBitmap corn_Grow01_D;
		CMovingBitmap corn_Grow01_W;
		CMovingBitmap corn_Grow02_D;
		CMovingBitmap corn_Grow02_W;
		CMovingBitmap corn_Grow03_D;
		CMovingBitmap corn_Grow03_W;
		CMovingBitmap corn_Mature;
		// plant: Eggplant
		CMovingBitmap eggplant_Grow01_D;
		CMovingBitmap eggplant_Grow01_W;
		CMovingBitmap eggplant_Mature;
		// plant: Peanut
		CMovingBitmap peanut_Grow01_D;
		CMovingBitmap peanut_Grow01_W;
		CMovingBitmap peanut_Mature;
		// plant: Potato
		CMovingBitmap potato_Grow01_D;
		CMovingBitmap potato_Grow01_W;
		CMovingBitmap potato_Mature;
		// plant: Tomato
		CMovingBitmap tomato_Grow01_D;
		CMovingBitmap tomato_Grow01_W;
		CMovingBitmap tomato_Grow02_D;
		CMovingBitmap tomato_Grow02_W;
		CMovingBitmap tomato_Grow03_D;
		CMovingBitmap tomato_Grow03_W;
		CMovingBitmap tomato_Mature;

		CMovingBitmap animalGrass;
		CMovingBitmap egg;
		

		// Animal Shop
		CMovingBitmap animalShop_01;
		CMovingBitmap animalShop_02;
		CMovingBitmap animalShop_03;
		CMovingBitmap animalShop_04;
		CMovingBitmap animalShop_05;
		CMovingBitmap animalShop_06;
		CMovingBitmap animalShop_07;
		CMovingBitmap animalShop_08;
		CMovingBitmap animalShop_09;
		CMovingBitmap animalShop_10;
		CMovingBitmap animalShop_11;
		CMovingBitmap animalShop_12;
		CMovingBitmap animalShop_13;
		CMovingBitmap animalShop_14;
		CMovingBitmap animalShop_15;
		CMovingBitmap animalShop_16;
		CMovingBitmap animalShop_17;
		CMovingBitmap animalShop_18;
		CMovingBitmap animalShop_19;
		CMovingBitmap animalShop_20;
		
		// ToolsMachinesShop
		CMovingBitmap toolsMachinesShop_01;
		CMovingBitmap toolsMachinesShop_02;
		CMovingBitmap toolsMachinesShop_03;
		CMovingBitmap toolsMachinesShop_04;
		CMovingBitmap toolsMachinesShop_05;
		CMovingBitmap toolsMachinesShop_06;
		CMovingBitmap toolsMachinesShop_07;
		CMovingBitmap toolsMachinesShop_08;
		CMovingBitmap toolsMachinesShop_09;
		CMovingBitmap toolsMachinesShop_10;
		CMovingBitmap toolsMachinesShop_11;
		CMovingBitmap toolsMachinesShop_12;
		CMovingBitmap toolsMachinesShop_13;
		CMovingBitmap toolsMachinesShop_14;
		CMovingBitmap toolsMachinesShop_15;
		CMovingBitmap toolsMachinesShop_16;
		CMovingBitmap toolsMachinesShop_17;
		CMovingBitmap toolsMachinesShop_18;
		CMovingBitmap toolsMachinesShop_19;
		CMovingBitmap toolsMachinesShop_20;
		CMovingBitmap toolsMachinesShop_21;
		CMovingBitmap toolsMachinesShop_22;
		CMovingBitmap toolsMachinesShop_23;

		// Food Shop
		CMovingBitmap foodShop_01;
		CMovingBitmap foodShop_02;
		CMovingBitmap foodShop_03;
		CMovingBitmap foodShop_04;
		CMovingBitmap foodShop_05;
		CMovingBitmap foodShop_06;
		CMovingBitmap foodShop_10;
		CMovingBitmap foodShop_11;
		CMovingBitmap foodShop_16;
		CMovingBitmap foodShop_17;

		// Clinic
		CMovingBitmap clinic_01;
		CMovingBitmap clinic_02;
		CMovingBitmap clinic_03;
		CMovingBitmap clinic_04;
		CMovingBitmap clinic_05;
		CMovingBitmap clinic_06;
		CMovingBitmap clinic_07;
		CMovingBitmap clinic_08;
		CMovingBitmap clinic_09;
		CMovingBitmap clinic_10;
		CMovingBitmap clinic_11;
		CMovingBitmap clinic_12;
		CMovingBitmap clinic_13;
		CMovingBitmap clinic_14;
		CMovingBitmap clinic_15;
		CMovingBitmap clinic_16;
		CMovingBitmap clinic_17;
		CMovingBitmap clinic_18;
		CMovingBitmap clinic_19;
		CMovingBitmap clinic_20;
		CMovingBitmap clinic_21;
		CMovingBitmap clinic_22;
		CMovingBitmap clinic_23;


		// Machine
		CMovingBitmap cowMachine1;
		CMovingBitmap cowMachine2;
		CMovingBitmap sheepMachine1;
		CMovingBitmap sheepMachine2;

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