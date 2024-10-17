//------------------------------------------
//
//         チュートリアル処理
//       Author:Sudou Akito
//
//------------------------------------------

#include"set.h"
#include"fade.h"
#include"input.h"


//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureSet = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSet = NULL;

//------------------------------------------
//チュートリアルの初期化処理
//------------------------------------------
void InitSet(void)
{
	LPDIRECT3DDEVICE9 pDevice;   //デバイスへのポインタ
	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\set.png",
		&g_pTextureSet);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffSet,
		NULL);

	VERTEX_2D* pVtx;       //頂点情報のポインタ

	//頂点バッファをロックして頂点情報へのポインタを取得
	g_pVtxBuffSet->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffSet->Unlock();
}

//------------------------------------------
//チュートリアルの終了処理
//------------------------------------------
void UninitSet(void)
{
	//テクスチャの破棄
	if (g_pTextureSet != NULL)
	{
		g_pTextureSet->Release();
		g_pTextureSet = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffSet != NULL)
	{			  
		g_pVtxBuffSet->Release();
		g_pVtxBuffSet = NULL;
	}
}

//------------------------------------------
//チュートリアルの更新処理
//------------------------------------------
void UpdateSet(void)
{
	if (KeyboardTrigger(DIK_RETURN) == true || JoypadTrigger(JOYKEY_START) == true)
	{  //決定キーが押された
		//モード設定(ゲーム画面に移行)
		SetFade(MODE_GAME);
	}
}


//------------------------------------------
//チュートリアルの更新処理
//------------------------------------------
void DrawSet(void)
{
	LPDIRECT3DDEVICE9 pDevice;   //デバイスへのポインタ
		//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffSet, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureSet);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);//プリミティブの種類,プリミティブの数
}
