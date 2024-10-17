//---------------------------
//
//�^�C�}�[����
//Author:SUDO AKITO
//
//---------------------------

#include "Timer.h"
#include "fade.h"
#include "score.h"
#include "game.h"

#define MAX_TIMER (3)	//�ő�e�N�X�`����

//�\����
typedef struct
{
	bool bUse;		//�g�p����
}Timer;

//�O���[�o���ϐ�
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTimer = NULL;		//���_�o�b�t�@�̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureTimer[MAX_TIMER] = {};	//�e�N�X�`���̃|�C���^
Timer g_Timer[MAX_TIMER];							//�^�C�}�[�\����
int g_nTimer = 0;
int g_nTimerCount = 100;

//=======================
//�^�C�}�[�̏���������
//=======================
void InitTimer(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();


	VERTEX_2D* pVtx;				//���_���̃|�C���^

	//�e�N�X�`��2�̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Number2.png",
		&g_pTextureTimer[0]);

	//�e�N�X�`��2�̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Number2.png",
		&g_pTextureTimer[1]);

	//�e�N�X�`��2�̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Number2.png",
		&g_pTextureTimer[2]);

	//�\���̏�����
	for (int nCnt = 0; nCnt < MAX_TIMER; nCnt++)
	{
		g_Timer[nCnt].bUse = true;
	}

	g_nTimer = 0;	
	g_nTimerCount = 100;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TIMER,
		D3DUSAGE_WRITEONLY, FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTimer,
		NULL);

	//���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
	g_pVtxBuffTimer->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt1 = 0; nCnt1 < MAX_TIMER; nCnt1++)
	{
		//���_���W1�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(550.0f +(60.0f* nCnt1),10.0f,0.0f);	//1�ڂ̒��_���
		pVtx[1].pos = D3DXVECTOR3(600.0f +(60.0f* nCnt1),10.0f,0.0f);	//2�ڂ̒��_���
		pVtx[2].pos = D3DXVECTOR3(550.0f +(60.0f* nCnt1),80.0f,0.0f);	//3�ڂ̒��_���
		pVtx[3].pos = D3DXVECTOR3(600.0f +(60.0f* nCnt1),80.0f,0.0f);	//4�ڂ̒��_���

		//rhw�̐ݒ�(1.0f�ŌŒ�)
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;
	}

	//�A�����b�N
	g_pVtxBuffTimer->Unlock();

}
//=======================
//�^�C�}�[�̏I������
//=======================
void UninitTimer(void)
{
	//�e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < MAX_TIMER; nCnt++)
	{
		if (g_pTextureTimer[nCnt] != NULL)
		{
			g_pTextureTimer[nCnt]->Release();
			g_pTextureTimer[nCnt] = NULL;
		}

	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffTimer != NULL)
	{
		g_pVtxBuffTimer->Release();
		g_pVtxBuffTimer = NULL;
	}


}
//=======================
//�^�C�}�[�̍X�V����
//=======================
void UpdateTimer(void)
{
	//���[�J���ϐ�
	int g_nData[MAX_TIMER] = {};

	VERTEX_2D* pVtx;		//���_���̃|�C���^

	//���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
	g_pVtxBuffTimer->Lock(0, 0, (void**)&pVtx, 0);

	g_nTimer++;				//�^�C�}�[�����Z

	if (g_nTimer >= 60)
	{
		g_nTimerCount--;	//���Ԃ�1�b���炷
		g_nTimer = 0;
	}

	g_nData[0] = g_nTimerCount % 1000 / 100;		//�S�̈�
	g_nData[1] = g_nTimerCount % 100 / 10;			//�\�̈�
	g_nData[2] = g_nTimerCount % 10 / 1;			//��̈�

	for (int nCnt = 0; nCnt < MAX_TIMER; nCnt++)
	{
		//�e�N�X�`���ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f * g_nData[nCnt]), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * g_nData[nCnt]), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (0.1f * g_nData[nCnt]), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * g_nData[nCnt]), 1.0f);

		pVtx += 4;
	}

	//�A�����b�N
	g_pVtxBuffTimer->Unlock();

}
//=======================
//�^�C�}�[�̕`�揈��
//=======================
void DrawTimer(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTimer, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < MAX_TIMER; nCnt++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureTimer[nCnt]);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
	}

}
//====================
//�^�C�}�[�̎擾
//====================
int GetTimer(void)
{
	return g_nTimerCount;
}
