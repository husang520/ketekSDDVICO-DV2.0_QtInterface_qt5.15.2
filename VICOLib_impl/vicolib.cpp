#include "vicolib.h"
#include "vicolibglobal.h"
#include "vicolib.h"
#include "vicoquery.h"
#include "constants.h"
#include <QHostAddress>

#define VERSION "1.1.0.0"

/* IPv4 address regex */
QRegExp macRegex("^([0-9A-Fa-f]{2}[:-]){5}([0-9A-Fa-f]{2})|([0-9a-fA-F]{4}\\.[0-9a-fA-F]{4}\\.[0-9a-fA-F]{4})$");
/* MAC address regex */
QRegExp ipv4Regex("^(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$");

FloatType QUANTIFIER_12_5_NS = 12.5;
UInt8Type QUANTIFIER_10_0_US = 10;

void isIPv4Address(const char* ipAddress, bool* isValid) {
	*isValid = ipv4Regex.exactMatch(ipAddress);
}

void isMACAddress(const char* macAddress, bool* isValid) {
	*isValid = macRegex.exactMatch(macAddress);
}

MCUStatusType convertBytesToString(CharType* charVal, int arraySize, QVariantMap pairMap, int from, int to)
{
	// plus one because of starting from 0
	int requestedSize = to-from +1 ;
	if (requestedSize != arraySize) {
		return MCU_INVALID_ARGUMENT_ERROR;
	}
	QByteArray str;
	for (int i=from; i<=to; i++) {
		QString data = "data"+QString::number(i);
		str.append(pairMap.value(data).toUInt());
	}
	char *strData = str.data();
	memcpy(charVal, "", arraySize);
	strncpy(charVal, strData, str.length());
	return MCU_SUCCESS;
}

MCUStatusType convertBytesToFloat(FloatType* floatVal, UInt8Type b3, UInt8Type b2, UInt8Type b1, UInt8Type b0)
{
	uchar b[] = {b3, b2, b1, b0};
	memcpy(floatVal, &b, sizeof(*floatVal));
	return MCU_SUCCESS;
}

MCUStatusType convertBytesToUInt32(UInt32Type* uint32Type, UInt8Type b3, UInt8Type b2, UInt8Type b1, UInt8Type b0)
{
	uchar b[] = {b3, b2, b1, b0};
	memcpy(uint32Type, &b, sizeof(*uint32Type));
	return MCU_SUCCESS;
}

MCUStatusType convertBytesToUInt16(UInt16Type* uint16Type, UInt8Type b1, UInt8Type b0)
{
	uchar b[] = {b1, b0};
	memcpy(uint16Type, &b, sizeof(*uint16Type));
	return MCU_SUCCESS;
}

MCUStatusType convertByteToBoolean(BooleanType* booleanVal, UInt8Type b1)
{
	if (b1 == 1) {
		*booleanVal = true;
		return MCU_SUCCESS;
	}
	else if(b1 == 0) {
		*booleanVal = false;
		return MCU_SUCCESS;
	}
	else {
		return MCU_INVALID_ARGUMENT_ERROR;
	}
}

DPPStatusType convertByteToInt32(UInt8Type* byteArray, UInt32Type* intArray, UInt16Type numberOfBins, UInt8Type bytesPerBin)
{
	/* If bytesPerBin out of range then quit */
	if ((bytesPerBin<1) || (bytesPerBin>3))
		return DPP_INVALID_ARGUMENT_ERROR;
	/* If numberOfBins invalid then quit */
	if (((numberOfBins<512) || (numberOfBins>8192)) && numberOfBins%512 != 0)
		return DPP_INVALID_ARGUMENT_ERROR;

	switch(bytesPerBin)
	{
		case 1:
			for (int i=0; i<numberOfBins; i++)
			{
				intArray[i] = (UInt32Type)(byteArray[i]);
			}
			break;
		case 2:
			for (int i=0, j=0; i<numberOfBins; i++, j=i*bytesPerBin)
			{
				intArray[i] = (UInt32Type)(byteArray[j] | byteArray[j+1]<<8);
			}
			break;
		case 3:
			for (int i=0, j=0; i<numberOfBins; i++, j=i*bytesPerBin)
			{
				intArray[i] = (UInt32Type)(byteArray[j] | byteArray[j+1]<<8 | byteArray[j+2]<<16);
			}
			break;
	}
	return DPP_SUCCESS;
}

DPPStatusType getRC(QJsonObject data) {
	quint8 status;
	status =(DPPStatusType)data.value(API_STATUSTYPE).toInt();
	return (DPPStatusType) status;
}

VICOStatusType getLibRC(QJsonObject data) {
	quint8 status;
	status =(VICOStatusType)data.value(API_STATUSTYPE).toInt();
	return (VICOStatusType) status;
}

MCUStatusType getMcuRC(QJsonObject data) {
	quint8 status;
	status =(MCUStatusType)data.value(API_STATUSTYPE).toInt();
	return (MCUStatusType) status;
}

UInt16Type getData(QJsonObject majorVersionType) {
	return (UInt16Type)majorVersionType.value(API_DATA).toInt();
}

uint64_t getDeviceIdentifierfromString(const CharType* deviceStr) {
	bool bStatusType = false;
	if (deviceStr)
	{
		QString device = QString(deviceStr);
		uint64_t nHex = device.toULongLong(&bStatusType,16);
		return nHex;
	}
	else
	{
		return -1;
	}

}

VICOStatusType getLibraryVersion(VersionType* libraryVersion)
{
    QStringList versions = QStringLiteral(VERSION).split(".");
	if (versions.size() != 4) {
		return VICO_UNDEFINED_ERROR;
	}
	libraryVersion->major = versions.at(0).toInt();
	libraryVersion->minor = versions.at(1).toInt();
	libraryVersion->patch = versions.at(2).toInt();
	libraryVersion->build = versions.at(3).toInt();
	return VICO_SUCCESS;
}

VICOStatusType getDaemonVersion(VersionType* daemonVersion)
{
	VicoQuery query;
	QJsonObject reply = query.execute(API_INTERNAL_DAEMONVERSION);
	if (getLibRC(reply) != VICO_SUCCESS) {
		return getLibRC(reply);
	}
	QString version = reply.value(API_DATA).toString();
	QStringList versions = version.split(".");
	if (versions.size() != 4) {
		return VICO_UNDEFINED_ERROR;
	}
	daemonVersion->major = versions.at(0).toInt();
	daemonVersion->minor = versions.at(1).toInt();
	daemonVersion->patch = versions.at(2).toInt();
	daemonVersion->build = versions.at(3).toInt();
	return getLibRC(reply);
}

VICOStatusType scanTcpDevices(const CharType* fromIpAddress, const CharType* toIpAddress)
{
	if (! fromIpAddress)
	{
		return VICO_INVALID_ARGUMENT_ERROR;
	}
	if (! toIpAddress)
	{
		return VICO_INVALID_ARGUMENT_ERROR;
	}

	bool isIpv4 = false;
	isIPv4Address(fromIpAddress, &isIpv4);
	if (! isIpv4)
	{
		return VICO_INVALID_ARGUMENT_ERROR;
	}

	isIPv4Address(toIpAddress, &isIpv4);
	if (! isIpv4)
	{
		return VICO_INVALID_ARGUMENT_ERROR;
	}

	VicoQuery query;
	QJsonObject reply = query.execute(API_INTERNAL_SCANTCP, fromIpAddress, toIpAddress);
	return getLibRC(reply);
}

VICOStatusType cancelTcpScan(){
	VicoQuery query;
	QJsonObject reply = query.execute(API_INTERNAL_STOPTCP);
	return getLibRC(reply);
}

VICOStatusType scanUdpDevices(const CharType* netaddress, const UInt8Type netmask) {
	if (! netaddress)
	{
		return VICO_INVALID_ARGUMENT_ERROR;
	}

	bool isIpv4 = false;
	isIPv4Address(netaddress, &isIpv4);
	if (! isIpv4)
	{
		return VICO_INVALID_ARGUMENT_ERROR;
	}

	VicoQuery query;
	QJsonObject reply = query.execute(API_INTERNAL_SCANUDP, netaddress, netmask);
	return getLibRC(reply);
}

VICOStatusType cancelUdpScan(){
	VicoQuery query;
	QJsonObject reply = query.execute(API_INTERNAL_STOPUDP);
	return getLibRC(reply);
}

VICOStatusType scanUsbDevices() {
	VicoQuery query;
	QJsonObject scanUsbReply = query.execute(API_INTERNAL_SCANUSB);
	QJsonObject scanUsbHidReply = query.execute(API_INTERNAL_SCANUSBHID);
	return getLibRC(scanUsbHidReply);
}

VICOStatusType getNumberOfDevices(UInt8Type* numberOfDevices) {
	if (! numberOfDevices)
	{
		return VICO_INVALID_ARGUMENT_ERROR;
	}

	VicoQuery query;
	QJsonObject reply = query.execute(API_INTERNAL_GETNUMBERDEVICES);
	if (VICO_SUCCESS != getLibRC(reply)) {
		return getLibRC(reply);
	}
	*numberOfDevices = reply.value(API_DATA).toInt();
	return getLibRC(reply);
}

VICOStatusType getPreferredInterface(const CharType* serialNumber, InterfaceType* deviceInterface) {
	if (! serialNumber)
	{
		return VICO_INVALID_ARGUMENT_ERROR;
	}
	if (! deviceInterface)
	{
		return VICO_INVALID_ARGUMENT_ERROR;
	}

	VicoQuery query;
	QJsonObject reply = query.execute(API_INTERNAL_GET_PREFERRED_INTERFACE, quint64(getDeviceIdentifierfromString(serialNumber)));
	if (VICO_SUCCESS != getLibRC(reply)) {
		return getLibRC(reply);
	}
	*deviceInterface = (InterfaceType) reply.value(API_DATA).toInt();
	return getLibRC(reply);
}

VICOStatusType setPreferredInterface(const CharType* serialNumber, InterfaceType deviceInterface) {
	if (! serialNumber)
	{
		return VICO_INVALID_ARGUMENT_ERROR;
	}
	VicoQuery query;
	QJsonObject reply = query.execute(API_INTERNAL_SET_PREFERRED_INTERFACE, getDeviceIdentifierfromString(serialNumber), quint8(deviceInterface));
	return getLibRC(reply);
}

VICOStatusType getDeviceInfoByIndex(const UInt8Type index, const UInt8Type serialNumberSize, CharType* serialNumber, InterfaceType* deviceInterface)
{
	if (! serialNumber)
	{
		return VICO_INVALID_ARGUMENT_ERROR;
	}
	if (! deviceInterface)
	{
		return VICO_INVALID_ARGUMENT_ERROR;
	}

	VicoQuery query;
	QJsonObject reply = query.execute(API_INTERNAL_GETDEVICEINFOBYINDEX, index);
	if (VICO_SUCCESS != getLibRC(reply)) {
		return getLibRC(reply);
	}
	QJsonArray deviceInfosJ = reply.value(API_DATA).toArray();
	QString serialNumberStr = deviceInfosJ.at(0).toString();
	quint32 devInterface = deviceInfosJ.at(1).toInt();

	std::string conAddrStr = serialNumberStr.toStdString();
	const char *conAddrSrc = conAddrStr.data();
	if (serialNumberSize >= conAddrStr.size()) {
		memcpy(serialNumber, "", serialNumberSize);
		// +1 to add terminating null character
		strncpy(serialNumber, conAddrSrc, conAddrStr.size()+1);
		*deviceInterface =(InterfaceType) devInterface;
		return getLibRC(reply);
	}
	else {
		return VICO_RESPONSE_OUT_OF_BOUNDS_ERROR;
	}
}

VICOStatusType refreshDeviceConnections() {
	VicoQuery query;
	QJsonObject reply = query.execute(API_INTERNAL_REFRESHDEVICECONNECTIONS);
	return getLibRC(reply);
}


/* Start Run Control API */

DPPStatusType startRun(const CharType* serialNumber)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	VicoQuery query;
	// Use data value 0 to delete existing MCA data
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 0, WRITE, 0);
	return getRC(answer);
}

DPPStatusType resumeRun(const CharType* serialNumber)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	VicoQuery query;
	// Use data value 1 to resume existing MCA data
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 0, WRITE, 1);
	return getRC(answer);
}

DPPStatusType stopRun(const CharType* serialNumber)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	VicoQuery query;
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 1, WRITE, 0);
	return getRC(answer);
}

DPPStatusType setStopCondition(const CharType* serialNumber, StopConditionType stopConditionType, DoubleType* stopConditionValue)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	if (*stopConditionValue < 0) {
		return DPP_INVALID_ARGUMENT_ERROR;
	}

	UInt32Type dppValue = 0;
	if (stopConditionType == STOP_AT_FIXED_INPUT_COUNTS || stopConditionType == STOP_AT_FIXED_OUTPUT_COUNTS || stopConditionType == NONE) {
		if(*stopConditionValue < 0.0 || *stopConditionValue > DoubleType(ULONG_MAX)) {
			*stopConditionValue = UInt32Type(ULONG_MAX);
			return DPP_VICOLIB_OUT_OF_RANGE_ERROR;
		} else {
			dppValue = (unsigned int) *stopConditionValue;
		}
	}
	// Time quantification
	else if (stopConditionType == STOP_AT_FIXED_LIVETIME || stopConditionType == STOP_AT_FIXED_REALTIME) {
		// Only calculate the dppValue if we can stay in range
		if (*stopConditionValue >= 0 && *stopConditionValue <= 42949.67295) {
			dppValue = *stopConditionValue * 100000;
		}
		else {
			*stopConditionValue = 42949.67295;
			return DPP_VICOLIB_OUT_OF_RANGE_ERROR;
		}
	} else {
		return DPP_INVALID_ARGUMENT_ERROR;
	}

	quint16 byte0And1 = dppValue;
	quint16 byte2And3 = dppValue >> 16;

	// Ready to set all the valid values
	// Starting with the StopConditionType
	VicoQuery query;
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 2, WRITE, stopConditionType);
	if (DPP_SUCCESS != getRC(answer)) {
		return getRC(answer);
	}
	// Setting stopcondition value
	QJsonObject answer0And1 = query.execute(getDeviceIdentifierfromString(serialNumber), 3, WRITE, byte0And1);
	if (DPP_SUCCESS != getRC(answer0And1)) {
		return getRC(answer0And1);
	}
	QJsonObject answer2And3 = query.execute(getDeviceIdentifierfromString(serialNumber), 4, WRITE, byte2And3);
	if (DPP_SUCCESS != getRC(answer2And3)) {
		return getRC(answer2And3);
	}
	return getRC(answer);
}

DPPStatusType getStopCondition(const CharType* serialNumber, StopConditionType* stopConditionType, DoubleType* stopConditionValue)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	if (! stopConditionType)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	if (! stopConditionValue)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	VicoQuery query;
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 2, READ, 0);
	if (DPP_SUCCESS != getRC(answer)) {
		return getRC(answer);
	}
	*stopConditionType = (StopConditionType) answer.value(API_DATA).toInt();


	QJsonObject answer0And1 = query.execute(getDeviceIdentifierfromString(serialNumber), 3, READ, 0);
	if (DPP_SUCCESS != getRC(answer0And1)) {
		return getRC(answer0And1);
	}
	QJsonObject answer2And3 = query.execute(getDeviceIdentifierfromString(serialNumber), 4, READ, 0);
	if (DPP_SUCCESS != getRC(answer2And3)) {
		return getRC(answer2And3);
	}

	quint16 answer0And1AsInt = answer0And1.value(API_DATA).toInt();
	quint16 answer2And3AsInt = answer2And3.value(API_DATA).toInt();
	quint32 dppValue = answer2And3AsInt << 16 | answer0And1AsInt;
	*stopConditionValue = dppValue;
	// Time quantification
	if (*stopConditionType == STOP_AT_FIXED_LIVETIME || *stopConditionType == STOP_AT_FIXED_REALTIME) {
		*stopConditionValue = dppValue / 100000.0;
	}

	return getRC(answer);
}

DPPStatusType getRunStatus(const CharType* serialNumber, BooleanType* isRunActive)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	if (! isRunActive)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	VicoQuery query;
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 5, READ, 0);
	if (DPP_SUCCESS != getRC(answer)) {
		return getRC(answer);
	}
	if (answer.value(API_DATA).toInt() == 1) {
		*isRunActive = true;
	}
	else if (answer.value(API_DATA).toInt() == 0) {
		 *isRunActive = false;
	}
	else {
		// Response data couldn't be processed properly
		return DPP_INVALID_RESPONSE_DATA_ERROR;
	}
	return getRC(answer);
}

DPPStatusType getRunRealtime(const CharType* serialNumber, DoubleType* realtime)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	if (! realtime)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	VicoQuery query;
	QJsonObject answer0And1 = query.execute(getDeviceIdentifierfromString(serialNumber), 6, READ, 0);
	if (DPP_SUCCESS != getRC(answer0And1)) {
		return getRC(answer0And1);
	}
	QJsonObject answer2And3 = query.execute(getDeviceIdentifierfromString(serialNumber), 7, READ, 0);
	if (DPP_SUCCESS != getRC(answer2And3)) {
		return getRC(answer2And3);
	}

	quint32 answer0And1AsInt = answer0And1.value(API_DATA).toInt();
	quint32 answer2And3AsInt = answer2And3.value(API_DATA).toInt();
	quint64 dppValue = answer2And3AsInt << 16 | answer0And1AsInt;

	// Quantification
	*realtime = dppValue / 100000.0;

	return DPP_SUCCESS;
}

DPPStatusType getRunLivetime(const CharType* serialNumber, DoubleType* livetime)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	if (! livetime)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	VicoQuery query;
	QJsonObject answer0And1 = query.execute(getDeviceIdentifierfromString(serialNumber), 8, READ, 0);
	if (DPP_SUCCESS != getRC(answer0And1)) {
		return getRC(answer0And1);
	}
	QJsonObject answer2And3 = query.execute(getDeviceIdentifierfromString(serialNumber), 9, READ, 0);
	if (DPP_SUCCESS != getRC(answer2And3)) {
		return getRC(answer2And3);
	}

	quint32 answer0And1AsInt = answer0And1.value(API_DATA).toInt();
	quint32 answer2And3AsInt = answer2And3.value(API_DATA).toInt();
	quint64 dppValue = answer2And3AsInt << 16 | answer0And1AsInt;
	*livetime = dppValue / 100000.0;

	return DPP_SUCCESS;
}

DPPStatusType getRunOutputCounts(const CharType* serialNumber, UInt32Type* outputCounts)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	if (! outputCounts)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	VicoQuery query;
	QJsonObject answer0And1 = query.execute(getDeviceIdentifierfromString(serialNumber), 10, READ, 0);
	if (DPP_SUCCESS != getRC(answer0And1)) {
		return getRC(answer0And1);
	}
	QJsonObject answer2And3 = query.execute(getDeviceIdentifierfromString(serialNumber), 11, READ, 0);
	if (DPP_SUCCESS != getRC(answer2And3)) {
		return getRC(answer2And3);
	}
	quint16 answer0And1AsInt = answer0And1.value(API_DATA).toInt();
	quint16 answer2And3AsInt = answer2And3.value(API_DATA).toInt();
	quint32 rr = answer2And3AsInt << 16 | answer0And1AsInt;
	*outputCounts = rr;
	return DPP_SUCCESS;
}

DPPStatusType getRunInputCounts(const CharType* serialNumber, UInt32Type* inputCounts)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	if (! inputCounts)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	VicoQuery query;
	QJsonObject answer0And1 = query.execute(getDeviceIdentifierfromString(serialNumber), 12, READ, 0);
	if (DPP_SUCCESS != getRC(answer0And1)) {
		return getRC(answer0And1);
	}
	QJsonObject answer2And3 = query.execute(getDeviceIdentifierfromString(serialNumber), 13, READ, 0);
	if (DPP_SUCCESS != getRC(answer2And3)) {
		return getRC(answer2And3);
	}
	quint16 answer0And1AsInt = answer0And1.value(API_DATA).toInt();
	quint16 answer2And3AsInt = answer2And3.value(API_DATA).toInt();
	quint32 rr = answer2And3AsInt << 16 | answer0And1AsInt;
	*inputCounts = rr;
	return DPP_SUCCESS;
}

DPPStatusType getRunOutputCountRate(const CharType* serialNumber, UInt32Type* outputCountRate)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	if (! outputCountRate)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	VicoQuery query;
	QJsonObject answer0And1 = query.execute(getDeviceIdentifierfromString(serialNumber), 14, READ, 0);
	if (DPP_SUCCESS != getRC(answer0And1)) {
		return getRC(answer0And1);
	}
	QJsonObject answer2And3 = query.execute(getDeviceIdentifierfromString(serialNumber), 15, READ, 0);
	if (DPP_SUCCESS != getRC(answer2And3)) {
		return getRC(answer2And3);
	}
	quint16 answer0And1AsInt = answer0And1.value(API_DATA).toInt();
	quint16 answer2And3AsInt = answer2And3.value(API_DATA).toInt();
	quint32 rr = answer2And3AsInt << 16 | answer0And1AsInt;
	*outputCountRate = rr;
	return DPP_SUCCESS;
}

