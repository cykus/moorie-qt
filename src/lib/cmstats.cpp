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

#include "cmstats.h"

CMStats::CMStats()
{
}
CMStats::CMStats(int id, type t, state s, QString filePath, QString hashcode, int mailbox):
        _id(id),
        _type(t),
        _actState(s),
        _filePath(filePath),
        _hashcode(hashcode),
        _mailbox(mailbox)
{
}

QString CMStats::getId() const
{ return _id; }
CMStats::type CMStats::getType() const
{ return _type; }

CMStats::state CMStats::getState() const
{ return _actState; }

QString CMStats::getFilePath() const
{ return _filePath; }

QString CMStats::getHashcode() const
{ return _hashcode; }

int CMStats::getMailbox() const
{ return _mailbox; }

int CMStats::getTransferredSegmentsCount() const
{ return _segmentsTransferred; }

int CMStats::getTotalSegmentsCount() const
{ return _segmentsCount; }

void CMStats::setType(CMStats::type type)
{ _type = type; }

void CMStats::setState(CMStats::state newState)
{ _actState = newState; }

void CMStats::setFilePath(QString path)
{ _filePath = path; }

void CMStats::setHashcode(QString hashcode)
{ _hashcode = hashcode; }

void CMStats::setMailbox(int mailbox)
{ _mailbox = mailbox; }

void CMStats::setTotalSegmentsCount(int partsCount)
{ _segmentsCount = partsCount; }

void CMStats::setTransferredSegmentsCount(int partsTransferred)
{ _segmentsTransferred = partsTransferred; }

QString CMStats::stateToLocaleString(state s)
{
    switch(s)
    {
    case unprepared : return QObject::tr("unprepared"); break;
    case prepared : return QObject::tr("prepared"); break;
    case startingTransfer : return QObject::tr("starting transfer"); break;
    case transfering : return QObject::tr("transfering"); break;
    case segmentTransferred : return QObject::tr("segment transferred"); break;
    case transferred : return QObject::tr("transferred"); break;
    case finalized : return QObject::tr("done"); break;
    }
    return QString::Null();
}

QString CMStats::stateToString(state s)
{
    switch(s)
    {
    case unprepared : return "unprepared"; break;
    case prepared : return "prepared"; break;
    case startingTransfer : return "starting_transfer"; break;
    case transfering : return "transfering"; break;
    case segmentTransferred : return "segment_transferred"; break;
    case transferred : return "transferred"; break;
    case finalized : return "finalized"; break;
    }
    return QString::Null();
}

CMStats::state CMStats::stringToState(const QString strState)
{
    if( strState == "unprepared" ) return unprepared;
    else if( strState == "prepared" ) return prepared;
    else if( strState == "starting_transfer") return startingTransfer;
    else if( strState == "transfering" ) return transfering;
    else if( strState == "segment_transferred" ) return segmentTransferred;
    else if( strState == "transferred" ) return transferred;
    else if( strState == "finalized" ) return finalized;

    return stateInvalid;
}

QString CMStats::typeToLocaleString(type t)
{
    switch(t)
    {
    case upload : return QObject::tr("upload"); break;
    case download : return QObject::tr("download"); break;
    }
    return QString::Null();
}

QString CMStats::typeToString(type t)
{
    switch(t)
    {
    case upload : return "upload"; break;
    case download : return "download"; break;
    }
    return QString::Null();
}

CMStats::type CMStats::stringToType(const QString strType)
{
    if( strType == "upload" ) return upload;
    else if( strType == "download" ) return download;

    return typeInvalid;
}
