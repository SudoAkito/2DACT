//------------------------------------------
//
//			   敵処理
//         Author:Sudou Akito
//
//------------------------------------------

//#include"bullet.h"
#include"enemy.h"
#include"explosion.h"
#include "score.h"
#include "player.h"
#include"game.h"
#include"partycle.h"

//マクロ定義
#define NUM_ENEMY (2)                 //敵の種類

//グローバル変数
LPDIRECT3DTEXTURE9 g_apTextureEnemy[ENEMYTYPE_MAX] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;
Enemy g_aEnemy[MAX_ENEMY];      //敵の情報
int g_nNumEnemy;            //敵の総数

//------------------------------------------
//敵の初期化処理
//------------------------------------------
void InitEnemy(void)
{

	int nCntEN{};

	LPDIRECT3DDEVICE9 pDevice;   //デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();


	for (int n = 0; n < ENEMYTYPE_MAX; n++)
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			ENEMYTEX[n],
			&g_apTextureEnemy[n]);
	}

	//敵の初期化
	for (nCntEN = 0; nCntEN <MAX_ENEMY ; nCntEN++)
	{
		g_aEnemy[nCntEN].pos= D3DXVECTOR3(0.0f,0.0f,0.0f);
		g_aEnemy[nCntEN].move= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEN].rot= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEN].state = {};
		g_aEnemy[nCntEN].nCounterState=0;
		g_aEnemy[nCntEN].nLife=0;
		g_aEnemy[nCntEN].nType=0;
		g_aEnemy[nCntEN].bUse=false;
		g_aEnemy[nCntEN].fLength=0;
		g_aEnemy[nCntEN].fAngle = 0;
	}
	g_nNumEnemy = 0;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4*MAX_ENEMY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEnemy,
		NULL);

	VERTEX_2D* pVtx;        //頂点情報のポインタ

//頂点バッファをロックして頂点情報へのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEN = 0; nCntEN < MAX_ENEMY; nCntEN++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

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

		pVtx += 4;
	}
	
	//頂点バッファをアンロックする
	g_pVtxBuffEnemy->Unlock();
}

//------------------------------------------
//敵の終了処理
//------------------------------------------
void UninitEnemy(void)
{
	int nCntEN;

	//テクスチャの破棄
	for (nCntEN = 0; nCntEN < ENEMYTYPE_MAX; nCntEN++)
	{
		if (g_apTextureEnemy[nCntEN] != NULL)
		{
			g_apTextureEnemy[nCntEN]->Release();
			g_apTextureEnemy[nCntEN] = NULL;
		}
	}
	//頂点バッファの破棄
	if (g_pVtxBuffEnemy != NULL)
	{
		g_pVtxBuffEnemy->Release();
		g_pVtxBuffEnemy = NULL;
	}
}

//------------------------------------------
// 敵の更新処理
//------------------------------------------
void UpdateEnemy(void)
{
	int nCntEN{};

	VERTEX_2D* pVtx;        //頂点情報のポインタ

	// プレイヤーの位置を取得する
	D3DXVECTOR3 playerPos = GetPlayer()->pos;

	//頂点バッファをロックして頂点情報へのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	
	for (nCntEN = 0; nCntEN < MAX_ENEMY; nCntEN++)
	{
		float fspeed = (float)(rand() % 7) + 0.5f;

		if (g_aEnemy[nCntEN].bUse == true)
		{

			// プレイヤー (ターゲット) との差を求める
			D3DXVECTOR3 diff = playerPos - g_aEnemy[nCntEN].pos;

			// 角度を求める
			float fAngle = atan2f(diff.x, diff.y);

			// 移動量を更新する (増加)
			/*g_aEnemy[nCntEN].move.x = sinf(fAngle) * fspeed;
			g_aEnemy[nCntEN].move.y = cosf(fAngle) * fspeed;*/

			//位置を更新
			g_aEnemy[nCntEN].pos.x += g_aEnemy[nCntEN].move.x;
			g_aEnemy[nCntEN].pos.y += g_aEnemy[nCntEN].move.y;

			pVtx[0].pos.x = g_aEnemy->pos.x - (MAX_X / 2.0f);
			pVtx[0].pos.y = g_aEnemy->pos.y - MAX_Y;
			pVtx[0].pos.z = 0.0f;

			pVtx[1].pos.x = g_aEnemy->pos.x + (MAX_X / 2.0f);
			pVtx[1].pos.y = g_aEnemy->pos.y - MAX_Y;
			pVtx[1].pos.z = 0.0f;

			pVtx[2].pos.x = g_aEnemy->pos.x - (MAX_X / 2.0f);
			pVtx[2].pos.y = g_aEnemy->pos.y;
			pVtx[2].pos.z = 0.0f;

			pVtx[3].pos.x = g_aEnemy->pos.x + (MAX_X / 2.0f);
			pVtx[3].pos.y = g_aEnemy->pos.y;
			pVtx[3].pos.z = 0.0f;

			switch (g_aEnemy[nCntEN].state)
			{
			case ENEMYSTATE_NORMAL:
				/*g_aEnemy[nCntEN].nunti++;
				if (g_aEnemy[nCntEN].nunti >= 30)
				{
					SetBullet(g_aEnemy[nCntEN].pos, D3DXVECTOR3(sinf(g_aEnemy[nCntEN].rot.z + D3DX_PI) * MAX_SPEED, cosf(g_aEnemy[nCntEN].rot.z + D3DX_PI) * MAX_SPEED, 0.0f), g_aEnemy[nCntEN].rot, g_aEnemy[nCntEN].fLength, 150, BULLETTYPE_ENEMY);
					g_aEnemy[nCntEN].nunti = 0;
				}
				break;*/

			case ENEMYSTATE_DAMAGE:

				g_aEnemy[nCntEN].nCounterState--;
				if (g_aEnemy[nCntEN].nCounterState <= 0)
				{
					g_aEnemy[nCntEN].state = ENEMYSTATE_NORMAL;
					//頂点カラーの設定
					pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

				}
				break;
			}
		}
		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffEnemy->Unlock();
}

//------------------------------------------
// 敵の描画処理
//------------------------------------------
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;   //デバイスへのポインタ
	int nCntEN;
	//デバイスの取得
	pDevice = GetDevice();

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffEnemy, 0, sizeof(VERTEX_2D));

	for (nCntEN = 0; nCntEN < MAX_ENEMY; nCntEN++)
	{
		if (g_aEnemy[nCntEN].bUse == true)
		{
			int nType = g_aEnemy[nCntEN].nType;

			//テクスチャの設定

			pDevice->SetTexture(0, g_apTextureEnemy[nType]);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,4 * nCntEN,2);//プリミティブの種類,プリミティブの数
		}
	}

