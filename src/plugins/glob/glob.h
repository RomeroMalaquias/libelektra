/**
 * @file
 *
 * @brief
 *
 * @copyright BSD License (see doc/COPYING or http://www.libelektra.org)
 */

#ifndef ELEKTRA_PLUGIN_GLOB_H
#define ELEKTRA_PLUGIN_GLOB_H

#include <kdbplugin.h>

#include <stdlib.h>
#include <string.h>
#include <fnmatch.h>

int elektraGlobOpen(Plugin *handle, Key *errorKey);
int elektraGlobClose(Plugin *handle, Key *errorKey);
int elektraGlobGet(Plugin *handle, KeySet *ks, Key *parentKey);
int elektraGlobSet(Plugin *handle, KeySet *ks, Key *parentKey);
int elektraGlobError(Plugin *handle, KeySet *ks, Key *parentKey);

Plugin *ELEKTRA_PLUGIN_EXPORT(glob);

#endif
