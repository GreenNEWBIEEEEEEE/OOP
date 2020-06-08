#include "stdafx.h"
#include "resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include "CTimer.h"
#include "CWeather.h"
#include "CPlayer.h"
#include "CGameDialog.h"
#include "CShopMenu.h"
#include "CMapManager.h"
#include "CMapEvent.h"
#include "CMapTransitionEvent.h"
#include "CMapShowDialogEvent.h"
#include "CPlantShopMenu.h"
#include "CMapSleepEvent.h"
#include "CBackpackMenu.h"

namespace game_framework {
	CTimer::CTimer(){}
	CTimer::~CTimer(){}

	void CTimer::OnMove(CWeather* weather, CTimer* timer, CPlayer *p, CMapManager *mm, CGameDialog *gd, vector<CShopMenu*> sms, CBackpackMenu *bpm)
	{
		CountTime();
		if (hour == 23 && hourCounter == HOUR_COUNTER_MAX - 1)	// 太晚，強制遣返
		{
			// 先把目前的所有dialog 商店都disable
			gd->Disable();
			((CPlantShopMenu*)sms.at(0))->Disable();
			bpm->Disable();
	
			SetTimerSpeed(0);
			ForceToRepatriate(weather, timer, p, mm, gd, sms);
		}
		if (hour == 8 && hourCounter == 3)				// 生病，強制睡眠
		{												// 觸發時間和颱風觸發時間不同，如果相同會有bug
			if (p->GetSickPoint() > 200)
			{
				gd->Disable();
				((CPlantShopMenu*)sms.at(0))->Disable();
				bpm->Disable();

				SetTimerSpeed(0);
				ForceToRest(weather, timer, p, mm, gd, sms);
			}
			
		}
	}

	void CTimer::OnKeyDown(UINT key)
	{
		const char KEY_B = 'B';

		if (key == KEY_B)
		{
			TIME_SPEED = 50;
		}
	}

	void CTimer::ForceToRepatriate(CWeather* weather, CTimer* timer, CPlayer *p, CMapManager *mm, CGameDialog *gd, vector<CShopMenu*> sms)
	{
		CMapSleepEvent* toHome = new CMapSleepEvent(30001); // 時間太晚，強制睡眠
		toHome->Execute(p, mm, gd, sms);
		delete toHome;
	}

	void CTimer::ForceToRest(CWeather* weather, CTimer* timer, CPlayer *p, CMapManager *mm, CGameDialog *gd, vector<CShopMenu*> sms)
	{
		CMapSleepEvent* toHome = new CMapSleepEvent(30002); // 淋太多雨，強制睡眠
		toHome->Execute(p, mm, gd, sms);
		delete toHome;
	}

	void CTimer::OnKeyUp(UINT key)
	{
		const char KEY_B = 'B';

		if (key == KEY_B)
		{
			TIME_SPEED = 1;
		}
	}

	void CTimer::UpdateBrightness()
	{
		if (hour >= 8 && hour <= 16)
			state = CTimer::Brightness::Morning;
		else if (hour >= 17 && hour <= 18)
			state = CTimer::Brightness::Dusk;
		else
			state = CTimer::Brightness::Evening;
	}

	CTimer::Season CTimer::GetCurrentSeason()
	{
		return currentSeason;
	}

	void CTimer::UpdateSeason()
	{
		if (month >= 1 && month <= 3)
			currentSeason = CTimer::Season::Spring;
		else if (month >= 4 && month <= 6)
			currentSeason = CTimer::Season::Summer;
		else if (month >= 7 && month <= 9)
			currentSeason = CTimer::Season::Autumn;
		else
			currentSeason = CTimer::Season::Winter;
	}

	void CTimer::ChangeToNewDay(CWeather* weather, CTimer* timer)
	{
		hourCounter = 0;
		hour = 8;
		day += 1;
		UpdateDate();
		UpdateBrightness();
		UpdateSeason();
		weather->ChooseWeather(timer);
	}

	void CTimer::SetTimerSpeed(int speed)
	{
		TIME_SPEED = speed;
	}

	void CTimer::LoadBitmap()
	{
		dusk.LoadBitmap(IDB_OrangeMask, RGB(255, 157, 78));
		evening.LoadBitmap(IDB_BlackMask, RGB(255, 255, 255));
	}

	void CTimer::CountTime()
	{
		if (hourCounter < HOUR_COUNTER_MAX)
		{
			hourCounter += TIME_SPEED;
		}
		else
		{
			hourCounter = 0;
			hour += 1;
			UpdateDate();
			UpdateBrightness();
			UpdateSeason();
		}
	}
	
	bool CTimer::IsNewDay()
	{
		return hour == 8 && hourCounter == 2 ;
	}

	int CTimer::GetNumberOfDays()
	{
		if (month == 2)
		{
			if ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0))
				return 29;
			else
				return 28;
		}
		else if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
			return 31;
		else
			return 30;
	}

	void CTimer::UpdateDate()
	{
		if (hour >= 24)
		{
			hourCounter = 0;
			hour = 8;
			day += 1;
		}

		if (month > GetNumberOfDays())
		{
			day = 1;
			month += 1;
		}

		if (month > 12)
		{
			month = 1;
			year += 1;
		}
	}

	void CTimer::OnShow()
	{
		if (state == CTimer::Brightness::Dusk)
		{
			dusk.SetTopLeft(0, 0);
			dusk.ShowBitmap();
		}
		else if (state == CTimer::Brightness::Evening)
		{
			dusk.SetTopLeft(0, 0);
			evening.ShowBitmap();
		}
	}

	int CTimer::GetYear()
	{
		return year;
	}

	int CTimer::GetMonth()
	{
		return month;
	}

	int CTimer::GetDay()
	{
		return day;
	}

	int CTimer::GetHour()
	{
		return hour;
	}

	int CTimer::GetHourCounter()
	{
		return hourCounter;
	}
}