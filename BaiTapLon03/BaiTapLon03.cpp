// BaiTapLon03.cpp : Defines the entry point for the application.
//

#include "pch.h"
#include "framework.h"
#include "CRectangle.h"
#include "CEllipse.h"
#include "CCircle.h"
#include "CSquare.h"
#include "CTriangle.h"
#include "CPolygon.h"
#include "BaiTapLon03.h"
#include <vector>
#define MAX_LOADSTRING 100

//#define IDM_HCN 100
//#define IDM_ELLIPSE 101
//#define IDM_TRIANGLE 102


// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_BAITAPLON03, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_BAITAPLON03));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_BAITAPLON03));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_BAITAPLON03);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   /*HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);*/

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW|WS_CLIPCHILDREN,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);//WS_CLIPCHILDREN: Remove flicker

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
HWND hWndToolBar;
//Ham CALLBACK duoc goi nhieu lan
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static std::vector<Shape*> shapes;  //Danh sach cac hinh
    static int selecting = -1;          //Hinh dang chon de di chuyen voi keyboard
    static int currentMenuItem = -1;    //Loai  hinh CN,VUONG,...
    static PAINTSTRUCT ps;
    static HDC hdc;

    //Tao brush de to mau
    static HBRUSH hbr_green = CreateSolidBrush(RGB(131, 56, 236));
    static HBRUSH hbr_red=CreateSolidBrush(RGB(251, 86, 7));
    static HBRUSH hbr_blue=CreateHatchBrush(HS_FDIAGONAL ,RGB(255, 0, 110));
    static HBRUSH hbr_border=CreateSolidBrush(RGB(255, 190, 11));
    static HBRUSH hbr_hight_light = CreateSolidBrush(RGB(60, 90, 111));
    //Tao pen
    static HPEN hpen_highlight= CreatePen(PS_DASHDOT, 3, RGB(90, 70, 50));
    static HPEN hpen_normal = CreatePen(PS_SOLID, 1, RGB(30, 30, 30));
    //Region giao nhau
    static HRGN hrgn = CreateRectRgn(0, 0, 0, 0);
    //Mouse style
    static HCURSOR hCursorCross;
    
    static bool helpShow = true;

    RECT rt;
    enum { DRAW,DAGIAC };
    static INT flag = -1;
    
    switch (message)
    {
    case WM_CREATE:
        hWndToolBar = CreateSimpleToolbar(hWnd);
        hCursorCross = LoadCursor(NULL, IDC_CROSS);
        GetClientRect(hWnd, &rt);
        break;
    case WM_LBUTTONDOWN://Bam chuot trai
        {
        if (currentMenuItem != -1 && shapes.size() < 2) //Them hinh moi
        {
            flag = DRAW;
            int xPos = LOWORD(lParam);
            int yPos = HIWORD(lParam);

            Shape* shape;
            switch (currentMenuItem)
            {
            case 0://Hinh chu nhat
                shape = new CRectangle(Point(xPos, yPos), Point(xPos, yPos));
                break;
            case 1://Vuong
                shape = new CSquare(Point(xPos, yPos), 0);
                break;
            case 2://Ellip
                shape = new CEllipse(Point(xPos, yPos), 0, 0);
                break;
            case 3://Triangle
                shape = new CTriangle(Point(xPos, yPos), Point(xPos, yPos));
                break;
            case 4://Da giac
                flag = DAGIAC;
                shape = new CPolygon();
                ((CPolygon*)shape)->addPoint(xPos,yPos);
                //((CPolygon*)shape)->addPoint(700, 500);
                //((CPolygon*)shape)->addPoint(600, 800);
                break;
            case 5://Circle
                shape = new CCircle(Point(xPos, yPos), 0);
                break;
            }
            currentMenuItem = -1;
            shapes.push_back(shape);
            selecting = shapes.size() - 1;
            SetCursor(hCursorCross);
            hdc = GetDC(hWnd);
            SetROP2(hdc, R2_NOTXORPEN);
            shapes[shapes.size() - 1]->Draw(hdc);
            SetCapture(hWnd);

        }
        else if (flag == DAGIAC)   //Them diem moi cho da giac
        {
            int xPos = LOWORD(lParam);
            int yPos = HIWORD(lParam);
            //Them diem tai vi tri chuot vao da giac
            ((CPolygon*)shapes[shapes.size() - 1])->addPoint(xPos, yPos);
            InvalidateRect(hWnd, NULL, TRUE);
        }
        else
            flag = -1;
        }
        break;
    case WM_MOUSEMOVE:
    {
        if(currentMenuItem!=-1) 
            SetCursor(hCursorCross);
        if (GetCapture() == hWnd)
        {
            if (flag == DRAW)
            {
                SetROP2(hdc, R2_NOTXORPEN);
                int xPosEnd = LOWORD(lParam);
                int yPosEnd = HIWORD(lParam);
                shapes[shapes.size() - 1]->Draw(hdc);
                shapes[shapes.size() - 1]->UpdateBR(Point(xPosEnd, yPosEnd));
                shapes[shapes.size() - 1]->Draw(hdc);
            }
        }
    }
    break;
    case WM_RBUTTONDOWN:
        if (GetCapture() == hWnd)
        {
            ReleaseCapture();
            SendMessage(hWndToolBar, TB_CHECKBUTTON, IDM_DAGIAC, FALSE);
            flag = -1;
            InvalidateRect(hWnd, NULL, TRUE);
        }
        break;
    break;
    case WM_LBUTTONUP:  //Finish drawing polygon
        if (GetCapture() == hWnd)
        {
            if (flag != DAGIAC)
            {
                ReleaseCapture();

                SendMessage(hWndToolBar, TB_CHECKBUTTON, IDM_HCN, FALSE);//uncheck button
                SendMessage(hWndToolBar, TB_CHECKBUTTON, IDM_VUONG, FALSE);
                SendMessage(hWndToolBar, TB_CHECKBUTTON, IDM_ELLIP, FALSE);
                SendMessage(hWndToolBar, TB_CHECKBUTTON, IDM_TRIANGLE, FALSE);
                SendMessage(hWndToolBar, TB_CHECKBUTTON, IDM_TRON, FALSE);
                InvalidateRect(hWnd, NULL, TRUE);
                
            }
        }
        break;
    case WM_KEYDOWN://Hanh dong nhan phim
        {
            switch (wParam) //wParam: cu the la phim nao
            {
            case VK_UP:
                if (selecting != -1) 
                {
                    shapes[selecting]->Move(0, -8);
                    InvalidateRect(hWnd, NULL, TRUE);
                }
                break;
            case VK_DOWN:
                if (selecting != -1)
                {
                    shapes[selecting]->Move(0, 8);
                    InvalidateRect(hWnd, NULL, TRUE);
                }
                break;
            case VK_LEFT:
                if (selecting != -1)
                {
                    shapes[selecting]->Move(-8, 0);
                    InvalidateRect(hWnd, NULL, TRUE);
                }
                break;
            case VK_RIGHT:
                if (selecting != -1)
                {
                    shapes[selecting]->Move(8, 0);
                    InvalidateRect(hWnd, NULL, TRUE);
                }
                break;
            case VK_TAB:
                if (selecting != -1 && shapes.size()>1) 
                {
                    (selecting == 0) ? (selecting = 1) : (selecting = 0);
                    InvalidateRect(hWnd, NULL, TRUE);
                }
                break;
            case VK_OEM_PLUS:
                if (selecting != -1)
                {
                    shapes[selecting]->Scale(5);
                    InvalidateRect(hWnd, NULL, TRUE);
                }
                break;
            case VK_OEM_MINUS:
                if (selecting != -1)
                {
                    shapes[selecting]->Scale(-5);
                    InvalidateRect(hWnd, NULL, TRUE);
                }
                break;
            case VK_DELETE:
                if (selecting != -1) {
                    shapes.erase(shapes.begin()+selecting);
                    if (shapes.size() == 1) {//Sau khi xoa con 1 hinh thi chon hinh con lai
                        selecting = 0;
                    }
                    else //xoa het hinh
                    {
                        selecting = -1;
                    }
                    InvalidateRect(hWnd, NULL, TRUE);
                }
                break;
            }
        }
        break;
    case WM_COMMAND://Giai quyet cac nut bam.
        {
            int wmId = LOWORD(wParam);//Co san, lay ID cua nut
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_HCN:
                currentMenuItem = 0;
                break;
            case IDM_VUONG:
                currentMenuItem = 1;
                break;
            case IDM_ELLIP:
                currentMenuItem = 2;
                break;
            case IDM_TRIANGLE:
                currentMenuItem = 3;
                break;
            case IDM_DAGIAC:
                currentMenuItem = 4;
                break;
            case IDM_TRON:
                currentMenuItem = 5;
                break;
            case IDM_HELP:
                helpShow = helpShow?false:true;
                SendMessage(hWndToolBar, TB_CHECKBUTTON, IDM_HELP, FALSE);
                InvalidateRect(hWnd, NULL, TRUE);
                break;
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                DeleteObject(hbr_blue);
                DeleteObject(hbr_border);
                DeleteObject(hbr_green);
                DeleteObject(hbr_hight_light);
                DeleteObject(hbr_red);
                DeleteObject(hpen_highlight);
                DeleteObject(hpen_normal);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            //Get size of client rect
            GetClientRect(hWnd, &rt);

            //Start paiting
            hdc = BeginPaint(hWnd, &ps);

            HDC hdc_buffer = CreateCompatibleDC(hdc);//Create offscreen hdc
            HBITMAP hbmMem;

            // Create a bitmap big enough for our client rectangle.
            hbmMem = CreateCompatibleBitmap(hdc, rt.right - rt.left, rt.bottom - rt.top); 

            // Select the bitmap into the off-screen DC.
            SelectObject(hdc_buffer, hbmMem);

            // Erase the background.
            HBRUSH hbrBkGnd = CreateSolidBrush(GetSysColor(COLOR_WINDOW));
            FillRect(hdc_buffer, &rt, hbrBkGnd);
            DeleteObject(hbrBkGnd);

            for (int i = 0; i < shapes.size(); i++) 
            {
                if(i%2==0)//different color
                    SelectObject(hdc_buffer, hbr_red);
                else
                    SelectObject(hdc_buffer, hbr_green);

                if (i == selecting)//outline for selecting shape
                    SelectObject(hdc_buffer, hpen_highlight);
                else
                    SelectObject(hdc_buffer, hpen_normal);
                shapes[i]->Draw(hdc_buffer);
            }

           
            int t;
            //Ve phan giao
            if (shapes.size() == 2) {//Co 2 hinh
                //RGN_AND: Phan giao 2 hinh
                t=CombineRgn(hrgn, shapes[0]->getRegion(), shapes[1]->getRegion(), RGN_AND);
                FillRgn(hdc_buffer, hrgn, hbr_blue);//To mau
                FrameRgn(hdc_buffer, hrgn, hbr_border, 3, 3);//To vien

                if (t == NULLREGION) {
                    TextOutA(hdc_buffer, rt.right -150, rt.top+45, "Khong giao nhau", 15);
                }
                else {
                    TextOutA(hdc_buffer, rt.right - 150, rt.top+45, "Giao nhau", 9);
                }
            }
           
            if (helpShow)
            {

                LPCSTR helpText[] = {
                    "How to use?",
                    "1) Choose shape on toolbar. 2) Hold and drag mouse to draw a shape.",
                    "3) For polygon, left click to make new point, right click to finish the polygon.",
                    "4) Press <tab> to select a shape on screen. 5) Press arrow keys to move.",
                    "6) '-' and '+' key to resize. 7) Press 'del' to remove a shape.",
                    "8) You can only have 2 shapes, remove before adding a new one."
                };

                int line = 1;
                for (int i = 5; i >= 0; i--)
                {
                    TextOutA(hdc_buffer, 0, rt.bottom - line * 18, helpText[i], strlen(helpText[i]));
                    line++;
                }
            }
            BitBlt(hdc, rt.left, rt.top, rt.right-rt.left, rt.bottom-rt.top, hdc_buffer, 0, 0, SRCCOPY);

            DeleteObject(hbmMem);
            DeleteDC(hdc_buffer);
            SetTextAlign(hdc, TA_BOTTOM);

           
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        DeleteObject(hrgn);
        break;
    case WM_ERASEBKGND:
        return true;
    case WM_DRAWITEM:
        return true;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}


