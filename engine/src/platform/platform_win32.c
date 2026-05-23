#if PLATFORM_WINDOWS

#define WIN32_LEAN_AND_MEAN 
#pragma warning(push)
#pragma warning(disable : 4042)
#include <windows.h>
#include <windowsx.h>
#include <timeapi.h>
#pragma warning(pop)
////////////////////////////////////////////////////////////////
//~ Sebas: Win32 Types

typedef struct PlatformState PlatformState;
struct PlatformState
{
    HINSTANCE instance;
    HWND window;
};

////////////////////////////////////////////////////////////////
//~ Sebas: Time Global Variables
global LARGE_INTEGER frequency;
global TimeStamp start_time;

LRESULT CALLBACK win32_process_messages(HWND window, U32 msg, WPARAM w_param, LPARAM l_param);

////////////////////////////////////////////////////////////////
//~ Sebas: Winodw Life-Time Management Functions

function B8    
platform_startup(PlatformHandle* platform_handle, 
                 const char* app_name, 
                 S32 x, S32 y, 
                 S32 width, S32 height)
{
    B8 result = FALSE;
    
    platform_handle->state = malloc(sizeof(PlatformState));
    PlatformState* state = platform_handle->state;
    
    state->instance = GetModuleHandleA(0);
    
    //HICON icon = LoadIcon(state->instance, IDI_APPLICATION);
    WNDCLASSA wnd_class = {};
    wnd_class.style = CS_DBLCLKS;
    wnd_class.lpfnWndProc = win32_process_messages;
    wnd_class.cbClsExtra = 0;
    wnd_class.cbWndExtra = 0;
    wnd_class.hInstance = state->instance;
    wnd_class.hIcon = LoadIcon(state->instance, IDI_APPLICATION);
    wnd_class.hCursor = LoadCursor(state->instance, IDC_ARROW);
    wnd_class.hbrBackground = NULL;
    wnd_class.lpszClassName = "sidus_window_class";
    
    if (RegisterClassA(&wnd_class) != 0)
    {
        U32 client_x = x;
        U32 client_y = y;
        U32 client_width = width;
        U32 client_height = height;
        
        U32 window_style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU;
        U32 window_extended_style = WS_EX_APPWINDOW;
        
        window_style |= WS_MINIMIZEBOX;
        window_style |= WS_MAXIMIZEBOX;
        window_style |= WS_THICKFRAME;
        
        
#if 0
        RECT rect = {};
        rect.left = client_x;
        rect.top = client_y;
        rect.right = client_x + client_width;
        rect.bottom = client_y + client_height;
        AdjustWindowRectEx(&rect, window_style, FALSE, window_extended_style);
        U32 window_x = rect.left;
        U32 window_y = rect.top;
        U32 window_width = rect.right - rect.left;
        U32 window_height= rect.bottom - rect.top;
#else
        RECT border_rect = {};
        AdjustWindowRectEx(&border_rect, window_style, FALSE, window_extended_style);
        U32 window_x = border_rect.left + client_x;
        U32 window_y = border_rect.top + client_y;
        U32 window_width = client_width + border_rect.right - border_rect.left;
        U32 window_height = client_height + border_rect.bottom - border_rect.top;
#endif
        
        
        
        
        HWND window = CreateWindowExA(window_extended_style,
                                      "sidus_window_class",
                                      app_name, window_style, 
                                      window_x, window_y,
                                      window_width, window_height,
                                      NULL, NULL, state->instance, NULL);
        
        if (window != 0)
        {
            state->window = window;
            
            B32 should_activate = TRUE;
            S32 show_window_cmd_flags = should_activate ? SW_SHOW : SW_SHOWNOACTIVATE;
            
            ShowWindow(state->window, show_window_cmd_flags);
            
            QueryPerformanceFrequency(&frequency);
            timeBeginPeriod(1);
            start_time = platform_create_time_stamp();
            
            result = TRUE;
        }
        else
        {
            MessageBoxA(0, "Window Creation Failed!", "Error!",MB_ICONEXCLAMATION | MB_OK);
            state->window = NULL;
            SFATAL_LIT("Window Creation Failed!");
            result = FALSE;
        }
    }
    else
    {
        MessageBoxA(0, "Window Registration Failed!", "Error!",MB_ICONEXCLAMATION | MB_OK);
        SFATAL_LIT("Window Registration Failed!");
        result = FALSE;
    }
    
    if (result == FALSE)
    {
        SFATAL_LIT("Failed Platform Startup!");
    }
    return result;
}

