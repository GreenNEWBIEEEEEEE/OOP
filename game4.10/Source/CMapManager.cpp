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
	void game_framework::CMapManager::AddMap(string path, bool hasWeather)
	{
		maps.push_back(new CGameMap(path, hasWeather));
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

	void CMapManager::OnMove()
	{
		for (unsigned i = 0; i < maps.size(); ++i)
			maps.at(i)->OnMove();
	}
	
	///
	///
	///
	void CMapManager::OnShow()
	{
		maps[selector]->OnShow();
	}
	void CMapManager::OnShow_Weather()
	{
		maps[selector]->OnShow_Weather();
	}
}


