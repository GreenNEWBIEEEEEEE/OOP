#pragma once

#include "CGameMap.h"
#include <vector>

namespace game_framework {
	class CMapManager {
	public:
		CMapManager();
		~CMapManager();
		void AddMap(string path);
		void ChangeMap(unsigned mapID);
		CGameMap* GetCurrentMap() const;
		void LoadBitmapAll();
		void OnShow();
	private:
		unsigned selector = 0;
		std::vector<CGameMap*> maps;
	};
}