#ifndef VICO_LIBRARY_H
#define VICO_LIBRARY_H

#include <QLibrary>
#include <QDebug>
#include <QString>
#include <QVector>
#include <QFileInfo>
#include <QMessageBox>
#include <QDir>
#include <QCoreApplication>

#include <./VICOLib_impl/types.h>

// 定义函数指针类型
typedef VICOStatusType (*ScanUsbDevicesFunc)();
typedef VICOStatusType (*GetNumberOfDevicesFunc)(UInt8Type* numberOfDevices);
typedef VICOStatusType (*GetDeviceInfoByIndexFunc)(UInt8Type index, UInt8Type serialNumberSize, CharType* serialNumber, InterfaceType* deviceInterface);
typedef VICOStatusType (*SetSlowFilterPeakingTimeFunc)(const CharType* serialNumber, FloatType* peakingTime);
typedef VICOStatusType (*SetStopConditionFunc)(const CharType* serialNumber, StopConditionType stopConditionType, DoubleType* stopConditionValue);
typedef VICOStatusType (*SetMCANumberOfBinsFunc)(const CharType* serialNumber, UInt16Type* numberOfBins);
typedef VICOStatusType (*SetMCABytesPerBinFunc)(const CharType* serialNumber, UInt8Type* bytesPerBin);
typedef VICOStatusType (*StartRunFunc)(const CharType* serialNumber);
typedef VICOStatusType (*GetRunStatisticsFunc)(const CharType* serialNumber, RunStatisticsType* runStatistics);
typedef VICOStatusType (*GetMCADataUInt32Func)(const CharType* serialNumber, UInt8Type bytesPerBin, UInt16Type numberOfBins, UInt32Type* mcaData);
typedef VICOStatusType (*RefreshDeviceConnectionsFunc)();
typedef VICOStatusType (*GetLibraryVersionFunc)(VersionType* libraryVersion);
typedef VICOStatusType (*GetDaemonVersionFunc)(VersionType* daemonVersion);

typedef DPPStatusType (*GetMCUStatusInfoFunc)(const CharType* serialNumber, MCUStatusInfoType* mcuStatus);
typedef DPPStatusType (*GetFirmwareVersionFunc)(const CharType* serialNumber, FirmwareVersionType* version);
typedef DPPStatusType (*GetBoardTemperatureFunc)(const CharType* serialNumber, UInt16Type* temperature);


typedef MCUStatusType (*LiveInfo2VICOFunc)(const CharType* serialNumber, LiveInfo2VICOType* liveInfo);
typedef MCUStatusType (*SwPkgGetActiveFunc)(const CharType* serialNumber, SoftwarePackage *swPkg);
typedef MCUStatusType (*LiveInfo2VIAMPFunc)(const CharType* serialNumber, LiveInfo2VIAMPType* liveInfo);




class VicoLibrary
{
public:
    // 构造函数：加载 DLL 并解析函数
    VicoLibrary(const QString& dllName);

    // 析构函数：卸载 DLL
    ~VicoLibrary();

    void checkError(const VICOStatusType sta);
    void checkError_DPP(const DPPStatusType sta);
    void checkError_MCU(const MCUStatusType sta);

    // 扫描 USB 设备
    void scanDevices();

    // 获取设备数量
    void getNumOfDevices(UInt8Type* numberOfDevices);

    // 获取设备名称
    void GetDeviceInfoByIndex(const UInt8Type numberOfDevices, CharType* serialNumber, CharType* infoOfInterface);

    // 设置慢速 peakingtime
    void SetSlowFilterPeakingTime(const CharType* serialNumber, FloatType* peakingTime);

    // 设置停止条件
    void SetStopCondition(const CharType* serialNumber, StopConditionType stopConditionType, DoubleType* stopConditionValue);

    // 设置 MCA bins 的数量
    void SetMCANumberOfBins(const CharType* serialNumber, UInt16Type* numberOfBins);

    // 设置每个 Bin 的字节数
    void SetMCABytesPerBin(const CharType* serialNumber, UInt8Type* bytesPerBin);

