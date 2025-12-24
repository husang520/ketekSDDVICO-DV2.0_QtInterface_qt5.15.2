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
    , getLibraryVersion(nullptr)
    , getDaemonVersion(nullptr)
    , getMCUStatusInfo(nullptr)
    , getFirmwareVersion(nullptr)
    , getBoardTemperature(nullptr)
    , liveInfo2VICO(nullptr)
    , swPkgGetActive(nullptr)
    , liveInfo2VIAMP(nullptr)

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
    getLibraryVersion = loadFunction<GetLibraryVersionFunc>("getLibraryVersion");
    getMCUStatusInfo = loadFunction<GetMCUStatusInfoFunc>("getMCUStatusInfo");
    getFirmwareVersion = loadFunction<GetFirmwareVersionFunc>("getFirmwareVersion");
    getBoardTemperature = loadFunction<GetBoardTemperatureFunc>("getBoardTemperature");
    liveInfo2VICO = loadFunction<LiveInfo2VICOFunc>("liveInfo2VICO");
    swPkgGetActive = loadFunction<SwPkgGetActiveFunc>("swPkgGetActive");
    liveInfo2VIAMP = loadFunction<LiveInfo2VIAMPFunc>("liveInfo2VIAMP");

    // 更多函数加载...

}

// 析构函数：清理 QLibrary 对象
VicoLibrary::~VicoLibrary()
{
    delete vicoLib;  // 清理 QLibrary 对象
}

void VicoLibrary::checkError(const VICOStatusType sta)
{
    switch (sta) {
    case VICO_SUCCESS:

        break;
    case VICO_NO_DEVICE_WITH_ID_CONNECTED_ERROR:
        // 设备未连接的情况
        QMessageBox::warning(
            nullptr,
            "VICOStatusType",
            "No device connected with specified serial number."
            );
        break;

    case VICO_VICODAEMON_IS_STOPPED:
        // VICODaemon 未启动的情况
        QMessageBox::warning(
            nullptr,
            "VICOStatusType",
            "VICODAEMON is offline!"
            );
        break;

    case VICO_VICOLIB_TIMEOUT_ERROR:
        // 超时错误
        QMessageBox::warning(
            nullptr,
            "VICOStatusType",
            "Timeout error occurred."
            );

        break;

    case VICO_INVALID_ARGUMENT_ERROR:
        // 无效参数错误
        QMessageBox::warning(
            nullptr,
            "VICOStatusType",
            "Invalid argument passed."
            );
        break;

    default:
        // 未知错误
        QMessageBox::warning(
            nullptr,
            "VICOStatusType",
            "Unknown error occurred."
            );
        break;
    }
}

void VicoLibrary::checkError_DPP(const DPPStatusType sta)
{
    switch (sta) {
    case DPP_SUCCESS:
        // 成功的情况
        break;

    case DPP_OUT_OF_RANGE_ERROR:
        // 写入值超出范围
        QMessageBox::warning(
            nullptr,
            "DPPStatusType",
            "Written value is out of range. The value remains unchanged."
            );
        break;

    case DPP_PARAMETER_READ_ONLY_ERROR:
        // 试图写入只读参数
        QMessageBox::warning(
            nullptr,
            "DPPStatusType",
            "Requested parameter is read-only. The value remains unchanged."
            );
        break;

    case DPP_PARAMETER_NOT_EXISTING_ERROR:
        // 参数不存在
        QMessageBox::warning(
            nullptr,
            "DPPStatusType",
            "Requested parameter does not exist in the device."
            );
        break;

    case DPP_INVALID_COMMAND_ERROR:
        // 无效命令错误
        QMessageBox::warning(
            nullptr,
            "DPPStatusType",
            "Invalid command. No changes to the device configuration."
            );
        break;

    case DPP_REQUEST_CURRENTLY_NOT_POSSIBLE_ERROR:
        // 当前请求不可用
        QMessageBox::warning(
            nullptr,
            "DPPStatusType",
            "Parameter currently not accessible."
            );
        break;

    case DPP_TIMEOUT_ERROR:
        // 超时错误
        QMessageBox::warning(
            nullptr,
            "DPPStatusType",
            "Timeout error occurred. The value might be changed."
            );
        break;

    case DPP_SYNTAX_ERROR_INVALID_REQUEST_ERROR:
        // 语法错误
        QMessageBox::warning(
            nullptr,
            "DPPStatusType",
            "Syntax error. Invalid combination of requests."
            );
        break;

    case DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR:
        // 设备未连接
        QMessageBox::warning(
            nullptr,
            "DPPStatusType",
            "No device connected with the specified serial number."
            );
        break;

    case DPP_VICODAEMON_IS_STOPPED:
        // VICODaemon 未启动
        QMessageBox::warning(
            nullptr,
            "DPPStatusType",
            "VICODaemon is offline!"
            );
        break;

    case DPP_VICOLIB_TIMEOUT_ERROR:
        // VICOLib 超时
        QMessageBox::warning(
            nullptr,
            "DPPStatusType",
            "Timeout error occurred in VICOLib."
            );
        break;

    case DPP_RESPONSE_OUT_OF_BOUNDS_ERROR:
        // 响应数据超出范围
        QMessageBox::warning(
            nullptr,
            "DPPStatusType",
            "Response data is out of bounds."
            );
        break;

    case DPP_INVALID_ARGUMENT_ERROR:
        // 无效参数错误
        QMessageBox::warning(
            nullptr,
            "DPPStatusType",
            "Invalid argument passed to the device."
            );
        break;

    case DPP_INVALID_RESPONSE_DATA_ERROR:
        // 响应数据无效
        QMessageBox::warning(
            nullptr,
            "DPPStatusType",
            "Invalid response data from the device."
            );
        break;

    case DPP_VICOLIB_OUT_OF_RANGE_ERROR:
        // VICOLib 参数超出范围
        QMessageBox::warning(
            nullptr,
            "DPPStatusType",
            "Given argument value is out of range in VICOLib."
            );
        break;

    case DPP_COMMAND_NOT_SUPPORTED_ERROR:
        // 不支持的命令
        QMessageBox::warning(
            nullptr,
            "DPPStatusType",
            "Command is not applicable for the targeted device."
            );
        break;

    case DPP_UNDEFINED_ERROR:
        // 未定义错误
        QMessageBox::warning(
            nullptr,
            "DPPStatusType",
            "Undefined error occurred in DPP."
            );
        break;

    default:
        // 未知错误
        QMessageBox::warning(
            nullptr,
            "DPPStatusType",
            "Unknown error occurred in DPP."
            );
        break;
    }
}

