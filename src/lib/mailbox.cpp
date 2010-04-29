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

#include "mailbox.h"
#include <QDebug>

Mailbox::Mailbox(const QString &name, const QString &usr, const QString &passwd):
        user(usr),
        mailbox(name),
        password(passwd),
        headersList("")
{

    m_request.setRawHeader("User-Agent", "User-Agent: Mozilla/5.0 (compatible;)");
    m_manager = new QNetworkAccessManager(this);
    connect(m_manager, SIGNAL(finished(QNetworkReply*)),this,SLOT(replyFinished(QNetworkReply*)));
    connect(m_manager, SIGNAL( sslErrors (QNetworkReply *,const QList<QSslError>&)),
            this, SLOT(sslErrors(QNetworkReply *,const QList<QSslError>&)));
}

QString Mailbox::doGet(QString url, bool header)
{
    headers = header;
    host = QUrl(url).host();
    scheme = QUrl(url).scheme();
    m_request.setUrl(QUrl(url));
    m_manager->get( m_request );
    eLoop.exec();
    return resultData;
}
QString Mailbox::doPost(QString url, QString vars, bool header)
{
    headers = header;
    host = QUrl(url).host();
    scheme = QUrl(url).scheme();
    m_request.setUrl(QUrl(url));
    m_manager->post( m_request, vars.toAscii());
    eLoop.exec();
    return resultData;
}
void Mailbox::replyFinished(QNetworkReply *reply)
{
    if(headers)
    {
        for (int i = 0; i < reply->rawHeaderList().size(); ++i)
        {
            headersList += reply->rawHeaderList().at(i);
            headersList += " : ";
            headersList += reply->rawHeader(reply->rawHeaderList().at(i));
            headersList += "\n";
        }
        resultData = headersList;
    }
    resultData += reply->readAll();
    QUrl redir = reply->attribute(QNetworkRequest::RedirectionTargetAttribute).toUrl();
    if (!redir.isEmpty())
    {
        if(redir.host() == "")
        {
            redir.setScheme(scheme);
            redir.setHost(host);
        }
        else
        {
            host = QUrl(redir).host();
            scheme = QUrl(redir).scheme();
        }
        m_request.setUrl(redir);
        m_manager->get(m_request);
    }
    else {
        eLoop.quit();
    }
    reply->deleteLater();

}
void Mailbox::sslErrors(QNetworkReply *reply,const QList<QSslError> &errors)
{
    reply->ignoreSslErrors();
}
QString Mailbox::getMailbox() const
{
    return mailbox;
}
QString Mailbox::getUser() const
{
    return user;
}

QString Mailbox::getPassword() const
{
    return password;
}
Mailbox::~Mailbox()
{
    if(m_manager) {
        m_manager->deleteLater();
    }
}
QString Mailbox::escape(QString q)
{
    QUrl escaped(q);
   return QString(escaped.toEncoded());
}
QString Mailbox::unescape(QString q)
{
   return QString(QUrl::fromPercentEncoding(q.toAscii()));
}
