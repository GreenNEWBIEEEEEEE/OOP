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
#include "CWeather.h"


namespace game_framework {
	CMapTransitionEvent::CMapTransitionEvent(int eventCode)
		: CMapEvent(eventCode, 0x0D)
	{
		
	}

	void CMapTransitionEvent::Execute(CPlayer *p, CMapManager *mm, CGameDialog *gd, vector<CShopMenu*> sms)
	{
		CWeather* weather = mm->GetOutsideWeather();
		string today = weather->ForecastWeather();
		//
		// Event Code規範：
		// 場景轉換「內容」事件碼的範圍，須從20000~29999
		// 
		switch (eventCode)
		{
		case 20001: // From Town 1 to player's house
		{
			// 換地圖
			mm->ChangeMap(1);

			// 因為轉換後原來的位置會不適合
			// 所以要調整地圖的screen位置以及playery在地圖上的位置
			mm->GetCurrentMap()->SetSXSY(50, 500);
			p->SetX(4 * 64);
			p->SetY(11 * 53);
			break;
		}
		case 20002: // From player's house to Town 1
		{
			if (today != "Typhoon")
			{
				mm->ChangeMap(0);
				mm->GetCurrentMap()->SetSXSY(400, 100);
				p->SetX(10 * 64);
				p->SetY(5 * 53);
			}
			else
			{
				gd->AddMessage("You can't go outside.");
				gd->AddMessage("because of typhoon.");
				gd->Enable();
			}
			break;
		}
		case 20003: // From Town 1 to chicken coop
		{
			mm->ChangeMap(2);
			mm->GetCurrentMap()->SetSXSY(50, 500);
			p->SetX(5 * 64);
			p->SetY(12 * 53);
			break;
		}
		case 20004: // From chicken coop to Town 1
		{
			mm->ChangeMap(0);
			mm->GetCurrentMap()->SetSXSY(950, 100);
			p->SetX(18 * 64);
			p->SetY(5 * 53);
			break;
		}
		case 20005: // From Town 1 to Town 2
		{
			string weatherOfTown2 = mm->GetMapWeather(3)->ForecastWeather();
			if (weatherOfTown2 != "Typhoon")
			{
				mm->ChangeMap(3);
				mm->GetCurrentMap()->SetSXSY(880, 500);
				p->SetX(17 * 64);
				p->SetY(12 * 53);
				gd->AddMessage("Welcome to Town 2 !");
				gd->Enable();
			}
			else
			{
				gd->AddMessage("You can't enter Town 2.");
				gd->AddMessage("because of typhoon.");
				gd->Enable();
			}
			break;
		}
		case 20006: // From Town 2 to Town 1
		{
			mm->ChangeMap(0);
			mm->GetCurrentMap()->SetSXSY(750, -100);
			p->SetX(15 * 64);
			p->SetY(0 * 53);
			gd->AddMessage("Welcome to Town 1 !");
			gd->Enable();
			break;
		}
		case 20007: // From Town 1 to cow coop
		{
			mm->ChangeMap(4);
			mm->GetCurrentMap()->SetSXSY(50, 500);
			p->SetX(5 * 64);
			p->SetY(12 * 53);
			break;
		}
		case 20008: // From cow coop to Town 1
		{
			mm->ChangeMap(0);
			mm->GetCurrentMap()->SetSXSY(950, 500);
			p->SetX(18 * 64);
			p->SetY(11 * 53);
			break;
		}
		case 20009: // From Town 2 to Town 3
		{
			string weatherOfTown3 = mm->GetMapWeather(5)->ForecastWeather();
			if (weatherOfTown3 != "Typhoon")
			{
				mm->ChangeMap(5);
				mm->GetCurrentMap()->SetSXSY(400, 500);
				p->SetX(10 * 64);
				p->SetY(12 * 53);
				gd->AddMessage("Welcome to Town 3 !");
				gd->Enable();
			}
			else
			{
				gd->AddMessage("You can't enter Town 3.");
				gd->AddMessage("because of typhoon.");
				gd->Enable();
			}
			
			break;
		}
		case 20010: // From Town 3 to Town 2
		{
			mm->ChangeMap(3);
			mm->GetCurrentMap()->SetSXSY(500, -145);
			p->SetX(11 * 64);
			p->SetY(0 * 53);
			gd->AddMessage("Welcome to Town 2 !");
			gd->Enable();
			break;
		}
		default: break;
		}
	}
}