    // 开始测量
    void StartRun(const CharType* serialNumber);

    // 获取运行状态
    void GetRunStatistics(const CharType* serialNumber, RunStatisticsType* runStatistics);

    // 获取 MCA 数据
    void GetMCADataUInt32(const CharType* serialNumber, UInt8Type bytesPerBin, UInt16Type numberOfBins, UInt32Type* mcaData);

    // 刷新一下设备 只是检查是否在线
    void RefreshDeviceConnections(VICOStatusType &sta);

    // 查询库版本
    void GetLibraryVersion(VersionType* libraryVersion);

    // 查询 vicodaemon 版本
    void GetDaemonVersion(VersionType* daemonVersion);

    // 查询 DPP 板温度
    void GetBoardTemperature(const CharType* serialNumber, UInt16Type* temperature);


    /* DPPStatusType */
    // 查询 MCU 状态
    void GetMCUStatusInfo(const CharType* serialNumber, MCUStatusInfoType* mcuStatus);
    // 查询 dpp 硬件版本号
    void GetFirmwareVersion(const CharType* serialNumber, FirmwareVersionType* version);

    /* MCUStatusType */
    // 获取实时信息 但是获取之前 需要 SoftwarePackage 是 app 形式
    void LiveInfo2VICO(const CharType* serialNumber, LiveInfo2VICOType* liveInfo);
    // 获取 SoftwarePackage 是什么模式
    void SwPkgGetActive(const CharType* serialNumber, SoftwarePackage *swPkg);
    void LiveInfo2VIAMP(const CharType* serialNumber, LiveInfo2VIAMPType* liveInfo);



    // 通用加载函数模板
    template <typename FuncType>
    FuncType loadFunction(const char* functionName);

private:
    QLibrary* vicoLib;  // 用于加载 DLL 的 QLibrary 对象

    /* VICOStatusType */
    ScanUsbDevicesFunc scanUsbDevices;  // scanUsbDevices 函数指针
    GetNumberOfDevicesFunc getNumberOfDevices;  // getNumberOfDevices 函数指针
    GetDeviceInfoByIndexFunc getDeviceInfoByIndex;  // getDeviceInfoByIndex 函数指针
    SetSlowFilterPeakingTimeFunc setSlowFilterPeakingTime;  // setSlowFilterPeakingTime 函数指针
    SetStopConditionFunc setStopCondition;  // setStopCondition 函数指针
    SetMCANumberOfBinsFunc setMCANumberOfBins;  // setMCANumberOfBins 函数指针
    SetMCABytesPerBinFunc setMCABytesPerBin;  // setMCABytesPerBin 函数指针
    StartRunFunc startRun;  // startRun 函数指针
    GetRunStatisticsFunc getRunStatistics;  // getRunStatistics 函数指针
    GetMCADataUInt32Func getMCADataUInt32;  // getMCADataUInt32 函数指针
    RefreshDeviceConnectionsFunc refreshDeviceConnections;  // refreshDeviceConnections 函数指针
    GetLibraryVersionFunc getLibraryVersion;    // getLibraryVersionFunc 函数指针
    GetDaemonVersionFunc getDaemonVersion;   // getDaemonVersion 函数指针

    /* DPPStatusType */
    GetMCUStatusInfoFunc getMCUStatusInfo;  // getMCUStatusInfo 函数指针
    GetFirmwareVersionFunc getFirmwareVersion; // getFirmwareVersion 函数指针
    GetBoardTemperatureFunc getBoardTemperature;    // getBoardTemperature 函数指针

    /* MCUStatusType */
    LiveInfo2VICOFunc liveInfo2VICO;    // liveInfo2VICO 函数指针
    SwPkgGetActiveFunc swPkgGetActive;  // swPkgGetActive 函数指针
    LiveInfo2VIAMPFunc liveInfo2VIAMP;  // liveInfo2VIAMP 函数指针




};

#endif // VICO_LIBRARY_H
