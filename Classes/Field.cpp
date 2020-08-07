#include "Field.h"
void Square::operator=(Square other)
{
	//we just need to move current block and condition and DO NOT TOUCH THE POSITION of field block
	block = other.block;
	block.ShapeInit(pos);
	occupied = other.occupied;
}

Field::Field(Vector2f pos, int xSize, int ySize) 
{
	//constructor recieves size of field and its pos
	this->xSize = xSize;
	this->ySize = ySize;
	//frame init
	frame.setPosition(pos - Vector2f(1, 0));
	frame.setSize(Vector2f(xSize * blockSize, ySize * blockSize));
	frame.setFillColor(Color(35, 35, 35));
	frame.setOutlineColor(Color(35, 35, 35));
	frame.setOutlineThickness(4);
	//field blocks init by default they're gray and not occupied
	field = new Square*[ySize];
	for (int j = 0; j < ySize; j++)
	{
		field[j] = new Square[xSize];
		for (int i = 0; i < xSize; i++)
		{
			field[j][i].block = Block(Color(79, 79, 79));
			field[j][i].block.ShapeInit(pos + Vector2f(i * blockSize, j * blockSize));
			field[j][i].pos = pos + Vector2f(i * blockSize, j * blockSize);
		}
	}
}

int Field::Occupie(Piece block, int blockCount)
{
	//each block is being copied from piece to field
	for (int i = 0; i < blockCount; i++)
	{
		//index extraction
		float curX = block.getBlock(i).getPosition().x - field[0][0].pos.x;
		int x = curX / blockSize;
		float curY = block.getBlock(i).getPosition().y - field[0][0].pos.y;
		int y = curY / blockSize;
		field[y][x].occupied = true;
		field[y][x].block = block.getBlock(i);
	}
	return FieldCheck();//returns the score that was got from line clearing
}

bool Field::MoveCheck(Piece piece, int blockCount, Vector2f displacement)
{
	//checks if piece can move do direction
	for (int i = 0; i < blockCount; i++)
	{
		float curX = piece.getBlock(i).getPosition().x - field[0][0].pos.x + displacement.x;
		int x = curX / blockSize;
		float curY = piece.getBlock(i).getPosition().y - field[0][0].pos.y + displacement.y;
		int y = curY / blockSize;
		if (x >= xSize || x <= -1 || y >= ySize || y <= -1)
			return false;
		if (field[y][x].occupied)
			return false;
	}
	return true;
}

void Field::RotateCheck(Piece& piece, int blockCount)
{
	//check if piece can rotate at its pos
	piece.Rotate();//rotationg piece
	for (int i = 0; i < blockCount; i++)
	{
		//index extract
		float curX = piece.getBlock(i).getPosition().x - field[0][0].pos.x;
		int x = curX / blockSize;
		float curY = piece.getBlock(i).getPosition().y - field[0][0].pos.y;
		int y = curY / blockSize;
		if (y <= 0)//if any block of piece is on 0 line(that's one above the window) we exit so no checks will be performed(and no segmention fault)
			return;
		if (!(MoveCheck(piece, blockCount, Vector2f(0, -blockSize)) || MoveCheck(piece, blockCount, Vector2f(blockSize, 0)) || MoveCheck(piece, blockCount, Vector2f(-blockSize, 0))))
		{
			//if we can't move, just rotate it 3 more times to be as it was
			piece.Rotate();
			piece.Rotate();
			piece.Rotate();
		}
		if (x >= xSize || (MoveCheck(piece, blockCount, Vector2f(-blockSize, 0)) && field[y][x].occupied))//if we hit the wall or block, we move it to opposite direction
			piece.MoveLeft();
		else if (x <= -1 || (MoveCheck(piece, blockCount, Vector2f(blockSize, 0)) && field[y][x].occupied))
			piece.MoveRight();
		else if (y >= ySize || (MoveCheck(piece, blockCount, Vector2f(0, -blockSize)) && field[y][x].occupied))//if we hit block or bottom, we move it up
			piece.MoveUp();
	}//simple
}

bool Field::LoseCheck()
{
	//if first line if occupied we lose
	for (int i = 0; i < xSize; i++)
	{
		if (field[0][i].occupied)
			return true;
	}
	return false;
}

int Field::FieldCheck() 
{
	int clearedLines = 0;//clered lines count it determines how much points we will get
	for (int j = 0, m = 0; j < ySize; j++)//cheking
	{
		for (int i = 0; i < xSize; i++)
			if (field[j][i].occupied)
				m++;
		if (m == xSize) //if all blocks on line is occupied we clear it
		{
			ClearLine(j);
			clearedLines++;
		}
		m = 0;
	}
	switch (clearedLines)
	{
	case 1://and if we clear 1 line we get 100 points
		return 100;
	case 2://2 - 300
		return 300;
	case 3: //3 - 700
		return 700;
	case 4://and tetris is equal to 1500
		return 1500;
	default://this is classic tetris score valuing and if we clear 5< lines(that can be done by adding custom pieces) we get 0 points so it needed to handle such piece
		//but stop breaking this game mf 5 blocks in piece that's imbalance
		return 0;
	}
}

void Field::ClearLine(int line) 
{
	//when line is cleared we move all field blocks one by one to lower level
	for (int j = line; j > 0; j--)
		for (int i = 0; i < xSize; i++)
			field[j][i] = field[j - 1][i];
	//and reinitializing 0 row(that is unseen)
	for (int i = 0; i < xSize; i++) 
	{
		field[0][i].occupied = false;
		field[0][i].block = Block(Color(79, 79, 79));
		field[0][i].block.ShapeInit(field[0][i].pos);
	}
}

void Field::Draw(RenderWindow& window) 
{
	//DRAW!
	window.draw(frame);
	for (int j = 0; j < ySize; j++)
		for (int i = 0; i < xSize; i++)
			window.draw(field[j][i].block);
}