void VicoLibrary::checkError_MCU(const MCUStatusType sta)
{

    switch (sta) {
    case MCU_SUCCESS:
        // 成功的情况
        break;

    case MCU_COMMAND_NOT_SUPPORTED:
        // 命令不支持
        QMessageBox::warning(
            nullptr,
            "MCUStatusType",
            "Command not supported."
            );
        break;

    case MCU_WRONG_CRC_CHECKSUM:
        // CRC 校验错误
        QMessageBox::warning(
            nullptr,
            "MCUStatusType",
            "Wrong datagram CRC checksum."
            );
        break;

    case MCU_COMMAND_LENGTH_MISMATCH:
        // 命令长度不匹配
        QMessageBox::warning(
            nullptr,
            "MCUStatusType",
            "Command length mismatch."
            );
        break;

    case MCU_VERSION_NOT_SUPPORTED:
        // 不支持的版本
        QMessageBox::warning(
            nullptr,
            "MCUStatusType",
            "Datagram version not supported."
            );
        break;

    case MCU_ERROR:
        // 通用错误
        QMessageBox::warning(
            nullptr,
            "MCUStatusType",
            "Error during command processing."
            );
        break;

    case MCU_LEN_OUT_OF_VALID_RANGE:
        // 长度超出有效范围
        QMessageBox::warning(
            nullptr,
            "MCUStatusType",
            "Length outside the valid range."
            );
        break;

    case MCU_ADDRESS_OUT_OF_VALID_RANGE:
        // 地址超出有效范围
        QMessageBox::warning(
            nullptr,
            "MCUStatusType",
            "Address outside the valid range."
            );
        break;

    case MCU_SYSTEM_IS_NOT_IN_EEA_MODE:
        // 系统不在 EEA 模式
        QMessageBox::warning(
            nullptr,
            "MCUStatusType",
            "System is not in EEA mode."
            );
        break;

    case MCU_TWI_SLAVE_NACK:
        // TWI 从设备 NACK
        QMessageBox::warning(
            nullptr,
            "MCUStatusType",
            "TWI slave NACK received."
            );
        break;

    case MCU_BL_FLASH_SESSION_ACTIVE:
        // Flash 会话已激活
        QMessageBox::warning(
            nullptr,
            "MCUStatusType",
            "Flash session already active."
            );
        break;

    case MCU_BL_NO_FLASH_SESSION_ACTIVE:
        // 没有 Flash 会话
        QMessageBox::warning(
            nullptr,
            "MCUStatusType",
            "No flash session active."
            );
        break;

    case MCU_BL_ADDRESS_OUT_OF_VALID_RANGE:
        // 启动地址超出有效范围
        QMessageBox::warning(
            nullptr,
            "MCUStatusType",
            "Start address out of valid range."
            );
        break;

    case MCU_BL_LEN_OUT_OF_VALID_RANGE:
        // 数据长度超出有效范围
        QMessageBox::warning(
            nullptr,
            "MCUStatusType",
            "Invalid data length in bootloader."
            );
        break;

    case MCU_BL_DATA_NOT_IN_SEQUENCE_WITHIN_SESSION:
        // 数据块不按顺序
        QMessageBox::warning(
            nullptr,
            "MCUStatusType",
            "Data block not in sequence within session."
            );
        break;

    case MCU_BL_APPLICATION_CHECKSUM_INVALID:
        // 应用程序校验和无效
        QMessageBox::warning(
            nullptr,
            "MCUStatusType",
            "Application checksum invalid."
            );
        break;

    case MCU_BL_ALREADY_IN_APPLICATION:
        // 已经进入应用程序
        QMessageBox::warning(
            nullptr,
            "MCUStatusType",
            "Already in application."
            );
        break;

    case MCU_NO_DEVICE_WITH_ID_CONNECTED_ERROR:
        // 设备未连接
        QMessageBox::warning(
            nullptr,
            "MCUStatusType",
            "No device connected with specified serial number."
            );
        break;

    case MCU_VICODAEMON_IS_STOPPED:
        // VICODaemon 未启动
        QMessageBox::warning(
            nullptr,
            "MCUStatusType",
            "VICODaemon is offline!"
            );
        break;

    case MCU_VICOLIB_TIMEOUT_ERROR:
        // VICOLib 超时
        QMessageBox::warning(
            nullptr,
            "MCUStatusType",
            "Timeout error occurred in VICOLib."
            );
        break;

    case MCU_RESPONSE_OUT_OF_BOUNDS_ERROR:
        // 响应数据超出范围
        QMessageBox::warning(
            nullptr,
            "MCUStatusType",
            "Response data out of bounds."
            );
        break;

    case MCU_INVALID_ARGUMENT_ERROR:
        // 无效参数错误
        QMessageBox::warning(
            nullptr,
            "MCUStatusType",
            "Invalid argument passed."
            );
        break;

    case MCU_INVALID_RESPONSE_DATA_ERROR:
        // 无效响应数据错误
        QMessageBox::warning(
            nullptr,
            "MCUStatusType",
            "Invalid response data."
            );
        break;

    case DPP_UART_TIMEOUT_ERROR:
        // DPP UART 超时
        QMessageBox::warning(
            nullptr,
            "MCUStatusType",
            "UART timeout error occurred."
            );
        break;

    case DPP_NO_ACCESS_TO_INTERNAL_MEMORY_ERROR:
        // 无法访问内部存储器
        QMessageBox::warning(
            nullptr,
            "MCUStatusType",
            "No access to internal memory."
            );
        break;

    case DPP_INCOMPLETE_UART_COMMAND_ERROR:
        // 不完整的 UART 命令
        QMessageBox::warning(
            nullptr,
            "MCUStatusType",
            "Incomplete UART command error."
            );
        break;

    case MCU_UNDEFINED_ERROR:
        // 未定义的错误
        QMessageBox::warning(
            nullptr,
            "MCUStatusType",
            "Undefined error occurred."
            );
        break;

    default:
        // 未知错误
        QMessageBox::warning(
            nullptr,
            "MCUStatusType",
            "Unknown error occurred."
            );
        break;
    }
}

