#include "permanent_razor_sword.h"

RECOMP_IMPORT("*", int recomp_printf(const char* fmt, ...));

// Razor Sword no longer degrades:
RECOMP_PATCH s32 func_8083FFEC(PlayState* play, Player* this) {
    if (this->heldItemAction == PLAYER_IA_SWORD_RAZOR) {
        return true;
    }
    return false;
}

// Corrected to ensure zubora recognizes your razor sword on future cycles:
RECOMP_PATCH s32 func_80B41528(PlayState* play) {
    if (GET_CUR_EQUIP_VALUE(EQUIP_TYPE_SWORD) == EQUIP_VALUE_SWORD_GILDED) {
        return 0xC4C;
    }

    if (GET_CUR_EQUIP_VALUE(EQUIP_TYPE_SWORD) == EQUIP_VALUE_SWORD_RAZOR) {
        return 0xC45;
    }

    return 0xC3B;
}

u32 remembered_equip = 0;
u32 remembered_stolen_item_1 = 0;
u32 remembered_stolen_item_2 = 0;

RECOMP_HOOK("Sram_SaveEndOfCycle") void remember_sword(PlayState* play) {
    remembered_equip = GET_CUR_EQUIP_VALUE(EQUIP_TYPE_SWORD);
    remembered_stolen_item_1 = STOLEN_ITEM_1;
    remembered_stolen_item_2 = STOLEN_ITEM_2;
}

RECOMP_HOOK_RETURN("Sram_SaveEndOfCycle") void restore_sword(PlayState* play) {

    if (CUR_FORM == 0) {
        if ((remembered_stolen_item_1 >= ITEM_SWORD_GILDED) 
            || (remembered_stolen_item_2 >= ITEM_SWORD_GILDED)
            || (remembered_equip >= ITEM_SWORD_GILDED)
            ) {
            CUR_FORM_EQUIP(EQUIP_SLOT_B) = ITEM_SWORD_GILDED;
            SET_EQUIP_VALUE(EQUIP_TYPE_SWORD, EQUIP_VALUE_SWORD_GILDED);
        
        } else if ((remembered_stolen_item_1 == ITEM_SWORD_RAZOR) 
            || (remembered_stolen_item_2 == ITEM_SWORD_RAZOR)
            || (remembered_equip == ITEM_SWORD_RAZOR)
            ) {
            CUR_FORM_EQUIP(EQUIP_SLOT_B) = ITEM_SWORD_RAZOR;
            SET_EQUIP_VALUE(EQUIP_TYPE_SWORD, EQUIP_VALUE_SWORD_RAZOR);
        } else {
            CUR_FORM_EQUIP(EQUIP_SLOT_B) = ITEM_SWORD_KOKIRI;
            SET_EQUIP_VALUE(EQUIP_TYPE_SWORD, EQUIP_VALUE_SWORD_KOKIRI);
        }
    } else {
        if ((remembered_stolen_item_1 >= ITEM_SWORD_GILDED) 
            || (remembered_stolen_item_2 >= ITEM_SWORD_GILDED)
            || (remembered_equip >= ITEM_SWORD_GILDED)
            ) {
            BUTTON_ITEM_EQUIP(0, EQUIP_SLOT_B) = ITEM_SWORD_GILDED;
            SET_EQUIP_VALUE(EQUIP_TYPE_SWORD, EQUIP_VALUE_SWORD_GILDED);
        } else if ((remembered_stolen_item_1 == ITEM_SWORD_RAZOR) 
            || (remembered_stolen_item_2 == ITEM_SWORD_RAZOR)
            || (remembered_equip == ITEM_SWORD_RAZOR)
            ) {
            BUTTON_ITEM_EQUIP(0, EQUIP_SLOT_B) = ITEM_SWORD_RAZOR;
            SET_EQUIP_VALUE(EQUIP_TYPE_SWORD, EQUIP_VALUE_SWORD_RAZOR);
        } else {
            BUTTON_ITEM_EQUIP(0, EQUIP_SLOT_B) = ITEM_SWORD_KOKIRI;
            SET_EQUIP_VALUE(EQUIP_TYPE_SWORD, EQUIP_VALUE_SWORD_KOKIRI);
        }
    }
}
