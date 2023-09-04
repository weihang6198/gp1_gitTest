#ifndef OBJ2D_H
#define OBJ2D_H

//******************************************************************************
//
//
//      obj2d.h
//
//
//******************************************************************************

//------< 定数 >----------------------------------------------------------------
#define     SCREEN_LIMIT    (256)

//------< 構造体 >--------------------------------------------------------------
struct OBJ2D
{
    typedef void(*FUNC_PTR)(OBJ2D*);
    FUNC_PTR            moveAlg;    // 移動アルゴリズム

    int                 state;      // 状態
    int                 timer;      // タイマー

    bool                onGround;   // 地面フラグ
    bool                jumpEnd;    // 着地フラグ
    char                pad[2];     // パディング（隙間）

    GameLib::Sprite*    spr;        // スプライトポインタ
    int                 area;       // エリア
    VECTOR2             pos;        // 位置
    VECTOR2             scale;      // スケール
    VECTOR2             texPos;     // 画像位置
    VECTOR2             texSize;    // 画像サイズ
    VECTOR2             pivot;      // 基準点
    VECTOR4             color;      // 色

    VECTOR2             speed;      // 速度
    int                 jumpCount;  // 残りジャンプ回数
    int                 act;        // プレイヤーの行動遷移用
    int                 anime;      // アニメが現在何コマ目か
    int                 animeTimer; // アニメ用タイマー

    float               radius;     // 半径
    VECTOR2             offset;     // 位置からあたり領域の中心へのオフセット
    VECTOR2             origin;     // 初期位置を保持
    float               angle;      // 角度
};

//------< 関数 >----------------------------------------------------------------
OBJ2D* searchSet0(OBJ2D[], int, OBJ2D::FUNC_PTR, VECTOR2);
OBJ2D* searchSet(OBJ2D*, OBJ2D*, OBJ2D::FUNC_PTR, VECTOR2);

void sprite_render(OBJ2D*);
bool areaCheck(OBJ2D*);

#endif//OBJ2D_H