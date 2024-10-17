//------------------------------------------
//
//        2DSTG
//       Author:Sudou Akito
//
//------------------------------------------
#include"main.h"
#include "player.h"
#include"input.h"
#include"block.h"
#include "background.h"
#include"title.h"
#include"game.h"
#include"result.h"
#include"fade.h"
#include"sound.h"
#include "game.h"
#include "ranking.h"
#include"set.h"

//�O���[�o���ϐ�
LPDIRECT3D9 g_pD3D = NULL;       //DirectX�I�u�W�F�N�g�ւ̃|�C���^
LPDIRECT3DDEVICE9 g_pD3DDevice;  //DirectX�f�o�C�X�ւ̃|�C���^
MODE g_mode = MODE_TITLE;        //���݂̃��[�h
FADE g_fademode;
LPD3DXFONT g_pFont = NULL;   //�t�H���g�ւ̃|�C���^
int g_nCountFPS=0;           //FPS�J�E���^�[
RECT g_windowRect;
bool g_isFullscreen = false;


//------------------------------------------
//���C���֐�
//------------------------------------------
int WINAPI WinMain(_In_ HINSTANCE hInstance,_In_opt_ HINSTANCE hInstncePrev,_In_ LPSTR lPpCmdLine,_In_ int nCmdShow)
{
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),    //WNDCLASSEX�̃������T�C�Y
		CS_CLASSDC,            //�E�B���h�E�̃X�^�C��
		WindowProc,            //�E�B ���h�E�v���V�[�W��
		0,                     //0�ɂ���i�ʏ�͎g�p���Ȃ��j
		0,                     //0�ɂ���i�ʏ�͎g�p���Ȃ��j
		hInstance,             //�C���X�^���X�n���h��
		LoadIcon(NULL,IDI_APPLICATION), //�^�X�N�o�[�̃A�C�R��
		LoadCursor(NULL,IDC_ARROW),  //�}�E�X�J�[�\��
		(HBRUSH)(COLOR_WINDOW + 1),  //�N���C�A���g�̈�̔w�i�F
		NULL,                        //���j���[�o�[
		CLASS_NAME,                  //�E�B���h�E�N���X�̃A�C�R��
		LoadIcon(NULL,IDI_APPLICATION), //�t�@�C���̃A�C�R��
	};

	DWORD dwCurrentTime;   //���ݎ���
	DWORD dwExecLastTime;  //�Ō�ɏ�����������
	HWND hWnd;  //�E�B���h�E�n���h���i���ʎq�j
	MSG msg;    //���b�Z�[�W���i�[����ϐ�

	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };    //��ʃT�C�Y�̍\����

	//�E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	//�N���C�A���g�̈���w��̃T�C�Y�ɒ���
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//�E�B���h�E�𐶐�
	hWnd = CreateWindowEx(0,      //�g���E�B���h�E�X�^�C��
		CLASS_NAME,             //�E�B���h�E�N���X�̖��O
		WINDOW_NAME,            //�E�B���h�E�̖��O
		WS_OVERLAPPEDWINDOW,    //�E�B���h�E�X�^�C��
		CW_USEDEFAULT,          //�E�B���h�E�̍���X���W
		CW_USEDEFAULT,          //�V����Y���W
		(rect.right-rect.left),//�V��
		(rect.bottom - rect.top),//�V����
		NULL,					//�e�E�B���h�E�̃n���h��
		NULL,					//���j���[�n���h���܂��͎q�E�B���h�EID
		hInstance,				//�C���X�^���X�n���h��
		NULL);                  //�E�B���h�E�쐬�f�[�^

	//����������
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{
		return -1;
	}

	g_fademode = FADE_IN;

	//����\��ݒ�
	timeBeginPeriod(1);
	dwCurrentTime = 0;                //����������
	dwExecLastTime = timeGetTime();   //���ݎ������擾�i�ۑ��j

	ShowWindow(hWnd, nCmdShow);    //�E�B���h�E�̕\����Ԃ�ݒ�
	UpdateWindow(hWnd);            //�N���C�A���g�̈���X�V

	DWORD dwFrameCount;   //�t���[���J�E���g
	DWORD dwFPSLastTime;  //�Ō��FPS���v����������

	dwFrameCount = 0;
	dwFPSLastTime = timeGetTime();

	//���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//window�̏���
			if (msg.message == WM_QUIT)
			{//WM_QUIT���b�Z���󂯎�����烁�b�Z���[�v�𔲂���
				break;
			}
			else
			{
				//���b�Z�[�W�̐ݒ�
				TranslateMessage(&msg);   //���z���b�Z�[�W�𕶎����b�Z�[�W��
				DispatchMessage(&msg);    //�E�B���h�E�v���V�[�W���փ��b�Z�[�W�𑗏o
			}
		}
		else
		{//DirectX�̍X�V

			dwCurrentTime = timeGetTime();   //���ݎ������擾

			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{//0.5�b�o��
				//FPS���v��
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);

				dwFPSLastTime = dwCurrentTime;    //FPS�𑪒肵��������ۑ�

				dwFrameCount = 0;                 //�t���[���J�E���g�N���A
			}
			if ((dwCurrentTime- dwExecLastTime)>=(1000/60))
			{//60����1�b�o��
				dwExecLastTime = dwCurrentTime;  //�����J�n�̎���[���ݎ���]��ۑ�

				dwCurrentTime = timeGetTime();   //���ݎ������擾

				dwFrameCount++;                  //�t���[���J�E���g�����Z

				//�X�V����
				Update();

				//�`�揈��
				Draw();
			}
		}
	}

	//�I������
	Uninit();

	//����\��߂�
	timeEndPeriod(1);

	//�E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return(int)msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	const RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };  //�E�B���h�E�̗̈�(��`)

	switch (uMsg)
	{
	case WM_DESTROY:   //�E�B���h�E�j���̃��b�Z�[�W
		//WM_QUIT���b�Z�[�W�𑗂�
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN: //�L�[�����̃��b�Z�[�W
		switch (wParam)
		{
			case VK_ESCAPE: //[ESC]�L�[��������
				DestroyWindow(hWnd);
				break;

			case VK_F11:
				ToggleFullscreen(hWnd);
				break;
		}
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);   //����̏�����Ԃ�
}

