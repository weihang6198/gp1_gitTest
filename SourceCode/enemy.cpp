#include "all.h"

int enemy_state;

OBJ2D enemy[ENEMY_MAX];

// �G�f�[�^
struct ENEMY_DATA
{
    Sprite*         spr;
    const wchar_t*  filePath;
    VECTOR2         texPos;
    VECTOR2         texSize;
    VECTOR2         pivot;
    float           radius;
    OBJ2D::FUNC_PTR moveAlg;
} enemyData[] = {
    { NULL, L"./Data/Images/archer.png", { 0, 0 }, { 256, 256 }, { 128, 128 }, 30, moveEnemy0 }, 
    { NULL, L"./Data/Images/kuma.png",   { 0, 0 }, { 256, 256 }, { 128, 128 }, 50, moveEnemy1 },
    { NULL, L"./Data/Images/neko.png",   { 0, 0 }, { 256, 256 }, { 128, 256 }, 60, moveEnemy2 },//�\���ۑ�ver.
};

// �G�z�u�p�f�[�^
struct ENEMY_SET
{
    int         area;
    int         enemyType;
    VECTOR2     pos;
} enemySet[] = {
    {  0,  0, {  300, 600 } }, 
    {  0,  0, {  800, 500 } },
    {  1,  0, {  200, 400 } },
    {  1,  1, {  600, 600 } },
    {  1,  1, {  900, 500 } },
    {  2,  1, {  200, 400 } },
    {  2,  1, {  500, 500 } },
    {  2,  2, { 1200, 200 } },
    { -1, -1, {   -1,  -1 } },
};

//--------------------------------------
//  �G�̏����ݒ�
//--------------------------------------
void enemy_init()
{
    enemy_state = 0;
}

//--------------------------------------
//  �G�̏I������
//--------------------------------------
void enemy_deinit()
{
    int dataNum = ARRAYSIZE(enemyData);
    for (int i = 0; i < dataNum; ++i)
    {
        safe_delete(enemyData[i].spr);
    }
}

//--------------------------------------
//  �G�̍X�V����
//--------------------------------------
void enemy_update()
{
    switch (enemy_state)
    {
    case 0:
    {
        //////// �����ݒ� ////////

        // �G�f�[�^���̌v�Z
        int dataNum = sizeof(enemyData) / sizeof(ENEMY_DATA);

        // �X�v���C�g�ǂݍ���
        for (int i = 0; i < dataNum; ++i)
        {
            enemyData[i].spr = sprite_load(enemyData[i].filePath);
        }

        ++enemy_state;
        /*fallthrough*/
    }

    case 1:
        //////// �p�����[�^�̐ݒ� ////////

        // �G�f�[�^�̃N���A
        for (int i = 0; i < ENEMY_MAX; ++i)
        {
            enemy[i]            = {};
        }

        // �G�̏o��
        for (int i = 0; enemySet[i].enemyType >= 0; ++i)
        {
            OBJ2D* p = searchSet0(
                enemy, ENEMY_MAX, 
                enemyData[enemySet[i].enemyType].moveAlg, enemySet[i].pos
            );
            if (!p) break;

            p->area = enemySet[i].area;
        }

        ++enemy_state;
        /*fallthrough*/

    case 2:
        //////// �ʏ펞 ////////

        // �G�̍s��
        for (int i = 0; i < ENEMY_MAX; ++i)
        {
            if (!enemy[i].moveAlg)              continue;
            if (enemy[i].area != player.area)   continue;

            (*enemy[i].moveAlg)(&enemy[i]);

            ++enemy[i].timer;
        }

        break;
    }
}

//--------------------------------------
//  �G�̕`�揈��
//--------------------------------------
void enemy_render()
{
    for (int i = 0; i < ENEMY_MAX; ++i)
    {
        if (!enemy[i].moveAlg)              continue;
        if (enemy[i].area != player.area)   continue;

        sprite_render(
            enemy[i].spr, 
            enemy[i].pos.x,     enemy[i].pos.y, 
            enemy[i].scale.x,   enemy[i].scale.y, 
            enemy[i].texPos.x,  enemy[i].texPos.y, 
            enemy[i].texSize.x, enemy[i].texSize.y, 
            enemy[i].pivot.x,   enemy[i].pivot.y, 
            ToRadian(0), 
            enemy[i].color.x,   enemy[i].color.y, 
            enemy[i].color.z,   enemy[i].color.w
        );

        // �G�̂�����̈�̕`��
        primitive::circle(
            enemy[i].pos + enemy[i].offset, enemy[i].radius, 
            { 1, 1 }, ToRadian(0), 
            { 1, 0, 0, 0.2f }
        );
    }
}

