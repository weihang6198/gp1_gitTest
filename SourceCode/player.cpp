#include "all.h"

int     player_state;

OBJ2D   player;

Sprite* sprPlayer;

//--------------------------------------
//  プレイヤーの初期設定
//--------------------------------------
void player_init()
{
    player_state = 0;
}

//--------------------------------------
//  プレイヤーの終了処理
//--------------------------------------
void player_deinit()
{
    safe_delete(sprPlayer);
}

//--------------------------------------
//  プレイヤーの更新処理
//--------------------------------------
void player_update()
{
    switch (player_state)
    {
    case 0:
        //////// 初期設定 ////////

        sprPlayer = sprite_load(L"./Data/Images/stickman.png");

        ++player_state;
        /*fallthrough*/

    case 1:
        //////// パラメータの設定 ////////

        player              = {};
        player.timer        = 0;
        player.pos          = { SCREEN_W * 0.5f, SCREEN_H * 0.5f };
        player.scale        = { 1.0f, 1.0f };
        player.texPos       = { 0, 0 };
        player.texSize      = { PLAYER_TEX_W, PLAYER_TEX_H };
        player.pivot        = { PLAYER_PIVOT_X, PLAYER_PIVOT_Y };
        player.color        = { 1.000f, 0.6863f, 0.2980f, 1.0f };
        player.jumpCount    = 0;
        player.act          = PLAYER_ACT::JUMP_KEEP_INIT;

        player.radius       = 24;
        player.offset       = { 0, -64 };

        ++player_state;
        /*fallthrough*/

    case 2:
        {
        //////// 通常時 ////////

        // 現時点でのy方向の速度
        const float speedY = player.speed.y;

        // 行動の遷移
        player_act();

        // 位置に速度を足す
        player.pos += player.speed;

        // 位置・速度・行動の情報を表示
        debug::setString("pos.x:%f pos.y:%f",   player.pos.x, player.pos.y);
        debug::setString("speed:%f",            player.speed.x);
        debug::setString("");
        //debug::setString("player.act:%d",       player.act);
        //debug::setString("sizeof(OBJ2D):%d", sizeof(OBJ2D));

        player.onGround = false;

        // 地面とのあたり判定（仮）
        if (player.pos.y > GROUND_Y)
        {
            if (speedY > PLAYER_JUMP_POWER_HIGH)//
            {
                player.jumpEnd  = true;
            }

            player.pos.y        = GROUND_Y;
            player.speed.y      = 0.0f;
            player.onGround     = true;

            player.jumpCount    = PLAYER_JUMP_COUNT;
        }

        // エリア切り替え
        if (player.pos.x > SCREEN_W)
        {
            if (player.area < AREA_MAX - 1)
            {
                ++player.area;
                player.pos.x    = 0;
            }
            else
            {
                player.pos.x    = (float)SCREEN_W;
                player.speed.x  = 0.0f;
            }
        }
        if (player.pos.x < 0)
        {
            if (player.area > 0)
            {
                --player.area;
                player.pos.x = (float)SCREEN_W;
            }
            else
            {
                player.pos.x = 0;
                player.speed.x = 0;
            }
        }
        debug::setString("player.area:%d", player.area);




        }
        break;
        OutputDebugStringA("test for github");
    }
}

//--------------------------------------
//  プレイヤーの描画
//--------------------------------------
void player_render()
{
    sprite_render(
        sprPlayer,
        player.pos.x,       player.pos.y,
        player.scale.x,     player.scale.y,
        player.texPos.x,    player.texPos.y,
        player.texSize.x,   player.texSize.y,
        player.pivot.x,     player.pivot.y, 
        ToRadian(0),
        player.color.x,     player.color.y, 
        player.color.z,     player.color.w
    );

    // プレイヤーのあたり領域の表示
    primitive::circle(
        player.pos + player.offset,
        player.radius, { 1, 1 },
        ToRadian(0), {1, 0, 0, 0.2f}
    );

}

