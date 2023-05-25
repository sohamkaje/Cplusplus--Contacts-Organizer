#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <cstring>

using namespace std;

class Contact {
public:
    struct Numbers {
        string number;
        char phoneType;
    };

    vector<Numbers> phoneNumber;

    // Constructor
    Contact(char, string, string);
    Contact(char, vector<Numbers>&);

    // Getters
    string getFirstName();
    string getLastName();
    char getContactType();
    string getState();
    string getEmail();
    string getDateOfBirth();

    // Setters
    void setFirstName(string newFirstName);
    void setLastName(string newLastName);
    void setContactType(char newContactType);
    void setEmail(string newEmail);
    void setDateOfBirth(string newDateOfBirth);

    void setAddress(int newStreetNum, string newStreet, string newCity,
                    string newState, int newZipcode);
    string getName();
    string getAddress();
    string addPhone(char type, string number);
    string deletePhone(int index);
    string getAsString();
    string changeType(char contactType);

    string tester();

private:
    char contactType;

    string firstName;
    string lastName;
    string streetName;
    string city;
    string state;
    string email;
    string dateOfBirth;

    int streetNumber;
    int postalCode;
};

// Constructor (char, string, string)
Contact::Contact(char newContactType, string newFirstName, string newLastName)
        : contactType(newContactType), firstName(newFirstName),
          lastName(newLastName) {}

// Constructor (char, vector<Numbers>&)
Contact::Contact(char newContactType, vector<Numbers>& newNumbers)
        : contactType(newContactType), phoneNumber(newNumbers) {}

// Getters
string Contact::getFirstName() { return firstName; }

string Contact::getLastName() { return lastName; }

char Contact::getContactType() { return contactType; }

string Contact::getState() { return state; }

string Contact::getEmail() { return email; }

string Contact::getDateOfBirth() { return dateOfBirth; }

// Setters
void Contact::setFirstName(string newFirstName) { firstName = newFirstName; }

void Contact::setLastName(string newLastName) { lastName = newLastName; }

void Contact::setContactType(char newContactType) { contactType = newContactType; }

void Contact::setEmail(string newEmail) { email = newEmail; }

void Contact::setDateOfBirth(string newDateOfBirth) { dateOfBirth = newDateOfBirth; }

// Set address
void Contact::setAddress(int newStreetNum, string newStreet, string newCity,
                         string newState, int newZipcode) {
    streetNumber = newStreetNum;
    streetName = newStreet;
    city = newCity;
    state = newState;
    postalCode = newZipcode;
}

string Contact::getAddress() {
    return to_string(streetNumber) + " " + streetName + ", " + city +
           ", " + state + " " + to_string(postalCode);
}

string Contact::getName() {
    return lastName + ", " + firstName;
}

string Contact::addPhone(char type, string number) {
    string message;
    string stringtype(1, type);
    if ((toupper(type) == 'W') || (toupper(type) == 'H') ||
        (toupper(type) == 'C')) {
        Numbers n1;
        n1.number = number;
        n1.phoneType = type;
        phoneNumber.push_back(n1);
        string display = changeType(type);
        message = "success: added number " + number + " " + display;
    } else {
        message = "failure: invalid phone type - " + stringtype;
    }
    return message;
}

string Contact::deletePhone(int index) {
    string message;
    if (index < phoneNumber.size() && index >= 0) {
        // If the index is within the valid range, delete the phone number at the specified index
        phoneNumber.erase(phoneNumber.begin() + index);
        message = "success: deleted phone " + to_string(index);
    } else {
        // If the index is out of range, indicate failure to delete the phone number
        message = "failure: unable to delete phone " + to_string(index);
    }
    return message;
}

string Contact::changeType(char contactType) {
    string message;
    if ((toupper(contactType) == 'W') || (toupper(contactType) == 'H') ||
        (toupper(contactType) == 'C') || (toupper(contactType) == 'P')) {
        // Convert the character contactType to its corresponding string representation
        if (toupper(contactType) == 'W') {
            message = "Work";
        } else if (toupper(contactType) == 'H') {
            message = "Home";
        } else if (toupper(contactType) == 'C') {
            message = "Cell";
        } else if (toupper(contactType) == 'P') {
            message = "Personal";
        }
    }
    return message;
}

string Contact::getAsString() {
    string message;
    // Create a string representation of the contact's address
    string address = to_string(streetNumber) + " " + streetName + ", " + city +
                     ", " + state + " " + to_string(postalCode);
    string allNumbers;
    // Iterate over all phone numbers and create a string representation of each phone number
    for (int i = 0; i < phoneNumber.size(); i++) {
        allNumbers += changeType(phoneNumber.at(i).phoneType) + ": " +
                      phoneNumber.at(i).number + "\n";
    }
    // Create a formatted string representation of the contact's details
    message = getName() + "\n" + changeType(contactType) + "\n" + address + "\n" +
              dateOfBirth + "\n" + email + "\n" + allNumbers;
    return message;
}

bool operator<(Contact rhs, Contact lhs) {
    bool less;
    // Compare two Contact objects based on their names
    if (rhs.getName() < lhs.getName()) {
        less = true;
    } else {
        less = false;
    }
    return less;
}

class ContactList {
private: 
    vector<Contact> contacts;
public:
    string loadContactsFromFile(string filename);
    int getCount();
    string sortContacts();
    vector<int> findContactsByName(string checkname);
    void printContacts();
    void printContacts(vector<int> index);
    string addContact(Contact x);
    string deleteContact(int index);
    string tester();
};

