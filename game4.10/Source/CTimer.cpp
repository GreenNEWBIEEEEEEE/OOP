#include "stdafx.h"
#include "resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include "CTimer.h"
#include "CWeather.h"

namespace game_framework {
	CTimer::CTimer(){}
	CTimer::~CTimer(){}

	void CTimer::OnMove()
	{
		CountTime();
	}

	void CTimer::OnKeyDown(UINT key)
	{
		const char KEY_B = 'B';

		if (key == KEY_B)
		{
			TIME_SPEED = 50;
		}
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
		return GetHour() == 8 && GetHourCounter() == 0 ;
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