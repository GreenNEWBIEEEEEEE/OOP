#include "stdafx.h"
#include "resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include <string>
#include "CPlayer.h"
#include "CFood.h"

namespace game_framework {
	CFood::CFood(int foodID, int number)
	{
		this->foodID = foodID;
		this->number = number;

		switch (foodID)
		{
		case 0:			// appleJuice
			icon = &appleJuice;
			foodName = "AppleJuice";
			describe = "+ 15 HP";
			break;
		case 1:			// cake
			icon = &cake;
			foodName = "Cake";
			describe = "+ 10 HP";
			break;
		case 2:			// drinkBox
			icon = &drinkBox;
			foodName = "DrinkBox";
			describe = "+ 20 HP";
			break;
		case 3:			// lunchBox
			icon = &lunchBox;
			foodName = "LunchBox";
			describe = "+ 25 HP";
			break;
		case 4:			// meal
			icon = &meal;
			foodName = "Meal";
			describe = "+ 20 HP";
			break;
		case 5:			// orangeJuice
			icon = &orangeJuice;
			foodName = "OrangeJuice";
			describe = "+ 15 HP";
			break;
		default:
			break;
		}
	}

	CFood::~CFood()
	{

	}

	void CFood::LoadBitmap()
	{
		appleJuice.LoadBitmap(IDB_AppleJuice, RGB(255, 255, 255));
		orangeJuice.LoadBitmap(IDB_OrangeJuice, RGB(255, 255, 255));
		meal.LoadBitmap(IDB_Meal, RGB(255, 255, 255));
		lunchBox.LoadBitmap(IDB_LunchBox, RGB(255, 255, 255));
		drinkBox.LoadBitmap(IDB_DrinkBox, RGB(255, 255, 255));
		cake.LoadBitmap(IDB_Cake, RGB(255, 255, 255));
	}

	bool CFood::IsEnable() const
	{
		return number > 0;
	}

	int CFood::GetFoodID() const
	{
		return foodID;
	}

	int CFood::GetNumber() const
	{
		return this->number;
	}

	void CFood::ShowIcon(int x, int y)
	{
		icon->SetTopLeft(x, y);
		icon->ShowBitmap();
	}

	string CFood::GetName() const
	{
		return foodName;
	}

	string CFood::GetInfo() const
	{
		return foodName + "  *" + to_string(number);
	}

	string CFood::GetDescribe() const
	{
		return describe;
	}

	string CFood::GetWholeDescribe() const
	{
		return foodName + " " + describe;
	}

	void CFood::IncreaseNumber(int number)
	{
		if (number > 0)
		{
			this->number += number;
		}
	}

	void CFood::DecreaseNumber(int number)
	{
		if (this->number >= number)
		{
			this->number -= number;
		}
	}



}