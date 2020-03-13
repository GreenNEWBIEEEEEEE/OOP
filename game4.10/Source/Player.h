namespace game_framework {

	class CGameMap;
	class Player
	{
	public:
		Player();
		void LoadBitmap();
		void SetMovingLeft(bool flag);
		void SetMovingRight(bool flag);
		void SetMovingUp(bool flag);
		void SetMovingDown(bool flag);
		void OnMove(CGameMap *m);
		void OnShow(CGameMap *m);

	private:
		int width, height;
		// Position(left and top) based on "map", not screen
		int x, y;

		// Animations for moving(walking)
		CAnimation *facingDirection = nullptr;
		CAnimation aniMoveLeft, aniMoveRight, aniMoveUp, aniMoveDown;

		// Flags of States
		bool isMovingLeft , isMovingRight, isMovingUp, isMovingDown;



	};
}