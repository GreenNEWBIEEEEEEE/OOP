#include "stdafx.h"
#include "resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include "CMapSleepEvent.h"
#include "CGameDialog.h"
#include "CMapManager.h"


namespace game_framework
{
	CMapSleepEvent::CMapSleepEvent(int eventCode)
		:CMapEvent(eventCode, ' ')
	{

	}

	void ChangeToNewDay(CGameDialog::DialogOptionsResult result, CTimer* timer, CWeather* weather)
	{
		if (result == CGameDialog::DialogOptionsResult::Yes)
		{
			timer->ChangeToNewDay(weather, timer);
		}
	}

	void CMapSleepEvent::Execute(CPlayer *p, CMapManager *mm, CGameDialog *gd, CShopMenu *sm)
	{
		switch (eventCode)
		{
		case 30000:
			gd->SetCallback(&ChangeToNewDay, mm->GetTimer(), mm->GetOutsideWeather());
			gd->AddQuestion("Do you want to sleep 'til tomorrow?");
			gd->Enable();
			break;
		case 30001:
			//gd->SetCallback(&ChangeToNewDay);
			//gd->AddQuestion("Do you want to sleep 'til tomorrow?");
			//gd->Enable();
			break;
		default:
			break;
		}
	}


}