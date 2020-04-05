#include "StdAfx.h"
#include "resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include "CGameDialog.h"


namespace game_framework {
	CGameDialog::CGameDialog()
	{
		strSelector = 0;
		ss = 0;
		enable = false;
		done = true;
	}

	CGameDialog::~CGameDialog() {}

	void CGameDialog::SetMessage(string msg)
	{
		message = msg;
	}

	void CGameDialog::AddMessage(string msg)
	{
		messages.push_back(msg);
	}

	void CGameDialog::Enable()
	{
		TRACE("\n Game Dialog is enable now. \n");
		enable = canContinue = true;
		done = allDone = false;
		strSelector = 0;
		ss = 0;
	}

	void CGameDialog::Disable()
	{
		enable = false;
		messages.clear();
		TRACE("\n Game Dialog is disable now. \n");
	}

	bool CGameDialog::IsEnable() const
	{
		return enable;
	}

	void CGameDialog::LoadBitmap()
	{
		background.LoadBitmap(IDB_DIALOG_BG_01, RGB(0, 0, 0));
		background.SetTopLeft(20, 360);
	}

	void CGameDialog::OnKeyDown(UINT key)
	{
		// 按了SPACE 可以顯示下一個訊息了
		if (key == ' ')
		{
			if (allDone) // 如果所有messages中的訊息都已顯示完畢，則結束對話框
			{
				TRACE("\nallDone=%d\n", allDone);
				Disable();
			}
			else
			{
				done = false;
				canContinue = true;
				strSelector++;
				ss = 0;
			}
		}
	}

	void CGameDialog::OnMove()
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

	void CGameDialog::OnShow()
	{
		if (enable)
		{
			// Draw background
			background.ShowBitmap();

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