function void
platform_shutdown(PlatformHandle platform_handle)
{
    PlatformState* state = (PlatformState*)platform_handle.state;
    if (state->window)
    {
        DestroyWindow(state->window);
        state->window = NULL;
        timeEndPeriod(1);
    }
    
}

////////////////////////////////////////////////////////////////
//~ Sebas: Win32 Memory Functions

function void* 
platform_memory_reserve(U64 size)
{
    return malloc(size);
}

function void  
platform_memory_commit(void* ptr, U64 size)
{
    UnusedVariable(ptr);
    UnusedVariable(size);
}

function void  
platform_memory_decommit(void* ptr, U64 size)
{
    UnusedVariable(ptr);
    UnusedVariable(size);
}

function void  
platform_free(void* ptr)
{
    free(ptr);
}

////////////////////////////////////////////////////////////////
//~ Sebas: Win32 Logging Functions
function void  
platform_console_write(const char* message, U8 colour)
{
    HANDLE console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    local U8 levels[LOG_LEVEL_COUNT] = {64, 4, 6, 2, 1, 8};
    SetConsoleTextAttribute(console_handle, levels[colour]);
    OutputDebugStringA(message);
    U64 length = strlen(message);
    LPDWORD count = 0;
    WriteConsoleA(GetStdHandle(STD_OUTPUT_HANDLE), message, (DWORD)length, count, 0);
}

function void  
platform_console_write_error(const char* message, U8 colour)
{
    HANDLE console_handle = GetStdHandle(STD_ERROR_HANDLE);
    local U8 levels[LOG_LEVEL_COUNT] = {64, 4, 6, 2, 1, 8};
    SetConsoleTextAttribute(console_handle, levels[colour]);
    OutputDebugStringA(message);
    U64 length = strlen(message);
    LPDWORD count = 0;
    WriteConsoleA(GetStdHandle(STD_ERROR_HANDLE), message, (DWORD)length, count, 0);
}

////////////////////////////////////////////////////////////////
//~ Sebas: Win32 Time Functions

function TimeStamp   
platform_create_time_stamp()
{
    TimeStamp time_stamp = {};
    LARGE_INTEGER counter = {};
    QueryPerformanceCounter(&counter);
    time_stamp.win32_counter = (U64)counter.QuadPart;
    return time_stamp;
}

function F64   
platform_seconds_elapsed(TimeStamp start, TimeStamp end)
{
    F64 result = 0;
    result = (F64)(end.win32_counter - start.win32_counter) / (F64)frequency.QuadPart;
    return result;
}

function F64   
platform_get_absolute_time()
{
    F64 result = 0;
    LARGE_INTEGER now_time = {};
    QueryPerformanceCounter(&now_time);
    result = (F64)((U64)now_time.QuadPart - start_time.win32_counter) / (F64)frequency.QuadPart;
    return result;
}

function void  
platform_sleep(U64 ms)
{
    
    // TODO(Sebas): Rounding
    Sleep((DWORD)ms);
}


////////////////////////////////////////////////////////////////
//~ Sebas: Win32 Message Functions

function B8    
platform_pump_messages(PlatformHandle platform_handle)
{
    UnusedVariable(platform_handle);
    MSG message;
    while(PeekMessageA(&message, NULL, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&message);
        DispatchMessageA(&message);
    }
    return TRUE;
}

