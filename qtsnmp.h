/**
 * @version 1.0
 *
 * @section DESCRIPTION
 *
 * The class represents a SNMP session, which provides get and set
 * operations on SNMP agents.
 *
 */
 
 
#ifndef SNMPSESSION_H
#define SNMPSESSION_H
 
#include <QObject>
#include <QHostAddress>
#include <QByteArray>
#include <QString>
#include <QUdpSocket>
 
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
    int getValueFromGetResponse(QString &receivedValue, QByteArray &receivedDatagram,
                                    const int &errorIndex, const int &valueTypeIndex,
                                    const int &valueIndex, const int &valueLenghtIndex);
    QByteArray convertIntAccordingToBER(int valueToConvert);
    void convertOIDAccordingToBER(QByteArray &oid);
    void convertOIDAccordingToBER(QByteArray &oid);
 
    QUdpSocket udpSocket;
    QHostAddress *agentAddress;
    qint16 agentPort;
    qint16 socketPort;
};
 
#endif // SNMPSESSION_H
