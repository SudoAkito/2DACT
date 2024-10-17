//------------------------------------------
//
//         ランキング処理
//       Author:Sudou Akito
//
//------------------------------------------
#ifndef _RANKING_H_
#define _RANKING_H_

#include<stdio.h>
#include"main.h"

//マクロ定義
#define MAX_RANK (5)    //表示順位数



//プロトタイプ宣言
void InitRanking(void);
void UninitRanking(void);
void UpdateRanking(void);
void DrawRanking(void);
void DrawRankScore(void);
void ResetRanking(void);
void SetRanking(int nScore);
void SetpVtx(void);
void SetpVtx1(int nCnt,int nCntd,int nNumber);
void SetpVtx2(void);
void DrawBG(void);


#endif

