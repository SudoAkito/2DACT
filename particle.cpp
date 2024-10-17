//------------------------------------------
//
//         �p�[�e�B�N������
//       Author:Sudou Akito
//
//------------------------------------------

#include"partycle.h"
#include "effect.h"

//�}�N��
#define MAX_PARTYCLE (128)  //�p�[�e�B�N���ő吔

//�p�[�e�B�N���\����
typedef struct
{
	D3DXVECTOR3 pos;   //�����ʒu
	int nLife;         //����
	bool bUse;         //�g�p�̗L��
}Partycle;

//�O���[�o���ϐ�
Partycle g_apartycle[MAX_PARTYCLE];  //�p�[�e�B�N���̏��

//------------------------------------------
//�p�[�e�B�N���̏���������
//------------------------------------------
void InitPartycle(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//������
	for (int nCntPar = 0; nCntPar < MAX_PARTYCLE; nCntPar++)
	{
		D3DXVECTOR3 pos = D3DXVECTOR3(500.0f, 200.0f, 0.0f);
		int nLife = 10;
		bool bUse = false;
	}
	
}

//------------------------------------------
//�p�[�e�B�N���I������
//------------------------------------------
void UninitPartycle(void)
{
	//�������ƂȂ�
}


//------------------------------------------
//�p�[�e�B�N���X�V����
//------------------------------------------
void UpdatePartycle(void)
{
	int nCntpar;
	int nCntApper;
	D3DXVECTOR3 pos;   //�ʒu
	D3DXVECTOR3 move;  //�ړ���
	D3DXCOLOR col;     //�F
	float fPullRadius; //���_���W�ݒ� 
	float fPullMove;   //�ړ��ʌ���
	float falfa;       //���l�̐ݒ�
	float fData;       //���l�̌���
	float fRadius;     //���_���W�ݒ� 
	int nLife;         //�̗�


	for (nCntpar = 0; nCntpar < MAX_PARTYCLE; nCntpar++)
	{

		if (g_apartycle[nCntpar].bUse == true)
		{
			//�p�[�e�B�N������
			for (nCntApper = 0; nCntApper < 20; nCntApper++)
			{
				float fAngle = (float)(rand() % 629 - 314) / 100.0f;
				float fspeed = (float)(rand() % 10) + 1;

				//�ʒu�̐ݒ�
				pos = g_apartycle[nCntpar].pos;

				//�ړ��ʂ̐ݒ�
				move.x = sinf(fAngle) * fspeed;
				move.y = cosf(fAngle) * fspeed;

				//�ړ��ʌ���
				fPullMove = 0.01f;

				//�F�̐ݒ�
				col = D3DXCOLOR(0.6f, 0.3f, 0.6f, 0.5f);

				//���a�̐ݒ�
				fRadius = 20.0f;

				//���a�̌����W��
				fPullRadius = 0.01f;

				//���l�̏����ݒ�
				falfa = 0.5f;

				//���l�̌����l
				fData = 0.02f;

				//�̗�
				nLife = 60;

				SetEffect(pos
					,D3DXVECTOR3(move.x,move.y,move.z)
					,col
					,fRadius
					,falfa
					,fData
					,fPullRadius
					,fPullMove
					,nLife);
			}
			g_apartycle[nCntpar].bUse = false;
		}
	}
}

//------------------------------------------
//�p�[�e�B�N���`�揈��
//------------------------------------------
void DrawPartycle(void)
{
	//�������ƂȂ�
}

//------------------------------------------
//�p�[�e�B�N���ݒ菈��
//------------------------------------------
void SetPartycle(D3DXVECTOR3 pos)
{
	int nCntpar;

	for (nCntpar = 0; nCntpar < MAX_PARTYCLE; nCntpar++) 
	{
		if (g_apartycle[nCntpar].bUse == false)
		{
			g_apartycle[nCntpar].pos = pos;
			g_apartycle[nCntpar].nLife = 60;
			g_apartycle[nCntpar].bUse = true;  //�g�p���Ă��Ԃɂ���

			break;
		}
	}
}
