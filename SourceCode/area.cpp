#include "all.h"

AREA_DATA areaData[AREA_MAX] = {
    { { 1, 1, 1, 1 } },
    { { 1, 0, 1, 1 } },
    { { 1, 0, 0, 1 } },
};

extern Sprite* sprBack;

//--------------------------------------
//  �G���A�̕`��
//--------------------------------------
void area_render()
{
    AREA_DATA* area = &areaData[player.area];
    sprite_render(
        sprBack,        // �X�v���C�g�|�C���^
        0, 0,           // �`��ʒu
        1, 1,           // �X�P�[��
        0, 0,           // ���摜�ʒu
        1280, 720,      // �摜�傫��
        0, 0,           // ��_
        ToRadian(0),    // �p�x
        area->color.x, area->color.y, area->color.z, area->color.w  // �F
    );
}