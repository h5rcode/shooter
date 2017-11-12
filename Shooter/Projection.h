#pragma once

class Projection {
public:
	Projection(double min, double max);

public:
	bool overlaps(Projection& projection) const;

private:
	double _min;
	double _max;
};