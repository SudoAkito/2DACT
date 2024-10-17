//------------------------------------------
//
//         ���͏���
//       Author:Sudou Akito
//
//------------------------------------------

#include"input.h"

//�}�N����`
#define NUM_KEY_MAX (256)  //�L�[�̍ő吔

//�O���[�o���ϐ�
XINPUT_STATE g_joyKeyState;        //�W���C�p�b�h�̃v���X���
XINPUT_STATE g_joyKeyStateTrigger;//�W���C�p�b�h�̃g���K�[���
XINPUT_STATE g_OldKeyState;
LPDIRECTINPUT8 g_pInput = NULL;    //DirectInput�I�u�W�F�ւ̃|�C���^
LPDIRECTINPUTDEVICE8 g_pDevKeyboard = NULL; //���̓f�o�C�X�i�L�[�{�[�h�j�ւ̃|�C���^
BYTE g_aKeyState[NUM_KEY_MAX];
BYTE g_aOldKeyState[NUM_KEY_MAX];

HRESULT InitKeyBoard(HINSTANCE hInstance, HWND hWnd)
{
	//Direct�I�u�W�F�̐���
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, 
		(void**)&g_pInput, NULL)))
	{
		return E_FAIL;
	}

	//���̓f�o�C�X�i�L�[�{�[�h�j�̐���
	if (FAILED(g_pInput->CreateDevice(GUID_SysKeyboard, &g_pDevKeyboard, NULL)))
	{
		return E_FAIL;
	}

	//�f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	//�������[�h�̐ݒ�
	if (FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	g_pDevKeyboard->Acquire();

	return S_OK;
}

void UninitKeyBoard(void)
{
	//���̓f�o�C�X�̔j��
	if (g_pDevKeyboard != NULL)
	{
		g_pDevKeyboard->Unacquire();  //�L�[�{�[�h�ւ̃A�N�Z�X����j��
		g_pDevKeyboard->Release();
		g_pDevKeyboard = NULL;
	}

	//DirectInput�I�u�W�F�̔j��
	if (g_pInput != NULL)	
	{
		g_pInput->Release();
		g_pInput = NULL;
	}
}

void UpdateKeyBoard(void)
{
	BYTE aKeyState[NUM_KEY_MAX];  //�L�[�{�[�h�̓��͏��
	int nCntKey;

	for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
	{
		g_aOldKeyState[nCntKey] = g_aKeyState[nCntKey];  //�ЂƂO�̏����擾
	}
	//���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			g_aKeyState[nCntKey] = aKeyState[nCntKey];//�L�[�{�[�h�̃u���X����ۑ�
		}
	}
	else
	{
		g_pDevKeyboard->Acquire();   //�L�[�{�[�h�ւ̃A�N�Z�X�����l��
	}
}

//------------------------------------------
//�L�[�{�[�h�̃v���X�����擾
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
//�W���C�p�b�h�̏���������
//------------------------------------------
 HRESULT InitJoypad(void)
{
	//�������̃N���A
	memset(&g_joyKeyState, 0, sizeof(XINPUT_STATE));

	//�������̃N���A
	memset(&g_joyKeyStateTrigger, 0, sizeof(XINPUT_STATE));

	//Xinput�̃X�e�[�g��ݒ�(�L����)
	XInputEnable(true);

	return S_OK;
}

//------------------------------------------
//�W���C�p�b�h�̏I������
//------------------------------------------
void UninitJoypad(void)
{
	//Xinput�̃X�e�[�g�𖳌���
	XInputEnable(false);
}

//------------------------------------------
//�W���C�p�b�h�̍X�V����
//------------------------------------------
void UpdateJoypad(void)
{
	XINPUT_STATE joykeyState;//���͏����擾
	XINPUT_STATE* pStick;
	pStick = GetJoyStickAngle();

	//�W���C�p�b�h�̏�Ԃ��擾
	if (XInputGetState(0, &joykeyState) == ERROR_SUCCESS)
	{
		WORD Button = joykeyState.Gamepad.wButtons;//�������Ƃ��̓��͏��
		WORD OldButton = g_joyKeyState.Gamepad.wButtons;//1F�O�̓��͏��

		g_joyKeyStateTrigger.Gamepad.wButtons = Button & ~OldButton;

		g_joyKeyState = joykeyState;//�W���C�p�b�h�̃v���X����ۑ�(�i�[)
	}
}

//------------------------------------------
// �W���C�p�b�h�̃v���X�����擾
//------------------------------------------
bool GetJoypadPress(JOYKEY key)
{
	return (g_joyKeyState.Gamepad.wButtons & (0x01 << key)) ? true : false;
}

//------------------------------------------
//  �p�b�h�g���K�[����
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
//�p�b�h�̃X�e�B�b�N����
//======================
bool GetJoyStick(void)
{
	//���[�J���ϐ��錾
	bool joykey = false;

	//���S����Ȃ�������
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
//�X�e�B�b�N���̎擾
//========================
XINPUT_STATE* GetJoyStickAngle(void)
{
	return &g_joyKeyState;
}
