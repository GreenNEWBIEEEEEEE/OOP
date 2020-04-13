#include "stdafx.h"
#include "resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
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

	}
	CTool::~CTool()
	{

	}

	void CTool::LoadBitmap()
	{
		//TODO:���JIcon��
		switch (toolID)
		{
		case 0:			// ��
			break;
		case 1:			// ���Y
			break;
		case 2:			// �l�l
			break;
		case 3:			// �S�Y
			break;
		case 4:			// �ؤl�U
			break;
		case 5:			// �I�M
			break;
		case 6:			// �����
			break;
		default:
			break;
		}
	}

}