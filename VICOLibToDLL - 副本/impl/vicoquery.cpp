#include "vicoquery.h"

QScopedPointer<QFile> m_logFile;

// The implementation of the handler
void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg) {
//	// Open stream file writes
//	QTextStream out(m_logFile.data());
//	// Write the date of recording
//	out << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz ");
//	// By type determine to what level belongs message
//	switch (type)
//	{
//	case QtInfoMsg:     out << "INFO "; break;
//	case QtDebugMsg:    out << "DEBUG "; break;
//	case QtWarningMsg:  out << "WARNING "; break;
//	case QtCriticalMsg: out << "CRITICAL "; break;
//	case QtFatalMsg:    out << "FATAL "; break;
//	}
//	// Write to the output category of the message and the message itself
//	out << context.category << ": "
//		<< msg << endl;
//	out.flush();    // Clear the buffered data
}

VicoQuery::VicoQuery() {
	// error is overloaded, use this "convenient" way...source: https://doc.qt.io/qt-5/qlocalsocket-obsolete.html
	// with 5.15 error is replaced by errorOccurred()
	connect(&socket, QOverload<QLocalSocket::LocalSocketError>::of(&QLocalSocket::error), this, &VicoQuery::reportError);
	connect(this, &VicoQuery::dataReceived, this, &VicoQuery::onDataReceived);
	connect(&socket, &QLocalSocket::connected, this, &VicoQuery::onConnected);
	connect(&socket, &QLocalSocket::disconnected, this, &VicoQuery::onDisconnected);
	wait.store(false);
	connected.store(false);
//	#ifndef QT_DEBUG
//	// Set the logging file
//	// check which a path to file you use
//	QString filename = "log_" + QDateTime::currentDateTime().toString("yyyyMMdd_hh_mm") + ".txt";
//	QFileInfo file(QDir::currentPath(), filename);
//	m_logFile.reset(new QFile(file.absoluteFilePath()));
//	// Open the file logging
//	m_logFile.data()->open(QFile::Append | QFile::Text);
//	// Set handler
//	qInstallMessageHandler(messageHandler);
//	#endif
}

// Executes a request with given requestName as internal function.
QJsonObject VicoQuery::execute(const QString &request) {
	QJsonObject apiCall;
	connectToServer();
	if (socketHasErrors) {
		apiCall[API_STATUSTYPE] = VICOStatusType::VICO_VICODAEMON_IS_STOPPED;
		return apiCall;
	}

	apiCall[API_DATAGRAM_REQUEST] = request;
	socket.write(QJsonDocument(apiCall).toJson());
	socket.waitForBytesWritten(-1);
	socket.waitForReadyRead(-1);
	QJsonParseError parseError;
	const QJsonDocument jsonDoc = QJsonDocument::fromJson(socket.readAll(), &parseError);
	if (parseError.error == QJsonParseError::NoError) {
		// if the data was indeed valid JSON
		jsonReceived(jsonDoc);
	}
	socket.close();
	return lastResult;
}

// Executes getPreferredInterface
QJsonObject VicoQuery::execute(const QString &request, quint64 deviceId) {
	QJsonObject apiCall;
	connectToServer();
	if (socketHasErrors) {
		apiCall[API_STATUSTYPE] = VICOStatusType::VICO_VICODAEMON_IS_STOPPED;
		return apiCall;
	}
	apiCall[API_DATAGRAM_REQUEST] = request;
	apiCall[API_DATAGRAM_DEVICE] = QJsonValue::fromVariant(QString::number(deviceId, 16));
	socket.write(QJsonDocument(apiCall).toJson());
	socket.waitForBytesWritten(-1);
	socket.waitForReadyRead(-1);
	QJsonParseError parseError;
	const QJsonDocument jsonDoc = QJsonDocument::fromJson(socket.readAll(), &parseError);
	if (parseError.error == QJsonParseError::NoError) {
		// if the data was indeed valid JSON
		jsonReceived(jsonDoc);
	}
	socket.close();
	return lastResult;
}

