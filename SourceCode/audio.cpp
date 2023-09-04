#include "all.h"

//--------------------------------------
//  オーディオの初期設定
//--------------------------------------
void audio_init()
{
    // 音楽の読み込み
    music::load(0, L"./Data/Musics/bgm_maoudamashii_8bit29.wav");

    sound::load(XWB_SYSTEM, L"./Data/Sounds/system.xwb");    // メニューなどのSE
    sound::load(XWB_STAGE1, L"./Data/Sounds/stage1.xwb");    // ステージ用のSE

    sound::setVolume(XWB_STAGE1, XWB_STAGE1_JUMP, 0.1f);
}

//--------------------------------------
//  オーディオの終了処理
//--------------------------------------
void audio_deinit()
{
    // 音楽を全て解放
    music::clear();
}