//--------------------------------------
//  �G0�̓���
//--------------------------------------
void moveEnemy0(OBJ2D* obj)
{
    OBJ2D* s = NULL;
    switch (obj->state)
    {
    case 0:
        //////// �����ݒ� ////////

        obj->scale      = { 0.5f, 0.5f };
        obj->color      = { 1, 1, 1, 1 };
        obj->spr        = enemyData[0].spr;
        obj->texPos     = enemyData[0].texPos;
        obj->texSize    = enemyData[0].texSize;
        obj->pivot      = enemyData[0].pivot;
        obj->radius     = enemyData[0].radius;
        obj->origin     = obj->pos;

        ++obj->state;
        /*fallthrough*/

    case 1:
        //////// �ʏ펞 ////////

        switch (obj->act)
        {
        //�E�֐i��
        case 0:
            obj->speed = { 2, 0 };

#if 23
//******************************************************************************
// TODO:23 �G0�̒e���ˁi�v���C���[�֌����������e�𔭎ˁj
//------------------------------------------------------------------------------
/*
�ۑ�j
    �����͓G0�i�A�[�`���[�j�̍s����[�ʏ펞]�́A�E�֐i�����ƕ�����ݒ肷��u�Ԃł��B
    �����Őݖ�22�ō쐬���������e�𔭎˂����܂��傤�B

    �܂��Acase 2: case 4: case 6: �ł������������������܂��傤�i�����]������ƒe
    ���o��悤�ɂȂ�j

�菇�j
    s��searchSet�֐��̖߂�l��������B�isearchSet�̑�3������moveShot1�j
    s��NULL�łȂ���΁As�̃G���A�ɁA�v���C���[�̃G���A��������B

    �� s�͊֐��̐擪�Ő錾����Ă��܂��B
*/
//******************************************************************************
#endif
            //TODO_23 




            ++obj->act;
            /*fallthrough*/

        case 1:
            if (obj->pos.x > obj->origin.x + 50)
                ++obj->act;

            break;

        //���֐i��
        case 2:
            obj->speed = { 0, 2 };

            ++obj->act;
            /*fallthrough*/

        case 3:
            if (obj->pos.y > obj->origin.y + 50)
                ++obj->act;

            break;

        //���֐i��
        case 4:
            obj->speed = { -2, 0 };

            ++obj->act;
            /*fallthrough*/

        case 5:
            if (obj->pos.x < obj->origin.x - 50)
                ++obj->act;

            break;

        // ��֐i��
        case 6:
            obj->speed = { 0, -2 };

            ++obj->act;
            /*fallthrough*/

        case 7:
            if (obj->pos.y < obj->origin.y - 50)
                obj->act = 0;

            break;
        }

        obj->pos += obj->speed;

        break;
    }
}

