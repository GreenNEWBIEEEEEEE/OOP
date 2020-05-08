#include "StdAfx.h"
#include "resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include "CWeather.h"
#include "CTimer.h"
namespace game_framework
{
	CWeather::CWeather()
	{
		rain.SetDelayCount(2);
	}

	CWeather::~CWeather()
	{
	}
	
	void CWeather::ChooseWeather(CTimer* timer)
	{
		CTimer::Season currentSeason = timer->GetCurrentSeason();
		int rnd = (rand() % 100);

		if (currentSeason == CTimer::Season::Spring)
		{
			sunny = rnd < 95;             // 95%
			rainy = rnd >= 95;			  // 5%
			typhoon = false;
		}
		else if (currentSeason == CTimer::Season::Summer)
		{
			sunny = rnd < 40;             // 40%
			rainy = rnd >= 40;            // 60%
			typhoon = false;
		}
		else if (currentSeason == CTimer::Season::Autumn)
		{
			sunny = rnd < 60;             // 60%
			rainy = rnd >= 60 && rnd < 90;// 30%
			typhoon = rnd >= 90;	      // 10%
		}
		else if (currentSeason == CTimer::Season::Winter)
		{
			sunny = rnd < 90;             // 90%
			rainy = rnd >= 90;			  // 10%
			typhoon = false;	     
		}

		if (sunny)
			weatherType = WeatherType::Sunny;
		else if (rainy)
			weatherType = WeatherType::Rain;
		else if (typhoon)
			weatherType = WeatherType::Typhoon;
	}

	void CWeather::LoadBitmap()
	{
		// rain animation bitmaps
		{
			rain.AddBitmap(IDB_Test_RainMask_01, RGB(0, 0, 0));
			rain.AddBitmap(IDB_Test_RainMask_02, RGB(0, 0, 0));
			rain.AddBitmap(IDB_Test_RainMask_03, RGB(0, 0, 0));
		}

		{
			test_mask.LoadBitmap(IDB_BlackMask, RGB(255, 255, 255));
		}
	}

	void CWeather::OnMove(CTimer* timer)
	{
		if (timer->GetHour() == 8 && timer->GetHourCounter() == 0)
		{
			ChooseWeather(timer);
		}

		switch (weatherType)
		{
		case WeatherType::Rain:
			rain.OnMove();
			break;
		default:
			// Do nothing
			break;
		}
		

	}

	void CWeather::OnShow()
	{
		//test_mask.ShowBitmap();
		switch (weatherType)
		{
		case WeatherType::Rain:
			rain.OnShow();
			break;
		default:
			// Do nothing
			break;
		}
	}
}