/**
* \file
*
* \brief Header for logchange plugin
*
* \copyright BSD License (see doc/COPYING or http://www.libelektra.org)
*
*/

#ifndef ELEKTRA_PLUGIN_LOGCHANGE_H
#define ELEKTRA_PLUGIN_LOGCHANGE_H

#include <kdbplugin.h>


int elektraLogchangeGet(Plugin *handle, KeySet *ks, Key *parentKey);
int elektraLogchangeSet(Plugin *handle, KeySet *ks, Key *parentKey);

Plugin *ELEKTRA_PLUGIN_EXPORT(logchange);

#endif