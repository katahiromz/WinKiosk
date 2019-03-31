# WinKiosk by katahiromz

WinKiosk is a freeware information kiosk terminal for Windows.
It works in Windows XP/Vista/7/10.

## Composition

WinKiosk consists of SimpleBrowser and KeybdSystem.
SimpleBrowser is a Web browser.
KeybdSystem is an on-screen keyboard system.

WinKiosk will start up SimpleBrowser in kiosk mode.
You can launch KeybdSystem by pressing the "Keyboard" button on SimpleBrowser.

## Shortcut keys

On SimpleBrowser, you can toggle kiosk mode by pressing Ctrl+K.
On SimpleBrowser, you can exit SimpleBrowser by pressing Alt+F4.
On SimpleBrowser, you can display the SimpleBrowser's menu by pressing Alt+F.

You have to remember Alt+F4, Ctrl+K and Alt+F.

| Key Combination | Command            |
|-----------------|--------------------|
| Ctrl+R          | Refresh            |
| F5              | Refresh            |
| Alt+Left        | History Back       |
| Alt+Right       | History Forward    |
| Alt+Home        | Go Home            |
| Esc             | Stop               |
| Alt+D           | Go To Address Bar  |
| Ctrl+P          | Print...           |
| Shift+Ctrl+P    | Print!             |
| Ctrl+U          | View Source        |
| Alt+F           | Show Menu          |
| Ctrl+N          | New Window         |
| Ctrl+K          | Toggle Kiosk Mode  |
| Alt+F4          | Exit SimpleBrowser |

## Initial settings

After installing WinKiosk with the installer, it's ready for kiosk terminal.

When you restart Windows, WinKiosk will be launched automatically.

The button layout of SimpleBrowser is customizable by editing the following text files:

    Upside_en.txt
    Downside_en.txt
    LeftSide_en.txt
    RightSide_en.txt

## Security

If you want to use it as an information kiosk terminal, you might have to delete the useless printers.

In kiosk mode, the dotted menu ("...") and print preview are not available for security reason.

If you start using this software as kiosk terminal, please disconnect the physical keyboard.