// 调用 scanUsbDevices 函数
void VicoLibrary::scanDevices()
{
    if (scanUsbDevices) {
        VICOStatusType status = scanUsbDevices();  // 调用 DLL 中的函数
        checkError(status);
        qDebug() << "scanUsbDevices returned:" << status;
    }
}

// 调用 getNumberOfDevices 函数
void VicoLibrary::getNumOfDevices(UInt8Type* numberOfDevices)
{
    if (getNumberOfDevices) {
        VICOStatusType status = getNumberOfDevices(numberOfDevices);  // 调用 DLL 中的函数
        checkError(status);
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
            VICOStatusType status = getDeviceInfoByIndex(i, serialNumberSize, serialNumber, &deviceInterface);
            checkError(status);
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
        VICOStatusType status = setSlowFilterPeakingTime(serialNumber, peakingTime);  // 调用 DLL 中的函数
        checkError(status);
        qDebug() << "setSlowFilterPeakingTime returned:" << status;
        // qDebug() << "numberOfDevices:" << numberOfDevices;
    }
}

void VicoLibrary::SetStopCondition(const CharType *serialNumber, StopConditionType stopConditionType, DoubleType *stopConditionValue)
{
    if(setStopCondition){
        VICOStatusType status = setStopCondition(serialNumber, stopConditionType, stopConditionValue);
        checkError(status);
        qDebug() << "setStopCondition returned:" << status;
    }
}

