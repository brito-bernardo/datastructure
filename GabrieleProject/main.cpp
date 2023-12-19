#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iterator>
#include <set>
#include <algorithm>
#include <random>
//--------------------------------------------------------------------------------
// You can add additional libraries if you need them ...
//--------------------------------------------------------------------------------

//--------------------------------------------------------------------------------
using namespace std;


//================================================================================
// PARTIAL DEFINITION OF CLASSES
//================================================================================
struct Cell       // represents a cell of the Board
{
    char symbol_;   // a letter or a dot (= empty cell)
    char dir_;      // direction of the word(s) that ocupy the cell: H, V, + (= both H and V)
    int playerId_;  // player number: 1,2,3 or 4 ; 0 = no player, yet
};
class Hand {
public:
    Hand(const string& letters = "");
    string getLetters() const;            // returns all letters in hand
    void insert(const string& letters);   // letters = letters removed from the bag
    bool remove(char letter);             // letter = letter to be put on board
    // returns true if letter exists in hand and was removed
    void show() const;   // other methods ...?
private:
    multiset<char> letters_;              // letters are automatically sorted :-)
};
class Player
{
public:
    Player(int id, const string& name = "");
    Player() : id_(0), name_(""), points_(0) {
        // Initialize hand with an empty set of letters
        hand_ = Hand(); // Assuming Hand has a default constructor
    }

    // Constructor with parameters (if needed)


    // get() methods for all attributes
    int getId() const;
    string getName() const;
    int getPoints() const;
    Hand getHand()
    const;    // set() methods for all attributes
    void setId(int id);
    void setName(const string& name);
    void setPoints(int points);
    void setHand(const Hand &hand);
    void addPoints(int points);
    void insertHand(const string& letters);   // letters = letters to be inserted
    string removeHand(const string& letters); // letters = letters to be removed
    // other methods ...?
private:
    int id_;
    string name_;
    int points_;
    Hand hand_;
    // other attributes ...?
};
//--------------------------------------------------------------------------------
class Board {
public:
    // Constructor to import the board from file 'fileName'
    Board(const string& fileName, const vector<Player>& playersRef)
            : players(playersRef) {
        ifstream file(fileName);
        if (!file.is_open()) {
            throw runtime_error("Unable to open file: " + fileName);
        }

        string line;
        while (getline(file, line)) {
            if (line.find("BOARD SIZE :") != string::npos) {
                // Parse board size and initialize board dimensions
                istringstream iss(line);
                string temp;
                int rows, cols;
                getline(iss, temp, ':'); // Skip "BOARD SIZE :"
                iss >> rows >> temp >> cols; // temp is 'x'
                initializeBoard(rows, cols);
            } else if (line.find("BOARD :") != string::npos) {
                // Parse board layout
                for (int i = 0; i < numLins_ && getline(file, line); ++i) {
                    parseBoardRow(line, i);
                }
            }
            // Additional parsing for the words section if needed
        }
    }

    // Method to get all letters in board (useful for building the bag)
    string getLetters() const;

    // Method to check if a play can be made at a certain position
    bool canPlayAt(char lin, char col) const;

    // Method to show the board
    void show() const;

    // Method to play at a given position
    bool playAt(int playerId, char lin, char col, char letter);

    // Other methods ...?

private:
    vector<vector<Cell>> b_;       // Board represented as a 2D vector of Cells
    const vector<Player>& players; // Reference to the vector of players
    int numLins_;                  // Number of lines in the board
    int numCols_;                  // Number of columns in the board
    int numWords_;
    void initializeBoard(int rows, int cols);
    void parseBoardRow(const string& row, int rowIndex);// Total number of points for ending the game
    // Other attributes ...?
};

//================================================================================

class Bag
{
public:
    Bag(const string& letters);         // letters = all letters on the board
    bool isEmpty() const;
    void insert(const string& letters); // letters = letters to be inserted by a player
    string remove(int numLetters);      // letters = letters to be removed by a player
    // returns letter(s) effectively removed
    // or empty string, if there are no letters in bag
    void shuffle();   // other methods ...?
private:
    string letters_;
};

//================================================================================


//================================================================================


//================================================================================
// Class methods - Board

void Board::initializeBoard(int rows, int cols) {
    numLins_ = rows;
    numCols_ = cols;
    b_ = vector<vector<Cell>>(rows, vector<Cell>(cols, {'.', '.', 0}));
}

void Board::parseBoardRow(const string& row, int rowIndex) {
    istringstream iss(row);
    string temp;
    getline(iss, temp, ':'); // Skip "BOARD :"
    for (int i = 0; i < numCols_ && getline(iss, temp, ' '); ++i) {
        Cell& cell = b_[rowIndex][i];
        cell.symbol_ = temp[0];
        cell.dir_ = temp[1];
    }
}



string Board::getLetters() const {
    string letters;

    for (const auto& row : b_) {
        for (const auto& cell : row) {
            if (cell.symbol_ != '.') {
                letters += cell.symbol_;
            }
        }
    }
    return letters;
}

bool Board::canPlayAt(char lin, char col)  const {
    // Verificar se as coordenadas estão dentro dos limites do tabuleiro
    if (lin < 1 || lin >= b_.size() || col < 1 || col >= b_[lin].size()) {
        return false;
    }

    // Verificar se a célula está vazia (não pertence a nenhum jogador) e não está bloqueada
    const Cell& cell = b_[lin][col];
    return cell.playerId_ == 0 && cell.symbol_ != '+';
}

