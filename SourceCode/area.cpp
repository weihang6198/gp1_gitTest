#include "all.h"

AREA_DATA areaData[AREA_MAX] = {
    { { 1, 1, 1, 1 } },
    { { 1, 0, 1, 1 } },
    { { 1, 0, 0, 1 } },
};

extern Sprite* sprBack;

//--------------------------------------
//  エリアの描画
//--------------------------------------
void area_render()
{
    AREA_DATA* area = &areaData[player.area];
    sprite_render(
        sprBack,        // スプライトポインタ
        0, 0,           // 描画位置
        1, 1,           // スケール
        0, 0,           // 元画像位置
        1280, 720,      // 画像大きさ
        0, 0,           // 基準点
        ToRadian(0),    // 角度
        area->color.x, area->color.y, area->color.z, area->color.w  // 色
    );
}