#include "GameMechanics.h"

Player::Player() : numOfSmall(3), numOfMedium(3), numOfLarge(3) {};

Player::~Player()
{
	std::cout << "Player destroyed!\n";
}

///	---------------------//
//  PLAYER RELATED STUFF //
/// ---------------------//

void Player::setName(std::string name)
{
	this->name = name;
}

std::string Player::getName() const
{
	return name;
}

bool Player::setSize(uint16_t size)
{
	this->size = size;
	switch (size)
	{
	case 1:
		if (getSmall() <= 0) { std::cout << "You are out of small!\n"; return false; }
		setSmall(getSmall() - 1);
		return true;
	case 2:
		if (getMedium() <= 0) { std::cout << "You are out of medium!\n"; return false; }
		setMedium(getMedium() - 1);
		return true;
	case 3:
		if (getLarge() <= 0) { std::cout << "You are out of large!\n"; return false; }
		setLarge(getLarge() - 1);
		return true;
	}
}

uint16_t Player::getSize() const
{
	return size;
}

void Player::setBoardPosition(uint16_t boardPosition)
{
	this->boardPosition = boardPosition;
}

uint16_t Player::getBoardPosition() const
{
	return boardPosition;
}

void Player::setPlayerType(char playerType)
{
	this->playerType = playerType;
}

char Player::getPlayerType() const
{
	return playerType;
}

void Player::setSmall(uint16_t numOfSmall)
{
	this->numOfSmall = numOfSmall;
}

uint16_t Player::getSmall() const
{
	return numOfSmall;
}

void Player::setMedium(uint16_t numOfMedium)
{
	this->numOfMedium = numOfMedium;
}

uint16_t Player::getMedium() const
{
	return numOfMedium;
}

void Player::setLarge(uint16_t numOfLarge)
{
	this->numOfLarge = numOfLarge;
}

uint16_t Player::getLarge() const
{
	return numOfLarge;
}

void Player::resetPieceCount()
{
	setSmall(3);
	setMedium(3);
	setLarge(3);
}

///	--------------------//
//  BOARD RELATED STUFF //
/// --------------------//

void Board::printBoard() const
{
	for (uint16_t i = 1; i < MAX_BOARD_SIZE + 1; i++)
	{
		std::cout << gameBoard[i - 1];
		(i % 3 == 0) ? std::cout << "\n" : std::cout << "\t";
	}
}


void Board::fillBoard(char object)
{
	for (uint16_t i = 0; i < MAX_BOARD_SIZE; i++)
	{
		gameBoard[i] = object;
		pos_gameBoard[i] = object;
		size_gameBoard[i] = 0;
	}
}

void Board::placePiece(uint16_t size, uint16_t position, char playerType)
{
	// Remember: Player type "A" = X. Player type "B" = O.
	if (playerType == 'A')
	{
		switch (size)
		{
		case 1:
			gameBoard[position - 1] = "x";
			break;
		case 2:
			gameBoard[position - 1] = "xx";
			break;
		case 3:
			gameBoard[position - 1] = "xxx";
			break;
		default:
			std::cout << "ERROR: Invalid player size\n";
		}
	}
	else if (playerType == 'B')
	{
		switch (size)
		{
		case 1:
			gameBoard[position - 1] = "o";
			break;
		case 2:
			gameBoard[position - 1] = "oo";
			break;
		case 3:
			gameBoard[position - 1] = "ooo";
			break;
		default:
			std::cout << "ERROR: Invalid player size\n";
		}
	}
	else
	{
		std::cout << "ERROR: Invalid Player type!\n";
	}
}

void Board::pos_placePiece(uint16_t position, char playerType)
{
	pos_gameBoard[position - 1] = playerType;
}

bool Board::checkIfSmaller(uint16_t position, uint16_t size)
{
	if (size_gameBoard[position - 1] > size || size_gameBoard[position - 1] == size)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Board::size_setPiece()
{
	size_gameBoard[0] = 0;
}

bool Board::size_placePiece(uint16_t position, uint16_t size)
{
	if (checkIfSmaller(position, size) == true)
	{
		std::cout << "You cannot place here! (size difference invalid)\n";
		return false;
	}
	else
	{
		size_gameBoard[position - 1] = size;
		return true;
	}
}

bool Board::checkForWin() // returns true = there is a winner
{
	/*
		Board for reference:
		0	1	2
		3	4	5
		6	7	8
	*/
	for (uint16_t i = 0; i < 9; i+= 3)
	{
		// check HORIZONTAL
		if (pos_gameBoard[i] == pos_gameBoard[i + 1] &&
			pos_gameBoard[i + 1] == pos_gameBoard[i + 2] &&

			pos_gameBoard[i] != '#' &&
			pos_gameBoard[i + 1] != '#' &&
			pos_gameBoard[i + 2] != '#')
		{
			return true;
		} 
	}
	for (uint16_t i = 0; i < 3; i++)
	{
		// check VERTICAL
		if (pos_gameBoard[i] == pos_gameBoard[i + 3] &&
			pos_gameBoard[i + 3] == pos_gameBoard[i + 6] &&
			
			pos_gameBoard[i] != '#' &&
			pos_gameBoard[i + 3] != '#' &&
			pos_gameBoard[i + 6] != '#')
		{
			return true;
		}
	}
	// check DIAGONAL
	if (pos_gameBoard[0] == pos_gameBoard[4] &&
		pos_gameBoard[4] == pos_gameBoard[8] &&
		
		pos_gameBoard[0] != '#' &&
		pos_gameBoard[4] != '#' &&
		pos_gameBoard[8] != '#')
	{
		return true;
	}
	if (pos_gameBoard[2] == pos_gameBoard[4] &&
		pos_gameBoard[4] == pos_gameBoard[6] &&
		
		pos_gameBoard[2] != '#' &&
		pos_gameBoard[4] != '#' &&
		pos_gameBoard[6] != '#')
	{
		return true;
	}
	// if all checks fail, return false.
	return false;
}