bool Board::playAt(int playerId, char lin, char col, char letter) {
    int rowIndex = lin - 'A'; // Convert character to index
    int colIndex = col - '1';
    if (lin < 'A' || lin >= 'A' + b_.size() || col < '1' || col >= '1' + b_[0].size()) {
        return false;
    }


    // Access the cell
    Cell& cell = b_[rowIndex][colIndex];

    // Check if the cell is empty (not owned by any player) and not blocked
    if (cell.playerId_ != 0 || cell.symbol_ == '+') {
        return false;
    }

    // Check if the letter matches the cell's symbol
    // Assuming the cell's symbol is either the letter that should be played or a dot ('.') for empty
    if (cell.symbol_ != '.' && cell.symbol_ != letter) {
        return false;
    }

    // Assuming you have a way to access the player's hand (like a global vector of players)
    // If the player does not have the letter, return false
    // This check should ideally happen before modifying the board
    if (!players[playerId - 1].getHand().remove(letter)) {
        return false;
    }

    // Place the letter and update the player ID
    cell.symbol_ = letter;
    cell.playerId_ = playerId;

    return true;

}

void Board::show() const {
    for (const auto& row : b_) {
        for (const auto& cell : row) {
            cout << cell.symbol_ << ' ';
        }
        cout << endl;
    }
}

//================================================================================
// Class methods - Bag

Bag::Bag(const string& letters) : letters_(letters) {
    for (char c : letters) {
        if (!isalpha(c)) {
            throw std::invalid_argument("Bag contains invalid characters");
        }
    }
}

bool Bag::isEmpty() const {
    return letters_.empty();
}

void Bag::insert(const string& letters) {
    letters_ += letters;
}

string Bag::remove(int numLetters) {
    string letters;

    for (int i = 0; i < numLetters && !letters_.empty(); ++i) {
        letters += letters_.back();
        letters_.pop_back();
    }

    return letters;
}

void Bag::shuffle() {
    std::random_device rd;  // Non-deterministic random number generator
    std::default_random_engine rng(rd()); // Use rd to seed the random number generator

    std::shuffle(letters_.begin(), letters_.end(), rng);
}

//================================================================================
// Class methods - Hand

Hand::Hand(const string& letters) {
    for (char letter : letters) {
        letters_.insert(letter);
    }
}

string Hand::getLetters() const {
    string letters;

    for (char letter : letters_) {
        letters += letter;
    }

    return letters;
}

void Hand::insert(const string& letters) {
    for (char letter : letters) {
        letters_.insert(letter);
    }
}

bool Hand::remove(char letter) {
    auto it = letters_.find(letter);

    if (it != letters_.end()) {
        letters_.erase(it);
        return true;
    }

    return false;
}

void Hand::show() const {
    for (char letter : letters_) {
        cout << letter << ' ';
    }
    cout << endl;
}

//================================================================================
// Class methods - Player

Player::Player(int id, const string& name) : id_(id), name_(name), points_(0) {


}

int Player::getId() const {
    return id_;
}

string Player::getName() const {
    return name_;
}

int Player::getPoints() const {
    return points_;
}

Hand Player::getHand() const {
    return hand_;
}

void Player::setId(int id) {
    id_ = id;
}

void Player::setName(const string& name) {
    name_ = name;
}

void Player::setPoints(int points) {
    points_ = points;
}

void Player::setHand(const Hand& hand) {
    hand_ = hand;
}

void Player::addPoints(int points) {
    points_ += points;
}

void Player::insertHand(const string& letters) {
    hand_.insert(letters);
}


//================================================================================

void readPlayersInfo(vector<Player>& players) {
    for (int i = 0; i < players.size(); ++i) {
        cout << "Enter information for Player " << i + 1 << ":" << endl;

        // You can modify the prompts based on the actual attributes of the Player class
        cout << "Name: ";
        string name;
        cin >> name;

        // Assuming you have appropriate methods in the Player class to set attributes
        players[i].setName(name);
        cout << endl;
    }
}

void distributeLettersToPlayers(std::vector<Player>& players, int numPlayerLetters, Bag& bag) {
    for (auto& player : players) {
        // Remove um número especificado de letras da sacola
        std::string lettersDrawn = bag.remove(numPlayerLetters);

        // Insere as letras na mão do jogador
        player.insertHand(lettersDrawn);
    }
}


//================================================================================
//================================================================================
//================================================================================
int main()
{
    int numPlayers, numPlayerLetters;

    // First, read the number of players
    cout << "Number of players ? ";
    cin >> numPlayers;

    // Initialize the vector of players now that we have the number
    vector<Player> players(numPlayers);

    // Now read the players' information
    readPlayersInfo(players);

    // Create the Board and Bag objects
    Board board("board.txt", players);
    Bag bag(board.getLetters());
    bag.shuffle();

    // Read the number of letters each player will start with
    cout << "Number of players' letters ? ";
    cin >> numPlayerLetters;

    // Distribute letters to players
    distributeLettersToPlayers(players, numPlayerLetters, bag);

    board.show();

    // Game loop
    bool gameOver = false;
    while (!gameOver) {
        for (int i = 0; i < numPlayers && !gameOver; ++i) {
            cout << "Player " << players[i].getName() << "'s turn. Enter your move: " << endl;

            // Example player move input:
            // Ask for row, column, and letter
            char row, col, letter;
            cout << "Enter row (A-K), column (1-11), and letter: ";
            cin >> row >> col >> letter;

            // Implement move validation and update logic here
            // For now, let's just make a simple move
            if (!board.playAt(i + 1, row, col, letter)) {
                cout << "Invalid move!" << endl;
                continue; // Skip to the next player if the move is invalid
            }

            board.show(); // Show the board after each move

            // Simple game over condition (e.g., after one round of turns)
            if (i == numPlayers - 1) {
                gameOver = true;
            }
        }
    }

    cout << "Game over! Final board state:" << endl;
    board.show();
    return 0;
}