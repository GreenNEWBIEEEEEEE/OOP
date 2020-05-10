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

	CWeather* CMapManager::GetOutsideWeather()
	{
		return maps[0]->GetWeather(); // 地圖0是戶外
	}

	void CMapManager::SetTimer(CTimer* timer)
	{
		this->timer = timer;
	}

	CTimer* CMapManager::GetTimer()
	{
		return timer;
	}

	void CMapManager::OnMove()
	{
		for (unsigned i = 0; i < maps.size(); ++i)
			maps.at(i)->OnMove(timer);
	}
	
	///
	///
	///

	void CMapManager::OnShow()
	{
		maps[selector]->OnShow(timer);
	}
	void CMapManager::OnShow_Weather()
	{
		maps[selector]->OnShow_Weather();
	}
	void CMapManager::OnShow_Timer()
	{
		maps[selector]->OnShow_Timer(timer);
	}
}


