#include <Windows.h>

HHOOK _hook;
KBDLLHOOKSTRUCT kbdStruct;

BOOLEAN isEmulation;
BOOLEAN ReplaceButton(DWORD newButton) {
	if (isEmulation) {
		isEmulation = FALSE;
		return FALSE;
	}
	
	isEmulation = TRUE;

	keybd_event(newButton, 0, 0, 0);
	keybd_event(newButton, 0, KEYEVENTF_KEYUP, 0);
	
	return TRUE;
}

LRESULT __stdcall HookCallback(int nCode, WPARAM wParam, LPARAM lParam) {
	if (nCode >= 0 && (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN)) {
		kbdStruct = *((KBDLLHOOKSTRUCT*)lParam);
		switch (kbdStruct.vkCode) {
			case VK_VOLUME_MUTE:
				if (ReplaceButton(VK_F1)) return 1;
				break;
			case VK_F1:
				if (ReplaceButton(VK_VOLUME_MUTE)) return 1;
				break;

			case VK_VOLUME_DOWN:
				if (ReplaceButton(VK_F2)) return 1;
				break;
			case VK_F2:
				if (ReplaceButton(VK_VOLUME_DOWN)) return 1;
				break;

			case VK_VOLUME_UP:
				if (ReplaceButton(VK_F3)) return 1;
				break;
			case VK_F3:
				if (ReplaceButton(VK_VOLUME_UP)) return 1;
				break;

			case VK_MEDIA_PREV_TRACK:
				if (ReplaceButton(VK_F4)) return 1;
				break;
			case VK_F4:
				if (ReplaceButton(VK_MEDIA_PREV_TRACK)) return 1;
				break;

			case VK_MEDIA_PLAY_PAUSE:
				if (ReplaceButton(VK_F5)) return 1;
				break;
			case VK_F5:
				if (ReplaceButton(VK_MEDIA_PLAY_PAUSE)) return 1;
				break;

			case VK_MEDIA_NEXT_TRACK:
				if (ReplaceButton(VK_F6)) return 1;
				break;
			case VK_F6:
				if (ReplaceButton(VK_MEDIA_NEXT_TRACK)) return 1;
				break;

			case VK_BROWSER_BACK:
				if (ReplaceButton(VK_F7)) return 1;
				break;
			case VK_F7:
				if (ReplaceButton(VK_BROWSER_BACK)) return 1;
				break;

			case VK_BROWSER_HOME:
				if (ReplaceButton(VK_F8)) return 1;
				break;
			case VK_F8:
				if (ReplaceButton(VK_BROWSER_HOME)) return 1;
				break;

			case VK_APPS:
				if (ReplaceButton(VK_F9)) return 1;
				break;
			case VK_F9:
				if (ReplaceButton(VK_APPS)) return 1;
				break;

			// F10
			case VK_F21:
				if (!isEmulation) {
					isEmulation = TRUE;

					if (GetKeyState(VK_LWIN) & 0x8000)
						keybd_event(VK_LWIN, 0, KEYEVENTF_KEYUP, 0);

					if (GetKeyState(VK_LSHIFT) & 0x8000)
						keybd_event(VK_LSHIFT, 0, KEYEVENTF_KEYUP, 0);

					keybd_event(VK_F10, 0, 0, 0);
					keybd_event(VK_F10, 0, KEYEVENTF_KEYUP, 0);

					return 1;
				}
				else {
					isEmulation = FALSE;
				}
				break;
			case VK_F10:
				if (!isEmulation) {
					isEmulation = TRUE;

					keybd_event(VK_LSHIFT, 0, 0, 0);
					keybd_event(VK_LWIN, 0, 0, 0);

					keybd_event(VK_F21, 0, 0, 0);
					keybd_event(VK_F21, 0, KEYEVENTF_KEYUP, 0);

					keybd_event(VK_LSHIFT, 0, KEYEVENTF_KEYUP, 0);
					keybd_event(VK_LWIN, 0, KEYEVENTF_KEYUP, 0);

					return 1;
				}
				else {
					isEmulation = FALSE;
				}
				break;

			// F11
			case 0x9:
				if ((GetKeyState(VK_LCONTROL) & 0x8000) && (GetKeyState(VK_LMENU) & 0x8000)) {
					if (!isEmulation) {
						isEmulation = TRUE;

						keybd_event(VK_LCONTROL, 0, KEYEVENTF_KEYUP, 0);
						keybd_event(VK_LMENU, 0, KEYEVENTF_KEYUP, 0);

						keybd_event(VK_F11, 0, 0, 0);
						keybd_event(VK_F11, 0, KEYEVENTF_KEYUP, 0);

						return 1;
					}
					else {
						isEmulation = FALSE;
					}
				}
				break;
			case VK_F11:
				if (!isEmulation) {
					isEmulation = TRUE;

					keybd_event(VK_LCONTROL, 0, 0, 0);
					keybd_event(VK_LMENU, 0, 0, 0);

					keybd_event(0x9, 0, 0, 0);
					keybd_event(0x9, 0, KEYEVENTF_KEYUP, 0);

					keybd_event(VK_LCONTROL, 0, KEYEVENTF_KEYUP, 0);
					keybd_event(VK_LMENU, 0, KEYEVENTF_KEYUP, 0);

					return 1;
				}
				else {
					isEmulation = FALSE;
				}
				break;
		}
	}

	return CallNextHookEx(_hook, nCode, wParam, lParam);
}

void SetHook() {
	if (!(_hook = SetWindowsHookEx(WH_KEYBOARD_LL, HookCallback, NULL, 0))) {
		MessageBox(NULL, TEXT("Failed to install ThinkPad Compact Bluetooth Keyboard with TrackPoint hot key switch hook"), TEXT("Error"), MB_ICONERROR);
	}
}

void ReleaseHook() {
	UnhookWindowsHookEx(_hook);
}

void main() {
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	SetHook();

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {

	}
}
