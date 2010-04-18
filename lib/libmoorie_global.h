#ifndef MOORIE_GLOBAL_H
#define MOORIE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(MOORIE_LIBRARY)
#  define MOORIESHARED_EXPORT Q_DECL_EXPORT
#else
#  define MOORIESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // MOORIE_GLOBAL_H
