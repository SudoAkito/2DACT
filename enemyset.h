//------------------------------------------
//
//          敵処理
//       Author:Sudou Akito
//
//------------------------------------------
#ifndef _ENEMYSET_H_
#define _ENEMYSET_H_

#include "main.h"
#include"enemy.h"

//プロトタイプ宣言
void Initenemyset(void);
void loadenemy(void);
int GetEnemySet(void);
bool GetFinSet();

//マクロ
#define Enemypas ("Enemy\\enemy.txt")
#define MAX_ENESET (1)

#endif