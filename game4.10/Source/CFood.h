#pragma once
#include "CPlayer.h"
namespace game_framework
{

	class CFood
	{
	public:
		CFood(int foodID, int number);
		~CFood();
		bool IsEnable() const;
		void LoadBitmap();
		void ShowIcon(int x, int y);
		string GetName() const;
		string GetInfo() const;
		string GetDescribe() const;
		string GetWholeDescribe() const;
		int GetFoodID() const;
		int GetNumber() const;
		virtual void Execute(CPlayer* p) = 0;
		// ¼W´î¼Æ¶q
		void IncreaseNumber(int number);
		void DecreaseNumber(int number);


	protected:
		int foodID;
		string foodName;
		string describe;
		int number;
		CMovingBitmap appleJuice;
		CMovingBitmap orangeJuice;
		CMovingBitmap lunchBox;
		CMovingBitmap drinkBox;
		CMovingBitmap meal;
		CMovingBitmap cake;

		CMovingBitmap *icon = nullptr;
	};
}

