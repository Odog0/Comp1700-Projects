#include <iostream>
#include <array>
#include <cctype>
using namespace std;

const int COLS = 7;
const int ROWS = 6;

using Row = array<char, COLS>;
using Board = array<Row, ROWS>;


void printBoard(const Board& board);

void fillBoard(Board& board, char c);

bool dropPiece(Board& board, int col, char piece);

bool emptySpotsRemain(const Board& board);

bool getMove(char turn, int& col);

char horizontalWin(Board& board, int row, int col);

char verticalWin(Board& board, int row, int col);

char downDiagonalWin(Board& board, int row, int col);

char upDiagonalWin(Board& board, int row, int col);

char winner(Board& board);


int main() {
	Board board;
	fillBoard(board, ' ');

	char turn = 'X', w = ' ';
	int col;

	printBoard(board);

	while (w == ' ' && emptySpotsRemain(board) && getMove(turn, col)) {
		if (!dropPiece(board, col, turn)) continue;
		printBoard(board);
		turn = (turn == 'X' ? 'O' : 'X');

		w = winner(board);
	}
	printBoard(board);

	if (w == ' ')
		cout << "Tie game\n";
	else
		cout << w << " wins!\n";
}


void printBoard(const Board& board) {
	cout << "\n A B C D E F G\n";

	for (int i = 0; i < board.size(); ++i) {
		cout << '|';

		for (int j = 0; j < board[i].size(); ++j) {
			cout << board[i][j] << '|';
		}

		cout << '\n';
	}

	cout << "+-+-+-+-+-+-+-+\n\n";
}

void fillBoard(Board& board, char c) {
	for (int i = 0; i < board.size(); ++i) {
		for (int j = 0; j < board[i].size(); ++j) {
			board[i][j] = c;
		}
	}
}

bool dropPiece(Board& board, int col, char piece) {
	for (int i = board.size() - 1; i >= 0; --i) {
		if (board[i][col] == ' ') {
			board[i][col] = piece;
			return true;
		}
	}
	return false;
}

bool emptySpotsRemain(const Board& board) {
	for (int i = 0; i < board.size(); ++i) {
		for (int j = 0; j < board[i].size(); ++j) {
			if (board[i][j] == ' ')
				return true;
		}
	}

	return false;
}

bool getMove(char turn, int& col) {
	cout << turn << ": ";
	char move;
	do {
		cin >> move;
		move = toupper(move);
	} while (cin && (move < 'A' || move > 'G') && move != 'Q');

	if (!cin || move == 'Q') {
		return false;
	}
	else {
		col = move - 'A';
		return true;
	}
}

char horizontalWin(Board& board, int row, int col) {
	char piece = board[row][col];

	if (piece == ' ' || col + 3 >= COLS) return ' ';

	if (board[row][col + 1] == piece && board[row][col + 2] == piece && board[row][col + 3] == piece) {
		for (int i = 1; i < 4; ++i)
			board[row][col + i] = '*';
		return piece;
	}
	return ' ';
}

char verticalWin(Board& board, int row, int col) {
	char piece = board[row][col];

	if (piece == ' ' || row + 3 >= ROWS) return ' ';
	if (board[row + 1][col] == piece && board[row + 2][col] == piece && board[row + 3][col] == piece) {
		for (int i = 1; i < 4; ++i)
			board[row + i][col] = '*';
		return piece;
	}

	return ' ';
}

char downDiagonalWin(Board& board, int row, int col) {
	char piece = board[row][col];

	if (piece == ' ' || row + 3 >= ROWS || col + 3 >= COLS) return ' ';
	if (board[row + 1][col + 1] == piece && board[row + 2][col + 2] == piece && board[row + 3][col + 3] == piece) {
		for (int i = 1; i < 4; ++i)
			board[row + i][col + i] = '*';
		return piece;
	}

	return ' ';
}

char upDiagonalWin(Board& board, int row, int col) {
	char piece = board[row][col];

	if (piece == ' ' || row - 3 < 0 || col + 3 >= COLS) return ' ';
	if (board[row - 1][col + 1] == piece && board[row - 2][col + 2] == piece && board[row - 3][col + 3] == piece) {
		for (int i = 1; i < 4; ++i)
			board[row - i][col + i] = '*';
		return piece;
	}

	return ' ';
}

char winner(Board& board) {
	char w;
	for (int i = 0; i < board.size(); ++i) {
		for (int j = 0; j < board[i].size(); ++j) {
			if (horizontalWin(board, i, j) != ' ' ||
				verticalWin(board, i, j) != ' ' ||
				downDiagonalWin(board, i, j) != ' ' ||
				upDiagonalWin(board, i, j) != ' ') {
				w = board[i][j];
				board[i][j] = '*';
				return w;
			}
				
		}
	}

	return ' ';
}