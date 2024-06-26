import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.3

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: "Wordle Game"

    Rectangle {
        anchors.fill: parent
        color: "white"

        Column {
            anchors.centerIn: parent
            spacing: 20

            TextField {
                id: wordInput
                width: parent.width * 0.8
                height: 40
                font.pixelSize: 20
                placeholderText: "Enter a 5-letter word"
                horizontalAlignment: Text.AlignHCenter

                onTextChanged: {
                    if (text.length > 5) {
                        text = text.substring(0, 5);
                    }
                }
                onAccepted: {
                    if (!gameOver) {
                        if (text.length === 5) {
                            wordleLogic.evaluateGuess(text);
                            text = ""; // Clear the input field after submitting
                        }
                    }
                }
            }

            Grid {
                id: gameGrid
                rows: 6
                columns: 5
                spacing: 10

                Repeater {
                    model: 30 // for a 6x5 grid
                    Rectangle {
                        width: 40
                        height: 40
                        color: "lightgrey"
                        border.color: "black"
                        radius: 5

                        Text {
                            anchors.centerIn: parent
                            font.pixelSize: 24
                        }
                    }
                }
            }

            Text {
                id: statusMessage
                width: parent.width * 0.8
                height: 40
                font.pixelSize: 20
                color: "red"
                horizontalAlignment: Text.AlignHCenter
                text: ""
            }

            Button {
                text: "Restart"
                onClicked: {
                    wordleLogic.initializeGame();
                    for (var i = 0; i < gameGrid.children.length; i++) {
                        var cell = gameGrid.children[i]; // Assuming direct children are Rectangles
                        if (cell.hasOwnProperty('color')) {
                            cell.color = "lightgrey"; // Reset color of tiles
                            cell.children[0].text = ""; // Reset text of tiles
                        }
                    }
                    currentRowIndex = 0;
                    gameOver = false;
                    statusMessage.text = "";
                }
            }
        }
    }

    property int currentRowIndex: 0 // Explicitly track the current row for guesses
    property var validWords: ["stars", "apple", "berry", "loily", "exits", "slate", "crate", "blaze", "ghost", "flame", "stone", "light", "proud", "quilt"] // List of valid words
    property bool gameOver: false // Track game over state

    Connections {
        target: wordleLogic
        onGuessEvaluated: {
            if (currentRowIndex < 6) {
                var startIndex = currentRowIndex * 5; // Calculate start index for the row
                for (var i = 0; i < 5; i++) {
                    var tile = gameGrid.children[startIndex + i];
                    tile.color = feedback[i] === 'G' ? 'green' : feedback[i] === 'Y' ? 'yellow' : 'grey'; // Update tile color
                    tile.children[0].text = wordInput.text.charAt(i); // Set the letter
                }
                currentRowIndex++;
            }
        }
        onGameWon: {
            gameOver = true;
            statusMessage.text = "Congratulations! You've found the word!";
        }
        onGameLost: {
            gameOver = true;
            statusMessage.text = "Game Over! You've reached the maximum attempts.";
        }
        onInvalidWordEntered: {
            statusMessage.text = "The entered word is not in the list.";
            invalidWordTimer.start();
        }
        onClearInvalidWordWarning: {
            statusMessage.text = "";
        }
    }

    Timer {
        id: invalidWordTimer
        interval: 2000 // 2 seconds
        onTriggered: {
            statusMessage.text = "";
        }
    }
}
