#include <bits/stdc++.h>
#define width 23
using namespace std;

//prints header for player list table
void printHeader(){
    cout << left << setw(width) << "Name" << setw(width) << "Age" << setw(width) << "Country" << setw(width) << "Role" << setw(width) << "Style" << endl;
}

//prints border for player list table
void printBorder(){
    for (int i = 0; i < width*5; i++) 
            cout<< "-";
    cout << endl;   
}

// gets string input from line
string getString(const string& prompt) {
    cout << prompt;
    string input;
    getline(cin, input);
    return input;
}

int readInt(const string& prompt) {
    int value;
    cout << prompt;

    while (!(cin >> value)) {
        cin.clear(); // clear the error flags
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard the newline input
        cout << "\nERROR: Invalid input. Please enter an integer: ";
    }

    // Discard any remaining characters in the buffer
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    return value;
}

// Convert a string to lowercase
string toLowerCase(const string& str) {
    string result;
    for (char c : str) {
        result += tolower(c);
    }
    return result;
}

// Perform a case-insensitive string comparison
bool stringCompare(const string& str1, const string& str2) {
    return toLowerCase(str1) == toLowerCase(str2);
}

class Player
{

public:
    string playerName;
    int playerAge;
    string playerCountry;
    string playerRole;
    string playerStyle;
    Player()
    {
        playerName = "";
        playerAge = 0;
        playerCountry = "";
        playerRole = "";
        playerStyle = "";
    }
    Player(string name, int age, string country, string role, string style)
    {
        playerName = name;
        playerAge = age;
        playerCountry = country;
        playerRole = role;
        playerStyle = style;
    }
    
    void getPlayerDetails()
    {
        // make all strings take up the same space
        cout << left << setw(width) << playerName << setw(width) << playerAge << setw(width) << playerCountry << setw(width) << playerRole << setw(width) << playerStyle << endl;
    }
    void setPlayerDetails(string playerName, int playerAge, string playerCountry, string playerRole, string playerStyle)
    {
        this->playerName = playerName;
        this->playerAge = playerAge;
        this->playerCountry = playerCountry;
        this->playerRole = playerRole;
        this->playerStyle = playerStyle;
    }

    // update player details
    void updatePlayer(){
        cout << "\nWhich detail do you want to update?" << endl;
        cout << left << setw(width) << "\n1. Name    2. Age    3. Country    4. Role    5. Style    6. All details" <<endl;
        int choice = readInt("\nEnter your choice: ");
        switch (choice)
        {
            case 1:
            {
                string newName = getString("\nEnter new name: ");
                setPlayerName(newName);
                break;
            }
            case 2:
            {
                int newAge = readInt("\nEnter new age: ");
                setPlayerAge(newAge);
                break;
            }
            case 3:
            {
                string newCountry = getString("\nEnter new country: ");
                setPlayerCountry(newCountry);
                break;
            }
            case 4:
            {
                string newRole = getString("\nEnter new role: ");
                setPlayerRole(newRole);
                break;
            }
            case 5:
            {
                string newStyle = getString("\nEnter new style: ");
                setPlayerStyle(newStyle);
                break;
            }
            case 6:
            {
                string newName, newCountry, newRole, newStyle;
                int newAge;
                newName = getString("\nEnter new name: ");
                newAge = readInt("\nEnter new age: ");
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                newCountry = getString("\nEnter new country: ");
                newRole = getString("\nEnter new role: ");
                newStyle = getString("\nEnter new style: ");
                setPlayerDetails(newName, newAge, newCountry, newRole, newStyle);
                break;
            }
        }
    }
    string getPlayerName()
    {
        return playerName;
    }
    int getPlayerAge()
    {
        return playerAge;
    }
    string getPlayerCountry()
    {
        return playerCountry;
    }
    string getPlayerRole()
    {
        return playerRole;
    }
    string getPlayerStyle()
    {
        return playerStyle;
    }
    void setPlayerName(string name)
    {
        playerName = name;
    }
    void setPlayerAge(int age)
    {
        playerAge = age;
    }
    void setPlayerCountry(string country)
    {
        playerCountry = country;
    }
    void setPlayerRole(string role)
    {
        playerRole = role;
    }
    void setPlayerStyle(string style)
    {
        playerStyle = style;
    }
};
