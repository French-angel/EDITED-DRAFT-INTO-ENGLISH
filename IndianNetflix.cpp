#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

vector<string> films; // Global vector to store films

// Function to write films to file
void writeToFile(const vector<string> &filmNames, const vector<string> &filmInfo) {
    ofstream file("films.txt", ios::app);
    if (!file.is_open()) {
        cout << "Error opening file for writing." << endl;
        return;
    }
    
    for (size_t i = 0; i < filmNames.size() && i < filmInfo.size(); i++) {
        file << filmNames[i] << " | " << filmInfo[i] << endl;
    }
    file.close();
}

// Function to add a new film
void addFilm() {
    string filmName, filmDetails;
    cout << "Enter film title to add: ";
    cin.ignore();
    getline(cin, filmName);
    
    cout << "Enter film information (year, genre, etc.): ";
    getline(cin, filmDetails);
    
    films.push_back(filmName);
    films.push_back(filmDetails);
    
    writeToFile({filmName}, {filmDetails});
    cout << "Film: '" << filmName << "' added successfully." << endl;
}

// Function to search for a film
void searchFilm() {
    string searchQuery;
    cout << "Enter film title to search: ";
    cin.ignore();
    getline(cin, searchQuery);
    
    vector<string> storedFilms;
    ifstream file("films.txt");
    if (!file.is_open()) {
        cout << "Film database not found." << endl;
        return;
    }
    
    string line;
    bool found = false;
    while (getline(file, line)) {
        storedFilms.push_back(line);
        
        // Check if the line contains the search query
        if (line.find(searchQuery) != string::npos) {
            cout << "Film found!" << endl;
            cout << "Film details: " << line << endl;
            found = true;
        }
    }
    file.close();
    
    if (!found) {
        cout << "Film not found in the database." << endl;
    }
}

// Function to display all films
void displayAllFilms() {
    vector<string> storedFilms;
    ifstream file("films.txt");
    if (!file.is_open()) {
        cout << "Film database not found or empty." << endl;
        return;
    }
    
    string line;
    cout << "\n=== All Films in Database ===\n" << endl;
    int count = 1;
    while (getline(file, line)) {
        if (!line.empty()) {
            cout << count << ". " << line << endl;
            count++;
        }
    }
    file.close();
    
    if (count == 1) {
        cout << "No films found in the database." << endl;
    }
}

// Function to delete a film
void deleteFilm() {
    string filmToDelete;
    cout << "Enter film title to delete: ";
    cin.ignore();
    getline(cin, filmToDelete);
    
    vector<string> remainingFilms;
    ifstream fileIn("films.txt");
    if (!fileIn.is_open()) {
        cout << "Film database not found." << endl;
        return;
    }
    
    string line;
    bool found = false;
    while (getline(fileIn, line)) {
        // Extract film name (part before '|')
        size_t separatorPos = line.find('|');
        string filmName = (separatorPos != string::npos) ? 
                         line.substr(0, separatorPos) : line;
        
        // Trim whitespace
        filmName.erase(filmName.find_last_not_of(" \t") + 1);
        filmName.erase(0, filmName.find_first_not_of(" \t"));
        
        // Check if this is the film to delete
        if (filmName != filmToDelete) {
            remainingFilms.push_back(line);
        } else {
            found = true;
        }
    }
    fileIn.close();
    
    if (found) {
        // Rewrite file without the deleted film
        ofstream fileOut("films.txt");
        for (const auto& film : remainingFilms) {
            fileOut << film << endl;
        }
        fileOut.close();
        cout << "Film: '" << filmToDelete << "' successfully deleted." << endl;
    } else {
        cout << "Film not found in the database." << endl;
    }
}

int main() {
    string choice;
    
    cout << "=== FILM DATABASE ===" << endl;
    cout << "1. Add a new film" << endl;
    cout << "2. Search for a film" << endl;
    cout << "3. View all films" << endl;
    cout << "4. Delete a film" << endl;
    cout << "Enter your choice (1-4): ";
    cin >> choice;
    
    if (choice == "1") {
        addFilm();
    } else if (choice == "2") {
        searchFilm();
    } else if (choice == "3") {
        displayAllFilms();
    } else if (choice == "4") {
        deleteFilm();
    } else {
        cout << "Invalid choice: " << choice << endl;
    }
    
    return 0;
}
