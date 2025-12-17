#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , serviceStatusLabel(nullptr)
    , progressBar(nullptr)
    , otherInfoLabel(nullptr)
    , vicolib(nullptr)
{
    ui->setupUi(this);
    vicolib = new VicoLibrary("VICOLib2");  // 加载 dll 文件

    setupMenuConnections();
    setupStatusBar();
    setupUI();
    setupConnections();



}

MainWindow::~MainWindow()
{
    delete ui;

    delete vicolib;  // 清理 QLibrary 对象

}

void MainWindow::connectMenuAction(const QString &actionName, void (MainWindow::*slot)())
{
    QAction *action = findChild<QAction *>(actionName);
    if (action) {
        connect(action, &QAction::triggered, this, slot);
    } else {
        qDebug() << "Action " << actionName << " not found!";
    }
}


// 封装获取服务控制管理器和服务句柄的函数
SC_HANDLE MainWindow::openServiceHandle(const QString &serviceName, DWORD access)
{
    // 获取服务控制管理器句柄
    SC_HANDLE hSCManager = OpenSCManager(nullptr, nullptr, SC_MANAGER_CONNECT);
    if (hSCManager == nullptr) {
        DWORD dwError = GetLastError();
        qDebug() << "Failed to open service control manager. Error:" << dwError;
        QMessageBox::critical(this, "Error", "Failed to open service control manager.");
        return nullptr;
    }

    // 打开服务
    SC_HANDLE hService = OpenService(hSCManager, serviceName.toStdWString().c_str(), access);
    if (hService == nullptr) {
        DWORD dwError = GetLastError();
        qDebug() << "Failed to open service. Error:" << dwError;
        CloseServiceHandle(hSCManager);
        QMessageBox::critical(this, "Error", "Failed to open service.");
        return nullptr;
    }

    return hService;
}

// 封装查询服务状态的函数
SERVICE_STATUS_PROCESS MainWindow::getServiceStatus(SC_HANDLE hService)
{
    SERVICE_STATUS_PROCESS serviceStatus;
    DWORD bytesNeeded;

    // 查询服务状态
    if (!QueryServiceStatusEx(hService, SC_STATUS_PROCESS_INFO, (LPBYTE)&serviceStatus, sizeof(SERVICE_STATUS_PROCESS), &bytesNeeded)) {
        DWORD dwError = GetLastError();
        qDebug() << "Failed to query service status. Error:" << dwError;
        CloseServiceHandle(hService);
        QMessageBox::critical(this, "Error", "Failed to query service status.");
        return serviceStatus;  // 默认返回未初始化的 serviceStatus
    }

    return serviceStatus;
}

// 启动 VICODaemon 服务
void MainWindow::startVICODaemonService()
{
    // 获取当前目录
    QString currentDir = QCoreApplication::applicationDirPath();
    QString vicodaemonDir = currentDir + "/VICODaemon";
    //qDebug() << " currentDir: " << currentDir;

    // 检查 VICODaemon 文件夹是否存在
    QDir dir(vicodaemonDir);
    if (!dir.exists()) {
        // 如果文件夹不存在，提示用户
        QMessageBox::warning(this, "错误", "当前目录下没有找到 VICODaemon 文件夹！");
        return;
    }

    // 如果文件夹存在，使用管理员权限运行 VICODaemon_start.cmd
    QString command = currentDir + "/VICODaemon/VICODaemon_start.cmd";

    // 使用 QProcess 启动命令并请求以管理员身份运行
    QProcess *process = new QProcess(this);
    QString program = "powershell";
    QStringList arguments;
    arguments << "-Command" << "Start-Process cmd.exe -ArgumentList '/c, " + command + "' -Verb RunAs";

    process->start(program, arguments);
    if (!process->waitForStarted()) {
        QMessageBox::critical(this, "错误", "无法启动 VICODaemon 服务！");
        updateServiceStatus("Failed to start!");  // 在状态栏更新信息
    } else {
        QMessageBox::information(this, "成功", "VICODaemon 服务已启动！");
        updateServiceStatus("started!");  // 在状态栏更新信息
    }

    // SC_HANDLE hService = openServiceHandle(VICODaemonServiceName, SERVICE_QUERY_STATUS | SERVICE_START);
    // if (hService == nullptr) {
    //     return;  // 打开服务失败
    // }

    // // 查询服务状态
    // SERVICE_STATUS_PROCESS serviceStatus = getServiceStatus(hService);
    // if (serviceStatus.dwCurrentState == SERVICE_RUNNING) {
    //     qDebug() << "VICODaemon service is already running.";
    //     updateServiceStatus("Already Running");  // 在状态栏更新信息
    //     CloseServiceHandle(hService);
    //     return;  // 服务已在运行，无需启动
    // }

    // // 如果服务没有运行，尝试启动它
    // if (!StartService(hService, 0, nullptr)) {
    //     DWORD dwError = GetLastError();
    //     qDebug() << "Failed to start VICODaemon service. Error:" << dwError;
    //     updateServiceStatus("Failed to start");  // 在状态栏更新信息
    //     CloseServiceHandle(hService);
    //     QMessageBox::critical(this, "Error", "Failed to start VICODaemon service.");
    //     return;
    // }

    // qDebug() << "VICODaemon service started successfully.";
    // updateServiceStatus("Started");  // 在状态栏更新信息

    // CloseServiceHandle(hService);
    // // QMessageBox::information(this, "Success", "VICODaemon service started successfully.");
}

