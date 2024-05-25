#include "main.h"

#define SOUND_GEN 0
#define SOUND_JUMP 1
#define SOUND_HIT 2
#define SOUND_CARROTDIE 3

// Function prototypes
void CreateSoundInit();
void AllocateSound();
void ReleaseSound();
void PlayBGM();
void PlaySoundEffect(int soundCode);