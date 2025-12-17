#ifndef VICOLIB_H
#define VICOLIB_H

#include "types.h"
#include "vicolibglobal.h"
#ifdef __cplusplus
extern "C"
{
#endif

/**
 * Reads the major-, minor-, patch-, and build-version of the VICOLib.
 * @param[out] libraryVersion the major-, minor-, patch-, and build-version struct.
 * @return status #VICO_SUCCESS if the version was read successfully, #VICO_INVALID_ARGUMENT_ERROR if parameter libraryVersion is null, #VICO_UNDEFINED_ERROR if the version could not be retrieved from the library.
 */
VICOLIB_API VICOStatusType getLibraryVersion(VersionType* libraryVersion);

/**
 * Reads the major-, minor-, patch-, and build-version of the VICODaemon.
 * @param[out] daemonVersion the major-, minor-, patch-, and build-version struct.
 * @return status #VICO_SUCCESS if the version was read successfully, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #VICO_INVALID_ARGUMENT_ERROR if parameter daemonVersion is null, #VICO_UNDEFINED_ERROR if the version could not be retrieved from the library.
 */
VICOLIB_API VICOStatusType getDaemonVersion(VersionType* daemonVersion);

/**
 * Scans for TCP-connected ethernet devices between the range of given ip addresses.
 * Builds up a lasting connection to all found TCP devices in the VICODaemon.
 * @param[in] fromIpAddress the beginning ip of the ip range to be scanned.
 * @param[in] toIpAddress the end ip of the ip range to be scanned.
 * @return status #VICO_SUCCESS if the tcp scan was performed successfully, #VICO_INVALID_ARGUMENT_ERROR if fromIpAddress or toIpAddress is not a valid ipv4 address, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running.
 */
VICOLIB_API VICOStatusType scanTcpDevices(const CharType* fromIpAddress, const CharType* toIpAddress);

/**
 * Scans for UDP-connected ethernet devices by performing a directed broadcast in VICODaemon.
 * UDP devices can be found inputting a target net address (e.g. 192.168.0.0) with target netmask (e.g. 24 which means 255.255.255.0).
 * Builds up a lasting connection to all found UDP devices in the VICODaemon.
 * @param[in] netaddress the network address of the network to be scanned (e.g. 192.168.0.0)
 * @param[in] netmask the netmask prefix length of the network to be scanned (e.g. 24 for 255.255.255.0)
 * @return status #VICO_SUCCESS if the udp scan was performed successfully, #VICO_INVALID_ARGUMENT_ERROR if netaddress is not a valid ipv4 address, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running.
 */
VICOLIB_API VICOStatusType scanUdpDevices(const CharType* netaddress, const UInt8Type netmask);

/**
 * Scans for USB-connected devices and builds up a lasting connection to all found USB devices in the VICODaemon.
 * @return status #VICO_SUCCESS if the usb scan was performed successfully, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running.
 */
VICOLIB_API VICOStatusType scanUsbDevices();

/**
 * Reads the number of devices currently maintained by the VICODaemon.
 * After scanning for devices (TCP, UDP, USB) VICODaemon maintains certain device connections.
 * This function Reads the number devices currently maintained by the VICODaemon.
 * @param[out] numberOfDevices the number of devices currently maintained by the VICODaemon.
 * @return status #VICO_SUCCESS if the number of devices was retrieved successfully, #VICO_INVALID_ARGUMENT_ERROR if parameter numberOfDevices is null, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running.
 */
VICOLIB_API VICOStatusType getNumberOfDevices(UInt8Type* numberOfDevices);

/**
 * Reads the preferred interface for a certain device currently set in the VICODaemon.
 * Setting a preferred interface is optional. However in cases, where a device is connected to the host
 * with multiple interfaces, e.g. by USB and TCP, you might prefer a certain interface over another.
 * If no preferred interface is set, the first found active device connection will be used.
 * @param[in] serialNumber the target device.
 * @param[out] deviceInterface the target preferred interface to be retrieved.
 * @return status #VICO_SUCCESS if the preferred interface was retrieved successfully, #VICO_INVALID_ARGUMENT_ERROR if parameter serialNumber or deviceInterface is null, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running.
 */
VICOLIB_API VICOStatusType getPreferredInterface(const CharType* serialNumber, InterfaceType* deviceInterface);

/**
 * Sets the preferred interface for a certain device in the VICODaemon.
 * Setting a preferred interface is optional. However in cases, where a device is connected to the host
 * with multiple interfaces, e.g. by USB and TCP, you might prefer a certain interface over another.
 * If no preferred interface is set, the first found active device connection will be used.
 * @param[in] serialNumber the target device.
 * @param[in] deviceInterface the target preferred interface to be set.
 * @return status #VICO_SUCCESS if the preferred interface was set successfully, #VICO_INVALID_ARGUMENT_ERROR if parameter serialNumber or deviceInterface is null, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running.
 */
VICOLIB_API VICOStatusType setPreferredInterface(const CharType* serialNumber, InterfaceType deviceInterface);

/**
 * Reads the device informations of a device connected within VICODaemon.
 * The entered index Reads the information for the device connection maintained by VICODaemon under that index.
 * @param[in] index the index in which the VICODaemon currently maintains a device connection.
 * @param[in] serialNumberSize the size of the serial number array. The default serial number size is 12.
 * @param[out] serialNumber the serial number of the device currently connected under the given index.
 * @param[out] deviceInterface the device interface of the device currently connected under the given index. The interface is either TCP, UDP, USB (via FT4222), or USB_HID (via HID).
 * @return status #VICO_SUCCESS if the device infos were retrieved successfully, #VICO_INVALID_ARGUMENT_ERROR if parameter serialNumber or deviceInterface is null, #VICO_RESPONSE_OUT_OF_BOUNDS_ERROR if the response data is bigger than parameter serialNumberSize, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running.
 */
VICOLIB_API VICOStatusType getDeviceInfoByIndex(const UInt8Type index, const UInt8Type serialNumberSize, CharType* serialNumber, InterfaceType* deviceInterface);

/**
 * Refreshes the latest active device connections by pinging the devices with a dummy request.
 * If the device answers, it is considered as connected and will be kept active.
 * If the device doesn't answer, it is considered as disconnected and will be closed and removed from VICODaemon.
 * @return status #VICO_SUCCESS if the device connections were refreshed successfully, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running.
 */
VICOLIB_API VICOStatusType refreshDeviceConnections();

/**
 * Cancels scanning the TCP range requested by the device scanning.
 * Especially in cases, where broader TCP range scans are performed, the scanning can occupy much time.
 * @return status #VICO_SUCCESS if the TCP scan was stopped successfully, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running.
 */
VICOLIB_API VICOStatusType cancelTcpScan();

/**
 * Cancels scanning the UDP range requested by the device scanning.
 * @return status #VICO_SUCCESS if the UDP scan was stopped successfully, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running.
 */
VICOLIB_API VICOStatusType cancelUdpScan();

/**
 * Starts the acquisition of MCA data within the DPP.
 * @param[in] serialNumber the target device.
 * @return status #DPP_SUCCESS if the MCA data acquisition on the DPP was started successfully, #DPP_REQUEST_CURRENTLY_NOT_POSSIBLE_ERROR if MCA data acquisition is already active in the DPP or if analog hardware powerdown is enabled, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber is null, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType startRun(const CharType* serialNumber);

/**
 * Resumes the acquisition of exiting MCA data within the DPP, when before this request stopRun was requested.
 * @param[in] serialNumber the target device.
 * @return status #DPP_SUCCESS if the MCA data acquisition on the DPP was started successfully, #DPP_REQUEST_CURRENTLY_NOT_POSSIBLE_ERROR if MCA data acquisition is already active in the DPP or if analog hardware powerdown is enabled, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber is null, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType resumeRun(const CharType* serialNumber);

/**
 * Stops the acquisition of MCA data within the DPP, when before this request startRun or resumeRun was requested.
 * @param[in] serialNumber the target device.
 * @return status #DPP_SUCCESS if the MCA data acquisition on the DPP was started successfully, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber is null, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType stopRun(const CharType* serialNumber);

/**
 * Reads the stop condition type and stop condition value for the MCA data acquisition in counts or seconds.
 * If the stop condition type is set to a fixed number of counts (i.e. #STOP_AT_FIXED_INPUT_COUNTS, or #STOP_AT_FIXED_OUTPUT_COUNTS) the corresponding stop condition value
 * will be state the amount of counts. The valid range of counts is 0 - 4294967295.
 * If the stop condition type is set to a fixed time (#STOP_AT_FIXED_LIVETIME, or #STOP_AT_FIXED_REALTIME) the corresponding stop condition value will be returned
 * in seconds. The value is a quantized in 10µs. The valid range of time is 0s - 42949s.
 * @param[in] serialNumber the target device.
 * @param[out] stopConditionType the stop condition type to be retrieved.
 * @param[out] stopConditionValue the stop condition value to be retrieved.
 * @return status #DPP_SUCCESS if the stop condition type and stop condition were successfully read, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber, stopConditionType or stopConditionValue is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType getStopCondition(const CharType* serialNumber, StopConditionType* stopConditionType, DoubleType* stopConditionValue);

/**
 * Sets the stop condition type and stop condition value for MCA data acquisition.
 * If the stop condition type is #NONE the stop condition value has no influence.\n
 * If the stop condition type is #STOP_AT_FIXED_INPUT_COUNTS or #STOP_AT_FIXED_OUTPUT_COUNTS the stop condition value defines the amount of counts. The valid range in this case is 0 - 4294967295 counts.\n
 * If the stop condition type is #STOP_AT_FIXED_LIVETIME or #STOP_AT_FIXED_REALTIME the stop condition value defines the fixed time in seconds. The valid range in this case is 0 - 42949.67295s. The time has do be a multiple of 10µs in order to be applied on the DPP.
 * @param[in] serialNumber the target device.
 * @param[in] stopConditionType the stop condition type to be applied.
 * @param[in] stopConditionValue the stop condition value to be applied.
 * @return status #DPP_SUCCESS if the stop condition type and stop condition were successfully set, #DPP_VICOLIB_OUT_OF_RANGE_ERROR if the stopConditionType is set to #STOP_AT_FIXED_INPUT_COUNTS or #STOP_AT_FIXED_OUTPUT_COUNTS and the stopConditionValue is not an UINT32, #DPP_VICOLIB_OUT_OF_RANGE_ERROR if the stopConditionType is set to #STOP_AT_FIXED_LIVETIME or #STOP_AT_FIXED_REALTIME and the StopConditionValue is not a multiple of 10µs, #DPP_OUT_OF_RANGE_ERROR if the value in stopConditionValue is not in valid range, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber, stopConditionType or stopConditionValue is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType setStopCondition(const CharType* serialNumber, StopConditionType stopConditionType, DoubleType* stopConditionValue);

/**
 * Reads the current run status of a run to distinguish whether a MCA data acquisition is currently running on the device or not.
 * @param[in] serialNumber the target device.
 * @param[out] isRunActive true if a run is active, false if no run is active.
 * @return status #DPP_SUCCESS if the value was successfully read, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber or isRunActive is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType getRunStatus(const CharType* serialNumber, BooleanType* isRunActive);

/**
 * Reads the realtime of a run in seconds. Will read 0 if the target device has not acquired MCA data yet.
 * @param[in] serialNumber the target device.
 * @param[out] realtime the realtime of a run in seconds.
 * @return status #DPP_SUCCESS if the value was successfully read, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber or realtime is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType getRunRealtime(const CharType* serialNumber, DoubleType* realtime);

/**
 * Reads the livetime of a run in seconds. Will read 0 if the target device has not acquired MCA data yet.
 * @param[in] serialNumber the target device.
 * @param[out] livetime the livetime of a run in seconds.
 * @return status #DPP_SUCCESS if the value was successfully read, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber or livetime is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType getRunLivetime(const CharType* serialNumber, DoubleType* livetime);

/**
 * Reads the output counts of a run. Will read 0 if the target device has not acquired MCA data yet.
 * @param[in] serialNumber the target device.
 * @param[out] outputCounts the output counts of a run in counts.
 * @return status #DPP_SUCCESS if the value was successfully read, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber or outputCounts is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType getRunOutputCounts(const CharType* serialNumber, UInt32Type* outputCounts);

/**
 * Reads the input counts of a run. Will read 0 if the target device has not acquired MCA data yet.
 * @param[in] serialNumber the target device.
 * @param[out] inputCounts the input counts of a run in counts.
 * @return status #DPP_SUCCESS if the value was successfully read, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber or inputCounts is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType getRunInputCounts(const CharType* serialNumber, UInt32Type* inputCounts);

/**
 * Reads the output count rate of a run in counts per second. Will read 0 if the target device has not acquired MCA data yet.
 * @param[in] serialNumber the target device.
 * @param[out] outputCountRate the output count rate of a run in counts per second.
 * @return status #DPP_SUCCESS if the value was successfully read, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber or outputCountRate is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType getRunOutputCountRate(const CharType* serialNumber, UInt32Type* outputCountRate);

/**
 * Reads the input count rate of a run in counts per second. Will read 0 if the target device has not acquired MCA data yet.
 * @param[in] serialNumber the target device.
 * @param[out] inputCountRate the input count rate of a run in counts per second.
 * @return status #DPP_SUCCESS if the value was successfully read, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber or inputCountRate is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType getRunInputCountRate(const CharType* serialNumber, UInt32Type* inputCountRate);

/**
 * Reads all run statistics parameters simultaneously. These are run status as boolean, run realtime in seconds, run livetime in seconds, run output counts in counts, run input counts in counts,
 * run output count rate in counts per second, run input count rate in counts per second.
 * @param[in] serialNumber the target device.
 * @param[out] runStatistics the struct to retrieve run status as boolean, run realtime in seconds, run livetime in seconds, run output counts in counts, run input counts in counts,
 * run output count rate in counts per second, run input count rate in counts per second.
 * @return status #DPP_SUCCESS if the value was successfully read, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber or runStatistics is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType getRunStatistics(const CharType* serialNumber, RunStatisticsType* runStatistics);

/**
 * Reads the raw MCA data byte array of a current run and does not apply any conversion. Each UInt8 represents one byte of the data array. This method of reading MCA data has optimum memory efficiency but the user has to convert the byte array manually to counts. 
 
 The size of the MCA data is distinguished by set MCA number of bins with range 512-8192 multiplied by the MCA bytes per bin with range 1-3.
 * @param[in] serialNumber the target device.
 * @param[in] mcaDataSize the size of the MCA data to read, distinguished by set MCA number of bins with range 512-8192 multiplied by the MCA bytes per bin with range 1-3.
 * @param[out] mcaData the array to read the raw MCA data of the current run.
 * @return status #DPP_SUCCESS if the MCA data byte array was successfully read, #DPP_TIMEOUT_ERROR if a timeout appeared on the DPP, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_RESPONSE_OUT_OF_BOUNDS_ERROR if the response data size does not fit in the given mcaData array (e.g., argument mcaDataSize does not match with values in the device: use #getMCANumberOfBins() and #getMCABytesPerBin() to find out the settings in the device), #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber, mcaDataSize or mcaData is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType getMCADataRaw(const CharType* serialNumber, UInt16Type mcaDataSize, UInt8Type* mcaData);

/**
 * Reads the raw MCA data byte array of a current run and converts the values to UInt32 using the bytesPerBin passed to the function. Each UInt32 represents the counts in one MCA bin. This method of reading MCA data has non-optimum memory efficiency if the bytesPerBin is not equal to 3.
 
 The size of the MCA data is expected to be the set MCA number of bins with range 512-8192.
 * @param[in] serialNumber the target device.
 * @param[in] bytesPerBin the set MCA bytes per bin with range of 1-3.
 * @param[in] numberOfBins the set MCA number of bins with range 512-8192.
 * @param[out] mcaData the array to read the MCA data of the current run.
 * @return status #DPP_SUCCESS if the MCA data byte array was successfully read and converted to UInt32, #DPP_TIMEOUT_ERROR if a timeout appeared on the DPP, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_RESPONSE_OUT_OF_BOUNDS_ERROR if the response data size does not fit in the given mcaData array (e.g., argument mcaDataSize does not match with values in the device: use #getMCANumberOfBins() and #getMCABytesPerBin() to find out the settings in the device), #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber or mcaData is null or if bytesPerBin or numberOfBins are out of the valid range or null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType getMCADataUInt32(const CharType* serialNumber, UInt8Type bytesPerBin, UInt16Type numberOfBins, UInt32Type* mcaData);

/**
 * Reads the raw MCA data byte array of a current run and converts the values to UInt8. Each UInt8 represents the counts in one MCA bin. This method of reading MCA data has optimum memory efficiency but the conversation only works if bytesPerBin is set to 1 on the device.
 
 The size of the MCA data is expected to be the set MCA number of bins with range 512-8192.
 * @param[in] serialNumber the target device.
 * @param[in] numberOfBins the set MCA number of bins with range 512-8192.
 * @param[out] mcaData the array to read the MCA data of the current run.
 * @return status #DPP_SUCCESS if the MCA data byte array was successfully read and converted to UInt8, #DPP_TIMEOUT_ERROR if a timeout appeared on the DPP, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_RESPONSE_OUT_OF_BOUNDS_ERROR if the response data size does not fit in the given mcaData array (e.g., argument mcaDataSize does not match with values in the device: use #getMCANumberOfBins() and #getMCABytesPerBin() to find out the settings in the device), #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber or mcaData is null or if numberOfBins is out of the valid range or null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType getMCAData1BytePerBin(const CharType* serialNumber, UInt16Type numberOfBins, UInt8Type* mcaData);

/**
 * Reads the raw MCA data byte array of a current run and converts the values to UInt16. Each UInt16 represents the counts in one MCA bin. This method of reading MCA data has optimum memory efficiency but the conversation only works if bytesPerBin is set to 2 on the device.
 
 The size of the MCA data is expected to be the set MCA number of bins with range 512-8192. 
 * @param[in] serialNumber the target device.
 * @param[in] numberOfBins the set MCA number of bins with range 512-8192.
 * @param[out] mcaData the array to read the MCA data of the current run.
 * @return status #DPP_SUCCESS if the MCA data byte array was successfully read and converted to UInt16, #DPP_TIMEOUT_ERROR if a timeout appeared on the DPP, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_RESPONSE_OUT_OF_BOUNDS_ERROR if the response data size does not fit in the given mcaData array (e.g., argument mcaDataSize does not match with values in the device: use #getMCANumberOfBins() and #getMCABytesPerBin() to find out the settings in the device), #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber or mcaData is null or if numberOfBins is out of the valid range or null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType getMCAData2BytesPerBin(const CharType* serialNumber, UInt16Type numberOfBins, UInt16Type* mcaData);

/**
 * Reads the raw MCA data byte array of a current run and converts the values to UInt32. Each UInt32 represents the counts in one MCA bin. This method of reading MCA data has optimum memory efficiency but the conversation only works if bytesPerBin is set to 3 on the device.
 
 The size of the MCA data is expected to be the set MCA number of bins with range 512-8192. 
 * @param[in] serialNumber the target device.
 * @param[in] numberOfBins the set MCA number of bins with range 512-8192.
 * @param[out] mcaData the array to read the MCA data of the current run.
 * @return status #DPP_SUCCESS if the MCA data byte array was successfully read and converted to UInt32, #DPP_TIMEOUT_ERROR if a timeout appeared on the DPP, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_RESPONSE_OUT_OF_BOUNDS_ERROR if the response data size does not fit in the given mcaData array (e.g., argument mcaDataSize does not match with values in the device: use #getMCANumberOfBins() and #getMCABytesPerBin() to find out the settings in the device), #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber or mcaData is null or if numberOfBins is out of the valid range or null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType getMCAData3BytesPerBin(const CharType* serialNumber, UInt16Type numberOfBins, UInt32Type* mcaData);

/**
 * Sets the MCA number of bins. Valid values are 512, 1024, 2048, 4096 and 8192.
 * @param[in] serialNumber the target device.
 * @param[in] numberOfBins the MCA number of bins with valid values 512, 1024, 2048, 4096 and 8192.
 * @return status #DPP_SUCCESS if the value was successfully set, #DPP_VICOLIB_OUT_OF_RANGE_ERROR if the numberOfBins is not a valid value, #DPP_REQUEST_CURRENTLY_NOT_POSSIBLE_ERROR if MCA data acquisition is active, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber or numberOfBins is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).

 */
VICOLIB_API DPPStatusType setMCANumberOfBins(const CharType* serialNumber, UInt16Type* numberOfBins);

/**
 * Reads the MCA number of bins. Valid values are 512, 1024, 2048, 4096 and 8192.
 * @param[in] serialNumber the target device.
 * @param[out] numberOfBins the MCA number of bins with valid values 512, 1024, 2048, 4096 and 8192.
 * @return status #DPP_SUCCESS if the value was successfully read, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber or numberOfBins is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType getMCANumberOfBins(const CharType* serialNumber, UInt16Type* numberOfBins);

/**
 * Sets the MCA bytes per bin. The valid range is 1-3. If a given value is not within the range of 1-3, #DPP_OUT_OF_RANGE_ERROR will be returned along with the closest valid value in the parameter bytesPerBin.
 * @param[in] serialNumber the target device.
 * @param[in] bytesPerBin the MCA bytes per bin with a range between 1 and 3.
 * @return status #DPP_SUCCESS if the value was successfully set, #DPP_VICOLIB_OUT_OF_RANGE_ERROR if the bytesPerBin is not a valid value, #DPP_REQUEST_CURRENTLY_NOT_POSSIBLE_ERROR if MCA data acquisition is active, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber or bytesPerBin is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType setMCABytesPerBin(const CharType* serialNumber, UInt8Type* bytesPerBin);

/**
 * Reads the MCA bytes per bin. The valid range is 1-3.
 * @param[in] serialNumber the target device.
 * @param[out] bytesPerBin the MCA bytes per bin with a range between 1 and 3.
 * @return status #DPP_SUCCESS if the value was successfully read, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber or bytesPerBin is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType getMCABytesPerBin(const CharType* serialNumber, UInt8Type* bytesPerBin);

/**
 * Sets the peaking time of the fastfilter in nanoseconds. The valid range is 25ns - 500ns. The given peakingTime must be a multiple of 12.5ns otherwise #DPP_VICOLIB_OUT_OF_RANGE_ERROR will be returned along with the closest valid value.
 * @param[in] serialNumber the target device.
 * @param[in] peakingTime the peaking time of the fastfilter in nanoseconds with a range between 25ns and 500ns.
 * @return status #DPP_SUCCESS if the value was successfully set, #DPP_VICOLIB_OUT_OF_RANGE_ERROR if the peakingTime is not in valid range, #DPP_REQUEST_CURRENTLY_NOT_POSSIBLE_ERROR if MCA data acquisition is active, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber or peakingTime is null, #DPP_VICOLIB_OUT_OF_RANGE_ERROR if peakingTime is not an integer multiple of 12.5ns, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType setFastFilterPeakingTime(const CharType* serialNumber, FloatType* peakingTime);

/**
 * Reads the peaking time of the fastfilter in nanoseconds. The valid range is 25ns - 500ns.
 * @param[in] serialNumber the target device.
 * @param[out] peakingTime the peaking time of the fastfilter in nanoseconds with a range between 25ns and 500ns.
 * @return status #DPP_SUCCESS if the value was successfully read, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber or peakingTime is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType getFastFilterPeakingTime(const CharType* serialNumber, FloatType* peakingTime);

/**
 * Reads the gap time of the fastfilter in nanoseconds.
 * @param[in] serialNumber the target device.
 * @param[out] gapTime the gap time of the fastfilter in nanoseconds.
 * @return status #DPP_SUCCESS if the value was successfully read, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber or gapTime is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType getFastFilterGapTime(const CharType* serialNumber, FloatType* gapTime);

/**
 * Reads the peaking time of the mediumfilter in nanoseconds.
 * @param[in] serialNumber the target device.
 * @param[out] peakingTime the peaking time of the mediumfilter in nanoseconds.
 * @return status #DPP_SUCCESS if the value was successfully read, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber or peakingTime is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType getMediumFilterPeakingTime(const CharType* serialNumber, FloatType* peakingTime);

/**
 * Reads the gap time of the mediumfilter in nanoseconds.
 * @param[in] serialNumber the target device.
 * @param[out] gapTime the gap time of the mediumfilter in nanoseconds.
 * @return status #DPP_SUCCESS if the value was successfully read, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber or gapTime is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType getMediumFilterGapTime(const CharType* serialNumber, FloatType* gapTime);

/**
 * Sets the peaking time of the slowfilter in nanoseconds. The valid range is 25ns – 12600ns, with permitted values 12.5ns * (2, 4, 6, 8, 12, n*16).
 * @param[in] serialNumber the target device.
 * @param[in] peakingTime the peaking time of the slowfilter in nanoseconds with a range between 25ns and 12600ns, with permitted values 12.5ns * (2, 4, 6, 8, 12, n*16).
 * @return status #DPP_SUCCESS if the value was successfully set, #DPP_VICOLIB_OUT_OF_RANGE_ERROR if the peakingTime is not a valid value, #DPP_REQUEST_CURRENTLY_NOT_POSSIBLE_ERROR if MCA data acquisition is active, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber or peakingTime is null, #DPP_VICOLIB_OUT_OF_RANGE_ERROR if peakingTime is not an integer multiple of 12.5ns, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType setSlowFilterPeakingTime(const CharType* serialNumber, FloatType* peakingTime);

/**
 * Reads the peaking time of the slowfilter in nanoseconds. The valid range is 25ns – 12600ns, with permitted values 12.5ns * (2, 4, 6, 8, 12, n*16).
 * @param[in] serialNumber the target device.
 * @param[out] peakingTime the peaking time of the slowfilter in nanoseconds with a range between 25ns and 12600ns, with permitted values 12.5ns * (2, 4, 6, 8, 12, n*16).
 * @return status #DPP_SUCCESS if the value was successfully read, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber or peakingTime is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType getSlowFilterPeakingTime(const CharType* serialNumber, FloatType* peakingTime);

/**
 * Sets the gap time of the slowfilter in nanoseconds. The range is 25 – 1587.5ns. The given gapTime must be a multiple of 12.5ns otherwise #DPP_VICOLIB_OUT_OF_RANGE_ERROR will be returned along with the closest valid value.
 * @param[in] serialNumber the target device.
 * @param[in] gapTime the gap time of the slowfilter in nanoseconds with a range between 25 and 1587.5ns.
 * @return status #DPP_SUCCESS if the value was successfully set, #DPP_VICOLIB_OUT_OF_RANGE_ERROR if the gapTime is not a valid value, #DPP_REQUEST_CURRENTLY_NOT_POSSIBLE_ERROR if MCA data acquisition is active, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber or gapTime is null, #DPP_VICOLIB_OUT_OF_RANGE_ERROR if gapTime is not an integer multiple of 12.5ns, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType setSlowFilterGapTime(const CharType* serialNumber, FloatType* gapTime);

/**
 * Reads the gap time of the slowfilter in nanoseconds. The range is 25 – 1587.5ns.
 * @param[in] serialNumber the target device.
 * @param[out] gapTime the gap time of the slowfilter in nanoseconds with a range between 25 and 1587.5ns.
 * @return status #DPP_SUCCESS if the value was successfully read, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber or gapTime is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType getSlowFilterGapTime(const CharType* serialNumber, FloatType* gapTime);

/**
 * Sets the trigger threshold for pulse detection with the fastfilter. The range is 0 - 16384 in an arbitrary unit.
 * @param[in] serialNumber the target device.
 * @param[in] triggerThreshold the trigger threshold for pulse detection with the fastfilter with a range between 0 and 16384 in arbitrary unit.
 * @return status #DPP_SUCCESS if the value was successfully set, #DPP_VICOLIB_OUT_OF_RANGE_ERROR if the triggerThreshold is not a valid value, #DPP_REQUEST_CURRENTLY_NOT_POSSIBLE_ERROR if MCA data acquisition is active, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber or triggerThreshold is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType setFastFilterTriggerThreshold(const CharType* serialNumber, UInt16Type* triggerThreshold);

/**
 * Reads the trigger threshold for pulse detection with the fastfilter. The range is 0 - 16384 in an arbitrary unit.
 * @param[in] serialNumber the target device.
 * @param[out] triggerThreshold the trigger threshold for pulse detection with the fastfilter with a range between 0 and 16384 in arbitrary unit.
 * @return status #DPP_SUCCESS if the value was successfully read, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber or triggerThreshold is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType getFastFilterTriggerThreshold(const CharType* serialNumber, UInt16Type* triggerThreshold);

/**
 * Sets the trigger threshold for pulse detection with the mediumfilter. The range is 0 - 16384 in an arbitrary unit.
 * @param[in] serialNumber the target device.
 * @param[in] triggerThreshold the trigger threshold for pulse detection with the mediumfilter with a range between 0 and 16384 in arbitrary unit.
 * @return status #DPP_SUCCESS if the value was successfully set, #DPP_VICOLIB_OUT_OF_RANGE_ERROR if the triggerThreshold is not a valid value, #DPP_REQUEST_CURRENTLY_NOT_POSSIBLE_ERROR if MCA data acquisition is active, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber or triggerThreshold is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType setMediumFilterTriggerThreshold(const CharType* serialNumber, UInt16Type* triggerThreshold);

/**
 * Reads the trigger threshold for pulse detection with the mediumfilter. The range is 0 - 16384 in an arbitrary unit.
 * @param[in] serialNumber the target device.
 * @param[out] triggerThreshold the trigger threshold for pulse detection with the mediumfilter with a range between 0 and 16384 in arbitrary unit.
 * @return status #DPP_SUCCESS if the value was successfully read, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber or triggerThreshold is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType getMediumFilterTriggerThreshold(const CharType* serialNumber, UInt16Type* triggerThreshold);

/**
 * Enables the utilization of the mediumfilter for pulse detection.\n
   If enabled both fast- and mediumfilter will be used for pulse detection. If disabled only the fastfilter will be used for pulse detection.
 * @param[in] serialNumber the target device.
 * @return status #DPP_SUCCESS if successfully enabled, #DPP_REQUEST_CURRENTLY_NOT_POSSIBLE_ERROR if MCA data acquisition is active, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType enableMediumFilterPulseDetection(const CharType* serialNumber);

/**
 * Disables the utilization of the mediumfilter for pulse detection.\n
   If enabled both fast- and mediumfilter will be used for pulse detection. If disabled only the fastfilter will be used for pulse detection.
 * @param[in] serialNumber the target device.
 * @return status #DPP_SUCCESS if successfully disabled, #DPP_REQUEST_CURRENTLY_NOT_POSSIBLE_ERROR if MCA data acquisition is active, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType disableMediumFilterPulseDetection(const CharType* serialNumber);

/**
 * Reads whether the utilization of the mediumfilter for pulse detection is enabled or disabled.\n
   If enabled both fast- and mediumfilter will be used for pulse detection. If disabled only the fastfilter will be used for pulse detection.
 * @param[in] serialNumber the target device.
 * @param[out] enabled which is true if the mediumfilter for pulse detection is enabled, false if disabled.
 * @return status #DPP_SUCCESS if the value was successfully read, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber or enabled is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType isMediumFilterPulseDetectionEnabled(const CharType* serialNumber, BooleanType* enabled);

/**
 * Sets the maximum width of the fastfilter in nanoseconds. The range is 0ns - 3187.5ns. The given maxWidth must be a multiple of 12.5ns otherwise #DPP_VICOLIB_OUT_OF_RANGE_ERROR will be returned along with the closest valid value.
 * @param[in] serialNumber the target device.
 * @param[in] maxWidth the maximum width of the fastfilter in nanoseconds with a range between 0ns and 3187.5ns.
 * @return status #DPP_SUCCESS if the value was successfully set, #DPP_VICOLIB_OUT_OF_RANGE_ERROR if the maxWidth is not in valid range, #DPP_REQUEST_CURRENTLY_NOT_POSSIBLE_ERROR if MCA data acquisition is active, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber or maxWidth is null, #DPP_VICOLIB_OUT_OF_RANGE_ERROR if maxWidth is not an integer multiple of 12.5ns, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType setFastFilterMaxWidth(const CharType* serialNumber, FloatType* maxWidth);

/**
 * Reads the maximum width of the fastfilter in nanoseconds. The range is 0ns - 3187.5ns.
 * @param[in] serialNumber the target device.
 * @param[out] maxWidth the maximum width of the fastfilter in nanoseconds with a range between 0ns and 3187.5ns.
 * @return status #DPP_SUCCESS if the value was successfully read, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber or maxWidth is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType getFastFilterMaxWidth(const CharType* serialNumber, FloatType* maxWidth);

/**
 * Sets the maximum width of the mediumfilter in nanoseconds. The range is 0ns - 12787.5ns. The given maxWidth must be a multiple of 12.5ns otherwise #DPP_VICOLIB_OUT_OF_RANGE_ERROR will be returned along with the closest valid value.
 * @param[in] serialNumber the target device.
 * @param[in] maxWidth the maximum width of the mediumfilter in nanoseconds with a range between 0ns - 12787.5ns.
 * @return status #DPP_SUCCESS if the value was successfully set, #DPP_VICOLIB_OUT_OF_RANGE_ERROR if the maxWidth is not in valid range, #DPP_REQUEST_CURRENTLY_NOT_POSSIBLE_ERROR if MCA data acquisition is active, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber or maxWidth is null, #DPP_VICOLIB_OUT_OF_RANGE_ERROR if maxWidth is not an integer multiple of 12.5ns, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType setMediumFilterMaxWidth(const CharType* serialNumber, FloatType* maxWidth);

/**
 * Reads the maximum width of the mediumfilter in nanoseconds. The range is 0ns - 12787.5ns.
 * @param[in] serialNumber the target device.
 * @param[out] maxWidth the maximum width of the mediumfilter in nanoseconds with a range between 0ns - 12787.5ns.
 * @return status #DPP_SUCCESS if the value was successfully read, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber or maxWidth is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType getMediumFilterMaxWidth(const CharType* serialNumber, FloatType* maxWidth);

/**
 * Sets the inhibit time after detection of a reset in nanoseconds. The range is 0ns - 3187.5ns. The given resetInhibitTime must be a multiple of 12.5ns otherwise #DPP_VICOLIB_OUT_OF_RANGE_ERROR will be returned along with the closest valid value.
 * @param[in] serialNumber the target device.
 * @param[in] resetInhibitTime the inhibit time after detection of a reset in nanoseconds with a range between 0ns - 3187.5ns.
 * @return status #DPP_SUCCESS if the value was successfully set, #DPP_VICOLIB_OUT_OF_RANGE_ERROR if the resetInhibitTime is not in valid range, #DPP_REQUEST_CURRENTLY_NOT_POSSIBLE_ERROR if MCA data acquisition is active, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber or resetInhibitTime is null, #DPP_VICOLIB_OUT_OF_RANGE_ERROR if resetInhibitTime is not an integer multiple of 12.5ns, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType setResetInhibitTime(const CharType* serialNumber, FloatType* resetInhibitTime);

/**
 * Reads the inhibit time after detection of a reset in nanoseconds. The range is 0ns - 3187.5ns.
 * @param[in] serialNumber the target device.
 * @param[out] resetInhibitTime the inhibit time after detection of a reset in nanoseconds with a range between 0ns - 3187.5ns.
 * @return status #DPP_SUCCESS if the value was successfully read, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber or resetInhibitTime is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType getResetInhibitTime(const CharType* serialNumber, FloatType* resetInhibitTime);

/**
 * Sets the length of running average for baseline mean value as 2^x. The range is 1 - 8.
 * @param[in] serialNumber the target device.
 * @param[in] averageLength the length of running average for baseline mean value as 2^x, with a range between 1 and 8.
 * @return status #DPP_SUCCESS if the value was successfully set, #DPP_VICOLIB_OUT_OF_RANGE_ERROR if the averageLength is not in valid range, #DPP_REQUEST_CURRENTLY_NOT_POSSIBLE_ERROR if MCA data acquisition is active, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber or averageLength is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType setBaselineAverageLength(const CharType* serialNumber, UInt8Type* averageLength);

/**
 * Reads the length of running average for baseline mean value as 2^x. The range is 1 - 8.
 * @param[in] serialNumber the target device.
 * @param[out] averageLength the length of running average for baseline mean value as 2^x, with a range between 1 and 8.
 * @return status #DPP_SUCCESS if the value was successfully set, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber or averageLength is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType getBaselineAverageLength(const CharType* serialNumber, UInt8Type* averageLength);

/**
 * Sets the type of the baseline trim, from the longest to the shortest possible medium filter.
 * @param[in] serialNumber the target device.
 * @param[in] baselineTrim the type of the baseline trim, from the longest to the shortest possible medium filter.
 * @return status #DPP_SUCCESS if the value was successfully set, #DPP_REQUEST_CURRENTLY_NOT_POSSIBLE_ERROR if MCA data acquisition is active, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber or baselineTrim is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType setBaselineTrim(const CharType* serialNumber, BaselineTrimType baselineTrim);

/**
 * Reads the type of the baseline trim, from the longest to the shortest possible medium filter.
 * @param[in] serialNumber the target device.
 * @param[out] baselineTrim the type of the baseline trim, from the longest to the shortest possible medium filter.
 * @return status #DPP_SUCCESS if the value was successfully read, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber or baselineTrim is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType getBaselineTrim(const CharType* serialNumber, BaselineTrimType* baselineTrim);

/**
 * Enables the utilization of baseline correction.
 * @param[in] serialNumber the target device.
 * @return status #DPP_SUCCESS if successfully enabled, #DPP_REQUEST_CURRENTLY_NOT_POSSIBLE_ERROR if MCA data acquisition is active, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType enableBaselineCorrection(const CharType* serialNumber);

/**
 * Disables the utilization of baseline correction.
 * @param[in] serialNumber the target device.
 * @return status #DPP_SUCCESS if successfully disabled, #DPP_REQUEST_CURRENTLY_NOT_POSSIBLE_ERROR if MCA data acquisition is active, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType disableBaselineCorrection(const CharType* serialNumber);

/**
 * Reads whether the utilization of baseline correction is enabled or disabled.
 * @param[in] serialNumber the target device.
 * @param[out] enabled which is true if the utilization of baseline correction is enabled, false if disabled.
 * @return status #DPP_SUCCESS if the value was successfully read, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber or enabled is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType isBaselineCorrectionEnabled(const CharType* serialNumber, BooleanType* enabled);

/**
 * Sets the value for the digital gain for energy values. The range is 0 - 16383. The unit is an arbitrary unit. Since every energy value will be multiplied with the digital energy gain, large values will "stretch" and small values will "compress" the energy spectrum in the MCA data.
 * Examples: 
 * - A digital energy gain value of 5461 can be used for an MCA bin width of approximately 5eV/bin.
 * - A digital energy gain value of 4096 can be used for an MCA bin width of approximately 6.67eV/bin.
 * - A digital energy gain value of 2730 can be used for an MCA bin width of approximately 10eV/bin.
 * - A digital energy gain value of 1365 can be used for an MCA bin width of approximately 20eV/bin.
 * - A digital energy gain value of 10922 can be used for an MCA bin width of approximately 2.5eV/bin.
 * @param[in] serialNumber the target device.
 * @param[in] gain the value for the digital gain for energy values. The range is 0 - 16383.
 * @return status #DPP_SUCCESS if the value was successfully set, #DPP_VICOLIB_OUT_OF_RANGE_ERROR if the gain is not in valid range, #DPP_REQUEST_CURRENTLY_NOT_POSSIBLE_ERROR if MCA data acquisition is active, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber or gain is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType setDigitalEnergyGain(const CharType* serialNumber, UInt16Type* gain);

/**
 * Reads the value for the digital gain for energy values. The range is 0 - 16383. The unit is an arbitrary unit. Since every energy value will be multiplied with the digital energy gain, large values will "stretch" and small values will "compress" the energy spectrum in the MCA data.
 * Examples: 
 * - A digital energy gain value of 5461 can be used for an MCA bin width of approximately 5eV/bin.
 * - A digital energy gain value of 4096 can be used for an MCA bin width of approximately 6.67eV/bin.
 * - A digital energy gain value of 2730 can be used for an MCA bin width of approximately 10eV/bin.
 * - A digital energy gain value of 1365 can be used for an MCA bin width of approximately 20eV/bin.
 * - A digital energy gain value of 10922 can be used for an MCA bin width of approximately 2.5eV/bin.
 * @param[in] serialNumber the target device.
 * @param[out] gain the value for the digital gain for energy values. The range is 0 - 16383.
 * @return status #DPP_SUCCESS if the value was successfully read, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber or gain is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType getDigitalEnergyGain(const CharType* serialNumber, UInt16Type* gain);

/**
 * Sets the value for the digital offset for energy values. The range is 0 - 65535. The unit is an arbitrary unit for which 32768 equals to zero offset, 0 equals to a negative offset of 256 bins and 65535 equals to a positive offset of 256 bins.
 * @param[in] serialNumber the target device.
 * @param[in] offset the value for the digital offset for energy values. The range is 0 - 65535.
 * @return status #DPP_SUCCESS if the value was successfully set, #DPP_VICOLIB_OUT_OF_RANGE_ERROR if the offset is not in valid range, #DPP_REQUEST_CURRENTLY_NOT_POSSIBLE_ERROR if MCA data acquisition is active, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber or offset is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType setDigitalEnergyOffset(const CharType* serialNumber, UInt16Type offset);

/**
 * Reads the value for the digital offset for energy values. The range is 0 - 65535. The unit is an arbitrary unit for which 32768 equals to zero offset, 0 equals to a negative offset of 256 bins and 65535 equals to a positive offset of 256 bins.
 * @param[in] serialNumber the target device.
 * @param[out] offset the value for the digital offset for energy values. The range is 0 - 65535.
 * @return status #DPP_SUCCESS if the value was successfully read, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber or offset is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType getDigitalEnergyOffset(const CharType* serialNumber, UInt16Type* offset);

/**
 * Enables the utilization of dynamic reset.
 * @param[in] serialNumber the target device.
 * @return status #DPP_SUCCESS if successfully enabled, #DPP_REQUEST_CURRENTLY_NOT_POSSIBLE_ERROR if MCA data acquisition is active, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType enableDynamicReset(const CharType* serialNumber);

/**
 * Disables the utilization of dynamic reset.
 * @param[in] serialNumber the target device.
 * @return status #DPP_SUCCESS if successfully disabled, #DPP_REQUEST_CURRENTLY_NOT_POSSIBLE_ERROR if MCA data acquisition is active, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType disableDynamicReset(const CharType* serialNumber);

/**
 * Reads whether the utilization of dynamic reset is enabled or disabled.
 * @param[in] serialNumber the target device.
 * @param[out] enabled which is true if the utilization of dynamic reset is enabled, false if disabled.
 * @return status #DPP_SUCCESS if the value was successfully read, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber or enabled is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType isDynamicResetEnabled(const CharType* serialNumber, BooleanType* enabled);

/**
 * Sets the threshold of the dynamic reset. The range is 0 - 65535, which represents an ADC-Code (1LSB=30µV), leading to a range from 0=-1V; 65535=+1V.
 * @param[in] serialNumber the target device.
 * @param[in] threshold the threshold of the dynamic reset with a range between 0 - 65535, which represents an ADC-Code (1LSB=30µV), leading to a range from 0=-1V; 65535=+1V.
 * @return status #DPP_SUCCESS if the value was successfully set, #DPP_VICOLIB_OUT_OF_RANGE_ERROR if the threshold is not in valid range, #DPP_REQUEST_CURRENTLY_NOT_POSSIBLE_ERROR if MCA data acquisition is active, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber or threshold is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType setDynamicResetThreshold(const CharType* serialNumber, UInt16Type* threshold);

/**
 * Reads the threshold of the dynamic reset. The range is 0 - 65535, which represents an ADC-Code (1LSB=30µV), leading to a range from 0=-1V; 65535=+1V.
 * @param[in] serialNumber the target device.
 * @param[out] threshold the threshold of the dynamic reset with a range between 0 - 65535, which represents an ADC-Code (1LSB=30µV), leading to a range from 0=-1V; 65535=+1V.
 * @return status #DPP_SUCCESS if the value was successfully read, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber or threshold is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType getDynamicResetThreshold(const CharType* serialNumber, UInt16Type* threshold);

/**
 * Sets the duration of dynamic reset in nanoseconds. The range is 0ns - 819187.5ns. The given duration must be a multiple of 12.5ns otherwise #DPP_VICOLIB_OUT_OF_RANGE_ERROR will be returned along with the closest valid value.
 * @param[in] serialNumber the target device.
 * @param[in] duration the duration of dynamic reset in nanoseconds with a range between 0ns and 819187.5ns.
 * @return status #DPP_SUCCESS if the value was successfully set, #DPP_VICOLIB_OUT_OF_RANGE_ERROR if the duration is not in valid range, #DPP_REQUEST_CURRENTLY_NOT_POSSIBLE_ERROR if MCA data acquisition is active, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber or duration is null, #DPP_VICOLIB_OUT_OF_RANGE_ERROR if duration is not an integer multiple of 12.5ns, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType setDynamicResetDuration(const CharType* serialNumber, FloatType* duration);

/**
 * Reads the duration of dynamic reset in nanoseconds. The range is 0ns - 819187.5ns.
 * @param[in] serialNumber the target device.
 * @param[out] duration the duration of dynamic reset in nanoseconds with a range between 0ns and 819187.5ns.
 * @return status #DPP_SUCCESS if the value was successfully set, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber or duration is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType getDynamicResetDuration(const CharType* serialNumber, FloatType* duration);

/**
 * Sets the detector type for the reset detection, which is i.e. SDD or PIN.
 * This function is used KETEK-internal to set a proper reset detection for a given detector type.
 * @param[in] serialNumber the target device.
 * @param[in] resetDetection the detector type for the reset detection, which is i.e. SDD or PIN.
 * @return status #DPP_SUCCESS if the value was successfully set, #DPP_PARAMETER_READ_ONLY_ERROR if access is denied, #DPP_REQUEST_CURRENTLY_NOT_POSSIBLE_ERROR if MCA data acquisition is active, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber or resetDetection is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType setResetDetection(const CharType* serialNumber, ResetDetectionType resetDetection);

/**
 * Reads the detector type for the reset detection, which is SDD or PIN.
 * @param[in] serialNumber the target device.
 * @param[out] resetDetection the detector type for the reset detection, which is i.e. SDD or PIN.
 * @return status #DPP_SUCCESS if the value was successfully read, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber or resetDetection is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType getResetDetection(const CharType* serialNumber, ResetDetectionType* resetDetection);

/**
 * Loads the default parameter set from the user data memory of the target device.
 * @param[in] serialNumber the target device.
 * @return status #DPP_SUCCESS if successfully loaded, #DPP_REQUEST_CURRENTLY_NOT_POSSIBLE_ERROR if MCA data acquisition is active, #DPP_TIMEOUT_ERROR if a timeout appeared on the DPP, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType loadDefaultParameterSet(const CharType* serialNumber);

/**
 * Loads the saved parameter set from the user data memory of the target device.
 * @param[in] serialNumber the target device.
 * @return status #DPP_SUCCESS if successfully loaded, #DPP_REQUEST_CURRENTLY_NOT_POSSIBLE_ERROR if MCA data acquisition is active, #DPP_TIMEOUT_ERROR if a timeout appeared on the DPP, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType loadParameterSet(const CharType* serialNumber);

/**
 * Saves the currently used parameters of the targeted device into the default parameters slot of the user data memory.
 * This function is only used KETEK-internal to program proper default parameters to the device. The default parameter slot is not intended do be overwritten by user.
 Therefore, the status #DPP_OUT_OF_RANGE_ERROR will be returned if the device is not in maintenance mode.
 * @param[in] serialNumber the target device.
 * @return status #DPP_SUCCESS if successfully saved, #DPP_OUT_OF_RANGE_ERROR if access to this function is denied, #DPP_REQUEST_CURRENTLY_NOT_POSSIBLE_ERROR if MCA data acquisition is active, #DPP_TIMEOUT_ERROR if a timeout appeared on the DPP, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType saveDefaultParameterSet(const CharType* serialNumber);

/**
 * Saves the currently used parameters of the targeted device into the saved parameters slot of the user data memory.
 * @param[in] serialNumber the target device.
 * @return status #DPP_SUCCESS if successfully saved, #DPP_REQUEST_CURRENTLY_NOT_POSSIBLE_ERROR if MCA data acquisition is active, #DPP_TIMEOUT_ERROR if a timeout appeared on the DPP, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType saveParameterSet(const CharType* serialNumber);

/**
 * Reads the DPP firmware version into the given struct, consisting of major-, minor-, patch-, and build-version number.
 * @param[in] serialNumber the target device.
 * @param[out] version the DPP major-, minor-, patch-, and build-version number.
 * @return status #DPP_SUCCESS if the value was successfully read, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber or version is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType getFirmwareVersion(const CharType* serialNumber, FirmwareVersionType* version);

/**
 * Reads the device status information from the MCU, which are i.e. if the MCU has power, is ready, and is almostReady.
 * @param[in] serialNumber the target device.
 * @param[out] mcuStatus the status information about the MCU, which are i.e. if the MCU has power, is ready, and is almostReady.
 * @return status #DPP_SUCCESS if the value was successfully read, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber or mcuStatus is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType getMCUStatusInfo(const CharType* serialNumber, MCUStatusInfoType* mcuStatus);

/**
 * Reads the DPP board temperature. The returned value has to be divided by 16 in order to calculate the temperature in Kelvin. Example: A return value of 5388 equals a board temperature of 5388/16=336,75K or (336,75-273,15)°C=63,6°C.
 * @param[in] serialNumber the target device.
 * @param[out] temperature the board temperature (1 LSB equals 1/16K).
 * @return status #DPP_SUCCESS if successfully saved, #DPP_REQUEST_CURRENTLY_NOT_POSSIBLE_ERROR if temperature sensor in not ready yet (after a powercycle), #DPP_TIMEOUT_ERROR if a timeout appeared on the DPP, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber of temperature is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType getBoardTemperature(const CharType* serialNumber, UInt16Type* temperature);

/**
 * Enables the powerdown of DPP analog hardware. Power consumption is reduced in powerdown mode but MCA data acquisition is not possible.
 * @param[in] serialNumber the target device.
 * @return status #DPP_SUCCESS if successfully enabled, #DPP_REQUEST_CURRENTLY_NOT_POSSIBLE_ERROR if MCA data acquisition is active, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType enableAnalogHardwarePowerdown(const CharType* serialNumber);

/**
 * Disables the powerdown of DPP analog hardware. Power consumption is reduced in powerdown mode but MCA data acquisition is not possible.
 * @param[in] serialNumber the target device.
 * @return status #DPP_SUCCESS if successfully disabled, #DPP_REQUEST_CURRENTLY_NOT_POSSIBLE_ERROR if MCA data acquisition is active, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType disableAnalogHardwarePowerdown(const CharType* serialNumber);

/**
 * Reads whether the powerdown of DPP analog hardware is enabled or disabled. Power consumption is reduced in powerdown mode but MCA data acquisition is not possible.
 * @param[in] serialNumber the target device.
 * @param[out] enabled which is true if the DPP analog powerdown is enabled, false if disabled.
 * @return status #DPP_SUCCESS if the value was successfully read, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber or enabled is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType isAnalogHardwarePowerdownEnabled(const CharType* serialNumber, BooleanType* enabled);

/**
 * Sets the clocking speed of the DPP. 0 represents a clocking speed of 80MHz. Currently there is no other valid value than 0.
 * @param[in] serialNumber the target device.
 * @param[in] clockingSpeed the clocking speed of the DPP.
 * @return status #DPP_SUCCESS if the value was successfully set, #DPP_VICOLIB_OUT_OF_RANGE_ERROR if the clockingSpeed is not in valid range, #DPP_REQUEST_CURRENTLY_NOT_POSSIBLE_ERROR if MCA data acquisition is active, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber or clockingSpeed is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType setClockingSpeed(const CharType* serialNumber, ClockingSpeedType clockingSpeed);

/**
 * Gets the clocking speed of the DPP. 0 represents a clocking speed of 80Mhz.
 * @param[in] serialNumber the target device.
 * @param[out] clockingSpeed the clocking speed of the DPP.
 * @return status #DPP_SUCCESS if the value was successfully read, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber or clockingSpeed is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType getClockingSpeed(const CharType* serialNumber, ClockingSpeedType* clockingSpeed);

/**
 * Reads all 256 DPP parameters simultaneously into an array. The size is 4 bytes per parameter multiplied with the 256 parameters which results in 1024 bytes. This function is intended to be used for debug purposes.
 * @param[in] serialNumber the target device.
 * @param[in] allParametersSize the size of all parameters to read is 4 bytes multiplied with the 256 parameters which results in 1024 bytes.
 * @param[out] allParameters the values of parameters 0 to 255.
 * @return status #DPP_SUCCESS if the values were successfully read, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber, allParametersSize or allParameters is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 * @see #ALL_PARAMETERS_SIZE
 */
VICOLIB_API DPPStatusType getAllParameters(const CharType* serialNumber, const UInt16Type allParametersSize, UInt8Type* allParameters);

/**
 * Sets the trigger source for #getEventScope() and #calculateEventRate().
 * @param[in] serialNumber the target device.
 * @param[in] triggerSource the trigger source for #getEventScope() and #calculateEventRate().
 * @return status #DPP_SUCCESS if the value was successfully set, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber or triggerSource is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 * @see #TriggerSourceType
 */
VICOLIB_API DPPStatusType setEventTriggerSource(const CharType* serialNumber, TriggerSourceType triggerSource);

/**
 * Reads the trigger source for #getEventScope() and #calculateEventRate().
 * @param[in] serialNumber the target device.
 * @param[out] triggerSource the trigger source for #getEventScope() and #calculateEventRate().
 * @return status #DPP_SUCCESS if the value was successfully read, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber or triggerSource is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 * @see #TriggerSourceType
 */
VICOLIB_API DPPStatusType getEventTriggerSource(const CharType* serialNumber, TriggerSourceType* triggerSource);

/**
 * Sets the trigger value for #getEventScope() and #calculateEventRate(). The range is 0 - 65535. The trigger value does not have an influence for every trigger source set by #setEventTriggerSource (see: #TriggerSourceType)
 * @param[in] serialNumber the target device.
 * @param[in] triggerValue the trigger value for #getEventScope() and #calculateEventRate() with a range between 0 and 65535.
 * @return status #DPP_SUCCESS if the value was successfully set, #DPP_VICOLIB_OUT_OF_RANGE_ERROR if the triggerValue is not in valid range, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber or triggerValue is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType setEventTriggerValue(const CharType* serialNumber, UInt16Type triggerValue);

/**
 * Reads the trigger value for #getEventScope() and #calculateEventRate(). The range is 0 - 65535. The trigger value does not have an influence for every trigger source set by #setEventTriggerSource (see: #TriggerSourceType).
 * @param[in] serialNumber the target device.
 * @param[out] triggerValue the trigger value for #getEventScope() and #calculateEventRate() with a range between 0 and 65535.
 * @return status #DPP_SUCCESS if the value was successfully read, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber or triggerValue is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType getEventTriggerValue(const CharType* serialNumber, UInt16Type* triggerValue);

/**
 * Sets the sampling interval for #getEventScope(). The range is 1 - 65535 which represents the factor of down-sampling regarding 80MHz. Example: Setting samplingInterval to 2 results in signal traces with a sampling frequency of 80MHz/2=40MHz when calling #getEventScope(). 
 * @param[in] serialNumber the target device.
 * @param[in] samplingInterval the sampling interval for #getEventScope() with a range between 1 and 65535, which represents the factor of down-sampling regarding 80MHz.
 * @return status #DPP_SUCCESS if the value was successfully set, #DPP_VICOLIB_OUT_OF_RANGE_ERROR if the samplingInterval is not in valid range, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber or samplingInterval is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType setEventScopeSamplingInterval(const CharType* serialNumber, UInt16Type* samplingInterval);

/**
 * Reads the sampling interval for #getEventScope(). The range is 1 - 65535 which represents the factor of down-sampling regarding 80MHz. Example: Setting samplingInterval to 2 results in signal traces with a sampling frequency of 80MHz/2=40MHz when calling #getEventScope(). 
 * @param[in] serialNumber the target device.
 * @param[out] samplingInterval the sampling interval for #getEventScope() with a range between 1 and 65535, which represents the factor of down-sampling regarding 80MHz.
 * @return status #DPP_SUCCESS if the value was successfully read, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber or samplingInterval is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType getEventScopeSamplingInterval(const CharType* serialNumber, UInt16Type* samplingInterval);

/**
 * Sets the trigger timeout for #getEventScope() ranging from 1s to 16s (see: #TriggerTimeoutType). triggerTimeout defines the maximum time the DPP waits for a trigger to appear after calling #getEventScope() before #DPP_TIMEOUT_ERROR is returned.
 * @param[in] serialNumber the target device.
 * @param[in] triggerTimeout the trigger timeout for #getEventScope() ranging from 1s to 16s.
 * @return status #DPP_SUCCESS if the value was successfully set, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber or triggerTimeout is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType setEventScopeTriggerTimeout(const CharType* serialNumber, TriggerTimeoutType triggerTimeout);

/**
 * Reads the trigger timeout for #getEventScope() ranging from 1s to 16s (see: #TriggerTimeoutType). triggerTimeout defines the maximum time the DPP waits for a trigger to appear after calling #getEventScope() before #DPP_TIMEOUT_ERROR is returned.
 * @param[in] serialNumber the target device.
 * @param[out] triggerTimeout the trigger timeout for #getEventScope() ranging from 1s to 16s.
 * @return status #DPP_SUCCESS if the value was successfully read, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber or triggerTimeout is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType getEventScopeTriggerTimeout(const CharType* serialNumber, TriggerTimeoutType* triggerTimeout);

/**
 * Triggers and reads a signal trace from the DPP. Use #setEventTriggerSource(), #setEventTriggerValue(), #setEventScopeSamplingInterval() and #setEventScopeTriggerTimeout() to configure the trigger and the signal readout before calling this function. The argument eventScopeType defines which internal signal is read out (i.e., ADC-Data, fastfilter, mediumfilter, slowfilter), see #EventScopeType, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 * The returned eventScope has a length of 8192 sampling points which cannot be adjusted. In case no triggers occurred within the triggerTimeout time set by #setEventScopeTriggerTimeout the status #DPP_TIMEOUT_ERROR will be returned together with an array of zeros in eventScope.
 * @param[in] serialNumber the target device.
 * @param[in] eventScopeType the type of signal to read (i.e., ADC-Data, fastfilter, mediumfilter, slowfilter), see #EventScopeType.
 * @param[in] eventScopeSize the size of signal array which is fixed to 8192 and cannot be adjusted.
 * @param[out] eventScope the signal trace with a fixed size of 8192.
 * @return status #DPP_SUCCESS if the signal trace as successfully triggered and read out, #DPP_REQUEST_CURRENTLY_NOT_POSSIBLE_ERROR if MCA data acquisition is active, #DPP_TIMEOUT_ERROR if no triggers occurred within the triggerTimeout time set by #setEventScopeTriggerTimeout() (try to enlarge triggerTimeout or adjust trigger conditions), #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber, eventScopeType, eventScopeSize or eventScope is null or if eventScopeSize is out of the valid range, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 * @see #EVENT_SCOPE_SIZE, #EventScopeType
 */
VICOLIB_API DPPStatusType getEventScope(const CharType* serialNumber, const EventScopeType eventScopeType, const UInt16Type eventScopeSize, UInt32Type* eventScope);

/**
 * Starts the calculation of the trigger event rate which can be retrieved by #getEventRate(). Within the specified triggerTime ranging from 1s to 16s (see #TriggerDurationType) the amount of triggers for the current settings of #setEventTriggerSource() and #setEventTriggerValue() and counted. This counter value can be read out afterwards by #getEventRate().
 * @param[in] serialNumber the target device.
 * @param[in] triggerTime the specific trigger time in which the events are counted.
 * @return status #DPP_SUCCESS if the triggers were counted successfully, #DPP_REQUEST_CURRENTLY_NOT_POSSIBLE_ERROR if MCA data acquisition is active, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber or triggerTime is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 * @see #getEventRate()
 */
VICOLIB_API DPPStatusType calculateEventRate(const CharType* serialNumber, const TriggerDurationType triggerTime);

/**
 * Reads out the amount of triggered events after calculation with #calculateEventRate(). The readout with this function does not refresh the counter value.
 * @param[in] serialNumber the target device.
 * @param[out] eventRate the amount of triggered events within the trigger time.
 * @return status #DPP_SUCCESS if the value was successfully read, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber or eventRate is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 * @see #calculateEventRate()
 */
VICOLIB_API DPPStatusType getEventRate(const CharType* serialNumber, UInt32Type* eventRate);

/**
 * Deletes the firmware in the update section of the DPP configuration memory. When restarting the device after calling this function the firmware in the golden image section of the configuration memory will be loaded.
 * This function must be unlocked using #setServiceCode(), otherwise the status #DPP_PARAMETER_READ_ONLY_ERROR will be returned. 
 * The time to get a response is typically between 30 and 75 seconds. This function must be called before writing a new firmware version with #writeFirmwareSection().\n\n
 * It is not recommended to use #deleteFirmware(), #writeFirmwareSection() and #readFirmwareSection() in custom scripts in order to modify the DPP configuration memory. We recommend to use KETEKs VICOUpdate tool instead which has a graphical and a command line interface and ensures safe modifications of the configuration memory.
 * @param[in] serialNumber the target device.
 * @return status #DPP_SUCCESS if the firmware was successfully deleted, #DPP_PARAMETER_READ_ONLY_ERROR if access was denied due to wrong service code, #DPP_TIMEOUT_ERROR if a timeout appeared on the DPP, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 * @see #writeFirmwareSection(), #readFirmwareSection()
 */
VICOLIB_API DPPStatusType deleteFirmware(const CharType* serialNumber);

/**
 * Writes a section of firmware data in the given segment number of the DPP configuration memory. This datagram can only be used if #deleteFirmware() was executed before, otherwise the status #DPP_PARAMETER_READ_ONLY_ERROR will be returned.\n\n
 * It is not recommended to use #deleteFirmware(), #writeFirmwareSection() and #readFirmwareSection() in custom scripts in order to modify the DPP configuration memory. We recommend to use KETEKs VICOUpdate tool instead which has a graphical and a command line interface and ensures safe modifications of the configuration memory.
 * @param[in] serialNumber the target device.
 * @param[in] segmentNumber the segment number in which the firmware section should be written. Only values between 0 and 4095 are valid.
 * @param[in] firmwareSectionSize the size of the firmware section to be written, which is always 1024.
 * @param[in] firmwareSection the firmware data to be written in the given segment number of the memory.
 * @return status #DPP_SUCCESS if the firmware section was successfully written, #DPP_PARAMETER_READ_ONLY_ERROR if access was denied due not executing #deleteFirmware() before, #DPP_TIMEOUT_ERROR if a timeout appeared on the DPP, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber, segmentNumber, firmwareSectionSize or firmwareSection is null of if segmentNumber or firmwareSectionSize is not valid value, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 * @see #deleteFirmware(), #readFirmwareSection()
 */
VICOLIB_API DPPStatusType writeFirmwareSection(const CharType* serialNumber, UInt16Type* segmentNumber, UInt16Type firmwareSectionSize, UInt8Type* firmwareSection);

/**
 * Reads a section of firmware data from the given segment number of the DPP configuration memory. The returned firmware section consists of 4 header bytes (parameter id (1 byte), status (1 byte), segmentNumber (2 bytes)), and 1024 firmware data bytes.
 * If an error appeared, the returned 1024 data bytes all contain 0x00.\n\n
 * It is not recommended to use #deleteFirmware(), #writeFirmwareSection() and #readFirmwareSection() in custom scripts in order to modify the DPP configuration memory. We recommend to use KETEKs VICOUpdate tool instead which has a graphical and a command line interface and ensures safe modifications of the configuration memory.
 * @param[in] serialNumber the target device.
 * @param[in] segmentNumber the segment number in which the firmware section should be written. Only values between 0 and 4095 are valid.
 * @param[in] firmwareSectionSize the size of the firmware section to be read, which is always 1024.
 * @param[out] firmwareSection the firmware section data to be read from the given segment number of the memory.
 * @return status #DPP_SUCCESS if the firmware section was successfully read, #DPP_TIMEOUT_ERROR if a timeout appeared on the DPP, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber, segmentNumber, firmwareSectionSize or firmwareSection is null of if segmentNumber or firmwareSectionSize is not valid value, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 * @see #deleteFirmware(), #readFirmwareSection()
 */
VICOLIB_API DPPStatusType readFirmwareSection(const CharType* serialNumber, UInt16Type* segmentNumber, UInt16Type firmwareSectionSize, UInt8Type* firmwareSection);

/**
 * Sets a service code for maintenance access. This function is used to access KETEK-internal functions.
 * @param[in] serialNumber the target device.
 * @param[in] serviceCode the service code for maintenance access.
 * @return status #DPP_SUCCESS if the value was successfully set, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber or serviceCode is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType setServiceCode(const CharType* serialNumber, UInt32Type serviceCode);

/**
 * Reads the current service code for maintenance access. This function is used to access KETEK-internal functions.
 * @param[in] serialNumber the target device.
 * @param[out] serviceCode the currently set service code for maintenance access.
 * @return status #DPP_SUCCESS if the value was successfully read, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber or serviceCode is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType getServiceCode(const CharType* serialNumber, UInt32Type* serviceCode);

/**
 * Enables the powerdown of the ethernet communication. Power consumption is reduced by enabling ethernet powerdown but TCP or UDP communication is not possible.
 * @param[in] serialNumber the target device.
 * @return status #DPP_SUCCESS if successfully enabled, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType enableEthernetPowerdown(const CharType* serialNumber);

/**
 * Disables the powerdown of the ethernet communication. Power consumption is reduced by enabling ethernet powerdown but TCP or UDP communication is not possible.
 * @param[in] serialNumber the target device.
 * @return status #DPP_SUCCESS if successfully disabled, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType disableEthernetPowerdown(const CharType* serialNumber);

/**
 * Reads whether the powerdown of the ethernet communication is enabled or disabled. Power consumption is reduced by enabling ethernet powerdown but TCP or UDP communication is not possible.
 * @param[in] serialNumber the target device.
 * @param[out] enabled which is true if the powerdown of the ethernet chip is enabled, false if disabled.
 * @return status #DPP_SUCCESS if value successfully read, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber or enabled is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType isEthernetPowerdownEnabled(const CharType* serialNumber, BooleanType* enabled);

/**
 * Sets the ethernet protocol which is TCP or UDP (see #EthernetProtocolType). In order to apply the value set with this function #applyEthernetConfiguration() has be called.
 * @param[in] serialNumber the target device.
 * @param[in] ethernetProtocol the ethernet protocol which is TCP or UDP.
 * @return status #DPP_SUCCESS if value successfully set, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber or ethernetProtocol is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType setEthernetProtocol(const CharType* serialNumber, EthernetProtocolType ethernetProtocol);

/**
 * Sets the ethernet protocol which is TCP or UDP (see #EthernetProtocolType).
 * @param[in] serialNumber the target device.
 * @param[out] ethernetProtocol the ethernet protocol which is TCP or UDP.
 * @return status #DPP_SUCCESS if value successfully read, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber or ethernetProtocol is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType getEthernetProtocol(const CharType* serialNumber, EthernetProtocolType* ethernetProtocol);

/**
 * Sets the ethernet speed mode which is Auto negotiation, 10MBit/s Half Duplex, 10MBit/s Full Duplex, 100MBit/s Half Duplex or 100Mbit/s Full Duplex (see #EthernetSpeedType). Power consumption is reduced by choosing a slower ethernet speed. In order to apply the value set with this function #applyEthernetConfiguration() has be called.
 * @param[in] serialNumber the target device.
 * @param[in] ethernetSpeed the ethernet speed mode.
 * @return status #DPP_SUCCESS if value successfully set, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber or ethernetSpeed is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType setEthernetSpeed(const CharType* serialNumber, EthernetSpeedType ethernetSpeed);

/**
 * Reads the ethernet speed mode which is Auto negotiation, 10MBit/s Half Duplex, 10MBit/s Full Duplex, 100MBit/s Half Duplex or 100Mbit/s Full Duplex (see #EthernetSpeedType). Power consumption is reduced by choosing a slower ethernet speed.
 * @param[in] serialNumber the target device.
 * @param[out] ethernetSpeed the ethernet speed mode.
 * @return status #DPP_SUCCESS if value successfully read, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber or ethernetSpeed is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType getEthernetSpeed(const CharType* serialNumber, EthernetSpeedType* ethernetSpeed);

/**
 * Sets the ethernet IPv4 address in the following form: "XXX.XXX.XXX.XXX", for example "192.168.0.2".
 * @param[in] serialNumber the target device.
 * @param[in] ipAddress the ethernet IPv4 address.
 * @return status #DPP_SUCCESS if value successfully set, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber or ipAddress is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType setIPAddress(const CharType* serialNumber, const CharType* ipAddress);

/**
 * Reads the ethernet IPv4 address in the following form: "XXX.XXX.XXX.XXX", for example "192.168.0.2".
 * @param[in] serialNumber the target device.
 * @param[in] ipAddressSize the size of the ethernet Ipv4 address array (is typically 15).
 * @param[out] ipAddress the ethernet IPv4 address.
 * @return status #DPP_SUCCESS if value successfully read, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber or ipAddress is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType getIPAddress(const CharType* serialNumber, const UInt8Type ipAddressSize, CharType* ipAddress);

/**
 * Sets the ethernet IPv4 subnet mask in the following form: "XXX.XXX.XXX.XXX", for example "255.255.255.0". In order to apply the value set with this function #applyEthernetConfiguration() has be called.
 * @param[in] serialNumber the target device.
 * @param[in] subnetMask the ethernet IPv4 subnetMask.
 * @return status #DPP_SUCCESS if value successfully set, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber or subnetMask is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType setSubnetMask(const CharType* serialNumber, const CharType* subnetMask);

/**
 * Reads the ethernet IPv4 subnet mask in the following form: "XXX.XXX.XXX.XXX", for example "255.255.255.0".
 * @param[in] serialNumber the target device.
 * @param[in] subnetMaskSize the size of the subnet mask IPv4 address array (is typically 15).
 * @param[out] subnetMask the ethernet IPv4 subnetMask.
 * @return status #DPP_SUCCESS if value successfully read, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber or subnetMask is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType getSubnetMask(const CharType* serialNumber, const UInt8Type subnetMaskSize, CharType* subnetMask);

/**
 * Sets the ethernet IPv4 gateway IP address in the following form: "XXX.XXX.XXX.XXX", for example "192.168.0.0". In order to apply the value set with this function #applyEthernetConfiguration() has be called.
 * @param[in] serialNumber the target device.
 * @param[in] gatewayIpAddress the ethernet IPv4 gateway IP address.
 * @return status #DPP_SUCCESS if value successfully set, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber or gatewayIpAddress is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType setGatewayIPAddress(const CharType* serialNumber, const CharType* gatewayIpAddress);

/**
 * Reads the ethernet IPv4 gateway IP address in the following form: "XXX.XXX.XXX.XXX", for example "192.168.0.0".
 * @param[in] serialNumber the target device.
 * @param[in] gatewayIpAddressSize the size of the gateway IPv4 address array (is typically 15).
 * @param[out] gatewayIpAddress the ethernet IPv4 gateway IP address.
 * @return status #DPP_SUCCESS if value successfully read, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber or gatewayIpAddress is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType getGatewayIPAddress(const CharType* serialNumber, const UInt8Type gatewayIpAddressSize, CharType* gatewayIpAddress);

/**
 * Reads the ethernet port.
 * @param[in] serialNumber the target device.
 * @param[out] ethernetPort the ethernet port.
 * @return status #DPP_SUCCESS if value successfully read, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber or ethernetPort is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType getEthernetPort(const CharType* serialNumber, UInt16Type* ethernetPort);

/**
 * Sets the ethernet mac address in the form "XX:XX:XX:XX:XX:XX" or "XX-XX-XX-XX-XX-XX", for example "58-94-A2-00-00-23". In order to apply the value set with this function #applyEthernetConfiguration() has be called.
 * This function is only used KETEK-internal to program a unique mac address into the device.
 * @param[in] serialNumber the target device.
 * @param[in] macAddress the ethernet mac address.
 * @return status #DPP_SUCCESS if value successfully set, #DPP_PARAMETER_READ_ONLY_ERROR if access is denied, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber or macAddress is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType setMACAddress(const CharType* serialNumber, const CharType* macAddress);

/**
 * Reads the ethernet mac address in the following form: "XX-XX-XX-XX-XX-XX", for example "58-94-A2-00-00-23".
 * @param[in] serialNumber the target device.
 * @param[in] macAddressSize the size of the mac address array (is typically 17).
 * @param[out] macAddress the ethernet mac address.
 * @return status #DPP_SUCCESS if value successfully read, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber or macAddress is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType getMACAddress(const CharType* serialNumber, const UInt8Type macAddressSize, CharType* macAddress);

/**
 * Applies the current ethernet configuration regarding ethernet protocol (#setEthernetProtocol()), ethernet speed (#setEthernetSpeed()), ethernet IP address (#setIPAddress()),
 * ethernet subnet mask (#setSubnetMask()), ethernet gateway IP address (#setGatewayIPAddress()), and ethernet MAC address (#setMACAddress()).
 * After #applyEthernetConfiguration() is used any ethernet connection with the device will be gone. Hence, afterwards a scan using #scanTcpDevices() or #scanUdpDevices() is needed to establish a new connection.
 * @param[in] serialNumber the target device.
 * @return status #DPP_SUCCESS if ethernet configuration was successfully applied, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 * @see #setEthernetProtocol(), #setEthernetSpeed(), #setIPAddress(), #setSubnetMask(), #setGatewayIPAddress(), #setMACAddress(), #scanTcpDevices(), #scanUdpDevices().
 */
VICOLIB_API DPPStatusType applyEthernetConfiguration(const CharType* serialNumber);

/**
 * Enables the powerdown of the USB communication. Power consumption is reduced by enabling USB powerdown but communication via USB is not possible.
 * @param[in] serialNumber the target device.
 * @return status #DPP_SUCCESS if successfully enabled, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType enableUSBPowerdown(const CharType* serialNumber);

/**
 * Disables the powerdown of the USB communication. Power consumption is reduced by enabling USB powerdown but communication via USB is not possible.
 * @param[in] serialNumber the target device.
 * @return status #DPP_SUCCESS if successfully disabled, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType disableUSBPowerdown(const CharType* serialNumber);

/**
 * Reads whether the powerdown of the USB communication is enabled or disabled. Power consumption is reduced by enabling USB powerdown but communication via USB is not possible.
 * @param[in] serialNumber the target device.
 * @param[out] enabled which is true if the powerdown of the USB chip is enabled, or false if disabled.
 * @return status #DPP_SUCCESS if value successfully read, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber or enabled is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType isUSBPowerdownEnabled(const CharType* serialNumber, BooleanType* enabled);

/**
 * Enables the powerdown of the SPI communication.
 * @param[in] serialNumber the target device.
 * @return status #DPP_SUCCESS if successfully enabled, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType enableSPIPowerdown(const CharType* serialNumber);

/**
 * Disables the powerdown of the SPI communication.
 * @param[in] serialNumber the target device.
 * @return status #DPP_SUCCESS if successfully disabled, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType disableSPIPowerdown(const CharType* serialNumber);

/**
 * Reads whether the powerdown of the SPI communication is enabled or disabled.
 * @param[in] serialNumber the target device.
 * @param[out] enabled which is true if the powerdown of the SPI communication is enabled, or false if disabled.
 * @return status #DPP_SUCCESS if value successfully read, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber or enabled is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType isSPIPowerdownEnabled(const CharType* serialNumber, BooleanType* enabled);

/**
 * Reads the key revision version number for firmware encryption.
 * @param[in] serialNumber the target device.
 * @param[out] keyRevision the key revision version number.
 * @return status #DPP_SUCCESS if the value was successfully read, #DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #VICO_VICODAEMON_IS_STOPPED if VICODaemon is not running, #DPP_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #DPP_INVALID_ARGUMENT_ERROR if parameter serialNumber or keyRevision is null, #DPP_COMMAND_NOT_SUPPORTED_ERROR if command is not applicable for targeted device (e.g., DPP datagram sent to VICO-AV).
 */
VICOLIB_API DPPStatusType getKeyRevision(const CharType* serialNumber, UInt16Type* keyRevision);

/**
 * Returns an identifier of the currently active software package. Can be used to identify whether bootloader- or application-mode is active.
 * This request can be sent in bootloader-, application-, and EEA-mode.
 * @param[in] serialNumber the target device.
 * @param[out] swPkg contains the identifier for the currently active software package.
 * @return status #MCU_SUCCESS if the value was successfully read, #MCU_COMMAND_NOT_SUPPORTED if command index is not applicable for targeted device or current mode (#SoftwarePackage or #ModeType), #MCU_VERSION_NOT_SUPPORTED if command version is not applicable for targeted device, #MCU_ERROR if the command couldn't be processed by the device, #MCU_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #MCU_VICODAEMON_IS_STOPPED if VICODaemon is not running, #MCU_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #MCU_INVALID_ARGUMENT_ERROR if an input parameter is null, #DPP_UART_TIMEOUT_ERROR if no response was received from the device, #DPP_NO_ACCESS_TO_INTERNAL_MEMORY_ERROR if an internal data handling error occurs.
 */
VICOLIB_API MCUStatusType swPkgGetActive(const CharType* serialNumber, SoftwarePackage *swPkg);

/**
 * Returns contents of the flash.
 * This request can only be sent in bootloader-mode.
 * @param[in] serialNumber the target device.
 * @param[in] addStart the start address of the flash to read. The range is byte 0 - 2047.
 * @param[in] len the length of the data to read, which is maximum 249 bytes.
 * @param[out] data contains the read flash data.
 * @return status #MCU_SUCCESS if the data was successfully read, #MCU_COMMAND_NOT_SUPPORTED if command index is not applicable for targeted device or current mode (#SoftwarePackage or #ModeType), #MCU_VERSION_NOT_SUPPORTED if command version is not applicable for targeted device, #MCU_ERROR if the command couldn't be processed by the device, #MCU_BL_ADDRESS_OUT_OF_VALID_RANGE if parameter addStart is outside the valid range, #MCU_BL_LEN_OUT_OF_VALID_RANGE if parameter len is outside the valid range, #MCU_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #MCU_VICODAEMON_IS_STOPPED if VICODaemon is not running, #MCU_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #MCU_INVALID_ARGUMENT_ERROR if an input parameter is null, #DPP_UART_TIMEOUT_ERROR if no response was received from the device, #DPP_NO_ACCESS_TO_INTERNAL_MEMORY_ERROR if an internal data handling error occurs.
 */
VICOLIB_API MCUStatusType flashRead(const CharType* serialNumber, UInt32Type addStart, UInt8Type len, UInt8Type* data);

/**
 * Starts a write session, which is only possible if bootloader is active in "default" session.
 * This request can only be sent in bootloader-mode.
 * @param[in] serialNumber the target device.
 * @return status #MCU_SUCCESS if the write session was successfully started, #MCU_COMMAND_NOT_SUPPORTED if command index is not applicable for targeted device or current mode (#SoftwarePackage or #ModeType), #MCU_VERSION_NOT_SUPPORTED if command version is not applicable for targeted device, #MCU_ERROR if the command couldn't be processed by the device, #MCU_BL_FLASH_SESSION_ACTIVE if already in "flash" session, #MCU_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #MCU_VICODAEMON_IS_STOPPED if VICODaemon is not running, #MCU_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #MCU_INVALID_ARGUMENT_ERROR if an input parameter is null, #DPP_UART_TIMEOUT_ERROR if no response was received from the device, #DPP_NO_ACCESS_TO_INTERNAL_MEMORY_ERROR if an internal data handling error occurs.
 */
VICOLIB_API MCUStatusType flashWriteSessionStart(const CharType* serialNumber);

/**
 * Stops a write session, which is only possible if bootloader is in "flash" session.
 * This request can only be sent in bootloader-mode.
 * @param[in] serialNumber the target device.
 * @return status #MCU_SUCCESS if the write session was successfully stopped, #MCU_COMMAND_NOT_SUPPORTED if command index is not applicable for targeted device or current mode (#SoftwarePackage or #ModeType), #MCU_VERSION_NOT_SUPPORTED if command version is not applicable for targeted device, #MCU_ERROR if the command couldn't be processed by the device, #MCU_BL_NO_FLASH_SESSION_ACTIVE if no "flash" session active, #MCU_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #MCU_VICODAEMON_IS_STOPPED if VICODaemon is not running, #MCU_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #MCU_INVALID_ARGUMENT_ERROR if an input parameter is null, #DPP_UART_TIMEOUT_ERROR if no response was received from the device, #DPP_NO_ACCESS_TO_INTERNAL_MEMORY_ERROR if an internal data handling error occurs.
 */
VICOLIB_API MCUStatusType flashWriteSessionExit(const CharType* serialNumber);

/**
 * Resets the session state to initial values, which is only possible if the bootloader is in "flash" session.
 * This request can only be sent in bootloader-mode.
 * @param[in] serialNumber the target device.
 * @return status #MCU_SUCCESS if the session state was successfully reset, #MCU_COMMAND_NOT_SUPPORTED if command index is not applicable for targeted device or current mode (#SoftwarePackage or #ModeType), #MCU_VERSION_NOT_SUPPORTED if command version is not applicable for targeted device, #MCU_ERROR if the command couldn't be processed by the device, #MCU_BL_NO_FLASH_SESSION_ACTIVE if no "flash" session active, #MCU_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #MCU_VICODAEMON_IS_STOPPED if VICODaemon is not running, #MCU_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #MCU_INVALID_ARGUMENT_ERROR if an input parameter is null, #DPP_UART_TIMEOUT_ERROR if no response was received from the device, #DPP_NO_ACCESS_TO_INTERNAL_MEMORY_ERROR if an internal data handling error occurs.
 */
VICOLIB_API MCUStatusType flashWriteSessionReset(const CharType* serialNumber);

/**
 * Sends a data package to be flashed to the bootloader, which is only possible in bootloaders "flash" session.
 * This request can only be sent in bootloader-mode.
 * @param[in] serialNumber the target device.
 * @param[in] addStart the start address of the flash data to write.
 * @param[in] data the data package to write which must always have a size of 128 bytes.
 * @return status #MCU_SUCCESS if data was successfully written, #MCU_COMMAND_NOT_SUPPORTED if command index is not applicable for targeted device or current mode (#SoftwarePackage or #ModeType), #MCU_VERSION_NOT_SUPPORTED if command version is not applicable for targeted device, #MCU_ERROR if the command couldn't be processed by the device, #MCU_BL_NO_FLASH_SESSION_ACTIVE if no "flash" session active, #MCU_BL_ADDRESS_OUT_OF_VALID_RANGE if parameter addStart is outside the valid range, #MCU_BL_LEN_OUT_OF_VALID_RANGE if parameter data has an invalid length, #MCU_BL_DATA_NOT_IN_SEQUENCE_WITHIN_SESSION if the data block is not in sequence within the session, #MCU_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #MCU_VICODAEMON_IS_STOPPED if VICODaemon is not running, #MCU_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #MCU_INVALID_ARGUMENT_ERROR if an input parameter is null, #DPP_UART_TIMEOUT_ERROR if no response was received from the device, #DPP_NO_ACCESS_TO_INTERNAL_MEMORY_ERROR if an internal data handling error occurs.
 */
VICOLIB_API MCUStatusType flashWriteSessionData(const CharType* serialNumber, UInt32Type addStart, UInt8Type data[128]);

/**
 * Gets the session information from the MCU bootloader.
 * This request can only be sent in bootloader-mode.
 * @param[in] serialNumber the target device.
 * @param[out] blSession the session to read.
 * @return status #MCU_SUCCESS if the value was successfully read, #MCU_COMMAND_NOT_SUPPORTED if command index is not applicable for targeted device or current mode (#SoftwarePackage or #ModeType), #MCU_VERSION_NOT_SUPPORTED if command version is not applicable for targeted device, #MCU_ERROR if the command couldn't be processed by the device, #MCU_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #MCU_VICODAEMON_IS_STOPPED if VICODaemon is not running, #MCU_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #MCU_INVALID_ARGUMENT_ERROR if an input parameter is null, #DPP_UART_TIMEOUT_ERROR if no response was received from the device, #DPP_NO_ACCESS_TO_INTERNAL_MEMORY_ERROR if an internal data handling error occurs.
 */
VICOLIB_API MCUStatusType blGetSession(const CharType* serialNumber, BootloaderSessionType* blSession);

/**
 * Returns the reason why the bootloader was activated, which can be because of #RescuePinActive, #FlashRequest or #AppCrcInvalid.
 * This request can only be sent in bootloader-mode.
 * @param[in] serialNumber the target device.
 * @param[out] blReason the reason to read.
 * @return status #MCU_SUCCESS if the value was successfully read, #MCU_COMMAND_NOT_SUPPORTED if command index is not applicable for targeted device or current mode (#SoftwarePackage or #ModeType), #MCU_VERSION_NOT_SUPPORTED if command version is not applicable for targeted device, #MCU_ERROR if the command couldn't be processed by the device, #MCU_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #MCU_VICODAEMON_IS_STOPPED if VICODaemon is not running, #MCU_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #MCU_INVALID_ARGUMENT_ERROR if an input parameter is null, #DPP_UART_TIMEOUT_ERROR if no response was received from the device, #DPP_NO_ACCESS_TO_INTERNAL_MEMORY_ERROR if an internal data handling error occurs.
 */
VICOLIB_API MCUStatusType blGetReason(const CharType* serialNumber, BootloaderReasonType* blReason);

/**
 * Request bootloader to start the application, which is only possible if bootloader is in "default" state.
 * This request can only be sent in bootloader-mode.
 * @param[in] serialNumber the target device.
 * @return status #MCU_SUCCESS if successfully started, #MCU_COMMAND_NOT_SUPPORTED if command index is not applicable for targeted device or current mode (#SoftwarePackage or #ModeType), #MCU_VERSION_NOT_SUPPORTED if command version is not applicable for targeted device, #MCU_ERROR if the command couldn't be processed by the device, #MCU_BL_FLASH_SESSION_ACTIVE if start not possible because bootloader is in "flash" session, #MCU_BL_APPLICATION_CHECKSUM_INVALID if the application checksum is invalid, #MCU_BL_ALREADY_IN_APPLICATION if already in application, #MCU_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #MCU_VICODAEMON_IS_STOPPED if VICODaemon is not running, #MCU_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #MCU_INVALID_ARGUMENT_ERROR if an input parameter is null, #DPP_UART_TIMEOUT_ERROR if no response was received from the device, #DPP_NO_ACCESS_TO_INTERNAL_MEMORY_ERROR if an internal data handling error occurs.
 */
VICOLIB_API MCUStatusType swPkgStartApplication(const CharType* serialNumber);

/**
 * Requests the application software to start the bootloader.
 * This request can only be sent in application- and EEA-mode.
 * @param[in] serialNumber the target device.
 * @return status #MCU_SUCCESS if successfully started, #MCU_COMMAND_NOT_SUPPORTED if command index is not applicable for targeted device or current mode (#SoftwarePackage or #ModeType), #MCU_VERSION_NOT_SUPPORTED if command version is not applicable for targeted device, #MCU_ERROR if the command couldn't be processed by the device, #MCU_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #MCU_VICODAEMON_IS_STOPPED if VICODaemon is not running, #MCU_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #MCU_INVALID_ARGUMENT_ERROR if an input parameter is null, #DPP_UART_TIMEOUT_ERROR if no response was received from the device, #DPP_NO_ACCESS_TO_INTERNAL_MEMORY_ERROR if an internal data handling error occurs.
 */
VICOLIB_API MCUStatusType swPkgStartBootloader(const CharType* serialNumber);

/**
 * Returns live system status information from VICO.
 * This request can only be sent in application-mode.
 * @param[in] serialNumber the target device.
 * @param[out] liveInfo the live information to be read.
 * @return status #MCU_SUCCESS if the values were successfully read, #MCU_COMMAND_NOT_SUPPORTED if command index is not applicable for targeted device or current mode (#SoftwarePackage or #ModeType), #MCU_VERSION_NOT_SUPPORTED if command version is not applicable for targeted device, #MCU_ERROR if the command couldn't be processed by the device, #MCU_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #MCU_VICODAEMON_IS_STOPPED if VICODaemon is not running, #MCU_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #MCU_INVALID_ARGUMENT_ERROR if an input parameter is null, #DPP_UART_TIMEOUT_ERROR if no response was received from the device, #DPP_NO_ACCESS_TO_INTERNAL_MEMORY_ERROR if an internal data handling error occurs.
 */
VICOLIB_API MCUStatusType liveInfo1VICO(const CharType* serialNumber, LiveInfo1VICOType* liveInfo);

/**
 * Returns extended live system status information from VICO.
 * This request can only be sent in application-mode.
 * @param[in] serialNumber the target device.
 * @param[out] liveInfo the live information to be read.
 * @return status #MCU_SUCCESS if the values were successfully read, #MCU_COMMAND_NOT_SUPPORTED if command index is not applicable for targeted device or current mode (#SoftwarePackage or #ModeType), #MCU_VERSION_NOT_SUPPORTED if command version is not applicable for targeted device, #MCU_ERROR if the command couldn't be processed by the device, #MCU_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #MCU_VICODAEMON_IS_STOPPED if VICODaemon is not running, #MCU_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #MCU_INVALID_ARGUMENT_ERROR if an input parameter is null, #DPP_UART_TIMEOUT_ERROR if no response was received from the device, #DPP_NO_ACCESS_TO_INTERNAL_MEMORY_ERROR if an internal data handling error occurs.
 */
VICOLIB_API MCUStatusType liveInfo2VICO(const CharType* serialNumber, LiveInfo2VICOType* liveInfo);

/**
 * Returns boundary values for measured VICO live system status information values.
 * This request can only be sent in application-mode.
 * @param[in] serialNumber the target device.
 * @param[out] liveInfo the boundary values to be read.
 * @return status #MCU_SUCCESS if the values were successfully read, #MCU_COMMAND_NOT_SUPPORTED if command index is not applicable for targeted device or current mode (#SoftwarePackage or #ModeType), #MCU_VERSION_NOT_SUPPORTED if command version is not applicable for targeted device, #MCU_ERROR if the command couldn't be processed by the device, #MCU_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #MCU_VICODAEMON_IS_STOPPED if VICODaemon is not running, #MCU_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #MCU_INVALID_ARGUMENT_ERROR if an input parameter is null, #DPP_UART_TIMEOUT_ERROR if no response was received from the device, #DPP_NO_ACCESS_TO_INTERNAL_MEMORY_ERROR if an internal data handling error occurs.
 */
VICOLIB_API MCUStatusType liveInfoBoundariesVICO(const CharType* serialNumber, LiveInfoBoundariesVICOType* liveInfo);

/**
 * Returns live system status information from VIAMP.
 * This request can only be sent in application-mode.
 * @param[in] serialNumber the target device.
 * @param[out] liveInfo the live information to be read.
 * @return status #MCU_SUCCESS if the values were successfully read, #MCU_COMMAND_NOT_SUPPORTED if command index is not applicable for targeted device or current mode (#SoftwarePackage or #ModeType), #MCU_VERSION_NOT_SUPPORTED if command version is not applicable for targeted device, #MCU_ERROR if the command couldn't be processed by the device, #MCU_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #MCU_VICODAEMON_IS_STOPPED if VICODaemon is not running, #MCU_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #MCU_INVALID_ARGUMENT_ERROR if an input parameter is null, #DPP_UART_TIMEOUT_ERROR if no response was received from the device, #DPP_NO_ACCESS_TO_INTERNAL_MEMORY_ERROR if an internal data handling error occurs.
 */
VICOLIB_API MCUStatusType liveInfo1VIAMP(const CharType* serialNumber, LiveInfo1VIAMPType* liveInfo);

/**
 * Returns extended live system status information from VIAMP.
 * This request can only be sent in application-mode.
 * @param[in] serialNumber the target device.
 * @param[out] liveInfo the live information to be read.
 * @return status #MCU_SUCCESS if the values were successfully read, #MCU_COMMAND_NOT_SUPPORTED if command index is not applicable for targeted device or current mode (#SoftwarePackage or #ModeType), #MCU_VERSION_NOT_SUPPORTED if command version is not applicable for targeted device, #MCU_ERROR if the command couldn't be processed by the device, #MCU_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #MCU_VICODAEMON_IS_STOPPED if VICODaemon is not running, #MCU_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #MCU_INVALID_ARGUMENT_ERROR if an input parameter is null, #DPP_UART_TIMEOUT_ERROR if no response was received from the device, #DPP_NO_ACCESS_TO_INTERNAL_MEMORY_ERROR if an internal data handling error occurs.
 */
VICOLIB_API MCUStatusType liveInfo2VIAMP(const CharType* serialNumber, LiveInfo2VIAMPType* liveInfo);

/**
 * Returns boundary values for measured VIAMP live system status information values.
 * This request can only be sent in application-mode.
 * @param[in] serialNumber the target device.
 * @param[out] liveInfo the boundary values to be read.
 * @return status #MCU_SUCCESS if the values were successfully read, #MCU_COMMAND_NOT_SUPPORTED if command index is not applicable for targeted device or current mode (#SoftwarePackage or #ModeType), #MCU_VERSION_NOT_SUPPORTED if command version is not applicable for targeted device, #MCU_ERROR if the command couldn't be processed by the device, #MCU_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #MCU_VICODAEMON_IS_STOPPED if VICODaemon is not running, #MCU_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #MCU_INVALID_ARGUMENT_ERROR if an input parameter is null, #DPP_UART_TIMEOUT_ERROR if no response was received from the device, #DPP_NO_ACCESS_TO_INTERNAL_MEMORY_ERROR if an internal data handling error occurs.
 */
VICOLIB_API MCUStatusType liveInfoBoundariesVIAMP(const CharType* serialNumber, LiveInfoBoundariesVIAMPType* liveInfo);

/**
 * Returns VICO MCU bootloader firmware version.
 * This request can be sent in application- and EEA-mode.
 * @param[in] serialNumber the target device.
 * @param[out] devInfo the device information to be read.
 * @return status #MCU_SUCCESS if the values were successfully read, #MCU_COMMAND_NOT_SUPPORTED if command index is not applicable for targeted device or current mode (#SoftwarePackage or #ModeType), #MCU_VERSION_NOT_SUPPORTED if command version is not applicable for targeted device, #MCU_ERROR if the command couldn't be processed by the device, #MCU_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #MCU_VICODAEMON_IS_STOPPED if VICODaemon is not running, #MCU_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #MCU_INVALID_ARGUMENT_ERROR if an input parameter is null, #DPP_UART_TIMEOUT_ERROR if no response was received from the device, #DPP_NO_ACCESS_TO_INTERNAL_MEMORY_ERROR if an internal data handling error occurs.
 */
VICOLIB_API MCUStatusType devInfo1Bootloader(const CharType* serialNumber, DevInfo1BootloaderType* devInfo);

/**
 * Returns VICO MCU firmware version.
 * This request can be sent in application- and EEA-mode.
 * @param[in] serialNumber the target device.
 * @param[out] devInfo the device information to be read.
 * @return status #MCU_SUCCESS if the values were successfully read, #MCU_COMMAND_NOT_SUPPORTED if command index is not applicable for targeted device or current mode (#SoftwarePackage or #ModeType), #MCU_VERSION_NOT_SUPPORTED if command version is not applicable for targeted device, #MCU_ERROR if the command couldn't be processed by the device, #MCU_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #MCU_VICODAEMON_IS_STOPPED if VICODaemon is not running, #MCU_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #MCU_INVALID_ARGUMENT_ERROR if an input parameter is null, #DPP_UART_TIMEOUT_ERROR if no response was received from the device, #DPP_NO_ACCESS_TO_INTERNAL_MEMORY_ERROR if an internal data handling error occurs.
 */
VICOLIB_API MCUStatusType devInfo1VICO(const CharType* serialNumber, DevInfo1VICOType* devInfo);

/**
 * Returns VICO PCB and product article and serial number.
 * This request can be sent in bootloader- and application-mode.
 * @param[in] serialNumber the target device.
 * @param[in] infoSize the size of the voPcbArtNo, voPcbSerNo, voProdArtNo, and voProdSerNo arrays, which is typically 21.
 * @param[out] voPcbArtNo the article number of the VICO-AV/-DV PCB as string.
 * @param[out] voPcbSerNo the serial number of the VICO-AV/-DV PCB as string.
 * @param[out] voProdArtNo the product article number of the VICO-AV/-DV as string.
 * @param[out] voProdSerNo the product serial number of the VICO-AV/-DV as string.
 * @return status #MCU_SUCCESS if the values were successfully read, #MCU_COMMAND_NOT_SUPPORTED if command index is not applicable for targeted device or current mode (#SoftwarePackage or #ModeType), #MCU_VERSION_NOT_SUPPORTED if command version is not applicable for targeted device, #MCU_ERROR if the command couldn't be processed by the device, #MCU_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #MCU_VICODAEMON_IS_STOPPED if VICODaemon is not running, #MCU_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #MCU_INVALID_ARGUMENT_ERROR if an input parameter is null, #DPP_UART_TIMEOUT_ERROR if no response was received from the device, #DPP_NO_ACCESS_TO_INTERNAL_MEMORY_ERROR if an internal data handling error occurs.
 */
VICOLIB_API MCUStatusType devInfo2VICO(const CharType* serialNumber, const UInt8Type infoSize, CharType* voPcbArtNo, CharType* voPcbSerNo, CharType* voProdArtNo, CharType* voProdSerNo);

/**
 * Returns VIAMP PCB and product article and serial number and target temperature
 * This request can only be sent in application-mode.
 * @param[in] serialNumber the target device.
 * @param[in] infoSize the size of the vpPcbArtNo, vpPcbSerNo, vpProdArtNo, and vpProdSerNo arrays, which is typically 21.
 * @param[out] vpPcbArtNo the PCB article number of the VIAMP as string.
 * @param[out] vpPcbSerNo the PCB serial number of the VIAMP as string.
 * @param[out] vpProdArtNo the product article number of the VIAMP as string.
 * @param[out] vpProdSerNo the product serial number of the VIAMP as string.
 * @param[out] targetTmpEep the target temperature according to VIAMP EEPROM in degrees Celsius as 32 bit float.
 * @return status #MCU_SUCCESS if the values were successfully read, #MCU_COMMAND_NOT_SUPPORTED if command index is not applicable for targeted device or current mode (#SoftwarePackage or #ModeType), #MCU_VERSION_NOT_SUPPORTED if command version is not applicable for targeted device, #MCU_ERROR if the command couldn't be processed by the device, #MCU_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #MCU_VICODAEMON_IS_STOPPED if VICODaemon is not running, #MCU_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #MCU_INVALID_ARGUMENT_ERROR if an input parameter is null, #DPP_UART_TIMEOUT_ERROR if no response was received from the device, #DPP_NO_ACCESS_TO_INTERNAL_MEMORY_ERROR if an internal data handling error occurs.
 */
VICOLIB_API MCUStatusType devInfo1VIAMP(const CharType* serialNumber, const UInt8Type infoSize, CharType* vpPcbArtNo, CharType* vpPcbSerNo, CharType* vpProdArtNo, CharType* vpProdSerNo, FloatType* targetTmpEep);

/**
 * Changes the current operating mode.
 * This request can be sent in application- and EEA-mode.
 * @param[in] serialNumber the target device.
 * @param[in] md the mode to be set.
 * @return status #MCU_SUCCESS if the mode was successfully set, #MCU_COMMAND_NOT_SUPPORTED if command index is not applicable for targeted device or current mode (#SoftwarePackage or #ModeType), #MCU_VERSION_NOT_SUPPORTED if command version is not applicable for targeted device, #MCU_ERROR if the command couldn't be processed by the device, #MCU_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #MCU_VICODAEMON_IS_STOPPED if VICODaemon is not running, #MCU_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #MCU_INVALID_ARGUMENT_ERROR if an input parameter is null, #DPP_UART_TIMEOUT_ERROR if no response was received from the device, #DPP_NO_ACCESS_TO_INTERNAL_MEMORY_ERROR if an internal data handling error occurs.
 */
VICOLIB_API MCUStatusType setMode(const CharType* serialNumber, ModeType md);

/**
 * Performs a MCU software reset.
 * This request can be sent in bootloader-, application-, and EEA-mode.
 * @param[in] serialNumber the target device.
 * @return status #MCU_SUCCESS if MCU successfully reset, #MCU_COMMAND_NOT_SUPPORTED if command index is not applicable for targeted device or current mode (#SoftwarePackage or #ModeType), #MCU_VERSION_NOT_SUPPORTED if command version is not applicable for targeted device, #MCU_ERROR if the command couldn't be processed by the device, #MCU_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #MCU_VICODAEMON_IS_STOPPED if VICODaemon is not running, #MCU_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #MCU_INVALID_ARGUMENT_ERROR if an input parameter is null, #DPP_UART_TIMEOUT_ERROR if no response was received from the device, #DPP_NO_ACCESS_TO_INTERNAL_MEMORY_ERROR if an internal data handling error occurs.
 */
VICOLIB_API MCUStatusType resetMCU(const CharType* serialNumber);

/**
 * Performs a software reset of the FPGA (DPP) via MCU.
  * This request can be sent in application- and EEA-mode.
 * @note In order to ensure that the user can receive a response when calling this function, the FPGA reset will be triggered with a delay of 5s after the response has been sent out.
 * @param[in] serialNumber the target device.
 * @return status #MCU_SUCCESS if FPGA will successfully reset, #MCU_COMMAND_NOT_SUPPORTED if command index is not applicable for targeted device or current mode (#SoftwarePackage or #ModeType), #MCU_VERSION_NOT_SUPPORTED if command version is not applicable for targeted device, #MCU_ERROR if the command couldn't be processed by the device, #MCU_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #MCU_VICODAEMON_IS_STOPPED if VICODaemon is not running, #MCU_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #MCU_INVALID_ARGUMENT_ERROR if an input parameter is null, #DPP_UART_TIMEOUT_ERROR if no response was received from the device, #DPP_NO_ACCESS_TO_INTERNAL_MEMORY_ERROR if an internal data handling error occurs.
 */
VICOLIB_API MCUStatusType resetFPGA(const CharType* serialNumber);

/**
 * Reads out current SDD temperature.
 * This request can only be sent in application-mode.
 * @param[in] serialNumber the target device.
 * @param[out] tmp the temperature information to be read.
 * @return status #MCU_SUCCESS if the value was successfully read, #MCU_COMMAND_NOT_SUPPORTED if command index is not applicable for targeted device or current mode (#SoftwarePackage or #ModeType), #MCU_VERSION_NOT_SUPPORTED if command version is not applicable for targeted device, #MCU_ERROR if the command couldn't be processed by the device, #MCU_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #MCU_VICODAEMON_IS_STOPPED if VICODaemon is not running, #MCU_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #MCU_INVALID_ARGUMENT_ERROR if an input parameter is null, #DPP_UART_TIMEOUT_ERROR if no response was received from the device, #DPP_NO_ACCESS_TO_INTERNAL_MEMORY_ERROR if an internal data handling error occurs.
 */
VICOLIB_API MCUStatusType getTemp(const CharType* serialNumber, TempType* tmp);

/**
 * Sets a new SDD target temperature.
 * This request can only be sent in application-mode.
 * @note This temperature is volatile and will be used until a power cycle.
 * @param[in] serialNumber the target device.
 * @param[in] targetTmp the temperature to be set in °C.
 * @return status #MCU_SUCCESS if the value was successfully set, #MCU_COMMAND_NOT_SUPPORTED if command index is not applicable for targeted device or current mode (#SoftwarePackage or #ModeType), #MCU_VERSION_NOT_SUPPORTED if command version is not applicable for targeted device, #MCU_ERROR if the command couldn't be processed by the device, #MCU_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #MCU_VICODAEMON_IS_STOPPED if VICODaemon is not running, #MCU_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #MCU_INVALID_ARGUMENT_ERROR if an input parameter is null, #DPP_UART_TIMEOUT_ERROR if no response was received from the device, #DPP_NO_ACCESS_TO_INTERNAL_MEMORY_ERROR if an internal data handling error occurs.
 */
VICOLIB_API MCUStatusType setTemp(const CharType* serialNumber, FloatType targetTmp);

/**
 * Sets the deviation and time period for ready (RDY) output.
 * This request can only be sent in application-mode.
 * @note These values are volatile and will be used until a power cycle.
 * @param[in] serialNumber the target device.
 * @param[in] dvtn the deviation (temperature range (±) between expected and current temp) to set.
 * @param[in] prd the period (time the temperature shall be in deviation range) to set.
 * @return status #MCU_SUCCESS if the value were successfully set, #MCU_COMMAND_NOT_SUPPORTED if command index is not applicable for targeted device or current mode (#SoftwarePackage or #ModeType), #MCU_VERSION_NOT_SUPPORTED if command version is not applicable for targeted device, #MCU_ERROR if the command couldn't be processed by the device, #MCU_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #MCU_VICODAEMON_IS_STOPPED if VICODaemon is not running, #MCU_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #MCU_INVALID_ARGUMENT_ERROR if an input parameter is null, #DPP_UART_TIMEOUT_ERROR if no response was received from the device, #DPP_NO_ACCESS_TO_INTERNAL_MEMORY_ERROR if an internal data handling error occurs.
 */
VICOLIB_API MCUStatusType setRdy(const CharType* serialNumber, FloatType dvtn, FloatType prd);

/**
 * Sets deviation and time period for almost ready (ARDY) output.
 * This request can only be sent in application-mode.
 * @note These values are volatile and will be used until a power cycle.
 * @param[in] serialNumber the target device.
 * @param[in] dvtn the deviation (temperature range (±) between expected and current temp) to set.
 * @param[in] prd the period (time the temperature shall be in deviation range) to set.
 * @return status #MCU_SUCCESS if the value were successfully set, #MCU_COMMAND_NOT_SUPPORTED if command index is not applicable for targeted device or current mode (#SoftwarePackage or #ModeType), #MCU_VERSION_NOT_SUPPORTED if command version is not applicable for targeted device, #MCU_ERROR if the command couldn't be processed by the device, #MCU_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #MCU_VICODAEMON_IS_STOPPED if VICODaemon is not running, #MCU_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #MCU_INVALID_ARGUMENT_ERROR if an input parameter is null, #DPP_UART_TIMEOUT_ERROR if no response was received from the device, #DPP_NO_ACCESS_TO_INTERNAL_MEMORY_ERROR if an internal data handling error occurs.
 */
VICOLIB_API MCUStatusType setARdy(const CharType* serialNumber, FloatType dvtn, FloatType prd);

/**
 * Reads out the deviation and time period for ready (RDY) output.
 * This request can only be sent in application-mode.
 * @param[in] serialNumber the target device.
 * @param[out] dvtn the deviation (temperature range (±) between expected and current temp) to set.
 * @param[out] prd the period (time the temperature shall be in deviation range) to set.
 * @return status #MCU_SUCCESS if the value were successfully read, #MCU_COMMAND_NOT_SUPPORTED if command index is not applicable for targeted device or current mode (#SoftwarePackage or #ModeType), #MCU_VERSION_NOT_SUPPORTED if command version is not applicable for targeted device, #MCU_ERROR if the command couldn't be processed by the device, #MCU_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #MCU_VICODAEMON_IS_STOPPED if VICODaemon is not running, #MCU_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #MCU_INVALID_ARGUMENT_ERROR if an input parameter is null, #DPP_UART_TIMEOUT_ERROR if no response was received from the device, #DPP_NO_ACCESS_TO_INTERNAL_MEMORY_ERROR if an internal data handling error occurs.
 */
VICOLIB_API MCUStatusType getRdy(const CharType* serialNumber, FloatType* dvtn, FloatType* prd);

/**
 * Reads out deviation and time period for almost ready (ARDY) output.
 * This request can only be sent in application-mode.
 * @param[in] serialNumber the target device.
 * @param[out] dvtn the deviation (temperature range (±) between expected and current temp) to set.
 * @param[out] prd the period (time the temperature shall be in deviation range) to set.
 * @return status #MCU_SUCCESS if the value were successfully read, #MCU_COMMAND_NOT_SUPPORTED if command index is not applicable for targeted device or current mode (#SoftwarePackage or #ModeType), #MCU_VERSION_NOT_SUPPORTED if command version is not applicable for targeted device, #MCU_ERROR if the command couldn't be processed by the device, #MCU_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #MCU_VICODAEMON_IS_STOPPED if VICODaemon is not running, #MCU_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #MCU_INVALID_ARGUMENT_ERROR if an input parameter is null, #DPP_UART_TIMEOUT_ERROR if no response was received from the device, #DPP_NO_ACCESS_TO_INTERNAL_MEMORY_ERROR if an internal data handling error occurs.
 */
VICOLIB_API MCUStatusType getARdy(const CharType* serialNumber, FloatType* dvtn, FloatType* prd);

/**
 * Reads out the data from MCU EEPROM.
 * This request can be sent in application- and EEA-mode.
 * @param[in] serialNumber the target device.
 * @param[in] addStart the start address of the data to read with range 0-2047.
 * @param[in] len the length of the data to read, which is maximum 249 bytes.
 * @param[out] data the data to read from the MCU EEPROM.
 * @return status #MCU_SUCCESS if the data was successfully read, #MCU_COMMAND_NOT_SUPPORTED if command index is not applicable for targeted device or current mode (#SoftwarePackage or #ModeType), #MCU_VERSION_NOT_SUPPORTED if command version is not applicable for targeted device, #MCU_ERROR if the command couldn't be processed by the device, #MCU_LEN_OUT_OF_VALID_RANGE if parameter len is outside the valid range, #MCU_ADDRESS_OUT_OF_VALID_RANGE if parameter addStart is outside the valid range, #MCU_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #MCU_VICODAEMON_IS_STOPPED if VICODaemon is not running, #MCU_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #MCU_INVALID_ARGUMENT_ERROR if an input parameter is null, #DPP_UART_TIMEOUT_ERROR if no response was received from the device, #DPP_NO_ACCESS_TO_INTERNAL_MEMORY_ERROR if an internal data handling error occurs.
 */
VICOLIB_API MCUStatusType getEEP(const CharType* serialNumber, UInt16Type addStart, UInt8Type len, UInt8Type* data);

/**
 * Writes data to MCU EEPROM.
 * This request can only be sent in EEA-mode.
 * @param[in] serialNumber the target device.
 * @param[in] addStart the start address of the data to write with range 0-2047.
 * @param[in] len the length of the data to write, which is maximum 247 bytes.
 * @param[in] data the data to write to the MCU EEPROM.
 * @return #MCU_SUCCESS if the data was successfully set, #MCU_COMMAND_NOT_SUPPORTED if command index is not applicable for targeted device or current mode (#SoftwarePackage or #ModeType), #MCU_VERSION_NOT_SUPPORTED if command version is not applicable for targeted device, #MCU_ERROR if the command couldn't be processed by the device, #MCU_LEN_OUT_OF_VALID_RANGE if parameter len is outside the valid range, #MCU_ADDRESS_OUT_OF_VALID_RANGE if parameter addStart is outside the valid range, #MCU_SYSTEM_IS_NOT_IN_EEA_MODE if the request isn't done in EEA-mode, #MCU_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #MCU_VICODAEMON_IS_STOPPED if VICODaemon is not running, #MCU_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #MCU_INVALID_ARGUMENT_ERROR if an input parameter is null, #DPP_UART_TIMEOUT_ERROR if no response was received from the device, #DPP_NO_ACCESS_TO_INTERNAL_MEMORY_ERROR if an internal data handling error occurs.
 */
VICOLIB_API MCUStatusType setEEP(const CharType* serialNumber, UInt16Type addStart, UInt8Type len, UInt8Type* data);

/**
 * Performs two-wire interface (I2C) data communication.
 * This request can be sent in application- and EEA-mode.
 * @param[in] serialNumber the target device.
 * @param[in] ad the device address at TWI.
 * @param[in] md the mode, which is #TWI_WRITE, #TWI_READ, or #TWI_WRITE_READ
 * @param[in] ses the send buffer size, which contains the number of bytes to be transferred, which is maximum 246 bytes.
 * @param[in] res the receive buffer size, which contains the number of bytes to be received, which is maximum 249 bytes.
 * @param[in] sendData the data to be sent.
 * @param[out] recData the data to be received.
 * @return #MCU_SUCCESS if the data was successfully sent and/or received, #MCU_COMMAND_NOT_SUPPORTED if command index is not applicable for targeted device or current mode (#SoftwarePackage or #ModeType), #MCU_VERSION_NOT_SUPPORTED if command version is not applicable for targeted device, #MCU_ERROR if the command couldn't be processed by the device, #MCU_LEN_OUT_OF_VALID_RANGE if parameter ses/res is outside the valid range, #MCU_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #MCU_VICODAEMON_IS_STOPPED if VICODaemon is not running, #MCU_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #MCU_INVALID_ARGUMENT_ERROR if an input parameter is null, #DPP_UART_TIMEOUT_ERROR if no response was received from the device, #DPP_NO_ACCESS_TO_INTERNAL_MEMORY_ERROR if an internal data handling error occurs.
 */
VICOLIB_API MCUStatusType twi(const CharType* serialNumber, UInt8Type ad, TWIModeType md, UInt8Type ses, UInt8Type res, UInt8Type* sendData, UInt8Type* recData);

/**
 * Gets the value (0 or 1) of a specific MCU GPIO pin.
 * This request can be sent in application- and EEA-mode.
 * @param[in] serialNumber the target device.
 * @param[in] por the port of the pin.
 * @param[in] pin the pin number of the port.
 * @param[out] val the current value to be read as bool.
 * @return #MCU_SUCCESS if the value was successfully read, #MCU_COMMAND_NOT_SUPPORTED if command index is not applicable for targeted device or current mode (#SoftwarePackage or #ModeType), #MCU_VERSION_NOT_SUPPORTED if command version is not applicable for targeted device, #MCU_ERROR if the command couldn't be processed by the device, #MCU_LEN_OUT_OF_VALID_RANGE if parameter port is outside the valid range, #MCU_ADDRESS_OUT_OF_VALID_RANGE if parameter pin is outside the valid range, #MCU_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #MCU_VICODAEMON_IS_STOPPED if VICODaemon is not running, #MCU_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #MCU_INVALID_ARGUMENT_ERROR if an input parameter is null, #DPP_UART_TIMEOUT_ERROR if no response was received from the device, #DPP_NO_ACCESS_TO_INTERNAL_MEMORY_ERROR if an internal data handling error occurs.
 */
VICOLIB_API MCUStatusType getIO(const CharType* serialNumber, PortType por, UInt8Type pin, BooleanType* val);

/**
 * Sets the value (0 or 1) of a specific MCU GPIO pin.
 * This request can be sent in application- and EEA-mode.
 * @param[in] serialNumber the target device.
 * @param[in] por the port of the pin.
 * @param[in] pin the pin number of the port.
 * @param[in] val the current value to be set as bool.
 * @return #MCU_SUCCESS if the value was successfully set, #MCU_COMMAND_NOT_SUPPORTED if command index is not applicable for targeted device or current mode (#SoftwarePackage or #ModeType), #MCU_VERSION_NOT_SUPPORTED if command version is not applicable for targeted device, #MCU_ERROR if the command couldn't be processed by the device, #MCU_LEN_OUT_OF_VALID_RANGE if parameter port is outside the valid range, #MCU_ADDRESS_OUT_OF_VALID_RANGE if parameter pin is outside the valid range, #MCU_SYSTEM_IS_NOT_IN_EEA_MODE if parameter val is outside the valid range, #MCU_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #MCU_VICODAEMON_IS_STOPPED if VICODaemon is not running, #MCU_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #MCU_INVALID_ARGUMENT_ERROR if an input parameter is null, #DPP_UART_TIMEOUT_ERROR if no response was received from the device, #DPP_NO_ACCESS_TO_INTERNAL_MEMORY_ERROR if an internal data handling error occurs.
 */
VICOLIB_API MCUStatusType setIO(const CharType* serialNumber, PortType por, UInt8Type pin, BooleanType val);

/**
 * Reads out the ADC input of a specific MCU pin.
 * This request can be sent in application- and EEA-mode.
 * @param[in] serialNumber the target device.
 * @param[in] por the port of the pin.
 * @param[in] pin the pin number of the port.
 * @param[out] adcVal contains the ADC readout value in mV.
 * @return #MCU_SUCCESS if the value was successfully read, #MCU_COMMAND_NOT_SUPPORTED if command index is not applicable for targeted device or current mode (#SoftwarePackage or #ModeType), #MCU_VERSION_NOT_SUPPORTED if command version is not applicable for targeted device, #MCU_ERROR if the command couldn't be processed by the device, #MCU_LEN_OUT_OF_VALID_RANGE if parameter port is outside the valid range, #MCU_ADDRESS_OUT_OF_VALID_RANGE if parameter pin is outside the valid range, #MCU_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #MCU_VICODAEMON_IS_STOPPED if VICODaemon is not running, #MCU_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #MCU_INVALID_ARGUMENT_ERROR if an input parameter is null, #DPP_UART_TIMEOUT_ERROR if no response was received from the device, #DPP_NO_ACCESS_TO_INTERNAL_MEMORY_ERROR if an internal data handling error occurs.
 */
VICOLIB_API MCUStatusType getADC(const CharType* serialNumber, PortType por, UInt8Type pin, UInt16Type* adcVal);

/**
 * Sets the DAC output of a specific MCU pin.
 * This request can be sent in application- and EEA-mode.
 * @param[in] serialNumber the target device.
 * @param[in] por the port of the pin.
 * @param[in] pin the pin number of the port.
 * @param[in] dacVal the DAC set value in mV.
 * @return #MCU_SUCCESS if the value was successfully set, #MCU_COMMAND_NOT_SUPPORTED if command index is not applicable for targeted device or current mode (#SoftwarePackage or #ModeType), #MCU_VERSION_NOT_SUPPORTED if command version is not applicable for targeted device, #MCU_ERROR if the command couldn't be processed by the device, #MCU_LEN_OUT_OF_VALID_RANGE if parameter port is outside the valid range, #MCU_ADDRESS_OUT_OF_VALID_RANGE if parameter pin is outside the valid range, #MCU_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #MCU_VICODAEMON_IS_STOPPED if VICODaemon is not running, #MCU_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #MCU_INVALID_ARGUMENT_ERROR if an input parameter is null, #DPP_UART_TIMEOUT_ERROR if no response was received from the device, #DPP_NO_ACCESS_TO_INTERNAL_MEMORY_ERROR if an internal data handling error occurs.
 */
VICOLIB_API MCUStatusType setDAC(const CharType* serialNumber, PortType por, UInt8Type pin, UInt16Type dacVal);

/**
 * Sets the maximum TEC current.
 * This request can only be sent in application-mode.
 * @note This value is volatile and will be used until a power cycle. 
 * @param[in] serialNumber the target device.
 * @param[in] itecMax the maximum TEC current in mA with maximum 1000mA.
 * @return #MCU_SUCCESS if the value was successfully set, #MCU_COMMAND_NOT_SUPPORTED if command index is not applicable for targeted device or current mode (#SoftwarePackage or #ModeType), #MCU_VERSION_NOT_SUPPORTED if command version is not applicable for targeted device, #MCU_ERROR if the command couldn't be processed by the device, #MCU_LEN_OUT_OF_VALID_RANGE if parameter itecMax is outside the valid range, #MCU_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #MCU_VICODAEMON_IS_STOPPED if VICODaemon is not running, #MCU_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #MCU_INVALID_ARGUMENT_ERROR if an input parameter is null, #DPP_UART_TIMEOUT_ERROR if no response was received from the device, #DPP_NO_ACCESS_TO_INTERNAL_MEMORY_ERROR if an internal data handling error occurs.
 */
VICOLIB_API MCUStatusType setIMax(const CharType* serialNumber, UInt16Type itecMax);

/**
 * Sets the maximum TEC voltage.
 * This request can only be sent in application-mode.
 * @note This value is volatile and will be used until a power cycle.
 * @param[in] serialNumber the target device.
 * @param[in] utecMax the maximum TEC voltage in mV with maximum 10000mV.
 * @return #MCU_SUCCESS if the value was successfully set, #MCU_COMMAND_NOT_SUPPORTED if command index is not applicable for targeted device or current mode (#SoftwarePackage or #ModeType), #MCU_VERSION_NOT_SUPPORTED if command version is not applicable for targeted device, #MCU_ERROR if the command couldn't be processed by the device, #MCU_LEN_OUT_OF_VALID_RANGE if parameter utecMax is outside the valid range, #MCU_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #MCU_VICODAEMON_IS_STOPPED if VICODaemon is not running, #MCU_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #MCU_INVALID_ARGUMENT_ERROR if an input parameter is null, #DPP_UART_TIMEOUT_ERROR if no response was received from the device, #DPP_NO_ACCESS_TO_INTERNAL_MEMORY_ERROR if an internal data handling error occurs.
 */
VICOLIB_API MCUStatusType setUMax(const CharType* serialNumber, UInt16Type utecMax);

/**
 * Gets the debug information from TEC control loop.
 * This request can only be sent in application-mode.
 * @param[in] serialNumber the target device.
 * @param[out] dbgClp the debug control loop data elements.
 * @return #MCU_SUCCESS if the values were successfully read, #MCU_COMMAND_NOT_SUPPORTED if command index is not applicable for targeted device or current mode (#SoftwarePackage or #ModeType), #MCU_VERSION_NOT_SUPPORTED if command version is not applicable for targeted device, #MCU_ERROR if the command couldn't be processed by the device, #MCU_LEN_OUT_OF_VALID_RANGE if control loop not in operation (check #ModeType), #MCU_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #MCU_VICODAEMON_IS_STOPPED if VICODaemon is not running, #MCU_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #MCU_INVALID_ARGUMENT_ERROR if an input parameter is null, #DPP_UART_TIMEOUT_ERROR if no response was received from the device, #DPP_NO_ACCESS_TO_INTERNAL_MEMORY_ERROR if an internal data handling error occurs.
 */
VICOLIB_API MCUStatusType dbgClp(const CharType* serialNumber, DbgClpType* dbgClp);

/**
 * Gets the extended debug information from TEC control loop.
 * This request can only be sent in application-mode.
 * @param[in] serialNumber the target device.
 * @param[out] dbgClpExt the extended debug control loop data elements.
 * @return #MCU_SUCCESS if the values were successfully read, #MCU_COMMAND_NOT_SUPPORTED if command index is not applicable for targeted device or current mode (#SoftwarePackage or #ModeType), #MCU_VERSION_NOT_SUPPORTED if command version is not applicable for targeted device, #MCU_ERROR if the command couldn't be processed by the device, #MCU_LEN_OUT_OF_VALID_RANGE if control loop not in operation (check #ModeType), #MCU_NO_DEVICE_WITH_ID_CONNECTED_ERROR if no device connection with targeted serial number is active, #MCU_VICODAEMON_IS_STOPPED if VICODaemon is not running, #MCU_VICOLIB_TIMEOUT_ERROR if no response was received from the device, #MCU_INVALID_ARGUMENT_ERROR if an input parameter is null, #DPP_UART_TIMEOUT_ERROR if no response was received from the device, #DPP_NO_ACCESS_TO_INTERNAL_MEMORY_ERROR if an internal data handling error occurs.
 */
VICOLIB_API MCUStatusType dbgClpExt(const CharType* serialNumber, DbgClpExtType* dbgClpExt);

#ifdef __cplusplus
}
#endif

#endif // VICOLIB_H
