#include <iostream>
#include <cstdlib>
#include <time.h>
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include "Classes/Block.h"
#include "Classes/Piece.h"
#include "Classes/PosMatrix.h"
#include "Classes/Field.h"
#include "Classes/TextBox.h"
#include "main.h"
using namespace std;
using namespace sf;

Vector2f resolution(800, 600);//current window size
int blockSize = 22;//size of one block+outline
float startX = resolution.x/2.5;//field startX
float startY = 0;//field startY

//spawns pieces in next placeholder
Piece SpawnPiece() 
{
    int pieceCode = rand() % PosMatrix::pieceCount;
    int count = PosMatrix::getBlockCount(pieceCode);
    const Vector2f* posMatx = PosMatrix::getPiece(pieceCode);
    Vector2f startPos = Vector2f(startX + blockSize * 10 + 75, startY + 70) + Vector2f(2*blockSize, 2*blockSize);
    Color color = PosMatrix::getColor(pieceCode);
    return Piece(startPos, color, count, posMatx);
}
//move pieces to field from any point
void MoveToField(Piece& piece)
{
    float x = rand() % 6 + 2;
    piece.setPos(Vector2f(startX + x*blockSize, startY));
}
//refreshes the field
void Refresh(int& score, Field field, Piece& active, Piece& next, Text& scoreMsg) 
{
    score = 0;
    field.~Field();
    field = Field(Vector2f(startX, startY - blockSize), 10, 21);
    active = SpawnPiece();
    next = SpawnPiece();
    scoreMsg.setString("Score: \n" + to_string(score));
}
//initialize text shapes with given parameters, saves a lot of code
void SetText(Text& text, Font& font, String str, Vector2f pos, int size, Color fill)
{
    text = Text();
    text.setString(str);
    text.setCharacterSize(size);
    text.setFillColor(fill);
    text.setPosition(pos);
    text.setFont(font);
}
//pause func
void Pause(RenderWindow& window, Text& pauseT)
{
    window.draw(pauseT);
    window.display();
    Event event;
    while (window.waitEvent(event)) 
    {
        if (event.type == Event::KeyPressed)
            if (event.key.code == Keyboard::Escape)
                return;
        if (event.type == Event::Closed)
            window.close();
    }
}
//moving piece to hold placeholder
void Hold(Piece& active, Piece& held)
{
    //there's no need to any check so we just swap held and active blocks and game will know what to do itself
    Piece tmp = active;
    active = held;
    held = tmp;
    held.setPos(Vector2f(startX + blockSize * 10 + 75, startY + 230) + Vector2f(2 * blockSize, 2 * blockSize));
    MoveToField(active);
}
//if player lost game this func being called
void LostGame(RenderWindow& window)
{
    //actually just event listener lul
    Event event;
    while (window.waitEvent(event))
    {
        if (event.key.code == Keyboard::N)
            window.close();
        else if (event.key.code == Keyboard::Y)
            return;
        if (event.type == Event::Closed)
            window.close();
    }
}
//unfinished settings block 
void Settings(bool& holdStat, bool& nextStat) 
{
    //it needs more code of implementing radio buttons/lists and it will make a lot more code in such simple game like tetris so i left it as it is
    RenderWindow settings(VideoMode(400, 200), "Settings");
    Text holdT, nextT;
    while (settings.isOpen()) 
    {
        Event event;
        while(settings.pollEvent(event))
            if (event.type == Event::Closed)
                settings.close();
        settings.clear(Color::Black);
        settings.display();
    }
}

