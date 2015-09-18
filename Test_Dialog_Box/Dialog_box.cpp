
#include <windows.h>
#include <tchar.h>    
//#include <string>
#define IDCC_DROPDOWNLIST	200
#define IDC_COMBOBOX		201
#define IDC_BUTTON1			202
#define IDC_BUTTON2			203
#define ID_EDITCHILD		204


const char g_szClassName[] = "myWindowClass";

// Step 4: the Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {

		// Sent when an application requests that a window be created by calling the any Createwindow fn.
		// The window procedure of the new window receives this message after the window is 
		// created, but before the window becomes visible.
		case WM_CREATE:
			{
			// this is for combo box
			HWND hCombo = CreateWindowEx(0,                            //extended styles
                      _T("combobox"),               //control 'class' name
                      "Combo_Box",              //control caption
                      CBS_DROPDOWNLIST | WS_CHILD|WS_VISIBLE,                      //control style 
                      0,                      //position: left
                      0,                       //position: top
                      500,                     //width
                      300,                    //height
                      hwnd,                      //parent window handle
                      //control's ID
                      reinterpret_cast<HMENU>(static_cast<INT_PTR>(IDCC_DROPDOWNLIST)),
                      GetModuleHandle(NULL),                        //application instance
                      0);
				
			if(hCombo == NULL)
				{
					DWORD errCode = GetLastError();
					char* err;
					FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
						NULL,
						errCode,
						MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // default language
						(LPTSTR) &err,
						0,
						NULL);
					MessageBox(hwnd,err,"Error while creating combo box!",0);
			}
			else{
				UINT res = static_cast<UINT>(SendMessage(hCombo, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>("Bengali")));
				res = static_cast<UINT>(SendMessage(hCombo, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>("English")));
				res = static_cast<UINT>(SendMessage(hCombo, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>("Hindi")));
			}
			

			// This is for My choice button
			if(!CreateWindow(TEXT("button"), 
				TEXT("My Choice"),
				WS_VISIBLE | WS_CHILD ,
				20, 
				50, 
				95, 
				25, 
				hwnd,
				//NULL,
				reinterpret_cast<HMENU>(static_cast<INT_PTR>(IDC_BUTTON1)), 
				NULL, 
				NULL))
				{
					DWORD errCode = GetLastError();
					char* err;
					FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
						NULL,
						errCode,
						MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // default language
						(LPTSTR) &err,
						0,
						NULL);
					MessageBox(hwnd,err,"Error while creating my choice button!",0);
			}

			// This is for OK button
			if(!CreateWindow(TEXT("button"), 
				TEXT("Exit"),
				WS_VISIBLE | WS_CHILD ,
				20, 
				150, 
				95, 
				25, 
				hwnd,  
				//NULL,
				reinterpret_cast<HMENU>(static_cast<INT_PTR>(IDC_BUTTON2)), 
				NULL, 
				NULL))
				{
					DWORD errCode = GetLastError();
					char* err;
					FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
						NULL,
						errCode,
						MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // default language
						(LPTSTR) &err,
						0,
						NULL);
					MessageBox(hwnd,err,"Error while creating OK button!",0);
			}
			
			// this is for Edit control which will show the information related to the user's selection
			HWND hwndEdit = CreateWindowEx(
				0, "EDIT",   // predefined class 
				NULL,         // no window title 
				WS_CHILD | WS_VISIBLE | WS_VSCROLL | 
				ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL, 
				200, 
				50, 
				200, 
				100,   // set size in WM_SIZE message 
				hwnd,         // parent window 
				(HMENU) ID_EDITCHILD,   // edit control ID 
				(HINSTANCE) GetWindowLong(hwnd, GWL_HINSTANCE), 
				NULL);
			if(hwndEdit == NULL)
			{
				DWORD errCode = GetLastError();
				char* err;
				FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
					NULL,
					errCode,
					MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // default language
					(LPTSTR) &err,
					0,
					NULL);
				MessageBox(hwnd,err,"Error while creating Edit control box!",0);
			}

            // Add text to the window. 
			else
				SendMessage(hwndEdit, WM_SETTEXT, 0, (LPARAM)"Information about the language of your choice will be shown here."); 
			}
		break;

		// Sent when the user selects a command item from a menu, when a control 
		// sends a notification message to its parent window
		case WM_COMMAND:	
			
            switch(HIWORD(wParam))
            {
			case BN_CLICKED:
				{
					switch(LOWORD(wParam)){
					case IDC_BUTTON1:
						{
							//int nIndex;
							char pFilename[_MAX_PATH];
							HWND hCombo = GetDlgItem(hwnd, IDCC_DROPDOWNLIST );
							int nIndex = SendMessage( hCombo, CB_GETCURSEL, 0, 0 );
							SendMessage(hCombo , CB_GETLBTEXT, nIndex, (LPARAM)pFilename );

							HWND hwndEdit = GetDlgItem(hwnd, ID_EDITCHILD);
							if(nIndex == CB_ERR)
								MessageBox(hwnd, "You did not select anything from drop-down list", "Attention:", MB_OK | MB_ICONINFORMATION);
							else{
								char* pMessage = new char[100];

								if(strcmp(pFilename, "Bengali") == 0)
									strcpy_s(pMessage, 99, "Bengali is spoken in WB.");

								else if(strcmp(pFilename, "English") == 0)
									strcpy_s(pMessage, 99, "English is the international language.");
								else 
									strcpy_s(pMessage, 99, "Hindi is the national language.");

								SendMessage(hwndEdit, WM_SETTEXT, 0, (LPARAM)pMessage);
								//MessageBox(hwnd,pFilename,"You have chosen:",0);
								delete[] pMessage;
							}

						}
					break;

					case IDC_BUTTON2:
						{
							DestroyWindow(hwnd);
						}
						break;
               
            }
			break;
			}
			
			}
			break;

		// Sent as a signal that a window or an application should terminate.
		// This msg is received from WndProc
        case WM_CLOSE:
            DestroyWindow(hwnd);
        break;

		// Sent when a window is being destroyed. It is sent to the window procedure
		// of the window being destroyed after the window is removed from the screen. 
        case WM_DESTROY:
            PostQuitMessage(0);
        break;

		// Calls the default window procedure to provide default processing for any 
		// window messages that an application does not process. This function ensures 
		// that every message is processed.
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSEX wc;
    HWND hwnd;
    MSG Msg;

    //Step 1: Registering the Window Class
    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = 0;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;			// Window class name alone can't identify the class uniquely. So HINSTANCE is needed. It's a handle to an instance which is the base address of the module in memory.
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = g_szClassName;
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

	// Registering our window class
    if(!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "Window Registration Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }
	
    // Step 2: Creating the Window
    hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        g_szClassName,
        "Combo Box Example",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 500, 300,
        NULL, NULL, hInstance, NULL);

    if(hwnd == NULL)
    {
        MessageBox(NULL, "Window Creation Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

	// Here WndProc is called with the message WM_CREATE to create all the controls/windows that the application wants to create

	// Displaying window. ShowWindow shows the window on the screen, it sends the WM_PAINT message to the window procedure. 
	// nCmdShow  is used to keep track of the current state of the window (maximized, minimized, etc). 
    ShowWindow(hwnd, nCmdShow);

	//updates the client area of the specified window by sending a WM_PAINT message to the window.
	// Did not give any problem when it was commented
    UpdateWindow(hwnd); 

    // Step 3: The Message Loop. We used NULL as we want to retrieve all messages.
    while(GetMessage(&Msg, NULL, 0, 0) > 0)
    {
		// Translates virtual-key messages into character messages. The character messages are posted to 
		// the calling thread's message queue, to be read the next time the thread calls the GetMessage()
        TranslateMessage(&Msg);

		// DispatchMessage() function call sends the message to the window procedure
        DispatchMessage(&Msg);

		// Why is it failing?
		//WNDPROC fWndProc = (WNDPROC)GetWindowLong(Msg.hwnd, GWL_WNDPROC);
		//fWndProc(Msg.hwnd, Msg.message, Msg.wParam, Msg.lParam);
    }
    return Msg.wParam;
}