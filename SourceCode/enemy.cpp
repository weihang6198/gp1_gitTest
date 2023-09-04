#include "all.h"

int enemy_state;

OBJ2D enemy[ENEMY_MAX];

// 敵データ
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
    { NULL, L"./Data/Images/neko.png",   { 0, 0 }, { 256, 256 }, { 128, 256 }, 60, moveEnemy2 },//予備課題ver.
};

// 敵配置用データ
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
//  敵の初期設定
//--------------------------------------
void enemy_init()
{
    enemy_state = 0;
}

//--------------------------------------
//  敵の終了処理
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
//  敵の更新処理
//--------------------------------------
void enemy_update()
{
    switch (enemy_state)
    {
    case 0:
    {
        //////// 初期設定 ////////

        // 敵データ数の計算
        int dataNum = sizeof(enemyData) / sizeof(ENEMY_DATA);

        // スプライト読み込み
        for (int i = 0; i < dataNum; ++i)
        {
            enemyData[i].spr = sprite_load(enemyData[i].filePath);
        }

        ++enemy_state;
        /*fallthrough*/
    }

    case 1:
        //////// パラメータの設定 ////////

        // 敵データのクリア
        for (int i = 0; i < ENEMY_MAX; ++i)
        {
            enemy[i]            = {};
        }

        // 敵の出現
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
        //////// 通常時 ////////

        // 敵の行動
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
//  敵の描画処理
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

        // 敵のあたり領域の描画
        primitive::circle(
            enemy[i].pos + enemy[i].offset, enemy[i].radius, 
            { 1, 1 }, ToRadian(0), 
            { 1, 0, 0, 0.2f }
        );
    }
}

//--------------------------------------
//  敵0の動作
//--------------------------------------
void moveEnemy0(OBJ2D* obj)
{
    OBJ2D* s = NULL;
    switch (obj->state)
    {
    case 0:
        //////// 初期設定 ////////

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
        //////// 通常時 ////////

        switch (obj->act)
        {
        //右へ進む
        case 0:
            obj->speed = { 2, 0 };

#if 23
//******************************************************************************
// TODO:23 敵0の弾発射（プレイヤーへ向かう方向弾を発射）
//------------------------------------------------------------------------------
/*
課題）
    ここは敵0（アーチャー）の行動の[通常時]の、右へ進もうと方向を設定する瞬間です。
    ここで設問22で作成した方向弾を発射させましょう。

    また、case 2: case 4: case 6: でも同じ処理を実装しましょう（方向転換すると弾
    が出るようになる）

手順）
    sにsearchSet関数の戻り値を代入する。（searchSetの第3引数はmoveShot1）
    sがNULLでなければ、sのエリアに、プレイヤーのエリアを代入する。

    ※ sは関数の先頭で宣言されています。
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

        //下へ進む
        case 2:
            obj->speed = { 0, 2 };

            ++obj->act;
            /*fallthrough*/

        case 3:
            if (obj->pos.y > obj->origin.y + 50)
                ++obj->act;

            break;

        //左へ進む
        case 4:
            obj->speed = { -2, 0 };

            ++obj->act;
            /*fallthrough*/

        case 5:
            if (obj->pos.x < obj->origin.x - 50)
                ++obj->act;

            break;

        // 上へ進む
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
//  敵1の動作
//--------------------------------------
void moveEnemy1(OBJ2D* obj)
{
    switch (obj->state)
    {
    case 0:
        //////// 初期設定 ////////

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
        //////// 通常時 ////////

        switch (obj->act)
        {
        case 0:
            //////// 初期設定 ////////
            obj->angle = ToRadian(-90);

            ++obj->act;
            /*fallthrough*/

        case 1:
            //////// 通常時 ////////

            obj->pos = obj->origin + VECTOR2(sinf(obj->angle), -cosf(obj->angle)) * 200;
            obj->angle += ToRadian(1);
            while (obj->angle >= PI) obj->angle -= 2 * PI;  // -PIからPIまでで考える

#if 18
//******************************************************************************
// TODO:18 敵1の弾発射
//------------------------------------------------------------------------------
/*
課題）
    ここは敵1（クマ）の行動の[通常時]です。一定の間隔でobj->angleの方向に弾0を
    発射させましょう。

手順）
    もしobj->timerが4で割り切れる場合なら
        OBJ2D* sにsearchSetの戻り値を代入（searchSetの第3引数はmoveShot0）
        もしsがNULLでなければ
            生成されたショットのareaにプレイヤーのエリアを設定
            生成されたショットのangleにクマの角度を設定

※ 設問19を実装するまでエラーが出ます。

解説）
    searchSet関数で設定できるのは、移動関数（moveAlg）と位置だけです。
    この教材ではareaも位置情報の一部なので、searchSet関数で設定できるようにしても
    良いのですが、searchSet関数の戻り値を使って直に設定する事を覚えて貰えるような
    教え方にしています。
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
//  敵2の動作
//--------------------------------------
void moveEnemy2(OBJ2D* obj)
{
    switch (obj->state)
    {
    case 0:
        //////// 初期設定 ////////

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
        //////// 通常時 ////////

        switch (obj->act)
        {
        case 0:
            //////// 初期設定 ////////

            obj->speed = { -5, 0 };

            ++obj->act;
            /*fallthrough*/

        case 1:
            //////// 通常時 ////////

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
// TODO:26 敵2の弾発射
//------------------------------------------------------------------------------
/*
課題）
    ここは敵2（猫）の行動の[通常時]の、行動を一通り記述してある後です。
    ここで設問25で作成した弾を発射させましょう。

手順）
    もし猫の位置が画面半分よりも上で、かつ60分の1の確率で抽選に当選した場合
        for文で24回ループ（添え字はint iとする）
            OBJ2D* sにsearchSetの戻り値を代入（searchSetの第3引数はmoveShot2）
            もしsがNULLならbreak;
            弾のエリアにプレイヤーのエリアを設定
            弾の角度に(i * 15.0f)度を設定
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