DPPStatusType getRunInputCountRate(const CharType* serialNumber, UInt32Type* inputCountRate)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	if (! inputCountRate)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	VicoQuery query;
	QJsonObject answer0And1 = query.execute(getDeviceIdentifierfromString(serialNumber), 16, READ, 0);
	if (DPP_SUCCESS != getRC(answer0And1)) {
		return getRC(answer0And1);
	}
	QJsonObject answer2And3 = query.execute(getDeviceIdentifierfromString(serialNumber), 17, READ, 0);
	if (DPP_SUCCESS != getRC(answer2And3)) {
		return getRC(answer2And3);
	}
	quint16 answer0And1AsInt = answer0And1.value(API_DATA).toInt();
	quint16 answer2And3AsInt = answer2And3.value(API_DATA).toInt();
	quint32 rr = answer2And3AsInt << 16 | answer0And1AsInt;
	*inputCountRate = rr;
	return DPP_SUCCESS;
}

DPPStatusType getRunStatistics(const CharType* serialNumber, RunStatisticsType* runStatistics)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	if (! runStatistics)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	VicoQuery query;
	UInt8Type runStatisticsSize = 52;
	QJsonObject runStatisticsData = query.execute(getDeviceIdentifierfromString(serialNumber), 18, READ, (quint16) 0, (quint16) runStatisticsSize);
	if (DPP_SUCCESS != getRC(runStatisticsData)) {
		return getRC(runStatisticsData);
	}
	QJsonArray data = runStatisticsData.value(API_DATA).toArray();
	QJsonValue pairs = data.at(0);
	QVariantMap pairMap = pairs.toObject().toVariantMap();

	// First handle return codes that aren't a success
	DPPStatusType rc = (DPPStatusType) pairMap.value("data1").toUInt();
	if (DPP_SUCCESS != rc) {
		return (DPPStatusType) rc;
	}
	// Second check if the amount of data matches
	else if(pairMap.size() != runStatisticsSize) {
		return DPPStatusType::DPP_RESPONSE_OUT_OF_BOUNDS_ERROR;
	}
	// Process the data
	else {
		// Process boolean isActive individually
		quint8 b1 = pairMap.value("data3").toUInt();
		if (b1 == 1) {
			runStatistics->isRunActive = true;
		}
		else if(b1 == 0) {
			runStatistics->isRunActive = false;
		}
		else {
			return DPP_INVALID_RESPONSE_DATA_ERROR;
		}

		quint32 retRealTime;
		convertBytesToUInt32(&retRealTime, pairMap.value("data7").toUInt(), pairMap.value("data6").toUInt(), pairMap.value("data11").toUInt(), pairMap.value("data10").toUInt());
		// Quantification
		runStatistics->realTime = (retRealTime / 100000.0);

		quint32 retLiveTime;
		convertBytesToUInt32(&retLiveTime, pairMap.value("data15").toUInt(), pairMap.value("data14").toUInt(), pairMap.value("data19").toUInt(), pairMap.value("data18").toUInt());
		// Quantification
		runStatistics->liveTime = (retLiveTime / 100000.0);

		convertBytesToUInt32(&runStatistics->outputCounts, pairMap.value("data23").toUInt(), pairMap.value("data22").toUInt(), pairMap.value("data27").toUInt(), pairMap.value("data26").toUInt());
		convertBytesToUInt32(&runStatistics->inputCounts, pairMap.value("data31").toUInt(), pairMap.value("data30").toUInt(), pairMap.value("data35").toUInt(), pairMap.value("data34").toUInt());
		convertBytesToUInt32(&runStatistics->outputCountRate, pairMap.value("data39").toUInt(), pairMap.value("data38").toUInt(), pairMap.value("data43").toUInt(), pairMap.value("data42").toUInt());
		convertBytesToUInt32(&runStatistics->inputCountRate, pairMap.value("data47").toUInt(), pairMap.value("data46").toUInt(), pairMap.value("data51").toUInt(), pairMap.value("data50").toUInt());

	}
	return DPP_SUCCESS;
}

DPPStatusType getMCADataRaw(const CharType* serialNumber, UInt16Type mcaDataSize, UInt8Type* mcaData)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	if (! mcaData)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}

	VicoQuery query;
	QJsonObject mcaResponseData = query.execute(getDeviceIdentifierfromString(serialNumber), 19, READ, 0, mcaDataSize);
	if (DPP_SUCCESS != getRC(mcaResponseData)) {
		return getRC(mcaResponseData);
	}

	memset(mcaData, 0, mcaDataSize);
	QJsonArray bins = mcaResponseData.value(API_MCA).toArray();
	UInt16Type index = 0;
	for(const QJsonValue &pair : bins) {
		QVariantMap pairMap = pair.toObject().toVariantMap();
		uchar unsignedByte = 0x000000FF & pairMap.value("value").toUInt();
		UInt16Type count = pairMap.value("count").toUInt();
		for(UInt16Type i=0;i<count;i++) {
			mcaData[index] = unsignedByte;
			index++;
			if(index > mcaDataSize) {
				return DPP_RESPONSE_OUT_OF_BOUNDS_ERROR;
			}
		}
	}

	return DPP_SUCCESS;
}

DPPStatusType getMCADataUInt32(const CharType* serialNumber, UInt8Type bytesPerBin, UInt16Type numberOfBins, UInt32Type* mcaData)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	if (! mcaData)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}

	UInt16Type mcaDataSize = bytesPerBin*numberOfBins;
	UInt8Type mcaDataRaw[mcaDataSize];
	VicoQuery query;
	QJsonObject mcaResponseData = query.execute(getDeviceIdentifierfromString(serialNumber), 19, READ, 0, mcaDataSize);
	if (DPP_SUCCESS != getRC(mcaResponseData)) {
		return getRC(mcaResponseData);
	}

	memset(mcaDataRaw, 0, mcaDataSize);
	memset(mcaData, 0, numberOfBins);

	QJsonArray bins = mcaResponseData.value(API_MCA).toArray();
	UInt16Type index = 0;
	for(const QJsonValue &pair : bins) {
		QVariantMap pairMap = pair.toObject().toVariantMap();
		uchar unsignedByte = 0x000000FF & pairMap.value("value").toUInt();
		UInt16Type count = pairMap.value("count").toUInt();
		for(UInt16Type i=0;i<count;i++) {
			mcaDataRaw[index] = unsignedByte;
			index++;
			if(index > mcaDataSize) {
				return DPP_RESPONSE_OUT_OF_BOUNDS_ERROR;
			}
		}
	}
	return convertByteToInt32(mcaDataRaw, mcaData, numberOfBins, bytesPerBin);
}


DPPStatusType getMCAData1BytePerBin(const CharType* serialNumber, UInt16Type numberOfBins, UInt8Type* mcaData)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	if (! mcaData)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}

	UInt8Type bytesPerBin = 1;
	UInt16Type mcaDataSize = bytesPerBin*numberOfBins;
	VicoQuery query;
	QJsonObject mcaResponseData = query.execute(getDeviceIdentifierfromString(serialNumber), 19, READ, 0, mcaDataSize);
	if (DPP_SUCCESS != getRC(mcaResponseData)) {
		return getRC(mcaResponseData);
	}

	memset(mcaData, 0, numberOfBins);

	QJsonArray bins = mcaResponseData.value(API_MCA).toArray();
	UInt16Type index = 0;
	for(const QJsonValue &pair : bins) {
		QVariantMap pairMap = pair.toObject().toVariantMap();
		uchar unsignedByte = 0x000000FF & pairMap.value("value").toUInt();
		UInt16Type count = pairMap.value("count").toUInt();
		for(UInt16Type i=0;i<count;i++) {
			mcaData[index] = unsignedByte;
			index++;
			if(index > mcaDataSize) {
				return DPP_RESPONSE_OUT_OF_BOUNDS_ERROR;
			}
		}
	}

	// No conversion needed

	return DPP_SUCCESS;
}

DPPStatusType getMCAData2BytesPerBin(const CharType* serialNumber, UInt16Type numberOfBins, UInt16Type* mcaData)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	if (! mcaData)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}

	UInt8Type bytesPerBin = 2;
	UInt16Type mcaDataSize = bytesPerBin*numberOfBins;
	UInt8Type mcaDataRaw[mcaDataSize];
	VicoQuery query;
	QJsonObject mcaResponseData = query.execute(getDeviceIdentifierfromString(serialNumber), 19, READ, 0, mcaDataSize);
	if (DPP_SUCCESS != getRC(mcaResponseData)) {
		return getRC(mcaResponseData);
	}

	memset(mcaDataRaw, 0, mcaDataSize);
	memset(mcaData, 0, numberOfBins);

	QJsonArray bins = mcaResponseData.value(API_MCA).toArray();
	UInt16Type index = 0;
	for(const QJsonValue &pair : bins) {
		QVariantMap pairMap = pair.toObject().toVariantMap();
		uchar unsignedByte = 0x000000FF & pairMap.value("value").toUInt();
		UInt16Type count = pairMap.value("count").toUInt();
		for(UInt16Type i=0;i<count;i++) {
			mcaDataRaw[index] = unsignedByte;
			index++;
			if(index > mcaDataSize) {
				return DPP_RESPONSE_OUT_OF_BOUNDS_ERROR;
			}
		}
	}

	// Perform conversion from byte to uint16
	for (int i=0, j=0; i<numberOfBins; i++, j=i*bytesPerBin)
	{
		mcaData[i] = (UInt32Type)(mcaDataRaw[j] | mcaDataRaw[j+1]<<8);
	}

	return DPP_SUCCESS;
}

DPPStatusType getMCAData3BytesPerBin(const CharType* serialNumber, UInt16Type numberOfBins, UInt32Type* mcaData)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	if (! mcaData)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}

	UInt8Type bytesPerBin = 3;
	UInt16Type mcaDataSize = bytesPerBin*numberOfBins;
	UInt8Type mcaDataRaw[mcaDataSize];
	VicoQuery query;
	QJsonObject mcaResponseData = query.execute(getDeviceIdentifierfromString(serialNumber), 19, READ, 0, mcaDataSize);
	if (DPP_SUCCESS != getRC(mcaResponseData)) {
		return getRC(mcaResponseData);
	}

	memset(mcaDataRaw, 0, mcaDataSize);
	memset(mcaData, 0, numberOfBins);

	QJsonArray bins = mcaResponseData.value(API_MCA).toArray();
	UInt16Type index = 0;
	for(const QJsonValue &pair : bins) {
		QVariantMap pairMap = pair.toObject().toVariantMap();
		uchar unsignedByte = 0x000000FF & pairMap.value("value").toUInt();
		UInt16Type count = pairMap.value("count").toUInt();
		for(UInt16Type i=0;i<count;i++) {
			mcaDataRaw[index] = unsignedByte;
			index++;
			if(index > mcaDataSize) {
				return DPP_RESPONSE_OUT_OF_BOUNDS_ERROR;
			}
		}
	}

	// Perform conversion from byte to uint32
	return convertByteToInt32(mcaDataRaw, mcaData, numberOfBins, bytesPerBin);
}

DPPStatusType setMCANumberOfBins(const CharType* serialNumber, UInt16Type* numberOfBins)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	if (! numberOfBins)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	quint16 dppValue;
	// Don't recalculate if the given value is already a power of 2
	if (*numberOfBins && !(*numberOfBins & (*numberOfBins - 1)))
	{
		dppValue = log2(*numberOfBins);
	}
	else {
		// Find the power of the given number of bins that is closer to the original number of bins value
		// Example: 2900 -> is closer to 2048 than 4096, hence 2048 must be chosen
		quint8 lowerBins = ceil(log2(*numberOfBins));
		quint8 upperBins = floor(log2(*numberOfBins));
		quint16 lowerNumberOfBins = qPow(2, lowerBins);
		quint16 upperNumberOfBins = qPow(2, upperBins);
		// Every inapplicable value inbetween must be handled by VICOLib
		// If the numberOfBins value was recalculated by VICOLib, provide this applicable numberOfBins by API
		if (abs(lowerNumberOfBins-*numberOfBins) > abs(upperNumberOfBins-*numberOfBins)) {
			*numberOfBins = qPow(2, upperBins);
		}
		else {
			*numberOfBins = qPow(2, lowerBins);
		}
		return DPP_VICOLIB_OUT_OF_RANGE_ERROR;
	}
	VicoQuery query;
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 20, WRITE, dppValue);
	// OUT_OF_RANGE only happens on the DPP if we are exceeding lower or upper bounds.
	if (DPP_OUT_OF_RANGE_ERROR == getRC(answer)) {
		UInt8Type dppValue = answer.value(API_DATA).toInt();
		*numberOfBins = qPow(2, dppValue);
	}
	return getRC(answer);
}

DPPStatusType getMCANumberOfBins(const CharType* serialNumber, UInt16Type* numberOfBins)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	if (! numberOfBins)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	VicoQuery query;
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 20, READ, 0);
	if (DPP_SUCCESS != getRC(answer)) {
		return getRC(answer);
	}
	quint16 bins = answer.value(API_DATA).toInt();
	*numberOfBins = qPow(2, bins);
	return getRC(answer);
}

DPPStatusType setMCABytesPerBin(const CharType* serialNumber, UInt8Type* bytesPerBin)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	if (! bytesPerBin)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	VicoQuery query;
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 21, WRITE, *bytesPerBin);
	if (DPP_OUT_OF_RANGE_ERROR == getRC(answer)) {
		*bytesPerBin = answer.value(API_DATA).toInt();
	}
	return getRC(answer);
}

DPPStatusType getMCABytesPerBin(const CharType* serialNumber, UInt8Type* bytesPerBin)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	if (! bytesPerBin)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	VicoQuery query;
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 21, READ, 0);
	if (DPP_SUCCESS != getRC(answer)) {
		return getRC(answer);
	}
	*bytesPerBin = answer.value(API_DATA).toInt();
	return getRC(answer);
}

/* End Run Control API */

/* Start Pulse Processing API */

DPPStatusType setFastFilterPeakingTime(const CharType* serialNumber, FloatType* peakingTime)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	if (! peakingTime)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	if (*peakingTime < 0) {
		return DPP_INVALID_ARGUMENT_ERROR;
	}

	// Quantification
	quint32 dppValue = qRound(*peakingTime / QUANTIFIER_12_5_NS);
	quint16 isNotFit = dppValue >> 16;
	if (isNotFit != 0) {
		*peakingTime = UInt16Type(UINT_MAX)*QUANTIFIER_12_5_NS;
		return DPP_VICOLIB_OUT_OF_RANGE_ERROR;
	}
	if (fmodf(*peakingTime, QUANTIFIER_12_5_NS) != 0) {
		*peakingTime = dppValue*QUANTIFIER_12_5_NS;
		return DPP_VICOLIB_OUT_OF_RANGE_ERROR;
	}

	VicoQuery query;
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 32, WRITE, dppValue);
	if (DPP_OUT_OF_RANGE_ERROR == getRC(answer)) {
		UInt16Type responseVal = answer.value(API_DATA).toInt();
		*peakingTime = responseVal*QUANTIFIER_12_5_NS;
		return DPP_OUT_OF_RANGE_ERROR;
	}
	return getRC(answer);
}

DPPStatusType getFastFilterPeakingTime(const CharType* serialNumber, FloatType* peakingTime)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	if (! peakingTime)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	VicoQuery query;
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 32, READ, 0);
	if (DPP_SUCCESS != getRC(answer)) {
		return getRC(answer);
	}
	UInt8Type dppValue = answer.value(API_DATA).toInt();
	// Quantification
	*peakingTime = dppValue*QUANTIFIER_12_5_NS;

	return getRC(answer);
}

DPPStatusType getFastFilterGapTime(const CharType* serialNumber, FloatType* gapTime)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	if (! gapTime)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	VicoQuery query;
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 33, READ, 0);
	if (DPP_SUCCESS != getRC(answer)) {
		return getRC(answer);
	}
	UInt16Type dppValue = answer.value(API_DATA).toInt();
	// Quantification
	*gapTime = dppValue*QUANTIFIER_12_5_NS;

	return getRC(answer);
}

DPPStatusType getMediumFilterPeakingTime(const CharType* serialNumber, FloatType* peakingTime)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	if (! peakingTime)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	VicoQuery query;
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 34, READ, 0);
	if (DPP_SUCCESS != getRC(answer)) {
		return getRC(answer);
	}
	UInt16Type dppValue = answer.value(API_DATA).toInt();
	// Quantification
	*peakingTime = dppValue*QUANTIFIER_12_5_NS;

	return getRC(answer);
}

DPPStatusType getMediumFilterGapTime(const CharType* serialNumber, FloatType* gapTime)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	if (! gapTime)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	VicoQuery query;
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 35, READ, 0);
	if (DPP_SUCCESS != getRC(answer)) {
		return getRC(answer);
	}
	UInt16Type dppValue = answer.value(API_DATA).toInt();
	// Quantification
	*gapTime = dppValue*QUANTIFIER_12_5_NS;

	return getRC(answer);
}

DPPStatusType setSlowFilterPeakingTime(const CharType* serialNumber, FloatType* peakingTime)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	if (! peakingTime)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	if (*peakingTime < 0) {
		return DPP_INVALID_ARGUMENT_ERROR;
	}

	// Quantification
	quint32 dppValue = qRound(*peakingTime / QUANTIFIER_12_5_NS);
	quint16 isNotFit = dppValue >> 16;
	if (isNotFit != 0) {
		*peakingTime = UInt16Type(UINT_MAX)*QUANTIFIER_12_5_NS;
		return DPP_VICOLIB_OUT_OF_RANGE_ERROR;
	}
	if (fmodf(*peakingTime, QUANTIFIER_12_5_NS) != 0) {
		*peakingTime = dppValue*QUANTIFIER_12_5_NS;
		return DPP_VICOLIB_OUT_OF_RANGE_ERROR;
	}

	VicoQuery query;
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 36, WRITE, dppValue);
	if (DPP_OUT_OF_RANGE_ERROR == getRC(answer)) {
		UInt16Type responseVal = answer.value(API_DATA).toInt();
		*peakingTime = responseVal*QUANTIFIER_12_5_NS;
	}
	return getRC(answer);
}
DPPStatusType getSlowFilterPeakingTime(const CharType* serialNumber, FloatType* peakingTime)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	if (! peakingTime)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}

	VicoQuery query;
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 36, READ, 0);
	if (DPP_SUCCESS != getRC(answer)) {
		return getRC(answer);
	}
	UInt16Type dppValue = answer.value(API_DATA).toInt();
	// Quantification
	*peakingTime = dppValue * QUANTIFIER_12_5_NS;

	return getRC(answer);
}

DPPStatusType setSlowFilterGapTime(const CharType* serialNumber, FloatType* gapTime)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	if (! gapTime)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	if (*gapTime < 0) {
		return DPP_INVALID_ARGUMENT_ERROR;
	}

	// Quantification
	quint32 dppValue = qRound(*gapTime / QUANTIFIER_12_5_NS);
	quint16 isNotFit = dppValue >> 16;
	if (isNotFit != 0) {
		*gapTime = UInt16Type(UINT_MAX)*QUANTIFIER_12_5_NS;
		return DPP_VICOLIB_OUT_OF_RANGE_ERROR;
	}
	if (fmodf(*gapTime, QUANTIFIER_12_5_NS) != 0) {
		*gapTime = dppValue*QUANTIFIER_12_5_NS;
		return DPP_VICOLIB_OUT_OF_RANGE_ERROR;
	}

	VicoQuery query;
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 37, WRITE, dppValue);
	if (DPP_OUT_OF_RANGE_ERROR == getRC(answer)) {
		UInt16Type responseVal = answer.value(API_DATA).toInt();
		*gapTime = responseVal*QUANTIFIER_12_5_NS;
		return DPP_OUT_OF_RANGE_ERROR;
	}
	return getRC(answer);
}

DPPStatusType getSlowFilterGapTime(const CharType* serialNumber, FloatType* gapTime)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	if (! gapTime)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	VicoQuery query;
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 37, READ, 0);
	if (DPP_SUCCESS != getRC(answer)) {
		return getRC(answer);
	}
	UInt8Type dppValue = answer.value(API_DATA).toInt();
	// Quantification
	*gapTime = dppValue * QUANTIFIER_12_5_NS;

	return getRC(answer);
}

