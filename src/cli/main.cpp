#include <QtCore/QCoreApplication>
#include <src/lib/libmoorie.h>
#include <iostream>
#include <QStringList>
#include <QString>
#include "anyoption.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    AnyOption *opt = new AnyOption();
    opt->setVerbose(); /* print warnings about unknown options */
    opt->autoUsagePrint(true); /* print usage for bad options */
    opt->addUsage( "" );
    opt->addUsage( "Usage: " );
    opt->addUsage( "" );
    opt->addUsage( " -h  --help  		Prints this help " );
    opt->addUsage( " -s  --size 42 	        Image Size " );
    opt->addUsage( " -z  --zip  		Compress Image " );
    opt->addUsage( " -c   			convert Image " );
    opt->addUsage( "     --name image.jpg	Image Name " );
    opt->addUsage( "" );
    opt->setFlag(  "help", 'h' );   /* a flag (takes no argument), supporting long and short form */
    opt->setOption(  "size", 's' ); /* an option (takes an argument), supporting long and short form */
    opt->setOption(  "name" );      /* an option (takes an argument), supporting only long form */
    opt->setFlag( 'c' );            /* a flag (takes no argument), supporting only short form */
    opt->processCommandArgs( argc, argv );
    if( ! opt->hasOptions()) { /* print usage if no options */
                    opt->printUsage();
                    delete opt;
                    return 0;
            }
    /* 6. GET THE VALUES */
    if( opt->getFlag( "help" ) || opt->getFlag( 'h' ) )
            opt->printUsage();
    if( opt->getValue( 's' ) != NULL  || opt->getValue( "size" ) != NULL  )
            std::cout << "size = " << opt->getValue( 's' ) << endl ;
    if( opt->getValue( "name" ) != NULL )
        std::cout << "name = " << opt->getValue( "name" ) << endl ;
    cout << endl ;

    /* 7. GET THE ACTUAL ARGUMENTS AFTER THE OPTIONS */
    for( int i = 0 ; i < opt->getArgc() ; i++ ){
            cout << "arg = " <<  opt->getArgv( i ) << endl ;
    }

    /* 8. DONE */
    delete opt;

    Libmoorie moorie;
    std::cerr << qPrintable(moorie.hello());
    a.quit();
    return a.exec();
}
