# C-Matrix-Solver
Solves classic A.x = b with given A and b  
This program gives the result of A*x=B matrix equation.Assuming A is invertible(non-singular) and square  

1. Search cmd.exe (It should be in C:\Windows\System32)  
2. copy cmd.exe to same location with cpp file  
3. open cmd.exe  
4. drag and drop cpp file on cmd.exe  
5. Press enter(devC++ should be open)  
6. press F9 to compile file  
7. Now you need 2 txt files(one for A matrix and one for b matrix) to safely run the program  
8. drag and drop compiled exe file on cmd.exe  
9. Type " filename_of_A.txt filename_of_b.txt" on the command line  
	if filename_of_A.txt is A and filename_of_b.txt is b  
	your command should like this     
...Directory of cpp file..>"...Directory of cpp file\MehmetAlpSarkisla_project.exe" A.txt b.txt  
10. Press enter and run the program  
11. If everything done correctly you should see   
argv[1] = A.txt  
argv[2] = b.txt  
A.txt is open.          
b.txt is open.  
3.14 1.59 2.65 3.58    
9.79 3.23 8.46 2.64                                     <-----A matrix  
3.38 3.27 9.5 2.88    
4.19 7.16 9.39 9.37     
                               
0.793276  
-1.68867  
-0.060839                                              <------x matrix(solution)  
1.52383  
                               
* You can also see the x matrix in solution.txt  
* This program also find contional numbers at 1 and infinity for 2x2 matrices  
example:  
A:  
1.000 1.000  
1.000 1.001  
b1:		b2:  
2.000		2.000  
2.000		2.001  
x1:             x2:  
2.000		1.000  
0.000		1.000  

condition num at 1:4002  
condition num at inf:4002  
  
Large cond(A) means A is nearly singular  
It express how sensitive that function is to small changes.  
As you can see in example;for large condition number, 0.001 change results with drastic errors.  
