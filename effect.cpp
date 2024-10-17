//------------------------------------------
//
//         エフェクトの出力処理
//       Author:Sudou Akito
//
//------------------------------------------
#include"effect.h"

//マクロ定義
#define MAX_EFFECT (4096)  //エフェクトの最大数
#define EFFECT_WIDTH (50)
#define EFFECT_HEIGHT (50)

//弾の構造体
typedef struct
{
	D3DXVECTOR3 pos; //位置
	D3DXVECTOR3 move; //移動量
	D3DXCOLOR col;   //移動量
	D3DXVECTOR3 rot;
	float fRadius;
	float fPullMove;
	float fPullRadius;
	float falfa;
	float fData;
	int nLife;       //寿命(表示時間)
	bool bUse;       //使用しているかどうか
}EFFECT;

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureEffect = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;
EFFECT g_aEffect[MAX_EFFECT];                    //エフェクトの情報


//------------------------------------------
//エフェクトの初期化処理
//------------------------------------------
void InitEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntEffect;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\effect000.jpg",
		&g_pTextureEffect);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_EFFECT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEffect,
		NULL);

	VERTEX_2D* pVtx;

	//頂点バッファをロックして頂点情報へのポインタを取得
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	//弾の初期化
	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		g_aEffect[nCntEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntEffect].move = D3DXVECTOR3 (0.0f,0.0f,0.0f);
		g_aEffect[nCntEffect].col = D3DXCOLOR(0.7f,0.2f,0.7f,1.0f);
		g_aEffect[nCntEffect].nLife = 10;
		g_aEffect[nCntEffect].fRadius = 0;
		g_aEffect[nCntEffect].fPullMove = 0;
		g_aEffect[nCntEffect].fData = 0;
		g_aEffect[nCntEffect].falfa = 0;
		g_aEffect[nCntEffect].bUse = false;   //使用していない状態にする

		//頂点座標の設定
		pVtx[0].pos.x = g_aEffect[nCntEffect].pos.x-50.0f;
		pVtx[0].pos.y = g_aEffect[nCntEffect].pos.y-25.0f;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = g_aEffect[nCntEffect].pos.x+ 50.0f;
		pVtx[1].pos.y = g_aEffect[nCntEffect].pos.y- 25.0f;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = g_aEffect[nCntEffect].pos.x- 50.0f;
		pVtx[2].pos.y = g_aEffect[nCntEffect].pos.y+ 25.0f;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = g_aEffect[nCntEffect].pos.x+ 50.0f;
		pVtx[3].pos.y = g_aEffect[nCntEffect].pos.y+ 25.0f;
		pVtx[3].pos.z = 0.0f;

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;          //頂点データを4つ分進める
	}
	//頂点バッファをアンロックする
	g_pVtxBuffEffect->Unlock();
}

//------------------------------------------
//エフェクトの終了処理
//------------------------------------------
void UninitEffect(void)
{

	//テクスチャの破棄
	if (g_pTextureEffect != NULL)
	{
		g_pTextureEffect->Release();
		g_pTextureEffect = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}
}

