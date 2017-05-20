#pragma once

#include "Edge.h"

class Block
{
public:
	Block(const Edge** edges);

private:
	const Edge** _edges;
};

