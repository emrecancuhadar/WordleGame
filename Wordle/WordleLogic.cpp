#include "WordleLogic.h"
#include <QTimer>  // Include QTimer header

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
    if (!validWords.contains(guess)) {
        emit invalidWordEntered(); // Emit signal for invalid word
        QTimer::singleShot(2000, this, &WordleLogic::clearInvalidWordWarning); // Clear warning after 2 seconds
        return;
    }

    QString feedback = generateFeedback(guess);
    emit guessEvaluated(feedback); // Emit the feedback for the guess

    checkGameOver(feedback); // Check if the game is over
}

// Generates feedback for each letter in the guess
QString WordleLogic::generateFeedback(const QString &guess) {
    QString feedback;
    QVector<bool> used(5, false); // Track used letters in the word of the day

    // First pass: Check for correct letters in the correct position
    for (int i = 0; i < guess.length(); i++) {
        if (guess[i] == wordOfTheDay[i]) {
            feedback += "G"; // Green for correct position
            used[i] = true; // Mark this position as used
        } else {
            feedback += " "; // Placeholder for second pass
        }
    }

    // Second pass: Check for correct letters in the wrong position
    for (int i = 0; i < guess.length(); i++) {
        if (feedback[i] != 'G') {
            bool found = false;
            for (int j = 0; j < wordOfTheDay.length(); j++) {
                if (!used[j] && guess[i] == wordOfTheDay[j]) {
                    feedback[i] = 'Y'; // Yellow for correct letter in wrong position
                    used[j] = true; // Mark this position as used
                    found = true;
                    break;
                }
            }
            if (!found) {
                feedback[i] = 'B'; // Black for incorrect letter
            }
        }
    }

    return feedback;
}

// Resets the game by selecting a new word of the day
void WordleLogic::initializeGame() {
    wordOfTheDay = validWords.at(QRandomGenerator::global()->bounded(validWords.size()));
    attemptCount = 0;
    gameOver = false;
}

void WordleLogic::checkGameOver(const QString &feedback) {
    attemptCount++;
    if (feedback == "GGGGG") {
        gameOver = true;
        emit gameWon(); // Emit signal for winning the game
    } else if (attemptCount >= 6) {
        gameOver = true;
        emit gameLost(); // Emit signal for losing the game
    }
}
