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
// DEFINITION OF CLASSES
//================================================================================

struct Cell {
    char symbol_;   // A letter or a dot (= empty cell)
    char dir_;      // Direction of the word(s) that occupy the cell: H, V, + (= both H and V)
    int playerId_;  // Player number: 1,2,3,4; 0 = no player yet
    bool isModified_;
};

class Hand {
public:
    Hand(const string& letters = "");

    string getLetters() const;

    void insert(const string& letters);

    bool remove(char letter);

    void clear();

    void show() const;

private:
    multiset<char> letters_;  // Automatically sorted letters
};

class Player {
public:
    Player(int id, const string& name);

    int getId() const;

    string getName() const;

    int getPoints() const;

    Hand getHand() const;

    Hand& getHandReference();

    void setName(const string& name);

    void addPoints(int points);

    void drawLetters(string& letters);

    void showHand() const;

    int getExchangeCount() const;

    void incrementExchangeCount();

private:
    int exchangeCount_;
    int id_;
    string name_;
    int points_;
    Hand hand_;
};

class Board {
public:
    Board(const string& fileName, vector<Player>& playersRef);

    string getLetters() const;

    bool canPlayAt(char lin, char col) const;

    bool playAt(int playerId, char lin, char col, char letter);

    bool completesNewWord(int rowIndex, int colIndex, char direction);
    bool completesNewWordInLine(int fixed, int var, int start, int end, bool isHorizontal);

    int calculateScoreForPlacement(int rowIndex, int colIndex);

    void show() const;

    bool isBoardFullyCovered() const;

private:
    vector<vector<Cell>> b_;
    vector<Player>& players;
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
    Bag(const string& letters);

    bool isEmpty() const;

    void insert(const string& letters);

    string remove(int numLetters);

    void shuffle();

private:
    string letters_;
};

//================================================================================
// DEFINIITION OF METHODS/FUNCTIONS
//================================================================================

//--------------------------------------------------------------------------------
// HAND

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
    letter = toupper(letter);
    auto it = letters_.find(letter);
    if (it != letters_.end()) {
        letters_.erase(it);
        return true;
    }
    return false;
}

void Hand::clear() {
    letters_.clear();
}

void Hand::show() const {
    for (char letter : letters_) {
        cout << letter << ' ';
    }
    cout << endl;
}

//--------------------------------------------------------------------------------
// PLAYERS

Player::Player(int id, const string& name) : id_(id), name_(name), points_(0), exchangeCount_(0) {}

int Player::getId() const { return id_; }

string Player::getName() const { return name_; }

int Player::getPoints() const { return points_; }

Hand Player::getHand() const { return hand_; }

Hand& Player::getHandReference() {
    return hand_;
}

void Player::setName(const string& name) { name_ = name; }

void Player::addPoints(int points) { points_ += points; }

void Player::drawLetters(string& letters) {
    hand_.insert(letters);
}

void Player::showHand() const {
    hand_.show();
}

int Player::getExchangeCount() const {
    return exchangeCount_;
}

void Player::incrementExchangeCount() {
    ++exchangeCount_;
}

//--------------------------------------------------------------------------------
// BOARD

Board::Board(const string& fileName, vector<Player>& playersRef)
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

bool Board::canPlayAt(char lin, char col) const {
    int rowIndex = lin - 'A';
    int colIndex = col - 'a';
    if (rowIndex < 0 || rowIndex >= numLins_ || colIndex < 0 || colIndex >= numCols_) {
        return false;
    }
    const Cell& cell = b_[rowIndex][colIndex];
    return cell.symbol_ != '.';  // Alteração aqui
}

