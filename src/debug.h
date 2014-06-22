#ifndef DEBUG_H
#define DEBUG_H

/*!
 * \file debug.h
 * \author yann feunteun
 * \brief This file provides the developer some useful tools to build this software.
 * \version 0.1
 * \date 06/03/2014
 */

#include <QDebug>

//#ifndef QT_NO_DEBUG

#define FATAL_ERROR(msg) qFatal(qPrintable(msg))
#define CRITICAL_ERROR(msg) qCritical(qPrintable(msg))
#define WARNING(msg) qWarning(qPrintable(msg))
#define DEBUG(msg) qDebug(qPrintable(msg))

//#endif

#endif
