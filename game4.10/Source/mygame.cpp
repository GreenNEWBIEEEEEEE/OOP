/*
 * mygame.cpp: 本檔案儲遊戲本身的class的implementation
 * Copyright (C) 2002-2008 Woei-Kae Chen <wkc@csie.ntut.edu.tw>
 *
 * This file is part of game, a free game development framework for windows.
 *
 * game is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * game is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * History:
 *   2002-03-04 V3.1
 *          Add codes to demostrate the use of CMovingBitmap::ShowBitmap(CMovingBitmap &).
 *	 2004-03-02 V4.0
 *      1. Add CGameStateInit, CGameStateRun, and CGameStateOver to
 *         demonstrate the use of states.
 *      2. Demo the use of CInteger in CGameStateRun.
 *   2005-09-13
 *      Rewrite the codes for CBall and CEraser.
 *   2005-09-20 V4.2Beta1.
 *   2005-09-29 V4.2Beta2.
 *      1. Add codes to display IDC_GAMECURSOR in GameStateRun.
 *   2006-02-08 V4.2
 *      1. Revise sample screens to display in English only.
 *      2. Add code in CGameStateInit to demo the use of PostQuitMessage().
 *      3. Rename OnInitialUpdate() -> OnInit().
 *      4. Fix the bug that OnBeginState() of GameStateInit is not called.
 *      5. Replace AUDIO_CANYON as AUDIO_NTUT.
 *      6. Add help bitmap to CGameStateRun.
 *   2006-09-09 V4.3
 *      1. Rename Move() and Show() as OnMove and OnShow() to emphasize that they are
 *         event driven.
 *   2006-12-30
 *      1. Bug fix: fix a memory leak problem by replacing PostQuitMessage(0) as
 *         PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE,0,0).
 *   2008-02-15 V4.4
 *      1. Add namespace game_framework.
 *      2. Replace the demonstration of animation as a new bouncing ball.
 *      3. Use ShowInitProgress(percent) to display loading progress. 
 *   2010-03-23 V4.6
 *      1. Demo MP3 support: use lake.mp3 to replace lake.wav.
*/

#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "mygame.h"

namespace game_framework {


/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲開頭畫面物件
/////////////////////////////////////////////////////////////////////////////

CGameStateInit::CGameStateInit(CGame *g)

: CGameState(g)
{
	gameUI_cover.SetDelayCount(15);
	mainPages.push_back(&mainPage_OnStart);
	mainPages.push_back(&mainPage_OnAudio);
	mainPages.push_back(&mainPage_OnAbout);
	audioOn = true;
	for (unsigned i = 0; i < 18; ++i)
		aboutPages.push_back(CMovingBitmap());
}

void CGameStateInit::OnInit()
{
	// 外部載入字型
	int res = AddFontResourceEx("./RES/Fonts/pricedown_bl.ttf", FR_PRIVATE, nullptr);
	CAudio::Instance()->Load(BGM_GameStateInit, "./Sounds/BGM/BGM_GameStateInit.mp3");
	CAudio::Instance()->Load(BGM_GameStateRun, "./Sounds/BGM/BGM_GameStateRun.mp3");
	CAudio::Instance()->Play(BGM_GameStateInit, true);
	ShowInitProgress(0);
	gameUI_cover.AddBitmap(IDB_UI_Cover01);
	gameUI_cover.AddBitmap(IDB_UI_Cover02);
	gameUI_cover.SetTopLeft(0, 0);

	mainPage_OnStart.LoadBitmap(IDB_MainPage_OnStart);
	mainPage_OnAudio.LoadBitmap(IDB_MainPage_OnAudio);
	mainPage_OnAbout.LoadBitmap(IDB_MainPage_OnAbout);
	for (unsigned i = 0; i < mainPages.size(); ++i)
		mainPages.at(i)->SetTopLeft(0, 0);

	audioPage_Off_Back.LoadBitmap(IDB_Audio_Off_Back);
	audioPage_Off_Back.SetTopLeft(0, 0);

	audioPage_Off_On.LoadBitmap(IDB_Audio_Off_On);
	audioPage_Off_On.SetTopLeft(0, 0);

	audioPage_On_Back.LoadBitmap(IDB_Audio_On_Back);
	audioPage_On_Back.SetTopLeft(0, 0);

	audioPage_On_On.LoadBitmap(IDB_Audio_On_On);
	audioPage_On_On.SetTopLeft(0, 0);

	aboutPages.at(0).LoadBitmap(IDB_UI_About_00);
	aboutPages.at(1).LoadBitmap(IDB_UI_About_0A);
	aboutPages.at(2).LoadBitmap(IDB_UI_About_01);
	aboutPages.at(3).LoadBitmap(IDB_UI_About_02);
	aboutPages.at(4).LoadBitmap(IDB_UI_About_03);
	aboutPages.at(5).LoadBitmap(IDB_UI_About_04);
	aboutPages.at(6).LoadBitmap(IDB_UI_About_05);
	aboutPages.at(7).LoadBitmap(IDB_UI_About_06);
	aboutPages.at(8).LoadBitmap(IDB_UI_About_07);
	aboutPages.at(9).LoadBitmap(IDB_UI_About_08);
	aboutPages.at(10).LoadBitmap(IDB_UI_About_09);
	aboutPages.at(11).LoadBitmap(IDB_UI_About_10);
	aboutPages.at(12).LoadBitmap(IDB_UI_About_11);
	aboutPages.at(13).LoadBitmap(IDB_UI_About_12);
	aboutPages.at(14).LoadBitmap(IDB_UI_About_13);
	aboutPages.at(15).LoadBitmap(IDB_UI_About_14);
	aboutPages.at(16).LoadBitmap(IDB_UI_About_15);
	aboutPages.at(17).LoadBitmap(IDB_UI_About_16);
	for (unsigned i = 0; i < aboutPages.size(); ++i)
		aboutPages.at(i).SetTopLeft(0, 0);
}

void CGameStateInit::OnBeginState()
{
}

void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_ESC = 27;
	const char KEY_SPACE = ' ';
	const char KEY_ENTER = 0x0D;
	const char KEY_UP = 0x26;
	const char KEY_DOWN = 0x28;
	const char KEY_LEFT = 0x25;
	const char KEY_RIGHT = 0x27;

