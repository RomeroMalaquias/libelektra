#include <command.hpp>

#include <key.hpp>

#include <sstream>
#include <iostream>
#include <iomanip>

using namespace kdb;

void printError(Key error)
{
	if (!error.getMeta<const Key>("error"))
	{
		// no error available
		return;
	}

	try{
		error.getMeta<std::string>("error");
		std::cerr << "number: " << error.getMeta<std::string>("error/number") << std::endl;
		std::cerr << "description: " << error.getMeta<std::string>("error/description") << std::endl;
		std::cerr << "ingroup: " << error.getMeta<std::string>("error/ingroup") << std::endl;
		std::cerr << "module: " << error.getMeta<std::string>("error/module") << std::endl;
		std::cerr << "at: " << error.getMeta<std::string>("error/file") << ":" << error.getMeta<std::string>("error/line") << std::endl;
		std::cerr << "reason: " << error.getMeta<std::string>("error/reason") << std::endl;
	} catch (KeyMetaException const& e)
	{
		std::cerr << "Error meta data is not set correctly by a plugin" << std::endl;
	}
}

void printWarnings(Key error)
{
	if (!error.getMeta<const Key>("warnings"))
	{
		// no warnings were issued
		return;
	}

	try{
		int nr = error.getMeta<int>("warnings");
		std::cerr << nr+1 << " Warnings were issued" << std::endl;

		for (int i=0; i<=nr; i++)
		{
			std::ostringstream name;
			name << "warnings/#" << std::setfill('0') << std::setw(2) << i;
			std::cerr << name.str() << ": " << error.getMeta<std::string>(name.str()) << std::endl;
			std::cerr << "number: " << error.getMeta<std::string>(name.str() + "/number") << std::endl;
			std::cerr << "description: " << error.getMeta<std::string>(name.str() + "/description") << std::endl;
			std::cerr << "ingroup: " << error.getMeta<std::string>(name.str() + "/ingroup") << std::endl;
			std::cerr << "module: " << error.getMeta<std::string>(name.str() + "/module") << std::endl;
			std::cerr << "at: " << error.getMeta<std::string>(name.str() + "/file") << ":"
				<< error.getMeta<std::string>(name.str() + "/line") << std::endl;
			std::cerr << "reason: " << error.getMeta<std::string>(name.str() + "/reason") << std::endl;
		}

	} catch (KeyMetaException const& e)
	{
		std::cerr << "Warnings meta data not set correctly by a plugin" << std::endl;
	}
}