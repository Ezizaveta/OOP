#pragma once

struct Point final {
	int x, y;

public:
	int X() { return x; };
	int Y() { return y; };
};


class Board final {
private:
	int cols, rows;
	int* board;

public:
	Board() : cols(0), rows(0), board(nullptr) {};
	Board(int cols_, int rows_) : cols(cols_), rows(rows_), board(new int[cols * rows]) {};
	~Board()
	{
			delete[] board;
	};
	int Cols() { return cols; };
	int Rows() { return rows; };
};