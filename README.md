# ICC Cricket World Cup Squads

This is a C++ project to manage and view cricket World Cup squad details.

## Features

- Add, update, and remove players from country squads
- Search for players by name
- View all country squads and player details
- Data stored in liked lists by country
- Player info: name, age, country, role, batting style

## Usage

The `main.cpp` file handles the user interface and menu:

- Display all countries and players
- Search for a player 
- Display and edit specific country squad
- Add/remove players
- Update player details

The core classes are:

- `Player`: Holds details about each player
- `Country`: Contains a linked list of players in the squad
- `LinkedList`: Template linked list to store players

Sample player data is provided in `database.txt`, which can be loaded on startup.

## Installation

This uses standard C++ with no external dependencies. To compile:

```bash
g++ main.cpp Country.cpp Player.cpp LinkedList.cpp -o worldcup
```

## Contributing
Pull requests are welcome. Some ideas for improvement:
- Add additional player statistics
- Create a GUI version
- Allow importing player data from CSV/databases
