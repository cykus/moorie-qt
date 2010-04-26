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

#ifndef CMSTATS_H
#define CMSTATS_H

#include <QString>
#include <QObject>
class CMStats
{
public:
    /**
     * State of the transfer file.
     */
    enum state
    {
            unprepared,
            prepared,
            startingTransfer,
            transfering,
            transferred,
            finalized,
            stateInvalid = -1
    };

    /**
     * Type of transfer file.
     */
    enum type
    {
            upload,
            download,
            typeInvalid = -1
    };

    CMStats();
    CMStats(int id, type t, state s, QString filePath, QString Hashcode, int mailbox);

    QString getId() const; //!< @return Transfer file id.
    type getType() const; //!< @return Transfer file type.
    state getState() const; //!< @return Transfer file state.
    QString getFilePath() const; //!< @return Transfer files file path.
    QString getHashcode() const; //!< @return Hashcode string.
    int getMailbox() const; //!< @return Mailbox ID.
    int getTotalSegmentsCount() const; //!< @return Number of segments.
    int getTransferredSegmentsCount() const; //!< @return Number of transfered segments.

    void setType(type t); //!< See getType()
    void setState(state newState); //!< See getState()
    void setFilePath(QString path); //!< See getFilePath()
    void setHashcode(QString hashcode); //!< See getHashcode()
    void setMailbox(int mailbox); //!< See getMailbox()
    void setTotalSegmentsCount(int partsCount); //!< See getTotalSegmentsCount()
    void setTransferredSegmentsCount(int partsTransferd); //!< See getTransferredSegmentsCount()

    static QString stateToLocaleString(state s);
    static QString stateToString(state s);
    static state stringToState(QString strState);
    static QString typeToLocaleString(type t);
    static QString typeToString(type t);
    static type stringToType(QString strType);

private:
        QString _id;
        type _type;
        state _actState;
        QString _filePath;
        QString _hashcode;
        int _mailbox;
        int _segmentsCount, _segmentsTransferred;
};

#endif // CMSTATS_H
