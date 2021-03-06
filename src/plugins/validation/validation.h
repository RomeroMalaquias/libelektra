/**
 * @file
 *
 * @brief
 *
 * @copyright BSD License (see doc/COPYING or http://www.libelektra.org)
 */

#ifndef ELEKTRA_PLUGIN_VALIDATION_H
#define ELEKTRA_PLUGIN_VALIDATION_H

#include <sys/types.h>
#include <regex.h>

#include <kdbplugin.h>
#include <kdberrors.h>

int elektraValidationOpen(Plugin *handle, Key *errorKey);
int elektraValidationClose(Plugin *handle, Key *errorKey);
int elektraValidationGet(Plugin *handle, KeySet *ks, Key *parentKey);
int elektraValidationSet(Plugin *handle, KeySet *ks, Key *parentKey);
int elektraValidationError(Plugin *handle, KeySet *ks, Key *parentKey);

Key *ksLookupRE(KeySet *ks, const regex_t *regexp);

Plugin *ELEKTRA_PLUGIN_EXPORT(validation);

#endif
