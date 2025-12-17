#ifndef TYPES_H
#define TYPES_H
#include <stdbool.h>
/**
 * UInt8Type for a range between 0 and 255.
 */
typedef unsigned char		UInt8Type;

/**
 * UInt16Type for a range between 0 and 65535.
 */
typedef unsigned short		UInt16Type;

/**
 * UInt32Type for a range between 0 and 4294967295.
 */
typedef unsigned int		UInt32Type;

/**
 * FloatType for single-precision 32-bit floating point.
 */
typedef float				FloatType;

/**
 * DoubleType for double-precision 64-bit floating point.
 */
typedef double				DoubleType;

/**
 * BooleanType for usage of true and false.
 */
typedef bool				BooleanType;
/**
 * CharType for usage of Strings.
 */
typedef char				CharType;

/**
 * VICOLib-related return codes. Range 0x00 - 0x19 is reserved for DPP return codes. Range 0x20 - 0x39 is reserved for VICOLib-specific return codes.
 */
typedef enum
{
	/** 0x00: VICOLib return code: Request successfully processed. */
	VICO_SUCCESS =								0x00,
	/** 0x50: VICOLib return code: No device connection with targeted serial number active. */
	VICO_NO_DEVICE_WITH_ID_CONNECTED_ERROR =	0x50,
	/** 0x51: VICOLib return code: VICODaemon is currently not running. See \ref API (VICODaemon). */
	VICO_VICODAEMON_IS_STOPPED =				0x51,
	/** 0x52: VICOLib return code: Timeout error due to no response. */
	VICO_VICOLIB_TIMEOUT_ERROR =				0x52,
	/** 0x53: VICOLib return code: Data responded by the device does not fit into given data type. */
	VICO_RESPONSE_OUT_OF_BOUNDS_ERROR =			0x53,
	/** 0x54: VICOLib return code: Given argument(s) not allowed or null. */
	VICO_INVALID_ARGUMENT_ERROR =				0x54,
	/** 0x55: VICOLib return code: Data responded by the device not as expected. */
	VICO_INVALID_RESPONSE_DATA_ERROR =			0x55,
	/** 0xFF: VICOLib return code: Undefined error. */
	VICO_UNDEFINED_ERROR =						0xFF
} VICOStatusType;

/**
 * The connection type retrieved by #scanTcpDevices(), #scanUdpDevices(), and #scanUsbDevices().
 */
typedef enum
{
	/** 0: If the found device connection couldn't be assigned. */
	INTERFACE_UNKNOWN =			0U,
	/** 1: If the found device connection is established via TCP. */
	INTERFACE_ETHERNET_TCP =	1U,
	/** 2: If the found device connection is established via UDP. */
	INTERFACE_ETHERNET_UDP =	2U,
	/** 3: If the found device connection is established via USB (FT4222). */
	INTERFACE_USB =				3U,
	/** 4: If the found device connection is established via USB (HID). */
	INTERFACE_USB_HID =			4U
} InterfaceType;

/**
 * DPP-related return codes. Range 0x00 - 0x4F is reserved for DPP return codes. Range 0x50 - 0x7F is reserved for VICOLib-specific return codes.
 */
typedef enum
{
	/** 0x00: DPP return code: Request successfully processed. */
	DPP_SUCCESS =								0x00,
	/** 0x01: DPP return code: Error during write request: Written value is out of range. The value was not applied in the device and remains unchanged. The closed valid value for your request will be returned by the function call. */
	DPP_OUT_OF_RANGE_ERROR =					0x01,
	/** 0x02: DPP return code: Error during write request: Requested parameter is read-only and the write request was rejected. The value in the device remains unchanged. */
	DPP_PARAMETER_READ_ONLY_ERROR =				0x02,
	/** 0x03: DPP return code: Error during write request: Requested parameter does not exist in the device. No changes to the device configuration were made. */
	DPP_PARAMETER_NOT_EXISTING_ERROR =			0x03,
	/** 0x04: DPP return code: Invalid command: Request could not be interpreted since the low-level command byte was invalid valid. No changes to the device configuration were made. */
	DPP_INVALID_COMMAND_ERROR =					0x04,
	/** 0x05: DPP return code: Error during request: Parameter currently not accessible (e.g. due to running measurement, power down, temperature sensor not ready). No changes to the device configuration were made. */
	DPP_REQUEST_CURRENTLY_NOT_POSSIBLE_ERROR =	0x05,
	/** 0x06: DPP return code: Error during request: Internal timeout appeared. The value in the device might be changed. */
	DPP_TIMEOUT_ERROR =							0x06,
	/** 0x07: DPP return code: Syntax error, unpermitted combination of requests. No changes to the device configuration were made. */
	DPP_SYNTAX_ERROR_INVALID_REQUEST_ERROR =	0x07,

	/** 0x50: VICOLib return code: No device connection with targeted serial number active. Request could not be sent to the device. */
	DPP_NO_DEVICE_WITH_ID_CONNECTED_ERROR =		0x50,
	/** 0x51: VICOLib return code: VICODaemon is currently not running. See \ref API (VICODaemon). Request could not be sent to the device. */
	DPP_VICODAEMON_IS_STOPPED =					0x51,
	/** 0x52: VICOLib return code: Timeout error due to no response from the device. Make sure the device is powered up and connected to your system. Try to find the device using scanning functions (#scanUsbDevices(), #scanTcpDevices(), #scanUdpDevices()). */
	DPP_VICOLIB_TIMEOUT_ERROR =					0x52,
	/** 0x53: VICOLib return code: Data responded by the device does not fit into given data type. */
	DPP_RESPONSE_OUT_OF_BOUNDS_ERROR =			0x53,
	/** 0x54: VICOLib return code: Given argument(s) not allowed or null. No request was sent to the device. */
	DPP_INVALID_ARGUMENT_ERROR =				0x54,
	/** 0x55: VICOLib return code: Data responded by the device not as expected. */
	DPP_INVALID_RESPONSE_DATA_ERROR =			0x55,

	/** 0x56: VICOLib return code: Given argument value is not in valid range to be sent to the DPP. This might be due to a data type error (e.g., value is too high) or due to an quantization error (e.g., value is not an integer multiple of allowed quantization). Example: This error is returned when calling #setSlowFilterGapTime() with a gapTime value that is not an integer multiple of 12.5ns. <br>
	The value was not sent to the device and remains unchanged. The closed valid value for your request will be returned by the function call. */
	DPP_VICOLIB_OUT_OF_RANGE_ERROR =			0x56,
	/** 0x57: VICOLib return code: Command is not applicable for the targeted device (e.g. DPP datagram sent to VICO-AV). */
	DPP_COMMAND_NOT_SUPPORTED_ERROR =			0x57,

	/** 0xFF: VICOLib return code: Undefined error. */
	DPP_UNDEFINED_ERROR =						0xFF
} DPPStatusType;

