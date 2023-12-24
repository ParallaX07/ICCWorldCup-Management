#include <bits/stdc++.h>
#include "LinkedList.h"
#include "Player.h"
#include "Country.h"

using namespace std;

//contains list of all countries in the world cup
LinkedList<Country> countryList;

void addPlayer(string countryName, Player player); //adds player to a country
void deletePlayer(string countryName, string playerName); //deletes player from a country
void displayCountryList();  //displays all countries in the world cup
void displayPlayerList(string countryName);   //displays all players in a country
Node<Country> *findCountry(string name); //finds a country in the world cup
void writeToDatabase(); //writes all data to the database
void readFromDatabase(); //reads all data from the database
void displayMenu(); //displays the menu
void displayAllPlayers(); //displays all players in the world cup
Node<Player> *findPlayer(string name); //finds a player in the world cup
void updatePlayer(Node<Country> *country, string name); //updates player details

int main()
{
    readFromDatabase();
    bool exit = false;
    //start of menu
    while(exit == false){
        displayMenu();
        int choice = readInt("Enter your choice (int): ");
        cout << endl << endl;
        switch (choice)
        {
        case 1: //display all countries
            displayCountryList();
            cout << endl << endl;
            cout << "\n1. Display squad of a country\n2. Back" << endl;
            choice = readInt("Enter your choice (int): ");
            switch (choice)
            {
            case 1: 
            {
                string name = getString("Enter country name: ");
                displayPlayerList(name);
                break;
            }
            case 2:
                break;
            default:
                cout << "\nInvalid choice!" << endl;
                break;
            }
            break;
        case 2: //display all players
            displayAllPlayers();
            cout << endl << endl;
            break;
        case 3: //search player
        {
            string name = getString("Enter player name: ");
            Node<Player> *temp = findPlayer(name);
            if (temp == NULL)
            {
                cout <<endl;
                cout << "\nERROR: Player not found!" << endl;
                break;
            }
            else
            {   cout << endl;
                printBorder();
                printHeader();
                printBorder();
                temp->data.getPlayerDetails();
                printBorder();
                cout << endl;
                cout << "\n1. Update Player\n2. Remove Player\n3. Back" << endl;
                choice = readInt("Enter your choice (int): ");
                switch(choice){
                    case 1: //update player
                    {
                        writeToDatabase();
                        cout << endl;
                        printBorder();
                        printHeader();
                        printBorder();
                        temp->data.getPlayerDetails();
                        printBorder();
                        cout << "\nAre you sure you want to update this player? (y/n): ";
                        char choice;
                        cin >> choice;
                        choice = tolower(choice);
                        if (choice == 'n') break;
                        updatePlayer(findCountry(temp->data.getPlayerCountry()), name); //find country of player and update player details
                        writeToDatabase();
                        printBorder();
                        printHeader();
                        printBorder();
                        temp->data.getPlayerDetails();
                        printBorder();
                        
                        break;
                    }
                    case 2: //remove player
                    {
                        cout << "\nAre you sure you want to remove this player? (y/n): ";
                        char choice;
                        cin >> choice;
                        choice = tolower(choice);
                        if (choice == 'n') break;
                        string countryName = temp->data.getPlayerCountry();
                        deletePlayer(countryName, name);
                        writeToDatabase();
                        cout << endl;
                        cout << "\nPlayer removed!" << endl;
                        break;
                    }
                    case 3: //back
                        break;
                    default:
                        cout << "\nInvalid choice!" << endl;
                        break;
                }
            }
            break;
        }
        case 4: //search by country
        {   
            string name = getString("Enter country name: ");
            displayPlayerList(name);
            break;
        }
        case 5: //exit
            exit = true;
            cout << "Exiting...";
            writeToDatabase();
            break;
        default:
            cout << "\nInvalid choice!" << endl;
            break;
        }
    }
    return 0;
}