//--------------------------------------
//  プレイヤーのアニメ初期設定
//--------------------------------------
void player_animeInit(int animeNo)
{
    player.anime = player.animeTimer = 0;
    player.texPos = { 0, animeNo * player.texSize.y };
}

//--------------------------------------
//  プレイヤーのアニメ遷移
//--------------------------------------
bool player_anime(int total, int frame, bool loop)
{
    player.anime = player.animeTimer / frame;
    if (loop)
    {
        if (player.anime >= total)
        {
            player.anime = 0;
            player.animeTimer = 0;
        }
    }
    else
    {
        if (player.anime >= total)
        {
            player.anime = total - 1;
            return true;    // アニメの終端に達した
        }
    }
    player.texPos.x = player.anime * player.texSize.x;
    ++player.animeTimer;

    return false;           // アニメの終端ではない
}

//--------------------------------------
//  プレイヤーのジャンプ
//--------------------------------------
bool player_jump()
{
    if (TRG(0) & PAD_TRG1 && player.jumpCount > 0 && player.speed.y > 0)
    {
        sound::play(XWB_STAGE1, XWB_STAGE1_JUMP);
        --player.jumpCount;

        player.jumpEnd = false;
        return true;
    }

    return false;
}

//--------------------------------------
//  プレイヤーの行動の遷移
//--------------------------------------
void player_act()
{
    switch (player.act)
    {
    //--------------------------------
    // 待機
    //--------------------------------
    case PLAYER_ACT::IDLE_INIT:

        /*-------- アニメの初期設定 --------*/
        player_animeInit(0);

        ++player.act;
        /*fallthrough*/

    case PLAYER_ACT::IDLE:

        /*-------- この行動での動作 --------*/
        player_moveY();
        player_moveX();

        /*-------     アニメ処理     -------*/
        // なし
        player_anime(1, 1, false);

        /*--------    行動の遷移    --------*/
        if (player_jump())
        {
            player.act = PLAYER_ACT::JUMP_START_INIT;
            break;
        }

        // 歩きへの遷移
        if (fabsf(player.speed.x) >= 0.125f)
        {
            player.act = PLAYER_ACT::WALK_INIT;
            break;
        }

        break;

    //--------------------------------
    // 歩き
    //--------------------------------
    case PLAYER_ACT::WALK_INIT:

        /*-------- アニメの初期設定 --------*/
        player_animeInit(1);

        ++player.act;
        /*fallthrough*/

    case PLAYER_ACT::WALK:

        /*-------- この行動での動作 --------*/
        player_moveY();
        player_moveX();

        /*-------     アニメ処理     -------*/
        player_anime(8, 4, true);

        /*--------    行動の遷移    --------*/
        if (player_jump())
        {
            player.act = PLAYER_ACT::JUMP_START_INIT;
            break;
        }

        {
            const float speedX = fabsf(player.speed.x);
            if (speedX < 0.125f)     // アイドル状態へ
            {
                player.act = PLAYER_ACT::IDLE_INIT;
                break;
            }
            if (speedX >= 7.5f)      // 走り状態へ
            {
                player.act = PLAYER_ACT::RUN_INIT;
                break;
            }
        }

        break;

    //--------------------------------
    // 走り
    //--------------------------------
    case PLAYER_ACT::RUN_INIT:

        /*-------- アニメの初期設定 --------*/
        player_animeInit(2);

        ++player.act;
        /*fallthrough*/

    case PLAYER_ACT::RUN:

        /*-------- この行動での動作 --------*/
        player_moveY();
        player_moveX();

        /*-------     アニメ処理     -------*/
        player_anime(8, 4, true);

        /*--------    行動の遷移    --------*/
        if (player_jump())
        {
            player.act = PLAYER_ACT::JUMP_START_INIT;
            break;
        }

        if (fabsf(player.speed.x) < 7.5f)      // 歩き状態へ
        {
            player.act = PLAYER_ACT::WALK_INIT;
            break;
        }

        break;

    //--------------------------------
    // ジャンプ始め
    //--------------------------------
    case PLAYER_ACT::JUMP_START_INIT:

        /*-------- アニメの初期設定 --------*/
        player_animeInit(3);

        ++player.act;
        /*fallthrough*/

    case PLAYER_ACT::JUMP_START:

        /*-------- この行動での動作 --------*/
        player_moveY();
        player_moveX();

        // 弱ジャンプ
        if (TRG_RELEASE(0) & PAD_TRG1)
        {
            player.act = PLAYER_ACT::JUMP_KEEP_INIT;
            player.speed.y = -PLAYER_JUMP_POWER_LOW;

            --player.jumpCount;
            break;
        }

        /*-------     アニメ処理     -------*/
        if (player_anime(4, 2, false))
        {
            // 行動の遷移
            player.act = PLAYER_ACT::JUMP_KEEP_INIT;
            player.speed.y = -PLAYER_JUMP_POWER_HIGH;

            --player.jumpCount;
            break;
        }

        /*--------    行動の遷移    --------*/

        break;

    //--------------------------------
    // ジャンプ中
    //--------------------------------
    case PLAYER_ACT::JUMP_KEEP_INIT:

        /*-------- アニメの初期設定 --------*/
        player_animeInit(4);

        ++player.act;
        /*fallthrough*/

    case PLAYER_ACT::JUMP_KEEP:

        /*-------- この行動での動作 --------*/
        player_moveY();
        player_moveX();

        /*-------     アニメ処理     -------*/
        player_anime(7, 3, false);

        /*--------    行動の遷移    --------*/

        if (player_jump())
        {
            player.speed.y = -PLAYER_JUMP_POWER_LOW;
            break;
        }

        if (player.onGround)
        {
            if (player.jumpEnd)
                player.act = PLAYER_ACT::JUMP_END_INIT;
            else
                player.act = PLAYER_ACT::IDLE_INIT;
            break;
        }

        break;

    //--------------------------------
    // ジャンプ着地
    //--------------------------------
    case PLAYER_ACT::JUMP_END_INIT:
        player_animeInit(5);

        // 着地時の横方向の速度を0に
        player.speed.x = 0.0f;

        ++player.act;
        /*fallthrough*/

    case PLAYER_ACT::JUMP_END:

        /*-------- この行動での動作 --------*/
        // なし

        /*-------     アニメ処理     -------*/
        if (player_anime(8, 5, false))
        {
            player.act = PLAYER_ACT::IDLE_INIT;
            break;
        }

        /*--------    行動の遷移    --------*/
        // なし

        break;
    }
}

