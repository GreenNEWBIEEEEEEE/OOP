#pragma once
#include "CTimer.h"
#include <atlimage.h>

namespace game_framework {
	class CWeather
	{
	public:
		enum class WeatherType
		{
			Sunny,
			Rain,
			Typhoon,
		};

		CWeather();
		~CWeather();

		void LoadBitmap();
		void OnMove(CTimer* timer);
		void OnShow();
		void ChooseWeather(CTimer* timer);

	private:
		bool rainy = false;
		bool typhoon = false;
		bool sunny = true;
		CMovingBitmap test_mask;
		CAnimation rain;
		WeatherType weatherType = WeatherType::Rain;
	};
}
