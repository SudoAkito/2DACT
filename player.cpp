//------------------------------------------
//
//       �v���C���[����
//       Author:Sudou Akito
//
//------------------------------------------

#include"player.h"
#include "input.h"
#include "block.h"
#include"bullet.h"
#include "Life.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer= NULL;

int g_nCounterAnimPlayer;    //�A�j���[�V�����J�E���^�[
int g_nPatternAnimPlayer;    //�A�j���[�V�����p�^�[��NO.

Player g_player;

//------------------------------------------
//�v���C���[����������
//------------------------------------------
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;   //�f�o�C�X�ւ̃|�C���^
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\player.png",
		&g_pTexturePlayer);

	g_player.pos = D3DXVECTOR3(200.0f, 640.0f, 0.0f);  //�ʒu������
	g_player.move = D3DXVECTOR3(0.0f,0.0f,0.0f);	      //�ړ��ʏ�����
	g_player.rot = D3DXVECTOR3(0.0f,0.0f,0.0f);        //�����̏�����
	g_player.nLife = 3;
	g_player.bDisp = true;
	g_player.bJump = false;

	//�Ίp���̒����̎Z�o
	g_player.fLength = sqrtf(MAX_SIZE*MAX_SIZE)+(MAX_SIZE*MAX_SIZE) / 2.0f;

	//�Ίp���̊p�x���Z�o
	g_player.fAngle = atan2f(MAX_SIZE, MAX_SIZE);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPlayer,
		NULL);

	VERTEX_2D* pVtx;       //���_���̃|�C���^

	//���_�o�b�t�@�����b�N���Ē��_���ւ̃|�C���^���擾
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos.x = g_player.pos.x - (MAX_X/2.0f);
	pVtx[0].pos.y = g_player.pos.y - MAX_Y;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = g_player.pos.x + (MAX_X/2.0f);
	pVtx[1].pos.y = g_player.pos.y - MAX_Y;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = g_player.pos.x - (MAX_X/2.0f);
	pVtx[2].pos.y = g_player.pos.y;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = g_player.pos.x + (MAX_X/2.0f);
	pVtx[3].pos.y = g_player.pos.y;
	pVtx[3].pos.z = 0.0f;

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.25f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPlayer->Unlock();
}

//------------------------------------------
//�v���C���[�̏I������
//------------------------------------------
void UninitPlayer(void)
{

	//�e�N�X�`���̔j��
	if (g_pTexturePlayer != NULL)
	{
		g_pTexturePlayer->Release();
		g_pTexturePlayer = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPlayer != NULL)
	{
		g_pVtxBuffPlayer->Release();
		g_pVtxBuffPlayer = NULL;
	}
}

//------------------------------------------
//�v���C���[�̍X�V����
//------------------------------------------
void UpdatePlayer(void)
{
	SetLife(g_player.nLife);

	GetKeyPlayer();
}

//------------------------------------------
//�v���C���[�̕`�揈��
//------------------------------------------
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;   //�f�o�C�X�ւ̃|�C���^
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPlayer, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturePlayer);

	//�v���C���[�̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);//�v���~�e�B�u�̎��,�v���~�e�B�u�̐�
}
	
//------------------------------------------
// �v���C���[���̎擾
//------------------------------------------
Player* GetPlayer(void)
{
	return &g_player;
}

//------------------------------------------
// �����蔻���̏���
//------------------------------------------
void HitPlayer(int nDmg)
{
	VERTEX_2D* pVtx;//���_���̃|�C���^

	g_player.nLife -= nDmg;
	//���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);
	if (g_player.nLife <= 0)
	{
		g_player.bDisp = false;
		g_player.state1 = PLAYERSTATE_DEATH;
		g_player.nCounterState1 = 60;
	}
	else
	{
		g_player.state1 = PLAYERSTATE_DAMAGE;
		g_player.nCounterState1 = 5;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);
	}
	//�A�����b�N
	g_pVtxBuffPlayer->Unlock();
}