//------------------------------------------
// ����������
//------------------------------------------
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;           //�f�B�X�v���C���[�h
	D3DPRESENT_PARAMETERS d3dpp;    //�v���[���e�[�V�����p�����[�^�[

	//DirectX3D�I�u�W�F�̐���
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	//���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	//�v���[���e�[�V�����p�����[�^�[�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));    //�p�����[�^�̃[���N���A

	d3dpp.BackBufferWidth = SCREEN_WIDTH; //�Q�[����ʂ̃T�C�Y�i���j

	d3dpp.BackBufferHeight = SCREEN_HEIGHT;//�Q�[����ʂ̃T�C�Y�i�����j

	d3dpp.BackBufferFormat = d3ddm.Format; //�o�b�N�o�b�t�@�̌`��
	 
	d3dpp.BackBufferCount = 1;             //�o�b�N�o�b�t�@�̐�

	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD; //�_�u���o�b�t�@�̐؂�ւ��i�f���M���ɓ����j

	d3dpp.EnableAutoDepthStencil = TRUE;      //�f�v�X�o�b�t�@�ƃX�e���V���o�b�t�@���쐬

	d3dpp.AutoDepthStencilFormat = D3DFMT_D16; //�f�v�X�o�b�t�@�Ƃ���16bit���g��

	d3dpp.Windowed = bWindow;                 //�E�B���h�E���[�h

	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;  //���t���b�V�����[�g

	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;   //�C���^�[�o��

	//DirectX3D�f�o�C�X�̐����i�`�揈���ƒ��_�������n�[�h�E�F�A�ōs���j
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice)))

	{///DirectX3D�f�o�C�X�̐����i�`�揈�����n�[�h�E�F�A,���_������CPU�ōs���j
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))
		{
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_HAL,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&g_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}

	//�����_�[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE,D3DCULL_CCW);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//�T���v���[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	//�e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	//�f�o�b�O�\���p�t�H���g�̐���
	D3DXCreateFont(g_pD3DDevice,18, 0, 0, 0,
		FALSE, SHIFTJIS_CHARSET, 
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, 
		"Terminal", &g_pFont);

	if (FAILED(InitKeyBoard(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	if (FAILED(InitJoypad()))
	{
		return E_FAIL;
	}

	//�T�E���h�ݒ�
	InitSound(hWnd);

	//���[�h�ݒ�
	SetMode(g_mode);

	//�t�F�[�h�̐ݒ�
	InitFade(g_mode);

	//�`���[�g���A��
	InitSet();

	return S_OK;
}

//------------------------------------------
//�I������
//------------------------------------------
void Uninit(void)
{//�^�C�g���I������
	UninitTitle();

	//�`���[�g���A��
	UninitSet();

	//�Q�[����ʏI������
	UninitGame();

	//���U���g��ʂ̏I������
	UninitResult();

	//�T�E���h�I������
	UninitSound();

	//�L�[�{�[�h�̏I������
	UninitKeyBoard();

	//�W���C�p�b�h�̏I������
	UninitJoypad();

	//�t�F�[�h�̏I��
	UninitFade();

	//�f�o�b�O�\���p�t�H���g�̔j��
	if (g_pFont != NULL)
	{
		g_pFont->Release();
		g_pFont = NULL;
	}

	//Direct3D�f�o�C�X�̔j��
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}

	
}

//------------------------------------------
//�X�V����
//------------------------------------------
void Update(void)
{
	//�L�[�{�[�h�X�V����
	UpdateKeyBoard();

	//�W���C�p�b�h�X�V����
	UpdateJoypad();

	switch (g_mode)
	{
	case MODE_TITLE:   //�^�C�g�����
		UpdateTitle();
		break;

	case MODE_SET:    //�`���[�g���A�����

		UpdateSet();
		break;

	case MODE_GAME:   //�Q�[�����
		UpdateGame();
		break;

	case MODE_RESULT:  //���U���g���
		UpdateResult();
		break;
	case MODE_RANKING:
		UpdateRanking();
		break;
	}

	//�t�F�[�h�X�V
	UpdateFade();
}

//------------------------------------------
//�`�揈��
//------------------------------------------
void Draw(void)
{
	//��ʃN���A
	g_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	//�`��J�n
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		switch (g_mode)
		{
		case MODE_TITLE:
			DrawTitle();
			DrawT();
			break;

		case MODE_SET:
			DrawSet();
			break;

		case MODE_GAME:
			DrawGame();
			break;

		case MODE_RESULT:
			DrawResult();
			break;

		case MODE_RANKING:
			DrawBG();
			DrawRanking();
			break;

		}

		//�t�F�[�h�̍X�V����
		DrawFade();

#ifdef _DEBUG
		//FPS�̕\��
		DrawFPS();
#endif
		//�`��I��
		g_pD3DDevice->EndScene();
	}
	
	//�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�����ւ���
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//------------------------------------------
//���[�h�̐ݒ�
//------------------------------------------
void SetMode(MODE mode)
{
	//���݂̃��[�h�̏I������
	switch (g_mode)
	{
	case MODE_TITLE:
		//�^�C�g���I������
		UninitTitle();
		break;

	case MODE_SET:
		UninitSet();
		break;

	case MODE_GAME:
		//�Q�[����ʏI������
		UninitGame();
		break;

	case MODE_RESULT:
		//���U���g��ʂ̏I������
		UninitResult();
		break;

	case MODE_RANKING:
		UninitRanking();
		break;
	}

	//�V�������[�h�̏���������
	switch (mode)
	{
	case MODE_TITLE:
		InitTitle();
		break;

	case MODE_SET:
		InitSet();
		break;

	case MODE_GAME:
		InitGame();
		break;

	case MODE_RESULT:
		InitResult();
		break;

	case MODE_RANKING:
		InitRanking();
		break;
	}

	g_mode = mode;    //���݂̃��[�h��؂�ւ���
}

//------------------------------------------
//���[�h�̎擾
//------------------------------------------
MODE GetMode(void)
{
	return g_mode;
}

LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}


