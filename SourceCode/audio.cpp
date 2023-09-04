#include "all.h"

//--------------------------------------
//  �I�[�f�B�I�̏����ݒ�
//--------------------------------------
void audio_init()
{
    // ���y�̓ǂݍ���
    music::load(0, L"./Data/Musics/bgm_maoudamashii_8bit29.wav");

    sound::load(XWB_SYSTEM, L"./Data/Sounds/system.xwb");    // ���j���[�Ȃǂ�SE
    sound::load(XWB_STAGE1, L"./Data/Sounds/stage1.xwb");    // �X�e�[�W�p��SE

    sound::setVolume(XWB_STAGE1, XWB_STAGE1_JUMP, 0.1f);
}

//--------------------------------------
//  �I�[�f�B�I�̏I������
//--------------------------------------
void audio_deinit()
{
    // ���y��S�ĉ��
    music::clear();
}
