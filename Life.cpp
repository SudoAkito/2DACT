#include"Life.h"
#include"Player.h"


//マクロ
#define MAX_LIFE (3)


//グローバル
LPDIRECT3DTEXTURE9 g_pTextureLife = NULL;                           //テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLife = NULL;                      //頂点バッファへのポインタ
Life g_aLife[MAX_LIFE];
int g_nPlayerLife;



void InitPlayerHeart(void)
{
	LPDIRECT3DDEVICE9 pDevice;         //デバイスへのポインタ


	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Heart.png",
		&g_pTextureLife);

	int nCnt;
	for (nCnt = 0; nCnt < MAX_LIFE; nCnt++)
	{
		g_aLife[nCnt].pos = D3DXVECTOR3(30.0f + (20 * nCnt), 10.0f, 0.0f);
		g_aLife[nCnt].bUse = false;
	}
	VERTEX_2D* pVtx;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_LIFE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffLife,
		NULL);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffLife->Lock(0, 0, (void**)&pVtx, 0);

	for (nCnt = 0; nCnt < MAX_LIFE; nCnt++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(0.0f +(50 * nCnt), 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(50.0f +(50 * nCnt), 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f +(50 * nCnt), 80.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(50.0f +(50 * nCnt), 80.0f, 0.0f);

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

		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffLife->Unlock();
}

void UninitPlayerHeart(void)
{
	//テクスチャの破棄
	if (g_pTextureLife != NULL)
	{
		g_pTextureLife->Release();
		g_pTextureLife = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffLife != NULL)
	{
		g_pVtxBuffLife->Release();
		g_pVtxBuffLife = NULL;
	}
}

void DrawPlayerHeart(void)
{
	LPDIRECT3DDEVICE9 pDevice;     //デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffLife, 0, sizeof(VERTEX_2D));

	for (int nCnt = 0; nCnt < MAX_LIFE; nCnt++)
	{
		if (g_aLife[nCnt].bUse == true)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureLife);

			//プレイヤーの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
		}
	}

}

void UpdatePlayerHeart(void)
{
	int nCnt = 0;
	VERTEX_2D* pVtx;
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffLife->Lock(0, 0, (void**)&pVtx, 0);

	if (g_nPlayerLife == MAX_LIFE)
	{
		for (nCnt = 0; nCnt < g_nPlayerLife; nCnt++)
		{
			g_aLife[nCnt].bUse = true;
		}
	}
	else if (g_nPlayerLife >= MAX_LIFE)
	{
		g_nPlayerLife = MAX_LIFE;
	}
	else if (g_nPlayerLife <= 2)
	{

		if (g_nPlayerLife <= 2)
		{
			g_aLife[2].bUse = false;
			if (g_nPlayerLife <= 1)
			{
				g_aLife[1].bUse = false;
				if (g_nPlayerLife <= 0)
				{
					g_aLife[0].bUse = false;

				}
			}
		}

	}
	//頂点バッファをアンロックする
	g_pVtxBuffLife->Unlock();
}

void SetLife(int nLife)
{
	g_nPlayerLife = nLife;
}