#ifndef AUDIO_H
#define AUDIO_H

//******************************************************************************
//
//
//      audio.h
//
//
//******************************************************************************

//------< ’è” >----------------------------------------------------------------

// XWB‚ÌŽí—Þ
#define XWB_SYSTEM          0
#define XWB_STAGE1          1

// SYSTEM‚ÌŒø‰Ê‰¹
#define XWB_SYSTEM_KATI     0
#define XWB_SYSTEM_START    1

// STAGE1‚ÌŒø‰Ê‰¹
#define XWB_STAGE1_COIN     0
#define XWB_STAGE1_JUMP     1
#define XWB_STAGE1_SHOT     2
#define XWB_STAGE1_MISSILE  3
#define XWB_STAGE1_LASER    4
#define XWB_STAGE1_BOMB     5

//------< ŠÖ” >----------------------------------------------------------------
void audio_init();
void audio_deinit();

#endif//AUDIO_H
