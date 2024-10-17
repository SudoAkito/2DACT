//------------------------------------------
//
//        メインゲーム処理
//       Author:Sudou Akito
//
//------------------------------------------

#include"game.h"
#include "player.h"
#include"background.h"
#include"bullet.h"
#include"explosion.h"
#include"effect.h"
#include"enemy.h"
#include"fade.h"
#include "block.h"
#include"score.h"
#include"pause.h"
#include "ranking.h"
#include "partycle.h"
#include "enemyset.h"
#include"Timer.h"

//グローバル変数
GAMESTATE g_gameState = GAMESTATE_NONE;   //ゲームの状態
int g_nCounterGameState = 0;              //状態管理カウンター
bool g_bPause = false;                    //ポーズ中かどうか
int g_nCounter1;
int g_nCounter2;

//------------------------------------------
//ゲーム画面の初期化処理
//------------------------------------------
void InitGame(void)
{
	InitBackground();

	InitPlayer();

	InitBlock();

	SetBlock(D3DXVECTOR3(BLOCK_HEIGHT / 2, 680.0f, 0.0f), 1350.0f, 60.0f);
	SetBlock(D3DXVECTOR3(900.0f, 500.0f, 0.0f), 900.0f, 50.0f);
	SetBlock(D3DXVECTOR3(950.0f, 320.0f, 0.0f), 670.0f, 50.0f);
	SetBlock(D3DXVECTOR3(1050.0f, 140.0f, 0.0f), 500.0f, 50.0f);

	//スコアの初期化
	InitScore();

	//弾
	InitBullet();

	// 爆発
	InitExplosion();

	//エフェクト
	InitEffect();

	//パーティクル
	InitPartycle();

	//敵
	InitEnemy();
	Initenemyset();
	loadenemy();

	//ポーズ
	InitPause();

	//タイマー
	InitTimer();

	g_gameState = GAMESTATE_NORMAL;    //通常状態に設定

	g_nCounterGameState = 0;

	g_bPause = false;                 //ポーズ解除
}

//------------------------------------------
//ゲーム画面の終了処理
//------------------------------------------
void UninitGame(void)
{
	//タイマー
	UninitTimer();

	//プレイヤー
	UninitPlayer();

	//ブロック
	UninitBlock();
	
	//背景
	UninitBackground();

	//ポーズ
	UninitPause();

	//スコアの終了
	UninitScore();

	//弾
	UninitBullet();

	//爆発
	UninitExplosion();

	//エフェクト
	UninitEffect();

	////敵
	UninitEnemy();

}

//------------------------------------------
//ゲーム画面の更新処理
//------------------------------------------
void UpdateGame(void)
{
	int nEnemy = GetEnemySet();

	int nTimer = GetTimer();

	if (nEnemy <= 0)
	{
		loadenemy();
	}

	if (KeyboardTrigger(DIK_P) == true || GetJoypadPress(JOYKEY_START) == true)
	{  //P（ポーズキー）が押された
		g_bPause = g_bPause ? false : true;
	}
	
	if (g_bPause == true)
	{//ポーズ中
		//ポーズ更新処理
		UpdatePause();
	}
	else
	{
		//背景
		UpdateBackground();

		//タイマー
		UpdateTimer();

		//ブロック
		UpdateBlock();

		//プレイヤー
		UpdatePlayer();

		//スコアの更新
		UpdateScore();

		//弾
		UpdateBullet();

		//爆発
		UpdateExplosion();

		//エフェクト
		UpdateEffect();

		//パーティクル
		UpdatePartycle();

		////敵
		UpdateEnemy();
	}

	
	Player* pPlayer = GetPlayer();  //プレイヤーのポインタ

	if (pPlayer->bDisp==false||nEnemy<=0)   //いずれタイムオーバーの条件追加
	{
		//モード設定
		g_gameState=GAMESTATE_END;
	}

	switch (g_gameState)
	{
	case GAMESTATE_NORMAL:    //通常状態
		break;

	case GAMESTATE_END:       //終了状態
  		g_nCounterGameState++;
		if (g_nCounterGameState >= 60)
		{
			g_gameState = GAMESTATE_NONE;  //何もしていない状態に設定

			//画面の設定
			SetFade(MODE_RESULT);

			//ランキングの設定
			/*SetRanking(GetScore());*/
		}
		break;
	}
}

//------------------------------------------
// ゲームの描画処理
//------------------------------------------
void DrawGame(void)
{
	//背景
	DrawBackground();

	//ブロック
	DrawBlock();

	//タイマー
	DrawTimer();

	//プレイヤー
	DrawPlayer();

	//敵
	DrawEnemy();

	//弾
	DrawBullet();

	//爆発
	DrawExplosion();

	//スコア
	DrawScore();

	//エフェクト
	DrawEffect();

	if (g_bPause == true)
	{//ポーズ中
		//ポーズ描画処理
		DrawPause();
	}
}

//------------------------------------------
//ゲームの状態の設定
//------------------------------------------
void SetGameState(GAMESTATE state)
{
	g_gameState = state;

	/*g_nCounterGameState = 0;*/
}

//------------------------------------------
//ゲームの状態取得
//------------------------------------------
GAMESTATE GetGameState(void)
{
	return g_gameState;
}

//------------------------------------------
//ポーズの有効無効設定
//------------------------------------------
void SetEnablePause(bool bPause)
{
	g_bPause = bPause;
}

