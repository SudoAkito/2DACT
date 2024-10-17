//------------------------------------------
//
//         �G����
//       Author:Sudou Akito
//
//------------------------------------------

#ifndef _ENEMY_H_
#define _ENEMY_H_

#include"main.h"

//�}�N��
#define MAX_ENEMY (256)
#define MAX_WIDTH (50)
#define MAX_HEIGHT (75)

//�G�̏��
typedef enum
{
	ENEMYSTATE_NORMAL=0,  //�ʏ���
	ENEMYSTATE_DAMAGE,    //�_���[�W���
	ENEMYSTATE_MAX
}ENEMYSTATE;

//�G�\����
typedef struct
{
	D3DXVECTOR3 pos;  //�ʒu
	D3DXVECTOR3 move; //�ړ���
	D3DXVECTOR3 rot;  //�p�x
	ENEMYSTATE state; //���
	int nCounterState;//��ԊǗ��J�E���^�[
	int nLife;        //�̗�
	int nType;        //���
	bool bUse;        //�g�p�̗L��
	float fLength;
	float fAngle;
}Enemy;

typedef enum
{
	ENEMYTYPE_1,
	ENEMYTYPE_2,
	ENEMYTYPE_MAX,

}ENEMYTYPE;

static const char* ENEMYTEX[ENEMYTYPE_MAX] =
{
	"data\\TEXTURE\\enemy1.png",
    "data\\TEXTURE\\enemy2.png",





};

//�v���g�^�C�v�錾
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void SetEnemy(D3DXVECTOR3 pos,int nType);   //pos�͔��ˈʒu,nType�͎��
Enemy* GetEnemy(void);
void HitEnemy(int nCntEn, int nDmg);
int GetNumEnemy();

#endif