// Executes setPreferredInterface
QJsonObject VicoQuery::execute(const QString &request, quint64 deviceId, quint8 preferredInterface) {
	QJsonObject apiCall;
	connectToServer();
	if (socketHasErrors) {
		apiCall[API_STATUSTYPE] = VICOStatusType::VICO_VICODAEMON_IS_STOPPED;
		return apiCall;
	}
	apiCall[API_DATAGRAM_REQUEST] = request;
	apiCall[API_DATAGRAM_DEVICE] = QJsonValue::fromVariant(QString::number(deviceId, 16));
	apiCall[API_DATAGRAM_INTERFACE] = QJsonValue::fromVariant(QString::number(preferredInterface));
	socket.write(QJsonDocument(apiCall).toJson());
	socket.waitForBytesWritten(-1);
	socket.waitForReadyRead(-1);
	QJsonParseError parseError;
	const QJsonDocument jsonDoc = QJsonDocument::fromJson(socket.readAll(), &parseError);
	if (parseError.error == QJsonParseError::NoError) {
		// if the data was indeed valid JSON
		jsonReceived(jsonDoc);
	}
	socket.close();
	return lastResult;
}

// Executes getDeviceInfoByIndex
QJsonObject VicoQuery::execute(const QString &request, quint8 index) {
	QJsonObject apiCall;
	connectToServer();
	if (socketHasErrors) {
		apiCall[API_STATUSTYPE] = VICOStatusType::VICO_VICODAEMON_IS_STOPPED;
		return apiCall;
	}
	apiCall[API_DATAGRAM_REQUEST] = request;
	apiCall[API_DATAGRAM_DEVICEINDEX] = index;
	socket.write(QJsonDocument(apiCall).toJson());
	socket.waitForBytesWritten(-1);
	socket.waitForReadyRead(-1);
	QJsonParseError parseError;
	const QJsonDocument jsonDoc = QJsonDocument::fromJson(socket.readAll(), &parseError);
	if (parseError.error == QJsonParseError::NoError) {
		// if the data was indeed valid JSON
		jsonReceived(jsonDoc);
	}
	socket.close();
	return lastResult;
}

// Executes a TCP Scan.
QJsonObject VicoQuery::execute(const QString &request, const QString &fromIpAddress, const QString &toIpAddress) {
	QJsonObject apiCall;
	connectToServer();
	if (socketHasErrors) {
		apiCall[API_STATUSTYPE] = VICOStatusType::VICO_VICODAEMON_IS_STOPPED;
		return apiCall;
	}

	apiCall[API_DATAGRAM_REQUEST] = request;
	apiCall[API_DATAGRAM_FROM_IP] = fromIpAddress;
	apiCall[API_DATAGRAM_TO_IP] = toIpAddress;
	socket.write(QJsonDocument(apiCall).toJson());
	socket.waitForBytesWritten(-1);
	socket.waitForReadyRead(-1);
	QJsonParseError parseError;
	const QJsonDocument jsonDoc = QJsonDocument::fromJson(socket.readAll(), &parseError);
	if (parseError.error == QJsonParseError::NoError) {
		// if the data was indeed valid JSON
		jsonReceived(jsonDoc);
	}
	socket.close();
	return lastResult;
}

// Executes a UDP Scan.
QJsonObject VicoQuery::execute(const QString &request, const QString &ipAddress, const quint8 subnetMask) {
	QJsonObject apiCall;
	connectToServer();
	if (socketHasErrors) {
		apiCall[API_STATUSTYPE] = VICOStatusType::VICO_VICODAEMON_IS_STOPPED;
		return apiCall;
	}
	apiCall[API_DATAGRAM_REQUEST] = request;
	apiCall[API_DATAGRAM_UDPSCAN_IP] = ipAddress;
	apiCall[API_DATAGRAM_UDPSCAN_SUBNETMASK] = subnetMask;
	socket.write(QJsonDocument(apiCall).toJson());
	socket.waitForBytesWritten(-1);
	socket.waitForReadyRead(-1);
	QJsonParseError parseError;
	const QJsonDocument jsonDoc = QJsonDocument::fromJson(socket.readAll(), &parseError);
	if (parseError.error == QJsonParseError::NoError) {
		// if the data was indeed valid JSON
		jsonReceived(jsonDoc);
	}
	socket.close();
	return lastResult;
}

