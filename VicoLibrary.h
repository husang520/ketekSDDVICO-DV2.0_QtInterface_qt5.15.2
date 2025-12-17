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
typedef int (*ScanUsbDevicesFunc)();
typedef int (*GetNumberOfDevicesFunc)(UInt8Type* numberOfDevices);
typedef int (*GetDeviceInfoByIndexFunc)(UInt8Type index, UInt8Type serialNumberSize, CharType* serialNumber, InterfaceType* deviceInterface);
typedef int (*SetSlowFilterPeakingTimeFunc)(const CharType* serialNumber, FloatType* peakingTime);
typedef int (*SetStopConditionFunc)(const CharType* serialNumber, StopConditionType stopConditionType, DoubleType* stopConditionValue);
typedef int (*SetMCANumberOfBinsFunc)(const CharType* serialNumber, UInt16Type* numberOfBins);
typedef int (*SetMCABytesPerBinFunc)(const CharType* serialNumber, UInt8Type* bytesPerBin);
typedef int (*StartRunFunc)(const CharType* serialNumber);
typedef int (*GetRunStatisticsFunc)(const CharType* serialNumber, RunStatisticsType* runStatistics);
typedef int (*GetMCADataUInt32Func)(const CharType* serialNumber, UInt8Type bytesPerBin, UInt16Type numberOfBins, UInt32Type* mcaData);

typedef VICOStatusType (*RefreshDeviceConnectionsFunc)();


class VicoLibrary
{
public:
    // 构造函数：加载 DLL 并解析函数
    VicoLibrary(const QString& dllName);

    // 析构函数：卸载 DLL
    ~VicoLibrary();

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

    // 通用加载函数模板
    template <typename FuncType>
    FuncType loadFunction(const char* functionName);

private:
    QLibrary* vicoLib;  // 用于加载 DLL 的 QLibrary 对象
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
};

#endif // VICO_LIBRARY_H