// 停止 VICODaemon 服务
void MainWindow::stopVICODaemonService()
{
    // 获取当前目录
    QString currentDir = QCoreApplication::applicationDirPath();
    QString vicodaemonDir = currentDir + "/VICODaemon";
    //qDebug() << " currentDir: " << currentDir;

    // 检查 VICODaemon 文件夹是否存在
    QDir dir(vicodaemonDir);
    if (!dir.exists()) {
        // 如果文件夹不存在，提示用户
        QMessageBox::warning(this, "错误", "当前目录下没有找到 VICODaemon 文件夹！");
        return;
    }

    // 如果文件夹存在，使用管理员权限运行 VICODaemon_stop.cmd
    QString command = currentDir + "/VICODaemon/VICODaemon_stop.cmd";

    // 使用 QProcess 启动命令并请求以管理员身份运行
    QProcess *process = new QProcess(this);
    QString program = "powershell";
    QStringList arguments;
    arguments << "-Command" << "Start-Process cmd.exe -ArgumentList '/c, " + command + "' -Verb RunAs";

    process->start(program, arguments);
    if (!process->waitForStarted()) {
        QMessageBox::critical(this, "错误", "无法停止 VICODaemon 服务！");
        updateServiceStatus("Failed to stop!");  // 在状态栏更新信息
    } else {
        QMessageBox::information(this, "成功", "VICODaemon 服务已停止！");
        updateServiceStatus("stopped!");  // 在状态栏更新信息
    }

    // SC_HANDLE hService = openServiceHandle(VICODaemonServiceName, SERVICE_QUERY_STATUS | SERVICE_STOP);
    // if (hService == nullptr) {
    //     return;  // 打开服务失败
    // }

    // // 查询服务状态
    // SERVICE_STATUS_PROCESS serviceStatus = getServiceStatus(hService);
    // if (serviceStatus.dwCurrentState != SERVICE_RUNNING) {
    //     qDebug() << "VICODaemon service is not running.";
    //     updateServiceStatus("Not Running");  // 在状态栏更新信息
    //     CloseServiceHandle(hService);
    //     return;  // 服务没有运行，无需停止
    // }

    // // 尝试停止服务
    // if (!ControlService(hService, SERVICE_CONTROL_STOP, (LPSERVICE_STATUS)&serviceStatus)) {
    //     DWORD dwError = GetLastError();
    //     qDebug() << "Failed to stop VICODaemon service. Error:" << dwError;
    //     updateServiceStatus("Failed to stop");  // 在状态栏更新信息
    //     CloseServiceHandle(hService);
    //     QMessageBox::critical(this, "Error", "Failed to stop VICODaemon service.");
    //     return;
    // }

    // qDebug() << "VICODaemon service stopped successfully.";
    // updateServiceStatus("Stopped");  // 在状态栏更新信息

    // CloseServiceHandle(hService);
    // // QMessageBox::information(this, "Success", "VICODaemon service stopped successfully.");
}

