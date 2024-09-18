#pragma once

struct RainColumnCords {
	int row;
	int length;

	RainColumnCords() {
		row = 0;
		length = 0;
	}
};

class RainMatrix
{
	//const wchar_t* ALPHABET = L"あいうえおかきくけこさしすせそたちつてとなにぬねのはひふへほまみむめもやゆよらりるれろわをん123456789";
	const wchar_t* ALPHABET = L"abcdefghijklmnoprstqwxyz123456789";

	int _columns;
	int _rows;

	wchar_t* _charsMatrix;
	wchar_t* _maskMatrix;
	RainColumnCords* _rains;

public:
	RainMatrix(int columns, int rows);
	~RainMatrix();

	int getMatrixSize();

	int getStringOutputSize();

	void fillMatrix(wchar_t* out, int size);
	void nextFrame();
private: 
	void getRandomRainColumn();
	void updateRainColumns();

};

/* ALGORITHM DESCRIPTION
1. Create a matrix of characters with the size of columns * rows
2. Create a matrix of masks with the size of columns * rows
	
	characters:
	*----*
	|abcd|
	|1234|
	|efgh|
	*----*
	
	masks:
	*----*
	|0000|
	|0000|
	|0000|
	*----*
 
3. Create a matrix of rain columns with the size of columns
	- Each rain droplet is defined by starting row and length of the.
	- Every time a droplet is created it starts beyond top row of the mask matrix.
	- In each frame droplet moves one row lower.
	- Example for droplet size of 2:
	
	  1
	*-1--*	*-1--* *----*
	|0000|  |0100| |0100|
	|0000|  |0000| |0100|
	|0000|  |0000| |0000|
	*----*  *----* *----*
	 
4. 	
*/