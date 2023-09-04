#ifndef PLAYER_H
#define PLAYER_H

//******************************************************************************
//
//
//      player.h
//
//
//******************************************************************************

// プレイヤーの画像の定数
#define PLAYER_TEX_W            (128.0f)    // プレイヤーの画像1つの幅
#define PLAYER_TEX_H            (128.0f)    // プレイヤーの画像1つの高さ
#define PLAYER_PIVOT_X          (64.0f)     // プレイヤーの横方向の中心
#define PLAYER_PIVOT_Y          (128.0f)    // プレイヤーの縦方向の下端

// プレイヤーの加速・減速の定数
#define PLAYER_ACCEL_X          (0.3f)      // プレイヤーの横方向の加速度（加速用）
#define PLAYER_DECEL_X          (0.4f)      // プレイヤーの横方向の加速度（減速用）
#define PLAYER_SPEED_X_MAX      (8.0f)      // プレイヤーの横方向の速度の最大値

//プレイヤーの移動限界位置の定数
#define PLAYER_LIMIT_L          (PLAYER_TEX_W * 0.5f)
#define PLAYER_LIMIT_R          (SCREEN_W - PLAYER_TEX_W * 0.5f)

#define PLAYER_JUMP_COUNT       (3)
#define PLAYER_JUMP_POWER_HIGH  (22.0f)
#define PLAYER_JUMP_POWER_LOW   (18.0f)

#define GRAVITY                 (1.0f)      // 重力の定数
#define GROUND_Y                (640.0f)    // 地面の高さの定数

//------< 行動 >----------------------------------------------------------------

// プレイヤーの各行動を表す定数
enum PLAYER_ACT
{
    IDLE_INIT = 0,      //  0 待機_初期設定
    IDLE,               //  1 待機
    WALK_INIT,          //  2 歩き_初期設定
    WALK,               //  3 歩き
    RUN_INIT,           //  4 走り_初期設定
    RUN,                //  5 走り
    JUMP_START_INIT,    //  6 ジャンプ始め_初期設定
    JUMP_START,         //  7 ジャンプ始め
    JUMP_KEEP_INIT,     //  8 ジャンプ中_初期設定
    JUMP_KEEP,          //  9 ジャンプ中
    JUMP_END_INIT,      // 10 ジャンプ着地_初期設定
    JUMP_END,           // 11 ジャンプ着地
};

//------< 変数 >----------------------------------------------------------------
extern OBJ2D player;

//------< 関数 >----------------------------------------------------------------
void player_init();
void player_deinit();
void player_update();
void player_render();

void player_act();      // 状態遷移を行う
void player_moveX();
void player_moveY();

void player_animeInit(int);
bool player_anime(int, int, bool);
bool player_jump();

#endif//PLAYER_H