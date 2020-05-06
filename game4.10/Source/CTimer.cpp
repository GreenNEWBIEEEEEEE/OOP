#include "stdafx.h"
#include "resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include "CTimer.h"

namespace game_framework {
	CTimer::CTimer(){}
	CTimer::~CTimer(){}

	void CTimer::OnMove()
	{
		CountTime();
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

	void CTimer::CountTime()
	{
		if (hourCounter < HOUR_COUNTER_MAX)
		{
			hourCounter++;
		}
		else
		{
			hourCounter = 0;
			hour += 1;
			UpdateDate();
			UpdateBrightness();
		}
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
}