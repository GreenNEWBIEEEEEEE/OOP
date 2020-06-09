#pragma once
namespace game_framework {
	
	class CFoodMenu
	{
	public:
		CFoodMenu();
		void SetBackpack(vector<CTool*>* playerBackpack);
		~CFoodMenu();


		void Enable();
		void Disable();

		bool IsEnable() const;

		void SetHPField(int hp);

		void LoadBitmap();
		void OnKeyDown(UINT key, CPlayer* player);
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
		vector<CTool*>* playerBackpack;
		CMovingBitmap foodMenu;

		// HP field
		CMovingBitmap HPIcon;
		int HPField = 0;

		// Flags
		bool enable;

		// Icon
		CMovingBitmap selector;
	private:
		void DrawTexts(CString text, int posX, int posY, int fontSize);
	};
}

