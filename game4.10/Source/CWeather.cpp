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
	
	string CWeather::ForecastWeather()
	{
		if (weatherType == WeatherType::Sunny)
			return "Sunny";
		else if (weatherType == WeatherType::Rain)
			return "Rainy";
		else
			return "Typhoon";
	}

	string CWeather::ForecastFutureWeather()
	{
		
		if (mistake)
		{
			if (nextSunny)
			{
				return "Rainy";
			}

			else if (nextRainy)
			{
				return "Typhoon";
			}

			else
			{
				return "Typhoon";
			}
		}
		else
		{
			if (nextDayWeatherType == WeatherType::Sunny)
				return "Sunny";
			else if (nextDayWeatherType == WeatherType::Rain)
				return "Rainy";
			else
				return "Typhoon";
		}
		
	}

	void CWeather::ChooseWeather(CTimer* timer)
	{
		CTimer::Season currentSeason = timer->GetCurrentSeason();
		int rnd = (rand() % 100);
		mistake = (rand() % 100) >= 95;		// 隔天天氣預報誤報機率5%
											// ChooseWeather一天觸發一次，所以誤報會是一整天

		if (currentSeason == CTimer::Season::Spring)
		{
			nextSunny = rnd < 95;             // 95%
			nextRainy = rnd >= 95;			  // 5%
			nextTyphoon = false;
		}
		else if (currentSeason == CTimer::Season::Summer)
		{
			nextSunny = rnd < 40;             // 40%
			nextRainy = rnd >= 40;            // 60%
			nextTyphoon = false;
		}
		else if (currentSeason == CTimer::Season::Autumn)
		{
			nextSunny = rnd < 60;             // 60%
			nextRainy = rnd >= 60 && rnd < 90;// 30%
			nextTyphoon = rnd >= 90;	      // 10%
		}
		else if (currentSeason == CTimer::Season::Winter)
		{
			nextSunny = rnd < 90;             // 90%
			nextRainy = rnd >= 90;			  // 10%
			nextTyphoon = false;	     
		}

		/*
		if (sunny)
			weatherType = WeatherType::Sunny;
		else if (rainy)
			weatherType = WeatherType::Rain;
		else if (typhoon)
			weatherType = WeatherType::Typhoon;
		*/
		weatherType = nextDayWeatherType;

		if (nextSunny)
			nextDayWeatherType = WeatherType::Sunny;
		else if (nextRainy)
			nextDayWeatherType = WeatherType::Rain;
		else if (nextTyphoon)
			nextDayWeatherType = WeatherType::Typhoon;
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
		if (timer->IsNewDay())
		{
			TRACE("\nTRIGGER CHOOSE WEATHER\n");
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