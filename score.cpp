//------------------------------------------
//
//     　 スコア処理
//       Author:Sudou Akito
//
//------------------------------------------

#include "score.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureScore = NULL;      //テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL; //頂点バッファポインタ
D3DXVECTOR3 g_posScore;                         //スコアの位置
int g_nScore;                                   //スコアの値

//スコア型のグローバル変数
Score g_aScore[MAX_SCORE];

//------------------------------------------
//　スコア初期化処理
//------------------------------------------
void InitScore(void)
{
	int nCntscore;
	LPDIRECT3DDEVICE9 pDevice;   //デバイスへのポインタ
	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Number1.png",
		&g_pTextureScore);

	g_posScore = D3DXVECTOR3(0.0f,0.0f,0.0f);  //位置初期化
	g_nScore = 0;                              //値初期化

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 *MAX_SCORE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffScore,
		NULL);

	VERTEX_2D* pVtx;       //頂点情報のポインタ

	//頂点バッファをロックして頂点情報へのポインタを取得
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntscore = 0; nCntscore < MAX_SCORE; nCntscore++)
	{
		g_aScore[nCntscore].bUse = true;

		//頂点座標設定
		pVtx[0].pos = D3DXVECTOR3(820.0f + nCntscore * 40.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(820.0f + nCntscore * 40.0f + 40.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(820.0f + nCntscore * 40.0f, 90.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(820.0f + nCntscore * 40.0f + 40.0f, 90.0f, 0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255,255,255,255);
		pVtx[1].col = D3DCOLOR_RGBA(255,255,255,255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;
	}
	
	//頂点バッファをアンロックする
	g_pVtxBuffScore->Unlock();

	SetScore(0);
}

//------------------------------------------
//  スコア終了処理
//------------------------------------------
void UninitScore(void)
{
	//テクスチャの破棄
	if (g_pTextureScore != NULL)
	{
		g_pTextureScore->Release();
		g_pTextureScore = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffScore != NULL)
	{
		g_pVtxBuffScore->Release();
		g_pVtxBuffScore = NULL;
	}
}

//------------------------------------------
//  スコア更新処理
//------------------------------------------
void UpdateScore(void)
{
	int nData;  //ローカル変数

	//桁数保存
	nData = ScoreCounter(g_nScore);

	for (int nData1 = 0; nData1 < MAX_SCORE; nData1++)
	{
		if (nData >= MAX_SCORE - nData1)
		{
			//上の条件式を有効化
			g_aScore[nData1].bUse = true;
		}
		else
		{
			//それ以外の場合
			g_aScore[nData1].bUse = false;
		}
	}

}

//------------------------------------------
//     スコア描画処理
//------------------------------------------
void DrawScore(void)
{
	//必要桁数分の描画
	LPDIRECT3DDEVICE9 pDevice;   //デバイスへのポインタ
	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffScore, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);


	for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		if (g_aScore[nCnt].bUse == true)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureScore);

			//スコアの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCnt, 2);//プリミティブの種類,プリミティブの数
		}
	}

}

//------------------------------------------
//     スコア設定処理
//------------------------------------------
void SetScore(int nScore)
{
	int aPosTexU[MAX_SCORE] = {};    //各桁の数字を格納
	g_nScore = nScore;
	int eight = EIGHT;
	int seven = SEVEN;
	VERTEX_2D* pVtx;       //頂点情報のポインタ

	//頂点バッファをロックして頂点情報へのポインタを取得
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += (MAX_SCORE- 1)* 4 ;
	for (int nCnt = MAX_SCORE -  1; nCnt >= 0; nCnt--)
	{
		if (nCnt == 0)
		{
			aPosTexU[0] = g_nScore / EIGHT;
		}
		else
		{
			aPosTexU[nCnt] = g_nScore % EIGHT / SEVEN;
			eight = EIGHT / 10;
			seven = SEVEN / 10;
		}
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f * aPosTexU[nCnt]), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU[nCnt]), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (0.1f * aPosTexU[nCnt]), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU[nCnt]), 1.0f);

		pVtx -= 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffScore->Unlock();
}

//------------------------------------------
//     スコア加算処理
//------------------------------------------
void AddScore(int nValue)
{
	int aPosTexU[MAX_SCORE] = {};   //各桁の数字を格納
	int nCnt{};
	VERTEX_2D* pVtx;       //頂点情報のポインタ
	g_nScore += nValue;

	int eight = EIGHT;
	int seven = SEVEN;


	//頂点バッファをロックして頂点情報へのポインタを取得
 	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	int nBuf = g_nScore;

	pVtx += (MAX_SCORE - 1) * 4;
	for (int nCnt = MAX_SCORE - 1; nCnt >= 0; nCnt--)
	{
		aPosTexU[nCnt] = nBuf % 10;
		nBuf /= 10;

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f+(0.1f * aPosTexU[nCnt]), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f+(0.1f * aPosTexU[nCnt]), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f+(0.1f * aPosTexU[nCnt]), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f+(0.1f * aPosTexU[nCnt]), 1.0f);

		pVtx -= 4;
	}
	
	//頂点バッファをアンロックする
	g_pVtxBuffScore->Unlock();
}

//------------------------------------------
//     スコア0カウント
//------------------------------------------
int ScoreCounter(int nScore)
{
	int nNum = nScore;//スコアの０の部分をカウント
	int nNum1 = 0;    //スコア桁数

	while (nNum != 0)
	{
		nNum /= 10;  //10で÷
		nNum1++;    //桁数加算
	}
	if (nScore == 0)
	{//1桁目に0がはいってるとき
		nNum1 = 1;
	}

	return nNum1;    //スコア桁数を返す
}

//------------------------------------------
//     スコアの取得
//------------------------------------------
int GetScore(void)
{
	return g_nScore;
}