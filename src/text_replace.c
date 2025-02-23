#include "eztr_api.h"

EZTR_ON_INIT void replace_msgs() {
    EZTR_Basic_ReplaceText(
        0x0038,
        EZTR_STANDARD_TEXT_BOX_I,
        1,
        EZTR_ICON_RAZOR_SWORD,
        EZTR_NO_VALUE,
        EZTR_NO_VALUE,
        EZTR_NO_VALUE,
        true,
        "|17Your Kokiri Sword has been|11strengthened and forged into a|11|01Razor Sword|00!|18|11|12This new, sharper blade is a cut|11above the rest!|BF",
        NULL
    );

    EZTR_Basic_ReplaceText(
        0x0C3B,
        EZTR_STANDARD_TEXT_BOX_I,
        49,
        EZTR_ICON_NO_ICON,
        EZTR_NO_VALUE,
        100,
        EZTR_NO_VALUE,
        true,
        "All right...To |01reforge |00your sword,|11it will cost you |06100 Rupees|00. It'll|11be ready at |01sunrise.|11|00|12|17You'll have to let us hold onto|11your sword until then.|10So, would you like your sword|11reforged for |06100 Rupees|00?|11|02|C2I'll do it|11No thanks|BF|00|00",
        NULL
    );

    EZTR_Basic_ReplaceText(
        0x0C51,
        EZTR_STANDARD_TEXT_BOX_I,
        48,
        EZTR_ICON_NO_ICON,
        EZTR_NO_VALUE,
        EZTR_NO_VALUE,
        EZTR_NO_VALUE,
        true,
        "Now here's a secret...If you bring|11me |01gold dust|00, I'll be able to make|11it the |01strongest sword |00around.|10You got that? |01Gold dust|00!|19|BF|00",
        NULL
    );

    EZTR_Basic_ReplaceText(
        0x1785,
        EZTR_STANDARD_TEXT_BOX_II,
        1,
        EZTR_ICON_RAZOR_SWORD,
        EZTR_NO_VALUE,
        EZTR_NO_VALUE,
        EZTR_NO_VALUE,
        true,
        "|04Razor Sword|11|00The Kokiri Sword reforged at the|11smithy. A cut above the rest.|BF",
        NULL
    );
}