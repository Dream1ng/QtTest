#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(QSS_LIB)
#  define QSS_EXPORT Q_DECL_EXPORT
# else
#  define QSS_EXPORT Q_DECL_IMPORT
# endif
#else
# define QSS_EXPORT
#endif
