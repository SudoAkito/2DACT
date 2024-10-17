//------------------------------------------
//
//         パーティクル処理
//       Author:Sudou Akito
//
//------------------------------------------

#include"partycle.h"
#include "effect.h"

//マクロ
#define MAX_PARTYCLE (128)  //パーティクル最大数

//パーティクル構造体
typedef struct
{
	D3DXVECTOR3 pos;   //発生位置
	int nLife;         //寿命
	bool bUse;         //使用の有無
}Partycle;

//グローバル変数
Partycle g_apartycle[MAX_PARTYCLE];  //パーティクルの情報

//------------------------------------------
//パーティクルの初期化処理
//------------------------------------------
void InitPartycle(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//初期化
	for (int nCntPar = 0; nCntPar < MAX_PARTYCLE; nCntPar++)
	{
		D3DXVECTOR3 pos = D3DXVECTOR3(500.0f, 200.0f, 0.0f);
		int nLife = 10;
		bool bUse = false;
	}
	
}

//------------------------------------------
//パーティクル終了処理
//------------------------------------------
void UninitPartycle(void)
{
	//書くことなし
}


//------------------------------------------
//パーティクル更新処理
//------------------------------------------
void UpdatePartycle(void)
{
	int nCntpar;
	int nCntApper;
	D3DXVECTOR3 pos;   //位置
	D3DXVECTOR3 move;  //移動量
	D3DXCOLOR col;     //色
	float fPullRadius; //頂点座標設定 
	float fPullMove;   //移動量減衰
	float falfa;       //α値の設定
	float fData;       //α値の減衰
	float fRadius;     //頂点座標設定 
	int nLife;         //体力


	for (nCntpar = 0; nCntpar < MAX_PARTYCLE; nCntpar++)
	{

		if (g_apartycle[nCntpar].bUse == true)
		{
			//パーティクル生成
			for (nCntApper = 0; nCntApper < 20; nCntApper++)
			{
				float fAngle = (float)(rand() % 629 - 314) / 100.0f;
				float fspeed = (float)(rand() % 10) + 1;

				//位置の設定
				pos = g_apartycle[nCntpar].pos;

				//移動量の設定
				move.x = sinf(fAngle) * fspeed;
				move.y = cosf(fAngle) * fspeed;

				//移動量減衰
				fPullMove = 0.01f;

				//色の設定
				col = D3DXCOLOR(0.6f, 0.3f, 0.6f, 0.5f);

				//半径の設定
				fRadius = 20.0f;

				//半径の減少係数
				fPullRadius = 0.01f;

				//α値の初期設定
				falfa = 0.5f;

				//α値の減衰値
				fData = 0.02f;

				//体力
				nLife = 60;

				SetEffect(pos
					,D3DXVECTOR3(move.x,move.y,move.z)
					,col
					,fRadius
					,falfa
					,fData
					,fPullRadius
					,fPullMove
					,nLife);
			}
			g_apartycle[nCntpar].bUse = false;
		}
	}
}

//------------------------------------------
//パーティクル描画処理
//------------------------------------------
void DrawPartycle(void)
{
	//書くことなし
}

//------------------------------------------
//パーティクル設定処理
//------------------------------------------
void SetPartycle(D3DXVECTOR3 pos)
{
	int nCntpar;

	for (nCntpar = 0; nCntpar < MAX_PARTYCLE; nCntpar++) 
	{
		if (g_apartycle[nCntpar].bUse == false)
		{
			g_apartycle[nCntpar].pos = pos;
			g_apartycle[nCntpar].nLife = 60;
			g_apartycle[nCntpar].bUse = true;  //使用してる状態にする

			break;
		}
	}
}
