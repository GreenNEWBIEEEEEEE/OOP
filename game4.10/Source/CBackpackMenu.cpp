#include "StdAfx.h"
#include "resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include "CPlayer.h"
#include "CTool.h"
#include "CTimer.h"
#include "CBackpackMenu.h"
#include <iostream>

namespace game_framework {

	CBackpackMenu::CBackpackMenu()
	{
		enable = false;
	}

	void CBackpackMenu::SetTimer(CTimer* timer)
	{
		this->timer = timer;
	}

	void CBackpackMenu::SetBackpack(vector<CTool*>* playerBackpack)
	{
		this->playerBackpack = playerBackpack;
	}
	CBackpackMenu::~CBackpackMenu() {}


	void CBackpackMenu::Enable()
	{
		TRACE("\n Backpack Menu is enable now. \n");
		enable = true;
	}

	void CBackpackMenu::Disable()
	{
		enable = false;
		TRACE("\n Backpack Menu is disable now. \n");
	}

	bool CBackpackMenu::IsEnable() const
	{
		return enable;
	}

	void CBackpackMenu::SetMoneyField(int money)
	{
		this->moneyField = money;
	}

	void CBackpackMenu::SetHPField(int hp)
	{
		this->HPField = hp;
	}

	void CBackpackMenu::LoadBitmap()
	{
		backpackMenu.LoadBitmap(IDB_BackpackMenu, RGB(0,0,0));
		selector.LoadBitmap(IDB_Selector);
		nowTaking.LoadBitmap(IDB_NowTaking);
		question.LoadBitmap(IDB_Question, RGB(255, 255, 255));
		moneyIcon.LoadBitmap(IDB_Coin, RGB(255, 0, 255));
		HPIcon.LoadBitmap(IDB_HeartPoint, RGB(255, 0, 255));
	}

	void CBackpackMenu::OnKeyDown(UINT key, CPlayer* player)
	{
		int COL = 4;
		int ROW = 3;  
		const char KEY_LEFT = 0x25; // keyboard左箭頭
		const char KEY_UP = 0x26; // keyboard上箭頭
		const char KEY_RIGHT = 0x27; // keyboard右箭頭
		const char KEY_DOWN = 0x28; // keyboard下箭頭
		const char KEY_S = 'S'; // keyboard D
		const char KEY_A = 0x41;
		
		if (key == KEY_LEFT)
		{
			if (selectCol - 1 >= 0)
				selectCol -= 1;
		}
		else if (key == KEY_RIGHT)
		{
			if (selectCol + 1 < COL)
				selectCol += 1;
		}
		else if (key == KEY_DOWN)
		{
			if (selectRow + 1 < ROW)
				selectRow += 1;
		}
		else if (key == KEY_UP)
		{
			if (selectRow - 1 >= 0)
				selectRow -= 1;
		}
		else if (key == KEY_A)
		{
			player->SetToolSelector(selectRow * column + selectCol);
			// Update now taking id
			nowTakingID = player->GetCurrentTool()->GetToolID();
		}
		else if (key == KEY_S)
		{
			Disable();
		}
	}

	void CBackpackMenu::OnMove(CPlayer * p)
	{
		HPField = p->GetHealthPoint();
		moneyField = p->GetMoney();
	}

	

	void CBackpackMenu::OnShow()
	{
		unsigned int tool = 0;
		if (enable)
		{
			// Draw background
			backpackMenu.ShowBitmap();

			// First block:
			// Draw money and HP(health point)
			CString moneyStr, HPStr, timeStr;

			HPIcon.SetTopLeft(50, 15);
			HPIcon.ShowBitmap();
			HPStr.Format("%d", HPField);
			DrawTexts(HPStr, 100, 20, 150);

			moneyIcon.SetTopLeft(200, 15);
			moneyIcon.ShowBitmap();
			moneyStr.Format("%d", moneyField);
			DrawTexts(moneyStr, 250, 20, 150);


			timeStr.Format("%d/%d/%d  %d o'clock", timer->GetYear(), timer->GetMonth(), timer->GetDay(), timer->GetHour());
			DrawTexts(timeStr, 400, 20, 150);

			// Second block:
			// Draw Selector(cursor)
			int x = selectCol * width + fixWidth, y = selectRow * height + fixHeight;
			selector.SetTopLeft(x, y);
			selector.ShowBitmap();

			// Draw now taking selector
			int tcol = nowTakingID % 4, trow = 0;
			if (4 <= nowTakingID && nowTakingID <= 7) trow = 1;
			else if (8 <= nowTakingID && nowTakingID <= 11) trow = 2;
			int tx = tcol * width + fixWidth, ty = trow * height + fixHeight;
			nowTaking.SetTopLeft(tx, ty);
			nowTaking.ShowBitmap();

			// Draw Logos
			for (int i = 0; i < row; ++i)
			{
				for (int j = 0; j < column; ++j)
				{
					int x = j * width + fixWidth, y = i * height + fixHeight;
					if (tool >= playerBackpack->size())
					{
						question.SetTopLeft(x, y);
						question.ShowBitmap();
					}
					else
						(*playerBackpack)[tool++]->ShowIcon(x, y);


				}
			}

			// Third block:
			// Draw tool information text
			CString info = (*playerBackpack)[selectRow * column  + selectCol]->GetInfo().c_str();
			DrawTexts(info, 50, 380, 160);
			
			// 操作說明
			DrawTexts("[A] Use [S] Close", 400, 430, 140);
		}
	
	}

	void CBackpackMenu::DrawTexts(CString text, int posX, int posY, int fontSize)
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