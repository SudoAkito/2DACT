//------------------------------------------
//
//         弾の出力処理
//       Author:Sudou Akito
//
//------------------------------------------
#ifndef _BLOCK_H_
#define _BLOCK_H_

#include"main.h"

//プロトタイプ宣言
void InitBlock(void);
void UninitBlock(void);
void UpdateBlock(void);
void DrawBlock(void);
void SetBlock(D3DXVECTOR3 pos, float fWidth, float fHeight);   //posは発射位置,rotは向いた方向に出させる
bool CollsionBlock(D3DXVECTOR3* pPos, //現在位置
	D3DXVECTOR3* pPosOld,             //前回の位置
	D3DXVECTOR3* pMOVE,               //移動量
	float fWidth,                     //幅
	float fHeight);                   //高さ

//マクロ
#define MAX_SPEED (5)              //スピード
#define MAX_BLOCK (128)           //ブロックの最大数
#define BLOCK_WIDTH (80.0f)
#define BLOCK_HEIGHT (1280.0f)

#endif

