/* gcc -Wall -g elektra_set.c -o elektra-set `pkg-config --cflags --libs elektra` */
/* Thanks to
 * Kai-Uwe Behrmann" <ku.b@gmx.de>
 * for that example
 *
 * to clean up after executing this example you have to use:
 *  kdb rm user/sw/MyApp/Tests/TestKey1
 */

#include <kdb.h>
#include <stdio.h>

void print_warnings(Key * err)
{
	const Key *meta = 0; keyRewindMeta(err);
	while((meta = keyNextMeta(err)) != 0)
	{
		printf("%s:\t%s\n",
				keyName(meta), 
				keyString(meta)); 
	} 
}

/** After writing the key this function rereads the key and print it*/
void check_key()
{
	Key * error_key = keyNew(KEY_END);
	KDB * kdb_handle = kdbOpen(error_key);
	Key * top = keyNew(KEY_END);
	int rc = keySetName(top, "user/sw/MyApp"); // == 14
	KeySet * ks = ksNew(0);
	rc = kdbGet(kdb_handle, ks, top);
	Key * key = keyNew(KEY_END);
	rc = keySetName(key, "user/sw/MyApp/Tests/TestKey1"); // == 14
	Key * result = ksLookup(ks, key, KDB_O_NONE);
	const char * key_name = keyName(result);
	const char * key_value = keyString(result);
	const char * key_comment = keyString(keyGetMeta(result, "comment"));
	printf("key: %s value: %s comment: %s", key_name, key_value, key_comment);
	ksDel(ks);
	keyDel(key);
	keyDel(top);
	kdbClose(kdb_handle, error_key);
	keyDel(error_key);
}

// typical usage of Elektra
int main()
{
	Key * error_key = keyNew(KEY_END);
	KDB * kdb_handle = kdbOpen(error_key);
	Key * top = keyNew(KEY_END);
	int rc = keySetName(top, "user/sw/MyApp");

	KeySet * ks = ksNew(0);
	rc = kdbGet(kdb_handle, ks, top);

	Key * key = keyNew(KEY_END);
	rc = keySetName(key, "user/sw/MyApp/Tests/TestKey1"); // == 31
	rc = keySetString(key, "NULLTestValue"); // == 14
	rc = keySetMeta(key, "comment", "NULLTestComment"); // == 16
	ksAppendKey(ks, key); // == 1
	rc = keyNeedSync(key);
	rc = kdbSet(kdb_handle, ks, top); // == -1
	print_warnings(top);
	keyDel(top);
	ksDel(ks);
	kdbClose(kdb_handle, error_key);
	keyDel(error_key);

	check_key();

	return 0;
}
