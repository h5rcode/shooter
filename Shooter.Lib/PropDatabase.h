#pragma once

#include <map>
#include <string>

#include "IPropDatabase.h"

using namespace Shooter::WorldDatabase::Props;

namespace Shooter {
	namespace WorldDatabase {
		namespace Props {
			class PropDatabase : public IPropDatabase {
			public:
				PropDatabase(std::string fileName);

			public:
				PropDescriptor& getProp(std::string& id);

			private:
				std::map<std::string, PropDescriptor> _props;
			};
		}
	}
}