#include "VicoLibrary.h"

// 构造函数：加载 DLL 并解析函数
VicoLibrary::VicoLibrary(const QString& dllName)
    : vicoLib(nullptr)
    , scanUsbDevices(nullptr)
    , getNumberOfDevices(nullptr)
    , getDeviceInfoByIndex(nullptr)
    , setSlowFilterPeakingTime(nullptr)
    , setStopCondition(nullptr)
    , setMCANumberOfBins(nullptr)
    , setMCABytesPerBin(nullptr)
    , startRun(nullptr)
    , getRunStatistics(nullptr)
    , getMCADataUInt32(nullptr)
    , refreshDeviceConnections(nullptr)

{
    // 获取DLL文件的完整路径，假设dllName没有扩展名
    QString dllPath = QFileInfo(QCoreApplication::applicationDirPath(), dllName + ".dll").absoluteFilePath();

    // 检查DLL文件是否存在
    QFileInfo checkFile(dllPath);
    if (!checkFile.exists() || !checkFile.isFile()) {
        // 如果DLL文件不存在，提示用户添加
        QMessageBox::warning(
            nullptr,
            "DLL File Missing",
            "The required DLL file VICOLib2.dll is missing. Please add the DLL file VICOLib2.dll in the same directory as the executable."
            );
        return; // 不继续执行后面的加载操作
    }

    // 如果文件存在，尝试加载DLL
    vicoLib = new QLibrary(dllName);
    if (!vicoLib->load()) {
        // 如果加载失败，输出错误信息
        qDebug() << "Failed to load" << dllPath << ":" << vicoLib->errorString();
        return;
    }

    // 通过通用的加载函数模板加载函数
    scanUsbDevices = loadFunction<ScanUsbDevicesFunc>("scanUsbDevices");
    getNumberOfDevices = loadFunction<GetNumberOfDevicesFunc>("getNumberOfDevices");
    getDeviceInfoByIndex = loadFunction<GetDeviceInfoByIndexFunc>("getDeviceInfoByIndex");
    setSlowFilterPeakingTime = loadFunction<SetSlowFilterPeakingTimeFunc>("setSlowFilterPeakingTime");
    setStopCondition = loadFunction<SetStopConditionFunc>("setStopCondition");
    setMCANumberOfBins = loadFunction<SetMCANumberOfBinsFunc>("setMCANumberOfBins");
    setMCABytesPerBin = loadFunction<SetMCABytesPerBinFunc>("setMCABytesPerBin");
    startRun = loadFunction<StartRunFunc>("startRun");
    getRunStatistics = loadFunction<GetRunStatisticsFunc>("getRunStatistics");
    getMCADataUInt32 = loadFunction<GetMCADataUInt32Func>("getMCADataUInt32");
    refreshDeviceConnections = loadFunction<RefreshDeviceConnectionsFunc>("refreshDeviceConnections");

    // 更多函数加载...

}

// 析构函数：清理 QLibrary 对象
VicoLibrary::~VicoLibrary()
{
    delete vicoLib;  // 清理 QLibrary 对象
}

// 调用 scanUsbDevices 函数
void VicoLibrary::scanDevices()
{
    if (scanUsbDevices) {
        int status = scanUsbDevices();  // 调用 DLL 中的函数
        qDebug() << "scanUsbDevices returned:" << status;
    }
}

// 调用 getNumberOfDevices 函数
void VicoLibrary::getNumOfDevices(UInt8Type* numberOfDevices)
{
    if (getNumberOfDevices) {
        int status = getNumberOfDevices(numberOfDevices);  // 调用 DLL 中的函数
        qDebug() << "getNumberOfDevices returned:" << status;
        // qDebug() << "numberOfDevices:" << numberOfDevices;
    }
}

