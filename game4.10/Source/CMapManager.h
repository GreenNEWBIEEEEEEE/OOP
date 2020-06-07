#pragma once

#include "CGameMap.h"
#include "CTimer.h"
#include <vector>

namespace game_framework {
	class CMapManager {
	public:
		CMapManager();
		~CMapManager();
		void AddMap(string path, bool hasWeather);
		void ChangeMap(unsigned mapID);
		CWeather* GetOutsideWeather();
		CGameMap* GetChickenCoop(); // 拿雞舍的地圖
		CGameMap* GetCowCoop(); // 拿牛舍的地圖
		CGameMap* GetCurrentMap() const;
		void LoadBitmapAll();
		void OnMove();
		void OnShow();
		void OnShow_Weather();
		void OnShow_Timer();
		void SetTimer(CTimer* timer);
		CTimer* GetTimer();
	private:
		unsigned selector = 0;
		CTimer* timer;
		std::vector<CGameMap*> maps;
	};
}