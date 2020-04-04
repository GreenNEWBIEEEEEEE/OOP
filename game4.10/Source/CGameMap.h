#pragma once

namespace game_framework
{
	class CMapInfo;
	class CMapEvent;
	class CMapManager;
	class CPlayer;
	class CGameDialog;
	class CGameMap
	{
	public:
		CGameMap(string mapinfo_path);
		~CGameMap();
		void LoadBitmap();
		void OnShow();
		
		// 提供玩家或角色判斷即將移動的位置是否能夠行走, 也就是是否有障礙物
		// 因此, 玩家或角色的Class中需要做移動(OnMove)的，請將CGameMap當作參數傳入(詳見老師的講義MapIntroduction)
		bool IsEmpty(int x, int y) const;

		//
		void triggerMapEvents(UINT key, CPlayer *p, CMapManager *mm, CGameDialog *gd);

		
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
	private:
		// 地圖格元素
		/*
		CMovingBitmap gndGrass01;
		CMovingBitmap gndDirt01;
		CMovingBitmap gndBush01;
		CMovingBitmap gndNoticeBoard01;
		CMovingBitmap gndBridge01;
		CMovingBitmap gndHouseFloor01;
		CMovingBitmap gndHouseWall01;
		CMovingBitmap gndWall01;
		CMovingBitmap gndStone01;
		CAnimation gndWater01;
		*/
		// gnd
		CMovingBitmap sand;
		CMovingBitmap plantSoil;
		CMovingBitmap grass;
		CMovingBitmap soil;
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

		

		// 二維資料陣列
		int row, col;
		CMapInfo **map = nullptr;


		int sx, sy; // CGameMap在screen上的(left, top)
		int gndW, gndH; // 單格大小

		//
		void CreateMapInfos(string& mapinfo_path);

	};
}