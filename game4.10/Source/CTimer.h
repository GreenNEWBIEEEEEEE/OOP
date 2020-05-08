#pragma once
namespace game_framework {
	class CTimer
	{
	public:
		int year = 2000;
		int month = 1;
		int day = 1;
		int hour = 13;
		enum class Brightness {
			Morning,
			Dusk,
			Evening
		};

		enum class Season {
			Spring,
			Summer,
			Autumn,
			Winter
		};

		CTimer();
		~CTimer();
		void LoadBitmap();
		void OnShow();
		void OnMove();
		int GetYear();
		int GetMonth();
		int GetDay();
		int GetHour();
		int GetHourCounter();
		CTimer::Season GetCurrentSeason();
		void CountTime();    // �p��
		void UpdateDate();   // ��s���
		void UpdateBrightness();
		void UpdateSeason();
		int GetNumberOfDays();
	private:
		CTimer::Brightness state = CTimer::Brightness::Morning;
		CTimer::Season currentSeason = CTimer::Season::Spring;
		const int HOUR_COUNTER_MAX = 60; // onMove����2000������@�p��
		int hourCounter = 0;

		CMovingBitmap dusk;
		CMovingBitmap evening;
	};
}