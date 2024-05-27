#include "WordleLogic.h"

// Constructor implementation
WordleLogic::WordleLogic(QObject *parent) : QObject(parent) {
    initializeWordList();
    initializeGame(); // Initialize game settings on start
}

// Initializes the list of valid words for the game
void WordleLogic::initializeWordList() {
    validWords << "stars" << "apple" << "berry" << "loily" << "exits"
               << "slate" << "crate" << "blaze" << "ghost" << "flame" << "stone"
               << "light" << "proud" << "quilt";
}

// Processes the user's guess and emits a feedback signal
void WordleLogic::evaluateGuess(const QString &guess) {
    QString feedback = generateFeedback(guess);
    emit guessEvaluated(feedback); // Emit the feedback for the guess
}

// Generates feedback for each letter in the guess
QString WordleLogic::generateFeedback(const QString &guess) {
    QString feedback;
    for (int i = 0; i < guess.length(); i++) {
        if (guess[i] == wordOfTheDay[i]) {
            feedback += "G"; // Green for correct position
        } else if (wordOfTheDay.contains(guess[i])) {
            feedback += "Y"; // Yellow for correct letter in wrong position
        } else {
            feedback += "B"; // Black for incorrect letter
        }
    }
    return feedback;
}

// Resets the game by selecting a new word of the day
void WordleLogic::initializeGame() {
    wordOfTheDay = validWords.at(QRandomGenerator::global()->bounded(validWords.size()));
}
