#include "stdafx.h"
#include "resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CSettingPage.h"

namespace game_framework
{
	CSettingPage::CSettingPage()
	{
		pages.push_back(&settingPage_Resume);
		pages.push_back(&settingPage_Audio);
		pages.push_back(&settingPage_Quit);
	}

	void CSettingPage::Enable()
	{
		enable = true;
		screenState = ScreenState::OnSetting;
	}

	void CSettingPage::Disable()
	{
		enable = false;
	}

	bool CSettingPage::IsEnable() const
	{
		return enable;
	}

	void CSettingPage::LoadBitmap()
	{
		settingPage_Resume.LoadBitmap(IDB_Settings_Resume);
		settingPage_Resume.SetTopLeft(0, 0);
		settingPage_Audio.LoadBitmap(IDB_Settings_Audio);
		settingPage_Audio.SetTopLeft(0, 0);
		settingPage_Quit.LoadBitmap(IDB_Settings_Quit);
		settingPage_Quit.SetTopLeft(0, 0);

		audioPage_On_On.LoadBitmap(IDB_Audio_On_On);
		audioPage_On_On.SetTopLeft(0, 0);
		audioPage_On_Back.LoadBitmap(IDB_Audio_On_Back);
		audioPage_On_Back.SetTopLeft(0, 0);
		audioPage_Off_Back.LoadBitmap(IDB_Audio_Off_Back);
		audioPage_Off_Back.SetTopLeft(0, 0);
		audioPage_Off_On.LoadBitmap(IDB_Audio_Off_On);
		audioPage_Off_On.SetTopLeft(0, 0);
	}

	void CSettingPage::OnKeyDown(char key)
	{
		// update audio_on
		audio_on = CAudio::Instance()->IsPlaying();

		const char KEY_ESC = 27;
		const char KEY_SPACE = ' ';
		const char KEY_ENTER = 0x0D;
		const char KEY_UP = 0x26;
		const char KEY_DOWN = 0x28;
		const char KEY_LEFT = 0x25;
		const char KEY_RIGHT = 0x27;

		if (screenState == ScreenState::OnSetting)
		{
			if (key == KEY_ESC) enable = false;
			else if (key == KEY_DOWN)
			{
				if (pageSelector == 2) pageSelector = 0;
				else pageSelector++;
				pageState = (PageSelectionState)pageSelector;
			}
			else if (key == KEY_UP)
			{
				if (pageSelector == 0) pageSelector = 2;
				else pageSelector--;
				pageState = (PageSelectionState)pageSelector;
			}
			else if (key == KEY_SPACE || key == KEY_ENTER)
			{
				if (pageState == OnResume) enable = false;
				else if (pageState == OnAudio) screenState = ScreenState::OnAudioSetting;
				else if (pageState == OnQuit) quit_game = true;
			}
		}
		else if (screenState == ScreenState::OnAudioSetting)
		{
			if (key == KEY_ESC) screenState = ScreenState::OnSetting;
			
			else if (key == KEY_ENTER || key == KEY_SPACE)
			{
				if (audioPageState == AudioPageSelectionState::OnBack)
					screenState = ScreenState::OnSetting;
				else
				{
					audio_on = !audio_on;
					if (audio_on) CAudio::Instance()->Play(1, true); // stop BGM_GameStateRun
					else CAudio::Instance()->Stop(1);
				}
			}
			else if (key == KEY_DOWN || key == KEY_UP)
			{
				if (audioPageState == AudioPageSelectionState::OnBack)
					audioPageState = OnSwitch;
				else
					audioPageState = OnBack;
			}
			else if (key == KEY_LEFT)
			{
				CAudio::Instance()->DecreaseVolume();
			}
			else if (key == KEY_RIGHT)
			{
				CAudio::Instance()->IncreaseVolume();
			}
		}
	}

	void CSettingPage::OnMove(bool &quit)
	{ 
		// update audio_on
		audio_on = CAudio::Instance()->IsPlaying();

		if (enable)
		{
			// 設定quit給外部
			quit = quit_game;
			// 若是頁面在Audio Setting，改變顯示的圖
			if (screenState == ScreenState::OnAudioSetting)
			{
				if (audioPageState == AudioPageSelectionState::OnSwitch)
				{
					if (audio_on) audioPage = &audioPage_On_On;
					else audioPage = &audioPage_Off_On;
				}
				else if (audioPageState == AudioPageSelectionState::OnBack)
				{
					if (audio_on) audioPage = &audioPage_On_Back;
					else audioPage = &audioPage_Off_Back;
				}
			}
		}
	}

	void CSettingPage::OnShow()
	{
		// update audio_on
		audio_on = CAudio::Instance()->IsPlaying();

		if (enable)
		{
			if (screenState == ScreenState::OnSetting)
			{
				pages.at(pageSelector)->ShowBitmap();
			}
			else
			{
				audioPage->ShowBitmap();
				if (audio_on)
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
	}

	void CSettingPage::DrawTexts(CString text, int posX, int posY, int fontSize)
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

}