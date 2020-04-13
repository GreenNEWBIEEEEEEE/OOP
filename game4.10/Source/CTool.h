#pragma once
namespace game_framework{
	class CTool
	{
		public:
			CTool(int toolID, int number);
			~CTool();
			bool IsEnable();
			void LoadBitmap();

		protected:
			int toolID;
			int number;
			CMovingBitmap icon;
	};
}

