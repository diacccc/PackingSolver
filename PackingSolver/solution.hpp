#pragma once

#include "instance.hpp"
#include "heuristic.hpp"

using namespace std;

#pragma region Pattern

/*Use a binary tree to record a pattern of a bin*/

struct PatternNode {
	Rectangle	rec;
	Position	pos = 0;
	Orientation o = '*';
	PatternNode* leftchild = NULL;
	PatternNode* rightchild= NULL;
	PatternNode* parent;

	void onecut() { 
		leftchild = new PatternNode;
		rightchild = new PatternNode;
		if (o == 'h'){
			leftchild ->rec = Rectangle(rec.w, pos);
			rightchild->rec = Rectangle(rec.w, rec.h - pos);
		}
		else if(o == 'v') {
			leftchild ->rec = Rectangle(pos, rec.h);
			rightchild->rec = Rectangle(rec.w - pos, rec.h);
		}
		else {
			cerr << "Orientation is invalid" << endl;
			exit(1);
		}
	}
};

std::ostream& operator<<(std::ostream& os, PatternNode* Node);


struct Pattern {
	Count leaf_number = 0;
	PatternNode* root;

	void print(PatternNode* node)
	{
		if (node == NULL) return;
		if (node->rec.area())
		{
			cout << node->rec;
			if (node->leftchild == NULL && node->rightchild == NULL)
				cout << " is leaf node.";
			cout << endl;
		}
		print(node->leftchild);
		print(node->rightchild);
	}
};


class SolutionNode 
{
public:

	SolutionNode(const Instance& ins);
	SolutionNode(const SolutionNode& sol);

	~SolutionNode() {};

	bool is_complete() const { return unpacked_number() == 0; }

	inline Rectangle Bin() const { return Bin_; }

	inline Count unpacked_number()	const { return unpacked_number_; }
	inline Count used_bin_number()	const { return current_pattern_.size(); }

	inline Count Lower_Bound_1() const { return (unpacked_area_ - 1) / Bin_.area() + 1; }
	inline Count Guide_Function_1() const { return Lower_Bound_1() + used_bin_number(); }

	inline const vector<Item>& unpacked_items()	const { return unpacked_items_; }
	inline const vector<Pattern>& current_pattern() const { return current_pattern_; }

	inline Area unpacked_area() const { return unpacked_area_; }

	void GenerateChild(Index SelectionRule, Index CutRule);

private:
	vector<Item> unpacked_items_;
	Area unpacked_area_;

	vector<Pattern> current_pattern_;

	Rectangle Bin_;

	Count unpacked_number_;

	void compute_unpacked();
};

bool operator<(const SolutionNode& a, const SolutionNode& b);

#pragma endregion