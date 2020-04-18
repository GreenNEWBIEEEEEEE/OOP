#include "stdafx.h"
#include "resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include <string>
#include "CTool.h"

namespace game_framework {
	bool CTool::IsEnable()
	{
		return number > 0;
	}

	CTool::CTool(int toolID, int number)
	{
		this->toolID = toolID;
		this->number = number;

		switch (toolID)
		{
		case 0:			// ��
			icon = &hand;
				break;
		case 1:			// ���Y
			icon = &axe;
				break;
		case 2:			// �l�l
			icon = &hammer;
				break;
		case 3:			// �S�Y
			icon = &hoe;
				break;
		case 4:			// �ؤl�U
			icon = &seed01;
				break;
		case 5:			// �I�M
			icon = &sickle;
				break;
		case 6:			// �����
			icon = &waterer;
				break;
		default:
			break;
		}
	}
	CTool::~CTool()
	{

	}

	int CTool::GetToolID()
	{
		return toolID;
	}

	void CTool::ShowIcon(int x, int y)
	{
		icon->SetTopLeft(x, y);
		icon->ShowBitmap();
	}
	string CTool::GetInfo()
	{
		return toolName + "  *" + to_string(number);
	}
	void CTool::LoadBitmap()
	{
		hand.LoadBitmap(IDB_Axe, RGB(255, 255, 255));
		axe.LoadBitmap(IDB_Axe, RGB(255, 255, 255));
		hammer.LoadBitmap(IDB_Hammer, RGB(255, 255, 255));
		hoe.LoadBitmap(IDB_Hoe, RGB(255, 255, 255));
		seed01.LoadBitmap(IDB_Seed01, RGB(255, 255, 255));
		sickle.LoadBitmap(IDB_Sickle, RGB(255, 255, 255));
		waterer.LoadBitmap(IDB_WateringCan, RGB(255, 255, 255));
	}

}