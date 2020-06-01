/*
 * mygame.cpp: ���ɮ��x�C��������class��implementation
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
// �o��class���C�����C���}�Y�e������
/////////////////////////////////////////////////////////////////////////////

CGameStateInit::CGameStateInit(CGame *g)
: CGameState(g)
{
}

void CGameStateInit::OnInit()
{
	
	//
	// ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
	//     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
	//
	ShowInitProgress(0);	// �@�}�l��loading�i�׬�0%
	//
	// �}�l���J���
	//
	logo.LoadBitmap(IDB_BACKGROUND);
	//Sleep(300);				// ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
	//
	// ��OnInit�ʧ@�|����CGameStaterRun::OnInit()�A�ҥH�i���٨S��100%
	//
}

void CGameStateInit::OnBeginState()
{
}

void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_ESC = 27;
	const char KEY_SPACE = ' ';
	if (nChar == KEY_SPACE)
		GotoGameState(GAME_STATE_RUN);						// ������GAME_STATE_RUN
	else if (nChar == KEY_ESC)								// Demo �����C������k
		PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE,0,0);	// �����C��
}

void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
{
	GotoGameState(GAME_STATE_RUN);		// ������GAME_STATE_RUN
}

void CGameStateInit::OnShow()
{
	//
	// �K�Wlogo
	//
	logo.SetTopLeft((SIZE_X - logo.Width())/2, SIZE_Y/8);
	logo.ShowBitmap();
	//
	// Demo�ù��r�����ϥΡA���L�}�o�ɽкɶq�קK�����ϥΦr���A���CMovingBitmap����n
	//
	CDC *pDC = CDDraw::GetBackCDC();			// ���o Back Plain �� CDC 
	CFont f,*fp;
	f.CreatePointFont(160,"Times New Roman");	// ���� font f; 160���16 point���r
	fp=pDC->SelectObject(&f);					// ��� font f
	pDC->SetBkColor(RGB(0,0,0));
	pDC->SetTextColor(RGB(255,255,0));
	pDC->TextOut(120,220,"Please click mouse or press SPACE to begin.");
	pDC->TextOut(5,395,"Press Ctrl-F to switch in between window mode and full screen mode.");
	if (ENABLE_GAME_PAUSE)
		pDC->TextOut(5,425,"Press Ctrl-Q to pause the Game.");
	pDC->TextOut(5,455,"Press Alt-F4 or ESC to Quit.");
	pDC->SelectObject(fp);						// �� font f (�d�U���n�|�F��)
	CDDraw::ReleaseBackCDC();					// �� Back Plain �� CDC
}								

/////////////////////////////////////////////////////////////////////////////
// �o��class���C�����������A(Game Over)
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
	// ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
	//     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
	//
	ShowInitProgress(66);	// ���ӫe�@�Ӫ��A���i�סA���B�i�׵���66%
	//
	// �}�l���J���
	//
	Sleep(300);				// ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
	//
	// �̲׶i�׬�100%
	//
	ShowInitProgress(100);
}

void CGameStateOver::OnShow()
{
	CDC *pDC = CDDraw::GetBackCDC();			// ���o Back Plain �� CDC 
	CFont f,*fp;
	f.CreatePointFont(160,"Times New Roman");	// ���� font f; 160���16 point���r
	fp=pDC->SelectObject(&f);					// ��� font f
	pDC->SetBkColor(RGB(0,0,0));
	pDC->SetTextColor(RGB(255,255,0));
	char str[80];								// Demo �Ʀr��r�ꪺ�ഫ
	sprintf(str, "Game Over ! (%d)", counter / 30);
	pDC->TextOut(240,210,str);
	pDC->SelectObject(fp);						// �� font f (�d�U���n�|�F��)
	CDDraw::ReleaseBackCDC();					// �� Back Plain �� CDC
}

/////////////////////////////////////////////////////////////////////////////
// �o��class���C�����C�����檫��A�D�n���C���{�����b�o��
/////////////////////////////////////////////////////////////////////////////

CGameStateRun::CGameStateRun(CGame *g)
	: CGameState(g),
	plantShopMenu(&p1, &gameDialog, &timer),
	animalShopMenu(&p1, &gameDialog, &timer)
{
	mapManager.AddMap("Scripts/MapInfos/MapE01.txt", true);
	mapManager.AddMap("Scripts/MapInfos/MapE02.txt", false);
	mapManager.AddMap("Scripts/MapInfos/MapE03.txt", false);
	mapManager.AddMap("Scripts/MapInfos/MapE04.txt", true);
	mapManager.AddMap("Scripts/MapInfos/MapE05.txt", false);
	backpackMenu.SetBackpack(p1.GetBackpack());
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

void CGameStateRun::OnMove()							// ���ʹC������
{
	//
	// �p�G�Ʊ�ק�cursor���˦��A�h�N�U���{����commment�����Y�i
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

void CGameStateRun::OnInit()  								// �C������Ȥιϧγ]�w
{
	
	//
	// ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
	//     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
	//
	ShowInitProgress(33);	// ���ӫe�@�Ӫ��A���i�סA���B�i�׵���33%
	//
	// �}�l���J���
	//
	//mapManager.GetCurrentMap()->LoadBitmap();

	//
	// ��������Loading�ʧ@�A�����i��
	//
	ShowInitProgress(50);
	Sleep(300); // ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
	//
	// �~����J��L���
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
	gameDialog.LoadBitmap();
	plantShopMenu.LoadBitmap();
	animalShopMenu.LoadBitmap();
	mapManager.LoadBitmapAll();
	//
	//
	//
	c1->SetMap(mapManager.GetChickenCoop()); // �]�w�L�̩��ݦa��
	c1->SetTimer(&timer);
	c2->SetMap(mapManager.GetChickenCoop()); // �]�w�L�̩��ݦa��
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

	// �O�oPush�ʪ�&�H�쬡�ʪ��󪺰}�C
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

	// push�Ҧ��ө��ܰө��}�C
	sms.push_back(&plantShopMenu);
	sms.push_back(&animalShopMenu);


	//
	// ��OnInit�ʧ@�|����CGameStaterOver::OnInit()�A�ҥH�i���٨S��100%
	//
}

//
// Practice : "KeyDown" sets something to true, otherwise false.
// 
void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// ��Game Dialog ���b��ܮ�Player���i����L�ާ@
	if (gameDialog.IsEnable()) {
		gameDialog.OnKeyDown(nChar);
	}
	else if (backpackMenu.IsEnable()) {
		backpackMenu.OnKeyDown(nChar, &p1);
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
		p1.OnKeyDown(nChar, &mapManager, &gameDialog, sms, mapManager.GetCurrentMap(), &obj);
		const char KEY_LEFT = 0x25; // keyboard���b�Y
		const char KEY_UP = 0x26; // keyboard�W�b�Y
		const char KEY_RIGHT = 0x27; // keyboard�k�b�Y
		const char KEY_DOWN = 0x28; // keyboard�U�b�Y
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
			// �b���ǤJplayer�{�b��money�H��HP�� �H�K�Amenu���
			backpackMenu.SetMoneyField(p1.GetMoney());
			backpackMenu.SetHPField(p1.GetHealthPoint());
		}
	}
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_LEFT  = 0x25; // keyboard���b�Y
	const char KEY_UP    = 0x26; // keyboard�W�b�Y
	const char KEY_RIGHT = 0x27; // keyboard�k�b�Y
	const char KEY_DOWN  = 0x28; // keyboard�U�b�Y
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

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
{
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{
}

//
// Practice : Q : How to do OnMouseNotToMove?
// 
void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{
	// �S�ơC�p�G�ݭn�B�z�ƹ����ʪ��ܡA�gcode�b�o��
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
{
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{
}

void CGameStateRun::OnShow()
{
	//
	//  �`�N�GShow�̭��d�U���n���ʥ��󪫥󪺮y�СA���ʮy�Ъ��u�@����Move���~��A
	//        �_�h��������sø�Ϯ�(OnDraw)�A����N�|���ʡA�ݰ_�ӷ|�ܩǡC���ӳN�y
	//        ���AMove�t�dMVC����Model�AShow�t�dView�A��View�������Model�C
	//
	//
	//  �K�W�I���ϡB�����ơB�y�B���l�B�u�����y
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
	plantShopMenu.OnShow();
	animalShopMenu.OnShow();
	gameDialog.OnShow();
	
}
}