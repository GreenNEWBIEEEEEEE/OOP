#pragma once
namespace game_framework {
	class CTimer
	{
	public:
		int year = 2000;
		int month = 1;
		int day = 1;
		int hour = 8;
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
		bool IsNewDay();
		CTimer::Season GetCurrentSeason();
		void CountTime();    // �p��
		void UpdateDate();   // ��s���
		void UpdateBrightness();
		void UpdateSeason();
		int GetNumberOfDays();
		void OnKeyDown(UINT key);
		void OnKeyUp(UINT key);
	private:
		CTimer::Brightness state = CTimer::Brightness::Morning;
		CTimer::Season currentSeason = CTimer::Season::Spring;
		const int HOUR_COUNTER_MAX = 60; // onMove����2000������@�p��
		int hourCounter = 0;
		int TIME_SPEED = 1;
		CMovingBitmap dusk;
		CMovingBitmap evening;
	};
}