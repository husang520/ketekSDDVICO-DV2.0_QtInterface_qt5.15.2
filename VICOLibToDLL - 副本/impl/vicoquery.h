#ifndef VICOQUERY_H
#define VICOQUERY_H
#include "vicolibglobal.h"
#include "types.h"
#include <QLocalSocket>
#include <QDataStream>
#include <QtCore>

const QString API_MCA = QLatin1String("mca");
const QString API_DATA = QLatin1String("data");
const QString API_DATAGRAM_FIRMWARE = QLatin1String("fw");
const QString API_STATUSTYPE = QLatin1String("statusType");
const QString API_INTERNAL_GETDEVICEINFOBYINDEX = QLatin1String("getDeviceInfoByIndex");
const QString API_INTERNAL_GET_PREFERRED_INTERFACE = QLatin1String("getPreferredInterface");
const QString API_INTERNAL_SET_PREFERRED_INTERFACE = QLatin1String("setPreferredInterface");
const QString API_INTERNAL_REFRESHDEVICECONNECTIONS = QLatin1String("refreshDeviceConnections");
const QString API_INTERNAL_GETNUMBERDEVICES = QLatin1String("getNumberDevices");
const QString API_MCU_PROTOCOL_VERSION = QLatin1String("MCU_PROTOCOL_VERSION");
const QString API_INTERNAL_SCANTCP = QLatin1String("scanTcp");
const QString API_INTERNAL_SCANUDP = QLatin1String("scanUdp");
const QString API_INTERNAL_SCANUSB = QLatin1String("scanUsb");
const QString API_INTERNAL_SCANUSBHID = QLatin1String("scanUsbHid");
const QString API_INTERNAL_STOPTCP = QLatin1String("stopTcp");
const QString API_INTERNAL_STOPUDP = QLatin1String("stopUdp");
const QString API_INTERNAL_DAEMONVERSION = QLatin1String("daemonversion");

/**
 * @brief The VicoQuery class handles the requests and responses from host side to/from the VICODaemon and hence device.
 */
class VicoQuery : public QObject {
	Q_OBJECT

public:
	VicoQuery();
	// Executes VICOLib-internal requests
	QJsonObject execute(const QString &id);
	// Executes getDeviceInfoByIndex
	QJsonObject execute(const QString &request, quint8 index);
	// Executes getPreferredInterface
	QJsonObject execute(const QString &request, quint64 deviceId);
	// Executes setPreferredInterface
	QJsonObject execute(const QString &request, quint64 deviceId, quint8 preferredInterface);
	// Executes TCP Scan with from-to IP address
	QJsonObject execute(const QString &request, const QString &fromIpAddress, const QString &toIpAddress);
	// Executes UDP Scan with IP address and the subnetmask to be scanned
	QJsonObject execute(const QString &request, const QString &fromIpAddress, const quint8);
	// Executes the DPP datagram
	QJsonObject execute(quint64 deviceId, quint8 pid, quint8 command, quint16 data, quint16 size = 4);
	// Executes the DPP write firmware datagram
	QJsonObject execute(quint64 deviceId, quint8 pid, quint8 command, quint16 segmentNumber, uchar* firmwareSection);
	// Executes the MCU datagram
	QJsonObject execute(quint64 deviceId, quint8 ver, quint8 cix, quint8 cl, quint16 requestedDataLength, int dataByteCount, ...);

signals:
	void dataReceived();

private slots:
	void reportError(QLocalSocket::LocalSocketError socketError);
	void onDataReceived();
	void onDisconnected();
	void onConnected();

private:
	// Targeted request of internal function
	const QString API_DATAGRAM_REQUEST = QLatin1String("request");
	// Targeted request of internal function
	const QString API_DATAGRAM_FROM_IP = QLatin1String("fromIp");
	// Targeted request of internal function
	const QString API_DATAGRAM_TO_IP = QLatin1String("toIp");
	// Targeted request of internal function
	const QString API_DATAGRAM_UDPSCAN_IP = QLatin1String("udpScanIp");
	// Targeted request of internal function
	const QString API_DATAGRAM_UDPSCAN_SUBNETMASK = QLatin1String("udpScanSubnetMask");
	// Targeted device of DPP Datagram
	const QString API_DATAGRAM_DEVICE = QLatin1String("device");
	// Target preferred interface
	const QString API_DATAGRAM_INTERFACE = QLatin1String("interface");
	// getDeviceByIndex execute
	const QString API_DATAGRAM_DEVICEINDEX = QLatin1String("deviceIndex");
	// Parameter ID of DPP Datagram: 1 Byte
	const QString API_DATAGRAM_ID = QLatin1String("id");
	// Parameter VALUE of DPP Datagram: 1 Byte
	const QString API_DATAGRAM_DATA = QLatin1String("data");
	// Command of DPP Datagram: 0x00 for read, 0x01 for write
	const QString API_DATAGRAM_CMD = QLatin1String("cmd");
	// Size of DPP Datagram, by default 4, else non-standard size
	const QString API_DATAGRAM_SIZE = QLatin1String("size");
	// when this is enabled, vicodaemon will send the data with mcu passthrough
	const QString API_MCU_DATAGRAM_ENABLE = QLatin1String("MCU_DATAGRAM");
	const QString API_MCU_PROTOCOL_VERSION = QLatin1String("MCU_PROTOCOL_VERSION");
	const QString API_MCU_CRC = QLatin1String("MCU_CHECKSUM");
	const QString API_MCU_LENGTH = QLatin1String("MCU_LENGTH");

	QLocalSocket socket;
	quint32 blockSize;
	QJsonObject lastResult;
	bool socketHasErrors;
	void jsonReceived(const QJsonDocument &jsonDoc);
	void connectToServer();

	quint16 crc16(quint8 *data, quint8 offset, quint8 length) const;
	quint16 crc16LE(quint8 *data, quint8 offset, quint8 length) const;

	std::atomic_bool wait;
	std::atomic_bool connected;
	enum WaitType {
		Bytes,
		Disconnection
	};

	void doWait(WaitType type = WaitType::Bytes, qint64 msec = 30000);
};

#endif // VICOQUERY_H
