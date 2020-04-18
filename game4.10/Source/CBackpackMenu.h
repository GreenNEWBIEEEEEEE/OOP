#pragma once
namespace game_framework {
	class CBackpackMenu
	{
		public:
			CBackpackMenu();
			void SetBackpack(vector<CTool*>* playerBackpack);
			~CBackpackMenu();
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
			int selectRow = 0;
			int selectCol = 0;
			vector<CTool*>* playerBackpack;
			vector<string> messages;
			string messageToShow;
			unsigned strSelector;
			unsigned ss;
			CMovingBitmap backpackMenu;
			
			// Flags
			bool enable;
			bool canContinue;
			bool done;
			bool allDone;

			// Icon
			CMovingBitmap selector;
			CMovingBitmap question;
			
	};
}