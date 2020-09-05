/*
Implementation of Cryptarithmetic problem by Sava Dimitrov,
											FMI, F.N. 71737
Solving the popular cryptarithmetic problem which this time
is about multiplication of integers.
The task to solve is: 
			A B C
		Õ	D E B
		_________
			A B C
		  I A G
	  E H F A
	  ___________
	  E D B D F C

For solving the problem we will use CS(Constraint Satisfaction). 
*/

#include <iostream>

using namespace std;

class Cryptarithmetic {
public:
	///In the Brute-force algorithm B is by default = 1 
	///and we will not change the value in our program
	//Cryptarithmetic() : B(1), A(0), C(0), D(0), E(0),
	//	F(0), G(0), H(0), I(0), baseline1(0),
	//	baseline3(0), baseline4(0), baseline5(0) {} //we don't use baseline2 because
	//									//in isCorrectSolution() we use D, E, B, as 
	//									//separate variables(not as one: DEB)
		

	///In the Backtracking algorithm B will stay 0, will not have a default value
	Cryptarithmetic() : B(0), A(0), C(0), D(0), E(0),
		F(0), G(0), H(0), I(0), baseline1(0), 
		baseline3(0), baseline4(0), baseline5(0) {} //we don't use baseline2 because
										//in isCorrectSolution() we use D, E, B, as 
										//separate variables(not as one: DEB)

	//Main method for the program
	///Brute-force algorithm
	//void cryptarithmeticProblem(int &solutions) {
	//	//B is by default = 1 and will not use a for() for B
	//	for (A = 2; A <= 9; A++) { //Every possible digit for A
	//		//Skiping B
	//		for (C = 2; C <= 9; C++) { //Every possible digit for C
	//			for (D = 2; D <= 9; D++) { //Every possible digit for D
	//				for (E = 2; E <= 9; E++) { //Every possible digit for E
	//					for (F = 2; F <= 9; F++) { //Every possible digit for F
	//						for (G = 2; G <= 9; G++) { //Every possible digit for G
	//							for (H = 2; H <= 9; H++) { //Every possible digit for H
	//								for (I = 2; I <= 9; I++) { //Every possible digit for I
	//									if (allDiff())
	//									{
	//										buildBaselines();
	//										if (isCorrectSolution())
	//										{
	//											printSolution();
	//											solutions++;
	//										}
	//									} 
	//								}// end I
	//							} // end H
	//						} // end G
	//					} // end F
	//				} // end E
	//			} // end D
	//		} // end C
	//	} // end A
	//}


	///Backtracking algorithm
	void cryptarithmeticProblem(int *arr, int st, int ls, int &solutions) {
		int i = 0;
		if (st == ls)
		{
			changeVars(arr);
			if (allDiff())
			{
				buildBaselines();
				if (isCorrectSolution())
				{
					printSolution();
					solutions++;
				}
			}
		}
		else
		{
			for (i = st; i<ls; i++)
			{
				swap(arr + st, arr + i);
				cryptarithmeticProblem(arr, st + 1, ls, solutions);
				swap(arr + st, arr + i);
			}
		}
	}

private:
	//Our variables
	int A, B, C, D, E, F, G, H, I;
	
	//Baselines for the multiplication
	//line 1: A B C
	int baseline1;
	//line 2: D E B
	//int baseline2;

	//Each baseline of the accumulation
	//The first line of the accumulation is the same as the first 
	//line in the multiplication - reuseing it.
	
	//line 3: I A G 0
	int baseline3;
	//line 4: E H F A 0 0
	int baseline4;
	//The answer of the whole problem line 5: E D B D F C
	int baseline5;

	//Building each baseline 
	void buildBaselines() {
		//line 1
		baseline1 = this->C + (10 * this->B) + (100 * this->A);
		//line 2
		//baseline2 = this->B + (10 * this->E) + (100 * this->D);

		//line 3
		baseline3 = (this->G + (10 * this->A) + (100 * this->I)) * 10;
		//line 4
		baseline4 = (this->A + (10 * this->F) + (100 * this->H) + (1000 * this->E)) * 100;
		//line 5
		baseline5 = this->C + (10 * this->F) + (100 * this->D) +
			(1000 * this->B) + (10000 * this->D) + (100000 * this->E);
	}

	//Changing the variables
	void changeVars(int *arr) {
		this->A = arr[0];
		this->B = arr[1];
		this->C = arr[2];
		this->D = arr[3];
		this->E = arr[4];
		this->F = arr[5];
		this->G = arr[6];
		this->H = arr[7];
		this->I = arr[8];
	}

	//swapping digits for making all the permutations
	void swap(int *x1, int *x2)
	{
		int tmp = *x1;
		*x1 = *x2;
		*x2 = tmp;
	}

	//Checking if all variables are different
	bool allDiff() {
		if (A != C && A != D && A != E && A != F && A != G && A != H && A != I &&
			C != D && C != E && C != F && C != F && C != H && C != I &&
			D != E && D != F && D != G && D != H && D != I &&
			E != F && E != G && E != H && E != I &&
			F != G && F != H && F != I &&
			G != H && G != I &&
			H != I) {
			return true;
		}
		return false;
	}

	//Method for checking if the values satisfy the problem
	bool isCorrectSolution() {
		if (((baseline1 * B == baseline1) && (baseline1 * (E * 10) == baseline3)
			&& (baseline1 * (D * 100) == baseline4)) && (baseline1 + baseline3 + baseline4 == baseline5)) {
			return true;
		}
		return false;
	}

	//Method for printing a correct solution, if we find such
	void printSolution() {
		cout << "Output : One of the possible solution is:\n"
			<< "A = " << A << " " << "B = " << B << " " << "C = " << C << "\n"
			<< "D = " << D << " " << "E = " << E << " " << "F = " << F << "\n"
			<< "G = " << G << " " << "H = " << H << " " << "I = " << I << "\n"
			<< "Explanation:\n" << "The above values satisfy the below equation:\n"
			<< "\t\t\tA B C \n\t\t" << "X" << "\tD E B \n\t\t------------- \n"
			<< "\t\t\tA B C \n\t\t      I A G \n\t\t  E H F A \n\t\t-------------\n"
			<< "\t\t  E D B D F C \n" << endl;
	}

};

int main() {
	int solutions = 0;

	///For the Brute-force algorithm
	/*Cryptarithmetic problem;
	problem.cryptarithmeticProblem(solutions);*/
	
	///For the Backtracking algorithm
	int arr[9] = { 1,2,3,4,5,6,7,8,9 };
	Cryptarithmetic problem;
	problem.cryptarithmeticProblem(arr,0,9, solutions);
	
	if (solutions == 0)
		cout << "There were no solutions found!" << endl;
	else
		cout << "No more possible solutions." << endl;

	system("pause");
	return 0;
}