ifstream open(const string &src_file) {
    ifstream src{src_file};
    // if statement to check whether file is open or not.
    return src;
}

string ContactList::loadContactsFromFile(string filename) {
    string line;

    ifstream file;
    // Open the specified file
    file = open(filename);

    getline(file, line);
    while (getline(file, line)) {
        stringstream ss(line);

        string type;
        getline(ss, type, ',');
        char type1;
        if (type == "personal") {
            type = "P";
        } else if (type == "work") {
            type = "W";
        }
        // Convert the contact type string to a character
        type1 = type[0];

        string firstName;
        getline(ss, firstName, ',');

        string lastName;
        getline(ss, lastName, ',');

        Contact c1(type1, firstName, lastName);

        string streetNum;
        getline(ss, streetNum, ',');
        int streetNum1 = stoi(streetNum);

        string streetName;
        getline(ss, streetName, ',');

        string city;
        getline(ss, city, ',');

        string state;
        getline(ss, state, ',');

        string zipcode;
        getline(ss, zipcode, ',');
        int zipcode1 = stoi(zipcode);
        // Set the address of the contact
        c1.setAddress(streetNum1, streetName, city, state, zipcode1);

        string email;
        getline(ss, email, ',');
        // Set the email of the contact
        c1.setEmail(email);

        string date;
        getline(ss, date, ',');
        // Set the date of birth of the contact
        c1.setDateOfBirth(date);

        string age;
        getline(ss, age, ',');

        string phone1;
        getline(ss, phone1, ',');
        // Add the first phone number to the contact
        c1.addPhone('H', phone1);

        string phone2;
        getline(ss, phone2);
        // Add the second phone number to the contact
        c1.addPhone('C', phone2);

        // Add the contact to the contact list
        contacts.push_back(c1);
    }

    string message;
    if (contacts.size() > 0) {
        message = "success: " + to_string(contacts.size()) + " contacts added";
    } else {
        message = "failure: " + filename + " not found";
    }

    return message;
}

int ContactList::getCount() {
    int num;
    // Get the number of contacts in the contact list
    num = contacts.size();
    return num;
}

string ContactList::sortContacts() {
    if (contacts.size() <= 0) {
        // If there are no contacts, indicate failure to sort
        return "failure";
    }
    // Sort the contacts in the contact list based on their names
    sort(contacts.begin(), contacts.end());
    if (is_sorted(contacts.begin(), contacts.end())) {
        // If the contacts are sorted, indicate success
        return "success";
    } else {
        // If the contacts are not sorted, indicate failure
        return "failure";
    }
}

vector<int> ContactList::findContactsByName(string checkname) {
    vector<int> indices;
    // Change all letters of checkname to lowercase
    for (int x = 0; x < checkname.size(); x++) {
        checkname.at(x) = tolower(checkname.at(x));
    }

    size_t found;

    for (int i = 0; i < contacts.size(); i++) {
        // Change all letters of each getName() to lowercase
        string temp = contacts.at(i).getName();
        for (int y = 0; y < temp.size(); y++) {
            temp.at(y) = tolower(temp.at(y));
        }
        // Check if checkname is present in the contact's name
        found = temp.find(checkname);

        if (found != string::npos) {
            // If checkname is found, add the contact's index to the indices vector
            indices.push_back(i);
        }
    }
    return indices;
}

void ContactList::printContacts() {
    for (int i = 0; i < contacts.size(); i++) {
        if (i == (contacts.size() - 1)) {
            // Print the contact's details
            cout << contacts.at(i).getAsString() << endl;
        } else {
            cout << "--------------------" << endl;
            cout << endl;
            // Print the contact's details with a separator
            cout << contacts.at(i).getAsString() << endl;
        }
    }
}

void ContactList::printContacts(vector<int> index) {
    for (int i = 0; i < index.size(); i++) {
        if (i == (contacts.size() - 1)) {
            // Print the contact's details
            cout << contacts.at(index.at(i)).getAsString() << endl;
        } else {
            cout << "--------------------" << endl;
            cout << endl;
            // Print the contact's details with a separator
            cout << contacts.at(index.at(i)).getAsString() << endl;
        }
    }
}

string ContactList::addContact(Contact x) {
    string message;
    // Add the contact to the contact list
    contacts.push_back(x);
    for (int i = 0; i < contacts.size(); i++) {
        if (contacts.at(i).getAsString() == x.getAsString()) {
            // If the contact is successfully added, indicate success
            message = "success: contact " + x.getLastName() + ", " +  x.getFirstName() + " added";
            break;
        }
        else {
            // If the contact cannot be added, indicate failure
            message = "failure: unable to add contact";
        }
    }
    return message;
}

string ContactList::deleteContact(int index) {
    string message;
    string name = contacts.at(index).getName();
    for (int i = 0; i < contacts.size(); i++) {
        if (contacts.at(index).getAsString() == contacts.at(i).getAsString()) {
            // If the contact is found and deleted, indicate success
            contacts.erase(contacts.begin() + index);
            message = "success: deleted contact " + name;
            break;
        } else {
            // If the contact cannot be deleted, indicate failure
            message = "failure: unable to delete contact " + to_string(index);
        }
    }
    return message;
}

// EXAMPLE MAIN, USER CAN CHANGE TO THEIR LIKING
int main() {

    ContactList myContacts;

    myContacts.loadContactsFromFile("contacts.csv");

    myContacts.sortContacts();

    vector<int> v = myContacts.findContactsByName("ra");

    myContacts.printContacts(v);

    return 0;

}
