#pragma once
namespace game_framework {
	class CBackpackMenu
	{
		public:
			CBackpackMenu();
			void SetBackpack(vector<CTool*>* playerBackpack);
			~CBackpackMenu();
			

			void Enable();
			void Disable();

			bool IsEnable() const;

			void LoadBitmap();
			void OnKeyDown(UINT key, CPlayer* player);
			void OnShow();
		private:
			//
			int selectRow = 0;
			int selectCol = 0;
			int row = 3;
			int column = 4;
			int width = 130;
			int fixWidth = 20;
			int fixHeight = 20;
			int height = 114;
			vector<CTool*>* playerBackpack;
			CMovingBitmap backpackMenu;
			
			// Flags
			bool enable;

			// Icon
			CMovingBitmap selector;
			CMovingBitmap question;
			
	};
}