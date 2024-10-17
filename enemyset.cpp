//------------------------------------------
//
//          敵処理
//       Author:Sudou Akito
//
//------------------------------------------

#include "enemyset.h"
#include<stdio.h>
#include<string.h>
#include"enemy.h"


#define MAX_WORD (4096)

//アイテムセット
typedef struct
{
	D3DXVECTOR3 pos;
	int nType;
	bool bUse;
}LoadINFO;

//グロ
LoadINFO g_aInfo[MAX_ENEMY];
int g_nCountenemy;
int g_EnemySet;
bool g_bFinSet;

void Initenemyset(void)
{
	for (int n = 0; n < MAX_ENEMY; n++)
	{
		g_aInfo[n].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aInfo[n].nType = 0;
		g_aInfo[n].bUse = false;
	}

	g_nCountenemy = 0;
	g_EnemySet = 0;
	g_bFinSet = false;
}

void loadenemy(void)
{
	FILE* pFile;
	D3DXVECTOR3 pos;
	int nType = 0;
	g_nCountenemy = GetNumEnemy();

	switch (g_EnemySet)
	{
	case 0:
		pFile = fopen(Enemypas, "r");
		break;

	default:
		pFile = NULL;

		g_bFinSet = true;
		break;
	}

	if (pFile != NULL)
	{
		while(1)
		{
			char aStr[MAX_WORD];

			fscanf(pFile, "%s", &aStr[0]);

			if(strcmp(aStr,"ENEMYSET")==0)
			{
				while (1)
				{
					fscanf(pFile, "%s", &aStr[0]);

					if (strcmp(aStr, "POS") == 0)
					{
						fscanf(pFile, "%f", &pos.x);
						fscanf(pFile, "%f", &pos.y);
						fscanf(pFile, "%f", &pos.z);
					}
					else if (strcmp(aStr, "ENEMYTYPE") == 0)
					{
						fscanf(pFile, "%d", &nType);
					}
					else if (strcmp(aStr, "END_ENEMYSET") == 0)
					{
						SetEnemy(pos,nType);
						break;
					}
				}
			}
			if(strcmp(aStr,"END_SCRIPT")==0)
			{
				break;
			}
		}
		fclose(pFile);
		g_EnemySet++;
	}
	else
	{
		return;
	}
}

int GetEnemySet(void)
{
	return g_EnemySet;
}

bool GetFinSet()
{
	return g_bFinSet;
}


