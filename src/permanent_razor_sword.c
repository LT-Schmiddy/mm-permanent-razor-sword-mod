#include "permanent_razor_sword.h"

RECOMP_IMPORT("*", int recomp_printf(const char* fmt, ...));

// Patches a function in the base game that's used to check if the player should quickspin.
RECOMP_PATCH s32 func_8083FFEC(PlayState* play, Player* this) {
    // CUR_FORM_EQUIP(EQUIP_SLOT_B) = ITEM_SWORD_RAZOR;
    // SET_EQUIP_VALUE(EQUIP_TYPE_SWORD, EQUIP_VALUE_SWORD_RAZOR);

    if (this->heldItemAction == PLAYER_IA_SWORD_RAZOR) {
        return true;
    }
    return false;
}

RECOMP_PATCH void Sram_SaveEndOfCycle(PlayState* play) {
    s16 sceneId;
    s32 j;
    s32 i;
    u8 slot;
    u8 item;

    gSaveContext.save.timeSpeedOffset = 0;
    gSaveContext.save.eventDayCount = 0;
    gSaveContext.save.day = 0;
    gSaveContext.save.time = CLOCK_TIME(6, 0) - 1;

    gSaveContext.save.saveInfo.playerData.threeDayResetCount++;
    if (gSaveContext.save.saveInfo.playerData.threeDayResetCount > 999) {
        gSaveContext.save.saveInfo.playerData.threeDayResetCount = 999;
    }

    sceneId = Play_GetOriginalSceneId(play->sceneId);
    Play_SaveCycleSceneFlags(play);

    play->actorCtx.sceneFlags.chest &= sPersistentCycleSceneFlags[sceneId].chest;
    play->actorCtx.sceneFlags.switches[0] &= sPersistentCycleSceneFlags[sceneId].switch0;
    play->actorCtx.sceneFlags.switches[1] &= sPersistentCycleSceneFlags[sceneId].switch1;
    play->actorCtx.sceneFlags.collectible[0] &= sPersistentCycleSceneFlags[sceneId].collectible;
    play->actorCtx.sceneFlags.clearedRoom = 0;

    for (i = 0; i < SCENE_MAX; i++) {
        gSaveContext.cycleSceneFlags[i].switch0 =
            ((void)0, gSaveContext.cycleSceneFlags[i].switch0) & sPersistentCycleSceneFlags[i].switch0;
        gSaveContext.cycleSceneFlags[i].switch1 =
            ((void)0, gSaveContext.cycleSceneFlags[i].switch1) & sPersistentCycleSceneFlags[i].switch1;
        gSaveContext.cycleSceneFlags[i].chest =
            ((void)0, gSaveContext.cycleSceneFlags[i].chest) & sPersistentCycleSceneFlags[i].chest;
        gSaveContext.cycleSceneFlags[i].collectible =
            ((void)0, gSaveContext.cycleSceneFlags[i].collectible) & sPersistentCycleSceneFlags[i].collectible;
        gSaveContext.cycleSceneFlags[i].clearedRoom = 0;
        gSaveContext.save.saveInfo.permanentSceneFlags[i].unk_14 = 0;
        gSaveContext.save.saveInfo.permanentSceneFlags[i].rooms = 0;
    }

    for (; i < ARRAY_COUNT(gSaveContext.cycleSceneFlags); i++) {
        gSaveContext.cycleSceneFlags[i].chest = 0;
        gSaveContext.cycleSceneFlags[i].switch0 = 0;
        gSaveContext.cycleSceneFlags[i].switch1 = 0;
        gSaveContext.cycleSceneFlags[i].clearedRoom = 0;
        gSaveContext.cycleSceneFlags[i].collectible = 0;
    }

    for (i = 0; i < ARRAY_COUNT(gSaveContext.masksGivenOnMoon); i++) {
        gSaveContext.masksGivenOnMoon[i] = 0;
    }

    if (CHECK_WEEKEVENTREG(WEEKEVENTREG_84_20)) {
        Inventory_DeleteItem(ITEM_MASK_FIERCE_DEITY, SLOT(ITEM_MASK_FIERCE_DEITY));
    }

    for (i = 0; i < ARRAY_COUNT(sPersistentCycleWeekEventRegs); i++) {
        u16 isPersistentBits = sPersistentCycleWeekEventRegs[i];

        for (j = 0; j < ARRAY_COUNT(sBitFlags8); j++) {
            if (!(isPersistentBits & 3)) {
                gSaveContext.save.saveInfo.weekEventReg[i] =
                    ((void)0, gSaveContext.save.saveInfo.weekEventReg[i]) & (0xFF ^ sBitFlags8[j]);
            }
            isPersistentBits >>= 2;
        }
    }

    for (i = 0; i < ARRAY_COUNT(gSaveContext.eventInf); i++) {
        gSaveContext.eventInf[i] = 0;
    }

    CLEAR_EVENTINF(EVENTINF_THREEDAYRESET_LOST_RUPEES);
    CLEAR_EVENTINF(EVENTINF_THREEDAYRESET_LOST_BOMB_AMMO);
    CLEAR_EVENTINF(EVENTINF_THREEDAYRESET_LOST_NUT_AMMO);
    CLEAR_EVENTINF(EVENTINF_THREEDAYRESET_LOST_STICK_AMMO);
    CLEAR_EVENTINF(EVENTINF_THREEDAYRESET_LOST_ARROW_AMMO);

    if (gSaveContext.save.saveInfo.playerData.rupees != 0) {
        SET_EVENTINF(EVENTINF_THREEDAYRESET_LOST_RUPEES);
    }

    if (INV_CONTENT(ITEM_BOMB) == ITEM_BOMB) {
        item = INV_CONTENT(ITEM_BOMB);
        if (AMMO(item) != 0) {
            SET_EVENTINF(EVENTINF_THREEDAYRESET_LOST_BOMB_AMMO);
        }
    }
    if (INV_CONTENT(ITEM_DEKU_NUT) == ITEM_DEKU_NUT) {
        item = INV_CONTENT(ITEM_DEKU_NUT);
        if (AMMO(item) != 0) {
            SET_EVENTINF(EVENTINF_THREEDAYRESET_LOST_NUT_AMMO);
        }
    }
    if (INV_CONTENT(ITEM_DEKU_STICK) == ITEM_DEKU_STICK) {
        item = INV_CONTENT(ITEM_DEKU_STICK);
        if (AMMO(item) != 0) {
            SET_EVENTINF(EVENTINF_THREEDAYRESET_LOST_STICK_AMMO);
        }
    }
    if (INV_CONTENT(ITEM_BOW) == ITEM_BOW) {
        item = INV_CONTENT(ITEM_BOW);
        if (AMMO(item) != 0) {
            SET_EVENTINF(EVENTINF_THREEDAYRESET_LOST_ARROW_AMMO);
        }
    }

    for (i = 0; i < ITEM_NUM_SLOTS; i++) {
        if (gAmmoItems[i] != ITEM_NONE) {
            if ((gSaveContext.save.saveInfo.inventory.items[i] != ITEM_NONE) && (i != SLOT_PICTOGRAPH_BOX)) {
                item = gSaveContext.save.saveInfo.inventory.items[i];
                AMMO(item) = 0;
            }
        }
    }

    for (i = SLOT_BOTTLE_1; i <= SLOT_BOTTLE_6; i++) {
        // Check for all bottled items
        if (gSaveContext.save.saveInfo.inventory.items[i] >= ITEM_POTION_RED) {
            if (gSaveContext.save.saveInfo.inventory.items[i] <= ITEM_OBABA_DRINK) {
                for (j = EQUIP_SLOT_C_LEFT; j <= EQUIP_SLOT_C_RIGHT; j++) {
                    if (GET_CUR_FORM_BTN_ITEM(j) == gSaveContext.save.saveInfo.inventory.items[i]) {
                        SET_CUR_FORM_BTN_ITEM(j, ITEM_BOTTLE);
                        Interface_LoadItemIconImpl(play, j);
                    }
                }
                gSaveContext.save.saveInfo.inventory.items[i] = ITEM_BOTTLE;
            }
        }
    }

    REMOVE_QUEST_ITEM(QUEST_PICTOGRAPH);

    if (gSaveContext.save.saveInfo.playerData.health < 0x30) {
        gSaveContext.save.saveInfo.playerData.health = 0x30;
    }


    // The actual changes to the function:
    if (GET_CUR_EQUIP_VALUE(EQUIP_TYPE_SWORD) <= EQUIP_VALUE_SWORD_RAZOR) {
        // SET_EQUIP_VALUE(EQUIP_TYPE_SWORD, EQUIP_VALUE_SWORD_Razor);

        if (CUR_FORM == 0) {
            if ((STOLEN_ITEM_1 >= ITEM_SWORD_GILDED) || (STOLEN_ITEM_2 >= ITEM_SWORD_GILDED)) {
                CUR_FORM_EQUIP(EQUIP_SLOT_B) = ITEM_SWORD_GILDED;
                SET_EQUIP_VALUE(EQUIP_TYPE_SWORD, EQUIP_VALUE_SWORD_GILDED);
            
            } else if ((STOLEN_ITEM_1 == ITEM_SWORD_RAZOR) || (STOLEN_ITEM_2 == ITEM_SWORD_RAZOR)) {
                CUR_FORM_EQUIP(EQUIP_SLOT_B) = ITEM_SWORD_RAZOR;
                SET_EQUIP_VALUE(EQUIP_TYPE_SWORD, EQUIP_VALUE_SWORD_RAZOR);
            } else {
                CUR_FORM_EQUIP(EQUIP_SLOT_B) = ITEM_SWORD_KOKIRI;
            }
        } else {
            if ((STOLEN_ITEM_1 >= ITEM_SWORD_GILDED) || (STOLEN_ITEM_2 >= ITEM_SWORD_GILDED)) {
                BUTTON_ITEM_EQUIP(0, EQUIP_SLOT_B) = ITEM_SWORD_GILDED;
                SET_EQUIP_VALUE(EQUIP_TYPE_SWORD, EQUIP_VALUE_SWORD_GILDED);
            } else if ((STOLEN_ITEM_1 == ITEM_SWORD_RAZOR) || (STOLEN_ITEM_2 == ITEM_SWORD_RAZOR)) {
                BUTTON_ITEM_EQUIP(0, EQUIP_SLOT_B) = ITEM_SWORD_RAZOR;
                SET_EQUIP_VALUE(EQUIP_TYPE_SWORD, EQUIP_VALUE_SWORD_RAZOR);
            } else {
                BUTTON_ITEM_EQUIP(0, EQUIP_SLOT_B) = ITEM_SWORD_KOKIRI;
            }
        }
    }
    // End of changes

    if ((STOLEN_ITEM_1 == ITEM_SWORD_GREAT_FAIRY) || (STOLEN_ITEM_2 == ITEM_SWORD_GREAT_FAIRY)) {
        INV_CONTENT(ITEM_SWORD_GREAT_FAIRY) = ITEM_SWORD_GREAT_FAIRY;
    }

    if (STOLEN_ITEM_1 == ITEM_BOTTLE) {
        slot = SLOT(ITEM_BOTTLE);
        for (i = BOTTLE_FIRST; i < BOTTLE_MAX; i++) {
            if (gSaveContext.save.saveInfo.inventory.items[slot + i] == ITEM_NONE) {
                gSaveContext.save.saveInfo.inventory.items[slot + i] = ITEM_BOTTLE;
                break;
            }
        }
    }

    if (STOLEN_ITEM_2 == ITEM_BOTTLE) {
        slot = SLOT(ITEM_BOTTLE);
        for (i = BOTTLE_FIRST; i < BOTTLE_MAX; i++) {
            if (gSaveContext.save.saveInfo.inventory.items[slot + i] == ITEM_NONE) {
                gSaveContext.save.saveInfo.inventory.items[slot + i] = ITEM_BOTTLE;
                break;
            }
        }
    }

    SET_STOLEN_ITEM_1(STOLEN_ITEM_NONE);
    SET_STOLEN_ITEM_2(STOLEN_ITEM_NONE);

    Inventory_DeleteItem(ITEM_OCARINA_FAIRY, SLOT_TRADE_DEED);
    Inventory_DeleteItem(ITEM_SLINGSHOT, SLOT_TRADE_KEY_MAMA);
    Inventory_DeleteItem(ITEM_LONGSHOT, SLOT_TRADE_COUPLE);

    for (j = EQUIP_SLOT_C_LEFT; j <= EQUIP_SLOT_C_RIGHT; j++) {
        if ((GET_CUR_FORM_BTN_ITEM(j) >= ITEM_MOONS_TEAR) && (GET_CUR_FORM_BTN_ITEM(j) <= ITEM_PENDANT_OF_MEMORIES)) {
            SET_CUR_FORM_BTN_ITEM(j, ITEM_NONE);
            Interface_LoadItemIconImpl(play, j);
        }
    }

    gSaveContext.save.saveInfo.skullTokenCount &= ~0xFFFF0000;
    gSaveContext.save.saveInfo.skullTokenCount &= ~0x0000FFFF;
    gSaveContext.save.saveInfo.unk_EA0 = 0;

    gSaveContext.save.saveInfo.alienInfo[0] = 0;
    gSaveContext.save.saveInfo.alienInfo[1] = 0;
    gSaveContext.save.saveInfo.alienInfo[2] = 0;
    gSaveContext.save.saveInfo.alienInfo[3] = 0;
    gSaveContext.save.saveInfo.alienInfo[4] = 0;
    gSaveContext.save.saveInfo.alienInfo[5] = 0;
    gSaveContext.save.saveInfo.alienInfo[6] = 0;

    Sram_ClearHighscores();

    for (i = 0; i < 8; i++) {
        gSaveContext.save.saveInfo.inventory.dungeonItems[i] &= (u8)~1; // remove boss key
        DUNGEON_KEY_COUNT(i) = 0;
        gSaveContext.save.saveInfo.inventory.strayFairies[i] = 0;
    }

    gSaveContext.save.saveInfo.playerData.rupees = 0;
    gSaveContext.save.saveInfo.scarecrowSpawnSongSet = false;
    gSaveContext.powderKegTimer = 0;
    gSaveContext.unk_1014 = 0;
    gSaveContext.jinxTimer = 0;
    gSaveContext.rupeeAccumulator = 0;

    Horse_ResetHorseData(play);
}