void MainWindow::setupMenuConnections()
{
    // 连接 "Open" 菜单项
    connectMenuAction("actionopen", &MainWindow::startVICODaemonService);

    // 连接 "Close" 菜单项
    connectMenuAction("actionclose", &MainWindow::stopVICODaemonService);

    // 连接 "Scan" 菜单项
    connectMenuAction("actionUSB", &MainWindow::scanAndGetDeviceInfo);

    // 连接 "refresh" 菜单项
    connectMenuAction("actionrefresh", &MainWindow::refreshDeviceInfo);
}

void MainWindow::setupStatusBar()
{

    // 创建服务状态标签
    serviceStatusLabel = new QLabel("Please open VICODaemon Service.");
    statusBar()->addWidget(serviceStatusLabel);  // 将其添加到状态栏

    // 创建进度条
    progressBar = new QProgressBar();
    progressBar->setRange(0, 100);
    progressBar->setValue(0);  // 初始化进度条
    statusBar()->addWidget(progressBar);  // 将其添加到状态栏

    // 创建其他信息标签
    otherInfoLabel = new QLabel("");
    statusBar()->addWidget(otherInfoLabel);  // 将其添加到状态栏

}

void MainWindow::setupUI()
{
    // 设置每个字节的 Bin 数
    ui->comboBox_bytePerBin->addItem("1", 0);
    ui->comboBox_bytePerBin->addItem("2", 1);
    ui->comboBox_bytePerBin->addItem("3", 2);
    // 设置默认选中第一个项（索引为 0）
    ui->comboBox_bytePerBin->setCurrentIndex(2);

    // 设置 MCA 的 Bin 的数量
    ui->comboBox_numOfBins->addItem("512", 0);
    ui->comboBox_numOfBins->addItem("1024", 1);
    ui->comboBox_numOfBins->addItem("2048", 2);
    ui->comboBox_numOfBins->addItem("4096", 3);
    ui->comboBox_numOfBins->addItem("8192", 4);
    // 设置默认选中第一个项（索引为 0）
    ui->comboBox_numOfBins->setCurrentIndex(3);


    // 将 lineedit 设置为只读
    ui->lineEdit_realTime->setReadOnly(true);
    ui->lineEdit_liveTime->setReadOnly(true);
    ui->lineEdit_inCount->setReadOnly(true);
    ui->lineEdit_outCount->setReadOnly(true);
    ui->lineEdit_inRate->setReadOnly(true);
    ui->lineEdit_outRate->setReadOnly(true);

}

void MainWindow::setupConnections()
{
    connect(ui->pushButton_setPeakingTime, &QPushButton::clicked, this, &MainWindow::setPeakingTime);
    connect(ui->pushButton_setMeasureTime, &QPushButton::clicked, this, &MainWindow::setMeasureTime);
    connect(ui->pushButton_startRun, &QPushButton::clicked, this, &MainWindow::startRun);
}

void MainWindow::updateServiceStatus(const QString &status)
{
    // 更新 serviceStatusLabel 中的消息
    serviceStatusLabel->setText("VICODaemon Service: " + status);
}

void MainWindow::infoOutput(const QString &info)
{
    // 将 info 输出到 QTextEdit 中
    ui->textEdit_infoOutput->append(info);  // append 会将新的文本添加到现有文本后面
}

QString MainWindow::getSerialNumber()
{
    QString serialNumber;
    // 获取当前选中的行索引
    int row = ui->tableWidget_device->currentRow();

    if (row != -1) {  // 确保有选中行
        // 获取该行的 serialNumber 列的数据（serialNumber 是第 0 列）
        serialNumber = ui->tableWidget_device->item(row, 0)->text();

        // qDebug() << "Selected serial number: " << serialNumber;
    }
    else {
        qDebug() << "No Selected serial number.";
    }
    return serialNumber;
}

