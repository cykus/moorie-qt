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

#ifndef CMTRANSFER_H
#define CMTRANSFER_H

#include <QThread>
#include "cmstats.h"
#include "log.h"

class CMTransfer : public QThread
{
        Q_OBJECT

public:
    CMTransfer(CMStats *stats);
    virtual void run() = 0;
    virtual bool prepare() = 0;

    virtual bool selectMailbox() = 0;

    virtual bool startTransfer() = 0;
    virtual bool finalize() = 0;

    virtual bool resume() = 0;
    virtual bool needsResuming() = 0;

    virtual bool abort() = 0;

    CMStats *getStats();

signals:
    void statsChanged(CMStats *stats);
    //void transferFinished(Qp2mTransferFile*);

protected:
    void emitStatsChanged();
    CMStats *_stats;
};

#endif // CMTRANSFER_H
