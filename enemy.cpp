//------------------------------------------
//
//			   �G����
//         Author:Sudou Akito
//
//------------------------------------------

//#include"bullet.h"
#include"enemy.h"
#include"explosion.h"
#include "score.h"
#include "player.h"
#include"game.h"
#include"partycle.h"

//�}�N����`
#define NUM_ENEMY (2)                 //�G�̎��

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_apTextureEnemy[ENEMYTYPE_MAX] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;
Enemy g_aEnemy[MAX_ENEMY];      //�G�̏��
int g_nNumEnemy;            //�G�̑���

//------------------------------------------
//�G�̏���������
//------------------------------------------
void InitEnemy(void)
{

	int nCntEN{};

	LPDIRECT3DDEVICE9 pDevice;   //�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();


	for (int n = 0; n < ENEMYTYPE_MAX; n++)
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			ENEMYTEX[n],
			&g_apTextureEnemy[n]);
	}

	//�G�̏�����
	for (nCntEN = 0; nCntEN <MAX_ENEMY ; nCntEN++)
	{
		g_aEnemy[nCntEN].pos= D3DXVECTOR3(0.0f,0.0f,0.0f);
		g_aEnemy[nCntEN].move= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEN].rot= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEN].state = {};
		g_aEnemy[nCntEN].nCounterState=0;
		g_aEnemy[nCntEN].nLife=0;
		g_aEnemy[nCntEN].nType=0;
		g_aEnemy[nCntEN].bUse=false;
		g_aEnemy[nCntEN].fLength=0;
		g_aEnemy[nCntEN].fAngle = 0;
	}
	g_nNumEnemy = 0;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4*MAX_ENEMY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEnemy,
		NULL);

	VERTEX_2D* pVtx;        //���_���̃|�C���^

//���_�o�b�t�@�����b�N���Ē��_���ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEN = 0; nCntEN < MAX_ENEMY; nCntEN++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

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

		pVtx += 4;
	}
	
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEnemy->Unlock();
}

//------------------------------------------
//�G�̏I������
//------------------------------------------
void UninitEnemy(void)
{
	int nCntEN;

	//�e�N�X�`���̔j��
	for (nCntEN = 0; nCntEN < ENEMYTYPE_MAX; nCntEN++)
	{
		if (g_apTextureEnemy[nCntEN] != NULL)
		{
			g_apTextureEnemy[nCntEN]->Release();
			g_apTextureEnemy[nCntEN] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffEnemy != NULL)
	{
		g_pVtxBuffEnemy->Release();
		g_pVtxBuffEnemy = NULL;
	}
}

//------------------------------------------
// �G�̍X�V����
//------------------------------------------
void UpdateEnemy(void)
{
	int nCntEN{};

	VERTEX_2D* pVtx;        //���_���̃|�C���^

	// �v���C���[�̈ʒu���擾����
	D3DXVECTOR3 playerPos = GetPlayer()->pos;

	//���_�o�b�t�@�����b�N���Ē��_���ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	
	for (nCntEN = 0; nCntEN < MAX_ENEMY; nCntEN++)
	{
		float fspeed = (float)(rand() % 7) + 0.5f;

		if (g_aEnemy[nCntEN].bUse == true)
		{

			// �v���C���[ (�^�[�Q�b�g) �Ƃ̍������߂�
			D3DXVECTOR3 diff = playerPos - g_aEnemy[nCntEN].pos;

			// �p�x�����߂�
			float fAngle = atan2f(diff.x, diff.y);

			// �ړ��ʂ��X�V���� (����)
			/*g_aEnemy[nCntEN].move.x = sinf(fAngle) * fspeed;
			g_aEnemy[nCntEN].move.y = cosf(fAngle) * fspeed;*/

			//�ʒu���X�V
			g_aEnemy[nCntEN].pos.x += g_aEnemy[nCntEN].move.x;
			g_aEnemy[nCntEN].pos.y += g_aEnemy[nCntEN].move.y;

			pVtx[0].pos.x = g_aEnemy->pos.x - (MAX_X / 2.0f);
			pVtx[0].pos.y = g_aEnemy->pos.y - MAX_Y;
			pVtx[0].pos.z = 0.0f;

			pVtx[1].pos.x = g_aEnemy->pos.x + (MAX_X / 2.0f);
			pVtx[1].pos.y = g_aEnemy->pos.y - MAX_Y;
			pVtx[1].pos.z = 0.0f;

			pVtx[2].pos.x = g_aEnemy->pos.x - (MAX_X / 2.0f);
			pVtx[2].pos.y = g_aEnemy->pos.y;
			pVtx[2].pos.z = 0.0f;

			pVtx[3].pos.x = g_aEnemy->pos.x + (MAX_X / 2.0f);
			pVtx[3].pos.y = g_aEnemy->pos.y;
			pVtx[3].pos.z = 0.0f;

			switch (g_aEnemy[nCntEN].state)
			{
			case ENEMYSTATE_NORMAL:
				/*g_aEnemy[nCntEN].nunti++;
				if (g_aEnemy[nCntEN].nunti >= 30)
				{
					SetBullet(g_aEnemy[nCntEN].pos, D3DXVECTOR3(sinf(g_aEnemy[nCntEN].rot.z + D3DX_PI) * MAX_SPEED, cosf(g_aEnemy[nCntEN].rot.z + D3DX_PI) * MAX_SPEED, 0.0f), g_aEnemy[nCntEN].rot, g_aEnemy[nCntEN].fLength, 150, BULLETTYPE_ENEMY);
					g_aEnemy[nCntEN].nunti = 0;
				}
				break;*/

			case ENEMYSTATE_DAMAGE:

				g_aEnemy[nCntEN].nCounterState--;
				if (g_aEnemy[nCntEN].nCounterState <= 0)
				{
					g_aEnemy[nCntEN].state = ENEMYSTATE_NORMAL;
					//���_�J���[�̐ݒ�
					pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

				}
				break;
			}
		}
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEnemy->Unlock();
}

//------------------------------------------
// �G�̕`�揈��
//------------------------------------------
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;   //�f�o�C�X�ւ̃|�C���^
	int nCntEN;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffEnemy, 0, sizeof(VERTEX_2D));

	for (nCntEN = 0; nCntEN < MAX_ENEMY; nCntEN++)
	{
		if (g_aEnemy[nCntEN].bUse == true)
		{
			int nType = g_aEnemy[nCntEN].nType;

			//�e�N�X�`���̐ݒ�

			pDevice->SetTexture(0, g_apTextureEnemy[nType]);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,4 * nCntEN,2);//�v���~�e�B�u�̎��,�v���~�e�B�u�̐�
		}
	}

