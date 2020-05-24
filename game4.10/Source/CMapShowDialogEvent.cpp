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

	void CMapShowDialogEvent::Execute(CPlayer *p, CMapManager *mm, CGameDialog *gd, CShopMenu *sm)
	{
		//
		// 規範：
		// 對話框「內容」事件碼的範圍	，須從10001~20000
		// 數量上基本上很夠用了
		// 

		CWeather* weather = mm->GetOutsideWeather();
		string today = "The weather today is " + weather->ForecastWeather() + ".";
		string tomorrow = "The weather tomorrow is " +  weather->ForecastFutureWeather() + ".";

		switch (eventCode)
		{
		case 10001:
				gd->AddQuestion("Do you like this game?");
				gd->AddOptionResultMessage("Thank!", "Danke!");
				gd->AddOptionResultMessage("Have fun!", "Habe Spass!");
				gd->Enable();

				break;
		case 10002:
			gd->AddMessage("Press W to change tools.");
			gd->AddMessage("Press S to open backpack menu.");
			gd->AddMessage("In backpack menu. . .");
			gd->AddMessage("press A to select tool, ");
			gd->AddMessage("and press D to leave menu.");
			gd->Enable();
			break;
		case 10003:
			gd->AddMessage("Press A to Use tool.");
			gd->AddMessage("Do some agricultural work.");
			gd->AddMessage("Good luck!");
			gd->Enable();
			break;
		case 10004:
			gd->AddMessage("This is a notice board.");
			gd->Enable();
			break;
		case 10005:
			gd->AddMessage("Here is your home.");
			gd->Enable();
			break;
		case 10006:
			gd->AddMessage("Here is Plant Shop.");
			gd->AddMessage("You can buy seeds in this shop.");
			gd->AddMessage("Press H at the door to enter shop.");
			gd->Enable();
			break;
		case 10007:
			gd->AddMessage(today);
			gd->AddMessage(tomorrow);
			gd->Enable();
			break;
		case 10008:
			gd->AddMessage("This is chicken coop.");
			gd->Enable();
			break;
		case 10009:
			gd->AddMessage("This is chicken feed store box.");
			gd->AddMessage("Press A to take chicken feed.");
			gd->Enable();
			break;
		case 10010:
			gd->AddMessage("This is chicken feed box.");
			gd->AddMessage("Press A to put chicken feed.");
			gd->Enable();
			break;
		case 10011:
			gd->AddMessage("↑ Area 2");
			gd->Enable();
			break;
		case 10012:
			gd->AddMessage("↓ Area 1");
			gd->Enable();
			break;
		case 10013:
			gd->AddMessage("Here is animal shop.");
			gd->AddMessage("You can buy animals in this shop.");
			gd->AddMessage("Press H at the door to enter shop.");
			gd->Enable();
			break;
		default:
			break;
		}
	}


}