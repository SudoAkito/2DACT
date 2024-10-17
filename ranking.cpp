//------------------------------------------
//
//         ランキング処理
//       Author:Sudou Akito
//
//------------------------------------------

#include"ranking.h"
#include "fade.h"
#include "input.h"

//ランキングスコア構造体
typedef struct
{
	D3DXVECTOR3 pos;     //位置
	int nScore;          //スコア
}RankScore;

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureRank = NULL;      //テクスチャのポインタ
LPDIRECT3DTEXTURE9 g_pTextureRankScore = NULL; //テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRank = NULL; //頂点バッファポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRankScore = NULL; //頂点バッファポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRankBG = NULL; //頂点バッファポインタ
LPDIRECT3DTEXTURE9 g_pTextureRankBG = NULL; //テクスチャのポインタ

RankScore g_aRankScore[MAX_RANK];              //ランキングスコア情報
int g_nRankUpdate = -1;                        //更新ランクNo.
int g_nTimerRanking;                           //ランキング表示タイマー
int g_Score1[5] = {};

//------------------------------------------
//ランキングの初期化処理
//------------------------------------------
void InitRanking(void)
{
	LPDIRECT3DDEVICE9 pDevice;   //デバイスへのポインタ
	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\rank.png",
		&g_pTextureRank);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Number1.png",
		&g_pTextureRankScore);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\haikei.png",
		&g_pTextureRankBG);


	//g_nRankUpdate = -1;
	g_nTimerRanking = 0;
	for (int i = 0; i < MAX_RANK; i++)
	{
		g_Score1[i] = 0;
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRank,
		NULL);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_RANK*8,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRankScore,
		NULL);


	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRankBG,
		NULL);


	SetpVtx2();

	SetpVtx();    //順位用頂点座標

	SetpVtx1(0,0,0);   //スコア用頂点座標

	ResetRanking();

}

//------------------------------------------
//ランキングの終了処理
//------------------------------------------
void UninitRanking(void)
{
	//テクスチャの破棄
	if (g_pTextureRank != NULL)
	{
		g_pTextureRank->Release();
		g_pTextureRank = NULL;
	}

	if (g_pTextureRankScore != NULL)
	{
		g_pTextureRankScore->Release();
		g_pTextureRankScore = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffRank != NULL)
	{
		g_pVtxBuffRank->Release();
		g_pVtxBuffRank = NULL;
	}

	if (g_pVtxBuffRankScore != NULL)
	{
		g_pVtxBuffRankScore->Release();
		g_pVtxBuffRankScore = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffRankBG != NULL)
	{				  
		g_pTextureRankBG->Release();
		g_pTextureRankBG = NULL;
	}

	if (g_pVtxBuffRankBG != NULL)
	{				  
		g_pVtxBuffRankBG->Release();
		g_pVtxBuffRankBG = NULL;
	}
}

//------------------------------------------
//ランキングの更新処理
//------------------------------------------
void UpdateRanking(void)
{
	static int nCounter{};

	if (g_nRankUpdate != -1)
	{
		nCounter++;   //加算

		//該当スコアを点滅
		if (nCounter == 10)
		{
			VERTEX_2D* pVtx{};       //頂点情報のポインタ

			//頂点バッファをロックして頂点情報へのポインタを取得
			g_pVtxBuffRankScore->Lock(0, 0, (void**)&pVtx, 0);

			pVtx += (32 * g_nRankUpdate);

			for (int nCnt = 0; nCnt < 8; nCnt++)
			{
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 120);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 120);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 120);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 120);
				pVtx += 4;
			}

			g_pVtxBuffRankScore->Unlock();
		}
		else if (nCounter == 20)
		{
			VERTEX_2D* pVtx{};       //頂点情報のポインタ

			//頂点バッファをロックして頂点情報へのポインタを取得
			g_pVtxBuffRankScore->Lock(0, 0, (void**)&pVtx, 0);

			pVtx += (32 * g_nRankUpdate);

			for (int nCnt = 0; nCnt < 8; nCnt++)
			{
				pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 120);
				pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 120);
				pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 120);
				pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 120);
				pVtx += 4;
			}

			g_pVtxBuffRankScore->Unlock();

			nCounter = 0;
		}
		
	}
	
	g_nTimerRanking++;
	if(g_nTimerRanking>=600||GetJoypadPress(JOYKEY_BACK) == true|| KeyboardTrigger(DIK_RETURN) == true)
	{
		//タイトル画面に遷移
		SetFade(MODE_TITLE);
	}
}

