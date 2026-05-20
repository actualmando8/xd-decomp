// Decompiled from: dbgMenuSoundTest.cpp
// Address range: 0x8000BD20..0x8000C0C4 | size: 0x3A4

/*
  Debug menu for sound testing.
  Allows testing of SE, BGM, ENV, and NAKIGOE (cry) sounds.
*/

/* Forward declarations */
static void sndPlay(u16 soundId, u32 param);

/* External data */
extern u16 snd_test_se[];
extern u32 snd_test_se_number;
extern u16 snd_test_bgm[];
extern u32 snd_test_bgm_number;
extern u16 snd_test_env[];
extern u32 snd_test_env_number;
extern u16 snd_test_nakigoe[];
extern u32 snd_test_nakigoe_number;

/*
  Address: 0x8000BD20 | size: 0x64
  dbgMenuSoundTestChangeSE(s32 value)
  Changes SE (sound effect) master volume.
  Value 0x155: Set volume to 0x7F (max)
  Value 0x156: Set volume to 0 (mute)
*/
void dbgMenuSoundTestChangeSE(s32 value) {
    if (value == 0x155) {
        GSsndSetMasterVolume(0x7F, 0, 0, 1);
    } else if (value == 0x156) {
        GSsndSetMasterVolume(0, 0, 0, 1);
    }
    return;
}

/*
  Address: 0x8000BD84 | size: 0x64
  dbgMenuSoundTestChangeBGM(s32 value)
  Changes BGM master volume.
  Value 0x153: Set volume to 0x7F (max)
  Value 0x154: Set volume to 0 (mute)
*/
void dbgMenuSoundTestChangeBGM(s32 value) {
    if (value == 0x153) {
        GSsndSetMasterVolume(0x7F, 0, 1, 0);
    } else if (value == 0x154) {
        GSsndSetMasterVolume(0, 0, 1, 0);
    }
    return;
}

/*
  Address: 0x8000BDE8 | size: 0x64
  dbgMenuSoundTestNAKIGOE()
  Opens menu for testing Pokemon cry sounds.
*/
void dbgMenuSoundTestNAKIGOE(void) {
    s32 selection;
    while ((selection = menuOpen(2, 1)) != -1) {
        u32 count = *snd_test_nakigoe_number;
        if (selection < (s32)count) {
            u16 soundId = snd_test_nakigoe[selection];
            sndPlay(soundId, 0);
        }
    }
    menuClose(2);
    return;
}

/*
  Address: 0x8000BE4C | size: 0x64
  dbgMenuSoundTestSE()
  Opens menu for testing sound effects.
*/
void dbgMenuSoundTestSE(void) {
    s32 selection;
    while ((selection = menuOpen(2, 1)) != -1) {
        u32 count = *snd_test_se_number;
        if (selection < (s32)count) {
            u16 soundId = snd_test_se[selection];
            sndPlay(soundId, 0);
        }
    }
    menuClose(2);
    return;
}

/*
  Address: 0x8000BEB0 | size: 0xD8
  dbgMenuSoundTestENV()
  Opens menu for testing environment sounds.
  Closes any currently playing ENV sounds before playing the new one.
*/
void dbgMenuSoundTestENV(void) {
    s32 selection;
    while ((selection = menuOpen(2, 1)) != -1) {
        u32 count = *snd_test_env_number;
        if (selection < (s32)count) {
            // Close any currently playing ENV sounds
            for (u32 i = 0; i < count; i++) {
                if ((s32)i == selection) continue;
                u16 soundId = snd_test_env[i];
                s32 status = GSsndGetStatus(soundId);
                if (status >= 1 && status < 4) {
                    GSsndClose(soundId);
                }
            }
            // Play selected ENV sound
            u16 soundId = snd_test_env[selection];
            sndPlay(soundId, 0);
        }
    }
    menuClose(2);
    return;
}

/*
  Address: 0x8000BF88 | size: 0xB8
  dbgMenuSoundTestBGM()
  Opens menu for testing background music.
  Checks status of all BGM sounds before playing.
*/
void dbgMenuSoundTestBGM(void) {
    s32 selection;
    while ((selection = menuOpen(2, 1)) != -1) {
        u32 count = *snd_test_bgm_number;
        if (selection < (s32)count) {
            // Check status of all BGM sounds
            for (u32 i = 0; i < count; i++) {
                if ((s32)i == selection) continue;
                u16 soundId = snd_test_bgm[i];
                GSsndGetStatus(soundId);
            }
            // Play selected BGM
            u16 soundId = snd_test_bgm[selection];
            sndPlay(soundId, 1);
        }
    }
    menuClose(2);
    return;
}

/*
  Address: 0x8000C040 | size: 0x84
  sndPlay(soundId, param)
  Plays a sound, closing any currently playing sound with the same ID.
  If param == 0, uses soundOpenPlayEnv.
  If param != 0, uses soundOpenPlay.
*/
static void sndPlay(u16 soundId, u32 param) {
    s32 status = GSsndGetStatus(soundId);
    if (status > 0 && status < 4) {
        GSsndClose(soundId);
        return;
    }
    
    if (param != 0) {
        soundOpenPlay(soundId, 0, 0x7F);
    } else {
        soundOpenPlayEnv(soundId, 0, 0x7F);
    }
}