//------------------------------------------
//FPS�\������(�f�o�b�O��p)
//------------------------------------------
void DrawFPS(void)
{
	RECT rect = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};

	char aStr[256];

	//������ɑ��
	wsprintf(&aStr[0], "FPS:%d\n", g_nCountFPS);

	//�e�L�X�g��`��
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));

}
//------------------------------------------
//ENEMY�\������(�f�o�b�O��p)
//------------------------------------------
void DrawEnemyCnt(int nNumEnemy)
{
	RECT rectenemy = { 0,20,SCREEN_WIDTH,SCREEN_HEIGHT };

	char aStr[256];

	//������ɑ��
	wsprintf(&aStr[0], "�G�̑���:%d\n", nNumEnemy);

	//�e�L�X�g��`��
	g_pFont->DrawText(NULL, &aStr[0], -1, &rectenemy, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));

}

//------------------------------------------
// �E�B���h�E���t���X�N���[���ɕς��鏈��
//------------------------------------------
void ToggleFullscreen(HWND hWnd)
{
	// ���݂̃E�B���h�E�X�^�C�����擾
	DWORD dwStyle = GetWindowLong(hWnd, GWL_STYLE);

	if (g_isFullscreen)
	{
		// �E�B���h�E���[�h�ɐ؂�ւ�
		SetWindowLong(hWnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPos(hWnd, HWND_TOP, g_windowRect.left, g_windowRect.top,
			g_windowRect.right - g_windowRect.left, g_windowRect.bottom - g_windowRect.top,
			SWP_FRAMECHANGED | SWP_NOACTIVATE);
		ShowWindow(hWnd, SW_NORMAL);
	}
	else
	{
		// �t���X�N���[�����[�h�ɐ؂�ւ�
		GetWindowRect(hWnd, &g_windowRect);
		SetWindowLong(hWnd, GWL_STYLE, dwStyle & ~WS_OVERLAPPEDWINDOW);
		SetWindowPos(hWnd, HWND_TOP, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN),
			SWP_FRAMECHANGED | SWP_NOACTIVATE);
		ShowWindow(hWnd, SW_MAXIMIZE);
	}

	g_isFullscreen = !g_isFullscreen;
}