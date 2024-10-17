//------------------------------------------
//
//         �e�̏o�͏���
//       Author:Sudou Akito
//
//------------------------------------------
#ifndef _BULLET_H_
#define _BULLET_H_

#include"main.h"

//�e�̎��
typedef enum
{
	BULLETTYPE_PLAYER=0,  //�v���C���[�̒e
	BULLETTYPE_ENEMY,     //�G�̒e
	BULLETTYPE_MAX
}BULLETTYPE;

//�����蔻��̎��
typedef enum
{
	JUDGMENT_HEAD=0, //�w�b�h�V���b�g
	JUDGMENT_BODY,   //����
	JUDGMENT_MAX 
}JUDGMENT;

//�v���g�^�C�v�錾
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, float fLength, int nLife, BULLETTYPE type);   //pos�͔��ˈʒu,rot�͌����������ɏo������

//�}�N��
#define MAX_SPEED (5)              //�X�s�[�h

#endif

