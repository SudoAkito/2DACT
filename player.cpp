//------------------------------------------
//
//       プレイヤー処理
//       Author:Sudou Akito
//
//------------------------------------------

#include"player.h"
#include "input.h"
#include "block.h"
#include"bullet.h"
#include "Life.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer= NULL;

int g_nCounterAnimPlayer;    //アニメーションカウンター
int g_nPatternAnimPlayer;    //アニメーションパターンNO.

Player g_player;

//------------------------------------------
//プレイヤー初期化処理
//------------------------------------------
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;   //デバイスへのポインタ
	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\player.png",
		&g_pTexturePlayer);

	g_player.pos = D3DXVECTOR3(200.0f, 640.0f, 0.0f);  //位置初期化
	g_player.move = D3DXVECTOR3(0.0f,0.0f,0.0f);	      //移動量初期化
	g_player.rot = D3DXVECTOR3(0.0f,0.0f,0.0f);        //向きの初期化
	g_player.nLife = 3;
	g_player.bDisp = true;
	g_player.bJump = false;

	//対角線の長さの算出
	g_player.fLength = sqrtf(MAX_SIZE*MAX_SIZE)+(MAX_SIZE*MAX_SIZE) / 2.0f;

	//対角線の角度を算出
	g_player.fAngle = atan2f(MAX_SIZE, MAX_SIZE);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPlayer,
		NULL);

	VERTEX_2D* pVtx;       //頂点情報のポインタ

	//頂点バッファをロックして頂点情報へのポインタを取得
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos.x = g_player.pos.x - (MAX_X/2.0f);
	pVtx[0].pos.y = g_player.pos.y - MAX_Y;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = g_player.pos.x + (MAX_X/2.0f);
	pVtx[1].pos.y = g_player.pos.y - MAX_Y;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = g_player.pos.x - (MAX_X/2.0f);
	pVtx[2].pos.y = g_player.pos.y;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = g_player.pos.x + (MAX_X/2.0f);
	pVtx[3].pos.y = g_player.pos.y;
	pVtx[3].pos.z = 0.0f;

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.25f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffPlayer->Unlock();
}

//------------------------------------------
//プレイヤーの終了処理
//------------------------------------------
void UninitPlayer(void)
{

	//テクスチャの破棄
	if (g_pTexturePlayer != NULL)
	{
		g_pTexturePlayer->Release();
		g_pTexturePlayer = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffPlayer != NULL)
	{
		g_pVtxBuffPlayer->Release();
		g_pVtxBuffPlayer = NULL;
	}
}

//------------------------------------------
//プレイヤーの更新処理
//------------------------------------------
void UpdatePlayer(void)
{
	SetLife(g_player.nLife);

	GetKeyPlayer();
}

//------------------------------------------
//プレイヤーの描画処理
//------------------------------------------
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;   //デバイスへのポインタ
	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPlayer, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTexturePlayer);

	//プレイヤーの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);//プリミティブの種類,プリミティブの数
}
	
//------------------------------------------
// プレイヤー情報の取得
//------------------------------------------
Player* GetPlayer(void)
{
	return &g_player;
}

//------------------------------------------
// 当たり判定後の処理
//------------------------------------------
void HitPlayer(int nDmg)
{
	VERTEX_2D* pVtx;//頂点情報のポインタ

	g_player.nLife -= nDmg;
	//頂点バッファをロックし,頂点情報へのポインタを取得
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);
	if (g_player.nLife <= 0)
	{
		g_player.bDisp = false;
		g_player.state1 = PLAYERSTATE_DEATH;
		g_player.nCounterState1 = 60;
	}
	else
	{
		g_player.state1 = PLAYERSTATE_DAMAGE;
		g_player.nCounterState1 = 5;

		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);
	}
	//アンロック
	g_pVtxBuffPlayer->Unlock();
}


