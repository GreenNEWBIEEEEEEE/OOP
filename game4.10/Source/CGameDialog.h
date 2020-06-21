#pragma once

#include "CMapShowDialogEvent.h"

namespace game_framework {

	class CGameDialog {
	public:
		enum class DialogOptionsResult {
			Yes,
			No,
		};
		typedef void(*Callback) (void);
		typedef void(*CallbackForChangeToNewDay) (DialogOptionsResult, CTimer*, CWeather*);
		typedef void(*CallbackWithResult)(DialogOptionsResult);
		typedef void(*CallbackWithResultForShopMenu)(DialogOptionsResult, CShopMenu*);
		typedef void(*CallbackForTransitionMap)(CMapManager*, CPlayer*);

		CGameDialog();
		~CGameDialog();
		void AddMessage(string msg);
		void AddQuestion(string q);
		void AddOptionResultMessage(string msgForYes, string msgForNo);
		
		DialogOptionsResult GetCurrentOptionResult() const;

		void SetCallback(Callback cbp);
		void SetCallback(CallbackWithResult cbp);
		void SetCallback(CallbackWithResultForShopMenu cbp, CShopMenu* sm);
		void SetCallback(CallbackForChangeToNewDay cbp, CTimer* timer, CWeather* weather);	
		void SetCallback(CallbackForTransitionMap cbp, CMapManager* mm, CPlayer* p);
		void Enable();
		void Disable();

		bool IsEnable() const;

		void LoadBitmap();
		void OnKeyDown(UINT key);
		void OnMove();
		void OnShow();

	private:
		// DialogMessage����
		struct GameDialogMessage
		{
			// message����
			enum class MessageType
			{
				Normal,
				Question,
				OptionResult,
			};

			// �إ�normal message �� question message
			GameDialogMessage(string msg, bool isQuestion)
			{
				messageText = msg;
				if (isQuestion) 
				{
					messageType = MessageType::Question;
				}
				else
				{
					messageType = MessageType::Normal;
				}
			}

			// �إ� option result �� message
			GameDialogMessage(string msgForYes, string msgForNo)
			{
				messageType = MessageType::OptionResult;
				messageForYes = msgForYes;
				messageForNo = msgForNo;
			}

			~GameDialogMessage()
			{
			}

			string messageForYes = "";
			string messageForNo = "";
			string messageText = "";

			bool IsQuestion() const
			{
				return messageType == MessageType::Question;
			}

			void SetMessageTextForOptionResult(DialogOptionsResult dor)
			{
				result = dor;
			}
			string GetMessageText() const
			{
				if (messageType != MessageType::OptionResult)
				{
					return messageText;
				}
				else
				{
					if (result == DialogOptionsResult::Yes)
						return messageForYes;
					else
						return messageForNo;
				}
			}

			// ��ܸ�DialogMessage����message����
			MessageType messageType = MessageType::Normal;
			DialogOptionsResult result = DialogOptionsResult::Yes;


		};

		// GameDialog�һ�
		vector<GameDialogMessage> dialogMessages;
		string messageToShow;
		unsigned msgSelector;
		unsigned ss;
		CMovingBitmap background;
		CMovingBitmap backgroundOnOptionYes;
		CMovingBitmap backgroundOnOptionNo;
		CMovingBitmap imageBackground;
		CMovingBitmap characterAvatar;
		// GameDialog���AFlags
		bool enable;
		bool canContinue;
		bool isOnQuestion;
		bool done;
		bool allDone;
		// ��e��ܮؿﶵ�����G, �C�@�����ϥΪ̿�ܧ��N��s, �ݭn���ο�ܵ��G�i�H�γo��
		CGameDialog::DialogOptionsResult currentOptionResult;

		// Callback function pointer
		Callback cbFunc = nullptr;
		CallbackWithResult cbfwdor = nullptr;
		CallbackWithResultForShopMenu cbfwdor_sm = nullptr;
		CallbackForChangeToNewDay cbfctnd = nullptr;
		CallbackForTransitionMap cbftm = nullptr;


		CShopMenu *sm = nullptr;
		CTimer* timer = nullptr;
		CWeather* weather = nullptr;
		CMapManager* mm = nullptr;
		CPlayer* p = nullptr;

	private:
		void DrawTexts(CString text, int posX, int posY, int fontSize);

	};

}