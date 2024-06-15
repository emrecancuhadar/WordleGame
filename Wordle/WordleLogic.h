#ifndef WORDLELOGIC_H
#define WORDLELOGIC_H

#include <QObject>
#include <QString>
#include <QVector>
#include <QRandomGenerator>

// The WordleLogic class handles the game logic for a simple Wordle-like game
class WordleLogic : public QObject {
    Q_OBJECT
public:
    explicit WordleLogic(QObject *parent = nullptr); // Constructor
    Q_INVOKABLE void evaluateGuess(const QString &guess); // Processes user's guess and emits feedback

public slots:
    void initializeGame(); // Sets up or resets the game to start

signals:
    void guessEvaluated(QString feedback); // Signal to emit feedback on user's guess
    void gameWon(); // Signal to indicate the game is won
    void gameLost(); // Signal to indicate the game is lost
    void invalidWordEntered(); // Signal to indicate an invalid word was entered
    void clearInvalidWordWarning(); // Signal to clear invalid word warning

private:
    QString wordOfTheDay; // Stores the current word of the day
    QVector<QString> validWords; // List of valid words for the game
    int attemptCount; // Counter for the number of attempts made
    bool gameOver; // Indicates if the game is over
    void initializeWordList(); // Initializes the list of valid words
    QString generateFeedback(const QString &guess); // Generates feedback based on the guess compared to the word of the day
    void checkGameOver(const QString &feedback); // Checks if the game is over
};

#endif
