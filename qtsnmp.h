/**
 * @version 1.0
 *
 * @section DESCRIPTION
 *
 * The class represents a SNMP session, which provides get and set
 * operations on SNMP agents.
 *
 */
 
 
#ifndef QTSNMP_H
#define QTSNMP_H
 
#include <QObject>
#include <QHostAddress>
#include <QByteArray>
#include <QString>
#include <QUdpSocket>
#include <vector>
 
class SNMPSession : public QObject {
 
    Q_OBJECT
 
public:
    SNMPSession();
    SNMPSession(const QString &agentAddress, qint16 agentPort, qint16 socketPort);
    ~SNMPSession();
 
// get/set methods
    QHostAddress *getAgentAddress() const;
    qint16 getAgentPort() const;
    qint16 getSocketPort() const;
    QString getAgentMACAddress() const;
    void setAgentAddress(const QString &agentAddress);
    void setAgentPort(qint16 agentPort);
    void setSocketPort(qint16 socketPort);
 
// SNMP message methods
    int sendSetRequest(const QString &communityStringParameter, 
                       const QString oidParameter, int value);
    int sendSetRequest(const QString &communityStringParameter,
                       const QString oidParameter, const QString &valueParameter);
    int sendGetRequest(QString &receivedValue,
                       const QString &communityStringParameter, const QString &oidParameter);
 
// additional public methods
 
private:
    int getValueFromGetResponse(QString &receivedValue, QByteArray &receivedDatagram);
    QByteArray convertIntAccordingToBER(int valueToConvert);
    void convertOIDAccordingToBER(QByteArray &oid);
 
    QUdpSocket udpSocket;
    QHostAddress *agentAddress;
    qint16 agentPort;
    qint16 socketPort;

    int buildInt(int numBytes, QByteArray dataPart);
    bool decodeSNMP( QByteArray data );
    int errorStatus() { return snmpBlocs[5].data.at(0); }

    struct smntp_bloc {
        int type;
        int len;
        QByteArray data;
    };
    std::vector<smntp_bloc> snmpBlocs;
};
 
#endif // QTSNMP_H
