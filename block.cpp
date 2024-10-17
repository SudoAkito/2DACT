 //-----------------------------------------
//
//         ブロックの出力処理
//       Author:Sudou Akito
//
//------------------------------------------
#include"block.h"
#include"player.h"

//ブロックの構造体
typedef struct
{
	D3DXVECTOR3 pos;    //位置
	float fWidth;       //幅
	float fHeight;      //高さ
	bool bUse;          //使用しているかどうか
}Block;

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureBlock = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBlock = NULL;
Block g_aBlock[MAX_BLOCK];

//------------------------------------------
//弾の初期化処理
//------------------------------------------
void InitBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBlock;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\block.png",
		&g_pTextureBlock);

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		g_aBlock[nCntBlock].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBlock[nCntBlock].bUse = false;   //使用していない状態にする

		g_aBlock[nCntBlock].fWidth = 0;

		g_aBlock[nCntBlock].fWidth = 0;
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4*MAX_BLOCK,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBlock,
		NULL);

	VERTEX_2D* pVtx;

	//頂点バッファをロックして頂点情報へのポインタを取得
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < MAX_BLOCK; i++)
	{//頂点座標の設定
		pVtx[0].pos.x = 0.0f;
		pVtx[0].pos.y = 0.0f;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = 0.0f;
		pVtx[1].pos.y = 0.0f;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = 0.0f;
		pVtx[2].pos.y = 0.0f;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = 0.0f;
		pVtx[3].pos.y = 0.0f;
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
		pVtx[1].tex = D3DXVECTOR2(16.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(16.0f, 1.0f);

		pVtx += 4;
	}
		g_pVtxBuffBlock->Unlock();
}

//------------------------------------------
//プレイヤーの終了処理
//------------------------------------------
void UninitBlock(void)
{
	//テクスチャの破棄
	if (g_pTextureBlock != NULL)
	{
		g_pTextureBlock->Release();
		g_pTextureBlock = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffBlock != NULL)
	{
		g_pVtxBuffBlock->Release();
		g_pVtxBuffBlock = NULL;
	}
}

//------------------------------------------
//弾の更新処理
//------------------------------------------
void UpdateBlock(void)
{
	//int nCntBlock;
	//VERTEX_2D* pVtx;

	////頂点バッファをロックして頂点情報へのポインタを取得
	//g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	//for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	//{
	//	//頂点座標の設定
	//	pVtx[0].pos.x = 0.0f;
	//	pVtx[0].pos.y = 680.0f;
	//	pVtx[0].pos.z = 0.0f;

	//	pVtx[1].pos.x = BLOCK_HEIGHT;
	//	pVtx[1].pos.y = 680.0f;
	//	pVtx[1].pos.z = 0.0f;

	//	pVtx[2].pos.x = 0.0f;
	//	pVtx[2].pos.y = 720.0f;
	//	pVtx[2].pos.z = 0.0f;

	//	pVtx[3].pos.x = BLOCK_HEIGHT;
	//	pVtx[3].pos.y = 720.0f;
	//	pVtx[3].pos.z = 0.0f;

	//}
	//pVtx += 4;
	//g_pVtxBuffBlock->Unlock();
}

//------------------------------------------
//弾の描画処理
//------------------------------------------
void DrawBlock(void) 
{
	int nCntBlock;

	LPDIRECT3DDEVICE9 pDevice;   //デバイスへのポインタ
	//デバイスの取得
	pDevice = GetDevice();
	
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBlock, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{
			//弾が使用されている
			//ポリゴンの描画
			pDevice->SetTexture(0, g_pTextureBlock);
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntBlock, 2);
		}
	}
}