void MainWindow::scanAndGetDeviceInfo()
{

    vicolib->scanDevices();
    vico_ctx.numberOfDevices = 0;   // 初始化设备数量
    vicolib->getNumOfDevices(&vico_ctx.numberOfDevices);  // 调用函数并传递指针
    infoOutput("number: "  + QString::number(vico_ctx.numberOfDevices));
    qDebug() << "Number of devices:" << vico_ctx.numberOfDevices;  // 打印设备数量

    // 清空表格中之前的所有行
    ui->tableWidget_device->setRowCount(0);


    vicolib->GetDeviceInfoByIndex(vico_ctx.numberOfDevices, vico_ctx.serialNumber, vico_ctx.infoOfInterface);

    for (int i = 0; i < vico_ctx.numberOfDevices; ++i) {
        // 插入新行（如果有必要）
        ui->tableWidget_device->insertRow(i);

        // 将 serialNumber 和 infoOfInterface 填充到对应的单元格中
        ui->tableWidget_device->setItem(i, 0, new QTableWidgetItem(QString::fromLatin1(vico_ctx.serialNumber)));
        ui->tableWidget_device->setItem(i, 1, new QTableWidgetItem(QString::fromLatin1(vico_ctx.infoOfInterface)));
    }

}

void MainWindow::refreshDeviceInfo()
{
    vicolib->RefreshDeviceConnections(vico_ctx.vicostatype);
    switch (vico_ctx.vicostatype) {
    case VICO_SUCCESS:
        otherInfoLabel->setText(QString("VICODAEMON is online."));
        vicolib->getNumOfDevices(&vico_ctx.numberOfDevices);
        if(vico_ctx.numberOfDevices == 0){
            QMessageBox::warning(this,
                                 tr("Warning"),
                                 tr("Please scan device or connect device!"));
        }

        break;
    case VICO_NO_DEVICE_WITH_ID_CONNECTED_ERROR:
        // 设备未连接的情况
        otherInfoLabel->setText(QString("No device connected with specified serial number."));
        break;

    case VICO_VICODAEMON_IS_STOPPED:
        // VICODaemon 未启动的情况
        QMessageBox::warning(this,
                             tr("Operation not allowed"),
                             tr("Please open VICODAEMON service!"));
        otherInfoLabel->setText(QString("VICODAEMON is offline!"));
        break;

    case VICO_VICOLIB_TIMEOUT_ERROR:
        // 超时错误
        otherInfoLabel->setText(QString("Timeout error occurred."));
        break;

    case VICO_INVALID_ARGUMENT_ERROR:
        // 无效参数错误
        otherInfoLabel->setText(QString("Invalid argument passed."));
        break;

    default:
        // 未知错误
        otherInfoLabel->setText(QString("Unknown error occurred."));
        break;
    }
}

void MainWindow::onRunTimerTimeout()
{
    qDebug() << "enter onRunTimerTimeout";
    if(vico_ctx.serialNumber[0] == '\0') {
        QMessageBox::warning(
            this,
            tr("Operation not allowed"),
            tr("Please select a device (serial number) first.")
            );
        return;
    }
    memset(&vico_ctx.runStatistics, 0, sizeof(vico_ctx.runStatistics));     // 初始化结构体 runStatistics
    vicolib->GetRunStatistics(vico_ctx.serialNumber, &vico_ctx.runStatistics);

    // 刷新 UI
    ui->lineEdit_realTime->setText(QString::number(vico_ctx.runStatistics.realTime, 'f', 0));
    ui->lineEdit_liveTime->setText(QString::number(vico_ctx.runStatistics.liveTime, 'f', 0));
    ui->lineEdit_outRate->setText(QString::number(vico_ctx.runStatistics.outputCountRate));
    ui->lineEdit_inRate->setText(QString::number(vico_ctx.runStatistics.inputCountRate));

    // Run 结束 → 停止定时器
    if (!vico_ctx.runStatistics.isRunActive) {
        m_runTimer->stop();
        otherInfoLabel->setText("Measurement finished");
        infoOutput("measurement finished!");

        /* Prepare the spectrum data array */
        vico_ctx.mcaSize = vico_ctx.numberOfBins * vico_ctx.bytesPerBin;

        // 动态分配 mcaData
        vico_ctx.mcaData = new UInt32Type[vico_ctx.numberOfBins];

        vicolib->GetMCADataUInt32(vico_ctx.serialNumber, vico_ctx.bytesPerBin, vico_ctx.numberOfBins, vico_ctx.mcaData);

        // 使用 mcaData
        for (int i = 0; i < vico_ctx.numberOfBins; ++i) {
            qDebug() << "Bin" << i << ":" << vico_ctx.mcaData[i];
        }

        saveMCAToFile(vico_ctx.mcaData, vico_ctx.numberOfBins);

        // 释放内存
        delete[] vico_ctx.mcaData;
        vico_ctx.mcaData = nullptr;

    }
}