//------------------------------------------
//エフェクトの更新処理
//------------------------------------------
void UpdateEffect(void)
{
	VERTEX_2D* pVtx;
	int nCntEffect;
	//頂点バッファをロックして頂点情報へのポインタを取得
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == true)
		{
			//頂点カラーの設定(更新)
			pVtx[0].col =  g_aEffect[nCntEffect].col;
			pVtx[1].col =  g_aEffect[nCntEffect].col;
			pVtx[2].col =  g_aEffect[nCntEffect].col;
			pVtx[3].col =  g_aEffect[nCntEffect].col;

			//頂点座標の更新
			pVtx[0].pos.x = g_aEffect[nCntEffect].pos.x - g_aEffect[nCntEffect].fRadius/2;
			pVtx[0].pos.y = g_aEffect[nCntEffect].pos.y - g_aEffect[nCntEffect].fRadius/2;
			pVtx[0].pos.z = 0.0f;

			pVtx[1].pos.x = g_aEffect[nCntEffect].pos.x + g_aEffect[nCntEffect].fRadius/2;
			pVtx[1].pos.y = g_aEffect[nCntEffect].pos.y - g_aEffect[nCntEffect].fRadius/2;
			pVtx[1].pos.z = 0.0f;

			pVtx[2].pos.x = g_aEffect[nCntEffect].pos.x - g_aEffect[nCntEffect].fRadius/2;
			pVtx[2].pos.y = g_aEffect[nCntEffect].pos.y + g_aEffect[nCntEffect].fRadius/2;
			pVtx[2].pos.z = 0.0f;

			pVtx[3].pos.x = g_aEffect[nCntEffect].pos.x + g_aEffect[nCntEffect].fRadius/2;
			pVtx[3].pos.y = g_aEffect[nCntEffect].pos.y + g_aEffect[nCntEffect].fRadius/2;
			pVtx[3].pos.z = 0.0f;

			//移動量を更新
			g_aEffect[nCntEffect].pos.x += g_aEffect[nCntEffect].move.x;
			g_aEffect[nCntEffect].pos.y += g_aEffect[nCntEffect].move.y;

			//ポリゴンサイズ
			g_aEffect[nCntEffect].fRadius -= g_aEffect[nCntEffect].fPullRadius;

			//寿命
			g_aEffect[nCntEffect].nLife--;

			//α値減少
			g_aEffect[nCntEffect].falfa += g_aEffect[nCntEffect].falfa * -1 * g_aEffect[nCntEffect].fData;

			//移動量減衰
			g_aEffect[nCntEffect].move.x += g_aEffect[nCntEffect].move.x * -1 * g_aEffect[nCntEffect].fPullMove;
			g_aEffect[nCntEffect].move.y += g_aEffect[nCntEffect].move.y * -1 * g_aEffect[nCntEffect].fPullMove;

		}
			if(g_aEffect[nCntEffect].nLife <= 0)
			{
				g_aEffect[nCntEffect].bUse=false;
			}
			pVtx += 4;          //頂点データを4つ分進める
	}
	//頂点バッファをアンロックする
	g_pVtxBuffEffect->Unlock();
}

//------------------------------------------
//エフェクトの描画処理
//------------------------------------------
void DrawEffect(void)
{
	int nCntEffect;

	LPDIRECT3DDEVICE9 pDevice;   //デバイスへのポインタ
	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//αブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);  //ブレンド方法
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		pDevice->SetTexture(0, g_pTextureEffect);
		if (g_aEffect[nCntEffect].bUse == true)
		{
			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntEffect, 2);
		}
	}

	//αブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//------------------------------------------
//エフェクトの設定処理
//------------------------------------------
void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fRadius,float falfa,float fData,float fPullRadius,float fPullMove,int nLife)
{
	VERTEX_2D* pVtx;
	int nCntEffect;


	//頂点バッファをロックして頂点情報へのポインタを取得
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == false)
		{
			g_aEffect[nCntEffect].pos = pos;
			g_aEffect[nCntEffect].move = move;
			g_aEffect[nCntEffect].col = col;
			g_aEffect[nCntEffect].nLife = nLife;
			g_aEffect[nCntEffect].fRadius = fRadius;
			g_aEffect[nCntEffect].fPullRadius = fPullRadius;
			g_aEffect[nCntEffect].falfa = falfa;
			g_aEffect[nCntEffect].fData = fData;
			g_aEffect[nCntEffect].bUse = true;//使用してる状態にする


		//頂点座標の設定（更新）
			pVtx[0].pos.x = g_aEffect[nCntEffect].pos.x - g_aEffect[nCntEffect].fRadius / 2;
			pVtx[0].pos.y = g_aEffect[nCntEffect].pos.y - g_aEffect[nCntEffect].fRadius / 2;
			pVtx[0].pos.z = 0.0f;

			pVtx[1].pos.x = g_aEffect[nCntEffect].pos.x + g_aEffect[nCntEffect].fRadius / 2;
			pVtx[1].pos.y = g_aEffect[nCntEffect].pos.y - g_aEffect[nCntEffect].fRadius / 2;
			pVtx[1].pos.z = 0.0f;

			pVtx[2].pos.x = g_aEffect[nCntEffect].pos.x - g_aEffect[nCntEffect].fRadius / 2;
			pVtx[2].pos.y = g_aEffect[nCntEffect].pos.y + g_aEffect[nCntEffect].fRadius / 2;
			pVtx[2].pos.z = 0.0f;

			pVtx[3].pos.x = g_aEffect[nCntEffect].pos.x + g_aEffect[nCntEffect].fRadius / 2;
			pVtx[3].pos.y = g_aEffect[nCntEffect].pos.y + g_aEffect[nCntEffect].fRadius / 2;
			break;
		}
		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffEffect->Unlock();
}