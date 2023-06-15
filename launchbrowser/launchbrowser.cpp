// launchbrowser.cpp : Defines the entry point for the application.
//

#include "framework.h"

#include "../../lsMisc/CommandLineString.h"
#include "../../lsMisc/GetVersionString.h"
#include "../../lsMisc/OpenCommon.h"
#include "../../lsMisc/HighDPI.h"
#include "../../lsMisc/stdosd/stdosd.h"

#include "launchbrowser.h"

#define APPNAME L"launchbrowser"
#define I18N(s) s

#pragma comment(lib, "shlwapi.lib")

using namespace std;
using namespace Ambiesoft;
using namespace Ambiesoft::stdosd;

wstring getTitleString()
{
    return stdFormat(L"%s v%s",
        APPNAME,
        GetVersionString(nullptr, 3).c_str());
}

void showHelp()
{
    wstring message;
    MessageBox(nullptr,
        message.c_str(),
        getTitleString().c_str(),
        MB_ICONINFORMATION);
}
void showErrorAndExit(const wstring errorMessage)
{
    MessageBox(nullptr,
        errorMessage.c_str(),
        getTitleString().c_str(),
        MB_ICONERROR);
    exit(1);
}
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    
    InitHighDPISupport();

    wstring mainArg;
    CCommandLineString cmdLine;
    for (size_t i = 1; i < cmdLine.getCount(); ++i)
    {
        const wstring arg = cmdLine.getArg(i);
        if(false){}
        else if (arg == L"--help" || arg == L"-h" || arg == L"/?")
        {
            showHelp();
            return 0;
        }
        else if (stdStartWith(arg, L"-"))
        {
            showErrorAndExit(I18N(L"Unkown option:") + arg);
        }
    }

    if (mainArg.empty())
    {
        showErrorAndExit(I18N(L"No main argument specified"));
    }

    OpenCommon(nullptr,
        mainArg.c_str());

    return 0;
}
