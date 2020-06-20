#pragma once

namespace game_framework
{
	class CSettingPage
	{
	public:
		CSettingPage();
		void Enable();
		void Disable();
		bool IsEnable() const;
		void LoadBitmap();
		void OnKeyDown(char key);
		void OnMove(bool &quit);
		void OnShow();

	private:
		// Screen���A
		enum ScreenState
		{
			OnSetting,
			OnAudioSetting,
		};
		// Settings������ܪ��A
		enum PageSelectionState
		{
			OnResume,
			OnAudio,
			OnQuit,
		};
		// ���ĳ]�w����ܪ��A
		enum AudioPageSelectionState
		{
			OnSwitch,
			OnBack,
		};

	private:
		bool audio_on = false;
		bool enable = false;
		bool quit_game = false;
		ScreenState screenState = ScreenState::OnSetting;

		CMovingBitmap settingPage_Resume;
		CMovingBitmap settingPage_Audio;
		CMovingBitmap settingPage_Quit;
		vector<CMovingBitmap*> pages;
		int pageSelector = 0;
		PageSelectionState pageState = PageSelectionState::OnResume;

		CMovingBitmap audioPage_On_On;
		CMovingBitmap audioPage_On_Back;
		CMovingBitmap audioPage_Off_Back;
		CMovingBitmap audioPage_Off_On;
		CMovingBitmap *audioPage = nullptr;
		AudioPageSelectionState audioPageState = AudioPageSelectionState::OnSwitch;

	// Tool function:
	private:
		void DrawTexts(CString text, int posX, int posY, int fontSize);
	};
}
