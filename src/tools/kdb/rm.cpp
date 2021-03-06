/**
 * @file
 *
 * @brief
 *
 * @copyright BSD License (see doc/COPYING or http://www.libelektra.org)
 */

#include <rm.hpp>

#include <kdb.hpp>
#include <cmdline.hpp>

#include <iostream>

using namespace std;
using namespace kdb;

RemoveCommand::RemoveCommand()
{}

int RemoveCommand::execute(Cmdline const& cl)
{
	if (cl.arguments.size() != 1) throw invalid_argument("1 argument required");

	KeySet conf;
	Key x(cl.arguments[0], KEY_END);
	if (!x)
	{
		throw invalid_argument(cl.arguments[0] + " is not a valid keyname");
	}
	kdb.get(conf, x);

	if (!cl.recursive)
	{
		Key f = conf.lookup(x, KDB_O_POP);

		if (!f)
		{
			cerr << "Did not find the key" << endl;
			return 1;
		}
	} else {
		// do recursive removing
		KeySet ks = conf.cut (x);

		if (ks.size() == 0)
		{
			cerr << "Did not find any key" << endl;
			return 1;
		}
	}

	kdb.set(conf, x);

	return 0;
}

RemoveCommand::~RemoveCommand()
{}
