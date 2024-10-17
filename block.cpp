 //-----------------------------------------
//
//         �u���b�N�̏o�͏���
//       Author:Sudou Akito
//
//------------------------------------------
#include"block.h"
#include"player.h"

//�u���b�N�̍\����
typedef struct
{
	D3DXVECTOR3 pos;    //�ʒu
	float fWidth;       //��
	float fHeight;      //����
	bool bUse;          //�g�p���Ă��邩�ǂ���
}Block;

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureBlock = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBlock = NULL;
Block g_aBlock[MAX_BLOCK];

//------------------------------------------
//�e�̏���������
//------------------------------------------
void InitBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBlock;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\block.png",
		&g_pTextureBlock);

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		g_aBlock[nCntBlock].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBlock[nCntBlock].bUse = false;   //�g�p���Ă��Ȃ���Ԃɂ���

		g_aBlock[nCntBlock].fWidth = 0;

		g_aBlock[nCntBlock].fWidth = 0;
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4*MAX_BLOCK,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBlock,
		NULL);

	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���Ē��_���ւ̃|�C���^���擾
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < MAX_BLOCK; i++)
	{//���_���W�̐ݒ�
		pVtx[0].pos.x = 0.0f;
		pVtx[0].pos.y = 0.0f;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = 0.0f;
		pVtx[1].pos.y = 0.0f;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = 0.0f;
		pVtx[2].pos.y = 0.0f;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = 0.0f;
		pVtx[3].pos.y = 0.0f;
		pVtx[3].pos.z = 0.0f;
		//rhw�̐ݒ�
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
		pVtx[1].tex = D3DXVECTOR2(16.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(16.0f, 1.0f);

		pVtx += 4;
	}
		g_pVtxBuffBlock->Unlock();
}

//------------------------------------------
//�v���C���[�̏I������
//------------------------------------------
void UninitBlock(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureBlock != NULL)
	{
		g_pTextureBlock->Release();
		g_pTextureBlock = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffBlock != NULL)
	{
		g_pVtxBuffBlock->Release();
		g_pVtxBuffBlock = NULL;
	}
}

//------------------------------------------
//�e�̍X�V����
//------------------------------------------
void UpdateBlock(void)
{
	//int nCntBlock;
	//VERTEX_2D* pVtx;

	////���_�o�b�t�@�����b�N���Ē��_���ւ̃|�C���^���擾
	//g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	//for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	//{
	//	//���_���W�̐ݒ�
	//	pVtx[0].pos.x = 0.0f;
	//	pVtx[0].pos.y = 680.0f;
	//	pVtx[0].pos.z = 0.0f;

	//	pVtx[1].pos.x = BLOCK_HEIGHT;
	//	pVtx[1].pos.y = 680.0f;
	//	pVtx[1].pos.z = 0.0f;

	//	pVtx[2].pos.x = 0.0f;
	//	pVtx[2].pos.y = 720.0f;
	//	pVtx[2].pos.z = 0.0f;

	//	pVtx[3].pos.x = BLOCK_HEIGHT;
	//	pVtx[3].pos.y = 720.0f;
	//	pVtx[3].pos.z = 0.0f;

	//}
	//pVtx += 4;
	//g_pVtxBuffBlock->Unlock();
}

//------------------------------------------
//�e�̕`�揈��
//------------------------------------------
void DrawBlock(void) 
{
	int nCntBlock;

	LPDIRECT3DDEVICE9 pDevice;   //�f�o�C�X�ւ̃|�C���^
	//�f�o�C�X�̎擾
	pDevice = GetDevice();
	
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBlock, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{
			//�e���g�p����Ă���
			//�|���S���̕`��
			pDevice->SetTexture(0, g_pTextureBlock);
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntBlock, 2);
		}
	}
}

