#include "instance.hpp"
#include "solution.hpp"
#include "heuristic.hpp"
#include "search.hpp"

using namespace std;

int main(int argc, char* argv[])
{
	//cout << "Start running" << endl;
	//Instance ins("D:\\Microsoft Visual C++ Source\\Solution\\PackingSolver\\test.ins2D");
	Instance ins(argv[1]);
	ofstream outfile;
	outfile.open("Solution.csv", std::ios::app);
	vector<Item> I = ins.items();
	for (int i = 0; i < I.size(); ++i)
		cout << I[i] << endl;

	SolutionNode best_sol(ins);
	SolutionNode sol(ins);
	CPU start;
	start.t = clock();
	//sol.GenerateChild(0, 0);
	DFS(sol, best_sol, start);
	//A_Star(sol, best_sol, start);
	cout << start.branch << endl;
	cout << best_sol.used_bin_number() << endl;

	vector<Pattern> P = best_sol.current_pattern();
	for (Index i = 0; i < P.size(); ++i)
	{
		cout << i + 1 << "th bin packs " << P[i].leaf_number << " items." << endl;
		P[i].print(P[i].root);
		cout << endl;
	}
	outfile << best_sol.used_bin_number() << endl;

	return 0;
}
