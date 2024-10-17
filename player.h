//------------------------------------------
//
//     �@�v���C���[����
//       Author:Sudou Akito
//
//------------------------------------------
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include"main.h"

//�}�N����`
#define MAX_PLAYPATTERN (4)
#define MAX_SIZE (100)        //���ƍ���
#define MAX_X (40)
#define MAX_Y (100)
#define FJUMP (-25.0f)
#define FDA (1.0f)

//�v���C���[�̏��
typedef enum
{
	PLAYERSTATE_APPEAR=0,     //�o���n�_(�_��)
	PLAYERSTATE_NORMAL,       //�ʏ���
	PLAYERSTATE_DAMAGE,       //�_���[�W���
	PLAYERSTATE_DEATH,        //���S���
	PLAYERSTATE_MAX
}PLAYERSTATE1;

//�v���C���[�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;     //�ʒu
	D3DXVECTOR3 posOld;  //�O��̈ʒu
	D3DXVECTOR3 move;    //�ړ���
	D3DXVECTOR3 rot;     //����
	//PLAYERSTATE state;   //���
	PLAYERSTATE1 state1; //�v���C���[�̏��
	//int nCounterState;   //��ԊǗ��J�E���^�[
	int nCounterState1;  //��ԊǗ��J�E���^�[
	float fLength;       //�Ίp���̒���
	float fAngle;        //�Ίp���̊p�x
	bool bRightMove;     //����(true:�E����,false:������)
	int nLife;           //�̗�
	bool bDisp;          //�\�����邩���Ȃ���
	bool bJump;
}Player;

//�v���g�^�C�v�錾
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
Player* GetPlayer(void);
void HitPlayer(int nDmg);
void GetKeyPlayer(void);



#endif