DPPStatusType setFastFilterTriggerThreshold(const CharType* serialNumber, UInt16Type* triggerThreshold)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	if (! triggerThreshold)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	VicoQuery query;
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 38, WRITE, *triggerThreshold);
	if (DPP_OUT_OF_RANGE_ERROR == getRC(answer)) {
		*triggerThreshold = answer.value(API_DATA).toInt();
	}
	return getRC(answer);
}

DPPStatusType getFastFilterTriggerThreshold(const CharType* serialNumber, UInt16Type* triggerThreshold)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	if (! triggerThreshold)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	VicoQuery query;
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 38, READ, 0);
	if (DPP_SUCCESS != getRC(answer)) {
		return getRC(answer);
	}
	*triggerThreshold = answer.value(API_DATA).toInt();
	return getRC(answer);
}

DPPStatusType setMediumFilterTriggerThreshold(const CharType* serialNumber, UInt16Type* triggerThreshold)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	if (! triggerThreshold)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	VicoQuery query;
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 39, WRITE, *triggerThreshold);
	if (DPP_OUT_OF_RANGE_ERROR == getRC(answer)) {
		*triggerThreshold = answer.value(API_DATA).toInt();
	}
	return getRC(answer);
}
DPPStatusType  getMediumFilterTriggerThreshold(const CharType* serialNumber, UInt16Type* triggerThreshold)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	if (! triggerThreshold)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}

	VicoQuery query;
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 39, READ, 0);
	if (DPP_SUCCESS != getRC(answer)) {
		return getRC(answer);
	}
	*triggerThreshold = answer.value(API_DATA).toInt();
	return getRC(answer);
}

DPPStatusType enableMediumFilterPulseDetection(const CharType* serialNumber)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}

	VicoQuery query;
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 40, WRITE, 1);
	return getRC(answer);
}

DPPStatusType disableMediumFilterPulseDetection(const CharType* serialNumber)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}

	VicoQuery query;
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 40, WRITE, 0);
	return getRC(answer);
}

DPPStatusType isMediumFilterPulseDetectionEnabled(const CharType* serialNumber, BooleanType* enabled)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	if (! enabled)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}

	VicoQuery query;
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 40, READ, 0);
	if (DPP_SUCCESS != getRC(answer)) {
		return getRC(answer);
	}
	if (answer.value(API_DATA).toInt() == 1) {
		*enabled = true;
	}
	else if (answer.value(API_DATA).toInt() == 0) {
		 *enabled = false;
	}
	else {
		// Response data couldn't be processed properly
		return DPP_INVALID_RESPONSE_DATA_ERROR;
	}
	return getRC(answer);
}

DPPStatusType setFastFilterMaxWidth(const CharType* serialNumber, FloatType* maxWidth)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	if (! maxWidth)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	if (*maxWidth < 0) {
		return DPP_INVALID_ARGUMENT_ERROR;
	}

	// Quantification
	quint32 dppValue = qRound(*maxWidth / QUANTIFIER_12_5_NS);
	quint16 isNotFit = dppValue >> 16;
	if (isNotFit != 0) {
		*maxWidth = UInt16Type(UINT_MAX)*QUANTIFIER_12_5_NS;
		return DPP_VICOLIB_OUT_OF_RANGE_ERROR;
	}
	if (fmodf(*maxWidth, QUANTIFIER_12_5_NS) != 0) {
		*maxWidth = dppValue*QUANTIFIER_12_5_NS;
		return DPP_VICOLIB_OUT_OF_RANGE_ERROR;
	}

	VicoQuery query;
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 41, WRITE, dppValue);
	if (DPP_OUT_OF_RANGE_ERROR == getRC(answer)) {
		UInt16Type responseVal = answer.value(API_DATA).toInt();
		*maxWidth = responseVal*QUANTIFIER_12_5_NS;
		return DPP_OUT_OF_RANGE_ERROR;
	}
	return getRC(answer);
}

DPPStatusType getFastFilterMaxWidth(const CharType* serialNumber, FloatType* maxWidth)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	if (! maxWidth)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	VicoQuery query;
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 41, READ, 0);
	if (DPP_SUCCESS != getRC(answer)) {
		return getRC(answer);
	}
	UInt8Type dppValue = answer.value(API_DATA).toInt();

	// Quantification
	*maxWidth = dppValue*QUANTIFIER_12_5_NS;
	return getRC(answer);
}

DPPStatusType setMediumFilterMaxWidth(const CharType* serialNumber, FloatType* maxWidth)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	if (! maxWidth)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	if (*maxWidth < 0) {
		return DPP_INVALID_ARGUMENT_ERROR;
	}

	// Quantification
	quint32 dppValue = qRound(*maxWidth / QUANTIFIER_12_5_NS);
	quint16 isNotFit = dppValue >> 16;
	if (isNotFit != 0) {
		*maxWidth = UInt16Type(UINT_MAX)*QUANTIFIER_12_5_NS;
		return DPP_VICOLIB_OUT_OF_RANGE_ERROR;
	}
	if (fmodf(*maxWidth, QUANTIFIER_12_5_NS) != 0) {
		*maxWidth = dppValue*QUANTIFIER_12_5_NS;
		return DPP_VICOLIB_OUT_OF_RANGE_ERROR;
	}

	VicoQuery query;
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 42, WRITE, dppValue);
	if (DPP_OUT_OF_RANGE_ERROR == getRC(answer)) {
		UInt16Type responseVal = answer.value(API_DATA).toInt();
		*maxWidth = responseVal*QUANTIFIER_12_5_NS;
		return DPP_OUT_OF_RANGE_ERROR;
	}
	return getRC(answer);
}

DPPStatusType getMediumFilterMaxWidth(const CharType* serialNumber, FloatType* maxWidth)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	if (! maxWidth)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	VicoQuery query;
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 42, READ, 0);
	if (DPP_SUCCESS != getRC(answer)) {
		return getRC(answer);
	}
	UInt16Type dppValue = answer.value(API_DATA).toInt();
	// Quantification
	*maxWidth = dppValue * QUANTIFIER_12_5_NS;

	return getRC(answer);
}

DPPStatusType setResetInhibitTime(const CharType* serialNumber, FloatType* resetInhibitTime)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	if (! resetInhibitTime)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	if (*resetInhibitTime < 0) {
		return DPP_INVALID_ARGUMENT_ERROR;
	}

	// Quantification
	quint32 dppValue = qRound(*resetInhibitTime / QUANTIFIER_12_5_NS);
	quint16 isNotFit = dppValue >> 16;
	if (isNotFit != 0) {
		*resetInhibitTime = UInt16Type(UINT_MAX)*QUANTIFIER_12_5_NS;
		return DPP_VICOLIB_OUT_OF_RANGE_ERROR;
	}
	if (fmodf(*resetInhibitTime, QUANTIFIER_12_5_NS) != 0) {
		*resetInhibitTime = dppValue*QUANTIFIER_12_5_NS;
		return DPP_VICOLIB_OUT_OF_RANGE_ERROR;
	}

	VicoQuery query;
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 43, WRITE, dppValue);
	if (DPP_OUT_OF_RANGE_ERROR == getRC(answer)) {
		UInt16Type responseVal = answer.value(API_DATA).toInt();
		*resetInhibitTime = responseVal*QUANTIFIER_12_5_NS;
		return DPP_OUT_OF_RANGE_ERROR;
	}
	return getRC(answer);
}

DPPStatusType getResetInhibitTime(const CharType* serialNumber, FloatType* resetInhibitTime)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	if (! resetInhibitTime)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	VicoQuery query;
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 43, READ, 0);
	if (DPP_SUCCESS != getRC(answer)) {
		return getRC(answer);
	}
	UInt8Type dppValue = answer.value(API_DATA).toInt();
	// Quantification
	*resetInhibitTime = dppValue * QUANTIFIER_12_5_NS;

	return getRC(answer);
}

DPPStatusType setBaselineAverageLength(const CharType* serialNumber, UInt8Type* averageLength)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	if (! averageLength)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	VicoQuery query;
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 44, WRITE, *averageLength);
	if (DPP_OUT_OF_RANGE_ERROR == getRC(answer)) {
		*averageLength = answer.value(API_DATA).toInt();
	}
	return getRC(answer);
}

DPPStatusType getBaselineAverageLength(const CharType* serialNumber, UInt8Type* averageLength)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	if (! averageLength)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	VicoQuery query;
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 44, READ, 0);
	if (DPP_SUCCESS != getRC(answer)) {
		return getRC(answer);
	}
	*averageLength = answer.value(API_DATA).toInt();
	return getRC(answer);
}

DPPStatusType setBaselineTrim(const CharType* serialNumber, BaselineTrimType baselineTrim)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}

	VicoQuery query;
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 45, WRITE, baselineTrim);
	return getRC(answer);
}

DPPStatusType getBaselineTrim(const CharType* serialNumber, BaselineTrimType* baselineTrim)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	if (! baselineTrim)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	VicoQuery query;
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 45, READ, 0);
	if (DPP_SUCCESS != getRC(answer)) {
		return getRC(answer);
	}
	*baselineTrim = (BaselineTrimType) answer.value(API_DATA).toInt();
	return getRC(answer);
}

DPPStatusType enableBaselineCorrection(const CharType* serialNumber)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}

	VicoQuery query;
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 46, WRITE, true);
	return getRC(answer);
}

DPPStatusType disableBaselineCorrection(const CharType* serialNumber)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}

	VicoQuery query;
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 46, WRITE, false);
	return getRC(answer);
}

DPPStatusType isBaselineCorrectionEnabled(const CharType* serialNumber, BooleanType* enabled)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	if (! enabled)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	VicoQuery query;
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 46, READ, 0);
	if (DPP_SUCCESS != getRC(answer)) {
		return getRC(answer);
	}
	if (answer.value(API_DATA).toInt() == 1) {
		*enabled = true;
	}
	else if (answer.value(API_DATA).toInt() == 0) {
		 *enabled = false;
	}
	else {
		// Response data couldn't be processed properly
		return DPP_INVALID_RESPONSE_DATA_ERROR;
	}
	return getRC(answer);
}

DPPStatusType setDigitalEnergyGain(const CharType* serialNumber, UInt16Type* gain)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	if (! gain)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	VicoQuery query;
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 47, WRITE, *gain);
	if (DPP_OUT_OF_RANGE_ERROR == getRC(answer)) {
		*gain = answer.value(API_DATA).toInt();
	}
	return getRC(answer);
}

DPPStatusType getDigitalEnergyGain(const CharType* serialNumber, UInt16Type* gain)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	if (! gain)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	VicoQuery query;
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 47, READ, 0);
	if (DPP_SUCCESS != getRC(answer)) {
		return getRC(answer);
	}
	*gain = answer.value(API_DATA).toInt();
	return getRC(answer);
}

DPPStatusType setDigitalEnergyOffset(const CharType* serialNumber, UInt16Type offset)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	VicoQuery query;
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 48, WRITE, offset);
	return getRC(answer);
}

DPPStatusType getDigitalEnergyOffset(const CharType* serialNumber, UInt16Type* offset)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	if (! offset)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	VicoQuery query;
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 48, READ, 0);
	if (DPP_SUCCESS != getRC(answer)) {
		return getRC(answer);
	}
	*offset = answer.value(API_DATA).toInt();
	return getRC(answer);
}

DPPStatusType enableDynamicReset(const CharType* serialNumber)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}

	VicoQuery query;
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 49, WRITE, true);
	return getRC(answer);
}

DPPStatusType disableDynamicReset(const CharType* serialNumber)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}

	VicoQuery query;
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 49, WRITE, false);
	return getRC(answer);
}

DPPStatusType isDynamicResetEnabled(const CharType* serialNumber, BooleanType* enabled)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	if (! enabled)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	VicoQuery query;
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 49, READ, 0);
	if (DPP_SUCCESS != getRC(answer)) {
		return getRC(answer);
	}
	if (answer.value(API_DATA).toInt() == 1) {
		*enabled = true;
	}
	else if (answer.value(API_DATA).toInt() == 0) {
		 *enabled = false;
	}
	else {
		// Response data couldn't be processed properly
		return DPP_INVALID_RESPONSE_DATA_ERROR;
	}
	return getRC(answer);
}

DPPStatusType setDynamicResetThreshold(const CharType* serialNumber, UInt16Type* threshold)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	if (! threshold)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	VicoQuery query;
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 50, WRITE, *threshold);
	if (DPP_OUT_OF_RANGE_ERROR == getRC(answer)) {
		*threshold = answer.value(API_DATA).toInt();
	}
	return getRC(answer);
}

DPPStatusType getDynamicResetThreshold(const CharType* serialNumber, UInt16Type* threshold)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	if (! threshold)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	VicoQuery query;
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 50, READ, 0);
	if (DPP_SUCCESS != getRC(answer)) {
		return getRC(answer);
	}
	*threshold = answer.value(API_DATA).toInt();
	return getRC(answer);
}

DPPStatusType setDynamicResetDuration(const CharType* serialNumber, FloatType* duration)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	if (! duration)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	if (*duration < 0) {
		return DPP_INVALID_ARGUMENT_ERROR;
	}

	// Quantification
	quint32 dppValue = qRound(*duration / QUANTIFIER_12_5_NS);
	quint16 isNotFit = dppValue >> 16;
	if (isNotFit != 0) {
		*duration = UInt16Type(UINT_MAX)*QUANTIFIER_12_5_NS;
		return DPP_VICOLIB_OUT_OF_RANGE_ERROR;
	}
	if (fmodf(*duration, QUANTIFIER_12_5_NS) != 0) {
		*duration = dppValue*QUANTIFIER_12_5_NS;
		return DPP_VICOLIB_OUT_OF_RANGE_ERROR;
	}

	VicoQuery query;
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 51, WRITE, dppValue);
	if (DPP_OUT_OF_RANGE_ERROR == getRC(answer)) {
		UInt16Type responseVal = answer.value(API_DATA).toInt();
		*duration = responseVal*QUANTIFIER_12_5_NS;
		return DPP_OUT_OF_RANGE_ERROR;
	}
	return getRC(answer);
}

DPPStatusType getDynamicResetDuration(const CharType* serialNumber, FloatType* duration)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	if (! duration)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}

	VicoQuery query;
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 51, READ, 0);
	if (DPP_SUCCESS != getRC(answer)) {
		return getRC(answer);
	}
	UInt32Type dppValue = answer.value(API_DATA).toInt();
	// Quantification
	*duration = dppValue * QUANTIFIER_12_5_NS;

	return getRC(answer);
}

DPPStatusType setResetDetection(const CharType* serialNumber, ResetDetectionType resetDetection)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}

	VicoQuery query;
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 56, WRITE, resetDetection);
	return getRC(answer);
}

DPPStatusType getResetDetection(const CharType* serialNumber, ResetDetectionType* resetDetection)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	if (! resetDetection)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	VicoQuery query;
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 56, READ, 0);
	if (DPP_SUCCESS != getRC(answer)) {
		return getRC(answer);
	}
	*resetDetection = (ResetDetectionType) answer.value(API_DATA).toInt();
	return getRC(answer);
}

/* End Pulse Processing API */


/* Start Hardware and Diagnostic API */

DPPStatusType loadDefaultParameterSet(const CharType* serialNumber)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}

	VicoQuery query;
	// Default slot = slot 0
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 64, READ, 0);
	return getRC(answer);
}

DPPStatusType loadParameterSet(const CharType* serialNumber)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}

	VicoQuery query;
	// ReadWrite slot = slot 1
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 64, READ, 1);
	return getRC(answer);
}

DPPStatusType saveDefaultParameterSet(const CharType* serialNumber)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}

	VicoQuery query;
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 65, WRITE, 0);
	return getRC(answer);
}

DPPStatusType saveParameterSet(const CharType* serialNumber)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}

	VicoQuery query;
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 65, WRITE, 1);
	return getRC(answer);
}

DPPStatusType getFirmwareVersion(const CharType* serialNumber, FirmwareVersionType* version) {
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	if (! version)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}

	VicoQuery query;
	// Datagram 66: Firmware Major
	QJsonObject majorVersionType = query.execute(getDeviceIdentifierfromString(serialNumber), 66, READ, 0);
	if (DPP_SUCCESS != getRC(majorVersionType)) {
		return getRC(majorVersionType);
	}
	version->major = getData(majorVersionType);
	// Datagram 67: Firmware Minor
	QJsonObject minorVersionType = query.execute(getDeviceIdentifierfromString(serialNumber), 67, READ, 0);
	if (DPP_SUCCESS != getRC(minorVersionType)) {
		return getRC(minorVersionType);
	}
	version->minor = getData(minorVersionType);
	// Datagram 68: Firmware Patch
	QJsonObject patchVersionType = query.execute(getDeviceIdentifierfromString(serialNumber), 68, READ, 0);
	if (DPP_SUCCESS != getRC(patchVersionType)) {
		return getRC(patchVersionType);
	}
	version->patch = getData(patchVersionType);
	// Datagram 69: Firmware Build
	QJsonObject buildVersionType = query.execute(getDeviceIdentifierfromString(serialNumber), 69, READ, 0);
	if (DPP_SUCCESS != getRC(buildVersionType)) {
		return getRC(buildVersionType);
	}
	version->build = getData(buildVersionType);
	// Datagram 70: Firmware Variant
	QJsonObject variantType = query.execute(getDeviceIdentifierfromString(serialNumber), 70, READ, 0);
	if (DPP_SUCCESS != getRC(variantType)) {
		return getRC(variantType);
	}
	version->variant = getData(variantType);
	return DPP_SUCCESS;
}

DPPStatusType getMCUStatusInfo(const CharType* serialNumber, MCUStatusInfoType* mcuStatus)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	if (! mcuStatus)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}

	VicoQuery query;
	QJsonObject mcuStatusData = query.execute(getDeviceIdentifierfromString(serialNumber), 72, READ, 0);
	if (DPP_SUCCESS != getRC(mcuStatusData)) {
		return getRC(mcuStatusData);
	}
	UInt16Type mcuStatsDataBits = mcuStatusData.value(API_DATA).toInt();
	// Check whether the returned data has a value bigger than the expected first three set bits
	if (mcuStatsDataBits > 0x07) {
		return DPP_INVALID_RESPONSE_DATA_ERROR;
	}
	BooleanType powerBit = (mcuStatsDataBits & 1);
	BooleanType readyBit = (mcuStatsDataBits & 2) >> 1;
	BooleanType aReadyBit = (mcuStatsDataBits & 4) >> 2;

	mcuStatus->hasPower = powerBit;
	mcuStatus->isReady = readyBit;
	mcuStatus->isAlmostReady = aReadyBit;

	return DPP_SUCCESS;
}

DPPStatusType getBoardTemperature(const CharType* serialNumber, UInt16Type* temperature)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	if (! temperature)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	VicoQuery query;
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 73, READ, 0);
	if (DPP_SUCCESS != getRC(answer)) {
		return getRC(answer);
	}
	*temperature = answer.value(API_DATA).toInt();
	return getRC(answer);
}

DPPStatusType enableAnalogHardwarePowerdown(const CharType* serialNumber)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}

	VicoQuery query;
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 74, WRITE, 1);
	return getRC(answer);
}

DPPStatusType disableAnalogHardwarePowerdown(const CharType* serialNumber)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}

	VicoQuery query;
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 74, WRITE, 0);
	return getRC(answer);
}

DPPStatusType isAnalogHardwarePowerdownEnabled(const CharType* serialNumber, BooleanType* enabled)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	if (! enabled)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	VicoQuery query;
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 74, READ, 0);
	if (DPP_SUCCESS != getRC(answer)) {
		return getRC(answer);
	}
	if (answer.value(API_DATA).toInt() == 1) {
		*enabled = true;
	}
	else if (answer.value(API_DATA).toInt() == 0) {
		 *enabled = false;
	}
	else {
		// Response data couldn't be processed properly
		return DPP_INVALID_RESPONSE_DATA_ERROR;
	}
	return getRC(answer);
}

DPPStatusType setClockingSpeed(const CharType* serialNumber, ClockingSpeedType clockingSpeed)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}

	VicoQuery query;
	QJsonObject triggerSourceAnswer = query.execute(getDeviceIdentifierfromString(serialNumber), 75, WRITE, clockingSpeed);
	return getRC(triggerSourceAnswer);
}

DPPStatusType getClockingSpeed(const CharType* serialNumber, ClockingSpeedType* clockingSpeed)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	if (! clockingSpeed)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}

	VicoQuery query;
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 75, READ, 0);
	if (DPP_SUCCESS != getRC(answer)) {
		return getRC(answer);
	}
	*clockingSpeed = (ClockingSpeedType) answer.value(API_DATA).toInt();
	return getRC(answer);
}