//--------------------------------------
//  プレイヤーのY方向の移動
//--------------------------------------
void player_moveY()
{
    // Y方向の移動
    player.speed.y += GRAVITY;
}

//--------------------------------------
//  プレイヤーのX方向の移動
//--------------------------------------
void player_moveX()
{

    if (STATE(0) & PAD_RIGHT && !(STATE(0) & PAD_LEFT))
    {
        player.speed.x += PLAYER_ACCEL_X;
        player.scale.x = 1.0f;
    }
    else if (STATE(0) & PAD_LEFT && !(STATE(0) & PAD_RIGHT))
    {
        player.speed.x += -PLAYER_ACCEL_X;
        player.scale.x = -1.0f;
    }
    else
    {
        if (player.speed.x > 0)
        {
            player.speed.x += -PLAYER_DECEL_X;
            if (player.speed.x < 0)
                player.speed.x = 0.0f;
        }
        if (player.speed.x < 0)
        {
            player.speed.x += PLAYER_DECEL_X;
            if (player.speed.x > 0)
                player.speed.x = 0.0f;
        }
    }
    if (player.speed.x >  PLAYER_SPEED_X_MAX)
        player.speed.x =  PLAYER_SPEED_X_MAX;
    if (player.speed.x < -PLAYER_SPEED_X_MAX)
        player.speed.x = -PLAYER_SPEED_X_MAX;
}
