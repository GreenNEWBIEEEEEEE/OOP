#pragma once
namespace game_framework {
	class CBackpackMenu
	{
		public:
			CBackpackMenu();
			void SetBackpack(vector<CTool*>* playerBackpack);
			void SetTimer(CTimer* timer);
			~CBackpackMenu();
			

			void Enable();
			void Disable();

			bool IsEnable() const;

			void SetMoneyField(int money);
			void SetHPField(int hp);

			void LoadBitmap();
			void OnKeyDown(UINT key, CPlayer* player);
			void OnMove(CPlayer *p);
			void OnShow();
		private:
			// Backpack menu
			int selectRow = 0;
			int selectCol = 0;
			int row = 3;
			int column = 4;
			int width = 130;
			int height = 100;
			int fixWidth = 60;
			int fixHeight = 70;
			int nowTakingID = 0;
			vector<CTool*>* playerBackpack;
			CTimer* timer;
			CMovingBitmap backpackMenu;

			// Money field and HP field
			CMovingBitmap moneyIcon;
			CMovingBitmap HPIcon;
			int moneyField = 0;
			int HPField = 0;
			
			// Flags
			bool enable;

			// Icon
			CMovingBitmap selector;
			CMovingBitmap nowTaking;
			CMovingBitmap question;

		// Private tool functions:
		private:
			void DrawTexts(CString text, int posX, int posY, int fontSize);
			
	};
}