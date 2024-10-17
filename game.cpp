//------------------------------------------
//
//        ���C���Q�[������
//       Author:Sudou Akito
//
//------------------------------------------

#include"game.h"
#include "player.h"
#include"background.h"
#include"bullet.h"
#include"explosion.h"
#include"effect.h"
#include"enemy.h"
#include"fade.h"
#include "block.h"
#include"score.h"
#include"pause.h"
#include "ranking.h"
#include "partycle.h"
#include "enemyset.h"
#include"Timer.h"

//�O���[�o���ϐ�
GAMESTATE g_gameState = GAMESTATE_NONE;   //�Q�[���̏��
int g_nCounterGameState = 0;              //��ԊǗ��J�E���^�[
bool g_bPause = false;                    //�|�[�Y�����ǂ���
int g_nCounter1;
int g_nCounter2;

//------------------------------------------
//�Q�[����ʂ̏���������
//------------------------------------------
void InitGame(void)
{
	InitBackground();

	InitPlayer();

	InitBlock();

	SetBlock(D3DXVECTOR3(BLOCK_HEIGHT / 2, 680.0f, 0.0f), 1350.0f, 60.0f);
	SetBlock(D3DXVECTOR3(900.0f, 500.0f, 0.0f), 900.0f, 50.0f);
	SetBlock(D3DXVECTOR3(950.0f, 320.0f, 0.0f), 670.0f, 50.0f);
	SetBlock(D3DXVECTOR3(1050.0f, 140.0f, 0.0f), 500.0f, 50.0f);

	//�X�R�A�̏�����
	InitScore();

	//�e
	InitBullet();

	// ����
	InitExplosion();

	//�G�t�F�N�g
	InitEffect();

	//�p�[�e�B�N��
	InitPartycle();

	//�G
	InitEnemy();
	Initenemyset();
	loadenemy();

	//�|�[�Y
	InitPause();

	//�^�C�}�[
	InitTimer();

	g_gameState = GAMESTATE_NORMAL;    //�ʏ��Ԃɐݒ�

	g_nCounterGameState = 0;

	g_bPause = false;                 //�|�[�Y����
}

//------------------------------------------
//�Q�[����ʂ̏I������
//------------------------------------------
void UninitGame(void)
{
	//�^�C�}�[
	UninitTimer();

	//�v���C���[
	UninitPlayer();

	//�u���b�N
	UninitBlock();
	
	//�w�i
	UninitBackground();

	//�|�[�Y
	UninitPause();

	//�X�R�A�̏I��
	UninitScore();

	//�e
	UninitBullet();

	//����
	UninitExplosion();

	//�G�t�F�N�g
	UninitEffect();

	////�G
	UninitEnemy();

}

//------------------------------------------
//�Q�[����ʂ̍X�V����
//------------------------------------------
void UpdateGame(void)
{
	int nEnemy = GetEnemySet();

	int nTimer = GetTimer();

	if (nEnemy <= 0)
	{
		loadenemy();
	}

	if (KeyboardTrigger(DIK_P) == true || GetJoypadPress(JOYKEY_START) == true)
	{  //P�i�|�[�Y�L�[�j�������ꂽ
		g_bPause = g_bPause ? false : true;
	}
	
	if (g_bPause == true)
	{//�|�[�Y��
		//�|�[�Y�X�V����
		UpdatePause();
	}
	else
	{
		//�w�i
		UpdateBackground();

		//�^�C�}�[
		UpdateTimer();

		//�u���b�N
		UpdateBlock();

		//�v���C���[
		UpdatePlayer();

		//�X�R�A�̍X�V
		UpdateScore();

		//�e
		UpdateBullet();

		//����
		UpdateExplosion();

		//�G�t�F�N�g
		UpdateEffect();

		//�p�[�e�B�N��
		UpdatePartycle();

		////�G
		UpdateEnemy();
	}

	
	Player* pPlayer = GetPlayer();  //�v���C���[�̃|�C���^

	if (pPlayer->bDisp==false||nEnemy<=0)   //������^�C���I�[�o�[�̏����ǉ�
	{
		//���[�h�ݒ�
		g_gameState=GAMESTATE_END;
	}

	switch (g_gameState)
	{
	case GAMESTATE_NORMAL:    //�ʏ���
		break;

	case GAMESTATE_END:       //�I�����
  		g_nCounterGameState++;
		if (g_nCounterGameState >= 60)
		{
			g_gameState = GAMESTATE_NONE;  //�������Ă��Ȃ���Ԃɐݒ�

			//��ʂ̐ݒ�
			SetFade(MODE_RESULT);

			//�����L���O�̐ݒ�
			/*SetRanking(GetScore());*/
		}
		break;
	}
}

//------------------------------------------
// �Q�[���̕`�揈��
//------------------------------------------
void DrawGame(void)
{
	//�w�i
	DrawBackground();

	//�u���b�N
	DrawBlock();

	//�^�C�}�[
	DrawTimer();

	//�v���C���[
	DrawPlayer();

	//�G
	DrawEnemy();

	//�e
	DrawBullet();

	//����
	DrawExplosion();

	//�X�R�A
	DrawScore();

	//�G�t�F�N�g
	DrawEffect();

	if (g_bPause == true)
	{//�|�[�Y��
		//�|�[�Y�`�揈��
		DrawPause();
	}
}

//------------------------------------------
//�Q�[���̏�Ԃ̐ݒ�
//------------------------------------------
void SetGameState(GAMESTATE state)
{
	g_gameState = state;

	/*g_nCounterGameState = 0;*/
}

//------------------------------------------
//�Q�[���̏�Ԏ擾
//------------------------------------------
GAMESTATE GetGameState(void)
{
	return g_gameState;
}

//------------------------------------------
//�|�[�Y�̗L�������ݒ�
//------------------------------------------
void SetEnablePause(bool bPause)
{
	g_bPause = bPause;
}

