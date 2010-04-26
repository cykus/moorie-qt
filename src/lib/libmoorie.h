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

#ifndef LIBMOORIE_H
#define LIBMOORIE_H

#include "libmoorie_global.h"
#include "cmdownload.h"
#include "cmupload.h"
#include "cmstats.h"
#include <QString>
#include <QTextCodec>
#include <QHash>

class MOORIESHARED_EXPORT Libmoorie {
public:
    Libmoorie();
    QHash<int,CMTransfer*> transfers; //!< Hash wszystkich transferów
    QHash<int,CMStats*> stats; //!< Hash wszystkich transferów powiązanych z transferami
    int addDownloadTransfer(CMStats::type t,
                            CMStats::state s,
                            QString hashcode,
                            QString filePath,
                            int mailbox
                            ); //!< Dodaje nowe pobieranie zwracając jego ID
private:
    int transfersCount; //!< licznik transferów
    int maxRunTransfers; //!< Maksymalna liczba uruchomionych transferów
};

#endif // LIBMOORIE_H