/**
 * Structure to represent the major-, minor-, patch-, and build version of the VICOLib (acquired by #getLibraryVersion()) and VICODaemon (acquired by #getDaemonVersion()).
 */
typedef struct
{
	UInt16Type major;
	UInt16Type minor;
	UInt16Type patch;
	UInt16Type build;
} VersionType;

/**
 * Targeted DPP command, which is #READ or #WRITE, mainly used VICOLib-internally.
 */
typedef enum
{
	/** 0x00: Requests reading a value. */
	READ =	0U,
	/** 0x01: Requests writing a value. */
	WRITE =	1U
} CommandType;

/**
 * Stop condition type used in #setStopCondition() and #getStopCondition().
 */
typedef enum
{
	/** 0: Active run continues until a #stopRun() is received. */
	NONE =							0U,
	/** 1: Active run is stopped when a fixed livetime is reached. */
	STOP_AT_FIXED_LIVETIME =		1U,
	/** 2: Active run is stopped when a fixed realtime is reached. */
	STOP_AT_FIXED_REALTIME =		2U,
	/** 3: Active run is stopped when a fixed number of input counts is reached. */
	STOP_AT_FIXED_INPUT_COUNTS =	3U,
	/** 4: Active run is stopped when a fixed number of output counts is reached. */
	STOP_AT_FIXED_OUTPUT_COUNTS =	4U
} StopConditionType;

/**
 * All run statistics structure used in #getRunStatistics().
 */
typedef struct
{
	BooleanType isRunActive;
	DoubleType realTime;
	DoubleType liveTime;
	UInt32Type outputCounts;
	UInt32Type inputCounts;
	UInt32Type outputCountRate;
	UInt32Type inputCountRate;
} RunStatisticsType;

/**
 * Baseline trim type used in #setBaselineTrim() and #getBaselineTrim().
 */
typedef enum
{
	/** 0: Set the peaking time of the mediumfilter to the highest possible value (e.g. same length as slowfilter). */
	LONGEST_POSSIBLE_MEDIUM_FILTER =	0U,
	/** 1: Set the peaking time of the mediumfilter to a high value (e.g. half length of slowfilter). */
	LONG_MEDIUM_FILTER =				1U,
	/** 2: Set the peaking time of the mediumfilter to an intermediate value (e.g. quarter length of slowfilter). */
	INTERMEDIATE_MEDIUM_FILTER =		2U,
	/** 3: Set the peaking time of the mediumfilter to a short value (e.g. eighth length of slowfilter). */
	SHORT_MEDIUM_FILTER =				3U,
	/** 4: Set the peaking time of the mediumfilter to the shortest possible value (e.g. sixteenth length of slowfilter). */
	SHORTEST_POSSIBLE_MEDIUM_FILTER =	4U
} BaselineTrimType;

/**
 * Reset detection type used in #setResetDetection() and #getResetDetection().
 */
typedef enum
{
	/** 0: Use reset detection threshold suitable for a VITUS SDD. */
	CSA =	0U,
	/** 1: Use reset detection threshold suitable for a PIN diode replacement SDD. */
	CLD =	1U,
	/** 2: Use reset detection threshold suitable for a proportional counter replacement. */
	CPC =	2U
} ResetDetectionType;

/**
 * Clocking speed type used in #setClockingSpeed() and #getClockingSpeed().
 */
typedef enum
{
	/** 0: Use clocking speed of 80 MHz. */
	MHZ_80 =	0U
} ClockingSpeedType;

/**
 * Trigger source type used in #setEventTriggerSource() and #getEventTriggerSource().
 */