#ifdef _DEBUG

	// 敵の表示
	DrawEnemyCnt(g_nNumEnemy);

#endif // _DEBUG

}

//------------------------------------------
// 敵のセット処理
//------------------------------------------
void SetEnemy(D3DXVECTOR3 pos, int nType)
{
	int nCntEN;
	VERTEX_2D* pVtx;        //頂点情報のポインタ

	//頂点バッファをロックして頂点情報へのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEN = 0; nCntEN < MAX_ENEMY; nCntEN++)
	{
		if(g_aEnemy[nCntEN].bUse == false)
		{//敵が使用されていない

			//敵の情報の設定
			g_aEnemy[nCntEN].pos= pos;
			g_aEnemy[nCntEN].state = ENEMYSTATE_NORMAL;
			g_aEnemy[nCntEN].nCounterState = 0;//状態管理カウンター
			g_aEnemy[nCntEN].nLife = 5;        //体力
			g_aEnemy[nCntEN].nType = nType;
		
			//頂点座標の設定
			g_aEnemy[nCntEN].pos.x += g_aEnemy[nCntEN].move.x;
			g_aEnemy[nCntEN].pos.y += g_aEnemy[nCntEN].move.y;

			pVtx[0].pos.x = g_aEnemy->pos.x - (MAX_X / 2.0f);
			pVtx[0].pos.y = g_aEnemy->pos.y - MAX_Y;
			pVtx[0].pos.z = 0.0f;

			pVtx[1].pos.x = g_aEnemy->pos.x + (MAX_X / 2.0f);
			pVtx[1].pos.y = g_aEnemy->pos.y - MAX_Y;
			pVtx[1].pos.z = 0.0f;

			pVtx[2].pos.x = g_aEnemy->pos.x - (MAX_X / 2.0f);
			pVtx[2].pos.y = g_aEnemy->pos.y;
			pVtx[2].pos.z = 0.0f;

			pVtx[3].pos.x = g_aEnemy->pos.x + (MAX_X / 2.0f);
			pVtx[3].pos.y = g_aEnemy->pos.y;
			pVtx[3].pos.z = 0.0f;
			g_aEnemy[nCntEN].bUse = true;
			g_nNumEnemy++;
			break;
		}
		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffEnemy->Unlock();
}
//------------------------------------------
//敵の情報
//------------------------------------------
Enemy* GetEnemy(void)
{
	return &g_aEnemy[0];
}

//------------------------------------------
// 敵の当たり判定の後処理
//------------------------------------------
void HitEnemy(int nCntEn, int nDmg)
{
	VERTEX_2D* pVtx;        //頂点情報のポインタ

	g_aEnemy[nCntEn].nLife -= nDmg;

	//頂点バッファをロックして頂点情報へのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	if (g_aEnemy[nCntEn].nLife<=0||g_aEnemy[nCntEn].nType == 0)
	{
		SetExplosion(g_aEnemy[nCntEn].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), g_aEnemy[nCntEn].rot, g_aEnemy[nCntEn].fLength);
		g_aEnemy[nCntEn].bUse = false;
		SetPartycle(g_aEnemy[nCntEn].pos);
  		AddScore(250);
   		g_nNumEnemy--;                //敵の総数カウントダウン
	}
	else if (g_aEnemy[nCntEn].nLife <= 0 || g_aEnemy[nCntEn].nType == 1)
	{
		SetExplosion(g_aEnemy[nCntEn].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), g_aEnemy[nCntEn].rot, g_aEnemy[nCntEn].fLength);
		g_aEnemy[nCntEn].bUse = false;
		SetPartycle(g_aEnemy[nCntEn].pos);
		AddScore(500);
		g_nNumEnemy--;                //敵の総数カウントダウン
	}
	else if (g_aEnemy[nCntEn].nLife <= 0 || g_aEnemy[nCntEn].nType == 2)
	{
		SetExplosion(g_aEnemy[nCntEn].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), g_aEnemy[nCntEn].rot, g_aEnemy[nCntEn].fLength);
		g_aEnemy[nCntEn].bUse = false;
		SetPartycle(g_aEnemy[nCntEn].pos);
		AddScore(1000);
		g_nNumEnemy--;                //敵の総数カウントダウン
	}
	else
	{
		g_aEnemy[nCntEn].state=ENEMYSTATE_DAMAGE;
 		g_aEnemy[nCntEn].nCounterState = 5;

		pVtx += 4 * nCntEn;

		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0 ,255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 0 ,0, 255);
	}
	//頂点バッファをアンロックする
	g_pVtxBuffEnemy->Unlock();
}

int GetNumEnemy()
{
	return g_nNumEnemy;
}

