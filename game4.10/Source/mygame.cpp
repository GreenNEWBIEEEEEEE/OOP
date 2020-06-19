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
	mainPage_OnStart.SetTopLeft(0, 0);
	mainPage_OnAudio.LoadBitmap(IDB_MainPage_OnAudio);
	mainPage_OnAudio.SetTopLeft(0, 0);
	mainPage_OnAbout.LoadBitmap(IDB_MainPage_OnAbout);
	mainPage_OnAbout.SetTopLeft(0, 0);

	audioPage_Off_Back.LoadBitmap(IDB_Audio_Off_Back);
	audioPage_Off_Back.SetTopLeft(0, 0);

	audioPage_Off_On.LoadBitmap(IDB_Audio_Off_On);
	audioPage_Off_On.SetTopLeft(0, 0);

	audioPage_On_Back.LoadBitmap(IDB_Audio_On_Back);
	audioPage_On_Back.SetTopLeft(0, 0);

	audioPage_On_On.LoadBitmap(IDB_Audio_On_On);
	audioPage_On_On.SetTopLeft(0, 0);
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
		else if (nChar == KEY_LEFT)
		{
			CAudio::Instance()->DecreaseVolume();
		}
		else if (nChar == KEY_RIGHT)
		{
			CAudio::Instance()->IncreaseVolume();
		}
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

void CGameStateOver::OnMove()
{
	counter--;
	if (counter < 0)
		GotoGameState(GAME_STATE_INIT);
}

void CGameStateOver::OnBeginState()
{
	counter = 30 * 5; // 5 seconds
}

void CGameStateOver::OnInit()
{
	//
	// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
	//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
	//
	ShowInitProgress(66);	// 接個前一個狀態的進度，此處進度視為66%
	//
	// 開始載入資料
	//
	Sleep(300);				// 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
	//
	// 最終進度為100%
	//
	ShowInitProgress(100);
}

void CGameStateOver::OnShow()
{
	CDC *pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
	CFont f,*fp;
	f.CreatePointFont(160,"Times New Roman");	// 產生 font f; 160表示16 point的字
	fp=pDC->SelectObject(&f);					// 選用 font f
	pDC->SetBkColor(RGB(0,0,0));
	pDC->SetTextColor(RGB(255,255,0));
	char str[80];								// Demo 數字對字串的轉換
	sprintf(str, "Game Over ! (%d)", counter / 30);
	pDC->TextOut(240,210,str);
	pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
	CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
}

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
/////////////////////////////////////////////////////////////////////////////

CGameStateRun::CGameStateRun(CGame *g)
	: CGameState(g),
	plantShopMenu(&p1, &gameDialog, &timer),
	animalShopMenu(&p1, &gameDialog, &timer, &obj)
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
	delete c1;
	delete c2;
	delete c3;
	delete c4;
	delete cow1;
	delete cow2;
	delete cow3;
	delete cow4;
}

void CGameStateRun::OnBeginState()
{
	
}

void CGameStateRun::OnMove()							// 移動遊戲元素
{
	//
	// 如果希望修改cursor的樣式，則將下面程式的commment取消即可
	//
	// SetCursor(AfxGetApp()->LoadCursor(IDC_GAMECURSOR));

	CShopMenu *sm = &plantShopMenu;
	timer.OnMove(mapManager.GetOutsideWeather(), &timer, &p1, &mapManager, &gameDialog, sms, &backpackMenu);
	mapManager.OnMove();
	gameDialog.OnMove();
	plantShopMenu.OnMove();
	animalShopMenu.OnMove();
	p1.OnMove(mapManager.GetCurrentMap(), &obj);
	c1->OnMove(mapManager.GetCurrentMap(), &obj);
	c2->OnMove(mapManager.GetCurrentMap(), &obj);
	c3->OnMove(mapManager.GetCurrentMap(), &obj);
	c4->OnMove(mapManager.GetCurrentMap(), &obj);
	cow1->OnMove(mapManager.GetCurrentMap(), &obj);
	cow2->OnMove(mapManager.GetCurrentMap(), &obj);
	cow3->OnMove(mapManager.GetCurrentMap(), &obj);
	cow4->OnMove(mapManager.GetCurrentMap(), &obj);
}

