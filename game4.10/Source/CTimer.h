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

		CTimer();
		~CTimer();
		void OnShow();
		void OnMove();
		void CountTime();    // 計數
		void UpdateDate();   // 更新日期
		void UpdateBrightness();
		int GetNumberOfDays();
	private:
		CTimer::Brightness state = CTimer::Brightness::Morning;
		const int HOUR_COUNTER_MAX = 2000; // onMove執行2000次等於一小時
		int hourCounter = 0;
	};
}