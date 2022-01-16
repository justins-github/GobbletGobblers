#ifndef GAMEMECHANICS_H
#define GAMEMECHANICS_H
#pragma once

#include <stdint.h>
#include <string>
#include <iostream>

#define MAX_BOARD_SIZE 9
// uint16_t means UNSIGNED SHORT.
// 19/6/2021 5:20 PM - I just farted.

class Player
{
private:
	uint16_t numOfSmall;
	// number of small pieces each player has etc.
	uint16_t numOfMedium;
	uint16_t numOfLarge;
	uint16_t size;
	/// as in size of the piece
	/// 1 being the smallest, 3 being the largest.
	uint16_t boardPosition; // board position to place piece in
	// look at setBoardPosition() function to see where its useful
	char playerType;
	// This means are they player ONE (goes first) or player TWO?
	// I need this to determine whether it should be 'x' or 'o' on the board.
	std::string name;
public:
	std::string getName() const;
	void setName(std::string name);
	uint16_t getSize() const;
	bool setSize(uint16_t size);
	uint16_t getBoardPosition() const;
	void setBoardPosition(uint16_t boardPosition);
	char getPlayerType() const;
	void setPlayerType(char playerType);

	void setSmall(uint16_t numOfSmall);
	uint16_t getSmall() const;
	void setMedium(uint16_t numOfMedium);
	uint16_t getMedium() const;
	void setLarge(uint16_t numOfLarge);
	uint16_t getLarge() const;

	void resetPieceCount();
	
	Player();
	~Player();
};

class Board
{
private:
	std::string gameBoard[MAX_BOARD_SIZE];
	// the board for printing out the board to the console

	char pos_gameBoard[MAX_BOARD_SIZE];
	// the board that decides on the winning/losing conditions
	// based on vertical/horizontal/diagonal alignments
	// everything related to position will be marked with a 'pos_'

	uint16_t size_gameBoard[MAX_BOARD_SIZE];
	// the board that decides on whether moves are legal
	// based on checking the sizes of the pieces
public:
	void printBoard() const;
	void fillBoard(char object);
	void placePiece(uint16_t position, uint16_t size, char playerType);
	// Place a piece at a specific position in the board array, 
	// size refers to the size of the PIECE, represented
	// by the number of 'x' or 'o'.

	void pos_placePiece(uint16_t position, char playerType);
	bool size_placePiece(uint16_t position, uint16_t size);
	// It is a bool for the place piece function as:
	// 1) If it is true, it is a valid position and the
	// rest of the arrays can be filled up.
	// 2) If it is false, the rest of the arrays will
	// NOT be filled up, and the player has to RE-ENTER
	// size + position
	void size_setPiece();

	bool checkIfSmaller(uint16_t position, uint16_t size);

	bool checkForWin();
	// using pos_gameBoard's board to check for win.
	/* Remember: pos_gameBoard has the data for the Xs and Os. */
};

#endif