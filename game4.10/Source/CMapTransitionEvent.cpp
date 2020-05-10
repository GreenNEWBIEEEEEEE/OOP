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


namespace game_framework {
	CMapTransitionEvent::CMapTransitionEvent(int eventCode)
		: CMapEvent(eventCode, 0x0D)
	{
		
	}

	void CMapTransitionEvent::Execute(CPlayer *p, CMapManager *mm, CGameDialog *gd, CShopMenu *sm)
	{
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
		default:
			break;
		}
	}
}
