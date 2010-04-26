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

#include <QtCore/QCoreApplication>
#include <iostream>
#include <QStringList>
#include <QString>
#include <QDebug>
#include <QFile>
#include <QSharedPointer>
#include "anyoption.h"
#include "src/lib/libmoorie.h"
#include "src/lib/hashmanager.h"
#include "src/lib/tools.h"
#include "src/lib/hash.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString hash;
    QString pass = "p2mforum.info";
    bool download = false;
    /************************************************************/
    AnyOption *opt = new AnyOption();
    opt->setVerbose(); /* print warnings about unknown options */
    opt->autoUsagePrint(true); /* print usage for bad options */
    opt->addUsage( "" );
    opt->addUsage( "Usage: " );
    opt->addUsage( "" );
    opt->addUsage( " -h  --help                         Prints help " );
    opt->addUsage( " -f  --hash file.txt                Hash file " );
    opt->addUsage( "" );
    opt->setFlag(  "help", 'h' );   /* a flag (takes no argument), supporting long and short form */
    opt->setOption(  "hash", 'f' ); /* an option (takes an argument), supporting long and short form */
    opt->processCommandArgs( argc, argv );
    if( ! opt->hasOptions()) { /* print usage if no options */
        opt->printUsage();
        delete opt;
        return 0;
    }
    /*GET THE VALUES */
    if( opt->getFlag( "help" ) || opt->getFlag( 'h' ) )
        opt->printUsage();
    if( opt->getValue( 'f' ) != NULL  || opt->getValue( "hash" ) != NULL  )
    {
        QFile file( QString(opt->getValue( 'f' )) );
        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream in(&file);
            while (!in.atEnd()) {
                hash += in.readLine();
            }
            download = true;
        }
    }

    /*DONE */
    delete opt;

    if (download) {
        try
        {
            Hash *hhash(HashManager::fromString(hash));
            if (hhash->getInfo().valid)
            {
                std::string myPass;
                if (hhash->getInfo().accessPasswd.length() == 32) {
                    myPass = getMD5((unsigned char*)pass.toStdString().c_str());
                } else
                    myPass = pass.toStdString().c_str();

                if(myPass.compare( hhash->getInfo().accessPasswd.toLatin1()) == 0)
                {
                    Libmoorie moor;
                    moor.addDownloadTransfer(CMStats::download,
                                                       CMStats::unprepared,
                                                       "sss/sss\n",
                                                       hash,
                                                       0);
                }
                else std::cerr << std::endl << "Blad: Podane haslo pobierania jest nieprawidlowe!" << std::endl << std::endl;

            }
            else std::cerr << "Niepoprawny hashcode" << std::endl;

        }
        catch (std::exception& e)
        {
            std::cerr << "Blad! " << e.what() << std::endl;
        }
    }
    exit(1);
    return a.exec();
}
