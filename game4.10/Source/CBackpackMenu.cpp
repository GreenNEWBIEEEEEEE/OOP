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
		done = true;
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
		enable = canContinue = true;
		done = allDone = false;
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
		selector.LoadBitmap(IDB_Selector);
		question.LoadBitmap(IDB_Question);
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
			if (selectCol + 1 <= COL)
				selectCol += 1;
		}
		else if (key == KEY_DOWN)
		{
			if (selectRow <= ROW)
				selectRow += 1;
		}
		else if (key == KEY_UP)
		{
			if (selectRow >= 0)
			selectRow -= 1;
		}
		else if (key == KEY_D)
		{
			Disable();
		}
	}

	void CBackpackMenu::OnMove()
	{
		if (enable)
		{
			if (strSelector < messages.size())
			{
				if (ss < (messages[strSelector].size())) {
					ss++;
				}
				else {
					messageToShow = "";
					done = true;
				}
			}
			else
			{
				allDone = true;
				Disable();
			}
		}
	}

	void CBackpackMenu::OnShow()
	{
		int row = 3;
		int column = 4;
		int width = 130;
		int fixWidth = 20;
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
					int x = j * width, y = i * height;
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
			int x = selectCol * width, y = selectRow * height;

			selector.SetTopLeft(x, y);
			selector.ShowBitmap();

			// Draw text
			CDC *pDC = nullptr;
			CFont f, *fp = nullptr;
			pDC = CDDraw::GetBackCDC();
			f.CreatePointFont(160, "Consolas");

			fp = pDC->SelectObject(&f);
			pDC->SetBkColor(RGB(63, 72, 204));
			pDC->SetTextColor(RGB(255, 255, 255));



			// 所有字元顯示結束後 固定顯示一整個字串
			if (done)
			{
				CString out(messages[strSelector].c_str());
				pDC->TextOut(40, 370, out);
				canContinue = false;
				pDC->SelectObject(fp);
				CDDraw::ReleaseBackCDC();
			}
			else
			{
				for (unsigned i = 0; i < ss; ++i)
					messageToShow.push_back(messages[strSelector].at(i));

				CString out(messageToShow.c_str());
				pDC->TextOut(40, 370, out);
				messageToShow = "";
				pDC->SelectObject(fp);
				CDDraw::ReleaseBackCDC();
			}

		}
	
	}
}