void VicoLibrary::SetMCANumberOfBins(const CharType *serialNumber, UInt16Type *numberOfBins)
{
    if(setMCANumberOfBins){
        VICOStatusType status = setMCANumberOfBins(serialNumber, numberOfBins);
        checkError(status);
        qDebug() << "setMCANumberOfBins returned:" << status;
    }

}

void VicoLibrary::SetMCABytesPerBin(const CharType *serialNumber, UInt8Type *bytesPerBin)
{
    if(setMCABytesPerBin){
        VICOStatusType status = setMCABytesPerBin(serialNumber, bytesPerBin);
        checkError(status);
        qDebug() << "setMCABytesPerBin returned:" << status;
    }

}

void VicoLibrary::StartRun(const CharType *serialNumber)
{
    if(startRun){
        VICOStatusType status = startRun(serialNumber);
        checkError(status);
        qDebug() << "startRun returned:" << status;
    }
}

void VicoLibrary::GetRunStatistics(const CharType *serialNumber, RunStatisticsType *runStatistics)
{
    if(getRunStatistics){
        VICOStatusType status = getRunStatistics(serialNumber, runStatistics);
        checkError(status);
        qDebug() << "getRunStatistics returned:" << status;
    }
}

void VicoLibrary::GetMCADataUInt32(const CharType *serialNumber, UInt8Type bytesPerBin, UInt16Type numberOfBins, UInt32Type *mcaData)
{
    if(getMCADataUInt32){
        VICOStatusType status = getMCADataUInt32(serialNumber, bytesPerBin, numberOfBins, mcaData);
        checkError(status);
        qDebug() << "getMCADataUInt32 returned:" << status;
    }

}

void VicoLibrary::RefreshDeviceConnections(VICOStatusType &sta)
{
    if(refreshDeviceConnections){
        sta = refreshDeviceConnections();
        checkError(sta);
        qDebug() << "refreshDeviceConnections returned:" << sta;
    }
}

void VicoLibrary::GetLibraryVersion(VersionType *libraryVersion)
{
    if(getLibraryVersion){
        VICOStatusType status = getLibraryVersion(libraryVersion);
        checkError(status);
        qDebug() << "getLibraryVersion returned:" << status;
    }
}

void VicoLibrary::GetDaemonVersion(VersionType *daemonVersion)
{
    if(getDaemonVersion){
        VICOStatusType status = getDaemonVersion(daemonVersion);
        checkError(status);
        qDebug() << "getDaemonVersion returned:" << status;
    }
}

void VicoLibrary::GetBoardTemperature(const CharType *serialNumber, UInt16Type *temperature)
{
    if(getBoardTemperature){
        DPPStatusType status = getBoardTemperature(serialNumber, temperature);
        checkError_DPP(status);
        qDebug() << "getBoardTemperature returned:" << QString("0x%1").arg(status, 0, 16).toUpper();
    }
}

void VicoLibrary::GetMCUStatusInfo(const CharType *serialNumber, MCUStatusInfoType *mcuStatus)
{
    if(getMCUStatusInfo){
        DPPStatusType status = getMCUStatusInfo(serialNumber, mcuStatus);
        checkError_DPP(status);
        qDebug() << "getMCUStatusInfo returned:" << status;
    }

}

void VicoLibrary::GetFirmwareVersion(const CharType *serialNumber, FirmwareVersionType *version)
{
    if(getFirmwareVersion){
        DPPStatusType status = getFirmwareVersion(serialNumber, version);
        checkError_DPP(status);
        qDebug() << "getFirmwareVersion returned:" << QString("0x%1").arg(status, 0, 16).toUpper();
    }
}

void VicoLibrary::LiveInfo2VICO(const CharType *serialNumber, LiveInfo2VICOType *liveInfo)
{
    if(liveInfo2VICO){
        MCUStatusType status = liveInfo2VICO(serialNumber, liveInfo);
        checkError_MCU(status);
        qDebug() << "liveInfo2VICO returned:" << QString("0x%1").arg(status, 0, 16).toUpper();
    }

}

void VicoLibrary::SwPkgGetActive(const CharType *serialNumber, SoftwarePackage *swPkg)
{
    if(swPkgGetActive){
        MCUStatusType status = swPkgGetActive(serialNumber, swPkg);
        checkError_MCU(status);
        qDebug() << "swPkgGetActive returned:" << QString("0x%1").arg(status, 0, 16).toUpper();
    }
}

void VicoLibrary::LiveInfo2VIAMP(const CharType *serialNumber, LiveInfo2VIAMPType *liveInfo)
{
    if(liveInfo2VIAMP){
        MCUStatusType status = liveInfo2VIAMP(serialNumber, liveInfo);
        checkError_MCU(status);
        qDebug() << "swPkgGetActive returned:" << QString("0x%1").arg(status, 0, 16).toUpper();
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
