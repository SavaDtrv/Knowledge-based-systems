#include <iostream>
#include <fstream>

using namespace std;

int const MAX_SIZE = 79;

///function for calculating the average of the given data
double calculateMean(double data[]) {
	double sum = 0.0;
	for (int i = 0; i < MAX_SIZE; i++) {
		sum += data[i];
	}

	return sum / MAX_SIZE;
}

///function for calculating the standart deviation
double calculateSD(double data[])
{
	double mean, standardDeviation = 0.0;
	mean = calculateMean(data);

	for (int i = 0; i < MAX_SIZE; ++i)
		standardDeviation += pow(data[i] - mean, 2);

	return sqrt(standardDeviation / MAX_SIZE);
}

int main()
{
	///Arrays for the data in the file
	double age[MAX_SIZE];
	double weight[MAX_SIZE];
	double height[MAX_SIZE];
	
	///helping variables for reading from the file
	double num = 0;
	char symbol;
	int k = 0;

	///actual reading from the file
	ifstream fi("Trainingdataset.txt", ios::in);
	if (fi.is_open()) {
		while (!fi.eof()) {
			fi >> num;
			age[k] = num;
			fi >> symbol;
			fi >> num;
			weight[k] = num;
			fi >> symbol;
			fi >> num;
			height[k] = num;
			k++;
		}
	}
	fi.close();

	///calculating the age mean and standart deviation
	double ageMean = calculateMean(age);
	double ageSD = calculateSD(age);
	///calculating the weight mean and standart deviation
	double weightMean = calculateMean(weight);
	double weightSD = calculateSD(weight);
	///calculating the height mean and standart deviation
	double heightMean = calculateMean(height);
	double heightSD = calculateSD(height);

	///normalizing the data
	for (int i = 0; i < MAX_SIZE; ++i)
	{
		age[i] = (age[i] - ageMean) / ageSD;
		weight[i] = (weight[i] - weightMean) / weightSD;
		height[i] = (height[i] - heightMean) / heightSD;
	}

	///The linear regression using gradient descent
	///regresion coefficients
	double b0 = 0;
	double b1 = 0;
	double b2 = 0;
	///alpha
	double alpha = 0.01;
	///cicle for finding the lowest error 
	///from the regresion coefficients. 
	///The higher i is we should get more acurate model
	for (int i = 0; i < 500; ++i)
	{
		for (int j = 0; j < MAX_SIZE; ++j)
		{
			double p = b0 + b1*age[j] + b2*weight[j];
			///calculating the error
			double err = p - height[j];
			b0 = b0 - alpha*err;
			b1 = b1 - alpha*err*age[j];
			b2 = b2 - alpha*err*weight[j];
		}
	}

	///getting new data for age and weight
	cout << "Input new age and weght for predicting the height: " << endl;
	double newAgeData, newWeightData;
	cin >> newAgeData >> newWeightData;
	system("cls");
	cout << "Input new age and weght for predicting the height: " << endl;
	cout << newAgeData << ' ' << newWeightData << '\n';

	///normalizing the new age and weight
	newAgeData = (newAgeData - ageMean) / ageSD;
	newWeightData = (newWeightData - weightMean) / weightSD;

	///predicting the height
	cout << "height = " << (b0 + b1*newAgeData + b2*newWeightData)*heightSD + heightMean << endl;

	system("pause");
	return 0;
}