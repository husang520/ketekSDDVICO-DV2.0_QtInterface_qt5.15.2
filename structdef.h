#ifndef STRUCTDEF_H
#define STRUCTDEF_H
#include <QString>

#include <./VICOLib_impl/types.h>


#define VICO_SERIAL_MAX_LEN    64

typedef struct {
    UInt8Type numberOfDevices;  // 设备数量
    CharType serialNumber[VICO_SERIAL_MAX_LEN];  // 设备序列号 后面的大多数函数都是需要使用该序列号的
    CharType infoOfInterface[VICO_SERIAL_MAX_LEN];    // 设备类型：USB 或者 Ethernet
    FloatType peakingTime;      // peaking 时间
    DoubleType measureTime;     // 测量时间
    StopConditionType stopConditionType;    // 停止条件类型
    UInt16Type numberOfBins;    // Bin 的数量
    UInt8Type bytesPerBin;      // 每个 Bin 的字节数量
    RunStatisticsType runStatistics;      // 运行策略类型结构体
    UInt16Type mcaSize;         // mca 数据的大小
    UInt32Type* mcaData;    // mca 数据

    VICOStatusType vicostatype; // vico 的状态类型
    VersionType libraryVersion; // vico 库版本类型
    VersionType daemonVersion;  // daemon 服务版本类型
    MCUStatusInfoType mcuStatus; // MCU 信息类型
    FirmwareVersionType version; // 硬件版本
    UInt16Type temperature;    // DPP 板载温度
    LiveInfo2VICOType liveInfo;    // vico 信息 里面很多 都是关于 mcu 的
    SoftwarePackage swPkg; // 用于标识现在处于什么状态 有的函数必须是 应用状态才能使用
    LiveInfo2VIAMPType liveInfo_viamp;  // viamp 信息 都是关于 sdd 的


} VICOLib_DeviceContext;

#endif // STRUCTDEF_H
