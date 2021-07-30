#pragma once

#include <vector>
#include <utility>

inline const int CELL_NUM = 1600;

class Grid {
public:
	Grid();

	void initialize(int rows, int cols, int num = CELL_NUM, int seed = 2);
	std::pair<int, int> dim();
	int get(int i, int j);
	void set(int i, int j, int val);

	std::vector<int> getNeighbors(int i, int j);

	void update();

private:
	std::vector<int> m_data;
	int m_rows;
	int m_cols;
};
