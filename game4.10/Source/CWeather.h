#pragma once

#include <atlimage.h>

namespace game_framework {
	class CTimer;
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
		string ForecastWeather();
		string ForecastFutureWeather();
	private:
		bool mistake = false; // 隔天天氣預報誤報

		bool nextRainy = false;
		bool nextTyphoon = false;
		bool nextSunny = true;
		CMovingBitmap test_mask;
		CAnimation rain;
		WeatherType weatherType = WeatherType::Rain;
		WeatherType nextDayWeatherType = WeatherType::Sunny;
	};
}