bool Board::playAt(int playerId, char lin, char col, char letter) {
    int rowIndex = lin - 'A';
    int colIndex = col - 'a';
    char let = toupper(letter);

    if (!canPlayAt(lin, col)) {
        return false;
    }

    Cell& cell = b_[rowIndex][colIndex];
    Cell& prevCell = (colIndex > 0) ? b_[rowIndex][colIndex - 1] : cell;
    Cell& nextCell = (colIndex < numCols_ - 1) ? b_[rowIndex][colIndex + 1] : cell;
    Cell& aboveCell = (rowIndex > 0) ? b_[rowIndex - 1][colIndex] : cell;
    Cell& belowCell = (rowIndex < numLins_ - 1) ? b_[rowIndex + 1][colIndex] : cell;

    // Check if the cell is at the beginning of a word horizontally or vertically
    bool isStartOfWordH = (colIndex == 0) || (colIndex > 0 && prevCell.symbol_ == '.' && nextCell.symbol_ != '.');
    bool isStartOfWordV = (rowIndex == 0) || (rowIndex > 0 && aboveCell.symbol_ == '.' && belowCell.symbol_ != '.');
    bool isEndOfWordH = (colIndex == numCols_) || (colIndex < numCols_ && nextCell.symbol_ == '.' && prevCell.symbol_ != '.');
    bool isEndOfWordV = (rowIndex == numLins_) || (rowIndex < numLins_ && belowCell.symbol_ == '.' && aboveCell.symbol_ != '.');

    cell.dir_ = '+';

    // Check if it's a horizontal cell
    if (isStartOfWordH || isEndOfWordH || (nextCell.symbol_ != '.' && prevCell.symbol_ != '.')) {
        cell.dir_ = 'H';
    }

    // Check if it's a vertical cell
    if (isStartOfWordV || isEndOfWordV || (aboveCell.symbol_ != '.' && belowCell.symbol_ != '.')) {
        cell.dir_ = 'V';
    }

    if ((isStartOfWordV || isEndOfWordV || (aboveCell.symbol_ != '.' && belowCell.symbol_ != '.')) && (isStartOfWordH || isEndOfWordH || (nextCell.symbol_ != '.' && prevCell.symbol_ != '.'))) {
        cell.dir_ = '+';
    }
    cout << "Debug: " << cell.dir_ << endl;


    // Check if the direction is V and the cell is not at the top
    if (cell.dir_ == 'V' && rowIndex > 0) {
        if (!aboveCell.isModified_ && aboveCell.symbol_ != '.') {
            return false;
        }
    }

    // Check if the direction is H and the cell is not at the leftmost
    if (cell.dir_ == 'H' && colIndex > 0) {
        if (!prevCell.isModified_ && prevCell.symbol_ != '.') {
            return false;
        }
    }

    if (cell.dir_ == '+') {
        if (!prevCell.isModified_ && prevCell.symbol_ != '.' && !aboveCell.isModified_ && aboveCell.symbol_ != '.') {
            return false;
        }
    }

    if (cell.symbol_ != '.' && cell.symbol_ != let) {
        return false;  // Cell already contains a different letter
    }

    // Place the letter
    cell.symbol_ = let;
    cell.playerId_ = playerId;
    cell.isModified_ = true;

    int score = calculateScoreForPlacement(rowIndex, colIndex);
    players[playerId - 1].addPoints(score); // Assuming player IDs start from 1

    if (score > 0) {
        cout << "Great! You've completed a word and earned " << score << " points!" << endl;
    }
    else {
        cout << "Letter placed, but no word completed." << endl;
    }

    return true;
}

bool Board::completesNewWord(int rowIndex, int colIndex, char direction) {
    bool wordStarted = false, wordEnded = false;
    int i, j;

    if (direction == 'H') {
        i = colIndex - 1;
        j = colIndex + 1;
    } else { // direction == 'V'
        i = rowIndex - 1;
        j = rowIndex + 1;
    }

    // Check backward to the start of the word
    while (i >= 0) {
        Cell& cell = (direction == 'H') ? b_[rowIndex][i] : b_[i][colIndex];
        if (cell.symbol_ == '.') break;
        if (!cell.isModified_) return false; // Found an unmodified cell
        wordStarted = true;
        i--;
    }

    // Check forward to the end of the word
    int limit = (direction == 'H') ? numCols_ : numLins_;
    while (j < limit) {
        Cell& cell = (direction == 'H') ? b_[rowIndex][j] : b_[j][colIndex];
        if (cell.symbol_ == '.') {
            wordEnded = true;
            break;
        }
        if (!cell.isModified_) return false; // Found an unmodified cell
        j++;
    }

    // The word is completed if it has started and ended, and the placed letter is the first modification
    return wordStarted && wordEnded;
}