void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{
	
	//
	// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
	//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
	//
	ShowInitProgress(33);	// 接個前一個狀態的進度，此處進度視為33%
	//
	// 開始載入資料
	//
	//mapManager.GetCurrentMap()->LoadBitmap();

	//
	// 完成部分Loading動作，提高進度
	//
	ShowInitProgress(50);
	//Sleep(300); // 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
	//
	// 繼續載入其他資料
	//
	c1 = new CChicken(200, 400);
	c2 = new CChicken(200, 600);
	c3 = new CChicken(300, 600);
	c4 = new CChicken(350, 500);
	cow1 = new CCow(300, 500);
	cow2 = new CCow(512, 500);
	cow3 = new CCow(421, 600);
	cow4 = new CCow(324, 600);
	p1.LoadBitmap();
	c1->LoadBitmap();
	c2->LoadBitmap();
	c3->LoadBitmap();
	c4->LoadBitmap();
	cow1->LoadBitmap();
	cow2->LoadBitmap();
	cow3->LoadBitmap();
	cow4->LoadBitmap();
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
	mapManager.LoadBitmapAll();
	//
	//
	//
	c1->SetMap(mapManager.GetChickenCoop()); // 設定他們所屬地圖
	c1->SetTimer(&timer);
	c2->SetMap(mapManager.GetChickenCoop()); // 設定他們所屬地圖
	c2->SetTimer(&timer);
	c3->SetMap(mapManager.GetChickenCoop());
	c3->SetTimer(&timer);
	c4->SetMap(mapManager.GetChickenCoop());
	c4->SetTimer(&timer);
	cow1->SetMap(mapManager.GetCowCoop());
	cow1->SetTimer(&timer);
	cow2->SetMap(mapManager.GetCowCoop());
	cow2->SetTimer(&timer);
	cow3->SetMap(mapManager.GetCowCoop());
	cow3->SetTimer(&timer);
	cow4->SetMap(mapManager.GetCowCoop());
	cow4->SetTimer(&timer);

	// 記得Push動物&人到活動物件的陣列
	// obj[0] is player
	obj.push_back(&p1);
	// obj[1:4] is chickens
	obj.push_back(c1);
	obj.push_back(c2);
	obj.push_back(c3);
	obj.push_back(c4);
	// obj[5:8] is cows
	obj.push_back(cow1);
	obj.push_back(cow2);
	obj.push_back(cow3);
	obj.push_back(cow4);

	// push所有商店至商店陣列
	sms.push_back(&plantShopMenu);
	sms.push_back(&animalShopMenu);


	//
	// 此OnInit動作會接到CGameStaterOver::OnInit()，所以進度還沒到100%
	//
}

//
// Practice : "KeyDown" sets something to true, otherwise false.
// 
void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// 當Game Dialog 正在顯示時Player不可做其他操作
	if (gameDialog.IsEnable()) {
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
	else
	{
		p1.OnKeyDown(nChar, &mapManager, &gameDialog, sms, mapManager.GetCurrentMap(), &obj, &foodMenu);
		const char KEY_LEFT = 0x25; // keyboard左箭頭
		const char KEY_UP = 0x26; // keyboard上箭頭
		const char KEY_RIGHT = 0x27; // keyboard右箭頭
		const char KEY_DOWN = 0x28; // keyboard下箭頭
		const char KEY_S = 0x53; // keyboard S

		timer.OnKeyDown(nChar);

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

//
// Practice : Q : How to do OnMouseNotToMove?
// 
void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
	// 沒事。如果需要處理滑鼠移動的話，寫code在這裡
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnShow()
{
	//
	//  注意：Show裡面千萬不要移動任何物件的座標，移動座標的工作應由Move做才對，
	//        否則當視窗重新繪圖時(OnDraw)，物件就會移動，看起來會很怪。換個術語
	//        說，Move負責MVC中的Model，Show負責View，而View不應更動Model。
	//
	//
	//  貼上背景圖、撞擊數、球、擦子、彈跳的球
	//
	mapManager.OnShow();
	c1->OnShow(mapManager.GetCurrentMap());
	c2->OnShow(mapManager.GetCurrentMap());
	c3->OnShow(mapManager.GetCurrentMap());
	c4->OnShow(mapManager.GetCurrentMap());
	cow1->OnShow(mapManager.GetCurrentMap());
	cow2->OnShow(mapManager.GetCurrentMap());
	cow3->OnShow(mapManager.GetCurrentMap());
	cow4->OnShow(mapManager.GetCurrentMap());
	p1.OnShow(mapManager.GetCurrentMap());
	mapManager.OnShow_Weather();
	mapManager.OnShow_Timer();
	backpackMenu.OnShow();
	foodMenu.OnShow();
	plantShopMenu.OnShow();
	animalShopMenu.OnShow();
	gameDialog.OnShow();
	
}
}