DPPStatusType getAllParameters(const CharType* serialNumber, const UInt16Type allParametersSize, UInt8Type* allParameters)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	if (! allParameters)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}

	VicoQuery query;
	QJsonObject data = query.execute(getDeviceIdentifierfromString(serialNumber), 79, READ, 0, allParametersSize);
	if (DPP_SUCCESS != getRC(data)) {
		return getRC(data);
	}

	memset(allParameters, 0, allParametersSize);
	QJsonArray dataArray = data.value(API_DATA).toArray();
	QJsonValue pairs = dataArray.at(0);
	QVariantMap pairMap = pairs.toObject().toVariantMap();
	if(pairMap.size() != allParametersSize) {
		return DPPStatusType::DPP_RESPONSE_OUT_OF_BOUNDS_ERROR;
	} else {
		for(int i=0;i<pairMap.size();i++) {
			QString dataKey = "data"+QString::number(i);
			allParameters[i] = pairMap.value(dataKey, 0u).toUInt();
		}
	}

	return DPP_SUCCESS;
}


DPPStatusType setEventTriggerSource(const CharType* serialNumber, TriggerSourceType triggerSource)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}

	VicoQuery query;
	QJsonObject triggerSourceAnswer = query.execute(getDeviceIdentifierfromString(serialNumber), 80, WRITE, triggerSource);
	return getRC(triggerSourceAnswer);
}


DPPStatusType getEventTriggerSource(const CharType* serialNumber, TriggerSourceType* triggerSource)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	if (! triggerSource)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}

	VicoQuery query;
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 80, READ, 0);
	if (DPP_SUCCESS != getRC(answer)) {
		return getRC(answer);
	}
	*triggerSource = (TriggerSourceType) answer.value(API_DATA).toInt();
	return getRC(answer);
}

DPPStatusType setEventTriggerValue(const CharType* serialNumber, UInt16Type triggerValue)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}

	VicoQuery query;
	QJsonObject triggerValueAnswer = query.execute(getDeviceIdentifierfromString(serialNumber), 81, WRITE, triggerValue);
	return getRC(triggerValueAnswer);
}

DPPStatusType getEventTriggerValue(const CharType* serialNumber, UInt16Type* triggerValue)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	if (! triggerValue)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}

	VicoQuery query;
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 81, READ, 0);
	if (DPP_SUCCESS != getRC(answer)) {
		return getRC(answer);
	}
	*triggerValue = answer.value(API_DATA).toInt();
	return getRC(answer);
}

DPPStatusType setEventScopeSamplingInterval(const CharType* serialNumber, UInt16Type* samplingInterval)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	if (! samplingInterval)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	VicoQuery query;
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 82, WRITE, *samplingInterval);
	if (DPP_OUT_OF_RANGE_ERROR == getRC(answer)) {
		*samplingInterval = answer.value(API_DATA).toInt();
	}
	return getRC(answer);
}

DPPStatusType getEventScopeSamplingInterval(const CharType* serialNumber, UInt16Type* samplingInterval)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	if (! samplingInterval)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}

	VicoQuery query;
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 82, READ, 0);
	if (DPP_SUCCESS != getRC(answer)) {
		return getRC(answer);
	}
	*samplingInterval = answer.value(API_DATA).toInt();
	return getRC(answer);
}

DPPStatusType setEventScopeTriggerTimeout(const CharType* serialNumber, TriggerTimeoutType triggerTimeout)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}

	VicoQuery query;
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 83, WRITE, triggerTimeout);
	return getRC(answer);
}
DPPStatusType getEventScopeTriggerTimeout(const CharType* serialNumber, TriggerTimeoutType* triggerTimeout)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	if (! triggerTimeout)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}

	VicoQuery query;
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 83, READ, 0);
	if (DPP_SUCCESS != getRC(answer)) {
		return getRC(answer);
	}
	*triggerTimeout = (TriggerTimeoutType) answer.value(API_DATA).toInt();
	return getRC(answer);
}

DPPStatusType getEventScope(const CharType* serialNumber, const EventScopeType eventScopeType, const UInt16Type eventScopeSize, UInt32Type* eventScope)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	if (! eventScope)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}

	UInt16Type eventScopeNumberOfBins = 8192;
	UInt16Type eventScopeBytesPerBin = 3;

	UInt16Type eventScopeRawSize = eventScopeNumberOfBins*eventScopeBytesPerBin;
	UInt8Type eventScopeRaw[eventScopeRawSize];

	VicoQuery query;
	QJsonObject responseData = query.execute(getDeviceIdentifierfromString(serialNumber), 84, READ, eventScopeType, eventScopeRawSize);
	if (DPP_SUCCESS != getRC(responseData)) {
		return getRC(responseData);
	}
	memset(eventScope, 0, eventScopeSize);
	memset(eventScopeRaw, 0, eventScopeRawSize);
	QJsonArray bins = responseData.value(API_MCA).toArray();
	UInt16Type index = 0;
	for(const QJsonValue &pair : bins) {
		QVariantMap pairMap = pair.toObject().toVariantMap();
		uchar unsignedByte = 0x000000FF & pairMap.value("value").toUInt();
		UInt16Type count = pairMap.value("count").toUInt();
		for(UInt16Type i=0;i<count;i++) {
			eventScopeRaw[index] = unsignedByte;
			index++;
			if(index > eventScopeRawSize) {
				return DPP_RESPONSE_OUT_OF_BOUNDS_ERROR;
			}
		}
	}
	return convertByteToInt32(eventScopeRaw, eventScope, eventScopeNumberOfBins, eventScopeBytesPerBin);
}

DPPStatusType calculateEventRate(const CharType* serialNumber, const TriggerDurationType triggerDuration)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}

	VicoQuery query;
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 85, WRITE, triggerDuration);
	return getRC(answer);
}

DPPStatusType getEventRate(const CharType* serialNumber, UInt32Type* eventRate)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	if (! eventRate)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}

	VicoQuery query;
	QJsonObject answer0And1 = query.execute(getDeviceIdentifierfromString(serialNumber), 86, READ, 0);
	if (DPP_SUCCESS != getRC(answer0And1)) {
		return getRC(answer0And1);
	}
	QJsonObject answer2And3 = query.execute(getDeviceIdentifierfromString(serialNumber), 87, READ, 0);
	if (DPP_SUCCESS != getRC(answer2And3)) {
		return getRC(answer2And3);
	}
	quint16 answer0And1AsInt = answer0And1.value(API_DATA).toInt();
	quint16 answer2And3AsInt = answer2And3.value(API_DATA).toInt();
	quint32 rr = answer2And3AsInt << 16 | answer0And1AsInt;
	*eventRate = rr;
	return DPP_SUCCESS;
}

DPPStatusType deleteFirmware(const CharType* serialNumber) {
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	VicoQuery query;
	QJsonObject answer0And1 = query.execute(getDeviceIdentifierfromString(serialNumber), 91, READ, 0);
		return getRC(answer0And1);
}

DPPStatusType writeFirmwareSection(const CharType* serialNumber, UInt16Type* segmentNumber, UInt16Type firmwareSectionSize, UInt8Type* firmwareSection) {
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	if (! firmwareSection)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	if(firmwareSectionSize != 1024) {
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	VicoQuery query;
	// Requested size is 4
	QJsonObject mcaResponseData = query.execute(getDeviceIdentifierfromString(serialNumber), 92, WRITE, *segmentNumber, firmwareSection);
	*segmentNumber = mcaResponseData.value(API_DATA).toInt();
	return getRC(mcaResponseData);
}

DPPStatusType readFirmwareSection(const CharType* serialNumber, UInt16Type* segmentNumber, UInt16Type firmwareSectionSize, UInt8Type* firmwareSection) {
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	if (! firmwareSection)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	quint16 segmentNumber16 = *segmentNumber;
	VicoQuery query;// Requested size is 1024 bytes firmware + 4 bytes standard DG
	QJsonObject mcaResponseData = query.execute(getDeviceIdentifierfromString(serialNumber), 93, READ, segmentNumber16, 1028);
	QJsonObject jsonData = mcaResponseData.value(API_DATAGRAM_FIRMWARE).toObject();
	QVariantMap pairMap = jsonData.toVariantMap();
	if(pairMap.size() != 1024) {
		QJsonObject replyData;
		return DPP_INVALID_RESPONSE_DATA_ERROR;
	} else {
		*segmentNumber = mcaResponseData.value(API_DATA).toInt();
		for(int i=0;i<pairMap.size();i++) {
			if(i > firmwareSectionSize) {
				return DPP_RESPONSE_OUT_OF_BOUNDS_ERROR;
			}
			QString dataKey = API_DATAGRAM_FIRMWARE+QString::number(i);
			UInt8Type val = pairMap.value(dataKey, 0u).toUInt();
			firmwareSection[i] = val;
		}
	}
	return getRC(mcaResponseData);
}

DPPStatusType setServiceCode(const CharType* serialNumber, UInt32Type serviceCode)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}

	quint16 byte0And1 = serviceCode;
	quint16 byte2And3 = serviceCode >> 16;

	VicoQuery query;
	QJsonObject answer0And1 = query.execute(getDeviceIdentifierfromString(serialNumber), 94, WRITE, byte0And1);
	if (DPP_SUCCESS != getRC(answer0And1)) {
		return getRC(answer0And1);
	}
	QJsonObject answer2And3 = query.execute(getDeviceIdentifierfromString(serialNumber), 95, WRITE, byte2And3);
	if (DPP_SUCCESS != getRC(answer2And3)) {
		return getRC(answer2And3);
	}
	return DPP_SUCCESS;
}

DPPStatusType getServiceCode(const CharType* serialNumber, UInt32Type* serviceCode)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	if (! serviceCode)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}

	VicoQuery query;
	QJsonObject answer0And1 = query.execute(getDeviceIdentifierfromString(serialNumber), 94, READ, 0);
	if (DPP_SUCCESS != getRC(answer0And1)) {
		return getRC(answer0And1);
	}
	QJsonObject answer2And3 = query.execute(getDeviceIdentifierfromString(serialNumber), 95, READ, 0);
	if (DPP_SUCCESS != getRC(answer2And3)) {
		return getRC(answer2And3);
	}
	quint16 answer0And1AsInt = answer0And1.value(API_DATA).toInt();
	quint16 answer2And3AsInt = answer2And3.value(API_DATA).toInt();
	quint32 rr = answer2And3AsInt << 16 | answer0And1AsInt;
	*serviceCode = rr;
	return DPP_SUCCESS;
}

/* End Hardware and Diagnostic API */


/* Start Communication API */

DPPStatusType enableEthernetPowerdown(const CharType* serialNumber)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}

	VicoQuery query;
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 96, WRITE, true);
	return getRC(answer);
}

DPPStatusType disableEthernetPowerdown(const CharType* serialNumber)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}

	VicoQuery query;
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 96, WRITE, false);
	return getRC(answer);
}
DPPStatusType isEthernetPowerdownEnabled(const CharType* serialNumber, BooleanType* enabled)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	if (! enabled)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}

	VicoQuery query;
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 96, READ, 0);
	if (DPP_SUCCESS != getRC(answer)) {
		return getRC(answer);
	}
	if (answer.value(API_DATA).toInt() == 1) {
		*enabled = true;
	}
	else if (answer.value(API_DATA).toInt() == 0) {
		 *enabled = false;
	}
	else {
		// Response data couldn't be processed properly
		return DPP_INVALID_RESPONSE_DATA_ERROR;
	}
	return getRC(answer);
}

DPPStatusType setEthernetProtocol(const CharType* serialNumber, EthernetProtocolType ethernetProtocol)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}

	VicoQuery query;
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 97, WRITE, ethernetProtocol);
	return getRC(answer);
}

DPPStatusType getEthernetProtocol(const CharType* serialNumber, EthernetProtocolType* ethernetProtocol)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	if (! ethernetProtocol)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}

	VicoQuery query;
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 97, READ, 0);
	if (DPP_SUCCESS != getRC(answer)) {
		return getRC(answer);
	}
	*ethernetProtocol = (EthernetProtocolType) answer.value(API_DATA).toInt();
	return getRC(answer);
}

DPPStatusType setEthernetSpeed(const CharType* serialNumber, EthernetSpeedType data)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}

	VicoQuery query;
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 98, WRITE, data);
	return getRC(answer);
}

DPPStatusType getEthernetSpeed(const CharType* serialNumber, EthernetSpeedType* ethernetSpeed)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	if (! ethernetSpeed)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}

	VicoQuery query;
	// Datagram 98: Ethernet Speed
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 98, READ, 0);
	if (DPP_SUCCESS != getRC(answer)) {
		return getRC(answer);
	}
	*ethernetSpeed = (EthernetSpeedType) answer.value(API_DATA).toInt();
	return getRC(answer);
}

DPPStatusType setIPAddress(const CharType* serialNumber, const CharType* ipAddress)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	if (! ipAddress)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}

	bool isIpv4 = false;
	isIPv4Address(ipAddress, &isIpv4);
	if (! isIpv4)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}

	QHostAddress ipv4 = QHostAddress(ipAddress);
	quint32 ipv4AsInt = ipv4.toIPv4Address();
	quint16 byte2And3 = ipv4AsInt;
	quint16 byte0And1 = ipv4AsInt >> 16;

	VicoQuery query;
	QJsonObject answer0And1 = query.execute(getDeviceIdentifierfromString(serialNumber), 100, WRITE, byte0And1);
	if (DPP_SUCCESS != getRC(answer0And1)) {
		return getRC(answer0And1);
	}
	QJsonObject answer2And3 = query.execute(getDeviceIdentifierfromString(serialNumber), 101, WRITE, byte2And3);
	if (DPP_SUCCESS != getRC(answer2And3)) {
		return getRC(answer2And3);
	}
	return DPP_SUCCESS;
}

DPPStatusType getIPAddress(const CharType* serialNumber, const UInt8Type ipAddressSize, CharType* ipAddress)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	if (! ipAddress)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}

	VicoQuery query;
	QJsonObject answer0And1 = query.execute(getDeviceIdentifierfromString(serialNumber), 100, READ, 0);
	if (DPP_SUCCESS != getRC(answer0And1)) {
		return getRC(answer0And1);
	}
	QJsonObject answer2And3 = query.execute(getDeviceIdentifierfromString(serialNumber), 101, READ, 0);
	if (DPP_SUCCESS != getRC(answer2And3)) {
		return getRC(answer2And3);
	}
	quint16 answer0And1AsInt = answer0And1.value(API_DATA).toInt();
	quint16 answer2And3AsInt = answer2And3.value(API_DATA).toInt();
	quint32 rr = answer0And1AsInt << 16 | answer2And3AsInt;
	QHostAddress returnedAddr = QHostAddress(rr);
	QByteArray str = returnedAddr.toString().toLocal8Bit();
	const char *ip = str.data();
	if (ipAddressSize >= str.size()) {
		bool isIpv4 = false;
		isIPv4Address(ip, &isIpv4);
		if (isIpv4 && ipAddress)
		{
			memcpy(ipAddress, "", ipAddressSize);
			// +1 to add terminating null character
			strncpy(ipAddress, ip, str.size()+1);
			return DPP_SUCCESS;
		}
		else
		{
			return DPP_INVALID_RESPONSE_DATA_ERROR;
		}
	} else {
		return DPP_RESPONSE_OUT_OF_BOUNDS_ERROR;
	}
}

DPPStatusType setSubnetMask(const CharType* serialNumber, const CharType* subnetMask)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	if (! subnetMask)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}

	bool isIpv4 = false;
	isIPv4Address(subnetMask, &isIpv4);
	if (! isIpv4)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}

	QHostAddress ipv4 = QHostAddress(subnetMask);
	quint32 ipv4AsInt = ipv4.toIPv4Address();
	quint16 byte2And3 = ipv4AsInt;
	quint16 byte0And1 = ipv4AsInt >> 16;

	VicoQuery query;
	QJsonObject answer0And1 = query.execute(getDeviceIdentifierfromString(serialNumber), 102, WRITE, byte0And1);
	if (DPP_SUCCESS != getRC(answer0And1)) {
		return getRC(answer0And1);
	}
	QJsonObject answer2And3 = query.execute(getDeviceIdentifierfromString(serialNumber), 103, WRITE, byte2And3);
	if (DPP_SUCCESS != getRC(answer2And3)) {
		return getRC(answer2And3);
	}
	return DPP_SUCCESS;
}

DPPStatusType getSubnetMask(const CharType* serialNumber, const UInt8Type subnetMaskSize, CharType* subnetMask)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	if (! subnetMask)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}

	VicoQuery query;
	QJsonObject answer0And1 = query.execute(getDeviceIdentifierfromString(serialNumber), 102, READ, 0);
	if (DPP_SUCCESS != getRC(answer0And1)) {
		return getRC(answer0And1);
	}
	QJsonObject answer2And3 = query.execute(getDeviceIdentifierfromString(serialNumber), 103, READ, 0);
	if (DPP_SUCCESS != getRC(answer2And3)) {
		return getRC(answer2And3);
	}
	quint16 answer0And1AsInt = answer0And1.value(API_DATA).toInt();
	quint16 answer2And3AsInt = answer2And3.value(API_DATA).toInt();
	quint32 rr = answer0And1AsInt << 16 | answer2And3AsInt;
	QHostAddress returnedAddr = QHostAddress(rr);
	QByteArray str = returnedAddr.toString().toLocal8Bit();
	char *ip = str.data();
	if (subnetMaskSize >= str.size()) {
		bool isIpv4 = false;
		isIPv4Address(ip, &isIpv4);
		if (isIpv4 && subnetMask)
		{
			memcpy(subnetMask, "", subnetMaskSize);
			// +1 to add terminating null character
			strncpy(subnetMask, ip, str.size()+1);
			return DPP_SUCCESS;
		}
		else
		{
			return DPP_INVALID_RESPONSE_DATA_ERROR;
		}
	} else {
		return DPP_RESPONSE_OUT_OF_BOUNDS_ERROR;
	}
}

DPPStatusType setGatewayIPAddress(const CharType* serialNumber, const CharType* gatewayIpAddress)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	if (! gatewayIpAddress)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}

	bool isIpv4 = false;
	isIPv4Address(gatewayIpAddress, &isIpv4);
	if (! isIpv4)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}

	QHostAddress ipv4 = QHostAddress(gatewayIpAddress);
	quint32 ipv4AsInt = ipv4.toIPv4Address();
	quint16 byte2And3 = ipv4AsInt;
	quint16 byte0And1 = ipv4AsInt >> 16;

	VicoQuery query;
	QJsonObject answer0And1 = query.execute(getDeviceIdentifierfromString(serialNumber), 104, WRITE, byte0And1);
	if (DPP_SUCCESS != getRC(answer0And1)) {
		return getRC(answer0And1);
	}
	QJsonObject answer2And3 = query.execute(getDeviceIdentifierfromString(serialNumber), 105, WRITE, byte2And3);
	if (DPP_SUCCESS != getRC(answer2And3)) {
		return getRC(answer2And3);
	}
	return DPP_SUCCESS;
}

DPPStatusType getGatewayIPAddress(const CharType* serialNumber, const UInt8Type gatewayIpAddressSize, CharType* gatewayIpAddress)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	if (! gatewayIpAddress)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}

	VicoQuery query;
	QJsonObject answer0And1 = query.execute(getDeviceIdentifierfromString(serialNumber), 104, READ, 0);
	if (DPP_SUCCESS != getRC(answer0And1)) {
		return getRC(answer0And1);
	}
	QJsonObject answer2And3 = query.execute(getDeviceIdentifierfromString(serialNumber), 105, READ, 0);
	if (DPP_SUCCESS != getRC(answer2And3)) {
		return getRC(answer2And3);
	}
	quint16 answer0And1AsInt = answer0And1.value(API_DATA).toInt();
	quint16 answer2And3AsInt = answer2And3.value(API_DATA).toInt();
	quint32 rr = answer0And1AsInt << 16 | answer2And3AsInt;
	QHostAddress returnedAddr = QHostAddress(rr);
	QByteArray str = returnedAddr.toString().toLocal8Bit();
	char *ip = str.data();

	bool isIpv4 = false;
	isIPv4Address(ip, &isIpv4);
	if (gatewayIpAddressSize >= str.size()) {
		bool isIpv4 = false;
		isIPv4Address(ip, &isIpv4);
		if (isIpv4 && gatewayIpAddress)
		{
			memcpy(gatewayIpAddress, "", gatewayIpAddressSize);
			// +1 to add terminating null character
			strncpy(gatewayIpAddress, ip, str.size()+1);
			return DPP_SUCCESS;
		}
		else
		{
			return DPP_INVALID_RESPONSE_DATA_ERROR;
		}
	} else {
		return DPP_RESPONSE_OUT_OF_BOUNDS_ERROR;
	}
}

DPPStatusType getEthernetPort(const CharType* serialNumber, UInt16Type* ethernetPort) {
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	if (! ethernetPort)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	VicoQuery query;
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 106, READ, 0);
	if (DPP_SUCCESS != getRC(answer)) {
		return getRC(answer);
	}
	*ethernetPort = answer.value(API_DATA).toInt();
	return getRC(answer);
}


