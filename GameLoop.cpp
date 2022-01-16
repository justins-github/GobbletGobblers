#include "GameLoop.h"
#include "GameMechanics.h"
#pragma once

void Gobblers::Run()
{
	Player one, two;
	Board board;
	one.setName("PlayerOne");
	two.setName("PlayerTwo");

	one.setPlayerType('A');
	two.setPlayerType('B');

	static bool GameRuns = true;

	// Pointers to size of piece, and position in board
	// "Why is it temporary position?"
	/* 
	I want to avoid making new memory (through initializing it
	normally), so I think pointers are a good way of recalling
	the same variable over and over again.
	*/
	uint16_t tempSize;
	uint16_t *p_tempSize = &tempSize;
	uint16_t tempBoardPosition;
	uint16_t *p_tempBoardPosition = &tempBoardPosition;
	static char gameEnd;

	do {
		board.fillBoard('#');
		board.printBoard();
		one.resetPieceCount();
		two.resetPieceCount();

		static bool thereIsAWinner = false;
		static bool placeFlags = board.size_placePiece(1, 1);
		// this flag is to ensure that when the player input a size (size of
		// gobbler piece), that the input is VALID. If size is not VALID
		// (for example, if a player tries to put a '1' piece on a '3' piece)
		// it will return FALSE (INVALID) and they would have to RE-ENTER
		// size and position.

		// the (1, 1) parameter is to ensure that it doesn't play the
		// error message in size_placePiece() function.
		static bool compareSizeCheck = false;

		board.size_setPiece();
		// to undo the (1, 1) parameter on line 36.
		placeFlags = true;
		
		while (!thereIsAWinner)
		{
			while (placeFlags)
			{
				std::cout << one.getName() << ", enter a size: ";
				std::cin >> *p_tempSize;

				while (*p_tempSize > 3 || *p_tempSize < 0 || std::cin.fail())
					// basically there are only three sizes for the pieces (1, 2 or 3)
				{
					std::cout << "ERROR: Enter a number from 1-3: ";
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					std::cin >> *p_tempSize;
				}
				
				while (!one.setSize(*p_tempSize)) // or if there is not enough of whatever size
				{
					std::cout << "Enter a number from 1-3: ";
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					std::cin >> *p_tempSize;
					one.setSize(*p_tempSize);
				}

				compareSizeCheck = false;
				do {
					std::cout << "Where do you want to place the piece? ";
					std::cin >> *p_tempBoardPosition;
					while (*p_tempBoardPosition > 9 || *p_tempBoardPosition < 0 || std::cin.fail())
						// there is only 9 possible locations to input pieces at
					{
						std::cout << "ERROR: Enter a number from 1-9: ";
						std::cin.clear();
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						std::cin >> *p_tempBoardPosition;
					}

					bool* p_compareSize = new bool;
					*p_compareSize = board.size_placePiece(*p_tempBoardPosition, *p_tempSize);

					*p_compareSize == false ? compareSizeCheck = false : compareSizeCheck = true;
					delete p_compareSize;
				} while (!compareSizeCheck);

				one.setBoardPosition(*p_tempBoardPosition);
				board.placePiece(one.getSize(), one.getBoardPosition(), one.getPlayerType());
				// array #1
				board.pos_placePiece(one.getBoardPosition(), one.getPlayerType());
				// array #2
				board.checkForWin();
				// check for win for array #2

				if (board.checkForWin() == true)
				{
					board.printBoard();
					std::cout << "Player one wins!\n";
					thereIsAWinner = true;
					placeFlags = false;
					continue;
				}

				board.printBoard();

				/////////////////////////////
				/* // PLAYER TWO'S TURN // */
				/////////////////////////////

				std::cout << two.getName() << ", enter a size: ";
				std::cin >> *p_tempSize;

				while (*p_tempSize > 3 || *p_tempSize < 0 || std::cin.fail())
					// basically there are only three sizes for the pieces (1, 2 or 3)
				{
					std::cout << "ERROR: Enter a number from 1-3: ";
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					std::cin >> *p_tempSize;
				}

				while (!two.setSize(*p_tempSize)) // or if there is not enough of whatever size
				{
					std::cout << "Enter a number from 1-3: ";
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					std::cin >> *p_tempSize;
					two.setSize(*p_tempSize);
				}

				compareSizeCheck = false;
				do {
					std::cout << "Where do you want to place the piece? ";
					std::cin >> *p_tempBoardPosition;
					while (*p_tempBoardPosition > 9 || *p_tempBoardPosition < 0 || std::cin.fail())
						// there is only 9 possible locations to input pieces at
					{
						std::cout << "ERROR: Enter a number from 1-9: ";
						std::cin.clear();
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						std::cin >> *p_tempBoardPosition;
					}

					bool *p_compareSize = new bool;
					*p_compareSize = board.size_placePiece(*p_tempBoardPosition, *p_tempSize);

					*p_compareSize == false ? compareSizeCheck = false : compareSizeCheck = true;
					delete p_compareSize;
				} while (!compareSizeCheck);

				two.setBoardPosition(*p_tempBoardPosition);
				board.placePiece(two.getSize(), two.getBoardPosition(), two.getPlayerType());
				// array #1
				board.pos_placePiece(two.getBoardPosition(), two.getPlayerType());
				// array #2
				board.checkForWin();
				// check for win for array #2

				if (board.checkForWin() == true)
				{
					board.printBoard();
					std::cout << "Player two wins!\n";
					thereIsAWinner = true;
					placeFlags = false;
					continue;
				}

				board.printBoard();

			}

		}

		std::cout << "Continue playing the game? y/n\n";
		std::cin >> gameEnd;
		switch (gameEnd)
		{
		case 'y':
			break;
		case 'n': GameRuns = false; break;
		default: 
			std::cout << "ERROR: Enter 'y' or 'n'\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}

	} while (GameRuns);
}