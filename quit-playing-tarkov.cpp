#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>
#include <ctime>

namespace fs = std::filesystem;

const char* TARKOV_LAUNCHER_NAME = "BsgLauncher";
const char* REGISTRY_KEY_NAME = "QuitPlayingTarkov";
const std::string CUSTOM_MESSAGES_FILE = "messages-quit-playing-tarkov.txt";

std::wstring ConvertToWString(const std::string& utf8String)
{
    if (utf8String.empty())
        return L"";

    int sizeNeeded = MultiByteToWideChar(CP_UTF8, 0, &utf8String[0], (int)utf8String.size(), NULL, 0);
    std::wstring utf16String(sizeNeeded, 0);

    MultiByteToWideChar(CP_UTF8, 0, &utf8String[0], (int)utf8String.size(), &utf16String[0], sizeNeeded);

    if (utf16String.length() < 60)
        utf16String += std::wstring(60 - utf16String.length(), L' ');

    return utf16String;
}

void AddToStartup()
{
    HKEY hKey;

    char pathBuffer[MAX_PATH];
    GetModuleFileNameA(NULL, pathBuffer, MAX_PATH);

    if (RegOpenKeyExA(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_SET_VALUE, &hKey) == ERROR_SUCCESS)
    {
        RegSetValueExA(hKey, REGISTRY_KEY_NAME, 0, REG_SZ, (const BYTE*)pathBuffer, (DWORD)(strlen(pathBuffer) + 1));
        RegCloseKey(hKey);
    }
}

std::vector<std::string> LoadMessages()
{
    std::vector<std::string> messagePool;

    char pathBuffer[MAX_PATH];
    GetModuleFileNameA(NULL, pathBuffer, MAX_PATH);

    fs::path currentDir = fs::path(pathBuffer).parent_path();
    fs::path filePath = currentDir / CUSTOM_MESSAGES_FILE;

    if (!fs::exists(filePath))
    {
        std::ofstream newFile(filePath);

        newFile << "# [CUSTOM MESSAGES FILE]" << std::endl;
        newFile << "# Each line below is a random message. '#' lines are ignored." << std::endl;
        newFile << "# ------------------------------------------------------------" << std::endl;
        newFile << "Stop wasting your time. (Edit messages-quit-playing-tarkov.txt)" << std::endl;
        newFile << "Your life on Earth is not infinite. (Edit messages-quit-playing-tarkov.txt)" << std::endl;
        newFile << "Quit playing! (Edit messages-quit-playing-tarkov.txt)" << std::endl;
        newFile.close();
    }

    std::ifstream file(filePath);
    std::string line;

    while (std::getline(file, line))
    {
        if (!line.empty() && line[0] != '#')
            messagePool.push_back(line);
    }

    return messagePool;
}

int main()
{
    srand(static_cast<unsigned int>(time(NULL)));

    AddToStartup();
    ShowWindow(GetConsoleWindow(), SW_HIDE);

    while (true)
    {
        HWND launcherWindow = FindWindowA(NULL, TARKOV_LAUNCHER_NAME);

        if (launcherWindow != NULL)
        {
            PostMessage(launcherWindow, WM_CLOSE, 0, 0);

            std::vector<std::string> messages = LoadMessages();
            std::string randomMessage = messages[rand() % messages.size()];

            MessageBoxW(NULL, ConvertToWString(randomMessage).c_str(), L"Quit Playing Tarkov", MB_OK | MB_ICONINFORMATION | MB_SYSTEMMODAL);
        }

        Sleep(3000);
    }

    return 0;
}