//------------------------------------------
//
//         パーティクル処理
//       Author:Sudou Akito
//
//------------------------------------------
#ifndef _PARTYCLE_H_
#define _PARTYCLE_H_

#include"main.h"

//プロトタイプ宣言
void InitPartycle(void);
void UninitPartycle(void);
void UpdatePartycle(void);
void DrawPartycle(void);
void SetPartycle(D3DXVECTOR3 pos);

#endif
