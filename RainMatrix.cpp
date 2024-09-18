#include "RainMatrix.h"
#include <stdlib.h>

RainMatrix::RainMatrix(int columns, int rows)
{
	_columns = columns;
	_rows = rows;

	_charsMatrix = new wchar_t[_columns * _rows];
	_maskMatrix = new wchar_t[_columns * _rows];

	for (int i = 0; i < _columns * _rows; i++) {
		int letter = rand() % 33;
		_charsMatrix[i] = ALPHABET[letter];
		_maskMatrix[i] = 0;
	}

	_rains = new RainColumnCords[_columns];
}

RainMatrix::~RainMatrix()
{
	delete[] _charsMatrix;
	delete[] _maskMatrix;
	delete[] _rains;
}

int RainMatrix::getMatrixSize()
{
	return _columns * _rows;
}

int RainMatrix::getStringOutputSize()
{
	return (_columns + 1) * _rows;
}

void RainMatrix::fillMatrix(wchar_t* out, int size)
{
	if (size != this->getStringOutputSize())
		throw "Size of out must be equal to matrix size";
	
	// mapping x y to x + 1 y output
	for (int i = 0, j = 0; i < size; ++i) {
		if (i % (_columns + 1) == _columns) {
			out[i] = '\n';
			continue;
		}

		if (_maskMatrix[j] == 0) {
			//out[i] = _charsMatrix[j];
			out[i] = ' ';
		}
		else {
			//out[i] = ' ';
			out[i] = _charsMatrix[j];
		}
		j++;
	}

	out[size - 1] = '\0';
}

void RainMatrix::nextFrame()
{
	getRandomRainColumn();
	updateRainColumns();
}

void RainMatrix::getRandomRainColumn()
{
	int column = rand() % _columns;
	if (_rains[column].length != 0) {
		return;
	}

	int length = rand() % _rows;
	//int length = 1;

	_rains[column].row = -length;
	_rains[column].length = length;
}

void RainMatrix::updateRainColumns()
{
	for (int i = 0; i < _columns; i++) {
		if (_rains[i].length == 0) {
			continue;
		}

		int begin = _rains[i].row;
		if (begin >= 0)
			_maskMatrix[begin * _columns + i] = 0;

		_rains[i].row++;

		int newEnd = _rains[i].row + _rains[i].length - 1;
		if (newEnd < _rows)
			_maskMatrix[newEnd * _columns + i] = 1;

		if (_rains[i].row >= _rows) 
		{
			_rains[i].row = 0;
			_rains[i].length = 0;
		}
	}
}