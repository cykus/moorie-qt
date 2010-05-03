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

#include <QStringList>
#include <QString>
#include <QTextStream>
#include <QObject>
#include <QFile>
#include "anyoption.h"
#include "moorie.h"
#include "hashmanager.h"
#include "hash.h"
#include "tools.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTextStream cin(stdin, QIODevice::ReadOnly);
    QTextStream cout(stdout, QIODevice::WriteOnly);
    QTextStream cerr(stderr, QIODevice::WriteOnly);

    // usage
    moorie moorie;
    QString hash = "";
    QString pass = "";
    QString path = "";
    int mailbox  = 1 ;

    bool download = false;
    /************************************************************/
    AnyOption *opt = new AnyOption();
    opt->setVerbose(); /* print warnings about unknown options */
    opt->autoUsagePrint(true); /* print usage for bad options */
    opt->addUsage( "Usage: " );
    opt->addUsage( "" );
    opt->addUsage( " -h  --help\n   Prints help" );
    opt->addUsage( "" );
    opt->addUsage( " --hash <file> -f <file>\n   Hash file " );
    opt->addUsage( " --password <password> -p <password>\n   Hash file " );
    opt->addUsage( " --path <path>\n   download path " );
    opt->addUsage( " --mailbox <number> -m <number>\n   Select mailbox " );
    //opt->addUsage( " -s \"hashcode\" --shash \"hashcode\" \n   Hash string " );
    opt->addUsage( "" );
    opt->setFlag(  "help", 'h' );   /* a flag (takes no argument), supporting long and short form */
    opt->setOption(  "hash", 'f' ); /* an option (takes an argument), supporting long and short form */
    opt->setOption(  "password", 'p' ); /* an option (takes an argument), supporting long and short form */
    opt->setOption(  "mailbox", 'm' ); /* an option (takes an argument), supporting long and short form */
    opt->setOption(  "path"); /* an option (takes an argument), supporting long and short form */
    opt->processCommandArgs( argc, argv );
    if( ! opt->hasOptions()) { /* print usage if no options */
        opt->printUsage();
        delete opt;
        return 0;
    }
    /*GET THE VALUES */
    if( opt->getFlag( 'h' )  || opt->getFlag( "help" ) )
        opt->printUsage();
    if( opt->getValue( 'p' ) != NULL || opt->getValue( "password" ) != NULL )
        pass = opt->getValue( 'p' );
    if( opt->getValue( "path" ) != NULL )
        path = opt->getValue( "path" );
    if( opt->getValue( 'm' ) != NULL )
        mailbox = QString(opt->getValue( "m" )).toInt();

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
                QString myPass;
                if (hhash->getInfo().accessPasswd.length() == 32) {
                    myPass = getMD5(pass);
                } else
                    myPass = pass;
                if(myPass.compare( hhash->getInfo().accessPasswd) == 0)
                {
                    moorie.addDownloadTransfer(CMStats::download,
                                             CMStats::unprepared,
                                             path,
                                             hash,
                                             mailbox-1);
                }
                else cout << "Error: password incorrect!" << endl;

            }
            else cout << "Error: hashcode incorrect" << endl;

        }
        catch (std::exception& e)
        {
            cout << "Error! " << e.what() << endl;
        }
    }

    return a.exec();
}