//------------------------------------------
//ランキングの描画処理1
//------------------------------------------
void DrawRanking(void)
{

	LPDIRECT3DDEVICE9 pDevice;   //デバイスへのポインタ
	//デバイスの取得
	pDevice = GetDevice();

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffRank, 0, sizeof(VERTEX_2D));

	pDevice->SetTexture(0, g_pTextureRank);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0, 2);


	DrawRankScore();
}

//------------------------------------------
//ランキングの描画処理2
//------------------------------------------
void DrawRankScore(void)
{

	LPDIRECT3DDEVICE9 pDevice;   //デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt1 = 0; nCnt1 < MAX_RANK; nCnt1++)
	{
		for (int nCnt = 0; nCnt < 8; nCnt++)
		{
			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffRankScore, 0, sizeof(VERTEX_2D));

			pDevice->SetTexture(0, g_pTextureRankScore);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (32 * nCnt1) + (4 * nCnt), 2);
		}
	}
}

// -----------------------------------------
//ランキングの情報の取得
//------------------------------------------
void ResetRanking(void)
{
	FILE* pFile;

	pFile = fopen("data\\txt\\ranking.txt", "r");

	if (pFile != NULL)
	{
		for (int nCnt = 0; nCnt < MAX_RANK; nCnt++)
		{
			fscanf(pFile, "%d", &g_Score1[nCnt]);
		}
	}
	else
	{
		MessageBox(NULL,"開封出来ませんでした。","エラー",MB_OK);

		return;
	}
	fclose(pFile);


	for (int nCnt = 0; nCnt < MAX_RANK; nCnt++)
	{
		int adigits[8];
		int nData = 10000000, aData = 1000000;

		for (int nCntdigit = 0; nCntdigit < 8; nCntdigit++)
		{
			if (nCntdigit == 0)
			{
				adigits[0] = g_Score1[nCnt] / nData;
			}
			else
			{
				adigits[nCntdigit] = g_Score1[nCnt] % nData / aData;
				nData = nData / 10;
				aData = aData / 10;
			}
			SetpVtx1(nCnt, nCntdigit, adigits[nCntdigit]);
		}
	}

}