//------------------------------------------
//�u���b�N�̐ݒ菈��
//------------------------------------------
void SetBlock(D3DXVECTOR3 pos,float fWidth,float fHeight)
{

	int nCntBlock;
	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���Ē��_���ւ̃|�C���^���擾
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == false)
		{
			g_aBlock[nCntBlock].pos = pos;
			g_aBlock[nCntBlock].bUse = true;
			g_aBlock[nCntBlock].fWidth = fWidth;
			g_aBlock[nCntBlock].fHeight = fHeight;

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x - (fWidth / 2), g_aBlock[nCntBlock].pos.y - (fHeight / 2), g_aBlock[nCntBlock].pos.z);
			pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (fWidth / 2), g_aBlock[nCntBlock].pos.y - (fHeight / 2), g_aBlock[nCntBlock].pos.z);
			pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x - (fWidth / 2), g_aBlock[nCntBlock].pos.y + (fHeight / 2), g_aBlock[nCntBlock].pos.z);
			pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (fWidth / 2), g_aBlock[nCntBlock].pos.y + (fHeight / 2), g_aBlock[nCntBlock].pos.z);
																										  

			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(16.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(16.0f, 1.0f);

			break;
		}
		pVtx += 4;
	}
	g_pVtxBuffBlock->Unlock();
}

//�u���b�N�̓����蔻��
bool CollsionBlock(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3* pMove, float fWidth, float fHeight)
{
	bool bLanding = false;       //���n���Ă��邩�ǂ���

	for (int nCntblo = 0; nCntblo < MAX_BLOCK; nCntblo++)
	{
		if (g_aBlock[nCntblo].bUse == true)
		{
			if (pPos->x + MAX_X / 2 > g_aBlock[nCntblo].pos.x - g_aBlock[nCntblo].fWidth / 2 && pPos->x - MAX_X / 2 < g_aBlock[nCntblo].pos.x + g_aBlock[nCntblo].fWidth / 2)
			{
				//�ォ�牺�̔���
				if (pPosOld->y <= g_aBlock[nCntblo].pos.y - g_aBlock[nCntblo].fHeight / 2 && pPos->y > g_aBlock[nCntblo].pos.y - g_aBlock[nCntblo].fHeight / 2)
				{
					bLanding = true;
					pPos->y = g_aBlock[nCntblo].pos.y - (g_aBlock[nCntblo].fHeight / 2);
					pMove->y = 0.0f;
				}
				//�������̔���
				/*else if (pPosOld->y - MAX_Y >=g_aBlock[nCntblo].pos.y + g_aBlock[nCntblo].fHeight / 2 && pPos->y - MAX_Y < g_aBlock[nCntblo].pos.y + g_aBlock[nCntblo].fHeight / 2)
				{
					pPos->y =g_aBlock[nCntblo].pos.y - g_aBlock[nCntblo].fHeight / 2;
					pMove->y =0.0f;
				}
				 */

				if (pPosOld->y > g_aBlock[nCntblo].pos.y - g_aBlock[nCntblo].fHeight / 2 && pPosOld->y - MAX_Y < g_aBlock[nCntblo].pos.y + g_aBlock[nCntblo].fHeight / 2)
				{
					//������E�ɂ߂荞��
					if (pPosOld->x + MAX_X / 2 <= g_aBlock[nCntblo].pos.x - g_aBlock[nCntblo].fWidth / 2 && pPos->x + MAX_X / 2 > g_aBlock[nCntblo].pos.x - g_aBlock[nCntblo].fWidth / 2)
					{
						pPos->x = g_aBlock[nCntblo].pos.x - g_aBlock[nCntblo].fWidth / 2 - MAX_X / 2;
						pMove->x = 0.0f;
					}
					else if (pPosOld->x - MAX_X / 2 >= g_aBlock[nCntblo].pos.x + g_aBlock[nCntblo].fWidth / 2 && pPos->x - MAX_X / 2 < g_aBlock[nCntblo].pos.x + g_aBlock[nCntblo].fWidth / 2)
					{
						pPos->x = g_aBlock[nCntblo].pos.x + g_aBlock[nCntblo].fWidth / 2 - MAX_X / 2;
						pMove->x = 0.0f;
					}
				}
			}
		}
	}
	return bLanding;
}