#pragma once

namespace game_framework {
	class CGameDialog {
	public:
		CGameDialog();
		~CGameDialog();
		void SetMessage(string msg);
		void AddMessage(string msg);

		void Enable();
		void Disable();

		bool IsEnable() const;	

		void LoadBitmap();
		void OnKeyDown(UINT key);
		void OnMove();
		void OnShow();

	private:
		//
		vector<string> messages;
		string message;
		string messageToShow;
		unsigned strSelector;
		unsigned ss;
		CMovingBitmap background;

		// Flags
		bool enable;
		bool canContinue;
		bool done;
		bool allDone;
		

	};

}