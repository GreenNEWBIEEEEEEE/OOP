#pragma once

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
		void OnMove();
		void OnShow();
		//void ChooseWeather(CTimer* timer);

	private:
		CMovingBitmap test_mask;
		CAnimation rain;
		WeatherType weatherType = WeatherType::Rain;
	};
}
