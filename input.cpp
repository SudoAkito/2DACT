//------------------------------------------
//
//         入力処理
//       Author:Sudou Akito
//
//------------------------------------------

#include"input.h"

//マクロ定義
#define NUM_KEY_MAX (256)  //キーの最大数

//グローバル変数
XINPUT_STATE g_joyKeyState;        //ジョイパッドのプレス情報
XINPUT_STATE g_joyKeyStateTrigger;//ジョイパッドのトリガー情報
XINPUT_STATE g_OldKeyState;
LPDIRECTINPUT8 g_pInput = NULL;    //DirectInputオブジェへのポインタ
LPDIRECTINPUTDEVICE8 g_pDevKeyboard = NULL; //入力デバイス（キーボード）へのポインタ
BYTE g_aKeyState[NUM_KEY_MAX];
BYTE g_aOldKeyState[NUM_KEY_MAX];

HRESULT InitKeyBoard(HINSTANCE hInstance, HWND hWnd)
{
	//Directオブジェの生成
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, 
		(void**)&g_pInput, NULL)))
	{
		return E_FAIL;
	}

	//入力デバイス（キーボード）の生成
	if (FAILED(g_pInput->CreateDevice(GUID_SysKeyboard, &g_pDevKeyboard, NULL)))
	{
		return E_FAIL;
	}

	//データフォーマットを設定
	if (FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	//協調モードの設定
	if (FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	g_pDevKeyboard->Acquire();

	return S_OK;
}

void UninitKeyBoard(void)
{
	//入力デバイスの破棄
	if (g_pDevKeyboard != NULL)
	{
		g_pDevKeyboard->Unacquire();  //キーボードへのアクセス権を破棄
		g_pDevKeyboard->Release();
		g_pDevKeyboard = NULL;
	}

	//DirectInputオブジェの破棄
	if (g_pInput != NULL)	
	{
		g_pInput->Release();
		g_pInput = NULL;
	}
}

void UpdateKeyBoard(void)
{
	BYTE aKeyState[NUM_KEY_MAX];  //キーボードの入力情報
	int nCntKey;

	for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
	{
		g_aOldKeyState[nCntKey] = g_aKeyState[nCntKey];  //ひとつ前の情報を取得
	}
	//入力デバイスからデータを取得
	if (SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			g_aKeyState[nCntKey] = aKeyState[nCntKey];//キーボードのブレス情報を保存
		}
	}
	else
	{
		g_pDevKeyboard->Acquire();   //キーボードへのアクセス権を獲得
	}
}

//------------------------------------------
//キーボードのプレス情報を取得
//------------------------------------------
bool GetKeyboardPress(int nKey)
{
	return (g_aKeyState[nKey] & 0x80) ? true : false;
}

bool KeyboardTrigger(int nKey)
{
	bool Trigger = false;
	if (g_aKeyState[nKey] & 0x80 && !(g_aOldKeyState[nKey] & 0x80))
	{
		Trigger = true;
	}
	return Trigger;
}

bool KeyboardRelease(int nKey)
{
	bool Trigger = false;
	if (g_aOldKeyState[nKey] & 0x80 && !(g_aKeyState[nKey] & 0x80))
	{
		Trigger = true;
	}
	return Trigger;
}

bool KeyboardRepeat(int nKey)
{
	bool Trigger = false;
	if (g_aOldKeyState[nKey] & 0x80 && (g_aKeyState[nKey] & 0x80))
	{
		Trigger = true;
	}
	return Trigger;
}

//------------------------------------------
//ジョイパッドの初期化処理
//------------------------------------------
 HRESULT InitJoypad(void)
{
	//メモリのクリア
	memset(&g_joyKeyState, 0, sizeof(XINPUT_STATE));

	//メモリのクリア
	memset(&g_joyKeyStateTrigger, 0, sizeof(XINPUT_STATE));

	//Xinputのステートを設定(有効化)
	XInputEnable(true);

	return S_OK;
}

//------------------------------------------
//ジョイパッドの終了処理
//------------------------------------------
void UninitJoypad(void)
{
	//Xinputのステートを無効化
	XInputEnable(false);
}

//------------------------------------------
//ジョイパッドの更新処理
//------------------------------------------
void UpdateJoypad(void)
{
	XINPUT_STATE joykeyState;//入力情報を取得
	XINPUT_STATE* pStick;
	pStick = GetJoyStickAngle();

	//ジョイパッドの状態を取得
	if (XInputGetState(0, &joykeyState) == ERROR_SUCCESS)
	{
		WORD Button = joykeyState.Gamepad.wButtons;//押したときの入力情報
		WORD OldButton = g_joyKeyState.Gamepad.wButtons;//1F前の入力情報

		g_joyKeyStateTrigger.Gamepad.wButtons = Button & ~OldButton;

		g_joyKeyState = joykeyState;//ジョイパッドのプレス情報を保存(格納)
	}
}

//------------------------------------------
// ジョイパッドのプレス情報を取得
//------------------------------------------
bool GetJoypadPress(JOYKEY key)
{
	return (g_joyKeyState.Gamepad.wButtons & (0x01 << key)) ? true : false;
}

//------------------------------------------
//  パッドトリガー処理
//------------------------------------------
bool JoypadTrigger(JOYKEY key)
{
	return (g_joyKeyStateTrigger.Gamepad.wButtons & (0x01 << key)) ? true : false;
}

bool JoyPadRelease(JOYKEY key)
{
	bool joykey = false;

	if (g_OldKeyState.Gamepad.wButtons & (0x01 << key) && !(g_joyKeyState.Gamepad.wButtons & (0x01 << key)))
	{
		joykey = true;
	}
	return joykey;
}

bool JoyPadRepeat(JOYKEY key)
{
	bool joykey = false;

	if (g_OldKeyState.Gamepad.wButtons & (0x01 << key) && !(g_joyKeyState.Gamepad.wButtons & (0x01 << key)))
	{
		joykey = true;
	}
	return joykey;
}

//======================
//パッドのスティック処理
//======================
bool GetJoyStick(void)
{
	//ローカル変数宣言
	bool joykey = false;

	//中心じゃなかったら
	if (g_joyKeyState.Gamepad.sThumbLX >= 100 ||
		g_joyKeyState.Gamepad.sThumbLX <= -100 ||
		g_joyKeyState.Gamepad.sThumbLY >= 100 ||
		g_joyKeyState.Gamepad.sThumbLY <= -100)
	{
		joykey = true;
	}

	return joykey;
}

//========================
//スティック情報の取得
//========================
XINPUT_STATE* GetJoyStickAngle(void)
{
	return &g_joyKeyState;
}
