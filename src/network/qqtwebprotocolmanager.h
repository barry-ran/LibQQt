#ifndef QQTWEBWORKCLIENT_H
#define QQTWEBWORKCLIENT_H

#include <QNetworkAccessManager>
#include <QNetworkReply>
//import this struct will not build fail
#include <QNetworkProxy>
#include <QSslError>
#include <qqt-qt.h>
#include <qqt-local.h>


/**
 * @brief The QQtWebworkClient class
 * One Ftp Http 单工...
 * Multi 半双工（客户端并发，服务器序列） QNetworkAccessManager
 * Multi New Protocol 全双工 QWebSocket
 * need ssl
 * Qt team 实现了几种协议的管理，就能进行几种协议的通讯。supportedSchemes
 */
class QQtWebWorkSession;
class QQTSHARED_EXPORT QQtWebProtocolManager : public QNetworkAccessManager
{
    Q_OBJECT
public:
    explicit QQtWebProtocolManager ( QObject* parent = 0 );

    QNetworkReply* getReplyHandler ( QString& strUrl ) {}

    void sendGetRequest ( QString& strUrl );
    void sendPostRequest ( QString& strUrl );

signals:
    void updateUploadProgress ( QNetworkReply* reply, qint64 bytesSent, qint64 bytesTotal );
    void updateDownloadProgress ( QNetworkReply* reply, qint64 bytesReceived, qint64 bytesTotal );
    //reply->readAll but maybe not all data once
    void readyRead ( QNetworkReply* reply );
    //reply->readAll all data once in theory
    void replyFinished ( QNetworkReply* reply );
    void replyTimeOut ( QNetworkReply* reply );

public slots:

private slots:
    void finished ( QNetworkReply* reply );
    void authenticationRequired ( QNetworkReply*, QAuthenticator* );
    void proxyAuthenticationRequired ( QNetworkProxy, QAuthenticator* );
    void sslErrors ( QNetworkReply*, QList<QSslError> );
    void networkAccessibleChanged ( QNetworkAccessManager::NetworkAccessibility );
    void networkSessionConnected();

    void localReplyTimeOut();
    void localReadyRead();
    void localUpdateUploadProgress ( qint64 bytesSent, qint64 bytesTotal );
    void localUpdateDownloadProgress ( qint64 bytesReceived, qint64 bytesTotal );

private:

    QList<QQtWebWorkSession*> m_listWebWorkSession;
};

class QQtWebWorkSession : public QObject
{
    Q_OBJECT
public:
    explicit QQtWebWorkSession ( QObject* parent ) :
        QObject ( parent ) {}
    virtual ~QQtWebWorkSession() {}

    QNetworkReply* m_pNetworkReply; //封装请求返回信息
    QTimer* m_pTimer; //请求超时计时器
    QString m_strUrl; //记录当前请求的url
    /**
     * @brief m_sessionName
     * talk with whom, which protocol, req content, all represented by this name;
     */
    QString m_sessionName;
} ;

#endif // QQTWEBWORKCLIENT_H