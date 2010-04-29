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

#include "googleappsmailbox.h"

namespace {
    Mailbox* Create(const QString& name,
                    const QString& username,
                    const QString& password)
    {
        return new GoogleAppsMailbox(name, username, password);
    }
}

const QString c_names[] = {
    "gala.net",
    "gazeta.pl",
    "mailbox.hu",
    "vivapolska.tv",
    "gde.ru",
    "klikni.cz",
    "livedoor.com",
    "oneindia.in",
    "bigmir.net",
    "sify.com",
    QString()
};
const bool registered = MailboxFactory::Instance().Register(c_names, Create);

GoogleAppsMailbox::GoogleAppsMailbox(const QString &name, const QString &usr, const QString &passwd):
        Mailbox(name, usr, passwd),
        totalEmails( 0 )
{
}
int GoogleAppsMailbox::loginRequest()
{
    //const QRegExp moorhuntHashRegex("(<<a[a-h].*>>)");


    page = doGet("https://www.google.com/a/"+getMailbox());
    int pos = 0;
    QRegExp re3("GALX\\\".*value=\\\"(.*)\\\"./>");
    re3.setMinimal(true);
    if (re3.indexIn(page, pos) == -1)
        return 1;

    //LOG(Log::Info, page);
    const QString vars = QString("ltmpl=default&ltmplcache=2&continue=")
                + escape("https://mail.google.com/a/"+getMailbox()+"/")
                +"&service=mail&GALX="
                + escape(re3.cap(1))
                +"&rm=false&hl=pl&Email="+escape(getUser())
                +"&Passwd="+escape(getPassword())
                +"&rmShown=1";
    page = doPost("https://www.google.com/a/"+getMailbox()+"/LoginAction2?service=mail",vars, true);

    QString username = getUser();

    QRegExp re(username);
    QRegExp re2("&amp;");
    QRegExp authre("auth=([\\w\\d-]+)"); // To Do

    if (re.indexIn(page, pos) != -1)
    {
        QString url = re.cap(1);

        LOG(Log::Info, page + " <f");
        if(url.indexOf("answer=40695") != -1)
        {
            LOG(Log::Info, "Niestety, konto zostało wyłączone. - " + getMailbox());
            return 1;
        }
        url.replace(re2, "&");
        url = unescape(url);
        if (authre.indexIn(page, pos) != -1)
            auth = authre.cap(1);
            LOG(Log::Info, auth + " <s");
        return 0;
    }
    else
        return 1;
}
GoogleAppsMailbox::~GoogleAppsMailbox()
{
}
