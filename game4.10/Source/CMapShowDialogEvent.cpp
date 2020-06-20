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
			gd->AddMessage("↑ To Town 2 ↑");
			gd->AddMessage("Press ENTER to Town 2 !");
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
			gd->AddMessage("Here is your house.");
			gd->AddMessage("Go to the kitchen, ");
			gd->AddMessage("Press SPACE to select food to eat.");
			gd->AddMessage("There are a clock and a calendar, ");
			gd->AddMessage("you can view the date and the time.");
			gd->AddMessage("There is a TV, ");
			gd->AddMessage("you can watch the weather forecast.");
			gd->AddMessage("There is a bed, ");
			gd->AddMessage("you can sleep until 8:00 A.M.");
			gd->Enable();
			break;
		}
		///////////////////////////////////////////////
		// MapE03
		case 10009:
		{
			gd->AddMessage("This is the egg sold box.");
			gd->AddMessage("Press A to sell the egg you hold.");
			gd->Enable();
			break;
		}
		case 10010:
		{
			gd->AddMessage("This is the feed storage box.");
			gd->AddMessage("Press A to get a feed.");
			gd->Enable();
			break;
		}
		case 10011:
		{
			gd->AddMessage("This is the feed box.");
			gd->AddMessage("Press A to place feed.");
			gd->Enable();
			break;
		}
		///////////////////////////////////////////////
		// MapE04
		case 10014:
		{
			gd->AddMessage("↓ To Town 1 ↓");
			gd->AddMessage("Press ENTER to Town 1 !");
			gd->Enable();
			break;
		}
		case 10015:
		{
			gd->AddMessage("This is the animal shop.");
			gd->AddMessage("You can buy chicken and cow in here.");
			gd->AddMessage("Press ENTER to enter the shop.");
			gd->Enable();
			break;
		}
		case 10016:
		{
			gd->AddMessage("↑ To Town 3 ↑");
			gd->AddMessage("Press ENTER to Town 3 !");
			gd->Enable();
			break;
		}
		case 10017:
		{
			gd->AddMessage("This is the plant shop.");
			gd->AddMessage("You can buy some seeds in here.");
			gd->AddMessage("Press ENTER to enter the shop.");
			gd->Enable();
			break;
		}
		///////////////////////////////////////////////
		// MapE05
		case 10012:
		{
			gd->AddMessage("This is the dairy products sold box.");
			gd->AddMessage("Press A to sell the dairy product you hold.");
			gd->AddMessage("You can sell milk, cheese and butter.");
			gd->Enable();
			break;
		}
		case 10013:
		{
			gd->AddMessage("These are machines for making cheese ... and butter.");
			gd->AddMessage("and butter.");
			gd->AddMessage("Press A to make cheese and butter.");
			gd->Enable();
			break;
		}
		///////////////////////////////////////////////
		// MapE06
		case 10018:
		{
			gd->AddMessage("↓ To Town 2 ↓");
			gd->AddMessage("Press ENTER to Town 2 !");
			gd->Enable();
			break;
		}
		case 10019:
		{
			gd->AddMessage("This is the food shop.");
			gd->AddMessage("Buy some food here.");
			gd->AddMessage("Eating food will increase your HP.");
			gd->AddMessage("Press ENTER to enter the shop.");
			gd->Enable();
			break;
		}
		case 10020:
		{
			gd->AddMessage("This is the clinic.");
			gd->AddMessage("Press ENTER to enter the clinic.");
			gd->Enable();
			break;
		}
		default:
			break;
		}
	}


}