DPPStatusType setMACAddress(const CharType* serialNumber, const CharType* macAddress)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	if (! macAddress)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}

	bool isMac = false;
	isMACAddress(macAddress, &isMac);
	if (! isMac)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}

	QString macci = QString(macAddress);
	QRegExp ipv4Regex("[^0-9a-fA-F]+");
	macci.replace(ipv4Regex, "");
	bool ok;
	quint64 value = macci.toULongLong(&ok, 16);
	quint16 byte0And1 = value;
	quint16 byte2And3 = value >> 16;
	quint16 byte4And5 = value >> 32;

	VicoQuery query;
	QJsonObject answer0And1 = query.execute(getDeviceIdentifierfromString(serialNumber), 107, WRITE, byte4And5);
	if (DPP_SUCCESS != getRC(answer0And1)) {
		return getRC(answer0And1);
	}
	QJsonObject answer2And3 = query.execute(getDeviceIdentifierfromString(serialNumber), 108, WRITE, byte2And3);
	if (DPP_SUCCESS != getRC(answer2And3)) {
		return getRC(answer2And3);
	}
	QJsonObject answer4And5 = query.execute(getDeviceIdentifierfromString(serialNumber), 109, WRITE, byte0And1);
	if (DPP_SUCCESS != getRC(answer2And3)) {
		return getRC(answer2And3);
	}
	return DPP_SUCCESS;
}

DPPStatusType getMACAddress(const CharType* serialNumber, const UInt8Type macAddressSize, CharType* macAddress)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	if (! macAddress)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}

	VicoQuery query;
	QJsonObject answer0And1 = query.execute(getDeviceIdentifierfromString(serialNumber), 109, READ, 0);
	if (DPP_SUCCESS != getRC(answer0And1)) {
		return getRC(answer0And1);
	}
	QJsonObject answer2And3 = query.execute(getDeviceIdentifierfromString(serialNumber), 108, READ, 0);
	if (DPP_SUCCESS != getRC(answer2And3)) {
		return getRC(answer2And3);
	}
	QJsonObject answer4And5 = query.execute(getDeviceIdentifierfromString(serialNumber), 107, READ, 0);
	if (DPP_SUCCESS != getRC(answer4And5)) {
		return getRC(answer4And5);
	}

	quint16 answer0And1AsInt = answer0And1.value(API_DATA).toInt();
	quint8 byte0 = answer0And1AsInt;
	quint8 byte1 = answer0And1AsInt >> 8;
	quint16 answer2And3AsInt = answer2And3.value(API_DATA).toInt();
	quint8 byte2 = answer2And3AsInt;
	quint8 byte3 = answer2And3AsInt >> 8;
	quint16 answer4And5AsInt = answer4And5.value(API_DATA).toInt();
	quint8 byte4 = answer4And5AsInt;
	quint8 byte5 = answer4And5AsInt >> 8;
	QString hex0;
	hex0 = hex0.setNum(byte0, 16).rightJustified(2, '0');
	QString hex1;
	hex1 = hex1.setNum(byte1, 16).rightJustified(2, '0');
	QString hex2;
	hex2 = hex2.setNum(byte2, 16).rightJustified(2, '0');
	QString hex3;
	hex3 = hex3.setNum(byte3, 16).rightJustified(2, '0');
	QString hex4;
	hex4 = hex4.setNum(byte4, 16).rightJustified(2, '0');
	QString hex5;
	hex5 = hex5.setNum(byte5, 16).rightJustified(2, '0');

	QString hexadecimal;
	QString delimiter = "-";
	hexadecimal.append(hex5.toUpper()).append(delimiter).append(hex4.toUpper()).append(delimiter).append(hex3.toUpper()).append(delimiter).append(hex2.toUpper()).append(delimiter).append(hex1.toUpper()).append(delimiter).append(hex0.toUpper());
	QByteArray str = hexadecimal.toLocal8Bit();
	char *mac = str.data();

	if (macAddressSize >= str.size()) {
		bool isMacAddress = false;
		isMACAddress(mac, &isMacAddress);
		if (isMacAddress && macAddress)
		{
			memcpy(macAddress, "", macAddressSize);
			// +1 to add terminating null character
			strncpy(macAddress, mac, str.size()+1);
			return DPP_SUCCESS;
		}
		else
		{
			return DPP_INVALID_RESPONSE_DATA_ERROR;
		}
	} else {
		return DPP_RESPONSE_OUT_OF_BOUNDS_ERROR;
	}
}

DPPStatusType applyEthernetConfiguration(const CharType* serialNumber)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}

	VicoQuery query;
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 110, WRITE, 0);
	return getRC(answer);
}

DPPStatusType enableUSBPowerdown(const CharType* serialNumber)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}

	VicoQuery query;
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 115, WRITE, true);
	return getRC(answer);
}

DPPStatusType disableUSBPowerdown(const CharType* serialNumber)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}

	VicoQuery query;
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 115, WRITE, false);
	return getRC(answer);
}

DPPStatusType isUSBPowerdownEnabled(const CharType* serialNumber, BooleanType* enabled)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	if (! enabled)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}

	VicoQuery query;
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 115, READ, 0);
	if (DPP_SUCCESS != getRC(answer)) {
		return getRC(answer);
	}
	if (answer.value(API_DATA).toInt() == 1) {
		*enabled = true;
	}
	else if (answer.value(API_DATA).toInt() == 0) {
		 *enabled = false;
	}
	else {
		// Response data couldn't be processed properly
		return DPP_INVALID_RESPONSE_DATA_ERROR;
	}
	return getRC(answer);
}

DPPStatusType enableSPIPowerdown(const CharType* serialNumber)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}

	VicoQuery query;
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 118, WRITE, true);
	return getRC(answer);
}

DPPStatusType disableSPIPowerdown(const CharType* serialNumber)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}

	VicoQuery query;
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 118, WRITE, false);
	return getRC(answer);
}

DPPStatusType isSPIPowerdownEnabled(const CharType* serialNumber, BooleanType* enabled)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	if (! enabled)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}

	VicoQuery query;
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 118, READ, 0);
	if (DPP_SUCCESS != getRC(answer)) {
		return getRC(answer);
	}
	if (answer.value(API_DATA).toInt() == 1) {
		*enabled = true;
	}
	else if (answer.value(API_DATA).toInt() == 0) {
		 *enabled = false;
	}
	else {
		// Response data couldn't be processed properly
		return DPP_INVALID_RESPONSE_DATA_ERROR;
	}
	return getRC(answer);
}

/* End Communication API */

DPPStatusType getKeyRevision(const CharType* serialNumber, UInt16Type* keyRevision)
{
	if (! serialNumber)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	if (! keyRevision)
	{
		return DPP_INVALID_ARGUMENT_ERROR;
	}
	VicoQuery query;
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 90, READ, 0);
	if (DPP_SUCCESS != getRC(answer)) {
		return getRC(answer);
	}
	*keyRevision = answer.value(API_DATA).toInt();
	return getRC(answer);
}

/* Start MCU Datagram API */

MCUStatusType swPkgGetActive(const CharType* serialNumber, SoftwarePackage *swPkg) {
	quint8 expectedResponseLength = 1;
	if (!serialNumber) {
		return MCU_INVALID_ARGUMENT_ERROR;
	} else if (!swPkg) {
		return MCU_INVALID_ARGUMENT_ERROR;
	}

	VicoQuery query;
	// VER, CIX, CL, requestedDataLength, variableDataSendLength
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 0x01u, 0x00u, 0x05u, expectedResponseLength, 0);
	if (MCU_SUCCESS != getMcuRC(answer)) {
		return getMcuRC(answer);
	}
	answer.value(API_MCU_PROTOCOL_VERSION).toInt();

	QJsonArray data = answer.value(API_DATA).toArray();
	QJsonValue pairs = data.at(0);
	QVariantMap pairMap = pairs.toObject().toVariantMap();
	if(pairMap.size() != expectedResponseLength) {
		return MCUStatusType::MCU_RESPONSE_OUT_OF_BOUNDS_ERROR;
	} else {
		uint dataVal = pairMap.value("data0").toUInt();
		*swPkg = (SoftwarePackage) dataVal;
	}

	return getMcuRC(answer);
}

MCUStatusType flashRead(const CharType* serialNumber, UInt32Type addStart, UInt8Type len, UInt8Type* data) {
	if (len > 249) {
		return MCU_INVALID_ARGUMENT_ERROR;
	}
	if (!serialNumber) {
		return MCU_INVALID_ARGUMENT_ERROR;
	}
	if (! data)
	{
		return MCU_INVALID_ARGUMENT_ERROR;
	}

	// Break down to bytes
	quint8 startAddress1 = (addStart & 0xFF000000) >> 24;
	quint8 startAddress2 = (addStart & 0x00FF0000) >> 16;
	quint8 startAddress3 = (addStart & 0x0000FF00) >> 8;
	quint8 startAddress4 = (addStart & 0x000000FF);

	VicoQuery query;
	// Version, id, length, crc, add_start, len, requestedDataLength
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 0x01u, 0x01u, 0x0Au, len, 5, startAddress4, startAddress3, startAddress2, startAddress1, len);
	if (MCU_SUCCESS != getMcuRC(answer)) {
		return getMcuRC(answer);
	}
	answer.value(API_MCU_PROTOCOL_VERSION).toInt();

	QJsonArray jsonData = answer.value(API_DATA).toArray();
	QJsonValue pairs = jsonData.at(0);
	QVariantMap pairMap = pairs.toObject().toVariantMap();
	if(pairMap.size() != len) {
		return MCUStatusType::MCU_RESPONSE_OUT_OF_BOUNDS_ERROR;
	} else {
		for(int i=0;i<pairMap.size();i++) {
			QString dataKey = "data"+QString::number(i);
			data[i] = pairMap.value(dataKey, 0u).toUInt();
		}
	}

	return getMcuRC(answer);
}

MCUStatusType flashWriteSessionStart(const CharType* serialNumber) {
	if (!serialNumber) {
		return MCU_INVALID_ARGUMENT_ERROR;
	}

	VicoQuery query;
	// VER, CIX, CL, requestedDataLength, variableDataSendLength
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 0x01u, 0x02u, 0x05u, 0, 0);
	if (MCU_SUCCESS != getMcuRC(answer)) {
		return getMcuRC(answer);
	}
	answer.value(API_MCU_PROTOCOL_VERSION).toInt();
	return getMcuRC(answer);
}

MCUStatusType flashWriteSessionExit(const CharType* serialNumber) {
	if (!serialNumber) {
		return MCU_INVALID_ARGUMENT_ERROR;
	}

	VicoQuery query;
	// VER, CIX, CL, requestedDataLength, variableDataSendLength
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 0x01u, 0x03u, 0x05u, 0, 0);
	if (MCU_SUCCESS != getMcuRC(answer)) {
		return getMcuRC(answer);
	}
	answer.value(API_MCU_PROTOCOL_VERSION).toInt();
	return getMcuRC(answer);
}

MCUStatusType flashWriteSessionReset(const CharType* serialNumber) {
	if (!serialNumber) {
		return MCU_INVALID_ARGUMENT_ERROR;
	}

	VicoQuery query;
	// VER, CIX, CL, requestedDataLength, variableDataSendLength
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 0x01u, 0x04u, 0x05u, 0, 0);
	if (MCU_SUCCESS != getMcuRC(answer)) {
		return getMcuRC(answer);
	}
	answer.value(API_MCU_PROTOCOL_VERSION).toInt();
	return getMcuRC(answer);
}

MCUStatusType flashWriteSessionData(const CharType* serialNumber, UInt32Type addStart, UInt8Type* data)
{
	quint8 expectedRequestLength = 132+5;
	if (!serialNumber) {
		return MCU_INVALID_ARGUMENT_ERROR;
	}
	if (! data)
	{
		return MCU_INVALID_ARGUMENT_ERROR;
	}

	VicoQuery query;
	// Break down to bytes
	quint8 startAddress1 = (addStart & 0xFF000000) >> 24;
	quint8 startAddress2 = (addStart & 0x00FF0000) >> 16;
	quint8 startAddress3 = (addStart & 0x0000FF00) >> 8;
	quint8 startAddress4 = (addStart & 0x000000FF);

	// Version, id, length, add_start, len, requestedDataLength, sentDataLength
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 0x01u, 0x05u, expectedRequestLength, 0, 132, startAddress4, startAddress3, startAddress2, startAddress1, data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7], data[8], data[9], data[10], data[11], data[12], data[13], data[14], data[15], data[16], data[17], data[18], data[19], data[20], data[21], data[22], data[23], data[24], data[25], data[26], data[27], data[28], data[29], data[30], data[31], data[32], data[33], data[34], data[35], data[36], data[37], data[38], data[39], data[40], data[41], data[42], data[43], data[44], data[45], data[46], data[47], data[48], data[49], data[50], data[51], data[52], data[53], data[54], data[55], data[56], data[57], data[58], data[59], data[60], data[61], data[62], data[63], data[64], data[65], data[66], data[67], data[68], data[69], data[70], data[71], data[72], data[73], data[74], data[75], data[76], data[77], data[78], data[79], data[80], data[81], data[82], data[83], data[84], data[85], data[86], data[87], data[88], data[89], data[90], data[91], data[92], data[93], data[94], data[95], data[96], data[97], data[98], data[99], data[100], data[101], data[102], data[103], data[104], data[105], data[106], data[107], data[108], data[109], data[110], data[111], data[112], data[113], data[114], data[115], data[116], data[117], data[118], data[119], data[120], data[121], data[122], data[123], data[124], data[125], data[126], data[127]);
	if (MCU_SUCCESS != getMcuRC(answer)) {
		return getMcuRC(answer);
	}
	answer.value(API_MCU_PROTOCOL_VERSION).toInt();
	return getMcuRC(answer);
}

MCUStatusType blGetSession(const CharType* serialNumber, BootloaderSessionType* blSession) {
	quint8 expectedResponseLength = 1;
	if (!serialNumber) {
		return MCU_INVALID_ARGUMENT_ERROR;
	}
	if (!blSession) {
		return MCU_INVALID_ARGUMENT_ERROR;
	}
	VicoQuery query;
	// VER, CIX, CL, requestedDataLength, variableDataSendLength
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 0x01u, 0x0Au, 0x05u, expectedResponseLength, 0);
	if (MCU_SUCCESS != getMcuRC(answer)) {
		return getMcuRC(answer);
	}
	answer.value(API_MCU_PROTOCOL_VERSION).toInt();

	QJsonArray data = answer.value(API_DATA).toArray();
	QJsonValue pairs = data.at(0);
	QVariantMap pairMap = pairs.toObject().toVariantMap();
	if(pairMap.size() != expectedResponseLength) {
		return MCUStatusType::MCU_RESPONSE_OUT_OF_BOUNDS_ERROR;
	} else {
		uint dataVal = pairMap.value("data0").toUInt();
		*blSession = (BootloaderSessionType) dataVal;
	}

	return getMcuRC(answer);
}

MCUStatusType blGetReason(const CharType* serialNumber, BootloaderReasonType* blReason) {
	quint8 expectedResponseLength = 1;
	if (!serialNumber) {
		return MCU_INVALID_ARGUMENT_ERROR;
	}
	if (!blReason) {
		return MCU_INVALID_ARGUMENT_ERROR;
	}
	VicoQuery query;
	// VER, CIX, CL, requestedDataLength, variableDataSendLength
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 0x01u, 0x0Bu, 0x05u, expectedResponseLength, 0);
	if (MCU_SUCCESS != getMcuRC(answer)) {
		return getMcuRC(answer);
	}
	answer.value(API_MCU_PROTOCOL_VERSION).toInt();

	QJsonArray data = answer.value(API_DATA).toArray();
	QJsonValue pairs = data.at(0);
	QVariantMap pairMap = pairs.toObject().toVariantMap();
	if(pairMap.size() != expectedResponseLength) {
		return MCUStatusType::MCU_RESPONSE_OUT_OF_BOUNDS_ERROR;
	} else {
		uint dataVal = pairMap.value("data0").toUInt();
		*blReason = (BootloaderReasonType) dataVal;
	}

	return getMcuRC(answer);
}

MCUStatusType swPkgStartApplication(const CharType* serialNumber) {
	if (!serialNumber) {
		return MCU_INVALID_ARGUMENT_ERROR;
	}

	VicoQuery query;
	// VER, CIX, CL, requestedDataLength, variableDataSendLength
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 0x01u, 0x0Eu, 0x05u, 0, 0);
	if (MCU_SUCCESS != getMcuRC(answer)) {
		return getMcuRC(answer);
	}
	answer.value(API_MCU_PROTOCOL_VERSION).toInt();
	return getMcuRC(answer);
}

MCUStatusType swPkgStartBootloader(const CharType* serialNumber) {
	if (!serialNumber) {
		return MCU_INVALID_ARGUMENT_ERROR;
	}

	VicoQuery query;
	// VER, CIX, CL, requestedDataLength, variableDataSendLength
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 0x01u, 0x0Fu, 0x05u, 0, 0);
	if (MCU_SUCCESS != getMcuRC(answer)) {
		return getMcuRC(answer);
	}
	answer.value(API_MCU_PROTOCOL_VERSION).toInt();
	return getMcuRC(answer);
}

MCUStatusType liveInfo1VICO(const CharType* serialNumber, LiveInfo1VICOType* liveInfo) {
	quint8 expectedResponseLength = 15;
	if (!serialNumber) {
		return MCU_INVALID_ARGUMENT_ERROR;
	}
	if (!liveInfo) {
		return MCU_INVALID_ARGUMENT_ERROR;
	}
	VicoQuery query;
	// VER, CIX, CL, requestedDataLength, variableDataSendLength
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 0x01u, 0x10u, 0x05u, expectedResponseLength, 0);
	if (MCU_SUCCESS != getMcuRC(answer)) {
		return getMcuRC(answer);
	}
	answer.value(API_MCU_PROTOCOL_VERSION).toInt();

	QJsonArray data = answer.value(API_DATA).toArray();
	QJsonValue pairs = data.at(0);
	QVariantMap pairMap = pairs.toObject().toVariantMap();
	if(pairMap.size() != expectedResponseLength) {
		return MCUStatusType::MCU_RESPONSE_OUT_OF_BOUNDS_ERROR;
	} else {
		MCUStatusType rc;
		liveInfo->st = (LiveInfoVICOStateType) pairMap.value("data0").toUInt();
		liveInfo->er = (LiveInfoVICOErrorType) pairMap.value("data1").toUInt();
		rc = convertBytesToFloat(&liveInfo->vIn, pairMap.value("data2").toUInt(), pairMap.value("data3").toUInt(), pairMap.value("data4").toUInt(), pairMap.value("data5").toUInt());
		if (rc != MCU_SUCCESS) return rc;
		rc = convertByteToBoolean(&liveInfo->pwr, pairMap.value("data6").toUInt());
		if (rc != MCU_SUCCESS) return rc;
		rc = convertBytesToFloat(&liveInfo->therm1, pairMap.value("data7").toUInt(), pairMap.value("data8").toUInt(), pairMap.value("data9").toUInt(), pairMap.value("data10").toUInt());
		if (rc != MCU_SUCCESS) return rc;
		rc = convertBytesToFloat(&liveInfo->therm2, pairMap.value("data11").toUInt(), pairMap.value("data12").toUInt(), pairMap.value("data13").toUInt(), pairMap.value("data14").toUInt());
		if (rc != MCU_SUCCESS) return rc;
	}
	return getMcuRC(answer);
}

