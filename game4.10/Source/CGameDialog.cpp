#include "StdAfx.h"
#include "resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include "CGameDialog.h"
#include "CPlantShopMenu.h"


namespace game_framework {
	enum class DialogOptionsResult;

	CGameDialog::CGameDialog()
	{
		msgSelector = 0;
		ss = 0;
		enable = false;
		done = true;
		isOnQuestion = false;
		currentOptionResult = DialogOptionsResult::Yes;
	}

	CGameDialog::~CGameDialog() {
		this->sm = nullptr;
	}

	void CGameDialog::AddMessage(string msg)
	{
		dialogMessages.push_back(GameDialogMessage(msg, false));
	}

	void CGameDialog::AddQuestion(string q)
	{
		dialogMessages.push_back(GameDialogMessage(q, true));
	}

	void CGameDialog::AddOptionResultMessage(string msgForYes, string msgForNo)
	{
		dialogMessages.push_back(GameDialogMessage(msgForYes, msgForNo));
	}

	CGameDialog::DialogOptionsResult CGameDialog::GetCurrentOptionResult() const
	{
		return currentOptionResult;
	}

	void CGameDialog::SetCallback(Callback cbp)
	{
		cbFunc = cbp;
	}

	void CGameDialog::SetCallback(CallbackWithResult cbfwdor)
	{
		this->cbfwdor = cbfwdor;
	}

	void CGameDialog::SetCallback(CallbackWithResultForShopMenu cbp, CShopMenu *sm)
	{
		cbfwdor_sm = cbp;
		this->sm = sm;
	}

	void CGameDialog::Enable()
	{
		TRACE("\n Game Dialog is enable now. \n");
		enable = canContinue = true;
		done = allDone = false;
		msgSelector = 0;
		ss = 0;
	}

	void CGameDialog::Disable()
	{
		enable = false;
		if (cbFunc != nullptr)
		{
			cbFunc();
		}

		if (cbfwdor_sm != nullptr)
		{
			cbfwdor_sm(currentOptionResult, sm);
		}
		
		// 這一輪的對話框已結束 讓函式指標無效化
		cbFunc = nullptr;
		cbfwdor = nullptr;
		cbfwdor_sm = nullptr;
		
		dialogMessages.clear();
		TRACE("\n Game Dialog is disable now. \n");
	}

	bool CGameDialog::IsEnable() const
	{
		return enable;
	}

	void CGameDialog::LoadBitmap()
	{
		background.LoadBitmap(IDB_DIALOG_BG_01, RGB(255, 255, 255));
		backgroundOnOptionYes.LoadBitmap(IDB_DIALOG_BG_01_Yes, RGB(0, 0, 0));
		backgroundOnOptionNo.LoadBitmap(IDB_DIALOG_BG_01_No, RGB(0, 0, 0));
		imageBackground.LoadBitmap(IDB_DIALOG_BG_02, RGB(0, 0, 0));
	}

	void CGameDialog::OnKeyDown(UINT key)
	{
		// 按鍵常數
		const UINT KEY_SPACE = ' ';
		const UINT KEY_LEFT = 0x25;
		const UINT KEY_RIGHT = 0x27;

		// 如果現在這則message是一個question, 則不能馬上按掉, 必須等待顯示完畢,並做出選擇
		// 按了SPACE 可以顯示下一個訊息了

		if (isOnQuestion)
		{
			if (done)
			{
				switch (key)
				{
					// 方向鍵左右選擇
				case KEY_LEFT:
					currentOptionResult = DialogOptionsResult::Yes;
					break;
				case KEY_RIGHT:
					currentOptionResult = DialogOptionsResult::No;
					break;
					// 空白鍵選定
				case KEY_SPACE:
					// 解除question狀態
					// 跳到下一個message
					isOnQuestion = false;
					done = false;
					canContinue = true;
					msgSelector++;
					ss = 0;
					break;
				default:
					break;
				}
			}
		}
		else
		{
			if (key == KEY_SPACE)
			{
				if (allDone) // 如果所有messages中的訊息都已顯示完畢，則結束對話框
				{
					TRACE("\nallDone=%d\n", allDone);
					Disable();
				}
				else // 跳到下一個message
				{
					done = false;
					canContinue = true;
					msgSelector++;	
					ss = 0;
				}
			}
		}
		
	}

	void CGameDialog::OnMove()
	{
		if (enable)
		{
			if (msgSelector < dialogMessages.size())
			{
				// 
				isOnQuestion = dialogMessages[msgSelector].IsQuestion();

				// 
				if (dialogMessages[msgSelector].messageType ==
					CGameDialog::GameDialogMessage::MessageType::OptionResult)
				{
					dialogMessages[msgSelector].
						SetMessageTextForOptionResult(currentOptionResult);
				}

				// 遞增ss計數器
				if (ss < (dialogMessages[msgSelector].GetMessageText().size())) {
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
			background.SetTopLeft(20, 360);
			background.ShowBitmap();

			// Draw image background
			//imageBackground.SetTopLeft(20, 10);
			//imageBackground.ShowBitmap();

			// Draw text
			CDC *pDC = nullptr;
			CFont f, *fp = nullptr;
			pDC = CDDraw::GetBackCDC();
			f.CreatePointFont(160, "Consolas");
			

			fp = pDC->SelectObject(&f);
			pDC->SetBkMode(TRANSPARENT);
			//pDC->SetBkColor(RGB(63, 72, 204));
			pDC->SetTextColor(RGB(255, 255, 255));

			// 所有字元顯示結束後 固定顯示一整個字串
			if (done) 
			{
				CString out(dialogMessages[msgSelector].GetMessageText().c_str());
				pDC->TextOut(40, 370, out);
				canContinue = false;
				pDC->SelectObject(fp);
				CDDraw::ReleaseBackCDC();

				// 如果現在的message是question, 顯示出狀態
				if (isOnQuestion)
				{
					if (currentOptionResult == DialogOptionsResult::Yes)
					{
						DrawTexts("→Yes    No", 430, 420, 160);
					}
					else
					{
						DrawTexts(" Yes   →No", 430, 420, 160);
					}
				}

			}
			else
			{
				for (unsigned i = 0; i < ss; ++i)
					messageToShow.push_back(dialogMessages[msgSelector].GetMessageText().at(i));

				CString out(messageToShow.c_str());
				pDC->TextOut(40, 370, out);
				messageToShow = "";
				pDC->SelectObject(fp);
				CDDraw::ReleaseBackCDC();
			}
		}
	}

	void CGameDialog::DrawTexts(CString text, int posX, int posY, int fontSize)
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