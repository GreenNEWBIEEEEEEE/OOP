#include "stdafx.h"
#include "resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include <string>
#include "CFood.h"
#include "CFood.h"

namespace game_framework {
	CFood::CFood(int foodID, int number)
	{
		this->foodID = foodID;
		this->number = number;

		switch (foodID)
		{
		case 0:			// 手
			icon = &hand;
			break;
		case 1:			// 斧頭
			icon = &axe;
			break;
		case 2:			// 槌子
			icon = &hammer;
			break;
		case 3:			// 鋤頭
			icon = &hoe;
			break;
		case 4:			// 種子袋
			icon = &seed01;
			break;
		case 5:			// 鐮刀
			icon = &sickle;
			break;
		case 6:			// 澆水器
			icon = &waterer;
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
		hand.LoadBitmap(IDB_Axe, RGB(255, 255, 255));
		axe.LoadBitmap(IDB_Axe, RGB(255, 255, 255));
		hammer.LoadBitmap(IDB_Hammer, RGB(255, 255, 255));
		hoe.LoadBitmap(IDB_Hoe, RGB(255, 255, 255));
		seed01.LoadBitmap(IDB_Seed01, RGB(255, 255, 255));
		sickle.LoadBitmap(IDB_Sickle, RGB(255, 255, 255));
		waterer.LoadBitmap(IDB_WateringCan, RGB(255, 255, 255));
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

	string CFood::GetInfo() const
	{
		return foodName + "  *" + to_string(number);
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