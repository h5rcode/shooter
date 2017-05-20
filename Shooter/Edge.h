#pragma once

#include "Vector2.h"

class Edge
{
public:
	Edge(const Vector2& v1, const Vector2& v2);

private:
	const Vector2& _v1;
	const Vector2& _v2;
};

