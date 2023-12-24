#include <bits/stdc++.h>
using namespace std;
#define width 23 // make all strings take up the same space

class Country
{
public:
    LinkedList<Player> playerList; //linked list of players in the country
    
    Country()
    {
        countryName = "";
    }
    Country(string name)
    {
        countryName = name;
    }

    //searches for player in the country
    Node<Player> *searchPlayer(string name)
    {
        Node<Player> *front = playerList.head;
        Node<Player> *back = playerList.tail;
        bool foundFront = false;
        bool foundBack = false;
        while (front != back)
        {
            foundFront = stringCompare(front->data.getPlayerName(), name);
            foundBack = stringCompare(back->data.getPlayerName(), name);
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

    //adds player to the country
    void addPlayer(Player p)
    {
        //looks for duplicate players
        Node<Player> *temp = searchPlayer(p.getPlayerName());
        if (temp != NULL)
        {
            cout << "\nPlayer already exists!" << endl;
            cout << "\nWould you like to update player details? (y/n): ";
            char choice;
            cin >> choice;
            choice = tolower(choice);
            if (choice == 'y')
            printBorder();
            printHeader();
            temp->data.getPlayerDetails();
            printBorder();
            updatePlayer(p.getPlayerName());
            return;
        }
        playerList.insertNode(p);
    }

    //deletes player from the country
    void deletePlayer(string name)
    {
        Node<Player> *temp = searchPlayer(name);

        if (temp == NULL)
        {
            cout <<endl;
            cout << "\nERROR: Player not found!" << endl;
            return;
        }

        if (temp == playerList.head && temp == playerList.tail)
        {
            playerList.head = NULL;
            playerList.tail = NULL;
            delete temp;
        }
        else if (temp == playerList.head)
        {
            playerList.head = temp->next;
            delete temp;

        }
        else if (temp == playerList.tail)
        {
            playerList.tail = temp->prev;
            temp ->prev->next = NULL;
            delete temp;
        }
        else
        {
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            delete temp;
        }
        return;
    }


    //prints player list
    void displayPlayerList()
    {
        printBorder();
        cout << right << setw((int)(width*5)/2) << countryName << " Squad" << endl;
        printBorder();
        printHeader();
        printBorder();
        Node<Player> *temp = playerList.head;
        while (temp != NULL)
        {
            temp->data.getPlayerDetails();
            temp = temp->next;
        }
        printBorder();
    }

    //updates player details
    Player updatePlayer(string name)
    {   
        Node<Player> *temp = searchPlayer(name);
        Player p;
        if (temp == NULL)
        {
            cout <<endl;
            cout << "\nERROR: Player not found!" << endl;
            return p;
        }
        temp->data.updatePlayer();
         //checks if invalid country is entered during update, returns empty player if player not deleted
        if(temp->data.getPlayerCountry() != countryName){
            p = temp->data;
            deletePlayer(name);
        }
        return p;
    }
    string getCountryName()
    {
        return countryName;
    }
    void setCountryName(string name)
    {
        countryName = name;
    }

private:
    string countryName;
};
