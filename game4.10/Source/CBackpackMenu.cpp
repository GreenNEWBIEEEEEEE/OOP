#include "StdAfx.h"
#include "resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include "CPlayer.h"
#include "CTool.h"
#include "CBackpackMenu.h"

namespace game_framework {

	CBackpackMenu::CBackpackMenu()
	{
		enable = false;
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

	void CBackpackMenu::LoadBitmap()
	{
		backpackMenu.LoadBitmap(IDB_BackpackMenu, RGB(0,0,0));
		selector.LoadBitmap(IDB_Selector);
		question.LoadBitmap(IDB_Question, RGB(255, 255, 255));
	}

	void CBackpackMenu::OnKeyDown(UINT key, CPlayer* player)
	{
		int COL = 4;
		int ROW = 3;
		const char KEY_LEFT = 0x25; // keyboard左箭頭
		const char KEY_UP = 0x26; // keyboard上箭頭
		const char KEY_RIGHT = 0x27; // keyboard右箭頭
		const char KEY_DOWN = 0x28; // keyboard下箭頭
		const char KEY_D = 0x44; // keyboard D
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
		}
		else if (key == KEY_D)
		{
			Disable();
		}
	}

	

	void CBackpackMenu::OnShow()
	{
		unsigned int tool = 0;
		if (enable)
		{
			// Draw background
			backpackMenu.ShowBitmap();

			// Draw Selector
			int x = selectCol * width + fixWidth, y = selectRow * height + fixHeight;

			selector.SetTopLeft(x, y);
			selector.ShowBitmap();

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