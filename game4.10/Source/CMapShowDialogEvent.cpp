#include "stdafx.h"
#include "resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include "CPlayer.h"
#include "CGameDialog.h"
#include "CWeather.h"
#include "CMapShowDialogEvent.h"


namespace game_framework
{
	

	CMapShowDialogEvent::CMapShowDialogEvent(int eventCode)
		: CMapEvent(eventCode, ' ')
	{

	}

	CMapShowDialogEvent::~CMapShowDialogEvent()
	{
	}

	void CMapShowDialogEvent::Execute(CPlayer *p, CMapManager *mm, CGameDialog *gd, vector<CShopMenu*> sms)
	{
		//
		// 規範：
		// 對話框「內容」事件碼的範圍	，須從10000~19999
		// 數量上基本上很夠用了
		//

		switch (eventCode)
		{
		////////////////////////////////////////////////
		// MapE01
		case 10000:
		{
			gd->AddMessage("Here is your house!");
			gd->AddMessage("And you are in Town 1.");
			gd->AddMessage("Have fun!");
			gd->Enable();
			break;
		}
		case 10001:
		{
			gd->AddMessage("Here is a farm!");
			gd->AddMessage("Plant some crops, and sell them.");
			gd->Enable();
			break;
		}
		case 10002:
		{
			gd->AddMessage("Here is your cow coop !");
			gd->AddMessage("Press ENTER to the coop !");
			gd->Enable();
			break;
		}
		case 10003:
		{
			gd->AddMessage("Here is your chicken coop !");
			gd->AddMessage("Press ENTER to the coop !");
			gd->Enable();
			break;
		}
		case 10004:
		{
			gd->AddMessage("↑ To Town 1 ↑");
			gd->AddMessage("Press ENTER to Town 1 !");
			gd->Enable();
			break;
		}
		case 10005:
		{
			gd->AddMessage("This is the crop sold box.");
			gd->AddMessage("Press A to sell the crop you hold.");
			gd->Enable();
			break;
		}
		///////////////////////////////////////////////
		// MapE02
		case 10006:
		{
			CWeather* weather = mm->GetOutsideWeather();
			string today = "The weather today is " + weather->ForecastWeather() + ".";
			string tomorrow = "The weather tomorrow is " + weather->ForecastFutureWeather() + ".";
			gd->AddMessage(today);
			gd->AddMessage(tomorrow);
			gd->Enable();
			break;
		}
		case 10007:
		{
			int year = mm->GetTimer()->GetYear();
			int month = mm->GetTimer()->GetMonth();
			int day = mm->GetTimer()->GetDay();
			int hour = mm->GetTimer()->GetHour();
			CString date;
			date.Format("Today is %d / %02d / %02d.", year, month, day);
			CString time;
			time.Format("The time now is %02d : 00.", hour);
			gd->AddMessage((LPCTSTR)date);
			gd->AddMessage((LPCTSTR)time);
			gd->Enable();
			break;
		}
		case 10008:
		{
			gd->AddMessage("");
			gd->Enable();
			break;
		}
		///////////////////////////////////////////////
		// MapE03
		default:
			break;
		}
	}


}