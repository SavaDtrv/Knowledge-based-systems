#include <iostream>
#include <fstream>

using namespace std;

const int MAX_SIZE = 256;

// The freq size for the reading of the file
const int FREQ_SIZE = 10;

// Numbers for the interval of k
const int MIN = 1;
const int MAX = 40;

// Coefficients for the frequency
const int FREQ_TO_INT_1 = 1;
const int FREQ_TO_INT_2 = 2;
const int FREQ_TO_INT_3 = 3;
const int FREQ_TO_INT_4 = 4;

// Converts the string frequency to coefficients
int convertFreq(char* freq) {
	if (strcmp(freq, "Veryoften") == 0)
	{
		return FREQ_TO_INT_4;
	}
	else if (strcmp(freq, "Often") == 0)
	{
		return FREQ_TO_INT_3;
	}
	else if (strcmp(freq, "Sometimes") == 0)
	{
		return FREQ_TO_INT_2;
	}
	else
		return FREQ_TO_INT_1;
}

struct Person {
	int spendings; // The money that the person spent
	int frequency; // The frequency of the spendings will be converted to int
	int discountOrNo; // The person bought products with discount or with no discount
	double distance; // The distance between the neightbours

	Person() {
		spendings = 0;
		frequency = 0;
		discountOrNo = 0;
		distance = 0.0;
	}

	friend istream& operator >> (istream& in, Person& newPerson) {
		
		cout << "Enter the spendings: ";
		in >> newPerson.spendings;
		cout << "And enter the frequency:\n"
			<< "	1. Veryoften;\n"
			<< "	2. Often;\n"
			<< "	3. Sometimes;\n"
			<< "	4. Rarely;\n" 
			"Your input: ";
		char freq[FREQ_SIZE];
		in >> freq;
		cout << endl;
		newPerson.frequency = convertFreq(freq);

		return in;
	}
};

class Classification {
private:

	bool comparison(Person fPers, Person sPers)
	{
		return (fPers.distance > sPers.distance);
	}

	void swap(Person *fPers, Person *sPers)
	{
		Person temp = *fPers;
		*fPers = *sPers;
		*sPers = temp;
	}
public:
	// Default constructor
	Classification() {
		size = 0;
	}
	
	// Function for reading the file
	void readFile(char* fileName) {

		ifstream fi(fileName, ios::in);

		int cost;
		int discORno;
		char tmp[FREQ_SIZE];
		int freq;

		char symbol;

		if (fi.is_open()) {
			while (!fi.eof()) {
				cost = 0;
				discORno = 0;
				freq = 0;

				fi >> cost;
				people[size].spendings = cost;

				fi >> symbol;
				fi >> tmp;
				freq = convertFreq(tmp);
				people[size].frequency = freq;

				fi >> symbol;
				fi >> discORno;
				people[size].discountOrNo = discORno;

				size++;
			}
		}
		fi.close();
	}

	// I'm using bubble-sort since the dataset is small
	// and it will sort it fast. If i had a bigger dataset
	// i would have used merge-sort.
	void sort() {
		int i, j;
		for (i = 0; i < size - 1; i++)    
			for (j = 0; j < size - i - 1; j++)
				if (comparison(people[j], people[j + 1]))
					swap(&people[j], &people[j + 1]);
	}

	// This function finds classification of the new person using 
	// k nearest neighbours algorithm. It assumes only two 
	// groups and returns 0 if the person belongs to group 0, else 
	// 1 (belongs to group 1).
	int classifyAPerson(Person people[], int n, int k, Person newPerson)
	{
		// Fill distances of all people from the new person 
		for (int i = 0; i < n; i++)
			people[i].distance =
			sqrt((people[i].spendings - newPerson.spendings) * 
			(people[i].spendings - newPerson.spendings) +
			(people[i].frequency - newPerson.frequency) * 
			(people[i].frequency - newPerson.frequency));

		// Sort the people by distance from the new person 
		sort();
		
		// Considering: 
		// Two groups 
		int freq0 = 0;     // Frequency of group 0 
		int freq1 = 0;     // Frequency of group 1 

		// And the first k elements
		for (int i = 0; i < k; i++)
		{
			if (people[i].discountOrNo == 0)
				freq0++;
			else if (people[i].discountOrNo == 1)
				freq1++;
		}

		return (freq0 > freq1 ? 0 : 1);
	}

	// Main function of the class
	int classification(int k) {

		Person newPerson;
		cin >> newPerson;
		
		return classifyAPerson(people, size, k, newPerson);
	}

private:
	Person people[MAX_SIZE]; // The array of people for the training dataset
	int size; // The size of the array of people
};


int main() {
	// Reading and saving the dataset
	char* fileName = "Training_dataset.csv";
	Classification classif;
	classif.readFile(fileName);

	// The user inputs the number of the nearest neighbours
	int k = 0;
	cout << "Enter the number for the k nearest neighbours(between: 1 - 40): ";
	cin >> k;
	cout << endl;

	// We check if the number of neighbours satisfies the length
	// of our dataset, if not the user will have to input a new number
	// until the number satisfies our training dataset length.
	bool flag = false;
	bool check = (k < MIN || k > MAX);

	while (check && !flag) {
		system("cls");
		cout << "The number you have entered is not correct!\n"
			<< "Enter the number for the k nearest neighbours(between: 1 - 40): ";
		cin >> k;

		check = (k < MIN || k > MAX);
		if (!check) {
			flag = true;
		}
		
	}

	if(flag) {
		system("cls");
		cout << "Enter the number for the k nearest neighbours(between: 1 - 40): "
			<< k << "\n" << endl;
	}

	// We call the main function that will tell us the result.
	// And we print it as a message.
	if (classif.classification(k) == 0) {
		cout << "The person is expected to make "
		 << "non-discount purchases: 0" << endl;
	}
	else {
		cout << "The person is expected to make "
		 << "discount purchases: 1" << endl;
	}

	system("pause");
	return 0;
}