#include "roll.h"
#include "print.h"
#include "keycodes.h"
#include <tice.h>

int roll(int num, int sides, int res, roll_type_t typ)
{
    int ans;

    if (typ != roll_normal)
        ans = roll(num, sides, res, roll_normal);
    while (num-- > 0)
        res += randInt(1, sides);
    if (typ == roll_disadv)
        return ans < res ? ans : res;
    if (typ == roll_adv)
        return ans > res ? ans : res;
    return res;
}

void do_roll()
{
    uint8_t sel;
    int num, sides, mod, res;
    int *const lst[] = {&num, &sides, &mod};
    roll_type_t adv;
    uint16_t key;

    os_ClrHome();
    sel = 0;
    num = 1;
    sides = 20;
    mod = 0;
    adv = roll_normal;
    while (1)
    {
        os_SetCursorPos(0, 0);
        os_PutStrLine("Dice rolling");
        os_NewLine();
        os_PutStrLine(sel == 0 ? ">" : " ");
        os_PutStrLine("Num:");
        print(print_int, num);
        os_PutStrLine("        ");
        os_NewLine();
        os_PutStrLine(sel == 1 ? ">" : " ");
        os_PutStrLine("Sides:");
        print(print_int, sides);
        os_PutStrLine("        ");
        os_NewLine();
        os_PutStrLine(sel == 2 ? ">" : " ");
        os_PutStrLine("Mod:");
        print(print_int, mod);
        os_PutStrLine("        ");
        os_NewLine();
        os_PutStrLine(" ");
        if (adv == roll_disadv)
            os_PutStrLine("Disadvantage");
        else if (adv == roll_adv)
            os_PutStrLine("Advantage   ");
        else
            os_PutStrLine("Normal      ");
        os_NewLine();

        key = os_GetKey();
        switch (key)
        {
        case kClear:
            return;
        case kUp:
            if (sel)
                sel--;
            else
                sel = 2;
            break;
        case kDown:
            if (sel < 2)
                sel++;
            else
                sel = 0;
            break;
        case kLeft:
            adv--;
            if (adv < roll_disadv)
                adv = roll_adv;
            break;
        case kRight:
            adv++;
            if (adv > roll_adv)
                adv = roll_disadv;
            break;
        case kEnter:
            res = roll(num, sides, mod, adv);
            os_NewLine();
            os_PutStrLine("Result:");
            print(print_int, res);
            os_PutStrLine("        ");
            break;
        case kChs:
            *lst[sel] = -*lst[sel];
            break;
        case kDel:
            *lst[sel] = 0;
            break;
        default:
            res = key2int(key);
            if (res != -1)
                *lst[sel] = *lst[sel] * 10 + res;
            break;
        }
    }
}
