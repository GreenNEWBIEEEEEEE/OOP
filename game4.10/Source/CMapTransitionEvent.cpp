#include "stdafx.h"
<<<<<<< HEAD
#include "resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include "CPlayer.h"
#include "CGameMap.h"
#include "CMapManager.h"
#include "CMapEvent.h"
#include "CMapInfo.h"
#include "CMapTransitionEvent.h"


namespace game_framework {
	CMapTransitionEvent::CMapTransitionEvent()
		: CMapEvent(0, 0x0D)
	{
		
	}

	void CMapTransitionEvent::Execute(CPlayer *p, CMapManager * mm, CGameDialog *gd)
	{
		gd->AddMessage("Welcome to your home.");
		gd->AddMessage("This is a game dialog.");
		gd->AddMessage("Press SPACE to finish this dialog.");
		gd->Enable();

		mm->ChangeMap(1);
		p->SetX(300); p->SetY(200); // FIXME
	}
}
=======
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
>>>>>>> e2e1e32b2e3fbb9303805f93de1773125d6ea93e
