// Daily 205 Hard CPP.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

enum Type { I, D, S };

struct Node { int val; Type type; };

int main()
{
	std::string s1, s2;
	std::cin >> s1 >> s2;

	int M = s1.size() + 1, N = s2.size() + 1;

	auto tab = std::vector<std::vector<Node>>(M, std::vector<Node>(N));

	for (int i = 0; i < M; ++i)
		tab[i][0] = { i, I };
	for (int j = 0; j < N; ++j)
		tab[0][j] = { j, D };

	for (int i = 1; i < M; ++i) {
		for (int j = 1; j < N; ++j) {
			Node a = { tab[i - 1][j].val + 2, I },
				b = { tab[i][j - 1].val + 2, D },
				c = { tab[i - 1][j - 1].val + (s1[i - 1] == s2[j - 1] ? -2 : 1), S };

			auto comp = [](const Node &node1, const Node &node2) 
			{ return node1.val < node2.val; };

			tab[i][j] = std::min(c, std::min(a, b, comp), comp);
		}
	}

	std::string r1, r2, comp;

	int i = M - 1, j = N - 1;
	while (i != 0 || j != 0) {
		Node &node = tab[i][j];
		char c1 = '-', c2 = '-';
		if (node.type == S) {
			c1 = s1[--i];
			c2 = s2[--j];
		}
		else if (node.type == I)
			c1 = s1[--i];
		else if (node.type == D)
			c2 = s2[--j];

		r1.push_back(c1);
		r2.push_back(c2);
	}
	std::reverse(r1.begin(), r1.end());
	std::reverse(r2.begin(), r2.end());

	std::cout << r1 << "\n";
	std::cout << r2 << "\n";
}