	if (initScreenState == InitScreenState::OnCover)
	{
		if (nChar == KEY_SPACE)
		{
			// 改變GameStateInit的畫面狀態
			initScreenState = InitScreenState::OnMainMenu;
		}
		else if (nChar == KEY_ESC)								// Demo 關閉遊戲的方法
			PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);	// 關閉遊戲
	}
	else if (initScreenState == InitScreenState::OnMainMenu)
	{
		// 空白建
		if (nChar == KEY_ENTER || nChar == KEY_SPACE)
		{
			if (mainMenuState == MainMenuSelectionState::OnStart)
			{
				CAudio::Instance()->Stop(BGM_GameStateInit);
				if (audioOn)
					CAudio::Instance()->Play(BGM_GameStateRun, true);
				GotoGameState(GAME_STATE_RUN);
			}
				
			else if (mainMenuState == MainMenuSelectionState::OnAudio)
			{
				initScreenState = InitScreenState::OnAudioSettingPage;
				audioPageState = AudioPageSelectionState::OnSwitch;
				if (audioOn) audioPage = &audioPage_On_On;
				else audioPage = &audioPage_Off_On;
			}
			else if (mainMenuState == MainMenuSelectionState::OnAbout)
			{
				initScreenState = InitScreenState::OnAboutPages;
				aboutSelector = 0;
			}
		}
		else if (nChar == KEY_DOWN)
		{
			if (mainPageSelector == 2) mainPageSelector = 0;
			else mainPageSelector++;
			mainMenuState = (MainMenuSelectionState)mainPageSelector;
		}
		else if (nChar == KEY_UP)
		{
			if (mainPageSelector == 0) mainPageSelector = 2;
			else mainPageSelector--;
			mainMenuState = (MainMenuSelectionState)mainPageSelector;
		}
	}
	else if (initScreenState == InitScreenState::OnAudioSettingPage)
	{
		if (nChar == KEY_ENTER || nChar == KEY_SPACE)
		{
			if (audioPageState == AudioPageSelectionState::OnBack)
			{
				initScreenState = InitScreenState::OnMainMenu;
			}
			else if (audioPageState == AudioPageSelectionState::OnSwitch)
			{
				audioOn = !audioOn; // 開關反向
				if (!audioOn) CAudio::Instance()->Stop(BGM_GameStateInit);
				else CAudio::Instance()->Play(BGM_GameStateInit, true);
			}
		}
		else if (nChar == KEY_DOWN || nChar == KEY_UP)
		{
			if (audioPageState == AudioPageSelectionState::OnBack)
				audioPageState = OnSwitch;
			else
				audioPageState = OnBack;
		}
		else if (nChar == KEY_LEFT && audioOn)
		{
			CAudio::Instance()->DecreaseVolume();
		}
		else if (nChar == KEY_RIGHT && audioOn)
		{
			CAudio::Instance()->IncreaseVolume();
		}
	}
	else if (initScreenState == InitScreenState::OnAboutPages)
	{
		if (nChar == KEY_SPACE || nChar == KEY_ENTER || nChar == KEY_DOWN || nChar == KEY_RIGHT)
		{
			if (aboutSelector == 17) initScreenState = InitScreenState::OnMainMenu;
			else aboutSelector++;
		}
		else if (nChar == KEY_LEFT || nChar == KEY_UP)
		{
			if (aboutSelector > 0) aboutSelector--;
		}
		else if (nChar == KEY_ESC) initScreenState = InitScreenState::OnMainMenu;
	}
}

