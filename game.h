//------------------------------------------
//
//        メインゲーム処理
//       Author:Sudou Akito
//
//------------------------------------------
#ifndef _GAME_H_
#define _GAME_H_

#include "input.h"

//マクロ
#define HARF (200)

//ゲームの状態
typedef enum
{
	GAMESTATE_NONE=0,  //何もしてない状態
	GAMESTATE_NORMAL,  //通常状態(ゲーム進行中)
	GAMESTATE_END,     //終了状態(敵全滅、プレイヤー滅、タイムオーバーなど)
	GAMESTATE_MAX     
}GAMESTATE;

//プロトタイプ宣言
void InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);
void SetGameState(GAMESTATE state);
GAMESTATE GetGameState(void);
void SetEnablePause(bool bPause);


#endif
