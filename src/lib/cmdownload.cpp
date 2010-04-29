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

#include "cmdownload.h"
#include <QDebug>

CMDownload::CMDownload(CMStats *stats ):
        CMTransfer(stats),
        doStop(false)
{
}
void CMDownload::run()
{
    while(!doStop)
    {
        CMStats::state state = getStats()->getState();

        if(needsResuming())
            resume();

        if( state == CMStats::unprepared )
        {
            if( prepare() )
                selectMailbox();
            startTransfer();

        }
        else if( state == CMStats::prepared )
        {
            startTransfer();
        }
        else if( state == CMStats::transferred )
        {
            finalize();
        }
        doStop =true;
    }
}
bool CMDownload::prepare(){
    myHash = HashManager::fromString(_stats->getHashcode());

    _stats->setState(CMStats::prepared);
    emitStatsChanged();
    return myHash->getInfo().valid;
}
bool CMDownload::selectMailbox(){}
bool CMDownload::startTransfer(){
    int selected = 0;
    for (int i = 0; i < myHash->getInfo().accounts.size(); ++i) {
        qDebug() << "name: " <<     myHash->getInfo().accounts.at(i).name;
        qDebug() << "login: " <<    myHash->getInfo().accounts.at(i).login ;
        qDebug() << "password: " << myHash->getInfo().accounts.at(i).password;
    };
    LOG(Log::Info, "saas:" +QString::number(myHash->getInfo().accounts.size()) + "22");
    QString mailbox = myHash->getInfo().accounts[selected].name;
    QString login = myHash->getInfo().accounts[selected].login;
    QString passwd = myHash->getInfo().accounts[selected].password;

    myMailBox = MailboxFactory::Instance().Create(mailbox, login, passwd);
    if (myMailBox) {
        LOG(Log::Info, "Logowanie do: " + myHash->getInfo().accounts[selected].name);
        myHash->getInfo().accounts[selected].name;
        if (myMailBox->loginRequest() == 0) {
            LOG(Log::Info, "Zalogowano: ");
        }
    }
}
bool CMDownload::finalize(){}
bool CMDownload::resume(){}
bool CMDownload::needsResuming(){}
bool CMDownload::abort(){}
