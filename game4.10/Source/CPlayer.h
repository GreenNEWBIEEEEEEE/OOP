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
		// ���a����Ϥ��e��
		int width, height;
		// ���a�b�a�ϤW���y��(�I�y��)
		int x, y;

		// ���ʪ��ʵe
		CAnimation *facingDirection = nullptr; // ���V��e���V����V���ʵe
		CAnimation aniMoveLeft, aniMoveRight, aniMoveUp, aniMoveDown;

		// ���A�X�� : �O�_�W/�U/��/�k��
		bool isMovingLeft , isMovingRight, isMovingUp, isMovingDown;
	};
}