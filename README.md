# ThinkPad-Bluetooth-Keyboard-Hotkey-Switch
Switch between the hot key and the standard F1-F12 function for ThinkPad Compact Bluetooth Keyboard with TrackPoint (4X30K12182).

https://support.lenovo.com/ru/en/solutions/pd026744

## Why
ThinkPad Compact Bluetooth Keyboard with TrackPoint do not support "Fn Lock" (at last 4X30K12182). So users cannot use standard F1-F12 function without pressing Fn. This project fix this.

## How to use
Place ThinkPadBluetoothKeyboardHotkeySwitch.exe to windows startup folder. This will switch F1-F12 functions to default, to use special functions press Fn+[F1-F12]. 

Change which apps run automatically at startup in Windows 10

https://support.microsoft.com/en-us/help/4026268/windows-10-change-startup-apps

Tested on Windows 10 x64. Should work for x32 too.

## How it works
ThinkPadBluetoothKeyboardHotkeySwitch.exe create a hook that process keyboard events. You can see ThinkPadBluetoothKeyboardHotkeySwitch.exe in task manager.

## Known issue
F12 button behavior did not change.