void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
{
}

void CGameStateInit::OnMove()
{
	if (initScreenState == InitScreenState::OnCover)
	{
		gameUI_cover.OnMove();
	}
	else if (initScreenState == InitScreenState::OnMainMenu)
	{

	}
	else if (initScreenState == InitScreenState::OnAudioSettingPage)
	{
		if (audioPageState == AudioPageSelectionState::OnSwitch)
		{
			if (audioOn) audioPage = &audioPage_On_On;
			else audioPage = &audioPage_Off_On;
		}
		else if (audioPageState == AudioPageSelectionState::OnBack)
		{
			if (audioOn) audioPage = &audioPage_On_Back;
			else audioPage = &audioPage_Off_Back;
		}
	}
}

void CGameStateInit::OnShow()
{
	if (initScreenState == InitScreenState::OnCover)
	{
		gameUI_cover.OnShow();
	}
	else if (initScreenState == InitScreenState::OnMainMenu)
	{
		mainPages.at(mainPageSelector)->ShowBitmap();
	}
	else if (initScreenState == InitScreenState::OnAudioSettingPage)
	{
		audioPage->ShowBitmap();
		if (audioOn)
		{
			int volume = CAudio::Instance()->GetVolume() / 10;
			CString volume_str = "";
			volume_str.Format("%d%%", volume);
			DrawTexts(volume_str, 192, 125, 320);
			
		}
		else
			DrawTexts("0%", 192, 125, 320);
		

	}
	else if (initScreenState == InitScreenState::OnAboutPages)
	{
		aboutPages.at(aboutSelector).ShowBitmap();
	}
}

void CGameStateInit::DrawTexts(CString text, int posX, int posY, int fontSize)
{
	CDC *pDC = CDDraw::GetBackCDC();
	CFont f, *fp = nullptr;
	f.CreatePointFont(fontSize, "pricedown bl");
	fp = pDC->SelectObject(&f);
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(255, 255, 255));
	pDC->TextOut(posX, posY, text);
	pDC->SelectObject(fp);
	CDDraw::ReleaseBackCDC();
}

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的結束狀態(Game Over)
/////////////////////////////////////////////////////////////////////////////

CGameStateOver::CGameStateOver(CGame *g)
: CGameState(g)
{
}

void CGameStateOver::OnMove() {}

void CGameStateOver::OnBeginState() {}

void CGameStateOver::OnInit()
{
	ShowInitProgress(66);
	Sleep(300);
	ShowInitProgress(100);
	gameOverScreen.LoadBitmap(IDB_UI_MissionComplete);
	gameOverScreen.SetTopLeft(0, 0);
}

void CGameStateOver::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == ' ' || nChar == 27)
	{
		PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);
	}
}

void CGameStateOver::OnShow()
{
	gameOverScreen.ShowBitmap();
}

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
/////////////////////////////////////////////////////////////////////////////

CGameStateRun::CGameStateRun(CGame *g)
	: CGameState(g),
	plantShopMenu(&p1, &gameDialog, &timer),
	animalShopMenu(&p1, &gameDialog, &timer, &obj, &mapManager),
	foodShopMenu(&p1, &gameDialog, &timer),
	clinic(&p1, &gameDialog, &timer)
{
	mapManager.AddMap("Scripts/MapInfos/MapE01.txt", true);
	mapManager.AddMap("Scripts/MapInfos/MapE02.txt", false);
	mapManager.AddMap("Scripts/MapInfos/MapE03.txt", false);
	mapManager.AddMap("Scripts/MapInfos/MapE04.txt", true);
	mapManager.AddMap("Scripts/MapInfos/MapE05.txt", false);
	mapManager.AddMap("Scripts/MapInfos/MapE06.txt", true);
	backpackMenu.SetBackpack(p1.GetBackpack());
	foodMenu.SetFood(p1.GetFood());
}

