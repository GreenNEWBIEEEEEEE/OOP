#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CMapTransitionEvent.h"
#include "mygame.h"
namespace game_framework {
	CMapTransitionEvent::CMapTransitionEvent(int ID) : mapID(ID)
	{
	}

	void CMapTransitionEvent::Execute()
	{
		if(mapID == 2)
			CGameStateRun::mainMap = &(CGameStateRun::map2);
	}
}