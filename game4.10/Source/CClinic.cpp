#include "StdAfx.h"
#include "resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include "CClinic.h"

namespace game_framework
{
	CClinic::CClinic(CPlayer * p, CGameDialog * gd, CTimer * timer)
		: CShopMenu(p, gd, timer)
	{
	}
	
	void CClinic::LoadBitmap()
	{
		CShopMenu::LoadBitmap();
		background.LoadBitmap(IDB_ToolsMachinesShopBG);
		background.SetTopLeft(0, 0);
	}

	void CClinic::OnKeyDown(UINT key)
	{

	}
	
	void CClinic::OnMove()
	{

	}

	void CClinic::OnShow()
	{

	}
}