typedef enum
{
	/** 0: Trigger is activated instantly without any condition. The trigger value defined by #setEventTriggerValue() has no influence. */
	INSTANT_TRIGGER =						0U,
	/** 1: Trigger when an specific output value of the ADC is reached. The specific ADC code is defined by #setEventTriggerValue(). */
	SPECIFIC_ADC_VALUE =					1U,
	/** 2: Trigger when an ADC overrange occurs (overvoltage or undervoltage at ADC signal input). The trigger value defined by #setEventTriggerValue() has no influence. */
	ADC_OUT_OF_RANGE =						2U,
	/** 3: Trigger when an input count is detected in the fastfilter. The trigger value defined by #setEventTriggerValue() has no influence. */
	FASTFILTER_TRIGGER =					3U,
	/** 4: Trigger when a reset is detected in the fastfilter. The trigger value defined by #setEventTriggerValue() has no influence. */
	FASTFILTER_RESET_DETECTED =				4U,
	/** 5: Trigger when a pileup is rejected in the fastfilter using the maximum width criteria defined by #setFastFilterMaxWidth(). The trigger value defined by #setEventTriggerValue() has no influence. */
	FASTFILTER_PILEUP =						5U,
	/** 6: Trigger when an input count is detected in the mediumfilter. The trigger value defined by #setEventTriggerValue() has no influence. */
	MEDIUMFILTER_TRIGGER =					6U,
	/** 7: Trigger when a reset is detected in the mediumfilter. The trigger value defined by #setEventTriggerValue() has no influence. */
	MEDIUMFILTER_RESET_DETECTED =			7U,
	/** 8: Trigger when a pileup is rejected in the mediumfilter using the maximum width criteria defined by #setMediumFilterMaxWidth(). The trigger value defined by #setEventTriggerValue() has no influence. */
	MEDIUMFILTER_PILEUP =					8U,
	/** 9: Trigger when a new output count of any energy is added to the MCA. The trigger value defined by #setEventTriggerValue() has no influence. */
	NEW_OUTPUT_COUNT_ANY_ENERGY =			9U,
	/** 10: Trigger when a new output count of a specific energy is added to the MCA. The MCA bin of the specific energy is defined by defined by #setEventTriggerValue(). */
	NEW_OUTPUT_COUNT_SPECIFIC_ENERGY =		10U,
	/** 11: Trigger when a new baseline sample is acquired. The trigger value defined by #setEventTriggerValue() has no influence. */
	NEW_BASELINE_SAMPLE =					11U,
	/** 12: Trigger when a dynamic reset is initiated by the DPP. The trigger value defined by #setEventTriggerValue() has no influence. */
	ACTIVE_RESET_INITIATE =					12U
} TriggerSourceType;

/**
 * Trigger timeout type used in #setEventScopeTriggerTimeout() and #getEventScopeTriggerTimeout(). */
typedef enum
{
	/** 0: Wait up to 1s for a trigger when reading an event scope signal trace using #getEventScope(). */
	TIMEOUT_1_SECOND =	0U,
	/** 1: Wait up to 2s for a trigger when reading an event scope signal trace using #getEventScope(). */
	TIMEOUT_2_SECOND =	1U,
	/** 2: Wait up to 4s for a trigger when reading an event scope signal trace using #getEventScope(). */
	TIMEOUT_4_SECOND =	2U,
	/** 3: Wait up to 8s for a trigger when reading an event scope signal trace using #getEventScope(). */
	TIMEOUT_8_SECOND =	3U,
	/** 4: Wait up to 16s for a trigger when reading an event scope signal trace using #getEventScope(). */
	TIMEOUT_16_SECOND =	4U,
} TriggerTimeoutType;


/**
 * Event scope type used in #getEventScope().
 */
typedef enum
{
	/** 0: Raw signal data of the ADC. */
	ADC_DATA =			0U,
	/** 1: Fastfilter signal data. */
	FASTFILTER =		1U,
	/** 2: Mediumfilter signal data. */
	MEDIUMFILTER =		2U,
	/** 3: Slowfilter signal data. */
	SLOWFILTER =		3U,
	/** 4: Moving average signal of baseline value. */
	BASELINE_AVERAGE =	4U,
	/** 5: Signal of latest baseline values. */
	BASELINE_SAMPLE =	5U
} EventScopeType;

/**
 * Ethernet protocol type used in #setEthernetProtocol() and #getEthernetProtocol().
 */
typedef enum
{
	/** 1: Transmission control protocol (TCP). */
	TCP =	1U,
	/** 2: User datagram protocol (UDP). */
	UDP =	2U
} EthernetProtocolType;

/**
 * Ethernet speed type used in #setEthernetSpeed() and #getEthernetSpeed().
 */
typedef enum
{
	/** 0: Use Auto-negotiation to determine ethernet speed and duplex mode. */
	AUTO_NEGOTIATION =		0U,
	/** 1: Force ethernet to run at 10Mbit/s and half duplex mode. */
	HALF_DUPLEX_10_MBITS =	1U,
	/** 2: Force ethernet to run at 10Mbit/s and full duplex mode. */
	FULL_DUPLEX_10_MBITS =	2U,
	/** 3: Force ethernet to run at 100Mbit/s and half duplex mode. */
	HALF_DUPLEX_100_MBITS =	3U,
	/** 4: Force ethernet to run at 10Mbit/s and full duplex mode. */
	FULL_DUPLEX_100_MBITS =	4U
} EthernetSpeedType;

