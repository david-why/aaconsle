#include "defs.h"
#include "main.h"
#include "print.h"
#include "stats.h"
#include "keycodes.h"
#include "prgm.h"
#include "usb.h"
#include "timer.h"
#include "roll.h"
#include "pwdctl.h"
#include "help.h"
#include "mines.h"
#include "appvar.h"
#include "flags.h"
#include "testmode.h"
#include <tice.h>
#include <string.h>
#include <stdio.h>

char buf[64];

#define _C(c, f) \
    case c:      \
        f();     \
        break

int real_main()
{
    uint16_t key;

    while (true)
    {
        os_ClrHome();
        os_PutStrFull(">>>");
        key = os_GetKey();
        if (key == kClear)
            break;
        switch (key)
        {
            _C(kPrgm, do_program_list);
            _C(kVars, do_stats);
            _C(kMode, do_usb);
            _C(kCapT, do_timer);
            _C(kCapR, do_roll);
            _C(kCapP, do_setpwd);
            _C(kCapH, do_help);
            _C(kCapA, do_appvars);

            // hidden features
            _C(kCapM, do_mines);
            _C(kCapY, do_toggle_testmodebar);
        case kCapV:
            os_PutStrFull("AACONSLE ");
            os_PutStrFull(aaconsle_version);
            os_GetKey();
            break;

            // developer features
            _C(kCapF, do_flags);
        }
    }

    return 0;
}

int main() { return chkpwd() ? real_main() : 1; }