CGameStateRun::~CGameStateRun()
{
	for (unsigned i = 1; i < obj.size(); ++i)
	{
		if (obj[i] != nullptr)
		{
			if (i >= 1 && i <= 4)
			{
				/****重要*****/
				/****要先轉成真實類型的指標，delete才有用！*****/
				delete ((CChicken*)obj[i]);
				obj[i] = nullptr;
			}
			else
			{
				/****重要*****/
				/****要先轉成真實類型的指標，delete才有用！*****/
				delete ((CCow*)obj[i]);
				obj[i] = nullptr;
			}
		}
	}
}

void CGameStateRun::OnBeginState()
{
	
}

void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{
	ShowInitProgress(33);
	Sleep(300);
	settingPage.LoadBitmap();
	backpackMenu.SetBackpack(p1.GetBackpack());
	backpackMenu.SetTimer(&timer);
	mapManager.SetTimer(&timer);
	timer.LoadBitmap();
	backpackMenu.LoadBitmap();
	foodMenu.SetFood(p1.GetFood());
	foodMenu.LoadBitmap();
	gameDialog.LoadBitmap();
	plantShopMenu.LoadBitmap();
	animalShopMenu.LoadBitmap();
	foodShopMenu.LoadBitmap();
	clinic.LoadBitmap();
	mapManager.LoadBitmapAll();

	// 記得Push動物&人到活動物件的陣列
	// obj[0] is player
	obj.push_back(&p1);
	// obj[1:4] is chickens
	obj.push_back(new CChicken(200, 400));
	obj.push_back(new CChicken(200, 600));
	obj.push_back(nullptr);
	obj.push_back(nullptr);
	// obj[5:8] is cows
	obj.push_back(new CCow(300, 500));
	obj.push_back(new CCow(512, 500));
	obj.push_back(nullptr);
	obj.push_back(nullptr);
	
	
	// 載入obj的bitmap & 設定所屬地圖 & 設定時間
	for (unsigned i = 0; i < obj.size(); ++i)
	{
		if (obj[i] != nullptr) {
			obj[i]->LoadBitmap();
			if (i != 0) ((CAnimal*)obj[i])->SetTimer(&timer);
			if (i >= 1 && i <= 4)
				((CAnimal*)obj[i])->SetMap(mapManager.GetChickenCoop());
			else if (i >= 5 && i <= 8)
				((CAnimal*)obj[i])->SetMap(mapManager.GetCowCoop());;
		}
	}
	// push所有商店至商店陣列
	sms.push_back(&plantShopMenu);
	sms.push_back(&animalShopMenu);
	sms.push_back(&foodShopMenu);
	sms.push_back(&clinic);
}