/**
 * Trigger duration type used in #calculateEventRate().
 */
typedef enum
{
	/** 0: Count the amount of triggered events within 1s. */
	TRIGGER_DURATION_1_SECOND =		0U,
	/** 1: Count the amount of triggered events within 2s. */
	TRIGGER_DURATION_2_SECONDS =	1U,
	/** 2: Count the amount of triggered events within 4s. */
	TRIGGER_DURATION_4_SECONDS =	2U,
	/** 3: Count the amount of triggered events within 8s. */
	TRIGGER_DURATION_8_SECONDS =	3U,
	/** 4: Count the amount of triggered events within 16s. */
	TRIGGER_DURATION_16_SECONDS =	4U
} TriggerDurationType;

/**
 * DPP firmware version structure used in #getFirmwareVersion().
 */
typedef struct
{
	UInt16Type major;
	UInt16Type minor;
	UInt16Type patch;
	UInt16Type build;
	UInt16Type variant;
} FirmwareVersionType;

/**
 * MCU status structure used in #getMCUStatusInfo().
 */
typedef struct
{
	BooleanType hasPower;
	BooleanType isReady;
	BooleanType isAlmostReady;
} MCUStatusInfoType;

/**
 * MCU-related return codes. Range 0x00 - 0x4F is reserved for MCU and MCU bootloader return codes. Range 0x50-0x7F is reserved for MCU-related VICOLib return codes. Range 0x80 - 0x9F is reserved for UART-passthrough-related DPP return codes.
 */
typedef enum
{
	/** 0x00: MCU return code: Request successfully processed. */
	MCU_SUCCESS =								0x00,
	/** 0x01: MCU return code: Command not supported. */
	MCU_COMMAND_NOT_SUPPORTED =					0x01,
	/** 0x02: MCU return code: Wrong datagram CRC checksum. */
	MCU_WRONG_CRC_CHECKSUM =					0x02,
	/** 0x03: MCU return code: Command length mismatch. */
	MCU_COMMAND_LENGTH_MISMATCH =				0x03,
	/** 0x04: MCU return code: Datagram version not supported. */
	MCU_VERSION_NOT_SUPPORTED =					0x04,

	/** 0x10: MCU return code: Error during command processing. */
	MCU_ERROR =									0x10,

	/** 0x20: MCU return code: For #flashRead(), #flashWriteSessionData(), and #setEEP() Length requirement (len) outside the valid range, for #twi() Buffer sizes (ses/res) outside the valid range, for #getIO(), #setIO(), #getADC(), and #setDAC() Port requirement (por) outside the valid range, for #setIMax() Maximum current (itecMax) outside the valid range, #setUMax() Maximum voltage (utecMax) outside the valid range, for #dbgClp() and #dbgClpExt() control loop not in operation (check system states). */
	MCU_LEN_OUT_OF_VALID_RANGE =				0x20,
	/** 0x21: MCU return code: For #flashRead(), #flashWriteSessionData(), and #setEEP() Start address (addStart) outside the valid range, for #getIO(), #setIO(), #getADC(), and #setDAC() Pin requirement (pin) outside the valid range. */
	MCU_ADDRESS_OUT_OF_VALID_RANGE =			0x21,
	/** 0x22: MCU return code: For #setEEP() System is not in EEA mode, for #setIO() Value requirement (val) outside the valid range. */
	MCU_SYSTEM_IS_NOT_IN_EEA_MODE =				0x22,
	/** 0x23: MCU return code: For #twi() most recent acknowledge bit from slave is NACK. */
	MCU_TWI_SLAVE_NACK =						0x23,

	/** 0x30: MCU bootloader return code: Already in "flash" session, or request not possible because flash write session active. */
	MCU_BL_FLASH_SESSION_ACTIVE =				0x30,
	/** 0x31: MCU bootloader return code: No flash session active. */
	MCU_BL_NO_FLASH_SESSION_ACTIVE =			0x31,
	/** 0x32: MCU bootloader return code: Start address (addStart) out of range. */
	MCU_BL_ADDRESS_OUT_OF_VALID_RANGE =			0x32,
	/** 0x33: MCU bootloader return code: Invalid data length. */
	MCU_BL_LEN_OUT_OF_VALID_RANGE =				0x33,
	/** 0x34: MCU bootloader return code: The data block is not in sequence within the session. */
	MCU_BL_DATA_NOT_IN_SEQUENCE_WITHIN_SESSION =0x34,
	/** 0x35: MCU bootloader return code: Application checksum invalid. */
	MCU_BL_APPLICATION_CHECKSUM_INVALID =		0x35,
	/** 0x36: MCU bootloader return code: Already in application. */
	MCU_BL_ALREADY_IN_APPLICATION =				0x36,

	/** 0x50: VICOLib return code: No device connection with targeted serial number active. Request could not be sent to the device. */
	MCU_NO_DEVICE_WITH_ID_CONNECTED_ERROR =		0x50,
	/** 0x51: VICOLib return code: VICODaemon is currently not running. See \ref API (VICODaemon). Request could not be sent to the device. */
	MCU_VICODAEMON_IS_STOPPED =					0x51,
	/** 0x52: VICOLib return code: Timeout error due to no response from the device. Make sure the device is powered up and connected to your system. Try to find the device using scanning function (#scanUsbDevices()). */
	MCU_VICOLIB_TIMEOUT_ERROR =					0x52,
	/** 0x53: VICOLib return code: Data responded by the device does not fit into given data type. */
	MCU_RESPONSE_OUT_OF_BOUNDS_ERROR =			0x53,
	/** 0x54: VICOLib return code: Given argument(s) not allowed or null. No request was sent to the device. */
	MCU_INVALID_ARGUMENT_ERROR =				0x54,
	/** 0x55: VICOLib return code: Data responded by the device not as expected. */
	MCU_INVALID_RESPONSE_DATA_ERROR =			0x55,

	/** 0x80: DPP passthrough return code: UART timeout error due to no response from the MCU. */
	DPP_UART_TIMEOUT_ERROR =					0x80,
	/** 0x81: DPP passthrough return code: No access to internal memory due to an DPP data handling error. */
	DPP_NO_ACCESS_TO_INTERNAL_MEMORY_ERROR =	0x81,
	/** 0x82: DPP passthrough return code: Incomplete UART request with data and command length mismatch. */
	DPP_INCOMPLETE_UART_COMMAND_ERROR =			0x82,

	/** 0xFF: VICOLib return code: Undefined error. */
	MCU_UNDEFINED_ERROR =						0xFF,
} MCUStatusType;

