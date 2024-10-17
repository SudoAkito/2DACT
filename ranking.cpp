//------------------------------------------
//
//         �����L���O����
//       Author:Sudou Akito
//
//------------------------------------------

#include"ranking.h"
#include "fade.h"
#include "input.h"

//�����L���O�X�R�A�\����
typedef struct
{
	D3DXVECTOR3 pos;     //�ʒu
	int nScore;          //�X�R�A
}RankScore;

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureRank = NULL;      //�e�N�X�`���̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureRankScore = NULL; //�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRank = NULL; //���_�o�b�t�@�|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRankScore = NULL; //���_�o�b�t�@�|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRankBG = NULL; //���_�o�b�t�@�|�C���^
LPDIRECT3DTEXTURE9 g_pTextureRankBG = NULL; //�e�N�X�`���̃|�C���^

RankScore g_aRankScore[MAX_RANK];              //�����L���O�X�R�A���
int g_nRankUpdate = -1;                        //�X�V�����NNo.
int g_nTimerRanking;                           //�����L���O�\���^�C�}�[
int g_Score1[5] = {};

//------------------------------------------
//�����L���O�̏���������
//------------------------------------------
void InitRanking(void)
{
	LPDIRECT3DDEVICE9 pDevice;   //�f�o�C�X�ւ̃|�C���^
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\rank.png",
		&g_pTextureRank);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Number1.png",
		&g_pTextureRankScore);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\haikei.png",
		&g_pTextureRankBG);


	//g_nRankUpdate = -1;
	g_nTimerRanking = 0;
	for (int i = 0; i < MAX_RANK; i++)
	{
		g_Score1[i] = 0;
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRank,
		NULL);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_RANK*8,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRankScore,
		NULL);


	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRankBG,
		NULL);


	SetpVtx2();

	SetpVtx();    //���ʗp���_���W

	SetpVtx1(0,0,0);   //�X�R�A�p���_���W

	ResetRanking();

}

//------------------------------------------
//�����L���O�̏I������
//------------------------------------------
void UninitRanking(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureRank != NULL)
	{
		g_pTextureRank->Release();
		g_pTextureRank = NULL;
	}

	if (g_pTextureRankScore != NULL)
	{
		g_pTextureRankScore->Release();
		g_pTextureRankScore = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffRank != NULL)
	{
		g_pVtxBuffRank->Release();
		g_pVtxBuffRank = NULL;
	}

	if (g_pVtxBuffRankScore != NULL)
	{
		g_pVtxBuffRankScore->Release();
		g_pVtxBuffRankScore = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffRankBG != NULL)
	{				  
		g_pTextureRankBG->Release();
		g_pTextureRankBG = NULL;
	}

	if (g_pVtxBuffRankBG != NULL)
	{				  
		g_pVtxBuffRankBG->Release();
		g_pVtxBuffRankBG = NULL;
	}
}

//------------------------------------------
//�����L���O�̍X�V����
//------------------------------------------
void UpdateRanking(void)
{
	static int nCounter{};

	if (g_nRankUpdate != -1)
	{
		nCounter++;   //���Z

		//�Y���X�R�A��_��
		if (nCounter == 10)
		{
			VERTEX_2D* pVtx{};       //���_���̃|�C���^

			//���_�o�b�t�@�����b�N���Ē��_���ւ̃|�C���^���擾
			g_pVtxBuffRankScore->Lock(0, 0, (void**)&pVtx, 0);

			pVtx += (32 * g_nRankUpdate);

			for (int nCnt = 0; nCnt < 8; nCnt++)
			{
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 120);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 120);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 120);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 120);
				pVtx += 4;
			}

			g_pVtxBuffRankScore->Unlock();
		}
		else if (nCounter == 20)
		{
			VERTEX_2D* pVtx{};       //���_���̃|�C���^

			//���_�o�b�t�@�����b�N���Ē��_���ւ̃|�C���^���擾
			g_pVtxBuffRankScore->Lock(0, 0, (void**)&pVtx, 0);

			pVtx += (32 * g_nRankUpdate);

			for (int nCnt = 0; nCnt < 8; nCnt++)
			{
				pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 120);
				pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 120);
				pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 120);
				pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 120);
				pVtx += 4;
			}

			g_pVtxBuffRankScore->Unlock();

			nCounter = 0;
		}
		
	}
	
	g_nTimerRanking++;
	if(g_nTimerRanking>=600||GetJoypadPress(JOYKEY_BACK) == true|| KeyboardTrigger(DIK_RETURN) == true)
	{
		//�^�C�g����ʂɑJ��
		SetFade(MODE_TITLE);
	}
}

