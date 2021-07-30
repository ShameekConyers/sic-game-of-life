#include "Grid.hpp"
#include <cassert>
#include <random>
#include <iostream>

inline const int GRID_BOUND_CODE = -10;
inline const int GRID_NULL_CODE = -11;

Grid::Grid()
	: m_data{},
	m_rows{ -1 },
	m_cols{ -1 }
{

}

void Grid::initialize(int rows, int cols, int num, int seed)
{
	m_rows = rows;
	m_cols = cols;

	//


	m_data.reserve(rows * cols);
	for (int i = 0; i < rows * cols; i++) {
		m_data.push_back(0);
	}
	assert(m_data.size() == rows * cols);

	//top
	for (int j = 0; j < cols; j++) {
		set(0, j, GRID_BOUND_CODE);
	}

	//left
	for (int i = 0; i < rows; i++) {
		set(i, 0, GRID_BOUND_CODE);

	}
	//right
	for (int i = 0; i < rows; i++) {
		set(i, cols - 1, GRID_BOUND_CODE);

	}
	//bottom
	for (int j = 0; j < cols; j++) {
		set(rows - 1, j, GRID_BOUND_CODE);
	}

	//rand
	// std::mt19937 engine(seed);
	std::random_device engine;
	std::uniform_int_distribution<int> row_distr(10, rows - 10);
	std::uniform_int_distribution<int> col_distr(10, cols - 10);
	for (int i = 0; i < num; i++) {
		set(
			row_distr(engine),
			col_distr(engine),
			1
		);
	}
}

std::pair<int, int> Grid::dim()
{
	return { m_rows, m_cols };
}

int Grid::get(int i, int j)
{
	assert(i < m_rows&& i < m_cols);

	return m_data[(i * m_cols) + j];

}

void Grid::set(int i, int j, int val)
{
	assert(i < m_rows&& i < m_cols);
	m_data[(i * m_cols) + j] = val;
	assert(m_data[(i * m_cols) + j] == val);

}

std::vector<int> Grid::getNeighbors(int i, int j)
{
	/*
		XXX
		XTX
		XXX <- end
	*/

	std::vector<int> result;

	for (int k = -1; k <= 1; k++) {
		for (int l = -1; l <= 1; l++) {
			int x = i + k;
			int y = j + l;
			if (x < 0 || x >= m_rows || y < 0 || y >= m_cols) {
				result.push_back(GRID_NULL_CODE);
			}
			else {
				result.push_back(get(x, y));
			}
		}
	}
	return result;
}

void Grid::update()
{
	std::vector<int> new_data(m_data.size());
	auto new_set = [&new_data, this](int i, int j, int val)
	{
		new_data[(i * m_cols) + j] = val;
	};

	//rand
	//std::mt19937 engine(seed);
	std::random_device engine;
	std::uniform_int_distribution<int> row_distr(1, m_rows - 2);
	std::uniform_int_distribution<int> col_distr(1, m_cols - 2);
	for (int i = 0; i < 200; i++) {
		set(
			row_distr(engine),
			col_distr(engine),
			1
		);
	}
	for (int i = 0; i < 200; i++) {
		set(
			row_distr(engine),
			col_distr(engine),
			0
		);
	}

	for (int i = 0; i < m_rows; i++) {
		for (int j = 0; j < m_cols; j++) {
			std::vector<int> mini_grid = getNeighbors(i, j);
			int center = mini_grid[4];
			if (center == GRID_BOUND_CODE) {
				new_set(i, j, GRID_BOUND_CODE);
			}

			int alive = 0;
			int count = 0;
			for (auto neighbor : mini_grid) {
				if (neighbor == 1) {
					alive++;
				}
			}
			if (center == 0) {
				if (alive == 3) {
					new_set(i, j, 1);
				}
				else {
					new_set(i, j, 0);
				}
			}
			else if (center == 1) {
				if (alive == 3 || alive == 4) {
					new_set(i, j, 1);
				}
				else {
					new_set(i, j, 0);
				}

			}

		}
	}


	m_data = new_data;
}
