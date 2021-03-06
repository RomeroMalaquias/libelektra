/**
 * @file
 *
 * @brief
 *
 * @copyright BSD License (see doc/COPYING or http://www.libelektra.org)
 */

#include <kdbplugin.h>
#include <kdberrors.h>


int elektraErrorGet(Plugin *handle, KeySet *ks, Key *parentKey);
int elektraErrorSet(Plugin *handle, KeySet *ks, Key *parentKey);
Plugin *ELEKTRA_PLUGIN_EXPORT(error);
