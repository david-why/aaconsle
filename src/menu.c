#include "menu.h"
#include "keycodes.h"
#include <stdlib.h>
#include <tice.h>
#include <stdio.h>

int select_menu(const char *title, const void *data, unsigned int nmemb, unsigned int size, const char *gettext(const void *))
{
    const unsigned int n_pages = (nmemb + MENU_ITEMS_PER_PAGE - 1) / MENU_ITEMS_PER_PAGE;
    unsigned int sel, page, i, ind;
    uint16_t key;
    uint8_t need;

    os_ClrHome();
    os_PutStrLine(title);

    sel = page = 0;
    need = 1;
    while (1)
    {
        if (need)
        {
            need = 0;
            for (i = 0; i < MENU_ITEMS_PER_PAGE; i++)
            {
                ind = page * MENU_ITEMS_PER_PAGE + i;
                os_SetCursorPos(i + 1, 1);
                // os_SetCursorPos(i + 1, 0);
                // os_PutStrFull(sel == i ? ">" : " ");
                if (ind < nmemb)
                    os_PutStrLine(gettext(data + size * ind));
                for (ind = 0; ind < 26; ind++)
                    os_PutStrLine(" ");
            }
        }
        for (i = 0; i < MENU_ITEMS_PER_PAGE; i++)
            os_SetCursorPos(i + 1, 0),
                os_PutStrFull(i == sel ? ">" : " ");
        // os_SetCursorPos(sel + 1, 0);
        // os_PutStrFull(">");

        key = os_GetKey();
        switch (key)
        {
        case kEnter:
            return page * MENU_ITEMS_PER_PAGE + sel;
        case kClear:
            return -1;
        case kUp:
            if (sel == 0)
            {
                sel = MENU_ITEMS_PER_PAGE - 1;
                if (page * MENU_ITEMS_PER_PAGE + sel >= nmemb)
                    sel = nmemb % MENU_ITEMS_PER_PAGE - 1;
            }
            else
                sel--;
            break;
        case kDown:
            sel++;
            if (sel == MENU_ITEMS_PER_PAGE || page * MENU_ITEMS_PER_PAGE + sel >= nmemb)
                sel = 0;
            break;
        case kLeft:
            need = 1;
            if (page == 0)
                page = n_pages;
            page--;
            break;
        case kRight:
            need = 1;
            page++;
            if (page == n_pages)
                page = 0;
            // if (page * MENU_ITEMS_PER_PAGE >= nmemb)
            //     page--;
            break;
        }
    }
}

int areyousure_menu(const char *title)
{
    os_ClrHome();
    puts(title);
    os_NewLine();
    puts("Are you sure?");
    puts("enter=Yes   clear=No");
    uint16_t key = 0;
    while (key != kClear && key != kEnter)
        key = os_GetKey();
    return key == kEnter;
}