int Board::calculateScoreForPlacement(int rowIndex, int colIndex) {
    int score = 0;

    // Check if the placed letter completes a new word horizontally
    if (completesNewWord(rowIndex, colIndex, 'H')) {
        score += 1;
    }

    // Check if the placed letter completes a new word vertically
    if (completesNewWord(rowIndex, colIndex, 'V')) {
        score += 1;
    }

    return score;
}

void Board::show() const {
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

bool Board::isBoardFullyCovered() const {
    for (const auto& row : b_) {
        for (const auto& cell : row) {
            if (cell.symbol_ != '.' && !cell.isModified_) {
                return false;  // At least one letter is not covered
            }
        }
    }
    return true;  // All letters are covered
}

//--------------------------------------------------------------------------------
// BAG

Bag::Bag(const string& letters) : letters_(letters) {
    shuffle();
}

bool Bag::isEmpty() const {
    return letters_.empty();
}

void Bag::insert(const string& letters) {
    letters_ += letters;
    shuffle();
}

string Bag::remove(int numLetters) {
    string removedLetters;
    for (int i = 0; i < numLetters && !letters_.empty(); ++i) {
        removedLetters += letters_.back();
        letters_.pop_back();
    }
    return removedLetters;
}

void Bag::shuffle() {
    random_device rd;
    default_random_engine rng(rd());
    std::shuffle(letters_.begin(), letters_.end(), rng);
}

//--------------------------------------------------------------------------------
// FUNCTIONS

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

//================================================================================
// MAIN
//================================================================================

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
            int turn = 0;
            while (turn < 2) {
                turn = turn + 1;
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
                        if (bag.isEmpty()) {
                            cout << "Letter bag is empty. Unable to exchange letters." << endl;
                            continue;
                        }

                        if (player.getExchangeCount() >= 10) {
                            cout << "You can only exchange letters once per turn." << endl;
                            continue;
                        }

                        Hand& playerHand = player.getHandReference(); // Reference to the player's hand
                        string oldLetters = playerHand.getLetters();

                        bag.insert(oldLetters);

                        bag.shuffle();

                        // Remove old letters from player's hand
                        for (char letter : oldLetters) {
                            playerHand.remove(letter);
                        }

                        string newLetters = bag.remove(numPlayerLetters);
                        playerHand.insert(newLetters); // Insert new letters

                        cout << player.getName() << "'s turn. This is your new hand: ";
                        player.showHand();

                        // Increment the exchange count
                        player.incrementExchangeCount();

                        continue;
                    }


                    if (input.length() != 3 || !isalpha(input[0]) || !isalpha(input[1]) || !isalpha(input[2])) {
                        cout << "Invalid input format. Please enter line, column, and letter (AaB)." << endl;
                        continue;  // Volta para o início do loop interno
                    }

                    char row = input[0];
                    char column = input[1];
                    char letter = input[2];

                    if (board.playAt(player.getId(), row, column, letter)) {
                        Hand& playerHand = player.getHandReference();
                        playerHand.remove(letter);

                        string newLetters = bag.remove(1);
                        player.drawLetters(newLetters);

                        board.show();
                        validMove = true;
                    }
                    else {
                        cout << "Invalid move. Try again." << endl;
                    }

                    cout << "Current Scores:" << endl;
                    for (const auto& p : players) {
                        cout << p.getName() << ": " << p.getPoints() << " points" << endl;
                    }
                }
            }
            if (board.isBoardFullyCovered() == true) {
                gameOver = true;
            }

        }

    }
    if (gameOver) {
        cout << "Game over! Final Scores:" << endl;

        int highestScore = 0;
        string winner;
        for (const auto& player : players) {
            cout << player.getName() << ": " << player.getPoints() << " points" << endl;
            if (player.getPoints() > highestScore) {
                highestScore = player.getPoints();
                winner = player.getName();
            }
        }

        // Display the winner
        if (!winner.empty()) {
            cout << "The winner is: " << winner << " with " << highestScore << " points!" << endl;
        } else {
            cout << "It's a tie!" << endl;
        }
    }

    return 0;
}