#pragma once
namespace game_framework{
	class CTool
	{
		public:
			CTool(int toolID, int number);
			~CTool();
			bool IsEnable();
			void LoadBitmap();
			void ShowIcon(int x, int y);
			string GetInfo();

			int GetToolID();
		protected:
			int toolID;
			string toolName;
			int number;
			CMovingBitmap hoe;
			CMovingBitmap hand;
			CMovingBitmap axe;
			CMovingBitmap seed01;
			CMovingBitmap waterer;
			CMovingBitmap sickle;
			CMovingBitmap hammer;

			CMovingBitmap *icon = &hoe;
	};
}

