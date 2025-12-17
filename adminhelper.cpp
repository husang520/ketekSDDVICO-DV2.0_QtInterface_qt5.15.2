#include "adminhelper.h"
#include <QCoreApplication>
#include <QDebug>
#include <QtWidgets/QMessageBox>

bool isRunAsAdmin()
{
    BOOL fIsRunAsAdmin = FALSE;
    PSID pAdministratorsGroup = NULL;

    SID_IDENTIFIER_AUTHORITY NtAuthority = SECURITY_NT_AUTHORITY;
    if (AllocateAndInitializeSid(&NtAuthority, 2,
                                 SECURITY_BUILTIN_DOMAIN_RID,
                                 DOMAIN_ALIAS_RID_ADMINS,
                                 0,0,0,0,0,0,
                                 &pAdministratorsGroup))
    {
        CheckTokenMembership(NULL, pAdministratorsGroup, &fIsRunAsAdmin);
        FreeSid(pAdministratorsGroup);
    }

    return fIsRunAsAdmin;
}

bool restartAsAdmin()
{
    QString exePath = QCoreApplication::applicationFilePath().replace("/", "\\");

    SHELLEXECUTEINFO sei = { sizeof(sei) };
    sei.lpVerb = L"runas"; // 请求管理员权限
    sei.lpFile = (LPCWSTR)exePath.utf16();
    sei.lpParameters = L"";
    sei.lpDirectory = (LPCWSTR)QCoreApplication::applicationDirPath().utf16(); // 工作目录
    sei.nShow = SW_NORMAL;

    if (!ShellExecuteEx(&sei))
    {
        DWORD dwError = GetLastError();
        qDebug() << "Failed to restart as admin. Error:" << dwError;
        return false;
    }

    return true;
}
