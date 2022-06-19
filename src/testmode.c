#include "testmode.h"
#include "keycodes.h"
#include "pwdctl.h"
#include <tice.h>
#include <stdio.h>
#include <string.h>

#define textFlags (*(uint8_t *)(0xD00085))
#define trigFlags (*(uint8_t *)(0xD00080))
#define statusBarFlags (*(uint8_t *)(0xD000C7))

#define invcol() (textFlags ^= 1 << 3)

const uint16_t testmode_pwd[] = {kCapT, kCapE, kCapS, kCapT, k1};

void do_toggle_testmodebar()
{
    uint16_t buf[6];
    uint16_t cnt;

    cnt = getpwd(buf, 6);
    if (cnt != 5 || memcmp(buf, testmode_pwd, sizeof(uint16_t) * 5))
        return;
    toggle_testmodebar();
}
