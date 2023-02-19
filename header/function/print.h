#pragma once

#include <iostream>
#include <vector>

void constvPrint();
void frameTimePrint();
template<typename TN>
void matrixPrint(int, int, const TN* const);
void print();
void staticvPrint();
template<typename TN>
void vectorPrint(int, const TN* const);
template<typename TN>
void vectorPrint_index(const std::vector<int>&, const std::vector<TN>&);



template<typename TN>
void matrixPrint(int M, int N, const TN* const mat)
{
	for (int i = 0;i < M;i++) { vectorPrint(N, &mat[i * N]); }
	std::cout << std::endl;
}
template<typename TN>
void vectorPrint(int dimension, const TN* const vec)
{
	for (int i = 0;i < dimension;i++) { std::cout << vec[i] << "  "; }
	std::cout << std::endl;
}
template<typename TN>
void vectorPrint_index(const std::vector<int>& vecI, const std::vector<TN>& vec)
{
	int size = vecI.size();
	for (int i = 0;i < size;i++) { vectorPrint(2, vec[vecI[i]].get()); }
}
