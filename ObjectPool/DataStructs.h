#pragma once

class Point final {
private:
	size_t x, y;

public:
	Point() : x(0), y(0) {};
	Point(size_t x, size_t y) : x(x), y(y) {};
	~Point() = default;
	size_t X() { return x; };
	size_t Y() { return y; };
};

class Board final {
private:
	size_t cols, rows;
	double* board;

public:
	Board() : cols(0), rows(0), board(nullptr) {};
	Board(size_t cols_, size_t rows_) : cols(cols_), rows(rows_), board(new double[cols * rows]) {};
	~Board()
	{
		if (board != nullptr)
			delete[] board;
	};
	size_t Cols() { return cols; };
	size_t Rows() { return rows; };
};