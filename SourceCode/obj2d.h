#ifndef OBJ2D_H
#define OBJ2D_H

//******************************************************************************
//
//
//      obj2d.h
//
//
//******************************************************************************

//------< �萔 >----------------------------------------------------------------
#define     SCREEN_LIMIT    (256)

//------< �\���� >--------------------------------------------------------------
struct OBJ2D
{
    typedef void(*FUNC_PTR)(OBJ2D*);
    FUNC_PTR            moveAlg;    // �ړ��A���S���Y��

    int                 state;      // ���
    int                 timer;      // �^�C�}�[

    bool                onGround;   // �n�ʃt���O
    bool                jumpEnd;    // ���n�t���O
    char                pad[2];     // �p�f�B���O�i���ԁj

    GameLib::Sprite*    spr;        // �X�v���C�g�|�C���^
    int                 area;       // �G���A
    VECTOR2             pos;        // �ʒu
    VECTOR2             scale;      // �X�P�[��
    VECTOR2             texPos;     // �摜�ʒu
    VECTOR2             texSize;    // �摜�T�C�Y
    VECTOR2             pivot;      // ��_
    VECTOR4             color;      // �F

    VECTOR2             speed;      // ���x
    int                 jumpCount;  // �c��W�����v��
    int                 act;        // �v���C���[�̍s���J�ڗp
    int                 anime;      // �A�j�������݉��R�}�ڂ�
    int                 animeTimer; // �A�j���p�^�C�}�[

    float               radius;     // ���a
    VECTOR2             offset;     // �ʒu���炠����̈�̒��S�ւ̃I�t�Z�b�g
    VECTOR2             origin;     // �����ʒu��ێ�
    float               angle;      // �p�x
};

//------< �֐� >----------------------------------------------------------------
OBJ2D* searchSet0(OBJ2D[], int, OBJ2D::FUNC_PTR, VECTOR2);
OBJ2D* searchSet(OBJ2D*, OBJ2D*, OBJ2D::FUNC_PTR, VECTOR2);

void sprite_render(OBJ2D*);
bool areaCheck(OBJ2D*);

#endif//OBJ2D_H