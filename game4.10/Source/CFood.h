#pragma once
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
		string GetInfo() const;
		int GetFoodID() const;
		int GetNumber() const;
		virtual void Execute() = 0;
		// ¼W´î¼Æ¶q
		void IncreaseNumber(int number);
		void DecreaseNumber(int number);


	protected:
		int foodID;
		string foodName;
		int number;
		CMovingBitmap hoe;
		CMovingBitmap hand;
		CMovingBitmap axe;
		CMovingBitmap seed01;
		CMovingBitmap waterer;
		CMovingBitmap sickle;
		CMovingBitmap hammer;

		CMovingBitmap *icon = nullptr;
	};
}

