#pragma once
#include "instance.hpp"
#include "solution.hpp"

using namespace std;

class Heuristic {
public:
	inline bool able_rotate() const { return rotate; }
	inline Value normal(Value x) { return x >= 0 ? x : INF; }

	pair<Value, bool> SelectPair(Rectangle S, Rectangle I, Index SelectionRule)
	{
		pair<Value, bool> tmp;

		switch (SelectionRule)
		{
			case 0:
			if (S.w >= I.w && S.h >= I.h)
				tmp.first = S.area() - I.area(), tmp.second = 0;
			else
				tmp.first = S.area() - I.area(), tmp.second = 1;
			break;

			case 1:
			if (normal(S.w - I.w) < normal(S.w - I.h))
				tmp.first = normal(S.w - I.w), tmp.second = 0;
			else
				tmp.first = normal(S.w - I.h), tmp.second = 1;
			break;

			case 2:
			if (normal(S.h - I.w) < normal(S.h - I.h))
				tmp.first =  normal(S.h - I.w), tmp.second = 1;
			else
				tmp.first =  normal(S.h - I.h), tmp.second = 0;
			
			default:
			break;
		}
		return tmp;
	}



	char CutDirection(Rectangle S, Rectangle I, Index CutRule, bool rotate) 

	{
		bool res;

		switch (CutRule)
		{
			case 0:
			res = S.w - I.w >= S.h - I.h;
			break;

			case 1:
			res = S.w - I.w < S.h - I.h;
			break;

			case 2:
			res = I.h * (S.w - I.w) < I.w * (S.h - I.h);
			break;

		default:
			break;
		}
		if (res) return 'h';
		else return 'v';
	}
private:
	bool rotate = 1;

};