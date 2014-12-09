#include <iostream>
#include <algorithm>
#include <ctime>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

const unsigned SIZE=9;

typedef unsigned char sudoku[SIZE][SIZE];

bool check(sudoku matrix,unsigned x,unsigned y){
	unsigned char val=matrix[x][y];
	for (unsigned a=0;a<x;a++)
		if (matrix[a][y]==val)
			return 0;
	for (unsigned a=x+1;a<SIZE;a++)
		if (matrix[a][y]==val)
			return 0;
	for (unsigned a=0;a<y;a++)
		if (matrix[x][a]==val)
			return 0;
	for (unsigned a=y+1;a<SIZE;a++)
		if (matrix[x][a]==val)
			return 0;
	unsigned startx=x/(SIZE/3)*3,
		starty=y/(SIZE/3)*3,
		endx=startx+SIZE/3,
		endy=starty+SIZE/3;
	for (unsigned a=startx;a<endx;a++){
		for (unsigned b=starty;b<endy;b++){
			if (a!=x && b!=y && matrix[a][b]==val)
				return 0;
		}
	}
	return 1;
}

void printMatrix(sudoku matrix){
	for (unsigned b=0;b<SIZE;b++){
		for (unsigned a=0;a<SIZE;a++){
			if (matrix[a][b])
				std::cout <<(int)matrix[a][b];
			else
				std::cout <<'_';
			if (a && a%(SIZE/3)==SIZE/3-1)
				std::cout <<' ';
		}
		std::cout <<std::endl;
		if (b && b%(SIZE/3)==SIZE/3-1)
			std::cout <<std::endl;
	}
}

void transpose(sudoku matrix){
	for (unsigned y=0;y<SIZE-1;y++){
		for (unsigned x=y+1;x<SIZE;x++){
			std::swap(matrix[x][y],matrix[y][x]);
		}
	}
}

unsigned solution_time=0;

bool solve(sudoku matrix,unsigned pos=0){
	unsigned x=pos%SIZE,
		y=pos/SIZE;
	if (y>=SIZE)
		return 1;
	if (matrix[x][y])
		return solve(matrix,pos+1);
	for (unsigned a=1;a<=SIZE;a++){
		solution_time++;
		matrix[x][y]=a;
		if (check(matrix,x,y) && solve(matrix,pos+1))
			return 1;
	}
	matrix[x][y]=0;
	return 0;
}

int main(){
	string filename;
	string readin;
	double _readin;
	vector<double> File;
	cout << "What is the name of the file? ";
	cin >> filename;

	ifstream infile(filename);
	if (infile.fail()) {
		cout << "couldn't open " << filename << ". Aborting\n";
		return 0;
	}
	while (!infile.eof()) {
		getline(infile, readin, ' ');
		_readin = stod(readin);
		File.push_back(_readin);
	}
	sudoku matrix=
	{
		File[0],File[1],File[2],File[3],File[4],File[5],File[6],File[7],File[8],File[9],
		File[10],File[11],File[12],File[13],File[14],File[15],File[16],File[17],File[18],File[19],
		File[20],File[21],File[22],File[23],File[24],File[25],File[26],File[27],File[28],File[29],
		File[30],File[31],File[32],File[33],File[34],File[35],File[36],File[37],File[38],File[39],
		File[40],File[41],File[42],File[43],File[44],File[45],File[46],File[47],File[48],File[49],
		File[50],File[51],File[52],File[53],File[54],File[55],File[56],File[57],File[58],File[59],
		File[60],File[61],File[62],File[63],File[64],File[65],File[66],File[67],File[68],File[69],
		File[70],File[71],File[72],File[73],File[74],File[75],File[76],File[77],File[78],File[79],
		File[80],
		


	};
	clock_t t0,t1;
	t0=clock();
	transpose(matrix);
	if (!solve(matrix))
		std::cout <<"Unsolvable!"<<std::endl;
	else
		printMatrix(matrix);
	t1=clock();
	std::cout <<"Solved in "<<solution_time<<" iterations."<<std::endl;
	std::cout <<double(t1-t0)/(double(CLOCKS_PER_SEC)/1000.0)<<" ms"<<std::endl;
	return 0;
}