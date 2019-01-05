#include "Grid.h"

Grid::Grid(int MapWidth)
{

	Width = MapWidth / SCREEN_WIDTH_HALF;
	
	Map = new vector<int>[Width+1];

}

void Grid::AddId(float x, int IdObjects)
{

	int Id = x / SCREEN_WIDTH_HALF;
	if (Id < Width)
	Map[Id].push_back(IdObjects);
}

void Grid::Remove(int id)
{
	if (Width > id) 
	{
		Map[id].erase(Map[id].begin() + id);
	}
}

vector<int> Grid::GetIdInGrid(int idsimon)
{
	vector<int> temp;

	if (idsimon < Width && idsimon >= 0)
	{
		
		temp = Map[idsimon];

		if (idsimon + 1 <= Width)
		{
			for (int i = 0; i < Map[idsimon + 1].size(); i++)
			{
				temp.push_back(Map[idsimon + 1][i]);
			}
		}
		if (idsimon -1>=0)
		{
			for (int i = 0; i < Map[idsimon - 1].size(); i++)
			{
				temp.push_back(Map[idsimon - 1][i]);
			}

		}

	}

		return temp;
}