//------------------------------------------
//ブロックの設定処理
//------------------------------------------
void SetBlock(D3DXVECTOR3 pos,float fWidth,float fHeight)
{

	int nCntBlock;
	VERTEX_2D* pVtx;

	//頂点バッファをロックして頂点情報へのポインタを取得
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == false)
		{
			g_aBlock[nCntBlock].pos = pos;
			g_aBlock[nCntBlock].bUse = true;
			g_aBlock[nCntBlock].fWidth = fWidth;
			g_aBlock[nCntBlock].fHeight = fHeight;

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x - (fWidth / 2), g_aBlock[nCntBlock].pos.y - (fHeight / 2), g_aBlock[nCntBlock].pos.z);
			pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (fWidth / 2), g_aBlock[nCntBlock].pos.y - (fHeight / 2), g_aBlock[nCntBlock].pos.z);
			pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x - (fWidth / 2), g_aBlock[nCntBlock].pos.y + (fHeight / 2), g_aBlock[nCntBlock].pos.z);
			pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (fWidth / 2), g_aBlock[nCntBlock].pos.y + (fHeight / 2), g_aBlock[nCntBlock].pos.z);
																										  

			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			//テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(16.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(16.0f, 1.0f);

			break;
		}
		pVtx += 4;
	}
	g_pVtxBuffBlock->Unlock();
}

//ブロックの当たり判定
bool CollsionBlock(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3* pMove, float fWidth, float fHeight)
{
	bool bLanding = false;       //着地しているかどうか

	for (int nCntblo = 0; nCntblo < MAX_BLOCK; nCntblo++)
	{
		if (g_aBlock[nCntblo].bUse == true)
		{
			if (pPos->x + MAX_X / 2 > g_aBlock[nCntblo].pos.x - g_aBlock[nCntblo].fWidth / 2 && pPos->x - MAX_X / 2 < g_aBlock[nCntblo].pos.x + g_aBlock[nCntblo].fWidth / 2)
			{
				//上から下の判定
				if (pPosOld->y <= g_aBlock[nCntblo].pos.y - g_aBlock[nCntblo].fHeight / 2 && pPos->y > g_aBlock[nCntblo].pos.y - g_aBlock[nCntblo].fHeight / 2)
				{
					bLanding = true;
					pPos->y = g_aBlock[nCntblo].pos.y - (g_aBlock[nCntblo].fHeight / 2);
					pMove->y = 0.0f;
				}
				//下から上の判定
				/*else if (pPosOld->y - MAX_Y >=g_aBlock[nCntblo].pos.y + g_aBlock[nCntblo].fHeight / 2 && pPos->y - MAX_Y < g_aBlock[nCntblo].pos.y + g_aBlock[nCntblo].fHeight / 2)
				{
					pPos->y =g_aBlock[nCntblo].pos.y - g_aBlock[nCntblo].fHeight / 2;
					pMove->y =0.0f;
				}
				 */

				if (pPosOld->y > g_aBlock[nCntblo].pos.y - g_aBlock[nCntblo].fHeight / 2 && pPosOld->y - MAX_Y < g_aBlock[nCntblo].pos.y + g_aBlock[nCntblo].fHeight / 2)
				{
					//左から右にめり込んだ
					if (pPosOld->x + MAX_X / 2 <= g_aBlock[nCntblo].pos.x - g_aBlock[nCntblo].fWidth / 2 && pPos->x + MAX_X / 2 > g_aBlock[nCntblo].pos.x - g_aBlock[nCntblo].fWidth / 2)
					{
						pPos->x = g_aBlock[nCntblo].pos.x - g_aBlock[nCntblo].fWidth / 2 - MAX_X / 2;
						pMove->x = 0.0f;
					}
					else if (pPosOld->x - MAX_X / 2 >= g_aBlock[nCntblo].pos.x + g_aBlock[nCntblo].fWidth / 2 && pPos->x - MAX_X / 2 < g_aBlock[nCntblo].pos.x + g_aBlock[nCntblo].fWidth / 2)
					{
						pPos->x = g_aBlock[nCntblo].pos.x + g_aBlock[nCntblo].fWidth / 2 - MAX_X / 2;
						pMove->x = 0.0f;
					}
				}
			}
		}
	}
	return bLanding;
}