MCUStatusType liveInfo2VICO(const CharType* serialNumber, LiveInfo2VICOType* liveInfo) {
	quint8 expectedResponseLength = 42;

	if (!serialNumber) {
		return MCU_INVALID_ARGUMENT_ERROR;
	}
	if (!liveInfo) {
		return MCU_INVALID_ARGUMENT_ERROR;
	}
	VicoQuery query;
	// VER, CIX, CL, requestedDataLength, variableDataSendLength
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 0x01u, 0x11u, 0x05u, expectedResponseLength, 0);
	if (MCU_SUCCESS != getMcuRC(answer)) {
		return getMcuRC(answer);
	}
	answer.value(API_MCU_PROTOCOL_VERSION).toInt();

	QJsonArray data = answer.value(API_DATA).toArray();
	QJsonValue pairs = data.at(0);
	QVariantMap pairMap = pairs.toObject().toVariantMap();
	if(pairMap.size() != expectedResponseLength) {
		return MCUStatusType::MCU_RESPONSE_OUT_OF_BOUNDS_ERROR;
	} else {
		MCUStatusType rc;
		liveInfo->st = (LiveInfoVICOStateType) pairMap.value("data0").toUInt();
		liveInfo->er = (LiveInfoVICOErrorType) pairMap.value("data1").toUInt();
		rc = convertBytesToFloat(&liveInfo->vIn, pairMap.value("data2").toUInt(), pairMap.value("data3").toUInt(), pairMap.value("data4").toUInt(), pairMap.value("data5").toUInt());
		if (rc != MCU_SUCCESS) return rc;
		rc = convertBytesToFloat(&liveInfo->p5v, pairMap.value("data6").toUInt(), pairMap.value("data7").toUInt(), pairMap.value("data8").toUInt(), pairMap.value("data9").toUInt());
		if (rc != MCU_SUCCESS) return rc;
		rc = convertByteToBoolean(&liveInfo->n5vActive, pairMap.value("data10").toUInt());
		if (rc != MCU_SUCCESS) return rc;
		rc = convertBytesToFloat(&liveInfo->mcu3v3, pairMap.value("data11").toUInt(), pairMap.value("data12").toUInt(), pairMap.value("data13").toUInt(), pairMap.value("data14").toUInt());
		if (rc != MCU_SUCCESS) return rc;
		rc = convertBytesToFloat(&liveInfo->ref2v5, pairMap.value("data15").toUInt(), pairMap.value("data16").toUInt(), pairMap.value("data17").toUInt(), pairMap.value("data18").toUInt());
		if (rc != MCU_SUCCESS) return rc;
		rc = convertByteToBoolean(&liveInfo->hvActive, pairMap.value("data19").toUInt());
		if (rc != MCU_SUCCESS) return rc;
		rc = convertBytesToUInt16(&liveInfo->hvDac, pairMap.value("data20").toUInt(), pairMap.value("data21").toUInt());
		if (rc != MCU_SUCCESS) return rc;
		rc = convertBytesToFloat(&liveInfo->hv, pairMap.value("data22").toUInt(), pairMap.value("data23").toUInt(), pairMap.value("data24").toUInt(), pairMap.value("data25").toUInt());
		if (rc != MCU_SUCCESS) return rc;
		rc = convertByteToBoolean(&liveInfo->pwr, pairMap.value("data26").toUInt());
		if (rc != MCU_SUCCESS) return rc;
		rc = convertByteToBoolean(&liveInfo->usb, pairMap.value("data27").toUInt());
		if (rc != MCU_SUCCESS) return rc;
		rc = convertByteToBoolean(&liveInfo->gpio, pairMap.value("data28").toUInt());
		if (rc != MCU_SUCCESS) return rc;
		rc = convertByteToBoolean(&liveInfo->reqfbl, pairMap.value("data29").toUInt());
		if (rc != MCU_SUCCESS) return rc;
		rc = convertBytesToFloat(&liveInfo->fpga3v3, pairMap.value("data30").toUInt(), pairMap.value("data31").toUInt(), pairMap.value("data32").toUInt(), pairMap.value("data33").toUInt());
		if (rc != MCU_SUCCESS) return rc;
		rc = convertBytesToFloat(&liveInfo->therm1, pairMap.value("data34").toUInt(), pairMap.value("data35").toUInt(), pairMap.value("data36").toUInt(), pairMap.value("data37").toUInt());
		if (rc != MCU_SUCCESS) return rc;
		rc = convertBytesToFloat(&liveInfo->therm2, pairMap.value("data38").toUInt(), pairMap.value("data39").toUInt(), pairMap.value("data40").toUInt(), pairMap.value("data41").toUInt());
		if (rc != MCU_SUCCESS) return rc;
	}
	return getMcuRC(answer);
}

MCUStatusType liveInfoBoundariesVICO(const CharType* serialNumber, LiveInfoBoundariesVICOType* liveInfo) {
	quint8 expectedResponseLength = 48;
	if (!serialNumber) {
		return MCU_INVALID_ARGUMENT_ERROR;
	}
	if (!liveInfo) {
		return MCU_INVALID_ARGUMENT_ERROR;
	}
	VicoQuery query;
	// VER, CIX, CL, requestedDataLength, variableDataSendLength
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 0x01u, 0x12u, 0x05u, expectedResponseLength, 0);
	if (MCU_SUCCESS != getMcuRC(answer)) {
		return getMcuRC(answer);
	}
	answer.value(API_MCU_PROTOCOL_VERSION).toInt();

	QJsonArray data = answer.value(API_DATA).toArray();
	QJsonValue pairs = data.at(0);
	QVariantMap pairMap = pairs.toObject().toVariantMap();
	if(pairMap.size() != expectedResponseLength) {
		return MCUStatusType::MCU_RESPONSE_OUT_OF_BOUNDS_ERROR;
	} else {
		MCUStatusType rc;
		rc = convertBytesToFloat(&liveInfo->vInMin, pairMap.value("data0").toUInt(), pairMap.value("data1").toUInt(), pairMap.value("data2").toUInt(), pairMap.value("data3").toUInt());
		if (rc != MCU_SUCCESS) return rc;
		rc = convertBytesToFloat(&liveInfo->vInMax, pairMap.value("data4").toUInt(), pairMap.value("data5").toUInt(), pairMap.value("data6").toUInt(), pairMap.value("data7").toUInt());
		if (rc != MCU_SUCCESS) return rc;
		rc = convertBytesToFloat(&liveInfo->p5vMin, pairMap.value("data8").toUInt(), pairMap.value("data9").toUInt(), pairMap.value("data10").toUInt(), pairMap.value("data11").toUInt());
		if (rc != MCU_SUCCESS) return rc;
		rc = convertBytesToFloat(&liveInfo->p5vMax, pairMap.value("data12").toUInt(), pairMap.value("data13").toUInt(), pairMap.value("data14").toUInt(), pairMap.value("data15").toUInt());
		if (rc != MCU_SUCCESS) return rc;
		rc = convertBytesToFloat(&liveInfo->mcu3v3Min, pairMap.value("data16").toUInt(), pairMap.value("data17").toUInt(), pairMap.value("data18").toUInt(), pairMap.value("data19").toUInt());
		if (rc != MCU_SUCCESS) return rc;
		rc = convertBytesToFloat(&liveInfo->mcu3v3Max, pairMap.value("data20").toUInt(), pairMap.value("data21").toUInt(), pairMap.value("data22").toUInt(), pairMap.value("data23").toUInt());
		if (rc != MCU_SUCCESS) return rc;
		rc = convertBytesToFloat(&liveInfo->ref2v5Min, pairMap.value("data24").toUInt(), pairMap.value("data25").toUInt(), pairMap.value("data26").toUInt(), pairMap.value("data27").toUInt());
		if (rc != MCU_SUCCESS) return rc;
		rc = convertBytesToFloat(&liveInfo->ref2v5Max, pairMap.value("data28").toUInt(), pairMap.value("data29").toUInt(), pairMap.value("data30").toUInt(), pairMap.value("data31").toUInt());
		if (rc != MCU_SUCCESS) return rc;
		rc = convertBytesToFloat(&liveInfo->hvMin, pairMap.value("data32").toUInt(), pairMap.value("data33").toUInt(), pairMap.value("data34").toUInt(), pairMap.value("data35").toUInt());
		if (rc != MCU_SUCCESS) return rc;
		rc = convertBytesToFloat(&liveInfo->hvMax, pairMap.value("data36").toUInt(), pairMap.value("data37").toUInt(), pairMap.value("data38").toUInt(), pairMap.value("data39").toUInt());
		if (rc != MCU_SUCCESS) return rc;
		rc = convertBytesToFloat(&liveInfo->therm1Max, pairMap.value("data40").toUInt(), pairMap.value("data41").toUInt(), pairMap.value("data42").toUInt(), pairMap.value("data43").toUInt());
		if (rc != MCU_SUCCESS) return rc;
		rc = convertBytesToFloat(&liveInfo->therm2Max, pairMap.value("data44").toUInt(), pairMap.value("data45").toUInt(), pairMap.value("data46").toUInt(), pairMap.value("data47").toUInt());
		if (rc != MCU_SUCCESS) return rc;
	}
	return getMcuRC(answer);
}

MCUStatusType liveInfo1VIAMP(const CharType* serialNumber, LiveInfo1VIAMPType* liveInfo) {
	quint8 expectedResponseLength = 19;
	if (!serialNumber) {
		return MCU_INVALID_ARGUMENT_ERROR;
	}
	if (!liveInfo) {
		return MCU_INVALID_ARGUMENT_ERROR;
	}
	VicoQuery query;
	// VER, CIX, CL, requestedDataLength, variableDataSendLength
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 0x01u, 0x15u, 0x05u, expectedResponseLength, 0);
	if (MCU_SUCCESS != getMcuRC(answer)) {
		return getMcuRC(answer);
	}
	answer.value(API_MCU_PROTOCOL_VERSION).toInt();

	QJsonArray data = answer.value(API_DATA).toArray();
	QJsonValue pairs = data.at(0);
	QVariantMap pairMap = pairs.toObject().toVariantMap();
	if(pairMap.size() != expectedResponseLength) {
		return MCUStatusType::MCU_RESPONSE_OUT_OF_BOUNDS_ERROR;
	} else {
		MCUStatusType rc;
		liveInfo->st = (LiveInfoVIAMPStateType) pairMap.value("data0").toUInt();
		liveInfo->er = (LiveInfoVIAMPErrorType) pairMap.value("data1").toUInt();
		rc = convertBytesToFloat(&liveInfo->itec, pairMap.value("data2").toUInt(), pairMap.value("data3").toUInt(), pairMap.value("data4").toUInt(), pairMap.value("data5").toUInt());
		if (rc != MCU_SUCCESS) return rc;
		rc = convertBytesToFloat(&liveInfo->utec, pairMap.value("data6").toUInt(), pairMap.value("data7").toUInt(), pairMap.value("data8").toUInt(), pairMap.value("data9").toUInt());
		if (rc != MCU_SUCCESS) return rc;
		rc = convertBytesToFloat(&liveInfo->sddTmp, pairMap.value("data10").toUInt(), pairMap.value("data11").toUInt(), pairMap.value("data12").toUInt(), pairMap.value("data13").toUInt());
		if (rc != MCU_SUCCESS) return rc;
		rc = convertByteToBoolean(&liveInfo->rdy, pairMap.value("data14").toUInt());
		if (rc != MCU_SUCCESS) return rc;
		rc = convertBytesToFloat(&liveInfo->hotSide, pairMap.value("data15").toUInt(), pairMap.value("data16").toUInt(), pairMap.value("data17").toUInt(), pairMap.value("data18").toUInt());
		if (rc != MCU_SUCCESS) return rc;
	}
	return getMcuRC(answer);
}

MCUStatusType liveInfo2VIAMP(const CharType* serialNumber, LiveInfo2VIAMPType* liveInfo) {
	quint8 expectedResponseLength = 64;
	if (!serialNumber) {
		return MCU_INVALID_ARGUMENT_ERROR;
	}
	if (!liveInfo) {
		return MCU_INVALID_ARGUMENT_ERROR;
	}
	VicoQuery query;
	// VER, CIX, CL, requestedDataLength, variableDataSendLength
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 0x01u, 0x16u, 0x05u, expectedResponseLength, 0);
	if (MCU_SUCCESS != getMcuRC(answer)) {
		return getMcuRC(answer);
	}
	answer.value(API_MCU_PROTOCOL_VERSION).toInt();

	QJsonArray data = answer.value(API_DATA).toArray();
	QJsonValue pairs = data.at(0);
	QVariantMap pairMap = pairs.toObject().toVariantMap();
	if(pairMap.size() != expectedResponseLength) {
		return MCUStatusType::MCU_RESPONSE_OUT_OF_BOUNDS_ERROR;
	} else {
		MCUStatusType rc;
		liveInfo->st = (LiveInfoVIAMPStateType) pairMap.value("data0").toUInt();
		liveInfo->er = (LiveInfoVIAMPErrorType) pairMap.value("data1").toUInt();
		rc = convertBytesToFloat(&liveInfo->viampAdc, pairMap.value("data2").toUInt(), pairMap.value("data3").toUInt(), pairMap.value("data4").toUInt(), pairMap.value("data5").toUInt());
		if (rc != MCU_SUCCESS) return rc;
		rc = convertBytesToFloat(&liveInfo->r1, pairMap.value("data6").toUInt(), pairMap.value("data7").toUInt(), pairMap.value("data8").toUInt(), pairMap.value("data9").toUInt());
		if (rc != MCU_SUCCESS) return rc;
		rc = convertBytesToFloat(&liveInfo->bk, pairMap.value("data10").toUInt(), pairMap.value("data11").toUInt(), pairMap.value("data12").toUInt(), pairMap.value("data13").toUInt());
		if (rc != MCU_SUCCESS) return rc;
		rc = convertBytesToFloat(&liveInfo->rx, pairMap.value("data14").toUInt(), pairMap.value("data15").toUInt(), pairMap.value("data16").toUInt(), pairMap.value("data17").toUInt());
		if (rc != MCU_SUCCESS) return rc;
		rc = convertBytesToFloat(&liveInfo->itec, pairMap.value("data18").toUInt(), pairMap.value("data19").toUInt(), pairMap.value("data20").toUInt(), pairMap.value("data21").toUInt());
		if (rc != MCU_SUCCESS) return rc;
		rc = convertBytesToFloat(&liveInfo->utec, pairMap.value("data22").toUInt(), pairMap.value("data23").toUInt(), pairMap.value("data24").toUInt(), pairMap.value("data25").toUInt());
		if (rc != MCU_SUCCESS) return rc;
		rc = convertBytesToFloat(&liveInfo->sddTmp, pairMap.value("data26").toUInt(), pairMap.value("data27").toUInt(), pairMap.value("data28").toUInt(), pairMap.value("data29").toUInt());
		if (rc != MCU_SUCCESS) return rc;
		rc = convertBytesToFloat(&liveInfo->targetTmp, pairMap.value("data30").toUInt(), pairMap.value("data31").toUInt(), pairMap.value("data32").toUInt(), pairMap.value("data33").toUInt());
		if (rc != MCU_SUCCESS) return rc;
		rc = convertByteToBoolean(&liveInfo->rdy, pairMap.value("data34").toUInt());
		if (rc != MCU_SUCCESS) return rc;
		rc = convertByteToBoolean(&liveInfo->ardy, pairMap.value("data35").toUInt());
		if (rc != MCU_SUCCESS) return rc;
		rc = convertBytesToFloat(&liveInfo->hotSide, pairMap.value("data36").toUInt(), pairMap.value("data37").toUInt(), pairMap.value("data38").toUInt(), pairMap.value("data39").toUInt());
		if (rc != MCU_SUCCESS) return rc;
		rc = convertBytesToFloat(&liveInfo->monSigFinal, pairMap.value("data40").toUInt(), pairMap.value("data41").toUInt(), pairMap.value("data42").toUInt(), pairMap.value("data43").toUInt());
		if (rc != MCU_SUCCESS) return rc;
		rc = convertBytesToFloat(&liveInfo->ctrlSigFinal, pairMap.value("data44").toUInt(), pairMap.value("data45").toUInt(), pairMap.value("data46").toUInt(), pairMap.value("data47").toUInt());
		if (rc != MCU_SUCCESS) return rc;
		rc = convertByteToBoolean(&liveInfo->iPartLimit, pairMap.value("data48").toUInt());
		if (rc != MCU_SUCCESS) return rc;
		rc = convertByteToBoolean(&liveInfo->tecActive, pairMap.value("data49").toUInt());
		if (rc != MCU_SUCCESS) return rc;
		rc = convertBytesToUInt16(&liveInfo->tecDac, pairMap.value("data50").toUInt(), pairMap.value("data51").toUInt());
		if (rc != MCU_SUCCESS) return rc;
		rc = convertBytesToFloat(&liveInfo->pPart, pairMap.value("data52").toUInt(), pairMap.value("data53").toUInt(), pairMap.value("data54").toUInt(), pairMap.value("data55").toUInt());
		if (rc != MCU_SUCCESS) return rc;
		rc = convertBytesToFloat(&liveInfo->iPart, pairMap.value("data56").toUInt(), pairMap.value("data57").toUInt(), pairMap.value("data58").toUInt(), pairMap.value("data59").toUInt());
		if (rc != MCU_SUCCESS) return rc;
		rc = convertBytesToFloat(&liveInfo->dPart, pairMap.value("data60").toUInt(), pairMap.value("data61").toUInt(), pairMap.value("data62").toUInt(), pairMap.value("data63").toUInt());
		if (rc != MCU_SUCCESS) return rc;
	}
	return getMcuRC(answer);
}

MCUStatusType liveInfoBoundariesVIAMP(const CharType* serialNumber, LiveInfoBoundariesVIAMPType* liveInfo) {
	quint8 expectedResponseLength = 52;
	if (!serialNumber) {
		return MCU_INVALID_ARGUMENT_ERROR;
	}
	if (!liveInfo) {
		return MCU_INVALID_ARGUMENT_ERROR;
	}
	VicoQuery query;
	// VER, CIX, CL, requestedDataLength, variableDataSendLength
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 0x01u, 0x17u, 0x05u, expectedResponseLength, 0);
	if (MCU_SUCCESS != getMcuRC(answer)) {
		return getMcuRC(answer);
	}
	answer.value(API_MCU_PROTOCOL_VERSION).toInt();

	QJsonArray data = answer.value(API_DATA).toArray();
	QJsonValue pairs = data.at(0);
	QVariantMap pairMap = pairs.toObject().toVariantMap();
	if(pairMap.size() != expectedResponseLength) {
		return MCUStatusType::MCU_RESPONSE_OUT_OF_BOUNDS_ERROR;
	} else {
		MCUStatusType rc;
		rc = convertBytesToFloat(&liveInfo->viampAdcMin, pairMap.value("data0").toUInt(), pairMap.value("data1").toUInt(), pairMap.value("data2").toUInt(), pairMap.value("data3").toUInt());
		if (rc != MCU_SUCCESS) return rc;
		rc = convertBytesToFloat(&liveInfo->viampAdcMax, pairMap.value("data4").toUInt(), pairMap.value("data5").toUInt(), pairMap.value("data6").toUInt(), pairMap.value("data7").toUInt());
		if (rc != MCU_SUCCESS) return rc;
		rc = convertBytesToFloat(&liveInfo->r1Min, pairMap.value("data8").toUInt(), pairMap.value("data9").toUInt(), pairMap.value("data10").toUInt(), pairMap.value("data11").toUInt());
		if (rc != MCU_SUCCESS) return rc;
		rc = convertBytesToFloat(&liveInfo->r1Max, pairMap.value("data12").toUInt(), pairMap.value("data13").toUInt(), pairMap.value("data14").toUInt(), pairMap.value("data15").toUInt());
		if (rc != MCU_SUCCESS) return rc;
		rc = convertBytesToFloat(&liveInfo->bkMin, pairMap.value("data16").toUInt(), pairMap.value("data17").toUInt(), pairMap.value("data18").toUInt(), pairMap.value("data19").toUInt());
		if (rc != MCU_SUCCESS) return rc;
		rc = convertBytesToFloat(&liveInfo->bkMax, pairMap.value("data20").toUInt(), pairMap.value("data21").toUInt(), pairMap.value("data22").toUInt(), pairMap.value("data23").toUInt());
		if (rc != MCU_SUCCESS) return rc;
		rc = convertBytesToFloat(&liveInfo->rxMin, pairMap.value("data24").toUInt(), pairMap.value("data25").toUInt(), pairMap.value("data26").toUInt(), pairMap.value("data27").toUInt());
		if (rc != MCU_SUCCESS) return rc;
		rc = convertBytesToFloat(&liveInfo->rxMax, pairMap.value("data28").toUInt(), pairMap.value("data29").toUInt(), pairMap.value("data30").toUInt(), pairMap.value("data31").toUInt());
		if (rc != MCU_SUCCESS) return rc;
		rc = convertBytesToFloat(&liveInfo->itecMax, pairMap.value("data32").toUInt(), pairMap.value("data33").toUInt(), pairMap.value("data34").toUInt(), pairMap.value("data35").toUInt());
		if (rc != MCU_SUCCESS) return rc;
		rc = convertBytesToFloat(&liveInfo->utecMax, pairMap.value("data36").toUInt(), pairMap.value("data37").toUInt(), pairMap.value("data38").toUInt(), pairMap.value("data39").toUInt());
		if (rc != MCU_SUCCESS) return rc;
		rc = convertBytesToFloat(&liveInfo->kp, pairMap.value("data40").toUInt(), pairMap.value("data41").toUInt(), pairMap.value("data42").toUInt(), pairMap.value("data43").toUInt());
		if (rc != MCU_SUCCESS) return rc;
		rc = convertBytesToFloat(&liveInfo->ki, pairMap.value("data44").toUInt(), pairMap.value("data45").toUInt(), pairMap.value("data46").toUInt(), pairMap.value("data47").toUInt());
		if (rc != MCU_SUCCESS) return rc;
		rc = convertBytesToFloat(&liveInfo->kd, pairMap.value("data48").toUInt(), pairMap.value("data49").toUInt(), pairMap.value("data50").toUInt(), pairMap.value("data51").toUInt());
		if (rc != MCU_SUCCESS) return rc;
	}
	return getMcuRC(answer);
}

