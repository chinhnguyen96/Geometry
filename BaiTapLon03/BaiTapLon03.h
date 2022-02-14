#pragma once

#include "resource.h"
// tu lam, so khong trung
#define IDM_HCN 100
#define IDM_VUONG 101
#define IDM_ELLIP 102
#define IDM_TRIANGLE 103
#define IDM_DAGIAC 106
#define IDM_TRON 107
#define IDM_HELP 108
HIMAGELIST g_hImageList = NULL;
HWND CreateSimpleToolbar(HWND hWndParent)
{
    // Declare and initialize local constants.
    const int ImageListID = 0;
    const int numButtons = 7;//So nut
    const int bitmapSize = 8;//Kich thuoc

    const DWORD buttonStyles = BTNS_CHECKGROUP;//Style cua nut

    // Create the toolbar.
    HWND hWndToolbar = CreateWindowEx(0, TOOLBARCLASSNAME, NULL,
        WS_CHILD | TBSTYLE_CHECK, 0, 0, 0, 0,
        hWndParent, NULL, (HINSTANCE)GetWindowLong(hWndParent, GWLP_HINSTANCE), NULL);

    if (hWndToolbar == NULL)//Neu tao that bai thi return
        return NULL;

    // Create the image list.
    g_hImageList = ImageList_Create(bitmapSize, bitmapSize,   // Dimensions of individual bitmaps.
        ILC_COLOR16 | ILC_MASK,   // Ensures transparent background.
        numButtons, 0);

    // Set the image list.
    SendMessage(hWndToolbar, TB_SETIMAGELIST,
        (WPARAM)ImageListID,
        (LPARAM)g_hImageList);

    // Load the button images.
    SendMessage(hWndToolbar, TB_LOADIMAGES,
        (WPARAM)IDB_STD_SMALL_COLOR,
        (LPARAM)HINST_COMMCTRL);

    // Initialize button info.
    // IDM_NEW, IDM_OPEN, and IDM_SAVE are application-defined command constants.

    TBBUTTON tbButtons[numButtons] =
    {
        { I_IMAGENONE, IDM_HCN,  TBSTATE_ENABLED, buttonStyles, {0}, 0, (INT_PTR)L"Hình chữ nhật" },
        { I_IMAGENONE, IDM_VUONG,  TBSTATE_ENABLED, buttonStyles, {0}, 0, (INT_PTR)L"Hình vuông" },
        { I_IMAGENONE, IDM_ELLIP, TBSTATE_ENABLED, buttonStyles, {0}, 0, (INT_PTR)L"Hình ellips"},
        { I_IMAGENONE, IDM_TRIANGLE, TBSTATE_ENABLED, buttonStyles, {0}, 0, (INT_PTR)L"Hình tam giác"},
        { I_IMAGENONE, IDM_DAGIAC,  TBSTATE_ENABLED, buttonStyles, {0}, 0, (INT_PTR)L"Hình đa giác" },
        { I_IMAGENONE, IDM_TRON, TBSTATE_ENABLED, buttonStyles, {0}, 0, (INT_PTR)L"Hình tròn"},
        { I_IMAGENONE, IDM_HELP, TBSTATE_ENABLED, buttonStyles, {0}, 0, (INT_PTR)L"Hướng dẫn"}
    };

    // Add buttons.
    SendMessage(hWndToolbar, TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0);
    SendMessage(hWndToolbar, TB_ADDBUTTONS, (WPARAM)numButtons, (LPARAM)&tbButtons);

    // Resize the toolbar, and then show it.
    SendMessage(hWndToolbar, TB_AUTOSIZE, 0, 0);
    ShowWindow(hWndToolbar, TRUE);

    return hWndToolbar;
}