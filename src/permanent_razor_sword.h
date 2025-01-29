#include "modding.h"
#include "global.h"

#include "z64horse.h"
#include "overlays/gamestates/ovl_file_choose/z_file_select.h"

void Sram_SyncWriteToFlash(SramContext* sramCtx, s32 curPage, s32 numPages);
void func_80147314(SramContext* sramCtx, s32 fileNum);
void func_80147414(SramContext* sramCtx, s32 fileNum, s32 arg2);

#define CHECK_NEWF(newf)                                                                                 \
    ((newf)[0] != 'Z' || (newf)[1] != 'E' || (newf)[2] != 'L' || (newf)[3] != 'D' || (newf)[4] != 'A' || \
     (newf)[5] != '3')

typedef struct PersistentCycleSceneFlags {
    /* 0x0 */ u32 switch0;
    /* 0x4 */ u32 switch1;
    /* 0x8 */ u32 chest;
    /* 0xC */ u32 collectible;
} PersistentCycleSceneFlags; // size = 0x10

#define PERSISTENT_CYCLE_FLAGS_SET(switch0, switch1, chest, collectible) { switch0, switch1, chest, collectible },
#define PERSISTENT_CYCLE_FLAGS_NONE PERSISTENT_CYCLE_FLAGS_SET(0, 0, 0, 0)

#define DEFINE_SCENE(_name, _enumValue, _textId, _drawConfig, _restrictionFlags, persistentCycleFlags) \
    persistentCycleFlags
#define DEFINE_SCENE_UNSET(_enumValue) PERSISTENT_CYCLE_FLAGS_NONE

/**
 * Array of bitwise flags which won't be turned off on a cycle reset (will persist between cycles)
 */
PersistentCycleSceneFlags sPersistentCycleSceneFlags[SCENE_MAX] = {
#include "tables/scene_table.h"
};

#undef DEFINE_SCENE
#undef DEFINE_SCENE_UNSET

// Each flag has 2 bits to store persistence over the three-day reset cycle
// Only 1 of these bits need to be set to persist (Values 1, 2, 3).
// Therefore, the final game does not distinguish between these two macros in use
#define PERSISTENT_WEEKEVENTREG(flag) (3 << (2 * BIT_FLAG_TO_SHIFT(flag)))
#define PERSISTENT_WEEKEVENTREG_ALT(flag) (2 << (2 * BIT_FLAG_TO_SHIFT(flag)))

// weekEventReg flags which will be not be cleared on a cycle reset
//! @note The index of the flag in this array must be the same to its index in the WeekeventReg array
//!       Only the mask is read from the `PERSISTENT_` macros.
// Size: 100
extern u16 sPersistentCycleWeekEventRegs[100];

// Unused remnant values from OoT. Not the correct sizes in MM.
#define OOT_SAVECONTEXT_SIZE 0x1428
#define OOT_SLOT_SIZE (OOT_SAVECONTEXT_SIZE + 0x28)
#define OOT_SRAM_HEADER_SIZE 0x10
#define OOT_SLOT_OFFSET(index) (OOT_SRAM_HEADER_SIZE + 0x10 + (index * OOT_SLOT_SIZE))

// used in other files
extern u32 gSramSlotOffsets[];


// Size: 24
extern u8 gAmmoItems[24];

// Stores flash start page number
extern s32 gFlashSaveStartPages[];

// Flash rom number of pages
extern s32 gFlashSaveNumPages[];

// Flash rom number of pages on very first time Player enters South Clock Town from the Clock Tower
extern s32 gFlashSpecialSaveNumPages[];

// Owl Save flash rom start page number
extern s32 gFlashOwlSaveStartPages[];

// Owl Save flash rom number of pages
extern s32 gFlashOwlSaveNumPages[];

// Save Options Sram Header flash rom start page number
extern s32 gFlashOptionsSaveStartPages[];

// Save Options Sram Header flash rom number of pages
extern s32 gFlashOptionsSaveNumPages[];

// Flash rom actual size needed
extern s32 gFlashSaveSizes[];

// Bit Flag array in which sBitFlags8[n] is (1 << n)
// Size: 8
extern u8 sBitFlags8[8];

extern u16 D_801F6AF0;
extern u8 D_801F6AF2;

void Sram_ClearHighscores(void);