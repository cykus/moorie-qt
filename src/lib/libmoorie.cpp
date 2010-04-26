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

#include "libmoorie.h"
#include <iostream>

Libmoorie::Libmoorie():
        transfersCount(0)
{
    QTextCodec::setCodecForTr (QTextCodec::codecForName ("UTF-8"));
    QTextCodec::setCodecForCStrings ( QTextCodec::codecForName ("UTF-8"));
    QTextCodec::setCodecForLocale ( QTextCodec::codecForName ("UTF-8"));
}
int Libmoorie::addDownloadTransfer(CMStats::type t,
                                   CMStats::state s,
                                   QString hashcode,
                                   QString filePath,
                                   int mailbox)
{
    CMStats stat(transfersCount,t, s,hashcode,filePath,mailbox); //!<< tworzymy obiekt "statów" dla konkretnego transferu
    stats.insert(transfersCount, &stat); //!< wrzucamy staty do hasha
    CMDownload file(stats.value(transfersCount)); //!< wrzucamy wskaźnik na staty do obieku "transferu"
    transfers.insert(transfersCount,&file); // wrzucamy transfer do hasha
    return transfersCount++; //!< zwracamy numer transferu/statów i zwiększamy index transferów o jeden
}
