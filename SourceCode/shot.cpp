//******************************************************************************
//
//
//      shot
//
//
//******************************************************************************

//------< �C���N���[�h >--------------------------------------------------------
#include "all.h"

//------< �ϐ� >----------------------------------------------------------------
int     shot_state;
Sprite* sprShot;
#if 9
//******************************************************************************
// TODO:09 �e�̔z���p��
//------------------------------------------------------------------------------
/*
�ۑ�j
    OBJ2D�^�ŗv�f��SHOT_MAX�̔z��shot��錾���܂��B
*/
//******************************************************************************
#endif
//TODO_09


//--------------------------------------
//  �e�̏����ݒ�
//--------------------------------------
void shot_init()
{
#if 5
//******************************************************************************
// TODO:05 �e�̏����ݒ�
//------------------------------------------------------------------------------
/*
�ۑ�j
    shot_state��0�������Ă����܂��B

����j
    ���̃\�[�X�R�[�h���̂��e�̃}�l�[�W���̂悤�ȓ��������܂��B�����ݒ�Ƃ��ẮA
    shot_state��0�������邾���ŗǂ��̂ł��B
*/
//******************************************************************************
#endif
    //TODO_05
    
}

//--------------------------------------
//  �e�̏I������
//--------------------------------------
void shot_deinit()
{
#if 6
//******************************************************************************
// TODO:06 �e�̏I������
//------------------------------------------------------------------------------
/*
�ۑ�j
    sprShot��j�����܂��B
*/
//******************************************************************************
#endif
    //TODO_06
    
}

//--------------------------------------
//  �e�̍X�V����
//--------------------------------------
void shot_update()
{
    switch (shot_state)
    {
    case 0:
        //////// �����ݒ� ////////

#if 7
//******************************************************************************
// TODO:07 �e�̉摜��ǂݍ���
//------------------------------------------------------------------------------
/*
�ۑ�j
    sprShot��shot.png��ǂݍ��݂܂��傤�B
*/
//******************************************************************************
#endif
        //TODO_07 
        

        ++shot_state;
        /*fallthrough*/

    case 1:
        //////// �p�����[�^�̐ݒ� ////////

#if 10
//******************************************************************************
// TODO:10 �e���N���A
//------------------------------------------------------------------------------
/*
�ۑ�j
    �e�̔z���S��0�ŃN���A���܂��B
*/
//******************************************************************************
#endif
        //TODO_10




        ++shot_state;
        /*fallthrough*/

    case 2:
        //////// �ʏ펞 ////////

#if 21
//******************************************************************************
// TODO:21 �͈͊O�`�F�b�N
//------------------------------------------------------------------------------
/*
�ۑ�j
    �����͒e�̍X�V�����̒ʏ펞�ł��B
    �ݖ�16�ō쐬�������L��for���̒��ŁA�e�e���s�����I������̉ӏ��ŃG���A�`�F�b�N
    ���s���܂��傤�B�ݖ�20�ō쐬����areaCheck�֐����ĂсA�e����ʂ��܂ރG���A����
    ���Ȃ���΁A�e�̑��݂������܂��傤�B
*/
//******************************************************************************
#endif
#if 16
//******************************************************************************
// TODO:16 �e�̓���
//------------------------------------------------------------------------------
/*
�ۑ�j
    �e�̒ʏ펞�̓�����������܂��B
    �ݖ�14�ō쐬�����̂Ɠ����`��for�����g���܂��B

�菇�j
    for���Ń��[�v�i�ݖ�14�ō쐬�����̂ƑS�������j
        �����e��moveAlg��NULL�ł����
            continue
        �����e�̃G���A���v���C���[�̃G���A�ƈقȂ��
            �e��moveAlg��NULL��ݒ�
            continue
        �e��moveAlg���瓮��֐����Ăяo���i�����͒e�̃A�h���X�j
*/
//******************************************************************************
#endif
        //TODO_16




        break;
    }
}

//--------------------------------------
//  �e�̕`�揈��
//--------------------------------------
void shot_render()
{
#if 14
//******************************************************************************
// TODO:14 �|�C���^���g����for��
//------------------------------------------------------------------------------
/*
�ۑ�j
    �|�C���^��L���Ɏg����for���̃��[�v���L�q���܂��傤�B
    �ݖ�13�ԂŒ�`�����萔���g�p���Ă����܂��B

    for���͉��L�̂悤�Ȍ`�ł��B
    for (��������; �p��������; �ď�������)
    {
        ��;
    }

�菇�j
    �܂��A�ݖ�11�ŋL�q����for�̍s�����R�����g�A�E�g���܂��B
    
    ��������    OBJ2D* s��SHOT_BEGIN�������܂��B
    �p��������  s��SHOT_END�Ɠ������Ȃ���Όp�����܂��B
    �ď�������  s���C���N�������g���܂��B

    ��          �ݖ�11�ŋL�q����shot[i]��s�ɒu�������܂��傤�B
*/
//******************************************************************************
#endif
#if 11
//******************************************************************************
// TODO:11 �e�̕`��
//------------------------------------------------------------------------------
/*
�ۑ�j
    ���݂��Ă���e��`�悵�܂��傤�B
    
�菇�j
    for����shot[0]����shot[SHOT_MAX-1]�܂ł����[�v�i�Y������int i�Ƃ���j
        shot[i].moveAlg��NULL�ł����continue;
        sprite_render�֐���shot[i]��`��

    ��sprite_render�̈����Ƃ��Ă�&shot[i]���������Ă����܂��i�ݖ�12�ԂŎ����j
*/
//******************************************************************************
#endif
    //TODO_11 


}