/**
 * Software package used in #swPkgGetActive().
 */
typedef enum
{
	/** 0x10: Bootloader. */
	Bootloader =	0x10,
	/** 0x20: Application. */
	Application =	0x20,
} SoftwarePackage;


/**
 * Software package used in #blGetSession().
 */
typedef enum
{
	/** 0x01: The session of the bootloader where all datagrams, beside the SESSION_WRITE datagram, are available. */
	Default =	0x01,
	/** 0x02: The session where flashing is active. */
	Flash =		0x02
} BootloaderSessionType;

/**
 * Software package used in #blGetReason().
 */
typedef enum
{
	/** 0x10: Rescue pin active when the MCU started. */
	RescuePinActive =	0x10,
	/** 0x20: Request made by the application. */
	FlashRequest =		0x20,
	/** 0x30: Mismatch between the calculated application checksum and the value written in the application section. */
	AppCrcInvalid =		0x30
} BootloaderReasonType;

/**
 * VICO live info state used in #LiveInfo1VICOType and #LiveInfo2VICOType.
 */
typedef enum
{
	/** 0x00: Initialization. */
	INIT =			0x00,
	/** 0x01: Operation. */
	OPERATION =		0x01,
	/** 0x02: Error. See #LiveInfoVICOErrorType. */
	VICO_ERROR =	0x02,
	/** 0x03: Power saving ECO3. */
	ECO3 =			0x03,
	/** 0x04: EEPROM read/write mode. */
	EEA =			0x04
} LiveInfoVICOStateType;

/**
 * VICO live info error used in #LiveInfo1VICOType and #LiveInfo2VICOType.
 */
typedef enum
{
	/** 0x00: No error. */
	NO_VICO_ERROR =			0x00,
	/** 0x01: Positive voltage out of range (+5V). */
	VOERR_01 =				0x01,
	/** 0x02: Microcontroller voltage out of range (+3V3_MCU). */
	VOERR_02 =				0x02,
	/** 0x03: Reference voltage out of range (+2V5_REF). */
	VOERR_03 =				0x03,
	/** 0x04: Thermistor #1 temperature out of range (upper limit). */
	VOERR_11 =				0x04,
	/** 0x05: Thermistor #2 temperature out of range (upper limit). */
	VOERR_12 =				0x05,
	/** 0x06: Input voltage out of range (V_IN). */
	VOERR_13 =				0x06,
	/** 0x07: Negative high voltage out of range (HV). */
	VOERR_14 =				0x07,
	/** 0xFF: Unknown error. */
	UNKNOWN_VICO_ERROR =	0xFF
} LiveInfoVICOErrorType;

/**
 * VICO liveInfo1 structure used in #liveInfo1VICO().
 */
typedef struct
{
	/** The current system status of the VICO-AV/-DV. */
	LiveInfoVICOStateType st;
	/** The current error code of the VICO-AV/-DV. */
	LiveInfoVICOErrorType er;
	/** The input voltage in V as 32 bit float (Little-endian = low byte first). */
	FloatType vIn;
	/** The current "Power" output state as bool. */
	BooleanType pwr;
	/** The current temperature at thermistor 1 in degrees Celsius as 32 bit float (Little-endian = low byte first). */
	FloatType therm1;
	/** The current temperature at thermistor 2 in degrees Celsius as 32 bit float (Little-endian = low byte first). */
	FloatType therm2;
} LiveInfo1VICOType;

/**
 * VICO liveInfo2 structure used in #liveInfo2VICO().
 */
