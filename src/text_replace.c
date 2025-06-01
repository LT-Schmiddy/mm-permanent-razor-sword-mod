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

    EZTR_Basic_ReplaceText(
        0x0C3D,
        EZTR_STANDARD_TEXT_BOX_I,
        48,
        EZTR_ICON_NO_ICON,
        EZTR_NO_VALUE,
        EZTR_NO_VALUE,
        EZTR_NO_VALUE,
        true,
        "This is a secret, but I'll let you in|11on it...If you bring me some |01gold|11dust|00, I can forge the |01strongest|11of swords|00... the strongest...|E0|BF",
        NULL
    );

    EZTR_Basic_ReplaceText(
        0x0039,
        EZTR_TRANSLUSCENT_BLUE_TEXT_BOX,
        1,
        EZTR_ICON_GILDED_SWORD,
        EZTR_NO_VALUE,
        EZTR_NO_VALUE,
        EZTR_NO_VALUE,
        true,
        "|17Your Razor Sword has been|11strengthened. Now it's a|11|01Gilded Sword|00!|18|11|12Newly forged, your sword is|11better than ever!|BF",
        NULL
    );

    EZTR_Basic_ReplaceText(
        0x0C53,
        EZTR_STANDARD_TEXT_BOX_I,
        48,
        EZTR_ICON_NO_ICON,
        EZTR_NO_VALUE,
        EZTR_NO_VALUE,
        EZTR_NO_VALUE,
        true,
        "There it is. We can't make a|11sword stronger than that.|11|13|12Oh, I used up most of the |01gold|11dust|00. Just a tiny bit was left, so|11I got rid of it for you.|19|BF",
        NULL
    );

    EZTR_Basic_ReplaceText(
        0x1786,
        EZTR_STANDARD_TEXT_BOX_II,
        1,
        EZTR_ICON_GILDED_SWORD,
        EZTR_NO_VALUE,
        EZTR_NO_VALUE,
        EZTR_NO_VALUE,
        true,
        "|04Gilded Sword|11|00Forged from gold dust and the|11Razor Sword, it's better than ever.|BF",
        NULL
    );
}