MCUStatusType devInfo1Bootloader(const CharType* serialNumber, DevInfo1BootloaderType* devInfo) {
	quint8 expectedResponseLength = 5;
	if (!serialNumber) {
		return MCU_INVALID_ARGUMENT_ERROR;
	}
	if (!devInfo) {
		return MCU_INVALID_ARGUMENT_ERROR;
	}
	VicoQuery query;
	// VER, CIX, CL, requestedDataLength, variableDataSendLength
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 0x01u, 0x19u, 0x05u, expectedResponseLength, 0);
	if (MCU_SUCCESS != getMcuRC(answer)) {
		return getMcuRC(answer);
	}
	answer.value(API_MCU_PROTOCOL_VERSION).toInt();

	QJsonArray data = answer.value(API_DATA).toArray();
	QJsonValue pairs = data.at(0);
	QVariantMap pairMap = pairs.toObject().toVariantMap();
	if(pairMap.size() != expectedResponseLength) {
		return MCUStatusType::MCU_RESPONSE_OUT_OF_BOUNDS_ERROR;
	} else {
		MCUStatusType rc;
		devInfo->smj = pairMap.value("data0").toUInt();
		devInfo->smi = pairMap.value("data1").toUInt();
		devInfo->sms = pairMap.value("data2").toUInt();
		rc = convertBytesToUInt16(&devInfo->smb, pairMap.value("data4").toUInt(), pairMap.value("data3").toUInt());
		if (rc != MCU_SUCCESS) return rc;
	}
	return getMcuRC(answer);
}

MCUStatusType devInfo1VICO(const CharType* serialNumber, DevInfo1VICOType* devInfo) {
	quint8 expectedResponseLength = 5;
	if (!serialNumber) {
		return MCU_INVALID_ARGUMENT_ERROR;
	}
	if (!devInfo) {
		return MCU_INVALID_ARGUMENT_ERROR;
	}
	VicoQuery query;
	// VER, CIX, CL, requestedDataLength, variableDataSendLength
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 0x01u, 0x1Au, 0x05u, expectedResponseLength, 0);
	if (MCU_SUCCESS != getMcuRC(answer)) {
		return getMcuRC(answer);
	}
	answer.value(API_MCU_PROTOCOL_VERSION).toInt();

	QJsonArray data = answer.value(API_DATA).toArray();
	QJsonValue pairs = data.at(0);
	QVariantMap pairMap = pairs.toObject().toVariantMap();
	if(pairMap.size() != expectedResponseLength) {
		return MCUStatusType::MCU_RESPONSE_OUT_OF_BOUNDS_ERROR;
	} else {
		MCUStatusType rc;
		devInfo->smj = pairMap.value("data0").toUInt();
		devInfo->smi = pairMap.value("data1").toUInt();
		devInfo->sms = pairMap.value("data2").toUInt();
		rc = convertBytesToUInt16(&devInfo->smb, pairMap.value("data3").toUInt(), pairMap.value("data4").toUInt());
		if (rc != MCU_SUCCESS) return rc;
	}
	return getMcuRC(answer);
}

MCUStatusType devInfo2VICO(const CharType* serialNumber, const UInt8Type infoSize, CharType* voPcbArtNo, CharType* voPcbSerNo, CharType* voProdArtNo, CharType* voProdSerNo) {
	quint8 expectedResponseLength = 84;
	if (!serialNumber) {
		return MCU_INVALID_ARGUMENT_ERROR;
	}
	if (!voPcbArtNo || !voPcbSerNo || !voProdArtNo || !voProdSerNo) {
		return MCU_INVALID_ARGUMENT_ERROR;
	}
	VicoQuery query;
	// VER, CIX, CL, requestedDataLength, variableDataSendLength
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 0x01u, 0x1Bu, 0x05u, expectedResponseLength, 0);
	if (MCU_SUCCESS != getMcuRC(answer)) {
		return getMcuRC(answer);
	}
	answer.value(API_MCU_PROTOCOL_VERSION).toInt();

	QJsonArray data = answer.value(API_DATA).toArray();
	QJsonValue pairs = data.at(0);
	QVariantMap pairMap = pairs.toObject().toVariantMap();
	if(pairMap.size() != expectedResponseLength) {
		return MCUStatusType::MCU_RESPONSE_OUT_OF_BOUNDS_ERROR;
	} else {
		MCUStatusType rc;
		rc = convertBytesToString(voPcbArtNo, infoSize, pairMap, 0, 20);
		if (rc != MCU_SUCCESS) return rc;
		rc = convertBytesToString(voPcbSerNo, infoSize, pairMap, 21, 41);
		if (rc != MCU_SUCCESS) return rc;
		rc = convertBytesToString(voProdArtNo, infoSize, pairMap, 42, 62);
		if (rc != MCU_SUCCESS) return rc;
		rc = convertBytesToString(voProdSerNo, infoSize, pairMap, 63, 83);
		if (rc != MCU_SUCCESS) return rc;
	}
	return getMcuRC(answer);
}

MCUStatusType devInfo1VIAMP(const CharType* serialNumber, const UInt8Type infoSize, CharType* vpPcbArtNo, CharType* vpPcbSerNo, CharType* vpProdArtNo, CharType* vpProdSerNo, FloatType* targetTmpEep) {
	quint8 expectedResponseLength = 88;
	if (!serialNumber) {
		return MCU_INVALID_ARGUMENT_ERROR;
	}
	if (!vpPcbArtNo || !vpPcbSerNo || !vpProdArtNo || !vpProdSerNo || !targetTmpEep) {
		return MCU_INVALID_ARGUMENT_ERROR;
	}
	VicoQuery query;
	// VER, CIX, CL, requestedDataLength, variableDataSendLength
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 0x01u, 0x1Du, 0x05u, expectedResponseLength, 0);
	if (MCU_SUCCESS != getMcuRC(answer)) {
		return getMcuRC(answer);
	}
	answer.value(API_MCU_PROTOCOL_VERSION).toInt();

	QJsonArray data = answer.value(API_DATA).toArray();
	QJsonValue pairs = data.at(0);
	QVariantMap pairMap = pairs.toObject().toVariantMap();
	if(pairMap.size() != expectedResponseLength) {
		return MCUStatusType::MCU_RESPONSE_OUT_OF_BOUNDS_ERROR;
	} else {
		MCUStatusType rc;
		rc = convertBytesToString(vpPcbArtNo, infoSize, pairMap, 0, 20);
		if (rc != MCU_SUCCESS) return rc;
		rc = convertBytesToString(vpPcbSerNo, infoSize, pairMap, 21, 41);
		if (rc != MCU_SUCCESS) return rc;
		rc = convertBytesToString(vpProdArtNo, infoSize, pairMap, 42, 62);
		if (rc != MCU_SUCCESS) return rc;
		rc = convertBytesToString(vpProdSerNo, infoSize, pairMap, 63, 83);
		if (rc != MCU_SUCCESS) return rc;
		rc = convertBytesToFloat(targetTmpEep, pairMap.value("data84").toUInt(), pairMap.value("data85").toUInt(), pairMap.value("data86").toUInt(), pairMap.value("data87").toUInt());
		if (rc != MCU_SUCCESS) return rc;
	}
	return getMcuRC(answer);
}

MCUStatusType setMode(const CharType* serialNumber, ModeType md)
{
	quint8 cl = 5+1;
	if (!serialNumber) {
		return MCU_INVALID_ARGUMENT_ERROR;
	}
	VicoQuery query;
	// Version, id, length, add_start, len, requestedDataLength, sentDataLength
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 0x01u, 0x20u, cl, 0, 1, md);
	if (MCU_SUCCESS != getMcuRC(answer)) {
		return getMcuRC(answer);
	}
	answer.value(API_MCU_PROTOCOL_VERSION).toInt();
	return getMcuRC(answer);
}

MCUStatusType resetMCU(const CharType* serialNumber)
{
	if (!serialNumber) {
		return MCU_INVALID_ARGUMENT_ERROR;
	}
	VicoQuery query;
	// Version, id, length, add_start, len, requestedDataLength, sentDataLength
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 0x01u, 0x25u, 0x05u, 0, 0);
	if (MCU_SUCCESS != getMcuRC(answer)) {
		return getMcuRC(answer);
	}
	answer.value(API_MCU_PROTOCOL_VERSION).toInt();
	return getMcuRC(answer);
}

MCUStatusType resetFPGA(const CharType* serialNumber)
{
	if (!serialNumber) {
		return MCU_INVALID_ARGUMENT_ERROR;
	}
	VicoQuery query;
	// Version, id, length, add_start, len, requestedDataLength, sentDataLength
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 0x01u, 0x26u, 0x05u, 0, 0);
	if (MCU_SUCCESS != getMcuRC(answer)) {
		return getMcuRC(answer);
	}
	answer.value(API_MCU_PROTOCOL_VERSION).toInt();
	return getMcuRC(answer);
}

MCUStatusType getTemp(const CharType* serialNumber, TempType* temp) {
	quint8 expectedResponseLength = 10;
	if (!serialNumber) {
		return MCU_INVALID_ARGUMENT_ERROR;
	}
	if (!temp) {
		return MCU_INVALID_ARGUMENT_ERROR;
	}

	VicoQuery query;
	// VER, CIX, CL, requestedDataLength, variableDataSendLength
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 0x01u, 0x30u, 0x05u, expectedResponseLength, 0);
	if (MCU_SUCCESS != getMcuRC(answer)) {
		return getMcuRC(answer);
	}
	answer.value(API_MCU_PROTOCOL_VERSION).toInt();

	QJsonArray data = answer.value(API_DATA).toArray();
	QJsonValue pairs = data.at(0);
	QVariantMap pairMap = pairs.toObject().toVariantMap();
	if(pairMap.size() != expectedResponseLength) {
		return MCUStatusType::MCU_RESPONSE_OUT_OF_BOUNDS_ERROR;
	} else {
		MCUStatusType rc;
		rc = convertBytesToFloat(&temp->sddTmp, pairMap.value("data0").toUInt(), pairMap.value("data1").toUInt(), pairMap.value("data2").toUInt(), pairMap.value("data3").toUInt());
		if (rc != MCU_SUCCESS) return rc;
		rc = convertBytesToFloat(&temp->targetTmp, pairMap.value("data4").toUInt(), pairMap.value("data5").toUInt(), pairMap.value("data6").toUInt(), pairMap.value("data7").toUInt());
		if (rc != MCU_SUCCESS) return rc;
		rc = convertByteToBoolean(&temp->rdy, pairMap.value("data8").toUInt());
		if (rc != MCU_SUCCESS) return rc;
		rc = convertByteToBoolean(&temp->ardy, pairMap.value("data9").toUInt());
		if (rc != MCU_SUCCESS) return rc;
	}
	return getMcuRC(answer);
}

MCUStatusType setTemp(const CharType* serialNumber, FloatType targetTmp)
{
	quint8 cl = 5+4;
	if (!serialNumber) {
		return MCU_INVALID_ARGUMENT_ERROR;
	}
	VicoQuery query;
	// Break down to bytes
	uchar byteArray[4] = {0,0,0,0};
	memcpy(&byteArray, &targetTmp, sizeof(targetTmp));
	// Version, id, length, crc, add_start, len, requestedDataLength
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 0x01u, 0x31u, cl, 0, 4, byteArray[0], byteArray[1], byteArray[2], byteArray[3]);
	if (MCU_SUCCESS != getMcuRC(answer)) {
		return getMcuRC(answer);
	}
	answer.value(API_MCU_PROTOCOL_VERSION).toInt();
	return getMcuRC(answer);
}

MCUStatusType setRdy(const CharType* serialNumber, FloatType dvtn, FloatType prd)
{
	quint8 cl = 5+4+4;
	if (!serialNumber) {
		return MCU_INVALID_ARGUMENT_ERROR;
	}
	VicoQuery query;
	// Break down to bytes
	uchar dvtnBytes[4] = {0,0,0,0};
	memcpy(&dvtnBytes, &dvtn, sizeof(dvtn));
	uchar prdBytes[4] = {0,0,0,0};
	memcpy(&prdBytes, &prd, sizeof(prd));
	// Version, id, length, crc, add_start, len, requestedDataLength
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 0x01u, 0x36u, cl, 0, 8, dvtnBytes[0], dvtnBytes[1], dvtnBytes[2], dvtnBytes[3], prdBytes[0], prdBytes[1], prdBytes[2], prdBytes[3]);
	if (MCU_SUCCESS != getMcuRC(answer)) {
		return getMcuRC(answer);
	}
	answer.value(API_MCU_PROTOCOL_VERSION).toInt();
	return getMcuRC(answer);
}

MCUStatusType setARdy(const CharType* serialNumber, FloatType dvtn, FloatType prd)
{
	quint8 cl = 5+4+4;
	if (!serialNumber) {
		return MCU_INVALID_ARGUMENT_ERROR;
	}
	VicoQuery query;
	// Break down to bytes
	uchar dvtnBytes[4] = {0,0,0,0};
	memcpy(&dvtnBytes, &dvtn, sizeof(dvtn));
	uchar prdBytes[4] = {0,0,0,0};
	memcpy(&prdBytes, &prd, sizeof(prd));
	// Version, id, length, crc, add_start, len, requestedDataLength
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 0x01u, 0x37u, cl, 0, 8, dvtnBytes[0], dvtnBytes[1], dvtnBytes[2], dvtnBytes[3], prdBytes[0], prdBytes[1], prdBytes[2], prdBytes[3]);
	if (MCU_SUCCESS != getMcuRC(answer)) {
		return getMcuRC(answer);
	}
	answer.value(API_MCU_PROTOCOL_VERSION).toInt();
	return getMcuRC(answer);
}

MCUStatusType getRdy(const CharType* serialNumber, FloatType* dvtn, FloatType* prd) {
	quint8 expectedResponseLength = 8;
	if (!serialNumber) {
		return MCU_INVALID_ARGUMENT_ERROR;
	}
	if (!dvtn) {
		return MCU_INVALID_ARGUMENT_ERROR;
	}
	if (!prd) {
		return MCU_INVALID_ARGUMENT_ERROR;
	}
	VicoQuery query;
	// VER, CIX, CL, requestedDataLength, variableDataSendLength
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 0x01u, 0x38u, 0x05u, expectedResponseLength, 0);
	if (MCU_SUCCESS != getMcuRC(answer)) {
		return getMcuRC(answer);
	}
	answer.value(API_MCU_PROTOCOL_VERSION).toInt();

	QJsonArray data = answer.value(API_DATA).toArray();
	QJsonValue pairs = data.at(0);
	QVariantMap pairMap = pairs.toObject().toVariantMap();
	if(pairMap.size() != expectedResponseLength) {
		return MCUStatusType::MCU_RESPONSE_OUT_OF_BOUNDS_ERROR;
	} else {
		MCUStatusType rc;
		rc = convertBytesToFloat(dvtn, pairMap.value("data0").toUInt(), pairMap.value("data1").toUInt(), pairMap.value("data2").toUInt(), pairMap.value("data3").toUInt());
		if (rc != MCU_SUCCESS) return rc;
		rc = convertBytesToFloat(prd, pairMap.value("data4").toUInt(), pairMap.value("data5").toUInt(), pairMap.value("data6").toUInt(), pairMap.value("data7").toUInt());
		if (rc != MCU_SUCCESS) return rc;
	}
	return getMcuRC(answer);
}

MCUStatusType getARdy(const CharType* serialNumber, FloatType* dvtn, FloatType* prd) {
	quint8 expectedResponseLength = 8;
	if (!serialNumber) {
		return MCU_INVALID_ARGUMENT_ERROR;
	}
	if (!dvtn) {
		return MCU_INVALID_ARGUMENT_ERROR;
	}
	if (!prd) {
		return MCU_INVALID_ARGUMENT_ERROR;
	}
	VicoQuery query;
	// VER, CIX, CL, requestedDataLength, variableDataSendLength
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 0x01u, 0x39u, 0x05u, expectedResponseLength, 0);
	if (MCU_SUCCESS != getMcuRC(answer)) {
		return getMcuRC(answer);
	}
	answer.value(API_MCU_PROTOCOL_VERSION).toInt();

	QJsonArray data = answer.value(API_DATA).toArray();
	QJsonValue pairs = data.at(0);
	QVariantMap pairMap = pairs.toObject().toVariantMap();
	if(pairMap.size() != expectedResponseLength) {
		return MCUStatusType::MCU_RESPONSE_OUT_OF_BOUNDS_ERROR;
	} else {
		MCUStatusType rc;
		rc = convertBytesToFloat(dvtn, pairMap.value("data0").toUInt(), pairMap.value("data1").toUInt(), pairMap.value("data2").toUInt(), pairMap.value("data3").toUInt());
		if (rc != MCU_SUCCESS) return rc;
		rc = convertBytesToFloat(prd, pairMap.value("data4").toUInt(), pairMap.value("data5").toUInt(), pairMap.value("data6").toUInt(), pairMap.value("data7").toUInt());
		if (rc != MCU_SUCCESS) return rc;
	}
	return getMcuRC(answer);
}

MCUStatusType getEEP(const CharType* serialNumber, UInt16Type addStart, UInt8Type len, UInt8Type* data) {
	if (len > 249) {
		return MCU_INVALID_ARGUMENT_ERROR;
	}
	if (!serialNumber) {
		return MCU_INVALID_ARGUMENT_ERROR;
	}
	if (! data)
	{
		return MCU_INVALID_ARGUMENT_ERROR;
	}

	// Break down to bytes
	quint8 startAddress1 = (addStart & 0x0000FF00) >> 8;
	quint8 startAddress2 = (addStart & 0x000000FF);

	VicoQuery query;
	// Version, id, length, crc, add_start, len, requestedDataLength
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 0x01u, 0x040u, 0x08u, len, 3, startAddress2, startAddress1, len);
	if (MCU_SUCCESS != getMcuRC(answer)) {
		return getMcuRC(answer);
	}
	answer.value(API_MCU_PROTOCOL_VERSION).toInt();

	QJsonArray retData = answer.value(API_DATA).toArray();
	QJsonValue pairs = retData.at(0);
	QVariantMap pairMap = pairs.toObject().toVariantMap();
	if(pairMap.size() != len) {
		return MCUStatusType::MCU_RESPONSE_OUT_OF_BOUNDS_ERROR;
	} else {
		for(int i=0;i<pairMap.size();i++) {
			QString dataKey = "data"+QString::number(i);
			data[i] = pairMap.value(dataKey, 0u).toUInt();
		}
	}

	return getMcuRC(answer);
}

MCUStatusType setEEP(const CharType* serialNumber, UInt16Type addStart, UInt8Type len, UInt8Type* data)
{
	// Because CL is sent in an uint8, the length cannot be bigger than 247 (247+5+2+1=255 bytes)
	if (len > 247) {
		return MCU_INVALID_ARGUMENT_ERROR;
	}
	if (!serialNumber) {
		return MCU_INVALID_ARGUMENT_ERROR;
	}
	if (! data)
	{
		return MCU_INVALID_ARGUMENT_ERROR;
	}
	quint16 cl = 5+2+1+len;
	quint8 onlyDataLength = len+2+1;

	VicoQuery query;
	// Break down to bytes
	quint8 addStart1 = (addStart & 0x0000FF00) >> 8;
	quint8 addStart2 = (addStart & 0x000000FF);

	// Version, id, length, add_start, len, requestedDataLength, sentDataLength
	// Carful here: We just place all possible maximum of 248 bytes, which will be cut off by length in the VicoQuery execute, the rest will be thrown away
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 0x01u, 0x41u, cl, 0, onlyDataLength, addStart2, addStart1, len, data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7], data[8], data[9], data[10], data[11], data[12], data[13], data[14], data[15], data[16], data[17], data[18], data[19], data[20], data[21], data[22], data[23], data[24], data[25], data[26], data[27], data[28], data[29], data[30], data[31], data[32], data[33], data[34], data[35], data[36], data[37], data[38], data[39], data[40], data[41], data[42], data[43], data[44], data[45], data[46], data[47], data[48], data[49], data[50], data[51], data[52], data[53], data[54], data[55], data[56], data[57], data[58], data[59], data[60], data[61], data[62], data[63], data[64], data[65], data[66], data[67], data[68], data[69], data[70], data[71], data[72], data[73], data[74], data[75], data[76], data[77], data[78], data[79], data[80], data[81], data[82], data[83], data[84], data[85], data[86], data[87], data[88], data[89], data[90], data[91], data[92], data[93], data[94], data[95], data[96], data[97], data[98], data[99], data[100], data[101], data[102], data[103], data[104], data[105], data[106], data[107], data[108], data[109], data[110], data[111], data[112], data[113], data[114], data[115], data[116], data[117], data[118], data[119], data[120], data[121], data[122], data[123], data[124], data[125], data[126], data[127], data[128], data[129], data[130], data[131], data[132], data[133], data[134], data[135], data[136], data[137], data[138], data[139], data[140], data[141], data[142], data[143], data[144], data[145], data[146], data[147], data[148], data[149], data[150], data[151], data[152], data[153], data[154], data[155], data[156], data[157], data[158], data[159], data[160], data[161], data[162], data[163], data[164], data[165], data[166], data[167], data[168], data[169], data[170], data[171], data[172], data[173], data[174], data[175], data[176], data[177], data[178], data[179], data[180], data[181], data[182], data[183], data[184], data[185], data[186], data[187], data[188], data[189], data[190], data[191], data[192], data[193], data[194], data[195], data[196], data[197], data[198], data[199], data[200], data[201], data[202], data[203], data[204], data[205], data[206], data[207], data[208], data[209], data[210], data[211], data[212], data[213], data[214], data[215], data[216], data[217], data[218], data[219], data[220], data[221], data[222], data[223], data[224], data[225], data[226], data[227], data[228], data[229], data[230], data[231], data[232], data[233], data[234], data[235], data[236], data[237], data[238], data[239], data[240], data[241], data[242], data[243], data[244], data[245], data[246]);
	if (MCU_SUCCESS != getMcuRC(answer)) {
		return getMcuRC(answer);
	}
	answer.value(API_MCU_PROTOCOL_VERSION).toInt();
	return getMcuRC(answer);
}

