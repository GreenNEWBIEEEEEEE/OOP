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

	void CMapTransitionEvent::Execute(CPlayer *p, CMapManager *mm, CGameDialog *gd, CShopMenu *sm)
	{
		CWeather* weather = mm->GetOutsideWeather();
		string today = weather->ForecastWeather();
		//
		// 規範：
		// 場景轉換「內容」事件碼的範圍，須從10001~20000
		// 
		switch (eventCode)
		{
		case 20001:
			// 換地圖
			mm->ChangeMap(1);
			
			// 因為轉換後原來的位置會不適合
			// 所以要調整地圖的screen位置以及playery在地圖上的位置
			mm->GetCurrentMap()->SetSXSY(50, 500);
			p->SetX(4 * 64);
			p->SetY(11 * 53);
			break;
		case 20002:
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
		default:
			break;
		}
	}
}
