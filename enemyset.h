//------------------------------------------
//
//          �G����
//       Author:Sudou Akito
//
//------------------------------------------
#ifndef _ENEMYSET_H_
#define _ENEMYSET_H_

#include "main.h"
#include"enemy.h"

//�v���g�^�C�v�錾
void Initenemyset(void);
void loadenemy(void);
int GetEnemySet(void);
bool GetFinSet();

//�}�N��
#define Enemypas ("Enemy\\enemy.txt")
#define MAX_ENESET (1)

#endif