#include "solution.hpp"
#include "instance.hpp"
#include "heuristic.hpp"

#include <climits>

std::ostream& operator<<(std::ostream& os, PatternNode* Node)
{
	if (Node->o == 'h')
		os
		<< Node->rec << " is cut at "
		<< "y="
		<< Node->pos;
	else 
		os
		<< Node->rec << " is cut at "
		<< "x="
		<< Node->pos;
	return os;
}



SolutionNode::SolutionNode(const Instance& ins)
{
	unpacked_items_ = ins.items();
	Bin_ = ins.Bin();

	compute_unpacked();
}

SolutionNode::SolutionNode(const SolutionNode& sol)
{
	unpacked_items_ = sol.unpacked_items();
	current_pattern_ = sol.current_pattern();
	Bin_ = sol.Bin();

	compute_unpacked();
}




void SolutionNode::GenerateChild(Index SelectionRule, Index CutRule)
{
	Pattern P;
	P.root = new PatternNode; P.root->rec = Bin_;
	vector<PatternNode*> S; S.push_back(P.root);
	vector<bool> vis; vis.push_back(0);
	PatternNode* ChoosenNode;
	Index ChoosenItemID = 0;
	Index ChoosenNodeID = 0;
	Count cnt = 0;
	pair<Value, bool> res;
	Heuristic heur;

	//cerr << endl << "start packing....." << endl;

	//cerr << unpacked_items_.size() << endl;

	

	while (1)
	{
		res.first = INF;
		for (Index i = 0; i < unpacked_items_.size(); ++i)
		{
			if (!unpacked_items_[i].num) continue;
			for (Index j = 0; j < S.size(); ++j)
			{
				if (vis[j]) continue;
				//cerr << S[j]->rec << endl;
				if (S[j]->rec.AbleInsert(unpacked_items_[i].rec))
				{
					pair<Value, bool> tmp = heur.SelectPair(S[j]->rec, unpacked_items_[i].rec, SelectionRule);
					if (tmp.first < res.first) { res = tmp, ChoosenItemID = i, ChoosenNodeID = j, ChoosenNode = S[j]; }
				}
			}
		}
		//cerr << Bin().h << " " << Bin().w << endl;
		//cerr << unpacked_number_ << endl;
		//cout << ChoosenNode << " " << S[0] << endl;
		//cerr << unpacked_items_[ChoosenItemID].rec << " " << ChoosenNode->rec << endl;
		//cerr << res.second << endl;
		//if (cnt == 2) for (int i = 0; i < S.size(); ++i) cerr << vis[i] << endl;
		if (res.first == INF) break;
		//if (ChoosenItemID > unpacked_items_.size()) { cerr << ChoosenItemID << endl; break; }
		
		vis[ChoosenNodeID] = 1;
		cnt++;
		bool rotate = res.second;
		
		unpacked_items_[ChoosenItemID].num--;
		ChoosenNode->o = heur.CutDirection(ChoosenNode->rec, unpacked_items_[ChoosenItemID].rec, CutRule, rotate);

		if (ChoosenNode->o == 'h') {
			ChoosenNode->pos = unpacked_items_[ChoosenItemID].height(rotate);
			ChoosenNode->onecut();
			ChoosenNode->leftchild->o = 'v';
			ChoosenNode->leftchild->pos = unpacked_items_[ChoosenItemID].width(rotate);
			ChoosenNode->leftchild->onecut();
		}
		else if (ChoosenNode->o == 'v') {
			ChoosenNode->pos = unpacked_items_[ChoosenItemID].width(rotate);
			ChoosenNode->onecut();
			ChoosenNode->leftchild->o = 'h';
			ChoosenNode->leftchild->pos = unpacked_items_[ChoosenItemID].height(rotate);
			ChoosenNode->leftchild->onecut();
		}	

		S.push_back(ChoosenNode->leftchild->leftchild);  vis.push_back(1);
		S.push_back(ChoosenNode->leftchild->rightchild);  vis.push_back(0);
		S.push_back(ChoosenNode->rightchild); vis.push_back(0);

	}
	P.leaf_number = cnt;
	current_pattern_.push_back(P);
	compute_unpacked();
}

void SolutionNode::compute_unpacked()
{
	unpacked_number_ = 0, unpacked_area_ = 0;
	for (Index i = 0; i < unpacked_items_.size(); ++i)
		unpacked_number_ += unpacked_items_[i].num, unpacked_area_ += unpacked_items_[i].rec.area() * unpacked_items_[i].num;
}


bool operator<(const SolutionNode& a, const SolutionNode& b)
{
	return a.Guide_Function_1() > b.Guide_Function_1();
}