void displayMenu()
{
    cout << "\nMENU" << endl;
    cout << "1. Display all countries" << endl;
    cout << "2. Display players of all countries" << endl;
    cout << "3. Search a player" << endl;
    cout << "4. Search Country" << endl;
    cout << "5. Exit" << endl;
}

//goes through each country and searches for the player
Node<Player> *findPlayer(string name)
{
    Node<Country> *front = countryList.head;
    Node<Country> *back = countryList.tail;
    while (front != back)
    {
        Node<Player> *temp = front->data.searchPlayer(name);
        Node<Player> *temp2 = back->data.searchPlayer(name);
        if (temp != NULL )
        {
            return temp;
        }
        if (temp2 != NULL)
        {
            return temp2;
        }
        front = front->next;
        back = back->prev;
    }
    return NULL;
}

//goes through all countires to find the country
Node<Country>* findCountry(string name)
{
    Node<Country>* front = countryList.head;
    Node<Country>* back = countryList.tail;
    bool foundFront = false;
    bool foundBack = false;
    while (front != back)
    {
        foundFront = stringCompare(front->data.getCountryName(), name);
        foundBack = stringCompare(back->data.getCountryName(), name);
        if (foundFront)
        {
            return front;
        }
        if (foundBack)
        {
            return back;
        }
        front = front->next;
        back = back->prev;
    }
    return NULL;
}


//adds player to a country
void addPlayer(string countryName, Player player)
{
    Node<Country> *temp = findCountry(countryName);
    if (temp == NULL)
    {
        cout << endl;
        cout << "\nERROR: Country not found!" << endl;
        return;
    }
    temp->data.addPlayer(player);
}

//deletes player from a country
void deletePlayer(string countryName, string playerName)
{
    Node<Country> *temp = findCountry(countryName);
    if (temp == NULL)
    {
        cout << endl;
        cout << "\nERROR: Country not found!" << endl;
        return;
    }
    temp->data.deletePlayer(playerName);
}

//updates player details
void updatePlayer(Node<Country> *country, string name){
    //keep a copy of the original player, in case user wants to revert changes
    Player originalPlayer = country->data.searchPlayer(name)->data;
    string originalCountry = originalPlayer.getPlayerCountry();
    Player temp = country->data.updatePlayer(name);
    if (temp.getPlayerName() == "") return; //if player country not changed, return
    Node<Country> *temp2 = findCountry(temp.getPlayerCountry()); //finds country if player country changed
    if (temp2 == NULL) //if country does not exist, don't let player change country
    {
        cout << "\nERROR: Country not found in ICC World Cup 2023 list!" << endl;
        cout << "\nReverting changes..." << endl << endl;
        addPlayer(originalCountry, originalPlayer); //add player back to original country
        return;
    }
    temp2->data.addPlayer(temp);
}


//displays all countries in the world cup
void displayCountryList()
{
    cout << "----------------------------" << endl;
    cout << "ICC Cricket World Cup Squads" << endl;
    cout << "----------------------------" << endl;
    Node<Country> *temp = countryList.head;
    int i = 1;
    while (temp != NULL)
    {
        cout << i << ". " << temp->data.getCountryName() << endl;
        temp = temp->next;
        i++;
    }
    cout << "----------------------------" << endl;
}


