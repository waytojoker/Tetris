#pragma once
class point
{
public:
	int getRow();
	int getColumn();
	void setRow(int r);
	void setColumn(int c);
private:
	int row;
	int column;
};