// -----------------------------------------
//ランキングの設定
//------------------------------------------
void SetRanking(int nScore)
{
	FILE* pFile;

	pFile = fopen("data\\txt\\ranking.txt", "r");

	if (pFile != NULL)
	{
		for (int nCnt = 0; nCnt < MAX_RANK; nCnt++)
		{
			fscanf(pFile, "%d", &g_Score1[nCnt]);
		}
	}
	else
	{
		MessageBox(NULL, "開封出来ませんでした。", "エラー", MB_OK);

		return;
	}

	fclose(pFile);

	int nCntRank;
	int Temp{};

	for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{
		for (int nCnt2 = nCntRank + 1; nCnt2 < MAX_RANK; nCnt2++)
		{
			if (g_Score1[nCntRank] <= g_Score1[nCnt2])
			{
				Temp = g_Score1[nCntRank]; //上書き前保存
				g_Score1[nCntRank] = g_Score1[nCnt2];//上書き
				g_Score1[nCnt2] = Temp;//保存した値で上書き
			}
		}
	}

	bool bChange = false;	// リザルトを変更したかどうか
	int nResult = -1;		// ランクインした順位 (-1 の場合はランク外)
	for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{
		if (g_Score1[nCntRank] < nScore)
		{
			if (bChange == false)
			{ // まだ変更されていない (つまり最初の変更)
				nResult = nCntRank;
				bChange = true;	// すでに変更済み
			}
			Temp = g_Score1[nCntRank]; //上書き前保存
			g_Score1[nCntRank] = nScore;//上書き
			nScore = Temp;//保存した値で上書き
		}
	}
	g_nRankUpdate = nResult;	// ランクを登録

	pFile = fopen("data\\txt\\ranking.txt", "w");

	if (pFile != NULL)
	{
		for (int nCnt = 0; nCnt < MAX_RANK; nCnt++)
		{
			fprintf(pFile, "%d\n", g_Score1[nCnt]);
		}
	}
	else
	{
		MessageBox(NULL, "開封出来ませんでした。", "エラー", MB_OK);

		return;
	}
	fclose(pFile);

	//指定スコアがランクインしたらg_nRankUpdateを更新してテクスチャ座標の設定

}
// -----------------------------------------
//ランキングのカラー設定
//------------------------------------------
//void SetRankcolor(void)
//{
//
//	VERTEX_2D* pVtx;       //頂点情報のポインタ
//
//	//頂点バッファをロックして頂点情報へのポインタを取得
//	g_pVtxBuffRank->Lock(0, 0, (void**)&pVtx, 0);
//
//	//頂点カラーの設定
//	pVtx[0].col = D3DCOLOR_RGBA(255,0,0,255);
//	pVtx[1].col = D3DCOLOR_RGBA(255,0,0,255);
//	pVtx[2].col = D3DCOLOR_RGBA(255,0,0,255);
//	pVtx[3].col = D3DCOLOR_RGBA(255,0,0,255);
//
//
//	//頂点バッファをアンロックする
//	g_pVtxBuffRank->Unlock();
//}


// -----------------------------------------
//順位用頂点座標設定
//------------------------------------------
void SetpVtx (void)
{

	VERTEX_2D* pVtx;       //頂点情報のポインタ

	//頂点バッファをロックして頂点情報へのポインタを取得
	g_pVtxBuffRank->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標設定
	pVtx[0].pos = D3DXVECTOR3(220.0f,90.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(369.0f,90.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(220.0f,620.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(369.0f,620.0f, 0.0f);

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
	g_pVtxBuffRank->Unlock();
}

// -----------------------------------------
//　スコアランキング用頂点座標設定
//------------------------------------------
void SetpVtx1(int nCntRank,int nCntd, int nNumber)
{
	VERTEX_2D* pVtx;       //頂点情報のポインタ

	//頂点バッファをロックして頂点情報へのポインタを取得
	g_pVtxBuffRankScore->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += ((nCntRank*32)+(nCntd*4));

	float min_x = 450.0f+50.0f*nCntd;
	float min_y = 100.0f+100.0f*nCntRank;
	float max_x = min_x+50.0f;
	float max_y = min_y+100.0f;

	
	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(min_x,min_y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(max_x, min_y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(min_x, max_y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(max_x, max_y, 0.0f);

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

	float fu1 = nNumber * 0.1f;
	float fu2 = fu1 + 0.1f;

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(fu1, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(fu2, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(fu1, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(fu2, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffRankScore->Unlock();
}

void DrawBG(void)
{

	LPDIRECT3DDEVICE9 pDevice;   //デバイスへのポインタ
	//デバイスの取得
	pDevice = GetDevice();

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffRankBG, 0, sizeof(VERTEX_2D));

	pDevice->SetTexture(0, g_pTextureRankBG);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

// -----------------------------------------
//　ランキング用背景設定
//------------------------------------------
void SetpVtx2(void)
{

	VERTEX_2D* pVtx;       //頂点情報のポインタ


		//頂点バッファをロックして頂点情報へのポインタを取得
	g_pVtxBuffRankBG->Lock(0, 0, (void**)&pVtx, 0);

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
	pVtx[0].tex = D3DXVECTOR2(0.0f,0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f,0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f,1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f,1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffRankBG->Unlock();
}