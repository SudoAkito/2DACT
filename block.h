//------------------------------------------
//
//         �e�̏o�͏���
//       Author:Sudou Akito
//
//------------------------------------------
#ifndef _BLOCK_H_
#define _BLOCK_H_

#include"main.h"

//�v���g�^�C�v�錾
void InitBlock(void);
void UninitBlock(void);
void UpdateBlock(void);
void DrawBlock(void);
void SetBlock(D3DXVECTOR3 pos, float fWidth, float fHeight);   //pos�͔��ˈʒu,rot�͌����������ɏo������
bool CollsionBlock(D3DXVECTOR3* pPos, //���݈ʒu
	D3DXVECTOR3* pPosOld,             //�O��̈ʒu
	D3DXVECTOR3* pMOVE,               //�ړ���
	float fWidth,                     //��
	float fHeight);                   //����

//�}�N��
#define MAX_SPEED (5)              //�X�s�[�h
#define MAX_BLOCK (128)           //�u���b�N�̍ő吔
#define BLOCK_WIDTH (80.0f)
#define BLOCK_HEIGHT (1280.0f)

#endif

