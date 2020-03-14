namespace game_framework {

	class CGameMap;
	class CPlayer
	{
	public:
		CPlayer();
		~CPlayer();
		void LoadBitmap();
		void SetMovingLeft(bool flag);
		void SetMovingRight(bool flag);
		void SetMovingUp(bool flag);
		void SetMovingDown(bool flag);
		void OnMove(CGameMap *m);
		void OnShow(CGameMap *m);

	private:
		// 玩家角色圖片寬高
		int width, height;
		// 玩家在地圖上的座標(點座標)
		int x, y;

		// 移動的動畫
		CAnimation *facingDirection = nullptr; // 指向當前面向的方向之動畫
		CAnimation aniMoveLeft, aniMoveRight, aniMoveUp, aniMoveDown;

		// 狀態旗標 : 是否上/下/左/右移
		bool isMovingLeft , isMovingRight, isMovingUp, isMovingDown;
	};
}