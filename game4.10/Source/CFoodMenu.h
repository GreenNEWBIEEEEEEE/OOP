#pragma once
namespace game_framework {
	class CFood;
	class CFoodMenu
	{
	public:
		CFoodMenu();
		~CFoodMenu();


		void Enable();
		void Disable();

		bool IsEnable() const;

		void SetHPField(int hp);
		void SetFood(vector<CFood*>* playerFood);

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
		vector<CFood*>* playerFood;
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

