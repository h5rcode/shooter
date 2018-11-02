#pragma once

#include "PropDescriptor.h"

namespace Shooter {
	namespace WorldDatabase {
		namespace Props {
			class IPropDatabase {
			public:
				virtual PropDescriptor& getProp(std::string& id) = 0;
			};
		}
	}
}