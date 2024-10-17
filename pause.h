//------------------------------------------
//
//         �|�[�Y����
//       Author:Sudou Akito
//
//------------------------------------------
#ifndef _PAUSE_H_
#define _PAUSE_H_

#include"main.h"

//�|�[�Y���j���[
typedef enum
{
	PAUSE_MENU_CONTINUE = 0,  //�Q�[���ɖ߂�
	PAUSE_MENU_OPERATION,     //����m�F
	PAUSE_MENU_RETRY,         //�Q�[����蒼��
	PAUSE_MENU_QUIT,          //�^�C�g���ɖ߂�
	PAUSE_MENU_MAX
}PAUSE_MENU;

//�v���g�^�C�v�錾
void InitPause(void);
void UninitPause(void);
void UpdatePause(void);
void DrawPause(void);
void SelectPause(int nNumSelect);

//�}�N����`
#define MAX_UI (5)
#define OFFSET_VALUE (120.0f)

#endif