// Executes the DPP datagram.
QJsonObject VicoQuery::execute(quint64 deviceId, quint8 pid, quint8 command, quint16 data, quint16 size) {
	QJsonObject apiCall;
	connectToServer();
	if (socketHasErrors) {
		apiCall[API_STATUSTYPE] = DPPStatusType::DPP_VICODAEMON_IS_STOPPED;
		return apiCall;
	}

	apiCall[API_DATAGRAM_DEVICE] = QJsonValue::fromVariant(QString::number(deviceId, 16));
	apiCall[API_DATAGRAM_ID] = pid;
	apiCall[API_DATAGRAM_CMD] = command;
	apiCall[API_DATAGRAM_DATA] = data;
	apiCall[API_DATAGRAM_SIZE] = size;
	socket.write(QJsonDocument(apiCall).toJson());
	socket.waitForBytesWritten(-1);
	socket.waitForReadyRead(-1);
	QJsonParseError parseError;
	const QJsonDocument jsonDoc = QJsonDocument::fromJson(socket.readAll(), &parseError);
	if (parseError.error == QJsonParseError::NoError) {
		// if the data was indeed valid JSON
		jsonReceived(jsonDoc);
	}
	socket.close();
	return lastResult;
}

// Executes the DPP write firmware datagram.
QJsonObject VicoQuery::execute(quint64 deviceId, quint8 pid, quint8 command, quint16 segmentNumber, uchar* firmwareSection) {
	QJsonObject apiCall;
	connectToServer();
	if (socketHasErrors) {
		apiCall[API_STATUSTYPE] = DPPStatusType::DPP_VICODAEMON_IS_STOPPED;
		return apiCall;
	}

	apiCall[API_DATAGRAM_DEVICE] = QJsonValue::fromVariant(QString::number(deviceId, 16));
	apiCall[API_DATAGRAM_ID] = pid;
	apiCall[API_DATAGRAM_CMD] = command;
	apiCall[API_DATAGRAM_DATA] = segmentNumber;

	QVariantMap map;
	for(int i=0;i<1024;i++) {
		QString key = API_DATAGRAM_FIRMWARE + QString::number(i);
		map.insert(key, quint8(firmwareSection[i]));
	}

	apiCall[API_DATAGRAM_FIRMWARE] = QJsonObject::fromVariantMap(map);
	apiCall[API_DATAGRAM_SIZE] = 4;
	socket.write(QJsonDocument(apiCall).toJson());
	socket.waitForBytesWritten(-1);
	socket.waitForReadyRead(-1);
	QJsonParseError parseError;
	const QJsonDocument jsonDoc = QJsonDocument::fromJson(socket.readAll(), &parseError);
	if (parseError.error == QJsonParseError::NoError) {
		// if the data was indeed valid JSON
		jsonReceived(jsonDoc);
	}
	socket.close();
	return lastResult;
}

// Executes the MCU datagram.
QJsonObject VicoQuery::execute(quint64 deviceId, quint8 ver, quint8 cix, quint8 cl, quint16 requestedDataLength, int dataByteCount, ...) {
	QJsonObject mcuQuery;
	connectToServer();
	if (socketHasErrors) {
		mcuQuery[API_STATUSTYPE] = MCUStatusType::MCU_VICODAEMON_IS_STOPPED;
		return mcuQuery;
	}

	mcuQuery[API_MCU_DATAGRAM_ENABLE] = true;
	mcuQuery[API_DATAGRAM_DEVICE] = QJsonValue::fromVariant(QString::number(deviceId, 16));
	mcuQuery[API_MCU_PROTOCOL_VERSION] = ver;
	mcuQuery[API_DATAGRAM_CMD] = cix;
	mcuQuery[API_DATAGRAM_SIZE] = cl;
	// Prepare the complete datagram to calculate the CRC
	quint8 datagram[5+dataByteCount];
	datagram[0] = ver;
	datagram[1] = cix;
	datagram[2] = cl;
	datagram[3] = 0;
	datagram[4] = 0;
	va_list args;
	va_start(args, dataByteCount);
	QVariantMap map;
	for(int i=0;i<dataByteCount;i++) {
		quint8 data = quint8(va_arg(args, uint));
		datagram[5+i] = data;
		QString key = API_DATAGRAM_DATA + QString::number(i);
		map.insert(key, data);
	}
	va_end(args);
	// Done preparing the datagram to calculate the CRC

	// Calculate and add the CRC
	quint16 crcLittleEndian = crc16LE(&datagram[0], 0, 5+dataByteCount);
	datagram[3] = (crcLittleEndian >> 8) & 0xFF;
	datagram[4] = crcLittleEndian & 0xFF;
	mcuQuery[API_MCU_LENGTH] = requestedDataLength;
	mcuQuery[API_MCU_CRC] = crcLittleEndian;
	mcuQuery[API_DATAGRAM_DATA] = QJsonObject::fromVariantMap(map);
	socket.write(QJsonDocument(mcuQuery).toJson());
	socket.waitForBytesWritten(-1);
	socket.waitForReadyRead(-1);
	QJsonParseError parseError;
	const QJsonDocument jsonDoc = QJsonDocument::fromJson(socket.readAll(), &parseError);
	if (parseError.error == QJsonParseError::NoError) {
		// if the data was indeed valid JSON
		jsonReceived(jsonDoc);
	}
	socket.close();
	return lastResult;
}