//--------------------------------------
//  �G1�̓���
//--------------------------------------
void moveEnemy1(OBJ2D* obj)
{
    switch (obj->state)
    {
    case 0:
        //////// �����ݒ� ////////

        obj->scale      = { 0.5f, 0.5f };
        obj->color      = { 1, 1, 1, 1 };
        obj->spr        = enemyData[1].spr;
        obj->texPos     = enemyData[1].texPos;
        obj->texSize    = enemyData[1].texSize;
        obj->pivot      = enemyData[1].pivot;
        obj->radius     = enemyData[1].radius;
        obj->origin     = obj->pos;

        ++obj->state;
        /*fallthrough*/

    case 1:
        //////// �ʏ펞 ////////

        switch (obj->act)
        {
        case 0:
            //////// �����ݒ� ////////
            obj->angle = ToRadian(-90);

            ++obj->act;
            /*fallthrough*/

        case 1:
            //////// �ʏ펞 ////////

            obj->pos = obj->origin + VECTOR2(sinf(obj->angle), -cosf(obj->angle)) * 200;
            obj->angle += ToRadian(1);
            while (obj->angle >= PI) obj->angle -= 2 * PI;  // -PI����PI�܂łōl����

#if 18
//******************************************************************************
// TODO:18 �G1�̒e����
//------------------------------------------------------------------------------
/*
�ۑ�j
    �����͓G1�i�N�}�j�̍s����[�ʏ펞]�ł��B���̊Ԋu��obj->angle�̕����ɒe0��
    ���˂����܂��傤�B

�菇�j
    ����obj->timer��4�Ŋ���؂��ꍇ�Ȃ�
        OBJ2D* s��searchSet�̖߂�l�����isearchSet�̑�3������moveShot0�j
        ����s��NULL�łȂ����
            �������ꂽ�V���b�g��area�Ƀv���C���[�̃G���A��ݒ�
            �������ꂽ�V���b�g��angle�ɃN�}�̊p�x��ݒ�

�� �ݖ�19����������܂ŃG���[���o�܂��B

����j
    searchSet�֐��Őݒ�ł���̂́A�ړ��֐��imoveAlg�j�ƈʒu�����ł��B
    ���̋��ނł�area���ʒu���̈ꕔ�Ȃ̂ŁAsearchSet�֐��Őݒ�ł���悤�ɂ��Ă�
    �ǂ��̂ł����AsearchSet�֐��̖߂�l���g���Ē��ɐݒ肷�鎖���o���ĖႦ��悤��
    �������ɂ��Ă��܂��B
*/
//******************************************************************************
#endif
            //TODO_18





            break;
        }

        break;
    }
}

//--------------------------------------
//  �G2�̓���
//--------------------------------------
void moveEnemy2(OBJ2D* obj)
{
    switch (obj->state)
    {
    case 0:
        //////// �����ݒ� ////////

        obj->scale      = { 0.5f, 0.5f };
        obj->color      = { 1, 1, 1, 1 };
        obj->spr        = enemyData[2].spr;
        obj->texPos     = enemyData[2].texPos;
        obj->texSize    = enemyData[2].texSize;
        obj->pivot      = enemyData[2].pivot;
        obj->radius     = enemyData[2].radius;
        obj->offset     = { 0, -64 };

        ++obj->state;
        /*fallthrough*/

    case 1:
        //////// �ʏ펞 ////////

        switch (obj->act)
        {
        case 0:
            //////// �����ݒ� ////////

            obj->speed = { -5, 0 };

            ++obj->act;
            /*fallthrough*/

        case 1:
            //////// �ʏ펞 ////////

            obj->speed.y += GRAVITY;

            if (obj->pos.y > GROUND_Y)
            {
                obj->pos.y = GROUND_Y;
                obj->speed.y = -30.0f;
            }

            if (obj->pos.x < player.pos.x - 240)
            {
                obj->speed.x = 5;
                obj->scale.x = -0.5f;
            }
            if (obj->pos.x > player.pos.x + 240)
            {
                obj->speed.x = -5;
                obj->scale.x = 0.5f;
            }

#if 26
//******************************************************************************
// TODO:26 �G2�̒e����
//------------------------------------------------------------------------------
/*
�ۑ�j
    �����͓G2�i�L�j�̍s����[�ʏ펞]�́A�s������ʂ�L�q���Ă����ł��B
    �����Őݖ�25�ō쐬�����e�𔭎˂����܂��傤�B

�菇�j
    �����L�̈ʒu����ʔ���������ŁA����60����1�̊m���Œ��I�ɓ��I�����ꍇ
        for����24�񃋁[�v�i�Y������int i�Ƃ���j
            OBJ2D* s��searchSet�̖߂�l�����isearchSet�̑�3������moveShot2�j
            ����s��NULL�Ȃ�break;
            �e�̃G���A�Ƀv���C���[�̃G���A��ݒ�
            �e�̊p�x��(i * 15.0f)�x��ݒ�
*/
//******************************************************************************
#endif
            //TODO_26





            break;
        }

        obj->pos += obj->speed;

        break;
    }
}
