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

#ifndef MOORIE_H
#define MOORIE_H

#include <QObject>
#include <iostream>
#include "src/lib/libmoorie.h"
#include "src/lib/log.h"
class moorie : public QObject
{
Q_OBJECT

public:
    explicit moorie(QObject *parent = 0);
    void addDownloadTransfer(CMStats::type t,
                            CMStats::state s,
                            QString hashcode,
                            QString filePath,
                            int mailbox
                            );
private:
    LibMoorie moor;
public slots:
    void refreashStats(CMStats *s);
    void showLog(const int ,const QString &);
};

#endif // MOORIE_H