void VicoQuery::connectToServer() {
	this->socketHasErrors = false;
	socket.abort();
	//qDebug() << "VicoQuery::disconnectFromServer: After abort: Local socket state:" << socket.state();
	socket.connectToServer("VICODaemon");
	//qDebug() << "VicoQuery::disconnectFromServer: After connectToServer: Local socket state:" << socket.state();
	socket.waitForConnected(-1);
	//qDebug() << "VicoQuery::disconnectFromServer: After waitForConnected: Local socket state:" << socket.state();
}

quint16 VicoQuery::crc16LE(quint8 *data, quint8 offset, quint8 length) const {

	quint16 calculatedCRC = crc16(&data[0], offset, length);
	quint16 crcLittleEndianHigh = (calculatedCRC & 0x00FF) << 8;
	quint16 crcLittleEndianLow = (calculatedCRC & 0xFF00) >> 8;
	quint16 crcLittleEndian = crcLittleEndianHigh | crcLittleEndianLow;
	return crcLittleEndian;
}

quint16 VicoQuery::crc16(quint8 *data, quint8 offset, quint8 length) const {
	if(!data || offset >= length) return 0;
	quint16 crc = 0xFFFFu;
	for(int i=0;i<length;i++) {
		crc ^= data[offset + i] << 8;
		for(int j=0;j<8;j++) {
			if((crc & 0x8000u) > 0) {
				crc = (crc << 1) ^ 0x1021;
			} else {
				crc = crc << 1;
			}
		}
	}
	return crc & 0xFFFF;
}

void VicoQuery::reportError(QLocalSocket::LocalSocketError socketError) {
	qDebug() << "Local socket couldn't be connected due to:" << socket.errorString() << ".Specific socket error is:" << socketError;
	qDebug() << "Local socket couldn't be connected due to:" << socket.state();
	this->socketHasErrors = true;
	connected.store(false);
}

void VicoQuery::doWait(WaitType type, qint64 msec) {
	qint64 startTimeMS = QDateTime::currentMSecsSinceEpoch();
	while((msec == -1 || (QDateTime::currentMSecsSinceEpoch() - startTimeMS) < msec) && ((type == WaitType::Bytes && wait.load()) || (type == WaitType::Disconnection && connected.load()))) {
		qDebug() << "waiting" << startTimeMS << QDateTime::currentMSecsSinceEpoch() << msec << wait.load() << connected.load();
		QThread::msleep(100);
	}
}

void VicoQuery::onDataReceived() {
	wait.store(false);
}

void VicoQuery::onDisconnected() {
	connected.store(false);
}

void VicoQuery::onConnected() {
	connected.store(true);
}

void VicoQuery::jsonReceived(const QJsonDocument &jsonDoc) {
	if (jsonDoc.isObject()) // and is a JSON object
		lastResult = jsonDoc.object(); // parse the JSON
	else
		qDebug() << "The received JSONDocument" << jsonDoc << "is not a JSONObject";

	emit dataReceived();
}