//displays all players in a country
void displayPlayerList(string countryName)
{
    Node<Country> *temp = findCountry(countryName);

    if (temp == NULL){
        cout << endl;
        cout << "\nERROR: Country not found!" << endl;
        return;
    }
    temp->data.displayPlayerList();
    cout <<"\n1. Add player\n2. Remove Player\n3. Update Player\n4. Back" << endl;
    int choice = choice = readInt("Enter your choice (int): ");
    switch(choice)
    {
        case 1: //add player to the country
        {
            string name = getString("Enter player name: ");
            int age = readInt("Enter player age: ");
            //cin.ignore(numeric_limits<streamsize>::max(), '\n');  // clear the buffer
            string role = getString("Enter player role: ");
            string style = getString("Enter player style: ");
            Player player(name, age, temp->data.getCountryName(), role, style);
            cout << endl;
            printBorder();
            printHeader();  
            printBorder();
            player.getPlayerDetails();
            printBorder();
            cout << "\nAre you sure you want to add this player? (y/n): ";
            char choice;
            cin >> choice;
            if (choice == 'n') break;
            temp->data.addPlayer(player);
            writeToDatabase();
            cout << endl;
            temp->data.displayPlayerList();
            break;
        }
        case 2: //remove player from the country
        {
            string name = getString("Enter player name: ");
            cout << "\nAre you sure you want to remove this player? (y/n): ";
            char choice;
            cin >> choice;
            choice = tolower(choice);
            if (choice == 'n') break;
            temp->data.deletePlayer(name);
            writeToDatabase();
            cout << endl;
            temp->data.displayPlayerList();
            break;
        }
        case 3: //update player details
        {
            string name = getString("Enter player name: ");
            cout << "\nAre you sure you want to update this player? (y/n): ";
            char choice;
            cin >> choice;
            choice = tolower(choice);
            if (choice == 'n') break;
            updatePlayer(temp, name);
            writeToDatabase();
            cout << endl;
            temp->data.displayPlayerList();
            break;
        }
        case 4: //back
            return;
        default:
            cout << "\nInvalid choice!" << endl;
            break;
    }
}


//displays all players in the world cup
void displayAllPlayers()
{
    Node<Country> *temp = countryList.head;
    while (temp != NULL)
    {
        temp->data.displayPlayerList();
        temp = temp->next;
    }
}

//writes all data to the database
void writeToDatabase() {
    // Open the database file in write mode
    ofstream databaseFile("database.txt");

    // Check if the file is open
    if (!databaseFile) {
        cout << "\nUnable to open file!";
        return;
    }

    Node<Country>* temp = countryList.head;
    while (temp != NULL) {
        Country country = temp->data;

        // Write the country name
        //databaseFile << country.getCountryName() << endl;

        // Iterate over the player list in the country
        Node<Player>* playerNode = country.playerList.head;
        while (playerNode != NULL) {
            Player player = playerNode->data;

            // Write each attribute of the player on a new line
            databaseFile << player.getPlayerName() << endl;
            databaseFile << player.getPlayerAge() << endl;
            databaseFile << player.getPlayerCountry() << endl;
            databaseFile << player.getPlayerRole() << endl;
            databaseFile << player.getPlayerStyle() << endl;

            playerNode = playerNode->next;
        }

        temp = temp->next;
    }

    // Close the file after writing
    databaseFile.close();
}

//reads all data from the database
void readFromDatabase() {
    // Open the database file in read mode
    ifstream databaseFile("database.txt");

    // Check if the file is open
    if (!databaseFile) {
        cout << "\nUnable to open file!";
        return;
    }

    string line;
    while (std::getline(databaseFile, line)) {
        // writes the first line to player name
        Player player;

        player.setPlayerName(line);

        std::getline(databaseFile, line);
        player.setPlayerAge(stoi(line)); // convert string to int

        std::getline(databaseFile, line);
        string countryName = line;
        player.setPlayerCountry(countryName);

        std::getline(databaseFile, line);
        player.setPlayerRole(line);

        std::getline(databaseFile, line);
        player.setPlayerStyle(line);

        //check if player country already exists
        Node<Country> *temp = countryList.head;
        bool found = false;
        while (temp != NULL)
        {
            found = stringCompare(temp->data.getCountryName(), player.getPlayerCountry());
            if (found) //if country exists, add player to the country
            {
                temp->data.addPlayer(player);
                break;
            }
            temp = temp->next;
        }
        if (temp == NULL){ //if country does not exist, create new country and add player to the country
            Country country(countryName);
            country.addPlayer(player);
            countryList.insertNode(country);
        }
    }

    // Close the file after reading
    databaseFile.close();
}
