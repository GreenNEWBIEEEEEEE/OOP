<<<<<<< HEAD
#pragma once
=======
#ifndef CGAMEMAP_H
#define CGAMEMAP_H

>>>>>>> e2e1e32b2e3fbb9303805f93de1773125d6ea93e

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
<<<<<<< HEAD
		CGameMap(string mapinfo_path);
=======
		CGameMap(string filePath);
>>>>>>> e2e1e32b2e3fbb9303805f93de1773125d6ea93e
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

		void Trigger(int x, int y);
	private:
		vector<string> SplitString(string& data, string delimiter);
		// 地圖格元素
		CMovingBitmap gndGrass01;
		CMovingBitmap gndDirt01;
		CMovingBitmap gndBridge01;
		CMovingBitmap gndHouseFloor01;
		CMovingBitmap gndHouseWall01;
		CAnimation gndWater01;
		

		

		// 二維資料陣列
<<<<<<< HEAD
		int row, col;
		CMapInfo **map = nullptr;

=======
		int ROW;
		int COL;
		CMapInfo **map = new CMapInfo*[ROW];
>>>>>>> e2e1e32b2e3fbb9303805f93de1773125d6ea93e

		int sx, sy; // CGameMap在screen上的(left, top)
		int gndW, gndH; // 單格大小

		//
		void CreateMapInfos(string& mapinfo_path);

	};
}
#endif