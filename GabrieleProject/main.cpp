//================================================================================
// WORD GAMES - BOARD MAKER PART 2
//
// GROUP 14
// MEMBERS:
//  Gabriele Rocha de Carvalho (up202302557)
//  Hannia Valentina Espinoza Reyes (up202302569)
//================================================================================

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iterator>
#include <set>
#include <algorithm>
#include <random>
#include <cctype>
//--------------------------------------------------------------------------------
//================================================================================
// COLOR CODES
//================================================================================
// TEXT COLOR
#define NO_COLOR      "\033[0m"
#define BLACK         "\033[0;30m"
#define RED           "\033[0;31m"
#define WHITE         "\033[1;37m"

// BACKGROUND COLOR
#define BLACK_B       "\033[0;40m"
#define WHITE_B       "\033[1;47m"
//--------------------------------------------------------------------------------
using namespace std;

//================================================================================
// PARTIAL DEFINITION OF CLASSES
//================================================================================

struct Cell {
    char symbol_;   // A letter or a dot (= empty cell)
    char dir_;      // Direction of the word(s) that occupy the cell: H, V, + (= both H and V)
    int playerId_;  // Player number: 1,2,3,4; 0 = no player yet
    bool isModified_;
};

class Hand {
public:
    Hand(const string& letters = "") {
        for (char letter : letters) {
            letters_.insert(letter);
        }
    }

    string getLetters() const {
        string letters;
        for (char letter : letters_) {
            letters += letter;
        }
        return letters;
    }

    void insert(const string& letters) {
        for (char letter : letters) {
            letters_.insert(letter);
        }
    }

    bool remove(char letter) {
        auto it = letters_.find(letter);
        if (it != letters_.end()) {
            letters_.erase(it);
            return true;
        }
        return false;
    }

    void clear() {
        letters_.clear();
    }

    void show() const {
        for (char letter : letters_) {
            cout << letter << ' ';
        }
        cout << endl;
    }

private:
    multiset<char> letters_;  // Automatically sorted letters
};

class Player {
public:
    Player(int id, const string& name) : id_(id), name_(name), points_(0) {}

    int getId() const { return id_; }
    string getName() const { return name_; }
    int getPoints() const { return points_; }
    Hand getHand() const { return hand_; }
    Hand& getHandReference() {
        return hand_;
    }

    void setName(const string& name) { name_ = name; }
    void addPoints(int points) { points_ += points; }

    void drawLetters(string& letters) {
        hand_.insert(letters);
    }

    void showHand() const {
        hand_.show();
    }

private:
    int id_;
    string name_;
    int points_;
    Hand hand_;
};

class Board {
public:
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
                b_ = vector<vector<Cell>>(numLins_, vector<Cell>(numCols_, { '.', '.', 0 }));
            }
            else if (line.find("BOARD :") != string::npos) {
                boardSection = true; // Indicates the start of the board layout section
            }
            else if (boardSection) {
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

    string getLetters() const {
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

    bool canPlayAt(char lin, char col) const {
        int rowIndex = lin - 'A';
        int colIndex = col - 'a';
        if (rowIndex < 0 || rowIndex >= numLins_ || colIndex < 0 || colIndex >= numCols_) {
            return false;
        }
        const Cell& cell = b_[rowIndex][colIndex];
        return cell.playerId_ == 0 && cell.symbol_ != '+';
    }

    bool playAt(int playerId, char lin, char col, char letter) {
        int rowIndex = lin - 'A';
        int colIndex = col - 'a';
        if (!canPlayAt(lin, col)) {
            return false;
        }

        Cell& cell = b_[rowIndex][colIndex];
        if (cell.symbol_ != '.' && cell.symbol_ != letter) {
            return false;
        }

        cell.symbol_ = letter; // Place the letter
        cell.playerId_ = playerId; // Mark the cell with the player's ID
        cell.isModified_ = true;
        return true;
    }

    void show() const {
        cout << "  ";  // Space for row labels
        for (int i = 0; i < numCols_; ++i) {
            cout << static_cast<char>('a' + i) << " ";
        }
        cout << endl;


        for (int i = 0; i < numLins_; ++i) {
            cout << static_cast<char>('A' + i) << " ";
            for (int j = 0; j < numCols_; ++j) {

                const Cell& cell = b_[i][j];
                if (cell.symbol_ != '.') {
                    if (cell.isModified_) {
                        cout << RED << WHITE_B << cell.symbol_ << " " << NO_COLOR;
                    }
                    else {
                        cout << BLACK << WHITE_B << cell.symbol_ << " " << NO_COLOR;
                    }
                }
                else {
                    cout << WHITE_B << WHITE_B << ' ' << " " << NO_COLOR;
                }

            }

            cout << endl;
        }
    }


private:
    vector<vector<Cell>> b_;
    const vector<Player>& players;
    int numLins_, numCols_;
    std::pair<int, int> lastPlay_;

    void initializeBoard(int rows, int cols) {
        numLins_ = rows;
        numCols_ = cols;
        b_ = vector<vector<Cell>>(rows, vector<Cell>(cols, { '.', '.', 0 }));
    }

    void parseBoardRow(const string& row, int rowIndex) {
        // Assuming the row format is like "A . . . . C . . E . . ."
        istringstream iss(row.substr(2)); // Skip the row label (e.g., 'A')
        char symbol;
        int colIndex = 0;
        while (iss >> symbol && colIndex < numCols_) {
            b_[rowIndex][colIndex].symbol_ = symbol;
            colIndex++;
        }
    }


    void placeWord(const string& position, char orientation, const string& word) {
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
        }
        else if (orientation == 'V') {
            for (size_t i = 0; i < word.length() && rowIndex + i < numLins_; ++i) {
                Cell& cell = b_[rowIndex + i][colIndex];
                // Only place the letter if the cell is empty or matches the word letter
                if (cell.symbol_ == '.' || cell.symbol_ == word[i]) {
                    cell.symbol_ = word[i];
                }
            }
        }
    }
};
class Bag {
public:
    Bag(const string& letters) : letters_(letters) {
        shuffle();
    }

