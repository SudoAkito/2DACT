//------------------------------------------
//
//         �`���[�g���A������
//       Author:Sudou Akito
//
//------------------------------------------

#include"set.h"
#include"fade.h"
#include"input.h"


//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureSet = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSet = NULL;

//------------------------------------------
//�`���[�g���A���̏���������
//------------------------------------------
void InitSet(void)
{
	LPDIRECT3DDEVICE9 pDevice;   //�f�o�C�X�ւ̃|�C���^
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\set.png",
		&g_pTextureSet);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffSet,
		NULL);

	VERTEX_2D* pVtx;       //���_���̃|�C���^

	//���_�o�b�t�@�����b�N���Ē��_���ւ̃|�C���^���擾
	g_pVtxBuffSet->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffSet->Unlock();
}

//------------------------------------------
//�`���[�g���A���̏I������
//------------------------------------------
void UninitSet(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureSet != NULL)
	{
		g_pTextureSet->Release();
		g_pTextureSet = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffSet != NULL)
	{			  
		g_pVtxBuffSet->Release();
		g_pVtxBuffSet = NULL;
	}
}

//------------------------------------------
//�`���[�g���A���̍X�V����
//------------------------------------------
void UpdateSet(void)
{
	if (KeyboardTrigger(DIK_RETURN) == true || JoypadTrigger(JOYKEY_START) == true)
	{  //����L�[�������ꂽ
		//���[�h�ݒ�(�Q�[����ʂɈڍs)
		SetFade(MODE_GAME);
	}
}


//------------------------------------------
//�`���[�g���A���̍X�V����
//------------------------------------------
void DrawSet(void)
{
	LPDIRECT3DDEVICE9 pDevice;   //�f�o�C�X�ւ̃|�C���^
		//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffSet, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureSet);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);//�v���~�e�B�u�̎��,�v���~�e�B�u�̐�
}