void MainWindow::setPeakingTime()
{
    QString peakingTime = ui->lineEdit_peakingTime->text();
    if(peakingTime.isEmpty()){
        return;
    }
    vico_ctx.peakingTime = peakingTime.toFloat();

    if(vico_ctx.serialNumber[0] == '\0') {
        QMessageBox::warning(
            this,
            tr("Operation not allowed"),
            tr("Please select a device (serial number) first.")
            );
        return;
    }

    vicolib->SetSlowFilterPeakingTime(vico_ctx.serialNumber, &vico_ctx.peakingTime);


}

void MainWindow::setMeasureTime()
{
    QString measureTime = ui->lineEdit_measureTime->text();
    if(measureTime.isEmpty()){
        return;
    }
    vico_ctx.measureTime = measureTime.toDouble();
    vico_ctx.stopConditionType = STOP_AT_FIXED_REALTIME;
    if(vico_ctx.serialNumber[0] == '\0') {
        QMessageBox::warning(
            this,
            tr("Operation not allowed"),
            tr("Please select a device (serial number) first.")
            );
        return;
    }
    vicolib->SetStopCondition(vico_ctx.serialNumber, vico_ctx.stopConditionType, &vico_ctx.measureTime);

}

void MainWindow::startRun()
{
    QString numberOfBins_text = ui->comboBox_numOfBins->currentText();
    QString bytesPerBin_text = ui->comboBox_bytePerBin->currentText();
    if(numberOfBins_text.isEmpty() || bytesPerBin_text.isEmpty()){
        return;
    }
    /* Set number of bins in spectrum to 4096 and bytes per bin to 3 */
    vico_ctx.numberOfBins = numberOfBins_text.toUInt();
    vico_ctx.bytesPerBin = bytesPerBin_text.toUInt();
    if(vico_ctx.serialNumber[0] == '\0') {
        QMessageBox::warning(
            this,
            tr("Operation not allowed"),
            tr("Please select a device (serial number) first.")
            );
        return;
    }
    vicolib->SetMCANumberOfBins(vico_ctx.serialNumber, &vico_ctx.numberOfBins);
    vicolib->SetMCABytesPerBin(vico_ctx.serialNumber, &vico_ctx.bytesPerBin);

    infoOutput(QString("successfully set numberOfBins %1, bytesPerBin %2").arg(vico_ctx.numberOfBins).arg(vico_ctx.bytesPerBin));

    /* Start measurement */
    vicolib->StartRun(vico_ctx.serialNumber);

    // 创建并启动定时器
    if (!m_runTimer) {
        m_runTimer = new QTimer(this);
        connect(m_runTimer, &QTimer::timeout,
                this, &MainWindow::onRunTimerTimeout);
    }

    m_runTimer->start(1000);  // 100 ms 刷新一次
}

void MainWindow::saveMCAToFile(const UInt32Type *mcaData, int numberOfBins)
{
    if(mcaData == nullptr || numberOfBins == 0){
        return;
    }
    // 1. 确保目录存在
    QDir dir("./spectrum");
    if (!dir.exists()) {
        dir.mkpath(".");
    }

    // 2. 生成文件名：时间戳.txt
    QString timestamp = QDateTime::currentDateTime().toString("yyyyMMdd_HHmmss");
    QString filePath = dir.filePath(timestamp + "_" + QString::number(vico_ctx.measureTime, 'f', 2) + "s" + ".txt");

    // 3. 打开文件写入
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "Failed to open file:" << filePath;
        return;
    }

    QTextStream out(&file);
    for (int i = 0; i < numberOfBins; ++i) {
        out << mcaData[i] << "\n";
    }

    file.close();
    qDebug() << "MCA data saved to" << filePath;

}





