//------------------------------------------
//
//          タイトル処理
//       Author:Sudou Akito
//
//------------------------------------------

#include"title.h"
#include"sound.h"
#include "fade.h"


//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureTitle= NULL;    //テクスチャポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL; //頂点バッファポイン
LPDIRECT3DTEXTURE9 g_pTextureTITLE1 = NULL;    //テクスチャポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTITLE1 = NULL; //頂点バッファポインタ
LPDIRECT3DTEXTURE9 g_pTextureTITLE2 = NULL;    //テクスチャポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTITLE2 = NULL; //頂点バッファポインタ


int g_nCounter;//タイムカウンター

//タイトル画面の初期化
void InitTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D* pVtx;       //頂点情報のポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\titlebg.png",
		&g_pTextureTitle);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Deadly Sight .png",
		&g_pTextureTITLE1);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\enter.png",
		&g_pTextureTITLE2);
	

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTITLE1,
		NULL);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTITLE2,
		NULL);

	g_nCounter = 0;//初期化

	//頂点バッファをロックして頂点情報へのポインタを取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

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
	g_pVtxBuffTitle->Unlock();

	TitlepVtx();

	EnterpVtx();

	//サウンド再生
	PlaySound(SOUND_LABEL_BGM);
	/*PlaySound(SOUND_LABEL_SE);*/
}

void UninitTitle(void)
{
	//テクスチャの破棄
	if (g_pTextureTitle != NULL)
	{
		g_pTextureTitle->Release();
		g_pTextureTitle = NULL;
	}

	//テクスチャの破棄
	if (g_pTextureTITLE1 != NULL)
	{			  
		g_pTextureTITLE1->Release();
		g_pTextureTITLE1 = NULL;
	}

	//テクスチャの破棄
	if (g_pTextureTITLE2 != NULL)
	{
		g_pTextureTITLE2->Release();
		g_pTextureTITLE2 = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffTITLE1 != NULL)
	{			  
		g_pVtxBuffTITLE1->Release();
		g_pVtxBuffTITLE1 = NULL;
	}			  

	//頂点バッファの破棄
	if (g_pVtxBuffTITLE2 != NULL)
	{
		g_pVtxBuffTITLE2->Release();
		g_pVtxBuffTITLE2 = NULL;
	}

	//サウンド停止
	StopSound();
}

void UpdateTitle(void)
{
	if (KeyboardTrigger(DIK_RETURN) == true||JoypadTrigger(JOYKEY_START)==true)
	{  //決定キーが押された
		//モード設定(ゲーム画面に移行)
		SetFade(MODE_SET);
	}

	g_nCounter++;//カウンターを加算
	if (g_nCounter >= 600)
	{
		SetFade(MODE_RANKING);//画面遷移
	}
}

void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;   //デバイスへのポインタ
		//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureTitle);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);//プリミティブの種類,プリミティブの数

	DrawT();

	DrawP();
}

void DrawT(void)
{
	LPDIRECT3DDEVICE9 pDevice;   //デバイスへのポインタ
		//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTITLE1, 0, sizeof(VERTEX_2D));

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureTITLE1);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);//プリミティブの種類,プリミティブの数
}

void DrawP(void)
{
	LPDIRECT3DDEVICE9 pDevice;   //デバイスへのポインタ
		//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTITLE2, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureTITLE2);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);//プリミティブの種類,プリミティブの数
}

void TitlepVtx(void)
{
	VERTEX_2D* pVtx;       //頂点情報のポインタ

	//頂点バッファをロックして頂点情報へのポインタを取得
	g_pVtxBuffTITLE1->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(185.0f, 100.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1095.0f, 100.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(185.0f, 220.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1095.0f, 220.0f, 0.0f);

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
	g_pVtxBuffTITLE1->Unlock();

}

void EnterpVtx(void)
{
	VERTEX_2D* pVtx;       //頂点情報のポインタ

	//頂点バッファをロックして頂点情報へのポインタを取得
	g_pVtxBuffTITLE2->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(222.0f, 520.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1058.0f, 520.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(222.0f, 643.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1058.0f, 643.0f, 0.0f);

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
	g_pVtxBuffTITLE2->Unlock();

}