#include "StdAfx.h"
#include "resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include "CShopMenu.h"

namespace game_framework
{
	CShopMenu::CShopMenu(CPlayer * p, CGameDialog * gd, CTimer * timer)
	{
		player = p;
		this->gd = gd;
		this->timer = timer;
	}

	CShopMenu::~CShopMenu()
	{
		player = nullptr;
		gd = nullptr;
		timer = nullptr;
	}

	void CShopMenu::Enable()
	{
		enable = true;
	}

	void CShopMenu::Enable_InfoBoard()
	{
		this->enable_infoboard = true;
	}

	void CShopMenu::Disable()
	{
		enable = false;
		this->enable_infoboard = false;
	}

	void CShopMenu::Disable_InfoBoard()
	{
		this->enable_infoboard = false;
	}

	bool CShopMenu::IsEnable() const
	{
		return enable;
	}

	int CShopMenu::GetCurrentSelection() const
	{
		return goodSelector;
	}

	CTimer * CShopMenu::GetTimer() const
	{
		return timer;
	}

	void CShopMenu::LoadBitmap()
	{
		blackBG.LoadBitmap(IDB_ShopMenuBlackBG);
		infoBoardBG.LoadBitmap(IDB_DIALOG_BG_01);
		selector.LoadBitmap(IDB_PlantShopSelector, RGB(255, 255, 255));

		blackBG.SetTopLeft(0, 0);
		infoBoardBG.SetTopLeft(20, 360);
		selector.SetTopLeft(120, 230);
	}

	void CShopMenu::DrawTexts(CString text, int posX, int posY, int fontSize)
	{
		CDC *pDC = CDDraw::GetBackCDC();
		CFont f, *fp = nullptr;
		f.CreatePointFont(fontSize, "Consolas");
		fp = pDC->SelectObject(&f);
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(255, 255, 255));
		pDC->TextOut(posX, posY, text);
		pDC->SelectObject(fp);
		CDDraw::ReleaseBackCDC();
	}
}