#ifdef _DEBUG

	// �G�̕\��
	DrawEnemyCnt(g_nNumEnemy);

#endif // _DEBUG

}

//------------------------------------------
// �G�̃Z�b�g����
//------------------------------------------
void SetEnemy(D3DXVECTOR3 pos, int nType)
{
	int nCntEN;
	VERTEX_2D* pVtx;        //���_���̃|�C���^

	//���_�o�b�t�@�����b�N���Ē��_���ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEN = 0; nCntEN < MAX_ENEMY; nCntEN++)
	{
		if(g_aEnemy[nCntEN].bUse == false)
		{//�G���g�p����Ă��Ȃ�

			//�G�̏��̐ݒ�
			g_aEnemy[nCntEN].pos= pos;
			g_aEnemy[nCntEN].state = ENEMYSTATE_NORMAL;
			g_aEnemy[nCntEN].nCounterState = 0;//��ԊǗ��J�E���^�[
			g_aEnemy[nCntEN].nLife = 5;        //�̗�
			g_aEnemy[nCntEN].nType = nType;
		
			//���_���W�̐ݒ�
			g_aEnemy[nCntEN].pos.x += g_aEnemy[nCntEN].move.x;
			g_aEnemy[nCntEN].pos.y += g_aEnemy[nCntEN].move.y;

			pVtx[0].pos.x = g_aEnemy->pos.x - (MAX_X / 2.0f);
			pVtx[0].pos.y = g_aEnemy->pos.y - MAX_Y;
			pVtx[0].pos.z = 0.0f;

			pVtx[1].pos.x = g_aEnemy->pos.x + (MAX_X / 2.0f);
			pVtx[1].pos.y = g_aEnemy->pos.y - MAX_Y;
			pVtx[1].pos.z = 0.0f;

			pVtx[2].pos.x = g_aEnemy->pos.x - (MAX_X / 2.0f);
			pVtx[2].pos.y = g_aEnemy->pos.y;
			pVtx[2].pos.z = 0.0f;

			pVtx[3].pos.x = g_aEnemy->pos.x + (MAX_X / 2.0f);
			pVtx[3].pos.y = g_aEnemy->pos.y;
			pVtx[3].pos.z = 0.0f;
			g_aEnemy[nCntEN].bUse = true;
			g_nNumEnemy++;
			break;
		}
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEnemy->Unlock();
}
//------------------------------------------
//�G�̏��
//------------------------------------------
Enemy* GetEnemy(void)
{
	return &g_aEnemy[0];
}

//------------------------------------------
// �G�̓����蔻��̌㏈��
//------------------------------------------
void HitEnemy(int nCntEn, int nDmg)
{
	VERTEX_2D* pVtx;        //���_���̃|�C���^

	g_aEnemy[nCntEn].nLife -= nDmg;

	//���_�o�b�t�@�����b�N���Ē��_���ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	if (g_aEnemy[nCntEn].nLife<=0||g_aEnemy[nCntEn].nType == 0)
	{
		SetExplosion(g_aEnemy[nCntEn].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), g_aEnemy[nCntEn].rot, g_aEnemy[nCntEn].fLength);
		g_aEnemy[nCntEn].bUse = false;
		SetPartycle(g_aEnemy[nCntEn].pos);
  		AddScore(250);
   		g_nNumEnemy--;                //�G�̑����J�E���g�_�E��
	}
	else if (g_aEnemy[nCntEn].nLife <= 0 || g_aEnemy[nCntEn].nType == 1)
	{
		SetExplosion(g_aEnemy[nCntEn].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), g_aEnemy[nCntEn].rot, g_aEnemy[nCntEn].fLength);
		g_aEnemy[nCntEn].bUse = false;
		SetPartycle(g_aEnemy[nCntEn].pos);
		AddScore(500);
		g_nNumEnemy--;                //�G�̑����J�E���g�_�E��
	}
	else if (g_aEnemy[nCntEn].nLife <= 0 || g_aEnemy[nCntEn].nType == 2)
	{
		SetExplosion(g_aEnemy[nCntEn].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), g_aEnemy[nCntEn].rot, g_aEnemy[nCntEn].fLength);
		g_aEnemy[nCntEn].bUse = false;
		SetPartycle(g_aEnemy[nCntEn].pos);
		AddScore(1000);
		g_nNumEnemy--;                //�G�̑����J�E���g�_�E��
	}
	else
	{
		g_aEnemy[nCntEn].state=ENEMYSTATE_DAMAGE;
 		g_aEnemy[nCntEn].nCounterState = 5;

		pVtx += 4 * nCntEn;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0 ,255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 0 ,0, 255);
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEnemy->Unlock();
}

int GetNumEnemy()
{
	return g_nNumEnemy;
}