//------------------------------------------
// キー入力の処理
//------------------------------------------
void GetKeyPlayer(void)
{
	VERTEX_2D* pVtx;        //頂点情報のポインタ
	static float fData = 0.2;

	if (GetKeyboardPress(DIK_A) == true)
	{//左方向
		fData = 0.2;
		g_player.move.x -= 0.4f;
	}
	else if (GetKeyboardPress(DIK_D) == true)
	{
		fData = -0.2;
		//右方向
		g_player.move.x += 0.4f;

	}
		//左＞右
	if (g_player.pos.x + (MAX_X / 2) < 0.0f)
	{
		g_player.pos.x = SCREEN_WIDTH + (MAX_X / 2);
	}
	//右＞左
	else if (g_player.pos.x - (MAX_X / 2) > SCREEN_WIDTH)
	{
		g_player.pos.x = (MAX_X / 2);
	}

	if (g_player.bJump == false)
	{
		if (GetKeyboardPress(DIK_SPACE) == true)
		{
			g_player.move.y = FJUMP;
			g_player.bJump = true;
		}

	}

	if (KeyboardTrigger(DIK_Q) == true)
	{
		SetBullet(D3DXVECTOR3(g_player.pos.x,g_player.pos.y-MAX_Y/2,0.0f), D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI) * MAX_SPEED, cosf(g_player.rot.z + D3DX_PI) * MAX_SPEED, 0.0f), g_player.rot, g_player.fLength, 150, BULLETTYPE_PLAYER);;
	}

	//前回の位置を保存
	g_player.posOld = g_player.pos;

	g_player.move.y += FDA;   //重力加算

	//位置を更新
	g_player.pos.x += g_player.move.x;
	g_player.pos.y += g_player.move.y;

	if (CollsionBlock(&g_player.pos,        //接地時にのみジャンプ可能にする 
		&g_player.posOld,
		&g_player.move,
		MAX_X,
		MAX_Y) == true)
	{
		g_player.bJump = false;
	}

	//移動量を更新(減衰させる)
	g_player.move.x += (0.0f - g_player.move.x) * 0.09f;

	if (g_player.pos.y > SCREEN_HEIGHT)
	{
		g_player.pos.y = SCREEN_HEIGHT;
		g_player.move.y = 0.0f;
		g_player.bJump = false;
	}

	g_nCounterAnimPlayer++;

	if ((g_nCounterAnimPlayer % 4) == 0)
	{
		g_nPatternAnimPlayer = (g_nPatternAnimPlayer + 1) % MAX_PLAYPATTERN;   //パターンNo.を更新する

		//頂点バッファをロックして頂点情報へのポインタを取得
		g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);
		//テクスチャ座標の設定
		if (GetKeyboardPress(DIK_A) == true || GetKeyboardPress(DIK_D) == true)
		{
			//左
			pVtx[0].tex = D3DXVECTOR2(g_nPatternAnimPlayer * 0.25f, (g_nPatternAnimPlayer / 5) * 1.0f);
			pVtx[1].tex = D3DXVECTOR2(fData + g_nPatternAnimPlayer * 0.25f, (g_nPatternAnimPlayer / 5) * 1.0f);
			pVtx[2].tex = D3DXVECTOR2(g_nPatternAnimPlayer * 0.25f, (g_nPatternAnimPlayer / 5) * 1.0f + 1.0f);
			pVtx[3].tex = D3DXVECTOR2(fData + g_nPatternAnimPlayer * 0.25f, (g_nPatternAnimPlayer / 5) * 1.0f + 1.0f);
		}
		//頂点バッファをアンロックする
		g_pVtxBuffPlayer->Unlock();
	}

	//頂点バッファをロックして頂点情報へのポインタを取得
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos.x = g_player.pos.x - (MAX_X / 2.0f);
	pVtx[0].pos.y = g_player.pos.y - MAX_Y;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = g_player.pos.x + (MAX_X / 2.0f);
	pVtx[1].pos.y = g_player.pos.y - MAX_Y;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = g_player.pos.x - (MAX_X / 2.0f);
	pVtx[2].pos.y = g_player.pos.y;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = g_player.pos.x + (MAX_X / 2.0f);
	pVtx[3].pos.y = g_player.pos.y;
	pVtx[3].pos.z = 0.0f;

	//頂点バッファをアンロックする
	g_pVtxBuffPlayer->Unlock();
}