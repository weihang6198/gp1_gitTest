#ifndef PLAYER_H
#define PLAYER_H

//******************************************************************************
//
//
//      player.h
//
//
//******************************************************************************

// �v���C���[�̉摜�̒萔
#define PLAYER_TEX_W            (128.0f)    // �v���C���[�̉摜1�̕�
#define PLAYER_TEX_H            (128.0f)    // �v���C���[�̉摜1�̍���
#define PLAYER_PIVOT_X          (64.0f)     // �v���C���[�̉������̒��S
#define PLAYER_PIVOT_Y          (128.0f)    // �v���C���[�̏c�����̉��[

// �v���C���[�̉����E�����̒萔
#define PLAYER_ACCEL_X          (0.3f)      // �v���C���[�̉������̉����x�i�����p�j
#define PLAYER_DECEL_X          (0.4f)      // �v���C���[�̉������̉����x�i�����p�j
#define PLAYER_SPEED_X_MAX      (8.0f)      // �v���C���[�̉������̑��x�̍ő�l

//�v���C���[�̈ړ����E�ʒu�̒萔
#define PLAYER_LIMIT_L          (PLAYER_TEX_W * 0.5f)
#define PLAYER_LIMIT_R          (SCREEN_W - PLAYER_TEX_W * 0.5f)

#define PLAYER_JUMP_COUNT       (3)
#define PLAYER_JUMP_POWER_HIGH  (22.0f)
#define PLAYER_JUMP_POWER_LOW   (18.0f)

#define GRAVITY                 (1.0f)      // �d�͂̒萔
#define GROUND_Y                (640.0f)    // �n�ʂ̍����̒萔

//------< �s�� >----------------------------------------------------------------

// �v���C���[�̊e�s����\���萔
enum PLAYER_ACT
{
    IDLE_INIT = 0,      //  0 �ҋ@_�����ݒ�
    IDLE,               //  1 �ҋ@
    WALK_INIT,          //  2 ����_�����ݒ�
    WALK,               //  3 ����
    RUN_INIT,           //  4 ����_�����ݒ�
    RUN,                //  5 ����
    JUMP_START_INIT,    //  6 �W�����v�n��_�����ݒ�
    JUMP_START,         //  7 �W�����v�n��
    JUMP_KEEP_INIT,     //  8 �W�����v��_�����ݒ�
    JUMP_KEEP,          //  9 �W�����v��
    JUMP_END_INIT,      // 10 �W�����v���n_�����ݒ�
    JUMP_END,           // 11 �W�����v���n
};

//------< �ϐ� >----------------------------------------------------------------
extern OBJ2D player;

//------< �֐� >----------------------------------------------------------------
void player_init();
void player_deinit();
void player_update();
void player_render();

void player_act();      // ��ԑJ�ڂ��s��
void player_moveX();
void player_moveY();

void player_animeInit(int);
bool player_anime(int, int, bool);
bool player_jump();

#endif//PLAYER_H