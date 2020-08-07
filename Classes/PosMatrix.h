#pragma once
#include "SFML/Graphics.hpp"
using namespace sf;
//this class contains all pieces information, their relative postioning and stuff
//first vector in any array should be pivot shift vector, all initialized pieces will shift pivot from given pos by a posMatrix[0] vector
//this class can be used to add new pieces or change that ones that is already here
//the class is completely static
class PosMatrix
{
public:
    PosMatrix() = default;
    static const int pieceCount = 7;//pieces count, change it if u add new piece
    static const Vector2f* getPiece(int);//get piece  matrix by code
    static Color getColor(int);//get piece color by code
    static int getBlockCount(int);//get block count by code(default 4)
private:
    static const int defaultBlockC = 4;
    static const int blockSize = 22;
    static const Vector2f zPiece[5];
    static const Vector2f sPiece[5];
    static const Vector2f lPiece[5];
    static const Vector2f jPiece[5];
    static const Vector2f tPiece[5];
    static const Vector2f oPiece[5];
    static const Vector2f iPiece[5];
};

 