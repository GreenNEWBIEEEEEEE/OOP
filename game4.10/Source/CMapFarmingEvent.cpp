#include "stdafx.h"
#include "resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include "CPlayer.h"
#include "CGameMap.h"
#include "CMapManager.h"
#include "CMapEvent.h"
#include "CMapInfo.h"
#include "CMapFarmingEvent.h"

namespace game_framework
{
	CMapFarmingEvent::CMapFarmingEvent(int eventCode = 1, UINT keyCode = 'A')
		: CMapEvent(eventCode, keyCode)
	{

	}

	CMapFarmingEvent::~CMapFarmingEvent()
	{

	}

	void CMapFarmingEvent::Execute(CPlayer *p, CMapManager *mm, CGameDialog *gd)
	{

	}

	int CMapFarmingEvent::getEventID() const
	{
		return CMapEvent::getEventID();
	}
	UINT CMapFarmingEvent::getKeyCode() const
	{
		return CMapEvent::getKeyCode();
	}
}