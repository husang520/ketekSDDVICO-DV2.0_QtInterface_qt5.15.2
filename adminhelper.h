#ifndef ADMINHELPER_H
#define ADMINHELPER_H

#include <windows.h>
#include <QString>

bool isRunAsAdmin();
bool restartAsAdmin();
bool startService(const QString &serviceName);

#endif // ADMINHELPER_H
