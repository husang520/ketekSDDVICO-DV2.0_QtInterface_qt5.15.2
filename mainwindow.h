#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <windows.h>
#include <QString>
#include <QCoreApplication>
#include <QDebug>
#include <QProcess>
#include <QFile>
#include <QtWidgets/QMessageBox>
#include <QTimer>
#include <QLabel>
#include <QProgressBar>
#include <QThread>
#include <QLibrary>
#include <QDir>
#include <QDateTime>
#include <QFile>
#include <QTextStream>


#include <./VICOLib_impl/vicolib.h>
#include <./VICOLib_impl/types.h>
#include <vicolibrary.h>
#include <structdef.h>

// 定义为 QString 类型
const QString VICODaemonServiceName = "VICODaemon";  // 或者 "VICODaemon" 根据实际服务名修改


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void connectMenuAction(const QString &actionName, void (MainWindow::*slot)());
    SC_HANDLE openServiceHandle(const QString &serviceName, DWORD access);
    SERVICE_STATUS_PROCESS getServiceStatus(SC_HANDLE hService);
    void startVICODaemonService();
    void stopVICODaemonService();
    void setupMenuConnections();
    void setupStatusBar();
    void setupUI();
    void setupConnections();
    void setupTimer();

    void updateServiceStatus(const QString &status);

    void infoOutput(const QString &info);

    QString getSerialNumber();

    void scanAndGetDeviceInfo();
    void refreshDeviceInfo();
    void getMCUStatus();

    void onRunTimerTimeout();

    void setPeakingTime();
    void setMeasureTime();
    void startRun();

    void saveMCAToFile(const UInt32Type* mcaData, int numberOfBins);

    void updateUI();




private:
    Ui::MainWindow *ui;

    QLabel *serviceStatusLabel;
    QProgressBar *progressBar;
    QLabel *otherInfoLabel;

    VicoLibrary* vicolib;

    QTimer *m_runTimer = nullptr;
    VICOLib_DeviceContext vico_ctx = {0};

    QTimer *m_liveTimer = nullptr;



};
#endif // MAINWINDOW_H