/*********************************************************************************

    �e�̈ړ��֐�

*********************************************************************************/

//--------------------------------------
//  �V���b�g0�i���i����e�j
//--------------------------------------
#if 15
//******************************************************************************
// TODO:15 �e�̈ړ��֐�0
//------------------------------------------------------------------------------
/*
�ۑ�j
    �e0�̈ړ��֐����쐬���܂��B
    �e0�͂��炩���ߐݒ肳�ꂽobj->angle�̕��p�Ɍ������Ē��i���܂��B

    �߂�l     void
    �֐���     moveShot0
    ����       OBJ2D* obj

�菇�j
    1.  obj->act�ŕ��򂳂���iswitch�����g���j
        case 0      �����ݒ�        break������
        case 1      �ʏ펞          break���L��

    2.  [�����ݒ�]
        obj�̊e�����o�ϐ��ɉ��L�̒l��ݒ肵�܂��B

        spr         sprShot
        scale       { 2, 2 }
        texPos      { 0, 0 }
        texSize     { 8, 8 }
        pivot       { 4, 4 }
        color       { 1, 1, 1, 1 }

        speed       obj->angle�̕����ɒ���8�ƂȂ�l��ݒ肵�܂��B

    3.  [�ʏ펞]
        �ʒu�ɑ��x�𑫂��܂��B

�⑫�j
    obj->angle�ɂ͂��炩���ߒl��ݒ肵�Ă����K�v������܂��B
*/
//******************************************************************************
#endif
//TODO_15



//--------------------------------------
//  �V���b�g1�i�v���C���[�Ɍ����������e�j
//--------------------------------------
#if 22
//******************************************************************************
// TODO:22 �e�̈ړ��֐�1
//------------------------------------------------------------------------------
/*
�ۑ�j
    �e1�̈ړ��֐����쐬���܂��B
    �e1�͔��˂��ꂽ�ʒu����A�v���C���[�Ɍ������Đ^���������ł����܂��B

    �߂�l     void
    �֐���     moveShot1
    ����       OBJ2D* obj

�菇�j
    1.  obj->act�ŕ��򂳂���iswitch�����g���j
        case 0      �����ݒ�        break������
        case 1      �ʏ펞          break���L��

    2.  [�����ݒ�]
        obj�̊e�����o�ϐ��ɉ��L�̒l��ݒ肵�܂��B

        spr         sprShot
        scale       { 2, 2 }
        texPos      { 0, 0 }
        texSize     { 8, 8 }
        pivot       { 4, 4 }
        color       { 1, 1, 1, 1 }

        speed       obj->pos����v���C���[�Ɍ������đ��x4�Ői�ޒl��ݒ肵�܂��B
                    [�v�����g�Q��]

    3.  [�ʏ펞]
        �ʒu�ɑ��x�𑫂��܂��B
*/
//******************************************************************************
#endif
//TODO_22



//--------------------------------------
//  �V���b�g2�i�ŏ��L������ �� �����e�j
//--------------------------------------
#if 25
//******************************************************************************
// TODO:25 �e�̈ړ��֐�2
//------------------------------------------------------------------------------
/*
�ۑ�j
    �e2�̈ړ��֐����쐬���܂��B
    �e2�́A���炩���ߐݒ肳�ꂽangle�̕����Ɉ�莞�Ԕ��ł����A��莞�ԐÎ~���A
    ���̌�v���C���[�ւƕ�����ς��Ē��i����e�ł��B

    �߂�l     void
    �֐���     moveShot2
    ����       OBJ2D* obj

�菇�j
    1.  obj->act�ŕ��򂳂���iswitch�����g���j
        case 0      �����ݒ�                  break������
        case 1      �L����                    break���L��
        case 2      ���@�ւƌ��������x��ݒ�  break������
        case 3      �ҋ@                      break���L��
        case 4      �ʏ펞                    break���L��

    2.  [�����ݒ�]
        obj�̊e�����o�ϐ��ɉ��L�̒l��ݒ肵�܂��B

        spr         sprShot
        scale       { 2, 2 }
        texPos      { 0, 0 }
        texSize     { 8, 8 }
        pivot       { 4, 4 }
        color       { 1, 1, 1, 1 }
        speed       angle�̕����֒���6
        timer       30

    3.  [�L����]
        timer��1���炷
        ����timer��0�ȉ��ɂȂ��Ă�����
            act���C���N�������g����
        pos��speed�𑫂�

    4.  [���@�ւƌ��������x��ݒ�]
        speed�ɁA���̎��_��pos����v���C���[�̒��S�ւƌ���������12�̃x�N�g����ݒ�
        timer��30��ݒ�

    5.  [�ҋ@]
        timer��1���炷
        ����timer��0�ȉ��ɂȂ��Ă�����
            act���C���N�������g����

    6.  [�ʏ펞]
        �ʒu�ɑ��x�𑫂�
*/
//******************************************************************************
#endif
//TODO_25

