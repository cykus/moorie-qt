/*
 * This file is a part of Moorie
 *
 * Copyright (C) 2007-2010 Moorie Team - http://moorie.pl
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */ 

#ifndef MAILBOX_H
#define MAILBOX_H

#include <QEventLoop>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class Mailbox : public QObject
{
    Q_OBJECT

    QNetworkAccessManager *m_manager;
    QNetworkRequest m_request;
    QEventLoop eLoop; //Used to stop main loop
    QString mailbox; //!< Mailbox Name
    QString user; //!< User login
    QString password; //!< User password

    // sprawdzanie przekierowań w metodzie GET nie ruszać
    QNetworkRequest request;
    QString host;
    QString resultData;
    QString scheme;
    bool headers;
    QString headersList;
private slots:
    void replyFinished(QNetworkReply *reply);
    void sslErrors(QNetworkReply *,const QList<QSslError>&); //only ignore ssl errors
protected:
    QString getMailbox() const; //!< Get Mailbox Name
    QString getUser() const; //!< Get User login
    QString getPassword() const; //!< Get User password
public:
    Mailbox(const QString &name, const QString &usr, const QString &passwd);
    ~Mailbox();
    QString doGet(QString url, bool header = false);
    QString doPost(QString host, QString vars, bool header = false);
    QString escape(QString q);
    QString unescape(QString q);
    virtual int loginRequest() = 0;

};

#endif // MAILBOX_H
