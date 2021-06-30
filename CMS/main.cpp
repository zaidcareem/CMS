/*
Author  - MZA Careem
Project - Contact Management System
Date    - 25/06/2021

This application can add a contact and display all contacts only. Done for practice as a beginner.
*/

#include <iostream>
#include <unistd.h>
#include <windows.h>
#include <conio.h>
#include <fstream>

using namespace std;

const int MAX_CONTACTS = 50;
const string PHONEBOOK_NAME = "MyPhoneBook.txt"; // data storage file name.

struct Contact {

    string name;
    string phone_number;
};

//function to get the data ready to be in use for the program. THIS CREATES AN .txt FILE AUTOMATICALLY. AND IT WILL BE EMPTY IF 
void readAllData(Contact contact_list[], int& num_people) {                                            // THERE ARE NO CONTACTS.

    ifstream reader;
    reader.open(PHONEBOOK_NAME, ios::app); // creates a .txt file if no file is there.

    if (reader.fail()) {
        cout << "Error opening database file." << endl;
        return;
    }
    // read data.
    int i = 0; // used for array indexing.
    getline(reader, contact_list[i].name);          // 1st line is name.

    while (!reader.eof() && i < MAX_CONTACTS) // eof() returns true if a file set to be reading reaches its end.
	{
		getline(reader, contact_list[i].phone_number);  // 2nd line of .txt file is number.  AND SO ON THE PATTERN GOES.

		i++;

		// Be careful not to read outside the array bounds
		if (i < MAX_CONTACTS) {
			getline(reader, contact_list[i].name);
        }
	}
    num_people = i;
    reader.close();
}

// add fata to file.
void appendToFile(Contact contact)
{
	ofstream writer;
	writer.open(PHONEBOOK_NAME, ios::app);

	writer << contact.name << endl;
	writer << contact.phone_number << endl;
   
	writer.close();  
}

// Add contacts to database file.
void addContacts(Contact contact_list[], int& num_people) {

    Contact contact;
    cin.ignore();
	cout <<"\nEnter a name to be added: ";
	getline(cin, contact.name);
	cout <<"Enter the person's number: ";
	getline(cin, contact.phone_number);

    for (int i=0; i < num_people; i++) {
        if (i+1 == num_people) {
            contact_list[num_people] = contact;
        }
    }
    num_people++;

    appendToFile(contact);
    readAllData(contact_list, num_people);
    cout <<"\n\nName has been added. "<<endl;  
}

// Display ALL contacts
void displayAllContacts(Contact contact_list[], int num_people) {

    cout << "--- ALL Contacts ------\n" << endl;
    for (int i=0; i < num_people; i++) {
        cout << contact_list[i].name << "\t--\t" << contact_list[i].phone_number << endl;
    }
}

int main() {

    Contact contact_list[MAX_CONTACTS]; // Array containing all contacts. (struct objects)
    int num_people; // through the power of referencing this will be given the value of the no:of currently existing contacts
                                                                                          // through the readAllData function.
    // LOAD THE DATA.
    readAllData(contact_list, num_people);                                                            

    cout << "\n\n\t\t--------  PHONE BOOK APP  ----------------------------------------------------------------------\n" << endl;

    int choice=10;

    while (choice!=0) {

    cout << "\n\t\tEnter # - ______________________________________________________________________________________\n" << endl;
    cout << "\t\t      1 - Add Contact" << endl;
    cout << "\t\t      2 - Display All Contacts\n" << endl;
    cout << "\t\t      0 - EXIT APP\n" << endl;

    cout << "ENTER CHOICE : ";
    cin >> choice;
    cout << "\n";

    switch (choice) {
    
        case (1) :
            addContacts(contact_list, num_people);
            break;
        case (2):
            displayAllContacts(contact_list, num_people);
            break;
        case (0):
            break; // EXITS
        default:
            cout << "Enter a valid CHOICE!" << endl; // issue = crashes when entered a non integer value.
            break; 

    }
}
    cout << "\n\n\t\t--------  PHONE BOOK APP  ----------------------------------------------------------------------\n\t\t--------  CLOSED.";
    sleep(1);
        
    

    return 0;
}