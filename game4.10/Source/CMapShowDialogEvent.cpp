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
		// 對話框「內容」事件碼的範圍	，須從10001~20000
		// 數量上基本上很夠用了
		// 

		CWeather* weather = mm->GetOutsideWeather();
		string today = "The weather today is " + weather->ForecastWeather() + ".";
		string tomorrow = "The weather tomorrow is " +  weather->ForecastFutureWeather() + ".";

		switch (eventCode)
		{
		case 10007:
			gd->AddMessage(today);
			gd->AddMessage(tomorrow);
			gd->Enable();
			break;
		default:
			break;
		}
	}


}