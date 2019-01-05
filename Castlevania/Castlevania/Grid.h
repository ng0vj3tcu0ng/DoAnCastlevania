#pragma once
#include<vector>

using namespace std;

#define SCREEN_WIDTH_HALF 180

class Grid
{
	int Width;
	vector<int> * Map;
public:
	Grid(int MapWidth);
	void AddId(float x, int id);
	void Remove(int id);
	vector<int> GetIdInGrid(int idsimon);	
	~Grid();
};

