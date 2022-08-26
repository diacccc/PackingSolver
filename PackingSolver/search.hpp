#pragma once
#include "instance.hpp"
#include "solution.hpp"
#include "heuristic.hpp"
#include <queue>

void DFS(SolutionNode sol, SolutionNode& best_sol, CPU& start)
{
	if (sol.is_complete()) {
		if (best_sol.used_bin_number() > sol.used_bin_number() || best_sol.used_bin_number() == 0)
			best_sol = sol;
		return;
	}

	if (sol.Lower_Bound_1() + sol.used_bin_number() >= best_sol.used_bin_number() && best_sol.used_bin_number() != 0)
		return;
	//cout << sol.used_bin_number() << sol.Bin() << endl;


	start.branch++;
	
	if (clock() - start.t > TimeLimit) return;
	if (best_sol.used_bin_number() != 0 && sol.used_bin_number() > best_sol.used_bin_number())
		return;


	SolutionNode tmp(sol);
	for (Index i = 0; i < 3; ++i)
		for (Index j = 0; j < 3; ++j)
		{
			tmp = sol;
			tmp.GenerateChild(i, j);
			DFS(tmp, best_sol, start);
			//sol.GenerateChild(i, j);
			//DFS(sol, best_sol, start);
		}
}

void A_Star(SolutionNode sol, SolutionNode& best_sol, CPU& start)
{
	priority_queue<SolutionNode> Q;
	Q.push(sol);
	while (!Q.empty())
	{
		SolutionNode Cur = Q.top();
		Q.pop();
		SolutionNode tmp(Cur);
		for (Index i = 0; i < 3; ++i)
			for (Index j = 0; j < 3; ++j)
			{
				start.branch++;
				tmp = Cur;
				tmp.GenerateChild(i, j);
				//cerr << tmp.used_bin_number() << endl;
				//if(tmp.Lower_Bound_1() + tmp.used_bin_number() >= 9)
				if (tmp.Lower_Bound_1() + tmp.used_bin_number() >= best_sol.used_bin_number() && best_sol.used_bin_number() != 0)
					continue;


				Q.push(tmp);
				if (tmp.is_complete()) {
					if (best_sol.used_bin_number() > tmp.used_bin_number() || best_sol.used_bin_number() == 0)
						best_sol = tmp;
				}
			}
		while (Q.size() > D) Q.pop();
		if (clock() - start.t > TimeLimit) return;
	}
}