#include "stdafx.h"
#include "resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include "CMapManager.h"

namespace game_framework {

	CMapManager::CMapManager()
	{
	}

	CMapManager::~CMapManager()
	{
		for (unsigned i = 0; i < maps.size(); ++i) {
			delete maps[i];
			maps[i] = nullptr;
		}
	}

	///
	///
	///
	void game_framework::CMapManager::AddMap(string path)
	{
		maps.push_back(new CGameMap(path));
	}

	///
	///
	///
	void game_framework::CMapManager::ChangeMap(unsigned mapID)
	{
		selector = mapID;
	}

	///
	///
	///
	CGameMap* CMapManager::GetCurrentMap() const
	{
		return maps[selector];
	}
	
	///
	///
	///
	void CMapManager::LoadBitmapAll()
	{
		for (unsigned i = 0; i < maps.size(); ++i)
			maps[i]->LoadBitmap();
	}
	
	///
	///
	///
	void CMapManager::OnShow()
	{
		maps[selector]->OnShow();
	}
}