LRESULT CALLBACK 
win32_process_messages(HWND window, U32 msg, WPARAM w_param, LPARAM l_param)
{
    LRESULT result = 0;
    switch(msg)
    {
        case WM_ERASEBKGND:
        {
            result = 1;
        } break;
        case WM_CLOSE:
        {
            // TODO(Sebas): Fire an event for the application to quit.
        } break;
        case WM_DESTROY:
        {
            PostQuitMessage(0);
        } break;
        case WM_SIZE:
        {
            RECT r;
            GetClientRect(window, &r);
            S32 width = r.right - r.left;
            S32 height = r.bottom - r.top;
            UnusedVariable(width);
            UnusedVariable(height);
            
            // TODO(Sebas): Fire an event for window resize.
        } break;
        case WM_KEYDOWN:
        case WM_SYSKEYDOWN:
        case WM_KEYUP:
        case WM_SYSKEYUP:
        {
            U8 vkcode = (U8)w_param;
            B8 is_repeat = (l_param & (1 << 30)) != 0;
            B8 is_up = (l_param & (1 << 31)) != 0;
            B8 released = is_up;
            B8 pressed = !is_up && !is_repeat;
            UnusedVariable(vkcode);
            UnusedVariable(released);
            UnusedVariable(pressed);
            /*if (pressed)
            {
                pressed_event.down_time_stamp = platform_create_time_stamp();
            }
            else if (released)
            {
                released_event.release_time_stamp = platform_create_time_stamp();
            }*/
            // TODO(Sebas): Input Processing.
        } break;
        case WM_MOUSEMOVE:
        {
            S32 mouse_x = GET_X_LPARAM(l_param);
            S32 mouse_y = GET_Y_LPARAM(l_param);
            UnusedVariable(mouse_x);
            UnusedVariable(mouse_y);
            // TODO(Sebas): Input Processing.
        } break;
        case WM_MOUSEWHEEL:
        {
            S16 raw_delta = GET_WHEEL_DELTA_WPARAM(w_param);
            F32 wheel_delta = (F32)raw_delta / (F32)WHEEL_DELTA;
            
            S32 screen_x = GET_X_LPARAM(l_param);
            S32 screen_y = GET_Y_LPARAM(l_param);
            
            // 3. Convert screen coordinates to your local window client coordinates
            POINT client_point = { screen_x, screen_y };
            ScreenToClient(window, &client_point);
            
            S32 mouse_x = client_point.x;
            S32 mouse_y = client_point.y;
            
            UnusedVariable(mouse_x);
            UnusedVariable(mouse_y);
            UnusedVariable(wheel_delta);
            
            // TODO(Sebas): Input Processing.
        } break;
        case WM_LBUTTONDOWN: 
        case WM_RBUTTONDOWN: 
        case WM_MBUTTONDOWN:
        case WM_LBUTTONUP:   
        case WM_RBUTTONUP:   
        case WM_MBUTTONUP:
        {
            U8 vkcode = 0;
            B8 is_up = FALSE;
            
            // Map the Win32 message to your existing U8 vkcode space
            switch (msg)
            {
                case WM_LBUTTONDOWN: { vkcode = VK_LBUTTON; is_up = FALSE; } break;
                case WM_LBUTTONUP:   { vkcode = VK_LBUTTON; is_up = TRUE;  } break;
                case WM_RBUTTONDOWN: { vkcode = VK_RBUTTON; is_up = FALSE; } break;
                case WM_RBUTTONUP:   { vkcode = VK_RBUTTON; is_up = TRUE;  } break;
                case WM_MBUTTONDOWN: { vkcode = VK_MBUTTON; is_up = FALSE; } break;
                case WM_MBUTTONUP:   { vkcode = VK_MBUTTON; is_up = TRUE;  } break;
            }
            
            // Windows mouse messages do not natively auto-repeat like keys
            B8 is_repeat = FALSE; 
            B8 released = is_up;
            B8 pressed = !is_up;
            UnusedVariable(is_repeat);
            UnusedVariable(released);
            UnusedVariable(pressed);
        } break;
        default:
        {
            result = DefWindowProc(window, msg, w_param, l_param);
        } break;
    }
    
    UnusedVariable(window);
    UnusedVariable(msg);
    UnusedVariable(w_param);
    UnusedVariable(l_param);
    return result;
}

#endif