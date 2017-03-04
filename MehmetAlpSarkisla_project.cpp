#include <fstream>
#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <math.h>
using namespace std;
void swaprows(double **TempMat,int colsize,int rowsize,int row1,int row2);

//Function that checks the files are entered correctly
int chkfile(int argc,char* argv[]){ 
	if(argc=3){
		cout << "argv[1] = " << argv[1] << endl;
		cout << "argv[2] = " << argv[2] << endl;
		//You should see :
		// argv[1]= A.txt
		// argv[2]= b.txt
		//if you did everything correctly
		return 0;
	}
	else{
		cout << "No file name entered.Exiting.";
		return 1;
	}
}
//Create vector
double *vector(string filename,int &rowsize,int &colsize){
	ifstream file(filename.c_str()); //input file stream to open the filename
	// Check the file is opened properly
	if (colsize !=0){
		if(file.is_open() && file.good())  { cout << filename << " is open.\n" ;}
		else{ cout << filename << " is failed to open.\n" ; 
			return NULL;
		}
	}
	// Then turn it to a vector
	string line;
	int idx =-1;
	double *vector = new double [1];//creates array
	double element;
	while (getline(file,line)){
		stringstream stream(line);
		rowsize++;
		colsize=0;
		while(1){
			stream >> element;
			if(!stream){break;}
			colsize++;
			idx++;
			//Dynamic allocation
			double *tempArr = new double[idx+1];
			copy(vector,vector+idx,tempArr);
			tempArr[idx]= element;
			delete[] vector;
			vector = tempArr;

		}
	}
	return vector;
}
//Swaping given two rows of a matrix
void swaprow(double **TempMat,int colsize,int rowsize,int row1,int row2){
	double temp;
	for (int k=0;k<colsize;k++){
			temp = TempMat [row1][k];
			TempMat [row1][k]=TempMat [row2][k];
			TempMat [row2][k]=temp;
	}
}
//Gaussian elimination with partial pivoting
void partpivot(double **matrix_A,double **matrix_B,int colsize,int rowsize,int x){
		double **TempMat=new double *[rowsize];//create dummy matrix_A
		//Define dummy matrix TempMat	
		for (int i=0;i<rowsize;i++){
			TempMat[i]= new double [colsize];
			for(int j=0;j<colsize;j++){
				TempMat[i][j]= matrix_A[i][j];
			}
		}
		//First find the row that has a highest abs value in the column x.And swap it.
		for(int i=x;i<rowsize;i++){			
			abs(TempMat[i][x]);//Take the abs value
			if (TempMat[i][x]>TempMat[x][x]){
			swaprow(matrix_A,colsize,rowsize,i,x);
			swaprow(matrix_B,1,rowsize,i,x);
			swaprow(TempMat,colsize,rowsize,i,x);
			}
		}
		//Divide the row x to its first term					
		matrix_B[x][0] /= matrix_A[x][x];
		for(int i=colsize-1;i>=x;i--){
			matrix_A[x][i]/= matrix_A[x][x];
		}
		//Then eliminate the other rows.
		for(int i=x+1;i<rowsize;i++){
			double k= matrix_A[i][x];
			matrix_B[i][0] -= k*matrix_B[x][0];
			for(int j=0;j<colsize;j++){		
				matrix_A[i][j] -= k*matrix_A[x][j];
			}
		}
}
//recursive function that solves the A*x=b equation and returns the value of x[n];
double findx(int n,double **matrix_A,double **matrix_B,int rowsize){
	double A =  matrix_B[n][0];
	if(n==rowsize-1){//recursive contidion
		double k=matrix_B[n][0]/matrix_A[n][n];
		return k;
	}
	else{//general term
		for(int i=n+1;i<rowsize;i++){
				 A -= findx(i,matrix_A,matrix_B,rowsize) * matrix_A [n][i]; 
		}
		return  A/matrix_A[n][n];
	}
}
//Condition number for 2x2 matrices
void condnum(double **matrix){
	double invmatrix[2][2];
	double sum1=0,sum2=0,tpsum1=0,tpsum2=0;
	double k=0;
	//Find determinant
	k= ((matrix [1][1]*matrix [0][0])-(matrix [0][1]*matrix [1][0]));
	k=1.0/k;
	//Find inverse
	invmatrix [0][0]=k*matrix [1][1];
	invmatrix [0][1]=-k*matrix [0][1];
	invmatrix [1][0]=-k*matrix [1][0];
	invmatrix [1][1]=k*matrix [0][0];
	//||A||1
	for(int i=0;i<2;i++){
		sum1=0;
		sum2=0;
		for(int j=0;j<2;j++){
			sum1 += abs(matrix [i][j]);
			sum2 += abs(invmatrix [i][j]);
		}
		if(sum1>tpsum1){tpsum1=	sum1;}
		if(sum2>tpsum2){tpsum2=	sum2;}
	}
	double tpsum3=0,tpsum4=0;
	//||A||inf
	for(int j=0;j<2;j++){
		sum1=0;
		sum2=0;
		for(int i=0;i<2;i++){
			sum1 += abs(matrix [i][j]);
			sum2 += abs(invmatrix [i][j]);
		}
		if(sum1>tpsum3){tpsum3=	sum1;}
		if(sum2>tpsum4){tpsum4=	sum2;}
	}
	double cond1 = tpsum1*tpsum2;
	double condinf=tpsum3*tpsum4;
	cout << endl << "Condition number at 1 is = " << cond1 <<endl;
	cout << endl << "Condition number at infinity is = " << condinf <<endl;
}
//MAIN FUNCTION
int main (int argc,char* argv[]){
	if 	(chkfile(argc,argv)){return -1 ;} //Checks the files entered correctly(Exits if they are not)
	int tempc,tempr=0;//temporary column and row variables
	if(vector(argv[1],tempr,tempc)==NULL){
		cout << "File couldn't open.\n";
		return -1;
	}
	tempc = 0;
	tempr = 0;
	vector(argv[1],tempr,tempc);
	//vector_A
	int rowsize = tempr;//To keep track of column and row sizes(permanent)
	int colsize = tempc;
	double *vector_A =new double [rowsize*colsize]; 
	vector_A  = vector(argv[1],tempr,tempc) ;
	//vector_b
	double *vector_b =new double [colsize] ;
	vector_b=vector(argv[2],tempr,tempc); 
	//AND TURN THE VECTORS TO THE MATRICES
	int idx=0;
	double **matrix_A=new double *[rowsize];//Creates array of pointers
	double **matrix_B=new double *[rowsize];
	for(int i=0;i<rowsize;i++){
		matrix_A[i] = new double [colsize];
		matrix_B[i] = new double [1];
		for(int j=0;j<colsize;j++){
			matrix_A[i][j]=vector_A[idx];
			cout << matrix_A [i][j] << " " ;//print A
			matrix_B [i][0] = vector_b[i];
			idx++;
		}
		cout << endl;
	}	
	//Condition number function	
	if(colsize==2){
		cout << endl;
		condnum(matrix_A);
	}
	cout << endl;
	//Gaussian elimination with partial pivoting
	for(int x=0;x<colsize;x++){
		partpivot(matrix_A,matrix_B,colsize,rowsize,x);
	}	
	//Check the singlarity of A
	if(abs(matrix_A [rowsize-1][colsize-1]) < 0.000009){
		cout << "Error,A is singular.Exiting.";
		return -1;
	}
	//solve the matrix equation and print it to the txt file
	double vector_x[colsize] ;
	ofstream solution ("solution.txt");
	for(int n=0;n<rowsize;n++){
		vector_x[n]=findx(n,matrix_A,matrix_B,rowsize);//solve the matrix equation
		cout << vector_x[n] << endl;
		solution << vector_x[n] << endl;
	}
	solution.close ();	
	return 0;
}

