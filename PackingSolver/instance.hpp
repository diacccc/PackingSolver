#pragma once

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <algorithm>
#include <vector>
#include <map>
#include <ctime>

#define INF 1008600
#define TimeLimit 10000
#define D 20000

using namespace std;

typedef int32_t Length;
typedef int32_t Area;
typedef int32_t Position;
typedef int32_t Index;
typedef int32_t Count;
typedef int32_t Value;
typedef char	Orientation;


#pragma region Common Struct
/**********************************************************************/

struct Coord {
	Length x;
	Length y;

	Coord(Length _x, Length _y) : x(_x), y(_y) {}
};

std::ostream& operator<<(std::ostream& os, Coord o);

/**********************************************************************/

struct Rectangle {
	Length w;
	Length h;

	Rectangle():w(0), h(0) {};
	Rectangle(Length _w, Length _h) : w(_w), h(_h) {}
	Area area() const { return w * h; }
	bool AbleInsert(Rectangle r) { return (w >= r.w && h >= r.h) || (w >= r.h&& h >= r.w); }

};

bool operator==(Rectangle const& a, Rectangle const& b);

bool operator<(Rectangle const& a, Rectangle const& b);


std::ostream& operator<<(std::ostream& os, Rectangle Rec);



/**********************************************************************/

struct Item {
	Index type;
	Rectangle rec;
	Count num;

	Item() : type(0), rec(Rectangle(0, 0)), num(0) {}
	Item(Index _type, Rectangle _rec, Count _num) : type(_type), rec(_rec), num(_num) {}
	Length width(bool rotate) const { return (!rotate) ? rec.w : rec.h; }
	Length height(bool rotate) const { return (!rotate) ? rec.h : rec.w; }
};

std::ostream& operator<<(std::ostream& os, Item I);

/**********************************************************************/
#pragma endregion

#pragma region Instance

class Instance
{
public:

	Instance(const char* filename);
	//Instance(const Count n, const Rectangle Bin, const vector<Item> items);

	inline Count item_types_number()	const { return items_.size(); }
	inline Count item_number()			const { return item_number_; }

	inline Index type(Rectangle r) { return Type_[r]; }

	inline Rectangle Bin() const { return Bin_; }

	inline Area item_area()		const { return item_area_; }
	inline Area mean_area()		const { return item_area_ / item_number_; }

	inline const Item& item_type(Index i) const { return items_[i]; }

	inline const std::vector<Item>& items()   const { return items_; }
private:

	Count item_number_ = 0;
	Area item_area_ = 0;
	Rectangle Bin_;

	map<Rectangle, Index> Type_;

	vector<Item> items_;

	void compute_item_number();
	void compute_item_area();
};

#pragma endregion

struct CPU {
	double t;
	int64_t branch = 0;
};