//------------------------------------------
//�����L���O�̕`�揈��1
//------------------------------------------
void DrawRanking(void)
{

	LPDIRECT3DDEVICE9 pDevice;   //�f�o�C�X�ւ̃|�C���^
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffRank, 0, sizeof(VERTEX_2D));

	pDevice->SetTexture(0, g_pTextureRank);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0, 2);


	DrawRankScore();
}

//------------------------------------------
//�����L���O�̕`�揈��2
//------------------------------------------
void DrawRankScore(void)
{

	LPDIRECT3DDEVICE9 pDevice;   //�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt1 = 0; nCnt1 < MAX_RANK; nCnt1++)
	{
		for (int nCnt = 0; nCnt < 8; nCnt++)
		{
			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffRankScore, 0, sizeof(VERTEX_2D));

			pDevice->SetTexture(0, g_pTextureRankScore);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (32 * nCnt1) + (4 * nCnt), 2);
		}
	}
}

// -----------------------------------------
//�����L���O�̏��̎擾
//------------------------------------------
void ResetRanking(void)
{
	FILE* pFile;

	pFile = fopen("data\\txt\\ranking.txt", "r");

	if (pFile != NULL)
	{
		for (int nCnt = 0; nCnt < MAX_RANK; nCnt++)
		{
			fscanf(pFile, "%d", &g_Score1[nCnt]);
		}
	}
	else
	{
		MessageBox(NULL,"�J���o���܂���ł����B","�G���[",MB_OK);

		return;
	}
	fclose(pFile);


	for (int nCnt = 0; nCnt < MAX_RANK; nCnt++)
	{
		int adigits[8];
		int nData = 10000000, aData = 1000000;

		for (int nCntdigit = 0; nCntdigit < 8; nCntdigit++)
		{
			if (nCntdigit == 0)
			{
				adigits[0] = g_Score1[nCnt] / nData;
			}
			else
			{
				adigits[nCntdigit] = g_Score1[nCnt] % nData / aData;
				nData = nData / 10;
				aData = aData / 10;
			}
			SetpVtx1(nCnt, nCntdigit, adigits[nCntdigit]);
		}
	}

}

