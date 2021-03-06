#include <editor.hpp>

#include <kdb.hpp>
#include <modules.hpp>
#include <cmdline.hpp>
#include <external.hpp>
#include <keysetio.hpp>

#include <unistd.h>

#include <export.hpp>
#include <import.hpp>

#include <iostream>
#include <string>

#include <merging/threewaymerge.hpp>
#include <merging/metamergestrategy.hpp>
#include <mergehelper.hpp>

using namespace kdb;
using namespace kdb::tools;
using namespace kdb::tools::merging;
using namespace std;

EditorCommand::EditorCommand()
{
}

EditorCommand::~EditorCommand()
{
}

void EditorCommand::tmpFile()
{
#ifndef _WIN32
	const char * tmpvar = getenv ("TMPDIR");
	if (!tmpvar)
	{
		tmpvar = "/tmp";
	}
	filename = tmpvar;
	filename += "/elektra-test.XXXXXX";
	char * fn = static_cast<char*>(malloc(filename.length()+1));
	strcpy(fn, filename.c_str());
	fd = mkstemp (fn);
	filename = std::string(fn);
	close(fd);
	free (fn);
#endif
}

bool runAllEditors(std::string filename)
{
	using namespace kdb;
	std::string dirname = "/sw/kdb/current/";
	KDB kdb;
	KeySet conf;
	kdb.get(conf, dirname);

	Key k = conf.lookup(dirname+"editor");
	if (k)
	{
		std::string editor = k.get<std::string>().c_str();
		if (runEditor(editor, filename))
		{
			return true;
		} else {
			std::cerr << "Could not run editor " << editor << std::endl;
		}
	}
	if (runEditor ("/usr/bin/sensible-editor", filename)) return true;
	if (runEditor ("/usr/bin/editor", filename)) return true;
	if (runEditor ("/usr/bin/vi", filename)) return true;
	return false;
}

int EditorCommand::execute(Cmdline const& cl)
{
	int argc = cl.arguments.size ();
	if (argc < 1)
	{
		throw invalid_argument ("wrong number of arguments, 1 needed");
	}

#ifndef _WIN32
	throw invalid_argument ("kdb-editor not available for windows");
#endif
	Key root (cl.arguments[0], KEY_END);

	KeySet ours;
	KDB kdb;
	kdb.get (ours, root);
	KeySet oursToEdit = ours.cut (root);

	// export it to file
	string format = cl.format;
	if (argc > 1) format = cl.arguments[1];

	Modules modules;
	PluginPtr plugin = modules.load(format);

	tmpFile();
	if (cl.verbose) std::cout << "filename set to " << filename << std::endl;
	Key errorKey(root);
	errorKey.setString(filename);

	if (plugin->set(oursToEdit, errorKey) == -1)
	{
		printWarnings(cerr, errorKey);
		printError(cerr, errorKey);
		return 11;
	}

	printWarnings(cerr, errorKey);


	// start editor
	if (cl.verbose) std::cout << "running editor with " << filename << std::endl;
	if (!cl.editor.empty())
	{
		if (!runEditor (cl.editor, filename))
		{
			std::cerr << "Could not run editor " << cl.editor << std::endl;
			return 12;
		}
	} else {
		if (!runAllEditors(filename))
		{
			std::cerr << "Could not run any editor, please change /sw/kdb/current/editor" << std::endl;
			return 12;
		}
	}

	// import from the file
	KeySet importedKeys;
	plugin->get(importedKeys, errorKey);
	importedKeys = importedKeys.cut(root);

	printWarnings (cerr, errorKey);
	printError (cerr, errorKey);

	ThreeWayMerge merger;
	MergeHelper helper;

	helper.configureMerger (cl, merger);
	MergeResult result = merger.mergeKeySet (
			MergeTask (BaseMergeKeys (oursToEdit, root), OurMergeKeys (oursToEdit, root),
					TheirMergeKeys (importedKeys, root), root));

	helper.reportResult (cl, result, cout, cerr);

	int ret = 13;
	if (!result.hasConflicts ())
	{
		if (cl.verbose)
		{
			cout << "The merged keyset with strategy " << cl.strategy << " is:" << endl;
			cout << result.getMergedKeys();
		}

		KeySet resultKeys = result.getMergedKeys();
		if (cl.verbose) std::cout << "about to write result keys " << resultKeys << std::endl;
		ours.append(resultKeys);
		kdb.set (ours, root);
		if (cl.verbose) std::cout << "successful, cleaning up " << filename << std::endl;
		unlink(filename.c_str());
		ret = 0;
	}
	else
	{
		std::cout << "Import not successful, please import and remove \"" << filename << '"' << std::endl;
	}

	return ret;
}

