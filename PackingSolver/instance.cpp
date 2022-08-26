// PackingSolver.cpp: 定义应用程序的入口点。
//

#include "instance.hpp"

#pragma region Common Struct

std::ostream& operator<<(std::ostream& os, Coord o)
{
	os << " (" << o.x << "," << o.y << ") ";
	return os;
}

std::ostream& operator<<(std::ostream& os, Rectangle rec)
{
	os << " Width " << rec.w << " Height " << rec.h;
	return os;
}

bool operator==(Rectangle const& a, Rectangle const& b)
{
	return a.w == b.w && a.h == b.h;
}

bool operator<(Rectangle const& a, Rectangle const& b)
{
	return a.area() < b.area();
}

std::ostream& operator<<(std::ostream& os, Item I)
{
	os
		<< " Type ID " << I.type << I.rec
		<< " Copies " << I.num;
	return os;
}

#pragma endregion


#pragma region Instance

Instance::Instance(const char* filename)
{
	ifstream infile(filename);
	Count n;
	Length j, w, h, d, b, p;
	Index t = 0;
	Rectangle r;

	if (!infile.is_open()) cout << "failed to open the input file: " << filename << endl;

	infile >> n >> r.w >> r.h;

	Bin_ = r;

	for (Index i = 0; i < n; ++i)
	{
		infile >> j >> w >> h >> d >> b >> p;
		if (w < h) swap(w, h);
		r.w = w, r.h = h;
		if (!type(r)) items_.push_back(Item(t, r, 1)), Type_[r] = t++;
		else items_[type(r)].num += 1;
	}

	Instance::compute_item_area();
	Instance::compute_item_number();
	cout << "Successfully build an instance!" << endl;
}

void Instance::compute_item_area()
{
	for (Index i = 0; i < item_types_number(); ++i)
	{
		item_area_ += item_type(i).num * item_type(i).rec.area();
	}
}

void Instance::compute_item_number()
{
	for (Index i = 0; i < item_types_number(); ++i)
	{
		item_number_ += item_type(i).num;
	}
}

#pragma endregion


