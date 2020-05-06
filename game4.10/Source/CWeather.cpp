#include "StdAfx.h"
#include "resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include "CWeather.h"

namespace game_framework
{
	CWeather::CWeather()
	{
		rain.SetDelayCount(2);
	}

	CWeather::~CWeather()
	{
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

	void CWeather::OnMove()
	{
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