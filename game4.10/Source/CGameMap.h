namespace game_framework
{
	
	class CGameMap
	{
	public:
		CGameMap();
		~CGameMap();
		void LoadBitmap();
		void OnShow();

		//
		bool IsEmpty(int x, int y) const;
		
		// 
		int GetSX() const;
		int GetSY() const;
		void SetSX(int nx);
		void SetSY(int ny);
		void SetSXSY(int nx, int ny);

		// Convert to screenX and screenY for player
		int ScreenX(int x) const;
		int ScreenY(int y) const;
	private:
		//
		// Textures of ground:
		//
		// grass01
		CMovingBitmap gndGrass01;
		CMovingBitmap gndDirt01;
		CMovingBitmap gndBridge01;
		CAnimation gndWater01;
		

		// 2D array of map information
		// value 0 : grass01
		const int ROW;
		const int COL;
		int **map = new int*[ROW];

		int sx, sy; // The (left,top) of the screen base on this map
		int gndW, gndH; // Width and height of a ground texture

	};
}