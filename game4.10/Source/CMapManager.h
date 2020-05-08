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
		CGameMap* GetCurrentMap() const;
		void LoadBitmapAll();
		void OnMove();
		void OnShow();
		void OnShow_Weather();
	private:
		unsigned selector = 0;
		std::vector<CGameMap*> maps;
	};
}