MCUStatusType twi(const CharType* serialNumber, UInt8Type ad, TWIModeType md, UInt8Type ses, UInt8Type res, UInt8Type* sendData, UInt8Type* recData)
{
	if (ses > 246) {
		return MCU_INVALID_ARGUMENT_ERROR;
	}
	if (res > 249) {
		return MCU_INVALID_ARGUMENT_ERROR;
	}
	if (!serialNumber) {
		return MCU_INVALID_ARGUMENT_ERROR;
	}
	if (! sendData)
	{
		return MCU_INVALID_ARGUMENT_ERROR;
	}
	if (! recData)
	{
		return MCU_INVALID_ARGUMENT_ERROR;
	}
	quint8 cl = 5+4+ses;
	quint16 sendDataLength = ses+4;

	VicoQuery query;


	// Version, id, length, add_start, len, requestedDataLength, sentDataLength
	// Carful here: We just place all possible maximum of 247 bytes, which will be cut off by length in the VicoQuery execute, the rest will be thrown away
	// Careful here: The maximum length to get here is 256 bytes. We need to ensure that expectedRequestLength of 256 is working
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 0x01u, 0x50u, cl, res, sendDataLength, ad, md, ses, res, sendData[0], sendData[1], sendData[2], sendData[3], sendData[4], sendData[5], sendData[6], sendData[7], sendData[8], sendData[9], sendData[10], sendData[11], sendData[12], sendData[13], sendData[14], sendData[15], sendData[16], sendData[17], sendData[18], sendData[19], sendData[20], sendData[21], sendData[22], sendData[23], sendData[24], sendData[25], sendData[26], sendData[27], sendData[28], sendData[29], sendData[30], sendData[31], sendData[32], sendData[33], sendData[34], sendData[35], sendData[36], sendData[37], sendData[38], sendData[39], sendData[40], sendData[41], sendData[42], sendData[43], sendData[44], sendData[45], sendData[46], sendData[47], sendData[48], sendData[49], sendData[50], sendData[51], sendData[52], sendData[53], sendData[54], sendData[55], sendData[56], sendData[57], sendData[58], sendData[59], sendData[60], sendData[61], sendData[62], sendData[63], sendData[64], sendData[65], sendData[66], sendData[67], sendData[68], sendData[69], sendData[70], sendData[71], sendData[72], sendData[73], sendData[74], sendData[75], sendData[76], sendData[77], sendData[78], sendData[79], sendData[80], sendData[81], sendData[82], sendData[83], sendData[84], sendData[85], sendData[86], sendData[87], sendData[88], sendData[89], sendData[90], sendData[91], sendData[92], sendData[93], sendData[94], sendData[95], sendData[96], sendData[97], sendData[98], sendData[99], sendData[100], sendData[101], sendData[102], sendData[103], sendData[104], sendData[105], sendData[106], sendData[107], sendData[108], sendData[109], sendData[110], sendData[111], sendData[112], sendData[113], sendData[114], sendData[115], sendData[116], sendData[117], sendData[118], sendData[119], sendData[120], sendData[121], sendData[122], sendData[123], sendData[124], sendData[125], sendData[126], sendData[127], sendData[128], sendData[129], sendData[130], sendData[131], sendData[132], sendData[133], sendData[134], sendData[135], sendData[136], sendData[137], sendData[138], sendData[139], sendData[140], sendData[141], sendData[142], sendData[143], sendData[144], sendData[145], sendData[146], sendData[147], sendData[148], sendData[149], sendData[150], sendData[151], sendData[152], sendData[153], sendData[154], sendData[155], sendData[156], sendData[157], sendData[158], sendData[159], sendData[160], sendData[161], sendData[162], sendData[163], sendData[164], sendData[165], sendData[166], sendData[167], sendData[168], sendData[169], sendData[170], sendData[171], sendData[172], sendData[173], sendData[174], sendData[175], sendData[176], sendData[177], sendData[178], sendData[179], sendData[180], sendData[181], sendData[182], sendData[183], sendData[184], sendData[185], sendData[186], sendData[187], sendData[188], sendData[189], sendData[190], sendData[191], sendData[192], sendData[193], sendData[194], sendData[195], sendData[196], sendData[197], sendData[198], sendData[199], sendData[200], sendData[201], sendData[202], sendData[203], sendData[204], sendData[205], sendData[206], sendData[207], sendData[208], sendData[209], sendData[210], sendData[211], sendData[212], sendData[213], sendData[214], sendData[215], sendData[216], sendData[217], sendData[218], sendData[219], sendData[220], sendData[221], sendData[222], sendData[223], sendData[224], sendData[225], sendData[226], sendData[227], sendData[228], sendData[229], sendData[230], sendData[231], sendData[232], sendData[233], sendData[234], sendData[235], sendData[236], sendData[237], sendData[238], sendData[239], sendData[240], sendData[241], sendData[242], sendData[243], sendData[244], sendData[245], sendData[246]);
	if (MCU_SUCCESS != getMcuRC(answer)) {
		return getMcuRC(answer);
	}
	answer.value(API_MCU_PROTOCOL_VERSION).toInt();

	QJsonArray data = answer.value(API_DATA).toArray();
	QJsonValue pairs = data.at(0);
	QVariantMap pairMap = pairs.toObject().toVariantMap();
	if(pairMap.size() != res) {
		return MCUStatusType::MCU_RESPONSE_OUT_OF_BOUNDS_ERROR;
	} else {
		for(int i=0;i<pairMap.size();i++) {
			QString dataKey = "data"+QString::number(i);
			recData[i] = pairMap.value(dataKey, 0u).toUInt();
		}
	}
	return getMcuRC(answer);
}

MCUStatusType getIO(const CharType* serialNumber, PortType por, UInt8Type pin, BooleanType* val) {
	quint8 expectedResponseLength = 1;
	if (!serialNumber) {
		return MCU_INVALID_ARGUMENT_ERROR;
	}

	VicoQuery query;
	// Version, id, length, crc, add_start, len, requestedDataLength
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 0x01u, 0x060u, 0x07u, expectedResponseLength, 2, por, pin);
	if (MCU_SUCCESS != getMcuRC(answer)) {
		return getMcuRC(answer);
	}
	answer.value(API_MCU_PROTOCOL_VERSION).toInt();

	QJsonArray retData = answer.value(API_DATA).toArray();
	QJsonValue pairs = retData.at(0);
	QVariantMap pairMap = pairs.toObject().toVariantMap();
	if(pairMap.size() != expectedResponseLength) {
		return MCUStatusType::MCU_RESPONSE_OUT_OF_BOUNDS_ERROR;
	} else {
		MCUStatusType rc;
		rc = convertByteToBoolean(val, pairMap.value("data0").toUInt());
		if (rc != MCU_SUCCESS) return rc;
	}

	return getMcuRC(answer);
}

MCUStatusType setIO(const CharType* serialNumber, PortType por, UInt8Type pin, BooleanType val) {
	if (!serialNumber) {
		return MCU_INVALID_ARGUMENT_ERROR;
	}

	VicoQuery query;
	// Version, id, length, crc, add_start, len, requestedDataLength
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 0x01u, 0x061u, 0x08u, 0, 3, por, pin, val);
	if (MCU_SUCCESS != getMcuRC(answer)) {
		return getMcuRC(answer);
	}
	answer.value(API_MCU_PROTOCOL_VERSION).toInt();
	return getMcuRC(answer);
}

MCUStatusType getADC(const CharType* serialNumber, PortType por, UInt8Type pin, UInt16Type* adcVal) {
	quint8 expectedResponseLength = 2;
	if (!serialNumber) {
		return MCU_INVALID_ARGUMENT_ERROR;
	}

	VicoQuery query;
	// Version, id, length, crc, add_start, len, requestedDataLength
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 0x01u, 0x062u, 0x07u, expectedResponseLength, 2, por, pin);
	if (MCU_SUCCESS != getMcuRC(answer)) {
		return getMcuRC(answer);
	}
	answer.value(API_MCU_PROTOCOL_VERSION).toInt();

	QJsonArray retData = answer.value(API_DATA).toArray();
	QJsonValue pairs = retData.at(0);
	QVariantMap pairMap = pairs.toObject().toVariantMap();
	if(pairMap.size() != expectedResponseLength) {
		return MCUStatusType::MCU_RESPONSE_OUT_OF_BOUNDS_ERROR;
	} else {
		MCUStatusType rc;
		rc = convertBytesToUInt16(adcVal, pairMap.value("data0").toUInt(), pairMap.value("data1").toUInt());
		if (rc != MCU_SUCCESS) return rc;
	}
	return getMcuRC(answer);
}

MCUStatusType setDAC(const CharType* serialNumber, PortType por, UInt8Type pin, UInt16Type dacVal) {
	if (!serialNumber) {
		return MCU_INVALID_ARGUMENT_ERROR;
	}

	VicoQuery query;
	// Break down to bytes
	quint8 dacVal1 = (dacVal & 0x0000FF00) >> 8;
	quint8 dacVal2 = (dacVal & 0x000000FF);
	// Version, id, length, crc, add_start, len, requestedDataLength
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 0x01u, 0x063u, 0x09u, 0, 4, por, pin, dacVal2, dacVal1);
	if (MCU_SUCCESS != getMcuRC(answer)) {
		return getMcuRC(answer);
	}
	answer.value(API_MCU_PROTOCOL_VERSION).toInt();
	return getMcuRC(answer);
}

MCUStatusType setIMax(const CharType* serialNumber, UInt16Type itecMax) {
	if (!serialNumber) {
		return MCU_INVALID_ARGUMENT_ERROR;
	}

	VicoQuery query;
	// Break down to bytes
	quint8 itecMax1 = (itecMax & 0x0000FF00) >> 8;
	quint8 itecMax2 = (itecMax & 0x000000FF);
	// Version, id, length, crc, add_start, len, requestedDataLength
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 0x01u, 0x064u, 0x07u, 0, 2, itecMax2, itecMax1);
	if (MCU_SUCCESS != getMcuRC(answer)) {
		return getMcuRC(answer);
	}
	answer.value(API_MCU_PROTOCOL_VERSION).toInt();
	return getMcuRC(answer);
}

MCUStatusType setUMax(const CharType* serialNumber, UInt16Type utecMax) {
	if (!serialNumber) {
		return MCU_INVALID_ARGUMENT_ERROR;
	}

	VicoQuery query;
	// Break down to bytes
	quint8 utecMax1 = (utecMax & 0x0000FF00) >> 8;
	quint8 utecMax2 = (utecMax & 0x000000FF);
	// Version, id, length, crc, add_start, len, requestedDataLength
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 0x01u, 0x065u, 0x07u, 0, 2, utecMax2, utecMax1);
	if (MCU_SUCCESS != getMcuRC(answer)) {
		return getMcuRC(answer);
	}
	answer.value(API_MCU_PROTOCOL_VERSION).toInt();
	return getMcuRC(answer);
}

MCUStatusType dbgClp(const CharType* serialNumber, DbgClpType* dbgClp) {
	quint8 expectedResponseLength = 29;
	if (!serialNumber) {
		return MCU_INVALID_ARGUMENT_ERROR;
	}
	if (!dbgClp) {
		return MCU_INVALID_ARGUMENT_ERROR;
	}
	VicoQuery query;
	// VER, CIX, CL, requestedDataLength, variableDataSendLength
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 0x01u, 0x6Eu, 0x05u, expectedResponseLength, 0);
	if (MCU_SUCCESS != getMcuRC(answer)) {
		return getMcuRC(answer);
	}
	answer.value(API_MCU_PROTOCOL_VERSION).toInt();

	QJsonArray data = answer.value(API_DATA).toArray();
	QJsonValue pairs = data.at(0);
	QVariantMap pairMap = pairs.toObject().toVariantMap();
	if(pairMap.size() != expectedResponseLength) {
		return MCUStatusType::MCU_RESPONSE_OUT_OF_BOUNDS_ERROR;
	} else {
		MCUStatusType rc;
		rc = convertBytesToUInt32(&dbgClp->stepCounter, pairMap.value("data0").toUInt(), pairMap.value("data1").toUInt(), pairMap.value("data2").toUInt(), pairMap.value("data3").toUInt());
		if (rc != MCU_SUCCESS) return rc;
		rc = convertBytesToFloat(&dbgClp->sddTmp, pairMap.value("data4").toUInt(), pairMap.value("data5").toUInt(), pairMap.value("data6").toUInt(), pairMap.value("data7").toUInt());
		if (rc != MCU_SUCCESS) return rc;
		rc = convertBytesToFloat(&dbgClp->itec, pairMap.value("data8").toUInt(), pairMap.value("data9").toUInt(), pairMap.value("data10").toUInt(), pairMap.value("data11").toUInt());
		if (rc != MCU_SUCCESS) return rc;
		rc = convertBytesToFloat(&dbgClp->utec, pairMap.value("data12").toUInt(), pairMap.value("data13").toUInt(), pairMap.value("data14").toUInt(), pairMap.value("data15").toUInt());
		if (rc != MCU_SUCCESS) return rc;
		rc = convertBytesToFloat(&dbgClp->monSigFinal, pairMap.value("data16").toUInt(), pairMap.value("data17").toUInt(), pairMap.value("data18").toUInt(), pairMap.value("data19").toUInt());
		if (rc != MCU_SUCCESS) return rc;
		rc = convertBytesToFloat(&dbgClp->pPart, pairMap.value("data20").toUInt(), pairMap.value("data21").toUInt(), pairMap.value("data22").toUInt(), pairMap.value("data23").toUInt());
		if (rc != MCU_SUCCESS) return rc;
		rc = convertBytesToFloat(&dbgClp->iPart, pairMap.value("data24").toUInt(), pairMap.value("data25").toUInt(), pairMap.value("data26").toUInt(), pairMap.value("data27").toUInt());
		if (rc != MCU_SUCCESS) return rc;
		rc = convertByteToBoolean(&dbgClp->rdy, pairMap.value("data28").toUInt());
		if (rc != MCU_SUCCESS) return rc;
	}
	return getMcuRC(answer);
}

MCUStatusType dbgClpExt(const CharType* serialNumber, DbgClpExtType* dbgClpExt) {
	quint8 expectedResponseLength = 52;
	if (!serialNumber) {
		return MCU_INVALID_ARGUMENT_ERROR;
	}
	if (!dbgClpExt) {
		return MCU_INVALID_ARGUMENT_ERROR;
	}
	VicoQuery query;
	// VER, CIX, CL, requestedDataLength, variableDataSendLength
	QJsonObject answer = query.execute(getDeviceIdentifierfromString(serialNumber), 0x01u, 0x6Fu, 0x05u, expectedResponseLength, 0);
	if (MCU_SUCCESS != getMcuRC(answer)) {
		return getMcuRC(answer);
	}
	answer.value(API_MCU_PROTOCOL_VERSION).toInt();

	QJsonArray data = answer.value(API_DATA).toArray();
	QJsonValue pairs = data.at(0);
	QVariantMap pairMap = pairs.toObject().toVariantMap();
	if(pairMap.size() != expectedResponseLength) {
		return MCUStatusType::MCU_RESPONSE_OUT_OF_BOUNDS_ERROR;
	} else {
		MCUStatusType rc;
		rc = convertBytesToUInt32(&dbgClpExt->stepCounter, pairMap.value("data0").toUInt(), pairMap.value("data1").toUInt(), pairMap.value("data2").toUInt(), pairMap.value("data3").toUInt());
		if (rc != MCU_SUCCESS) return rc;
		rc = convertBytesToFloat(&dbgClpExt->targetTmp, pairMap.value("data4").toUInt(), pairMap.value("data5").toUInt(), pairMap.value("data6").toUInt(), pairMap.value("data7").toUInt());
		if (rc != MCU_SUCCESS) return rc;
		rc = convertBytesToFloat(&dbgClpExt->sddTmp, pairMap.value("data8").toUInt(), pairMap.value("data9").toUInt(), pairMap.value("data10").toUInt(), pairMap.value("data11").toUInt());
		if (rc != MCU_SUCCESS) return rc;
		rc = convertBytesToFloat(&dbgClpExt->itec, pairMap.value("data12").toUInt(), pairMap.value("data13").toUInt(), pairMap.value("data14").toUInt(), pairMap.value("data15").toUInt());
		if (rc != MCU_SUCCESS) return rc;
		rc = convertBytesToFloat(&dbgClpExt->utec, pairMap.value("data16").toUInt(), pairMap.value("data17").toUInt(), pairMap.value("data18").toUInt(), pairMap.value("data19").toUInt());
		if (rc != MCU_SUCCESS) return rc;
		rc = convertBytesToFloat(&dbgClpExt->monStepSize, pairMap.value("data20").toUInt(), pairMap.value("data21").toUInt(), pairMap.value("data22").toUInt(), pairMap.value("data23").toUInt());
		if (rc != MCU_SUCCESS) return rc;
		rc = convertBytesToFloat(&dbgClpExt->monSigFinal, pairMap.value("data24").toUInt(), pairMap.value("data25").toUInt(), pairMap.value("data26").toUInt(), pairMap.value("data27").toUInt());
		if (rc != MCU_SUCCESS) return rc;
		rc = convertBytesToFloat(&dbgClpExt->ctrlSigFinal, pairMap.value("data28").toUInt(), pairMap.value("data29").toUInt(), pairMap.value("data30").toUInt(), pairMap.value("data31").toUInt());
		if (rc != MCU_SUCCESS) return rc;
		rc = convertBytesToFloat(&dbgClpExt->pPart, pairMap.value("data32").toUInt(), pairMap.value("data33").toUInt(), pairMap.value("data34").toUInt(), pairMap.value("data35").toUInt());
		if (rc != MCU_SUCCESS) return rc;
		rc = convertBytesToFloat(&dbgClpExt->iPart, pairMap.value("data36").toUInt(), pairMap.value("data37").toUInt(), pairMap.value("data38").toUInt(), pairMap.value("data39").toUInt());
		if (rc != MCU_SUCCESS) return rc;
		rc = convertByteToBoolean(&dbgClpExt->iPartLimit, pairMap.value("data40").toUInt());
		if (rc != MCU_SUCCESS) return rc;
		rc = convertBytesToFloat(&dbgClpExt->dPart, pairMap.value("data41").toUInt(), pairMap.value("data42").toUInt(), pairMap.value("data43").toUInt(), pairMap.value("data44").toUInt());
		if (rc != MCU_SUCCESS) return rc;
		rc = convertByteToBoolean(&dbgClpExt->rdy, pairMap.value("data45").toUInt());
		if (rc != MCU_SUCCESS) return rc;
		rc = convertByteToBoolean(&dbgClpExt->aRdy, pairMap.value("data46").toUInt());
		if (rc != MCU_SUCCESS) return rc;
		rc = convertByteToBoolean(&dbgClpExt->grnLed, pairMap.value("data47").toUInt());
		if (rc != MCU_SUCCESS) return rc;
		rc = convertBytesToFloat(&dbgClpExt->hotSide, pairMap.value("data48").toUInt(), pairMap.value("data49").toUInt(), pairMap.value("data50").toUInt(), pairMap.value("data51").toUInt());
		if (rc != MCU_SUCCESS) return rc;
	}
	return getMcuRC(answer);
}
/* End MCU Datagram API */
