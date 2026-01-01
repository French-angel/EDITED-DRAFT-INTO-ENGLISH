#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <limits>

using namespace std;

// Function to add user notes
void addNote(vector<string> &notes)
{
    string note;
    cout << "Enter your note: ";
    cin.ignore();
    getline(cin, note);
    notes.push_back(note);
    cout << "Note added successfully." << endl;
    
    ofstream file("users.txt", ios::app);
    for (size_t i = 0; i < notes.size(); i++)
    {
        file << notes[i] << endl;
    }
    file.close();
}

// User profile management function
void userProfile()
{
    vector<string> notes;
    while(true){
        string action;
        cout << "Select an action:" << endl;
        cout << "add - Add a note" << endl;
        cout << "change - Change account password" << endl;
        cin >> action;
        
        if (action == "add")
        {
            addNote(notes);
        }
        // Additional actions can be added here
    }
}

// Save users and passwords to file
void saveUsers(const vector<string> &users, const vector<string> &passwords)
{
    ofstream file("users.txt");
    for (size_t i = 0; i < users.size(); i++)
    {
        file << users[i] << " " << passwords[i] << endl;
    }
    file.close();
}

// Load users and passwords from file
void loadUsers(vector<string> &users, vector<string> &passwords)
{
    ifstream file("users.txt");
    if (!file.is_open())
    {
        cout << "No existing user file found." << endl;
        return;
    }
    
    string user, password;
    int count = 0;
    while (file >> user >> password)
    {
        users.push_back(user);
        passwords.push_back(password);
        count++;
    }
    file.close();

    if (count > 0)
    {
        cout << "Loaded " << count << " users" << endl;
    }
    else
    {
        cout << "File is empty" << endl;
    }
}

// Function to reset user password
void resetPassword(vector<string> &usernames, vector<string> &passwords)
{
    string usernameToChange;
    cout << "Enter username to change password: ";
    cin >> usernameToChange;

    bool userFound = false;
    for (size_t i = 0; i < usernames.size(); i++)
    {
        if (usernames[i] == usernameToChange)
        {
            userFound = true;
            string newPassword;
            cout << "Enter new password: ";
            cin >> newPassword;

            // Password validation
            if (newPassword.size() < 8 || newPassword.size() > 14)
            {
                cout << "Password must be between 8 and 14 characters." << endl;
                return;
            }

            // Check for valid characters
            for (char elem : newPassword)
            {
                if (elem < 33 || elem > 126)
                {
                    cout << "Invalid character detected." << endl;
                    return;
                }
            }

            // Check password complexity
            int uppercaseCount = 0;
            int lowercaseCount = 0;
            int specialCharCount = 0;

            for (char elem : newPassword)
            {
                if (elem >= 'A' && elem <= 'Z')
                {
                    uppercaseCount++;
                }
                else if (elem >= 'a' && elem <= 'z')
                {
                    lowercaseCount++;
                }
                else
                {
                    specialCharCount++;
                }
            }

            if (uppercaseCount >= 1 && lowercaseCount >= 1 && specialCharCount >= 1)
            {
                cout << "Enter old password for verification: ";
                string oldPassword;
                cin >> oldPassword;
                
                if (oldPassword != passwords[i])
                {
                    cout << "Incorrect old password." << endl;
                    return;
                }
                
                passwords[i] = newPassword;
                cout << "Password changed successfully." << endl;
                saveUsers(usernames, passwords);
            }
            else
            {
                cout << "Password must contain at least one uppercase letter, one lowercase letter, and one special character." << endl;
            }
            return;
        }
    }
    
    if (!userFound)
    {
        cout << "User '" << usernameToChange << "' not found!" << endl;
    }
}

// Main function
int main()
{
    vector<string> usernames;
    vector<string> passwords;
    vector<string> notes;
    string username;

    cout << "Welcome! What would you like to do?" << endl;
    cout << "Type 'change password' to reset your password" << endl;
    cout << "Type 'register' to create a new account" << endl;
    
    string action;
    getline(cin, action);
    
    loadUsers(usernames, passwords);
    
    if (action == "change password")
    {
        resetPassword(usernames, passwords);
    }
    else if (action == "register")
    {
        cout << "Enter username: ";
        cin >> username;

        bool usernameExists = false;
        for (auto existingUser : usernames)
        {
            if (existingUser == username)
            {
                cout << "Username already taken." << endl;
                usernameExists = true;
                break;
            }
        }

        string password;
        if (!usernameExists)
        {
            cout << "Enter password: ";
            cin >> password;
        }

        if (!usernameExists)
        {
            // Password validation
            if (password.size() < 8 || password.size() > 14)
            {
                cout << "Password must be between 8 and 14 characters." << endl;
                return 0;
            }

            // Check for valid characters
            for (char elem : password)
            {
                if (elem < 33 || elem > 126)
                {
                    cout << "Invalid character: " << elem << endl;
                    return 0;
                }
            }

            // Check password complexity
            int uppercaseCount = 0;
            int lowercaseCount = 0;
            int specialCharCount = 0;

            for (char elem : password)
            {
                if (elem >= 'A' && elem <= 'Z')
                {
                    uppercaseCount++;
                }
                else if (elem >= 'a' && elem <= 'z')
                {
                    lowercaseCount++;
                }
                else
                {
                    specialCharCount++;
                }
            }

            if (uppercaseCount >= 1 && lowercaseCount >= 1 && specialCharCount >= 1)
            {
                cout << "Registration successful!" << endl;
                usernames.push_back(username);
                passwords.push_back(password);

                saveUsers(usernames, passwords);

                cout << "\nSaved data:" << endl;
                cout << "Username: " << usernames.back() << endl;
                cout << "Password: " << passwords.back() << endl;

                addNote(notes);
                cout << "Note: " << notes.back() << endl;
            }
            else
            {
                cout << "Password must contain at least one uppercase letter, one lowercase letter, and one special character." << endl;
            }
        }

        return 0;
    }
    else
    {
        cout << "Invalid action. Please restart the program." << endl;
    }
    
    return 0;
}
