#include "all.h"

int     player_state;

OBJ2D   player;

Sprite* sprPlayer;

//--------------------------------------
//  �v���C���[�̏����ݒ�
//--------------------------------------
void player_init()
{
    player_state = 0;
}

//--------------------------------------
//  �v���C���[�̏I������
//--------------------------------------
void player_deinit()
{
    safe_delete(sprPlayer);
}

//--------------------------------------
//  �v���C���[�̍X�V����
//--------------------------------------
void player_update()
{
    switch (player_state)
    {
    case 0:
        //////// �����ݒ� ////////

        sprPlayer = sprite_load(L"./Data/Images/stickman.png");

        ++player_state;
        /*fallthrough*/

    case 1:
        //////// �p�����[�^�̐ݒ� ////////

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
        //////// �ʏ펞 ////////

        // �����_�ł�y�����̑��x
        const float speedY = player.speed.y;

        // �s���̑J��
        player_act();

        // �ʒu�ɑ��x�𑫂�
        player.pos += player.speed;

        // �ʒu�E���x�E�s���̏���\��
        debug::setString("pos.x:%f pos.y:%f",   player.pos.x, player.pos.y);
        debug::setString("speed:%f",            player.speed.x);
        debug::setString("");
        //debug::setString("player.act:%d",       player.act);
        //debug::setString("sizeof(OBJ2D):%d", sizeof(OBJ2D));

        player.onGround = false;

        // �n�ʂƂ̂����蔻��i���j
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

        // �G���A�؂�ւ�
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
//  �v���C���[�̕`��
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

    // �v���C���[�̂�����̈�̕\��
    primitive::circle(
        player.pos + player.offset,
        player.radius, { 1, 1 },
        ToRadian(0), {1, 0, 0, 0.2f}
    );

}

//--------------------------------------
//  �v���C���[�̃A�j�������ݒ�
//--------------------------------------
void player_animeInit(int animeNo)
{
    player.anime = player.animeTimer = 0;
    player.texPos = { 0, animeNo * player.texSize.y };
}

//--------------------------------------
//  �v���C���[�̃A�j���J��
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
            return true;    // �A�j���̏I�[�ɒB����
        }
    }
    player.texPos.x = player.anime * player.texSize.x;
    ++player.animeTimer;

    return false;           // �A�j���̏I�[�ł͂Ȃ�
}