int main()//game itself 
{
    //var init
    srand(time(nullptr));
    Font font;
    font.loadFromFile("font.ttf");
    int score = 0;
    float delay = 0.5, time = 0, acceleration = 0.05;
    bool holdDisabled = false, nextDisabled = false, holdOnCooldown = false;//this had to be used in setting but in fact only holdCooldown used
    RenderWindow window(VideoMode(resolution.x, resolution.y), "Tetris by DLWHI");
    Field field(Vector2f(startX, startY - blockSize), 10, 21);//field itself
    Field nextB(Vector2f(startX + blockSize*10 + 75, startY + 70), 4, 4);//placeholder for next block
    Field holdB(Vector2f(startX + blockSize * 10 + 75, startY + 230), 4, 4);//placeholder for held block
    Piece active = SpawnPiece(), next = SpawnPiece(), held = Piece();//active, next and held pieces
    Clock clock;
    Text scoreT, lostT, nextT, holdT, pauseT, sets;//some text
    Rect<float> setsHB(0, startY + resolution.y - 44, 44, 44);//unused settings button hitbox
    ShowWindow(GetConsoleWindow(), SW_HIDE);//console hider
    //some text inits
    SetText(scoreT, font, "Score:\n0", Vector2f(startX - 200, startY + 66), 33, Color::White);
    SetText(lostT, font, "You lost!\nRestart?(y/n)", Vector2f(resolution.x / 3, resolution.y * 4 / 5), 33, Color::White);
    SetText(pauseT, font, "Pause", Vector2f(resolution.x / 2.2, resolution.y * 4 / 5), 33, Color::White);
    SetText(nextT, font, "Next", Vector2f(startX + blockSize*10 + 66, startY + 15), 33, Color::White);
    SetText(holdT, font, "Hold", Vector2f(startX + blockSize*10 + 70, startY + 180), 33, Color::White);
    SetText(sets, font, "S", Vector2f(0, startY + resolution.y - 44), 44, Color::White);
    //
    MoveToField(active);//moving active piece to field so we could start

	while (window.isOpen())
	{
        time += clock.getElapsedTime().asSeconds();//adding move time
        clock.restart();
		Event event;
        while (window.pollEvent(event))//aaaand input processinsg
        {
            if (event.type == Event::KeyPressed)//if we pressed button
            {
                if (field.MoveCheck(active, active.getBlockCount(), Vector2f(0, blockSize)) && event.key.code == Keyboard::S)//S is for moving down, just shortens fall delay
                    delay = 0.05;
                if (field.MoveCheck(active, active.getBlockCount(), Vector2f(-blockSize, 0)) && event.key.code == Keyboard::A)//A is for moving left, field checks if piece can move then reacts
                    active.MoveLeft();
                if (field.MoveCheck(active, active.getBlockCount(), Vector2f(blockSize, 0)) && event.key.code == Keyboard::D)//D is for moving right, same as left
                    active.MoveRight();
                if (event.key.code == Keyboard::W)//W is for rotation, alghorithm described in field check funcs and in piece rotation func
                    field.RotateCheck(active, active.getBlockCount());
                if (event.key.code == Keyboard::Space && !holdDisabled && !holdOnCooldown)//Spacebar is for hold, checks if it disabled from settings, and makes it cooldown till piece falls to bottom
                {
                    Hold(active, held);
                    holdOnCooldown = true;
                }
                if (event.key.code == Keyboard::Escape)//Escape is for pause, if you'll need to take a break
                    Pause(window, pauseT);
            }
            else if (event.type == Event::Closed)// close checker
                window.close();
            /*else if (event.type == Event::MouseButtonPressed) //unused settings hitbox checker
                if (setsHB.contains(Vector2f(event.mouseButton.x, event.mouseButton.y)))
                    Settings(holdDisabled, nextDisabled);*/
            /*if (event.type == Event::MouseButtonPressed)//debug feature, prints current mouse coordinates
                cout << Mouse::getPosition().x << ", " << Mouse::getPosition().y << endl;*/
        }

        if (time > delay)//if our time is up, which is 0.5 by default
        {
            delay = 0.5*pow(1 - acceleration, score / 1000);//we lowering delay by 5%(which is acceleration var) for each 1000 score points
            time = 0;//reseting our time
            //delay = 80000;
            if (field.MoveCheck(active, active.getBlockCount(), Vector2f(0, blockSize)) && active.getBlockCount() != 0)//and if we can move down(we didn't hit the ground) we move down
                active.MoveDown();
            else//or
            {
                score += field.Occupie(active, active.getBlockCount());// placing current piece to field and check for cleared lines (field does it by auto)
                active = next;//moving our next piece and generating next
                MoveToField(active);
                next = SpawnPiece();

                holdOnCooldown = false;//resetting cooldown on hold
                scoreT.setString("Score: \n" + to_string(score));//some text changes
                if(field.LoseCheck())//if we lost
                {
                    window.draw(lostT);//draw message
                    window.display();
                    Refresh(score, field, active, next, scoreT);//refresh the game and field so we could play again
                    LostGame(window);//then ask if we want to play agaion (lulw)
                    continue;
                }


            }
        }
        window.clear(Color::Black);
        //some a lot of drawing
        //gotta say that piece and field classes has a lot of drawable things so i had to make them draw themselves by sendning window to them
        //it's just more convinient
        window.draw(holdT);
        window.draw(scoreT);
        //window.draw(sets);
        field.Draw(window);
        holdB.Draw(window);
        active.Draw(window);
        held.Draw(window);
        if (!nextDisabled)
        {
            window.draw(nextT);
            nextB.Draw(window);
            next.Draw(window);
        }
        window.display();//display shiet
	}
    return 0;
}