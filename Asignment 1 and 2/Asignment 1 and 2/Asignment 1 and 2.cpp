// Task 1.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Asignment 1 and 2.h"
#include "Resource.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
int lightState1 = 1;								// State of the trafic light 1
int lightState2 = 3;								// State of the trafic light 2
UINT_PTR tmr;									// Timer identifyer

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
    LoadStringW(hInstance, IDC_ASIGNMENT1AND2, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ASIGNMENT1AND2));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDC_ASIGNMENT1AND2));
    wcex.hCursor        = LoadCursor(nullptr, IDC_CROSS);
	// Change the background color of the application window on the below line into 
	// wcex.hbrBackground  = (HBRUSH)(CreateSolidBrush(RGB(0, 0, 0))); // black
	// where you change the RGB values into what you want. RGB codes retrievable at: https://www.rapidtables.com/web/color/RGB_Color.html
    //wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1); // White standard brush
	//wcex.hbrBackground  = (HBRUSH)(CreateSolidBrush(RGB(50, 50, 50))); // Dark grey
	wcex.hbrBackground = (HBRUSH)(CreateSolidBrush(RGB(60, 130, 60))); // Green
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_ASIGNMENT1AND2);
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

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   // Initialise timer function
   tmr = SetTimer(
		hWnd, // Window handle
	  //NULL, // Timer ID (one is created, works when stored in tmr)
		1, // Timer ID
		1000, // Timeout period
		NULL // Callback function ID
   );

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//	WM_TIMER	- Updates the main window state
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static int xpos = 100;
	static int ypos = 100;

    switch (message)
    {
	case WM_CREATE:
		//Timer and other Initializations could go here
		break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;

    case WM_PAINT:
        {
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		RECT rect;
		int width = 0;
		int height = 0;
		int roadWidth = 100;

		// Find window size
		if (GetWindowRect(hWnd, &rect)) {
			width = rect.right - rect.left;
			height = rect.bottom - rect.top;
		}

		// Create roads
		//createRoad(HDC hdc, int xStart, int yStart, int xEnd, int yEnd)
		createRoad(hdc, 0, height*0.5 - 0.5*roadWidth, width, height*0.5 + 0.5*roadWidth); // Horisontal
		createRoad(hdc, width*0.5 - 0.5*roadWidth, 0, width*0.5 + 0.5*roadWidth, height); // Vertical
		//createRoad(hdc, height*0.5, 0, 100, height);

		// void DrawTraficlight(int xPosition, int yPosition, int scale, int state , HDC hdc)
		DrawTraficlight(width*0.5 - 85, height*0.5 - 145, 3, lightState1, hdc); //Top left
		DrawTraficlight(width*0.5 + 55, height*0.5 + 55, 3, lightState2, hdc); // Bottom right
		//DrawTraficlight(300, 20, 5, lightState, hdc);
		//DrawTraficlight(500, 30, 5, lightState, hdc);
		//DrawTraficlight(700, 40, 5, lightState, hdc);
		
		// create car
		//void createCars(HDC hdc, int xPos, int yPos, int angle)

		EndPaint(hWnd, &ps);   
        }
        break;

	// NB! Low priority message
	case WM_TIMER:
		lightState1 = (lightState1 % 4) + 1;
		lightState2 = (lightState2 % 4) + 1;
		InvalidateRect(hWnd, NULL, true);// TRUE and true both works
		break;

	case WM_LBUTTONDOWN:	
		//lightState = (lightState % 4) + 1;
		lightState1 = 0; // Reset state for reasons
		lightState2 = 2; // Reset state for reasons
		InvalidateRect(hWnd, NULL, TRUE);
		break;

	case WM_RBUTTONDOWN:
		//lightState = (lightState % 4) + 1;
		lightState1 = 2; // Reset state for reasons
		lightState2 = 0; // Reset state for reasons
		InvalidateRect(hWnd, NULL, TRUE);
		break;

    case WM_DESTROY:
		KillTimer(NULL, tmr); // destroy the timer
		//KillTimer(hWnd, 1); // alternative method (same timer)
        PostQuitMessage(0);
        break;

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

// Draws a trafic light at the given x scale position, with the given scale in the given context
void DrawTraficlight(int xPos, int yPos, int scale, int state, HDC hdc) {
	//Setup
	HBRUSH hBrush; 
	HGDIOBJ hOrg;

	// Create the black frame
	hBrush = CreateSolidBrush(RGB(0, 0, 0)); // Select black brush
	hOrg = SelectObject(hdc, hBrush);

	// Define rectangle context, left, topp, right, bottom
	Rectangle(hdc, xPos, yPos, xPos + 10*scale, yPos + 30*scale);
	
	// Reset Original brush
	SelectObject(hdc, hOrg);
	DeleteObject(hBrush);

	// Create the RYG lights
	// Circle 1
	if (state == 0 || state == 1 || state == 2) { // The scircle should be red
		hBrush = CreateSolidBrush(RGB(255, 0, 0));// Select red brush
		hOrg = SelectObject(hdc, hBrush); // Activate hBrush and store original brush
	}else { // Else The scircle should be grey
		hBrush = CreateSolidBrush(RGB(100, 100, 100));
		hOrg = SelectObject(hdc, hBrush);
	}
	//Elipse specified by the bounding rectangle left, top, right, bottom utlined using the current pen and filled by using the current brush
	Ellipse(hdc, xPos, yPos, xPos + 10 * scale, yPos + 10 * scale);
	// Reset original brush
	SelectObject(hdc, hOrg);
	DeleteObject(hBrush);

	// Circle 2
	if (state == 0 || state == 2 || state == 4) {// Yellow circle	
		hBrush = CreateSolidBrush(RGB(255, 255, 0));
		hOrg = SelectObject(hdc, hBrush);	
	}else { // Grey circle
		hBrush = CreateSolidBrush(RGB(100, 100, 100));
		hOrg = SelectObject(hdc, hBrush);
	}
	Ellipse(hdc, xPos, yPos + 10 * scale, xPos + 10 * scale, yPos + 20 * scale);
	// Reset original brush
	SelectObject(hdc, hOrg);
	DeleteObject(hBrush);

	// Circle 3
	if (state == 0 || state == 3) {// Green circle
		hBrush = CreateSolidBrush(RGB(0, 255, 0));
		hOrg = SelectObject(hdc, hBrush);
	}else {// Grey circle
		hBrush = CreateSolidBrush(RGB(100, 100, 100));
		hOrg = SelectObject(hdc, hBrush);
	}
	Ellipse(hdc, xPos, yPos + 20 * scale, xPos + 10 * scale, yPos + 30 * scale);
	// Reset original brush
	SelectObject(hdc, hOrg);
	DeleteObject(hBrush);
}

//creates a road (grey rectangle) from position, to position
void createRoad(HDC hdc, int xStart, int yStart, int xEnd, int yEnd) {
	//Setup
	HBRUSH hBrush;
	HGDIOBJ hOrg;
	HPEN hPen;
	HGDIOBJ pOrg;


	// Create the frame
	// Select painting tools
	hBrush = CreateSolidBrush(RGB(50, 50, 50)); // Select asphalt grey brush
	hOrg = SelectObject(hdc, hBrush);
	hPen = CreatePen(PS_SOLID, 1, RGB(50, 50, 50));
	pOrg = SelectObject(hdc, hPen);

	// Define rectangle context, left, topp, right, bottom
	Rectangle(hdc, xStart, yStart, xEnd, yEnd);

	// Reset Original brush
	SelectObject(hdc, hOrg);
	DeleteObject(hBrush);
}

void createCars(HDC hdc, int xPos, int yPos, int angle) {
	// Creates a drawing context in memory
	//NB, is this the best placement for these?
	HDC hdcMem = CreateCompatibleDC(hdc);
	//Create new bitmap
	// CreateCompatibleBitmap(hdc, xdim, ydim);
	HBITMAP memBM = CreateCompatibleBitmap(hdc, 1000, 1000);
	// Adds the bitmap to the memory drawing context to create a drawing surface
	SelectObject(hdcMem, memBM);
	FloodFill(hdcMem, 0, 0, RGB(255, 255, 255));

	// Load the bitmap
	HDC hdcCar = CreateCompatibleDC(hdc);
	HBITMAP bmCar = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1));
	SelectObject(hdcCar, bmCar);

	BitBlt(hdcMem, 0 + xPos, 100, 200, 500, hdcCar, 0, 0, SRCCOPY);
	BitBlt(hdcMem, 0 + xPos * 1.5, 200, 200, 500, hdcCar, 0, 0, SRCCOPY);
	BitBlt(hdcMem, 0 + xPos, 300, 200, 500, hdcCar, 0, 0, SRCCOPY);
	BitBlt(hdcMem, 0 + xPos * 2, 400, 200, 500, hdcCar, 0, 0, SRCCOPY);

	// Copy memory buffer to screen
	BitBlt(hdc, 0, 0, 1000, 1000, hdcMem, 0, 0, SRCCOPY);

	// Cleanup
	DeleteDC(hdcCar);
	DeleteDC(hdcMem);
	DeleteObject(memBM);
	DeleteObject(bmCar);
}