//--------------------------------------
//  �v���C���[�̃W�����v
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
//  �v���C���[�̍s���̑J��
//--------------------------------------
void player_act()
{
    switch (player.act)
    {
    //--------------------------------
    // �ҋ@
    //--------------------------------
    case PLAYER_ACT::IDLE_INIT:

        /*-------- �A�j���̏����ݒ� --------*/
        player_animeInit(0);

        ++player.act;
        /*fallthrough*/

    case PLAYER_ACT::IDLE:

        /*-------- ���̍s���ł̓��� --------*/
        player_moveY();
        player_moveX();

        /*-------     �A�j������     -------*/
        // �Ȃ�
        player_anime(1, 1, false);

        /*--------    �s���̑J��    --------*/
        if (player_jump())
        {
            player.act = PLAYER_ACT::JUMP_START_INIT;
            break;
        }

        // �����ւ̑J��
        if (fabsf(player.speed.x) >= 0.125f)
        {
            player.act = PLAYER_ACT::WALK_INIT;
            break;
        }

        break;

    //--------------------------------
    // ����
    //--------------------------------
    case PLAYER_ACT::WALK_INIT:

        /*-------- �A�j���̏����ݒ� --------*/
        player_animeInit(1);

        ++player.act;
        /*fallthrough*/

    case PLAYER_ACT::WALK:

        /*-------- ���̍s���ł̓��� --------*/
        player_moveY();
        player_moveX();

        /*-------     �A�j������     -------*/
        player_anime(8, 4, true);

        /*--------    �s���̑J��    --------*/
        if (player_jump())
        {
            player.act = PLAYER_ACT::JUMP_START_INIT;
            break;
        }

        {
            const float speedX = fabsf(player.speed.x);
            if (speedX < 0.125f)     // �A�C�h����Ԃ�
            {
                player.act = PLAYER_ACT::IDLE_INIT;
                break;
            }
            if (speedX >= 7.5f)      // �����Ԃ�
            {
                player.act = PLAYER_ACT::RUN_INIT;
                break;
            }
        }

        break;

    //--------------------------------
    // ����
    //--------------------------------
    case PLAYER_ACT::RUN_INIT:

        /*-------- �A�j���̏����ݒ� --------*/
        player_animeInit(2);

        ++player.act;
        /*fallthrough*/

    case PLAYER_ACT::RUN:

        /*-------- ���̍s���ł̓��� --------*/
        player_moveY();
        player_moveX();

        /*-------     �A�j������     -------*/
        player_anime(8, 4, true);

        /*--------    �s���̑J��    --------*/
        if (player_jump())
        {
            player.act = PLAYER_ACT::JUMP_START_INIT;
            break;
        }

        if (fabsf(player.speed.x) < 7.5f)      // ������Ԃ�
        {
            player.act = PLAYER_ACT::WALK_INIT;
            break;
        }

        break;

    //--------------------------------
    // �W�����v�n��
    //--------------------------------
    case PLAYER_ACT::JUMP_START_INIT:

        /*-------- �A�j���̏����ݒ� --------*/
        player_animeInit(3);

        ++player.act;
        /*fallthrough*/

    case PLAYER_ACT::JUMP_START:

        /*-------- ���̍s���ł̓��� --------*/
        player_moveY();
        player_moveX();

        // ��W�����v
        if (TRG_RELEASE(0) & PAD_TRG1)
        {
            player.act = PLAYER_ACT::JUMP_KEEP_INIT;
            player.speed.y = -PLAYER_JUMP_POWER_LOW;

            --player.jumpCount;
            break;
        }

        /*-------     �A�j������     -------*/
        if (player_anime(4, 2, false))
        {
            // �s���̑J��
            player.act = PLAYER_ACT::JUMP_KEEP_INIT;
            player.speed.y = -PLAYER_JUMP_POWER_HIGH;

            --player.jumpCount;
            break;
        }

        /*--------    �s���̑J��    --------*/

        break;

    //--------------------------------
    // �W�����v��
    //--------------------------------
    case PLAYER_ACT::JUMP_KEEP_INIT:

        /*-------- �A�j���̏����ݒ� --------*/
        player_animeInit(4);

        ++player.act;
        /*fallthrough*/

    case PLAYER_ACT::JUMP_KEEP:

        /*-------- ���̍s���ł̓��� --------*/
        player_moveY();
        player_moveX();

        /*-------     �A�j������     -------*/
        player_anime(7, 3, false);

        /*--------    �s���̑J��    --------*/

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
    // �W�����v���n
    //--------------------------------
    case PLAYER_ACT::JUMP_END_INIT:
        player_animeInit(5);

        // ���n���̉������̑��x��0��
        player.speed.x = 0.0f;

        ++player.act;
        /*fallthrough*/

    case PLAYER_ACT::JUMP_END:

        /*-------- ���̍s���ł̓��� --------*/
        // �Ȃ�

        /*-------     �A�j������     -------*/
        if (player_anime(8, 5, false))
        {
            player.act = PLAYER_ACT::IDLE_INIT;
            break;
        }

        /*--------    �s���̑J��    --------*/
        // �Ȃ�

        break;
    }
}

//--------------------------------------
//  �v���C���[��Y�����̈ړ�
//--------------------------------------
void player_moveY()
{
    // Y�����̈ړ�
    player.speed.y += GRAVITY;
}

//--------------------------------------
//  �v���C���[��X�����̈ړ�
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
