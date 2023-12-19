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
        bool boardSection = false;
        while (getline(file, line)) {
            if (line.find("BOARD SIZE :") != string::npos) {
                // Parse board size and initialize dimensions
                istringstream iss(line.substr(12)); // Extract size part
                iss >> numLins_ >> line >> numCols_; // line is used to skip 'x'
                b_ = vector<vector<Cell>>(numLins_, vector<Cell>(numCols_, {'.', '.', 0}));
            } else if (line.find("BOARD :") != string::npos) {
                boardSection = true; // Indicates the start of the board layout section
            } else if (boardSection) {
                if (line.find("WORDS :") != string::npos) {
                    break; // End of the board layout section, start of the words section
                }
                if (!line.empty() && isalpha(line[0])) {
                    parseBoardRow(line, line[0] - 'A'); // Parse each row of the board
                }
            }
        }

        // Parse and place words
        while (getline(file, line)) {
            if (!line.empty()) {
                istringstream iss(line);
                string position, word;
                char orientation;
                iss >> position >> orientation >> word;
                placeWord(position, orientation, word);
            }
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
    void placeWord(const string& position, char orientation, const string& word);
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
    // Assuming the row format is like "A . . . . C . . E . . ."
    istringstream iss(row.substr(2)); // Skip the row label (e.g., 'A')
    char symbol;
    int colIndex = 0;
    while (iss >> symbol && colIndex < numCols_) {
        b_[rowIndex][colIndex].symbol_ = symbol;
        colIndex++;
    }
}


void Board::placeWord(const string& position, char orientation, const string& word) {
    int rowIndex = position[0] - 'A'; // Convert row letter to index
    int colIndex = tolower(position[1]) - 'a'; // Convert column letter to index

    if (orientation == 'H') {
        for (size_t i = 0; i < word.length() && colIndex + i < numCols_; ++i) {
            Cell& cell = b_[rowIndex][colIndex + i];
            // Only place the letter if the cell is empty or matches the word letter
            if (cell.symbol_ == '.' || cell.symbol_ == word[i]) {
                cell.symbol_ = word[i];
            }
        }
    } else if (orientation == 'V') {
        for (size_t i = 0; i < word.length() && rowIndex + i < numLins_; ++i) {
            Cell& cell = b_[rowIndex + i][colIndex];
            // Only place the letter if the cell is empty or matches the word letter
            if (cell.symbol_ == '.' || cell.symbol_ == word[i]) {
                cell.symbol_ = word[i];
            }
        }
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
    // Display column headers
    cout << "  ";  // Extra space for row labels alignment
    for (int col = 0; col < numCols_; ++col) {
        cout << char('a' + col) << ' ';
    }
    cout << endl;

    // Display the board with row labels
    for (int row = 0; row < numLins_; ++row) {
        cout << char('A' + row) << ' ';  // Row label
        for (int col = 0; col < numCols_; ++col) {
            cout << b_[row][col].symbol_ << ' ';
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
int main() {
    int numPlayers, numPlayerLetters;

    // Read the number of players
    cout << "Number of players ? ";
    cin >> numPlayers;

    // Initialize the vector of players
    vector<Player> players(numPlayers);

    // Read the players' information
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

    // Show initial board state
    board.show();

    // Game loop
    bool gameOver = false;
    while (!gameOver) {
        for (int i = 0; i < numPlayers && !gameOver; ++i) {
            cout << "Player " << players[i].getName() << "'s turn. Enter your move: " << endl;

            // Player move input: row (letter), column (letter), and letter to play
            char row, col, letter;
            cout << "Enter row (A-K): ";
            cin >> row;

            // Player move input: column (letter)
            cout << "Enter column (a-k): ";
            cin >> col;

            // Player move input: letter to play
            cout << "Enter letter to play: ";
            cin >> letter;

            // Convert column from letter to index ('a' -> 0, 'b' -> 1, ...)
            int colIndex = tolower(col) - 'a';

            // Make a move
            if (!board.playAt(i + 1, row, colIndex, letter)) {
                cout << "Invalid move!" << endl;
                continue; // Skip to the next player if the move is invalid
            }

            board.show(); // Show the board after each move

            // Implement your game-over condition here
            // gameOver = checkIfGameOver();
        }
    }

    cout << "Game over! Final board state:" << endl;
    board.show();


    return 0;
}