//------------------------------------------
// �L�[���͂̏���
//------------------------------------------
void GetKeyPlayer(void)
{
	VERTEX_2D* pVtx;        //���_���̃|�C���^
	static float fData = 0.2;

	if (GetKeyboardPress(DIK_A) == true)
	{//������
		fData = 0.2;
		g_player.move.x -= 0.4f;
	}
	else if (GetKeyboardPress(DIK_D) == true)
	{
		fData = -0.2;
		//�E����
		g_player.move.x += 0.4f;

	}
		//�����E
	if (g_player.pos.x + (MAX_X / 2) < 0.0f)
	{
		g_player.pos.x = SCREEN_WIDTH + (MAX_X / 2);
	}
	//�E����
	else if (g_player.pos.x - (MAX_X / 2) > SCREEN_WIDTH)
	{
		g_player.pos.x = (MAX_X / 2);
	}

	if (g_player.bJump == false)
	{
		if (GetKeyboardPress(DIK_SPACE) == true)
		{
			g_player.move.y = FJUMP;
			g_player.bJump = true;
		}

	}

	if (KeyboardTrigger(DIK_Q) == true)
	{
		SetBullet(D3DXVECTOR3(g_player.pos.x,g_player.pos.y-MAX_Y/2,0.0f), D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI) * MAX_SPEED, cosf(g_player.rot.z + D3DX_PI) * MAX_SPEED, 0.0f), g_player.rot, g_player.fLength, 150, BULLETTYPE_PLAYER);;
	}

	//�O��̈ʒu��ۑ�
	g_player.posOld = g_player.pos;

	g_player.move.y += FDA;   //�d�͉��Z

	//�ʒu���X�V
	g_player.pos.x += g_player.move.x;
	g_player.pos.y += g_player.move.y;

	if (CollsionBlock(&g_player.pos,        //�ڒn���ɂ̂݃W�����v�\�ɂ��� 
		&g_player.posOld,
		&g_player.move,
		MAX_X,
		MAX_Y) == true)
	{
		g_player.bJump = false;
	}

	//�ړ��ʂ��X�V(����������)
	g_player.move.x += (0.0f - g_player.move.x) * 0.09f;

	if (g_player.pos.y > SCREEN_HEIGHT)
	{
		g_player.pos.y = SCREEN_HEIGHT;
		g_player.move.y = 0.0f;
		g_player.bJump = false;
	}

	g_nCounterAnimPlayer++;

	if ((g_nCounterAnimPlayer % 4) == 0)
	{
		g_nPatternAnimPlayer = (g_nPatternAnimPlayer + 1) % MAX_PLAYPATTERN;   //�p�^�[��No.���X�V����

		//���_�o�b�t�@�����b�N���Ē��_���ւ̃|�C���^���擾
		g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);
		//�e�N�X�`�����W�̐ݒ�
		if (GetKeyboardPress(DIK_A) == true || GetKeyboardPress(DIK_D) == true)
		{
			//��
			pVtx[0].tex = D3DXVECTOR2(g_nPatternAnimPlayer * 0.25f, (g_nPatternAnimPlayer / 5) * 1.0f);
			pVtx[1].tex = D3DXVECTOR2(fData + g_nPatternAnimPlayer * 0.25f, (g_nPatternAnimPlayer / 5) * 1.0f);
			pVtx[2].tex = D3DXVECTOR2(g_nPatternAnimPlayer * 0.25f, (g_nPatternAnimPlayer / 5) * 1.0f + 1.0f);
			pVtx[3].tex = D3DXVECTOR2(fData + g_nPatternAnimPlayer * 0.25f, (g_nPatternAnimPlayer / 5) * 1.0f + 1.0f);
		}
		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffPlayer->Unlock();
	}

	//���_�o�b�t�@�����b�N���Ē��_���ւ̃|�C���^���擾
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos.x = g_player.pos.x - (MAX_X / 2.0f);
	pVtx[0].pos.y = g_player.pos.y - MAX_Y;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = g_player.pos.x + (MAX_X / 2.0f);
	pVtx[1].pos.y = g_player.pos.y - MAX_Y;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = g_player.pos.x - (MAX_X / 2.0f);
	pVtx[2].pos.y = g_player.pos.y;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = g_player.pos.x + (MAX_X / 2.0f);
	pVtx[3].pos.y = g_player.pos.y;
	pVtx[3].pos.z = 0.0f;

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPlayer->Unlock();
}