// -----------------------------------------
//�����L���O�̐ݒ�
//------------------------------------------
void SetRanking(int nScore)
{
	FILE* pFile;

	pFile = fopen("data\\txt\\ranking.txt", "r");

	if (pFile != NULL)
	{
		for (int nCnt = 0; nCnt < MAX_RANK; nCnt++)
		{
			fscanf(pFile, "%d", &g_Score1[nCnt]);
		}
	}
	else
	{
		MessageBox(NULL, "�J���o���܂���ł����B", "�G���[", MB_OK);

		return;
	}

	fclose(pFile);

	int nCntRank;
	int Temp{};

	for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{
		for (int nCnt2 = nCntRank + 1; nCnt2 < MAX_RANK; nCnt2++)
		{
			if (g_Score1[nCntRank] <= g_Score1[nCnt2])
			{
				Temp = g_Score1[nCntRank]; //�㏑���O�ۑ�
				g_Score1[nCntRank] = g_Score1[nCnt2];//�㏑��
				g_Score1[nCnt2] = Temp;//�ۑ������l�ŏ㏑��
			}
		}
	}

	bool bChange = false;	// ���U���g��ύX�������ǂ���
	int nResult = -1;		// �����N�C���������� (-1 �̏ꍇ�̓����N�O)
	for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{
		if (g_Score1[nCntRank] < nScore)
		{
			if (bChange == false)
			{ // �܂��ύX����Ă��Ȃ� (�܂�ŏ��̕ύX)
				nResult = nCntRank;
				bChange = true;	// ���łɕύX�ς�
			}
			Temp = g_Score1[nCntRank]; //�㏑���O�ۑ�
			g_Score1[nCntRank] = nScore;//�㏑��
			nScore = Temp;//�ۑ������l�ŏ㏑��
		}
	}
	g_nRankUpdate = nResult;	// �����N��o�^

	pFile = fopen("data\\txt\\ranking.txt", "w");

	if (pFile != NULL)
	{
		for (int nCnt = 0; nCnt < MAX_RANK; nCnt++)
		{
			fprintf(pFile, "%d\n", g_Score1[nCnt]);
		}
	}
	else
	{
		MessageBox(NULL, "�J���o���܂���ł����B", "�G���[", MB_OK);

		return;
	}
	fclose(pFile);

	//�w��X�R�A�������N�C��������g_nRankUpdate���X�V���ăe�N�X�`�����W�̐ݒ�

}
// -----------------------------------------
//�����L���O�̃J���[�ݒ�
//------------------------------------------
//void SetRankcolor(void)
//{
//
//	VERTEX_2D* pVtx;       //���_���̃|�C���^
//
//	//���_�o�b�t�@�����b�N���Ē��_���ւ̃|�C���^���擾
//	g_pVtxBuffRank->Lock(0, 0, (void**)&pVtx, 0);
//
//	//���_�J���[�̐ݒ�
//	pVtx[0].col = D3DCOLOR_RGBA(255,0,0,255);
//	pVtx[1].col = D3DCOLOR_RGBA(255,0,0,255);
//	pVtx[2].col = D3DCOLOR_RGBA(255,0,0,255);
//	pVtx[3].col = D3DCOLOR_RGBA(255,0,0,255);
//
//
//	//���_�o�b�t�@���A�����b�N����
//	g_pVtxBuffRank->Unlock();
//}


// -----------------------------------------
//���ʗp���_���W�ݒ�
//------------------------------------------
void SetpVtx (void)
{

	VERTEX_2D* pVtx;       //���_���̃|�C���^

	//���_�o�b�t�@�����b�N���Ē��_���ւ̃|�C���^���擾
	g_pVtxBuffRank->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�ݒ�
	pVtx[0].pos = D3DXVECTOR3(220.0f,90.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(369.0f,90.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(220.0f,620.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(369.0f,620.0f, 0.0f);

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
	g_pVtxBuffRank->Unlock();
}

// -----------------------------------------
//�@�X�R�A�����L���O�p���_���W�ݒ�
//------------------------------------------
void SetpVtx1(int nCntRank,int nCntd, int nNumber)
{
	VERTEX_2D* pVtx;       //���_���̃|�C���^

	//���_�o�b�t�@�����b�N���Ē��_���ւ̃|�C���^���擾
	g_pVtxBuffRankScore->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += ((nCntRank*32)+(nCntd*4));

	float min_x = 450.0f+50.0f*nCntd;
	float min_y = 100.0f+100.0f*nCntRank;
	float max_x = min_x+50.0f;
	float max_y = min_y+100.0f;

	
	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(min_x,min_y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(max_x, min_y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(min_x, max_y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(max_x, max_y, 0.0f);

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

	float fu1 = nNumber * 0.1f;
	float fu2 = fu1 + 0.1f;

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(fu1, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(fu2, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(fu1, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(fu2, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffRankScore->Unlock();
}

void DrawBG(void)
{

	LPDIRECT3DDEVICE9 pDevice;   //�f�o�C�X�ւ̃|�C���^
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffRankBG, 0, sizeof(VERTEX_2D));

	pDevice->SetTexture(0, g_pTextureRankBG);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

// -----------------------------------------
//�@�����L���O�p�w�i�ݒ�
//------------------------------------------
void SetpVtx2(void)
{

	VERTEX_2D* pVtx;       //���_���̃|�C���^


		//���_�o�b�t�@�����b�N���Ē��_���ւ̃|�C���^���擾
	g_pVtxBuffRankBG->Lock(0, 0, (void**)&pVtx, 0);

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
	pVtx[0].tex = D3DXVECTOR2(0.0f,0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f,0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f,1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f,1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffRankBG->Unlock();
}