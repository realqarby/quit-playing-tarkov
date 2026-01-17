# 🐀 Quit Playing Tarkov

_You need to study, but you can't stop raiding._

This stops you from playing Tarkov during exam weeks without the hassle of uninstalling and re-downloading 40GB later.

The tool runs in the background. If you try to launch **Escape from Tarkov**, it **kills the process** and displays a random message from a text file to remind you of your priorities.

## 🚀 How to Use

1. Extract the files to a folder.
2. Run **`quit-playing-tarkov.exe`** **once**.
3. Done. It now runs automatically on startup.

> **Note:** If you move the `.exe` to a new folder, run it again to update the startup path.

## 💬 Custom Messages

* Open the included `.txt` file.
* Write your messages (one per line).
* The app picks a random line every time it blocks the game.
## 🛡️ Antivirus Warnings (False Positives)

Your antivirus (e.g., Windows Defender) might flag this file. **This is normal.**

* **Why?** The program modifies the Registry (to auto-start) and forcibly kills other processes (the game). Antiviruses find this suspicious.
* **Safety:** This project is **Open Source**. There is no network code or malware. Feel free to inspect the `.cpp` source code yourself.

## 🗑️ Uninstall

To play again:
1. Run **`uninstall.bat`**.
2. Delete the folder.
