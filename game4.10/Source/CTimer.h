#pragma once

namespace game_framework {
	class CWeather;
	class CPlayer;
	class CMapManager;
	class CGameDialog;
	class CShopMenu;
	class CBackpackMenu;
	class CTimer
	{
	public:
		int year = 2020;	
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

		void OnMove(
			CWeather* weather, 
			CTimer* timer, 
			CPlayer *p, 
			CMapManager *mm, 
			CGameDialog *gd, 
			vector<CShopMenu*> sms,
			CBackpackMenu *bpm);

		int GetYear() const;
		int GetMonth() const;
		int GetDay() const;
		int GetHour() const;
		int GetHourCounter() const;
		CTimer::Season GetSeason() const;
		void SetTimerSpeed(int speed);
		void ChangeToNewDay(CWeather* weather, CTimer* timer);
		bool IsNewDay();
		CTimer::Season GetCurrentSeason();
		void CountTime();    // �p��
		void UpdateDate();   // ��s���
		void UpdateBrightness();
		void UpdateSeason();
		void ForceToRepatriate(
			CWeather* weather, 
			CTimer* timer, 
			CPlayer *p, 
			CMapManager *mm, 
			CGameDialog *gd, 
			vector<CShopMenu*> sms); // �b�]12�I�j���^�a

		void ForceToRest(
			CWeather* weather,
			CTimer* timer,
			CPlayer *p,
			CMapManager *mm,
			CGameDialog *gd,
			vector<CShopMenu*> sms); // �O�B�Ӧh�A�j��h�Τ@��

		int GetNumberOfDays();
		void OnKeyDown(UINT key);
		void OnKeyUp(UINT key);
	private:
		CTimer::Brightness state = CTimer::Brightness::Morning;
		CTimer::Season currentSeason = CTimer::Season::Spring;
		const int HOUR_COUNTER_MAX = 700; // onMove����2000������@�p��
		int hourCounter = 5;
		int TIME_SPEED = 1;
		CMovingBitmap dusk;
		CMovingBitmap evening;
	};
}