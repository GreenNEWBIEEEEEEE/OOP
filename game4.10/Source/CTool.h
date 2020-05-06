#pragma once
namespace game_framework{
	class CTool
	{
		public:
			CTool(int toolID, int number);
			~CTool();
			bool IsEnable() const;
			void LoadBitmap();
			void ShowIcon(int x, int y);
			string GetInfo() const;
			int GetToolID() const;
			int GetNumber() const;

			// ¼W´î¼Æ¶q
			void IncreaseNumber(int number);
			void DecreaseNumber(int number);

			
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

