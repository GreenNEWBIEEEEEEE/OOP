#include "stdafx.h"
#include "resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include "CMapSleepEvent.h"
#include "CGameDialog.h"
#include "CMapManager.h"
#include "CAnimal.h"
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

		// 因為轉換後原來的位置會不適合
		// 所以要調整地圖的screen位置以及playery在地圖上的位置
		mm->GetCurrentMap()->SetSXSY(0, 200);
		p->SetX(2 * 64);
		p->SetY(7 * 53);
	}

	void CMapSleepEvent::Execute(CPlayer *p, CMapManager *mm, CGameDialog *gd, vector<CShopMenu*> sms)
	{
		CAnimal* pickUpAnimal = p->GetPickUpAnimal();
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
			if (p->GetCurrentMoveState() != CPlayer::MoveState::NormalMove)
			{
				if (pickUpAnimal != nullptr)
				{
					pickUpAnimal->SetPickUp(false);
					pickUpAnimal->Reset();
					pickUpAnimal = nullptr;
				}
				p->ChangeMoveState(CPlayer::MoveState::NormalMove);
			}
			gd->Enable();
			break;
		case 30002:
			gd->SetCallback(&ChangeToNewDay, mm->GetTimer(), mm->GetOutsideWeather());
			p->SetSickPoint(0);
			gd->AddMessage("I'm not feeling well today. ");
			gd->AddMessage("I decided to sleep.");
			if (p->GetCurrentMoveState() != CPlayer::MoveState::NormalMove)
			{
				if (pickUpAnimal != nullptr)
				{
					pickUpAnimal->SetPickUp(false);
					pickUpAnimal->Reset();
					pickUpAnimal = nullptr;
				}
				p->ChangeMoveState(CPlayer::MoveState::NormalMove);
			}
			gd->Enable();
			break;
		default:
			break;
		}
	}


}