typedef struct
{
	/** The current system status of the VICO-AV/-DV. */
	LiveInfoVICOStateType st;
	/** The current error code of the VICO-AV/-DV. */
	LiveInfoVICOErrorType er;
	/** The input voltage in V as 32 bit float (Little-endian = low byte first). */
	FloatType vIn;
	/** The +5V in V as 32 bit float. */
	FloatType p5v;
	/** The status of the -5V as boolean. */
	BooleanType n5vActive;
	/** The +3V3 power supply of the MCU in V as 32 bit float. */
	FloatType mcu3v3;
	/** The +2V5 reference voltage in V as 32 bit float. */
	FloatType ref2v5;
	/** The status of the negative high voltage as boolean. */
	BooleanType hvActive;
	/** The DAC set value in mV as 16 bit unsigned short (Little-endian = low byte first). */
	UInt16Type hvDac;
	/** The negative high voltage in V as 32 bit float. */
	FloatType hv;
	/** The current "Power" output state as boolean. */
	BooleanType pwr;
	/** The information, if a USB cable is connected as boolean. */
	BooleanType usb;
	/** The current "MCU general purpose I/O" output state as boolean. */
	BooleanType gpio;
	/** The "request flash bootloader" input state as boolean. */
	BooleanType reqfbl;
	/** The +3V3 power supply of the FPGA in V as 32 bit float. */
	FloatType fpga3v3;
	/** The current temperature at thermistor 1 in degrees Celsius as 32 bit float (Little-endian = low byte first). */
	FloatType therm1;
	/** The current temperature at thermistor 2 in degrees Celsius as 32 bit float (Little-endian = low byte first). */
	FloatType therm2;
} LiveInfo2VICOType;

/**
 * VICO liveInfoBoundaries structure used in #liveInfoBoundariesVICO().
 */
typedef struct
{
	/** The lower boundary of the input voltage in V as 32 bit float. */
	FloatType vInMin;
	/** The upper boundary of the input voltage in V as 32 bit float . */
	FloatType vInMax;
	/** The lower boundary of the +5V in V as 32 bit float. */
	FloatType p5vMin;
	/** The upper boundary of the +5V in V as 32 bit float. */
	FloatType p5vMax;
	/** The lower boundary of the +3V3 power supply of the MCU in V as 32 bit float. */
	FloatType mcu3v3Min;
	/** The upper boundary of the +3V3 power supply of the MCU in V as 32 bit float. */
	FloatType mcu3v3Max;
	/** The lower boundary of the +2V5 reference voltage in V as 32 bit float. */
	FloatType ref2v5Min;
	/** The upper boundary of the +2V5 reference voltage in V as 32 bit float. */
	FloatType ref2v5Max;
	/** The lower boundary of the negative high voltage in V as 32 bit float. */
	FloatType hvMin;
	/** The upper boundary of the negative high voltage in V as 32 bit float. */
	FloatType hvMax;
	/** The upper boundary of the thermistor temperature in degrees Celsius as 32 bit float. */
	FloatType therm1Max;
	/** The upper boundary of the thermistor temperature in degrees Celsius as 32 bit float. */
	FloatType therm2Max;
} LiveInfoBoundariesVICOType;

/**
 * VIAMP live info used in #LiveInfo1VIAMPType and #LiveInfo2VIAMPType.
 */
typedef enum
{
	/** 0x00: Inactive. */
	INACTIVE =				0x00,
	/** 0x01: Enabling -5V voltage. */
	EN_VOLTAGE =			0x01,
	/** 0x02: Recognizing SDD thermistor. */
	CHECK_CONN_TEMP =		0x02,
	/** 0x03: Testing I2C connection. */
	CHECK_CONN_I2C =		0x03,
	/** 0x04: VIAMP not connected or connection failed. */
	DISCONNECTED =			0x04,
	/** 0x05: Checking the EEPROM CRC checksum. */
	VALIDATE_EEPCONTENT =	0x05,
	/** 0x06: EEPROM CRC checksum not valid or invalid VIAMP thermistor mode (linearization not supported). */
	NO_OPERATION =			0x06,
	/** 0x07: Enabling high voltage. */
	ENABLE_HV =				0x07,
	/** 0x08: Error. See #LiveInfoVIAMPErrorType. */
	VIAMP_ERROR =			0x08,
	/** 0x09: Initializing Peltier and checking the ring voltages. */
	PREPARE_OPERATION =		0x09,
	/** 0x0A: VIAMP ready for operation. */
	OP_READY =				0x0A,
	/** 0x0B: ECO1 operation mode active. */
	OP_ECO1 =				0x0B,
	/** 0x0C: FULL operation mode active. */
	OP_FULL =				0x0C,
	/** 0x0D: High voltage disabled. */
	DISABLE_HV =			0x0D,
	/** 0x0E: ECO2 operation mode active. */
	OP_ECO2 =				0x0E

} LiveInfoVIAMPStateType;

/**
 * VIAMP live info error used in #LiveInfo1VIAMPType and #LiveInfo2VIAMPType.
 */
