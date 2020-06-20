/*
 * mygame.h: 本檔案儲遊戲本身的class的interface
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
 *	 2004-03-02 V4.0
 *      1. Add CGameStateInit, CGameStateRun, and CGameStateOver to
 *         demonstrate the use of states.
 *   2005-09-13
 *      Rewrite the codes for CBall and CEraser.
 *   2005-09-20 V4.2Beta1.
 *   2005-09-29 V4.2Beta2.
 *   2006-02-08 V4.2
 *      1. Rename OnInitialUpdate() -> OnInit().
 *      2. Replace AUDIO_CANYON as AUDIO_NTUT.
 *      3. Add help bitmap to CGameStateRun.
 *   2006-09-09 V4.3
 *      1. Rename Move() and Show() as OnMove and OnShow() to emphasize that they are
 *         event driven.
 *   2008-02-15 V4.4
 *      1. Add namespace game_framework.
 *      2. Replace the demonstration of animation as a new bouncing ball.
 *      3. Use ShowInitProgress(percent) to display loading progress.
*/

#include "CGameObject.h"
#include "CPlayer.h"
#include "CAnimal.h"
#include "CChicken.h"
#include "CCow.h"
#include "CMapManager.h"
#include "CGameDialog.h"
#include "CBackpackMenu.h"
#include "CWeather.h"
#include "CFoodMenu.h"
#include "CPlantShopMenu.h"
#include "CAnimalShopMenu.h"
#include "CFoodShopMenu.h"
#include "CClinicMenu.h"
#include "CSettingPage.h"

namespace game_framework {
////
//// Audio IDs
////
	enum BGM
	{
		BGM_GameStateInit,
		BGM_GameStateRun
	};
	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲開頭畫面物件
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateInit : public CGameState {
	public:
		CGameStateInit(CGame *g);
		void OnInit();  								// 遊戲的初值及圖形設定
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnKeyUp(UINT, UINT, UINT); 				// 處理鍵盤Up的動作
		void OnLButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
	protected:
		void OnMove();
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		// 開頭畫面狀態，共3種：封面, 主選單, 音效設定頁
		enum InitScreenState
		{
			OnCover,
			OnMainMenu,
			OnAudioSettingPage,
		};
		// 主選單選擇狀態
		enum MainMenuSelectionState
		{
			OnStart,
			OnAudio,
			OnAbout
		};
		// 音效設定頁
		enum AudioPageSelectionState
		{
			OnSwitch,
			OnBack,
		};
	private:
		InitScreenState initScreenState = InitScreenState::OnCover;
		CAnimation gameUI_cover;
		// Main Page 
		CMovingBitmap mainPage_OnStart;
		CMovingBitmap mainPage_OnAudio;
		CMovingBitmap mainPage_OnAbout;
		vector<CMovingBitmap*> mainPages;
		int mainPageSelector = 0;
		MainMenuSelectionState mainMenuState = MainMenuSelectionState::OnStart;
		// Audio Setting Page
		CMovingBitmap audioPage_On_On;
		CMovingBitmap audioPage_On_Back;
		CMovingBitmap audioPage_Off_Back;
		CMovingBitmap audioPage_Off_On;
		CMovingBitmap *audioPage = nullptr;
		AudioPageSelectionState audioPageState = AudioPageSelectionState::OnSwitch;
		bool audioOn;
	// tool functions
	private:
		void DrawTexts(CString text, int posX, int posY, int fontSize);
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateRun : public CGameState {
	public:
		CGameStateRun(CGame *g);
		~CGameStateRun();
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnInit();  								// 遊戲的初值及圖形設定
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);
		void OnLButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
		void OnLButtonUp(UINT nFlags, CPoint point);	// 處理滑鼠的動作
		void OnMouseMove(UINT nFlags, CPoint point);	// 處理滑鼠的動作 
		void OnRButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
		void OnRButtonUp(UINT nFlags, CPoint point);	// 處理滑鼠的動作

		
	protected:
		void OnMove();									// 移動遊戲元素
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		//
		// 遊戲主體的各式物件/資源宣告在此:
		// 
		CTimer timer;
		CPlayer p1; // 玩家1
		bool quitFromSettingPage = false;
		CSettingPage settingPage;
		CMapManager mapManager;
		CGameDialog gameDialog;
		CBackpackMenu backpackMenu;
		CPlantShopMenu plantShopMenu;
		CAnimalShopMenu animalShopMenu;
		CFoodShopMenu foodShopMenu;
		CFoodMenu foodMenu;
		CClinic clinic;
		vector<CShopMenu*> sms; // 商店陣列
		vector<CGameObject*> obj;    // 用來放人和動物，index 0一定要放人
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的結束狀態(Game Over)
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateOver : public CGameState {
	public:
		CGameStateOver(CGame *g);
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnInit();
		void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	protected:
		void OnMove();									// 移動遊戲元素
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		CMovingBitmap gameOverScreen;
	};

}