void VicoLibrary::GetDeviceInfoByIndex(const UInt8Type numberOfDevices, CharType* serialNumber, CharType* infoOfInterface)
{
    if(getDeviceInfoByIndex){
        UInt8Type serialNumberSize = 12;
        // CharType serialNumber[serialNumberSize];
        InterfaceType deviceInterface;


        for (int i=0; i<numberOfDevices; i++)
        {
            int status = getDeviceInfoByIndex(i, serialNumberSize, serialNumber, &deviceInterface);
            qDebug() << "getNumberOfDevices returned:" << status;
            qDebug() << "Device #" << i << "serial number: " << serialNumber;
            switch (deviceInterface)
            {
               case INTERFACE_ETHERNET_TCP:
                   //status = getIPAddress(serialNumber, ipAddressSize, ipAddress);
                   qDebug() << "connected over TCP interface with IP %s\n";
                   strcpy(infoOfInterface, "TCP interface");
                   break;
               case INTERFACE_ETHERNET_UDP:
                   qDebug() << "connected over UDP interface\n";
                   strcpy(infoOfInterface, "UDP interface");

                   break;
               case INTERFACE_UNKNOWN:
                   qDebug() << "connected over unknown interface\n";
                   strcpy(infoOfInterface, "unknown interface");
                   // infoOfInterface = QString("unknown interface");
                   break;
               case INTERFACE_USB:
                   qDebug() << "connected over USB interface (FT4222)\n";
                   strcpy(infoOfInterface, "USB interface (FT4222)");
                   // infoOfInterface = QString("USB interface (FT4222)");
                   break;
               case INTERFACE_USB_HID:
                   qDebug() << "connected over USB interface (HID)\n";
                   strcpy(infoOfInterface, "USB interface (HID)");
                   // infoOfInterface = QString("USB interface (HID)");
                   break;

            }
        }

    }


}

void VicoLibrary::SetSlowFilterPeakingTime(const CharType *serialNumber, FloatType *peakingTime)
{
    if (setSlowFilterPeakingTime) {
        int status = setSlowFilterPeakingTime(serialNumber, peakingTime);  // 调用 DLL 中的函数
        qDebug() << "setSlowFilterPeakingTime returned:" << status;
        // qDebug() << "numberOfDevices:" << numberOfDevices;
    }
}

void VicoLibrary::SetStopCondition(const CharType *serialNumber, StopConditionType stopConditionType, DoubleType *stopConditionValue)
{
    if(setStopCondition){
        int status = setStopCondition(serialNumber, stopConditionType, stopConditionValue);
        qDebug() << "setStopCondition returned:" << status;
    }
}

void VicoLibrary::SetMCANumberOfBins(const CharType *serialNumber, UInt16Type *numberOfBins)
{
    if(setMCANumberOfBins){
        int status = setMCANumberOfBins(serialNumber, numberOfBins);
        qDebug() << "setMCANumberOfBins returned:" << status;
    }

}

void VicoLibrary::SetMCABytesPerBin(const CharType *serialNumber, UInt8Type *bytesPerBin)
{
    if(setMCABytesPerBin){
        int status = setMCABytesPerBin(serialNumber, bytesPerBin);
        qDebug() << "setMCABytesPerBin returned:" << status;
    }

}

void VicoLibrary::StartRun(const CharType *serialNumber)
{
    if(startRun){
        int status = startRun(serialNumber);
        qDebug() << "startRun returned:" << status;
    }
}

void VicoLibrary::GetRunStatistics(const CharType *serialNumber, RunStatisticsType *runStatistics)
{
    if(getRunStatistics){
        int status = getRunStatistics(serialNumber, runStatistics);
        qDebug() << "getRunStatistics returned:" << status;
    }
}

void VicoLibrary::GetMCADataUInt32(const CharType *serialNumber, UInt8Type bytesPerBin, UInt16Type numberOfBins, UInt32Type *mcaData)
{
    if(getMCADataUInt32){
        int status = getMCADataUInt32(serialNumber, bytesPerBin, numberOfBins, mcaData);
        qDebug() << "getMCADataUInt32 returned:" << status;
    }

}

void VicoLibrary::RefreshDeviceConnections(VICOStatusType &sta)
{
    if(refreshDeviceConnections){
        sta = refreshDeviceConnections();
        qDebug() << "refreshDeviceConnections returned:" << sta;
    }
}

template<typename FuncType>
FuncType VicoLibrary::loadFunction(const char *functionName)
{
    FuncType func = reinterpret_cast<FuncType>(vicoLib->resolve(functionName));
    if (!func) {
        qDebug() << "Failed to resolve function:" << functionName;
    }
    return func;
}
