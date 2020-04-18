#include "StdAfx.h"
#include "resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include "CTool.h"
#include "CBackpackMenu.h"

namespace game_framework {

	CBackpackMenu::CBackpackMenu()
	{
		strSelector = 0;
		ss = 0;
		enable = false;
	}

	void CBackpackMenu::SetBackpack(vector<CTool*>* playerBackpack) 
	{
		this->playerBackpack = playerBackpack;
	}
	CBackpackMenu::~CBackpackMenu() {}

	void CBackpackMenu::AddMessage(string msg)
	{
		messages.push_back(msg);
	}

	void CBackpackMenu::Enable()
	{
		TRACE("\n Backpack Menu is enable now. \n");
		enable = true;
		strSelector = 0;
		ss = 0;
	}

	void CBackpackMenu::Disable()
	{
		enable = false;
		messages.clear();
		TRACE("\n Backpack Menu is disable now. \n");
	}

	bool CBackpackMenu::IsEnable() const
	{
		return enable;
	}

	void CBackpackMenu::LoadBitmap()
	{
		backpackMenu.LoadBitmap(IDB_BackpackMenu);
		selector.LoadBitmap(IDB_Selector, RGB(255, 255, 255));
		question.LoadBitmap(IDB_Question, RGB(255, 255, 255));
	}

	void CBackpackMenu::OnKeyDown(UINT key)
	{
		int COL = 4;
		int ROW = 3;
		const char KEY_LEFT = 0x25; // keyboard左箭頭
		const char KEY_UP = 0x26; // keyboard上箭頭
		const char KEY_RIGHT = 0x27; // keyboard右箭頭
		const char KEY_DOWN = 0x28; // keyboard下箭頭
		const char KEY_D = 0x44; // keyboard D

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
		else if (key == KEY_D)
		{
			Disable();
		}
	}

	

	void CBackpackMenu::OnShow()
	{
		int row = 3;
		int column = 4;
		int width = 130;
		int fixWidth = 20;
		int fixHeight = 20;
		int height = 114;
		unsigned int tool = 0;
		if (enable)
		{
			// Draw background
			backpackMenu.ShowBitmap();

			// Draw Logo
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

			// Draw Selector
			int x = selectCol * width + fixWidth, y = selectRow * height + fixHeight;

			selector.SetTopLeft(x, y);
			selector.ShowBitmap();

			// Draw text

			CDC *pDC = CDDraw::GetBackCDC();
			CFont f, *fp = nullptr;
			CString info = (*playerBackpack)[selectRow * column  + selectCol]->GetInfo().c_str();

			f.CreatePointFont(160, "Consolas");

			fp = pDC->SelectObject(&f);
			pDC->SetBkColor(RGB(63, 72, 204));
			pDC->SetTextColor(RGB(255, 255, 255));
			pDC->TextOut(50, 380, info);
			pDC->SelectObject(fp);
			CDDraw::ReleaseBackCDC();


		}
	
	}
}