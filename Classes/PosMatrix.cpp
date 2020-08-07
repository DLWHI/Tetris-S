#include "PosMatrix.h"
//matrix inits
const Vector2f PosMatrix::zPiece[5] =
{
    Vector2f(blockSize/2, blockSize / 2),
    Vector2f(0, 0),
    Vector2f(0, -blockSize),
    Vector2f(-blockSize, -blockSize),
    Vector2f(blockSize, 0)
};
const Vector2f PosMatrix::sPiece[5] =
{
    Vector2f(blockSize / 2, blockSize / 2),
    Vector2f(0, 0),
    Vector2f(0, -blockSize),
    Vector2f(blockSize, -blockSize),
    Vector2f(-blockSize, 0)
};
const Vector2f PosMatrix::lPiece[5] =
{
    Vector2f(blockSize / 2, blockSize / 2),
    Vector2f(0, 0),
    Vector2f(-blockSize, -blockSize),
    Vector2f(blockSize, 0),
    Vector2f(-blockSize, 0)
};
const Vector2f PosMatrix::jPiece[5] =
{
    Vector2f(blockSize / 2, blockSize / 2),
    Vector2f(0, 0),
    Vector2f(blockSize, -blockSize),
    Vector2f(blockSize, 0),
    Vector2f(-blockSize, 0)
};
const Vector2f PosMatrix::tPiece[5] =
{
    Vector2f(blockSize / 2, blockSize / 2),
    Vector2f(0, 0),
    Vector2f(0, -blockSize),
    Vector2f(blockSize, 0),
    Vector2f(-blockSize, 0)

};
const Vector2f PosMatrix::oPiece[5] =
{
    Vector2f(0, 0),
    Vector2f(0, 0),
    Vector2f(0, -blockSize),
    Vector2f(-blockSize, -blockSize),
    Vector2f(-blockSize, 0)

};
const Vector2f PosMatrix::iPiece[5] =
{
    Vector2f(0, 0),
    Vector2f(-2*blockSize, -blockSize),
    Vector2f(-blockSize, -blockSize),
    Vector2f(0, -blockSize),
    Vector2f(blockSize, -blockSize)

};
//
const Vector2f* PosMatrix::getPiece(int code) 
{
    //you should add piece code after you created new piece, otherwise it will not be generated
    if (code == 0)
        return PosMatrix::zPiece;
    else if (code == 1)
        return PosMatrix::oPiece;
    else if (code == 2)
        return PosMatrix::sPiece;
    else if (code == 3)
        return PosMatrix::lPiece;
    else if (code == 4)
        return PosMatrix::jPiece;
    else if (code == 5)
        return PosMatrix::iPiece;
    else if (code == 6)
        return PosMatrix::tPiece;
    return nullptr;
 }
Color PosMatrix::getColor(int code)
{
    //same shit as getPiece() or your block will be black
    if (code == 0)
        return Color::Red;
    else if (code == 1)
        return Color::Yellow;
    else if (code == 2)
        return Color::Green;
    else if (code == 3)
        return Color(25, 25, 255);
    else if (code == 4)
        return Color(255, 170, 0);
    else if (code == 5)
        return Color(0, 255, 255);
    else if (code == 6)
        return Color(153, 0, 255);
    return Color(79, 79, 79);
}
int PosMatrix::getBlockCount(int code)
{
    //add here your block handling
    if (code >= 0 && code <= 6)
        return PosMatrix::defaultBlockC;
    return 0;
}