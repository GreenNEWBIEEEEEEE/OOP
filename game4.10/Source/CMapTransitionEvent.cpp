#include "stdafx.h"
#include "resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include "CPlayer.h"
#include "CGameMap.h"
#include "CMapManager.h"
#include "CMapEvent.h"
#include "CMapInfo.h"
#include "CMapTransitionEvent.h"
#include "CWeather.h"


namespace game_framework {
	CMapTransitionEvent::CMapTransitionEvent(int eventCode)
		: CMapEvent(eventCode, 0x0D)
	{
		
	}

	void CMapTransitionEvent::Execute(CPlayer *p, CMapManager *mm, CGameDialog *gd, vector<CShopMenu*> sms)
	{
		CWeather* weather = mm->GetOutsideWeather();
		string today = weather->ForecastWeather();
		//
		// �W�d�G
		// �����ഫ�u���e�v�ƥ�X���d��A���q10001~20000
		// 
		switch (eventCode)
		{
		case 20001:
			// ���a��
			mm->ChangeMap(1);
			
			// �]���ഫ���Ӫ���m�|���A�X
			// �ҥH�n�վ�a�Ϫ�screen��m�H��playery�b�a�ϤW����m
			mm->GetCurrentMap()->SetSXSY(50, 500);
			p->SetX(4 * 64);
			p->SetY(11 * 53);
			break;
		case 20002:
			if (today != "Typhoon")
			{
				mm->ChangeMap(0);
				mm->GetCurrentMap()->SetSXSY(400, 100);
				p->SetX(10 * 64);
				p->SetY(5 * 53);
			}
			else
			{
				gd->AddMessage("You can't go outside.");
				gd->AddMessage("because of typhoon.");
				gd->Enable();
			}
			break;
			// �ǥ~->����
		case 20003:
			mm->ChangeMap(2);
			mm->GetCurrentMap()->SetSXSY(50, 500);
			p->SetX(5 * 64);
			p->SetY(12 * 53);
			break;
			// ����->�ǥ~
		case 20004:
			mm->ChangeMap(0);
			mm->GetCurrentMap()->SetSXSY(950, 100);
			p->SetX(18 * 64);
			p->SetY(5 * 53);
			break;
			// �ǥ~1->�ǥ~2
		case 20005: 
			mm->ChangeMap(3);
			mm->GetCurrentMap()->SetSXSY(880, 500);
			p->SetX(17 * 64);
			p->SetY(12 * 53);
			gd->AddMessage("Area 2");
			gd->Enable();
			break;
			// �ǥ~2->�ǥ~1
		case 20006:
			mm->ChangeMap(0);
			mm->GetCurrentMap()->SetSXSY(750, -100);
			p->SetX(15 * 64);
			p->SetY(0 * 53);
			gd->AddMessage("Area 1");
			gd->Enable();
			break;
		default:
			break;
		}
	}
}
