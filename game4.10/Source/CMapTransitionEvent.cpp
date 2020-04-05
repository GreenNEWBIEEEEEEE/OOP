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
#include "CMapTransitionEvent.h"


namespace game_framework {
	CMapTransitionEvent::CMapTransitionEvent(int eventCode)
		: CMapEvent(eventCode, 0x0D)
	{
		
	}

	void CMapTransitionEvent::Execute(CPlayer *p, CMapManager * mm, CGameDialog *gd)
	{
		switch (eventCode)
		{
		case 20001:
			mm->ChangeMap(1);
			mm->GetCurrentMap()->SetSXSY(200, 500);
			p->SetX(7 * 64);
			p->SetY(12 * 53);
			break;
		case 20002:
			mm->ChangeMap(0);
			mm->GetCurrentMap()->SetSXSY(400, 100);
			p->SetX(10 * 64);
			p->SetY(5 * 53);
			break;
		default:
			break;
		}
	}
}