typedef enum
{
	/** 0x00: No error. */
	NO_VIAMP_ERROR =			0x00,
	/** 0x01: No connection to VIAMP over thermistor. */
	VPERR_01 =					0x01,
	/** 0x02: No connection to VIAMP over I2C. */
	VPERR_02 =					0x02,
	/** 0x03: EEPROM CRC checksum not valid. */
	VPERR_03 =					0x03,
	/** 0x04: Thermistor is set to linearization (not supported). */
	VPERR_04 =					0x04,
	/** 0x05: Unstable high voltage. */
	VPERR_05 =					0x05,
	/** 0x05: SDD ring voltages invalid. */
	VPERR_06 =					0x06,
	/** 0xFF: Unknown error. */
	UNKNOWN_VIAMP_ERROR =		0xFF
} LiveInfoVIAMPErrorType;

/**
 * VIAMP liveInfo1 structure used in #liveInfo1VIAMP().
 */
typedef struct
{
	/** The current system status of the VICO-AV/-DV. */
	LiveInfoVIAMPStateType st;
	/** The current error code of the VICO-AV/-DV. */
	LiveInfoVIAMPErrorType er;
	/** The peltier output current as 32 bit float in ampere (Little-endian = low byte first). */
	FloatType itec;
	/** The peltier output voltage as 32 bit float in volts (Little-endian = low byte first). */
	FloatType utec;
	/** The SDD temperature as 32 bit float in degrees Celsius (Little-endian = low byte first) . */
	FloatType sddTmp;
	/** The current "Ready" state as boolean. */
	BooleanType rdy;
	/** The TEC hot side temperature in degrees Celsius as 32 bit float (Little-endian = low byte first) . */
	FloatType hotSide;
} LiveInfo1VIAMPType;

/**
 * VIAMP liveInfo2 structure used in #liveInfo2VIAMP().
 */
typedef struct
{
	/** The current system status of the VICO-AV/-DV. */
	LiveInfoVIAMPStateType st;
	/** The current error code of the VICO-AV/-DV. */
	LiveInfoVIAMPErrorType er;
	/** The ADC value in V as 32 bit float. */
	FloatType viampAdc;
	/** The Ring1 voltage in V as 32 bit float. */
	FloatType r1;
	/** The Back voltage in V as 32 bit float. */
	FloatType bk;
	/** The RingX voltage in V as 32 bit float. */
	FloatType rx;
	/** The peltier output current as 32 bit float in ampere. */
	FloatType itec;
	/** The peltier output voltage as 32 bit float in volts. */
	FloatType utec;
	/** The SDD temperature as 32 bit float in degrees Celsius. */
	FloatType sddTmp;
	/** (Target temperature, not TARGET_TMP_EEP (EEPROM)) contains the current target SDD temperature as 32 bit float. */
	FloatType targetTmp;
	/** The current "Ready" state as boolean. */
	BooleanType rdy;
	/** The current "Almost Ready" state as boolean. */
	BooleanType ardy;
	/** The TEC hot side temperature in degrees Celsius as 32 bit float. */
	FloatType hotSide;
	/** The final limited control variable as float32. */
	FloatType monSigFinal;
	/** The calculated control variable as float32. */
	FloatType ctrlSigFinal;
	/** The information, if the integral part is limited as boolean. */
	BooleanType iPartLimit;
	/** The active status of the peltier cooler as boolean. */
	BooleanType tecActive;
	/** The DAC set value in mV as 16 bit unsigned short (Little-endian = low byte first). */
	UInt16Type tecDac;
	/** P part. */
	FloatType pPart;
	/** I part. */
	FloatType iPart;
	/** D part. */
	FloatType dPart;
} LiveInfo2VIAMPType;

/**
 * VIAMP liveInfoBoundaries structure used in #liveInfoBoundariesVIAMP().
 */
typedef struct
{
	/** The lower boundary of the ADC in V as 32 bit float. */
	FloatType viampAdcMin;
	/** The upper boundary of the ADC in V as 32 bit float. */
	FloatType viampAdcMax;
	/** The lower boundary of the Ring1 voltage in V as 32 bit float. */
	FloatType r1Min;
	/** The upper boundary of the Ring1 voltage in V as 32 bit float. */
	FloatType r1Max;
	/** The lower boundary of the Back voltage in V as 32 bit float. */
	FloatType bkMin;
	/** The upper boundary of the Back voltage in V as 32 bit float. */
	FloatType bkMax;
	/** The lower boundary of the RingX voltage in V as 32 bit float. */
	FloatType rxMin;
	/** The upper boundary of the RingX voltage in V as 32 bit float. */
	FloatType rxMax;
	/** The maximum TEC current in A as 32 bit float. */
	FloatType itecMax;
	/** The maximum TEC voltage in V as 32 bit float. */
	FloatType utecMax;
	/** The weight of the PID-factor as float32. */
	FloatType kp;
	/** The weight of the PID-factor as float32. */
	FloatType ki;
	/** The weight of the PID-factor as float32. */
	FloatType kd;
} LiveInfoBoundariesVIAMPType;

/**
 * VICO DevInfo1 structure used in #devInfo1VICO().
 */
typedef struct
{
	/** The software-major version number of the MCU firmware. */
	UInt8Type smj;
	/** The software-minor version number of the MCU firmware. */
	UInt8Type smi;
	/** The software-sub version number of the MCU firmware. */
	UInt8Type sms;
	/** The software-build version number of the MCU firmware. */
	UInt16Type smb;
} DevInfo1VICOType;

