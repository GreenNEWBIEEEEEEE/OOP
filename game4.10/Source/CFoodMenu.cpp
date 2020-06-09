#include "StdAfx.h"
#include "resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include "CPlayer.h"
#include "CFoodMenu.h"
#include <iostream>

namespace game_framework {
	CFoodMenu::CFoodMenu()
	{
		enable = false;
	}
	/*
	void CFoodMenu::SetFood(vector<CTool*>* playerFood)
	{
		this->playerFood = playerFood;
	}
	*/
	CFoodMenu::~CFoodMenu() {}


	void CFoodMenu::Enable()
	{
		TRACE("\n Food Menu is enable now. \n");
		enable = true;
	}

	void CFoodMenu::Disable()
	{
		enable = false;
		TRACE("\n Food Menu is disable now. \n");
	}

	bool CFoodMenu::IsEnable() const
	{
		return enable;
	}

	void CFoodMenu::SetHPField(int hp)
	{
		this->HPField = hp;
	}

	void CFoodMenu::LoadBitmap()
	{
		foodMenu.LoadBitmap(IDB_BackpackMenu, RGB(0, 0, 0));
		selector.LoadBitmap(IDB_Selector);
		HPIcon.LoadBitmap(IDB_HeartPoint, RGB(255, 0, 255));
	}

	void CFoodMenu::OnKeyDown(UINT key, CPlayer* player)
	{
		int COL = 4;
		int ROW = 2;  // 原版為3
		const char KEY_LEFT = 0x25; // keyboard左箭頭
		const char KEY_UP = 0x26; // keyboard上箭頭
		const char KEY_RIGHT = 0x27; // keyboard右箭頭
		const char KEY_DOWN = 0x28; // keyboard下箭頭
		const char KEY_D = 0x44; // keyboard D
		const char KEY_A = 0x41;

		/*  原版
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
		*/
		if (key == KEY_LEFT)
		{
			if (selectCol - 1 >= 0)
				selectCol -= 1;
		}
		else if (key == KEY_RIGHT)
		{
			if (selectRow == 1 && selectCol == 2)
				return;

			if (selectCol + 1 < COL)
				selectCol += 1;
		}
		else if (key == KEY_DOWN)
		{
			if (selectRow == 0 && selectCol == 3)
				return;

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
		}
		else if (key == KEY_D)
		{
			Disable();
		}
	}



	void CFoodMenu::OnShow()
	{
		unsigned int tool = 0;
		if (enable)
		{
			// Draw background
			foodMenu.ShowBitmap();

			// First block:
			// Draw money and HP(health point)
			CString moneyStr, HPStr, timeStr;

			HPIcon.SetTopLeft(50, 15);
			HPIcon.ShowBitmap();
			HPStr.Format("%d", HPField);
			DrawTexts(HPStr, 100, 20, 150);
			/*
			moneyIcon.SetTopLeft(200, 15);
			moneyIcon.ShowBitmap();
			moneyStr.Format("%d", moneyField);
			DrawTexts(moneyStr, 250, 20, 150);


			timeStr.Format("%d/%d/%d  %d o'clock", timer->GetYear(), timer->GetMonth(), timer->GetDay(), timer->GetHour());
			DrawTexts(timeStr, 400, 20, 150);
			*/
			// Second block:
			// Draw Selector(cursor)
			int x = selectCol * width + fixWidth, y = selectRow * height + fixHeight;
			selector.SetTopLeft(x, y);
			selector.ShowBitmap();

			// Draw Logos
			/*
			for (int i = 0; i < row; ++i)
			{
				for (int j = 0; j < column; ++j)
				{
					int x = j * width + fixWidth, y = i * height + fixHeight;
					if (tool >= playerFood->size())
					{
						question.SetTopLeft(x, y);
						question.ShowBitmap();
					}
					else
						(*playerFood)[tool++]->ShowIcon(x, y);


				}
			}
			*/

			// Third block:
			// Draw tool information text
			/*
			CString info = (*playerFood)[selectRow * column + selectCol]->GetInfo().c_str();
			DrawTexts(info, 50, 380, 160);
			*/

		}

	}

	void CFoodMenu::DrawTexts(CString text, int posX, int posY, int fontSize)
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