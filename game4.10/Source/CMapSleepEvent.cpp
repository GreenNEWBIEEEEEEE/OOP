#include "stdafx.h"
#include "resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include "CMapSleepEvent.h"
#include "CGameDialog.h"
#include "CMapManager.h"
#include "CPlayer.h"


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
			timer->SetTimerSpeed(1);
		}
	}

	void ChangeMapToHome(CMapManager* mm, CPlayer* p)
	{
		mm->ChangeMap(1);

		// �]���ഫ���Ӫ���m�|���A�X
		// �ҥH�n�վ�a�Ϫ�screen��m�H��playery�b�a�ϤW����m
		mm->GetCurrentMap()->SetSXSY(0, 200);
		p->SetX(2 * 64);
		p->SetY(7 * 53);
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
			gd->SetCallback(&ChangeMapToHome, mm, p);
			gd->SetCallback(&ChangeToNewDay, mm->GetTimer(), mm->GetOutsideWeather());
			gd->AddMessage("Now it's 12:00 a.m.");
			gd->AddMessage("We have to force you to go home.");
			gd->Enable();
			break;
		default:
			break;
		}
	}


}