/**
 * VICO DevInfo1 bootloader structure used in #devInfo1Bootloader().
 */
typedef struct
{
	/** The software-major version number of the MCU bootloader. */
	UInt8Type smj;
	/** The software-minor version number of the MCU bootloader. */
	UInt8Type smi;
	/** The software-sub version number of the MCU bootloader. */
	UInt8Type sms;
	/** The software-build version number of the MCU bootloader. */
	UInt16Type smb;
} DevInfo1BootloaderType;

/**
 * Mode used in #setMode().
 */
typedef enum
{
	/** 0x00: No request. */
	NO_REQUEST =	0x00,
	/** 0x01: Normal operation. */
	FULL_MODE =		0x01,
	/** 0x02: Power saving ECO1: SDD chip temperature set to 0°C (same as setting the chip temperature manually). */
	ECO1_MODE =		0x02,
	/** 0x03: Power saving ECO2: Peltier/TEC off. */
	ECO2_MODE =		0x03,
	/** 0x04: Power saving ECO3: VIAMP -5V off, high voltage off, Peltier off (maximum power saving but the longest recovery time to FULL operation mode). */
	ECO3_MODE =		0x04,
	/** 0x05: EEPROM read/write mode, no TEC control. */
	EEA_MODE =		0x05
} ModeType;

/**
 * TWI mode used in #twi().
 */
typedef enum
{
	/** 0x00: TWI write mode. */
	TWI_WRITE =			0x00,
	/** 0x01: TWI read mode. */
	TWI_READ =			0x01,
	/** 0x02: TWI write/read mode. */
	TWI_WRITE_READ =	0x02
} TWIModeType;

/**
 * Temperature structure used in #getTemp().
 */
typedef struct
{
	/** The current SDD temperature as 32 bit float (Little-endian = low byte first). */
	FloatType sddTmp;
	/** The currently set target temperature as 32 bit float (Little-endian = low byte first). */
	FloatType targetTmp;
	/** The current "Ready" state as boolean. */
	BooleanType rdy;
	/** The current "Almost Ready" state as boolean. */
	BooleanType ardy;
} TempType;

/**
 * Port used in #getIO(), #setIO(), #getADC(), #setDAC().
 */
typedef enum
{
	/** 0x00: Port A. */
	PORT_A =	0x00,
	/** 0x01: Port B. */
	PORT_B =	0x01,
	/** 0x02: Port C. */
	PORT_C =	0x02,
	/** 0x03: Port D. */
	PORT_D =	0x03,
	/** 0x04: Port E. */
	PORT_E =	0x04,
	/** 0x05: Port F. */
	PORT_F =	0x05,
	/** 0x06: Port G. */
	PORT_G =	0x06,
	/** 0x07: Port H. */
	PORT_H =	0x07,
	/** 0x08: Port J. */
	PORT_J =	0x08,
	/** 0x09: Port K. */
	PORT_K =	 0x09,
	/** 0x0A: Port L. */
	PORT_L =	 0x0A,
	/** 0x0B: Port M. */
	PORT_M =	 0x0B,
	/** 0x0C: Port N. */
	PORT_N =	0x0C,
	/** 0x0D: Port P. */
	PORT_P =	0x0D,
	/** 0x0E: Port Q. */
	PORT_Q =	0x0E,
	/** 0x0F: Port R. */
	PORT_R =	0x0F
} PortType;

/**
 * Debug control loop structure used in #dbgClp().
 */
typedef struct
{
	/** Number incrementing by each control step as unsigned int32. */
	UInt32Type stepCounter;
	/** The SDD temperature as 32 bit float in degrees Celsius. */
	FloatType sddTmp;
	/** The peltier output current as 32 bit float in ampere. */
	FloatType itec;
	/** The peltier output voltage as 32 bit float in volts. */
	FloatType utec;
	/** The final limited control variable. */
	FloatType monSigFinal;
	/** P part. */
	FloatType pPart;
	/** I part. */
	FloatType iPart;
	/** The current "Ready" state as boolean. */
	BooleanType rdy;
} DbgClpType;

/**
 * Extended debug control loop structure used in #dbgClpExt().
 */
typedef struct
{
	/** Number incrementing by each control step. */
	UInt32Type stepCounter;
	/** Target temperature in degrees. */
	FloatType targetTmp;
	/** The SDD temperature. */
	FloatType sddTmp;
	/** The peltier output current. */
	FloatType itec;
	/** The peltier output voltage. */
	FloatType utec;
	/** Step size. */
	FloatType monStepSize;
	/** Fhe final limited control variable. */
	FloatType monSigFinal;
	/** The calculated control variable. */
	FloatType ctrlSigFinal;
	/** P part. */
	FloatType pPart;
	/** I part. */
	FloatType iPart;
	/** The information, if the integral part is limited. */
	BooleanType iPartLimit;
	/** D part. */
	FloatType dPart;
	/** The current "Ready" state. */
	BooleanType rdy;
	/** The current "Almost Ready" state. */
	BooleanType aRdy;
	/** Green LED. */
	BooleanType grnLed;
	/** The TEC hot side temperature in degrees Celsius. */
	FloatType hotSide;
} DbgClpExtType;

#endif // TYPES_H
