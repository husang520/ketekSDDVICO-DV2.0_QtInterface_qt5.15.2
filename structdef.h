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


} VICOLib_DeviceContext;

#endif // STRUCTDEF_H