    bool isEmpty() const {
        return letters_.empty();
    }

    void insert(const string& letters) {
        letters_ += letters;
        shuffle();
    }

    string remove(int numLetters) {
        string removedLetters;
        for (int i = 0; i < numLetters && !letters_.empty(); ++i) {
            removedLetters += letters_.back();
            letters_.pop_back();
        }
        return removedLetters;
    }

    void shuffle() {
        random_device rd;
        default_random_engine rng(rd());
        std::shuffle(letters_.begin(), letters_.end(), rng);
    }

private:
    string letters_;
};

void readPlayersInfo(vector<Player>& players) {
    for (int i = 0; i < players.size(); ++i) {
        cout << "Enter information for Player " << i + 1 << ": " << endl;
        cout << "Name: ";
        string name;
        cin >> name;
        players[i].setName(name);
    }
}

void distributeLettersToPlayers(vector<Player>& players, Bag& bag, int numLetters) {
    for (auto& player : players) {
        string letters = bag.remove(numLetters);
        player.drawLetters(letters);
    }
}

int main() {
    int numPlayers, numPlayerLetters;
    cout << "Number of players ? ";
    cin >> numPlayers;
    vector<Player> players;
    for (int i = 0; i < numPlayers; ++i) {
        players.emplace_back(i + 1, "");
    }

    // Read the number of letters each player will start with
    cout << "Number of players' letters ? ";
    cin >> numPlayerLetters;

    readPlayersInfo(players);
    Board board("board.txt", players);
    Bag bag(board.getLetters());
    distributeLettersToPlayers(players, bag, numPlayerLetters);

    bool gameOver = false;

    while (!gameOver) {
        board.show();
        for (auto& player : players) {
            cout << player.getName() << "'s turn. Hand: ";
            player.showHand();

            bool validMove = false;

            while (!validMove) {
                cout << "Enter your move (LcLetter), 'EXCHANGE' to change the letters, or 'PASS' to skip: ";
                string input;
                cin >> input;

                if (input == "PASS") {
                    break;  // Pula para o próximo jogador
                }

                if (input == "EXCHANGE") {
                    Hand& playerHand = player.getHandReference(); // Reference to the player's hand
                    string oldLetters = playerHand.getLetters();

                    // Remove old letters from player's hand
                    for (char letter : oldLetters) {
                        playerHand.remove(letter);
                    }

                    // Debugging: Check if hand is empty
                    if (!playerHand.getLetters().empty()) {
                        cerr << "Error: Hand not empty after removal." << endl;
                    }

                    string newLetters = bag.remove(numPlayerLetters);
                    playerHand.insert(newLetters); // Insert new letters

                    cout << player.getName() << "'s turn. Hand: ";
                    player.showHand();
                    continue;
                }

                if (input.length() == 3 && isalpha(input[0]) && isalpha(input[1]) && isalpha(input[2])) {
                    char row = input[0];
                    char column = input[1];
                    char letter = input[2];

                    if (board.playAt(player.getId(), row, column, letter)) {
                        bool removed = player.getHand().remove(letter);
                        if (!removed) {
                            cerr << "Warning: Letter " << letter << " not found in hand." << endl;
                        }
                        cout << "You have chosen the letter: " << letter << endl;

                        string newLetters = bag.remove(1);
                        player.drawLetters(newLetters);
                        board.show();
                        validMove = true;
                    }
                    else {
                        cout << "Invalid move. Try again." << endl;
                    }
                } else {
                    cout << "Invalid input format. Please enter line, column, and letter (e.g., AaB)." << endl;
                }
            }
        }

    }

    cout << "Game over!" << endl;
    return 0;
}