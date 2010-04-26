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

#include "moorie.h"

moorie::moorie(QObject *parent) :
    QObject(parent)
{
}
void moorie::refreashStats(CMStats *s)
{
    std::cerr << qPrintable(CMStats::stateToLocaleString(s->getState()));
}
void moorie::addDownloadTransfer(CMStats::type t,CMStats::state s,QString hashcode,QString filePath,int mailbox)
{
    int transferID = moor.addDownloadTransfer(t,s,hashcode,filePath,mailbox);

    connect( moor.transfers.value(transferID),
            SIGNAL(statsChanged(CMStats*)),
            SLOT(refreashStats(CMStats*)), Qt::QueuedConnection);

    moor.transfers.value(transferID)->start();
}
