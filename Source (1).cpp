//MAIN

#include <iostream>
#include <string>
#include <fstream>
#include "HashADT.h"
#include "Incidents.h"
#include "BinarySearchTree.h"

using namespace std;

bool inputValidation(string choice);
void menu(HashTable <Incidents> &ht, BinarySearchTree<Incidents> &bst1, BinarySearchTree<Incidents> &bst2); // parameters will include objects of BST class and Hashing and Incidents
void readFile(string filename, HashTable<Incidents>& ht, BinarySearchTree<Incidents> &bst1, BinarySearchTree<Incidents> &bst2);
void insertData(BinarySearchTree <Incidents> &ht);
void listData(HashTable <Incidents> &ht, BinarySearchTree<Incidents> &bst1, BinarySearchTree<Incidents> &bst2);
void searchData(HashTable <Incidents> &ht, BinarySearchTree<Incidents> &bst1, BinarySearchTree<Incidents> &bst2);
void display(Incidents &incident);

int main()
{
    HashTable<Incidents> hTable;
	BinarySearchTree<Incidents> one;
	BinarySearchTree<Incidents> two;
    readFile("finaldata.txt", hTable, one, two);
	menu(hTable, one, two);
	return 0;
}

void menu(HashTable <Incidents> &ht, BinarySearchTree<Incidents> &bst1, BinarySearchTree<Incidents> &bst2)
{
	string choice;
	cout << "Choose one of the following: " << endl;
	cout << "A: Add data" << endl;
	cout << "D: Delete data" << endl;
	cout << "F: Find data" << endl;
	cout << "L: List data " << endl;
	cout << "W: Write data " << endl;
	cout << "S: Statistics " << endl;
	cout << "H: Help" << endl;
	cout << "E: Exit " << endl;

	cout << "Enter your choice: ";
	getline(cin, choice);

	while (choice[0] != 'E')
	{
		if (inputValidation(choice) == true)
		{
			switch (choice[0])
			{
				case 'A': //insertmanager
					break;
				case 'D': //deletemanager
					break;
				case 'F': //searchmanager
					break;
				case 'L': //listmanager 
				{	
					listData(ht, bst1, bst2);
					//bst1.inOrder(display);
					//ht.printHashTable();
				}
					break;
				case 'W': //write to file
					break;
				case 'S': //statsmanager
					break;
				case 'H':
				{
					cout << "-- Displaying menu -- " << endl;
					cout << "A: Add data" << endl;
					cout << "D: Delete data" << endl;
					cout << "F: Find data" << endl;
					cout << "L: List data " << endl;
					cout << "W: Write data " << endl;
					cout << "S: Statistics " << endl;
					cout << "H: Help" << endl;
					cout << "E: Exit " << endl;
				}
					break;
				default: "Invalid option. Try again.\n";
			}
		}

		cout << endl << "Enter your choice: ";
		getline(cin, choice);
	}

}

bool inputValidation(string choice)
{
	if (choice.length() == 1 && isalpha(choice[0]))
		return true;

	return false;
}


void readFile(string filename, HashTable <Incidents> &ht, BinarySearchTree<Incidents> &bst1, BinarySearchTree<Incidents> &bst2)
{
	ifstream infile;
	Incidents incident;


	// Open the input file
	infile.open(filename.c_str());
	if (infile.fail())
	{
		cout << "\nError opening the input file: " << filename << endl;
		return;
	}

	//Incidents incident;
	string ID, state, date, race, gender;
	int fatalities;

	// Read the file line by line.
	while (getline(infile, ID, ','))
	{
		infile.ignore(); // to discard ','
		//infile >> ID; infile.ignore();

		getline(infile, state, '"'); infile.ignore(); //ignore ,
		getline(infile, date, ',');
		infile >> fatalities; infile.ignore();
		getline(infile, race, ',');
		getline(infile, gender);

		// if DEBUG is defined, then print everything which was just read.

        cout << "ID=" <<ID << ",";
		cout << "State=" << state << ",";
		cout << "Date=" << date << ",";
		cout << "Fatalities=" << fatalities << ",";
		cout << "Race=" << race << ",";
		cout << "Gender=" << gender << "," << endl;

		incident.setID(ID);
		incident.setState(state);
		incident.setDate(date);
		incident.setFatalities(fatalities);
		incident.setRace(race);
		incident.setGender(gender);


		// Call insertnode with the correct templated type, once Incidents class is available
		ht.insertNode (incident,  ID);
		bst1.insert(incident);

		// Below is just for testing, using string instead of Incidents
        //hashTable.insertNode (title,  ID);


		// Below couts were just for testing the readFile function


	}

	// Close the input file
	infile.close();
}

void insertData(BinarySearchTree <Incidents> &ht)
{

}

void display(Incidents &incident)
{
	cout << incident.getID() << endl;
}

void listData(HashTable<Incidents> &ht, BinarySearchTree<Incidents> &bst1, BinarySearchTree<Incidents> &bst2)
{
	string choice;

	cout << "Choose one of the following: " << endl;
	cout << "U - Unsorted List in Hash Table Sequence" << endl;
	cout << "P - Sorted List by ID" << endl;
	cout << "S - Sorted List by State" << endl;
	cout << "E - Exit" << endl;
	cout << endl << "Enter your choice: " << endl;
	
	getline(cin, choice);

	while (choice[0]!='E')
	{
		if (inputValidation(choice) == true)
		{
			switch (choice[0])
			{
			case 'U': ht.printHashTable();
				break;
			case 'P': bst1.inOrder(display);
				break;
			case 'S': //bst2.inOrder(display);
				break;
			default: cout << "Invalid choice. Try again." << endl;
			}
		}
		else
			cout << "Invalid input. Try again." << endl;
		cout << "Enter your choice: " << endl;
		getline(cin, choice);
	}
}

void searchData(HashTable <Incidents> &ht, BinarySearchTree<Incidents> &bst1, BinarySearchTree<Incidents> &bst2)
{
	string choice;
	string ID;

	cout << "Choose one of the following: " << endl;
	cout << "P - Search by ID" << endl;
	cout << "S - Search by State" << endl;
	cout << "E - Exit" << endl;
	cout << endl << "Enter your choice: " << endl;

	getline(cin, choice);

	while (choice[0] != 'E')
	{
		if (inputValidation(choice) == true)
		{
			switch (choice[0])
			{
			case 'P': 
			{
				cout << "Enter ID to search: ";
				getline(cin, ID);
				if (inputValidation(ID) == true)
				{
					//ht.searchNode(ID[0], ID); //how to make this work - EDIT this line @Charu
				}
			}
				break;
			case 'S': //use bst2
				break;
			default: cout << "Invalid choice. Try again." << endl;
			}
		}
		else
			cout << "Invalid input. Try again." << endl;
		cout << "Enter your choice: " << endl;
		getline(cin, choice);
	}
}