void CGameStateRun::OnMove()							// 移動遊戲元素
{
	settingPage.OnMove(quitFromSettingPage);
	// 如果設定頁面正在跑，其他所有遊戲中物件不可更新
	if (!settingPage.IsEnable())
	{
		CShopMenu *sm = &plantShopMenu;
		timer.OnMove(mapManager.GetOutsideWeather(), &timer, &p1, &mapManager, &gameDialog, sms, &backpackMenu);
		mapManager.OnMove();
		gameDialog.OnMove();
		plantShopMenu.OnMove();
		animalShopMenu.OnMove();
		foodShopMenu.OnMove();
		clinic.OnMove();
		p1.OnMove(mapManager.GetCurrentMap(), &obj);
		for (unsigned i = 1; i < obj.size(); ++i)
		{
			if (obj[i] != nullptr)
			{
				// 如果有動物死掉，delete掉
				if (obj[i]->GetHealthPoint() == 0)
				{
					if (i >= 1 && i <= 4)
					{
						delete ((CChicken*)obj[i]);
						obj[i] = nullptr;
					}
					else if (i >= 5 && i <= 8)
					{
						delete ((CCow*)obj[i]);
						obj[i] = nullptr;
					}
				}
				else
				{
					obj[i]->OnMove(mapManager.GetCurrentMap(), &obj);
				}
			}
		}
		foodMenu.OnMove(&p1);
		backpackMenu.OnMove(&p1);
	}
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (settingPage.IsEnable()) settingPage.OnKeyDown(nChar);
	else if (gameDialog.IsEnable()) {
		gameDialog.OnKeyDown(nChar);
	}
	else if (backpackMenu.IsEnable()) {
		backpackMenu.OnKeyDown(nChar, &p1);
	}
	else if (foodMenu.IsEnable()) {
		foodMenu.OnKeyDown(nChar, &p1);
	}
	else if (plantShopMenu.IsEnable())
	{
		plantShopMenu.OnKeyDown(nChar);
	}
	else if (animalShopMenu.IsEnable())
	{
		animalShopMenu.OnKeyDown(nChar);
	}
	else if (foodShopMenu.IsEnable())
	{
		foodShopMenu.OnKeyDown(nChar);
	}
	else if (clinic.IsEnable())
	{
		clinic.OnKeyDown(nChar);
	}
	else
	{
		p1.OnKeyDown(nChar, &mapManager, &gameDialog, sms, mapManager.GetCurrentMap(), &obj, &foodMenu);
		const char KEY_LEFT = 0x25; // keyboard左箭頭
		const char KEY_UP = 0x26; // keyboard上箭頭
		const char KEY_RIGHT = 0x27; // keyboard右箭頭
		const char KEY_DOWN = 0x28; // keyboard下箭頭
		const char KEY_S = 0x53; // keyboard S
		const char KEY_ESC = 27;

		timer.OnKeyDown(nChar);
		
		if (nChar == KEY_ESC)
		{
			settingPage.Enable();
		}
		if (nChar == KEY_LEFT)
		{
			p1.SetMovingLeft(true);
		}
		if (nChar == KEY_RIGHT)
		{
			p1.SetMovingRight(true);
		}
		if (nChar == KEY_UP)
		{
			p1.SetMovingUp(true);
		}
		if (nChar == KEY_DOWN)
		{
			p1.SetMovingDown(true);
		}
		if (nChar == KEY_S)
		{
			backpackMenu.Enable();
			// 在此傳入player現在的money以及HP值 以便再menu顯示
			backpackMenu.SetMoneyField(p1.GetMoney());
			backpackMenu.SetHPField(p1.GetHealthPoint());
		}
		
	}
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_LEFT  = 0x25; // keyboard左箭頭
	const char KEY_UP    = 0x26; // keyboard上箭頭
	const char KEY_RIGHT = 0x27; // keyboard右箭頭
	const char KEY_DOWN  = 0x28; // keyboard下箭頭
	if (nChar == KEY_LEFT)
	{
		p1.SetMovingLeft(false);
	}	
	if (nChar == KEY_RIGHT)
	{
		p1.SetMovingRight(false);
	}
	if (nChar == KEY_UP)
	{
		p1.SetMovingUp(false);
	}
	if (nChar == KEY_DOWN)
	{
		p1.SetMovingDown(false);
	}
	timer.OnKeyUp(nChar);
	p1.OnKeyUp(nChar, &mapManager, &gameDialog);
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnShow()
{
	if (settingPage.IsEnable())
	{
		settingPage.OnShow();
	}
	else
	{
		mapManager.OnShow();
		// 先Show動物再show玩家
		for (unsigned i = 1; i < obj.size(); ++i)
		{
			if (obj[i] != nullptr)
			{
				obj.at(i)->OnShow(mapManager.GetCurrentMap());
			}
		}
		p1.OnShow(mapManager.GetCurrentMap());
		mapManager.OnShow_Weather();
		mapManager.OnShow_Timer();
		backpackMenu.OnShow();
		foodMenu.OnShow();
		plantShopMenu.OnShow();
		animalShopMenu.OnShow();
		foodShopMenu.OnShow();
		clinic.OnShow();
		gameDialog.OnShow();
	}
	
	// 可能不是很好的寫法，權責不在OnShow
	// 在這裡轉換直接銜接GameStateOver不會閃爍
	// 遊戲目標：賺到10000元後結束 or 在設定頁面按下quit game
	if (p1.GetMoney() >= 10000 || quitFromSettingPage)
	{
		// 跳到game over狀態
		GotoGameState(GAME_STATE_OVER);
		// 停止音樂
		CAudio::Instance()->Stop(BGM_GameStateRun);
	}
}
}