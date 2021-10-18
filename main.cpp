#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include "Board.h"
#include "TextureManager.h"
#include "SpriteObject.h"
#include "Game.h"
#include "Game.h"
#include <chrono>
#include <thread>

using namespace std;
using namespace std::this_thread;
using namespace std::chrono;

bool resetClick(sf::Event event, sf::Vector2i mousePos, SpriteObject Test1, SpriteObject Test2, SpriteObject Test3, SpriteObject Debug, SpriteObject faceLose, SpriteObject faceHappy, SpriteObject faceWin);
vector<SpriteObject> DebugMode(sf::Event event, sf::Vector2i mousePos, SpriteObject Debug, vector<SpriteObject> TileVector);
void recursionReveal(SpriteObject& TileVector, vector<int> numbers);
Board chooseBoard(Board newBoard, string file);
vector<string> initializeSprites(Board newBoard, vector<string> Sprites);
vector<SpriteObject>  initializeBoard(Board newBoard, vector<SpriteObject> TileVector);
vector<SpriteObject> mouseFunc(sf::Event event, sf::Vector2i mousePos, vector<SpriteObject> TileVector);
vector<SpriteObject> buttons(sf::Event event, sf::Vector2i mousePos, SpriteObject Test1, SpriteObject Test2, SpriteObject Test3, SpriteObject faceHappy, vector<SpriteObject> TileVector);

int getHeight() {
    int width;
    int height;
    ifstream file("boards/config.cfg");
    string width_str;
    getline(file, width_str);
    width = stoi(width_str);
    string height_str;
    getline(file, height_str);
    height = stoi(height_str);
    string mineCount_str;
    getline(file, mineCount_str);

    file.close();
    return height;
}
int getWidth() {
    int width;
    int height;
    ifstream file("boards/config.cfg");
    string width_str;
    getline(file, width_str);
    width = stoi(width_str);
    string height_str;
    getline(file, height_str);
    height = stoi(height_str);
    string mineCount_str;
    getline(file, mineCount_str);

    file.close();
    return  width;
}

int getMineCount() {
    int width;
    int height;
    ifstream file("boards/config.cfg");
    string width_str;
    getline(file, width_str);
    width = stoi(width_str);
    string height_str;
    getline(file, height_str);
    height = stoi(height_str);
    string mineCount_str;
    getline(file, mineCount_str);
    int mineCount = stoi(mineCount_str);
    file.close();
    return  mineCount;
}
int main()
{
    int bugFix = 0;
    int mineCount = 0;
    int tilesCount = 0;
    bool win = false;
    bool loss = false;
    Game newGame;
    Board newBoard;
    TextureManager textures;

    vector<SpriteObject> TileVector;
    vector<string> SpritesVector;
    vector<SpriteObject>* pointerVector;

    newBoard.width = getWidth();
    newBoard.height = getHeight();

    bool start = true;
    bool test = false;
    sf::RenderWindow window(sf::VideoMode(newBoard.getWidth(), newBoard.getHeight()), "Minesweeper - Project 3");
    cout << newBoard.getWidth() << " " << newBoard.getHeight() << endl;
    SpriteObject faceHappy("face_happy");
    SpriteObject tileHidden("tile_hidden");
    SpriteObject tileRevealed("tile_revealed");
    SpriteObject Debug("debug");
    SpriteObject Test1("test_1");
    SpriteObject Test2("test_2");
    SpriteObject Test3("test_3");
    SpriteObject Mine("mine");
    SpriteObject flag("flag");
    SpriteObject Digit1("digits");
    SpriteObject Digit2("digits");
    SpriteObject Digit3("digits");

    SpriteObject faceWin("face_win");
    SpriteObject faceLose("face_lose");

    faceLose.TSprite.setPosition(newBoard.getWidth() / 2, newBoard.getHeight() - 88);
    faceWin.TSprite.setPosition(newBoard.getWidth() / 2, newBoard.getHeight() - 88);
    faceHappy.TSprite.setPosition(newBoard.getWidth() / 2, newBoard.getHeight() - 88);
    Debug.TSprite.setPosition(newBoard.getWidth() - 66 * 4, newBoard.getHeight() - 88);
    Test1.TSprite.setPosition(newBoard.getWidth() - 66 * 3, newBoard.getHeight() - 88);
    Test2.TSprite.setPosition(newBoard.getWidth() - 66 * 2, newBoard.getHeight() - 88);
    Test3.TSprite.setPosition(newBoard.getWidth() - 66, newBoard.getHeight() - 88);
    //  fill in Board
    // write functionality
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

        }
        if (start == true) {
            vector<string> SpritesVector;
            vector<SpriteObject> rand;

            newBoard.width = getWidth();
            newBoard.height = getHeight();
            newBoard.mineCount = getMineCount();
            newBoard.randomMap();
            SpritesVector = initializeSprites(newBoard, SpritesVector);
            for (int i = 0; i < SpritesVector.size(); i++) {
                string name = SpritesVector[i];
                SpriteObject object(name);
                rand.push_back(object);
            }
            TileVector = initializeBoard(newBoard, rand);
            newGame.amountMines = newBoard.mineCount;

            start = false;
        }
        window.clear(sf::Color::White);
        window.draw(Debug.TSprite);
        window.draw(Test1.getSprite());
        window.draw(Test2.getSprite());
        window.draw(Debug.getSprite());
        window.draw(Test3.getSprite());



        for (int i = 0; i < TileVector.size(); i++) {
            TileVector[i].index = i;
        }

        int index = 0;
        for (int j = 0; j < newBoard.height; j++) {
            for (int i = 0; i < newBoard.width; i++) {
                tileRevealed.TSprite.setPosition(i * 32, j * 32);
                window.draw(tileRevealed.getSprite());
                index++;
            }

        }

        index = 0;

        for (int j = 0; j < newBoard.height; j++) {
            for (int i = 0; i < newBoard.width; i++) {

                if (TileVector[index].flagged == true) {

                    if (TileVector[index].type == "mine" && TileVector[index].debug == true) {

                        tileHidden.TSprite.setPosition(i * 32, j * 32);
                        window.draw(tileHidden.getSprite());

                        TileVector[index].x = i * 32;
                        TileVector[index].y = j * 32;

                        flag.TSprite.setPosition(i * 32, j * 32);
                        window.draw(flag.getSprite());

                        TileVector[index].TSprite.setPosition(i * 32, j * 32);
                        window.draw(TileVector[index].getSprite());


                    }
                    else if (TileVector[index].reveal == true) {


                    }
                    else {
                        tileHidden.TSprite.setPosition(i * 32, j * 32);
                        window.draw(tileHidden.getSprite());

                        TileVector[index].x = i * 32;
                        TileVector[index].y = j * 32;

                        flag.TSprite.setPosition(i * 32, j * 32);
                        window.draw(flag.TSprite);


                    }
                }
                else {
                    if (TileVector[index].type == "mine") {
                        if (TileVector[index].debug) {
                            tileHidden.TSprite.setPosition(i * 32, j * 32);
                            window.draw(tileHidden.getSprite());

                            TileVector[index].x = i * 32;
                            TileVector[index].y = j * 32;

                            TileVector[index].TSprite.setPosition(i * 32, j * 32);
                            window.draw(TileVector[index].getSprite());
                        }

                        else if (TileVector[index].reveal) {
                            tileRevealed.TSprite.setPosition(i * 32, j * 32);
                            window.draw(tileRevealed.getSprite());

                            TileVector[index].x = i * 32;
                            TileVector[index].y = j * 32;

                            TileVector[index].TSprite.setPosition(i * 32, j * 32);
                            window.draw(TileVector[index].getSprite());
                        }
                        else {


                            TileVector[index].x = i * 32;
                            TileVector[index].y = i * 32;

                            TileVector[index].TSprite.setPosition(i * 32, j * 32);
                            window.draw(TileVector[index].getSprite());

                            tileHidden.TSprite.setPosition(i * 32, j * 32);
                            window.draw(tileHidden.getSprite());



                        }

                    }
                    if (TileVector[index].type == "tile_hidden") {
                        if (TileVector[index].reveal == false) {
                            TileVector[index].TSprite.setPosition(i * 32, j * 32);
                            window.draw(TileVector[index].TSprite);

                        }
                        else {
                            tileRevealed.TSprite.setPosition(i * 32, j * 32);
                            window.draw(tileRevealed.getSprite());
                        }
                    }

                    if (TileVector[index].type == "number_1") {
                        if (TileVector[index].reveal) {
                            tileRevealed.TSprite.setPosition(i * 32, j * 32);
                            window.draw(tileRevealed.getSprite());
                            TileVector[index].TSprite.setPosition(i * 32, j * 32);
                            window.draw(TileVector[index].TSprite);
                        }
                        else {


                            TileVector[index].x = i * 32;
                            TileVector[index].y = i * 32;

                            TileVector[index].TSprite.setPosition(i * 32, j * 32);
                            window.draw(TileVector[index].getSprite());

                            tileHidden.TSprite.setPosition(i * 32, j * 32);
                            window.draw(tileHidden.getSprite());



                        }
                    }
                    if (TileVector[index].type == "number_2") {
                        if (TileVector[index].reveal) {
                            tileRevealed.TSprite.setPosition(i * 32, j * 32);
                            window.draw(tileRevealed.getSprite());
                            TileVector[index].TSprite.setPosition(i * 32, j * 32);
                            window.draw(TileVector[index].TSprite);
                        }
                        else {


                            TileVector[index].x = i * 32;
                            TileVector[index].y = i * 32;

                            TileVector[index].TSprite.setPosition(i * 32, j * 32);
                            window.draw(TileVector[index].getSprite());

                            tileHidden.TSprite.setPosition(i * 32, j * 32);
                            window.draw(tileHidden.getSprite());



                        }
                    }
                    if (TileVector[index].type == "number_3") {
                        if (TileVector[index].reveal) {
                            tileRevealed.TSprite.setPosition(i * 32, j * 32);
                            window.draw(tileRevealed.getSprite());
                            TileVector[index].TSprite.setPosition(i * 32, j * 32);
                            window.draw(TileVector[index].TSprite);
                        }
                        else {


                            TileVector[index].x = i * 32;
                            TileVector[index].y = i * 32;

                            TileVector[index].TSprite.setPosition(i * 32, j * 32);
                            window.draw(TileVector[index].getSprite());

                            tileHidden.TSprite.setPosition(i * 32, j * 32);
                            window.draw(tileHidden.getSprite());



                        }
                    }
                    if (TileVector[index].type == "number_4") {
                        if (TileVector[index].reveal) {
                            tileRevealed.TSprite.setPosition(i * 32, j * 32);
                            window.draw(tileRevealed.getSprite());
                            TileVector[index].TSprite.setPosition(i * 32, j * 32);
                            window.draw(TileVector[index].TSprite);
                        }
                        else {


                            TileVector[index].x = i * 32;
                            TileVector[index].y = i * 32;

                            TileVector[index].TSprite.setPosition(i * 32, j * 32);
                            window.draw(TileVector[index].getSprite());

                            tileHidden.TSprite.setPosition(i * 32, j * 32);
                            window.draw(tileHidden.getSprite());



                        }
                    }
                    if (TileVector[index].type == "number_5") {
                        if (TileVector[index].reveal) {
                            tileRevealed.TSprite.setPosition(i * 32, j * 32);
                            window.draw(tileRevealed.getSprite());
                            TileVector[index].TSprite.setPosition(i * 32, j * 32);
                            window.draw(TileVector[index].TSprite);
                        }
                        else {


                            TileVector[index].x = i * 32;
                            TileVector[index].y = i * 32;

                            TileVector[index].TSprite.setPosition(i * 32, j * 32);
                            window.draw(TileVector[index].getSprite());

                            tileHidden.TSprite.setPosition(i * 32, j * 32);
                            window.draw(tileHidden.getSprite());



                        }
                    }
                    if (TileVector[index].type == "number_6") {
                        if (TileVector[index].reveal) {
                            tileRevealed.TSprite.setPosition(i * 32, j * 32);
                            window.draw(tileRevealed.getSprite());
                            TileVector[index].TSprite.setPosition(i * 32, j * 32);
                            window.draw(TileVector[index].TSprite);
                        }
                        else {


                            TileVector[index].x = i * 32;
                            TileVector[index].y = i * 32;

                            TileVector[index].TSprite.setPosition(i * 32, j * 32);
                            window.draw(TileVector[index].getSprite());

                            tileHidden.TSprite.setPosition(i * 32, j * 32);
                            window.draw(tileHidden.getSprite());



                        }
                    }
                    if (TileVector[index].type == "number_7") {
                        if (TileVector[index].reveal) {
                            tileRevealed.TSprite.setPosition(i * 32, j * 32);
                            window.draw(tileRevealed.getSprite());
                            TileVector[index].TSprite.setPosition(i * 32, j * 32);
                            window.draw(TileVector[index].TSprite);
                        }
                        else {


                            TileVector[index].x = i * 32;
                            TileVector[index].y = i * 32;

                            TileVector[index].TSprite.setPosition(i * 32, j * 32);
                            window.draw(TileVector[index].getSprite());

                            tileHidden.TSprite.setPosition(i * 32, j * 32);
                            window.draw(tileHidden.getSprite());



                        }
                    }
                    if (TileVector[index].type == "number_8") {
                        if (TileVector[index].reveal) {
                            tileRevealed.TSprite.setPosition(i * 32, j * 32);
                            window.draw(tileRevealed.getSprite());
                            TileVector[index].TSprite.setPosition(i * 32, j * 32);
                            window.draw(TileVector[index].TSprite);
                        }
                        else {


                            TileVector[index].x = i * 32;
                            TileVector[index].y = i * 32;

                            TileVector[index].TSprite.setPosition(i * 32, j * 32);
                            window.draw(TileVector[index].getSprite());

                            tileHidden.TSprite.setPosition(i * 32, j * 32);
                            window.draw(tileHidden.getSprite());



                        }
                    }
                }
                index++;

            }

        }

        if (event.type == sf::Event::MouseButtonPressed) {


            sf::Vector2i mousePos = sf::Mouse::getPosition(window);


            if (win == true) {
                TileVector = mouseFunc(event, mousePos, TileVector);
                TileVector = DebugMode(event, mousePos, Debug, TileVector);
            }
            if (loss == false) {
                TileVector = mouseFunc(event, mousePos, TileVector);
                TileVector = DebugMode(event, mousePos, Debug, TileVector);
            }

            if (resetClick(event, mousePos, Test1, Test2, Test3, Debug, faceHappy, faceWin, faceLose)) {
                loss = false;
                win = false;
                TileVector.clear();
                TileVector = buttons(event, mousePos, Test1, Test2, Test3, faceHappy, TileVector);
          
            }

            vector<int> list;
            if (event.mouseButton.button == sf::Mouse::Left) {
                for (int i = 0; i < TileVector.size(); i++) {
                    if (TileVector[i].getRect().contains(sf::Vector2f(mousePos.x, mousePos.y))) {
                        if (TileVector[i].type == "tile_hidden") {

                            recursionReveal(TileVector[i], list);



                        }
                    }

                }
            }
            for (int i = 0; i < list.size(); i++) {
                TileVector[list[i]].reveal = true;
            }
            list.clear();
        }

        // get numbr of flags.
        int flags = 0;
        for (int i = 0; i < TileVector.size(); i++) {

            if (TileVector[i].flagged == true) {
                flags++;
            }
        }

        for (int i = 0; i < TileVector.size(); i++) {

            if (TileVector[i].type == "mine") {
                mineCount++;
            }
        }
        newGame.amountMines = mineCount;
        mineCount = 0;

        newGame.amountFlags = flags;
        flags = 0;

        newGame.counter();
        if (newGame.counter() >= 0 && newGame.counter() <= newGame.amountMines) {
            int ones = newGame.counter() % 10;
            int tens = newGame.counter() / 10;
            tens = tens % 10;

            int hundreds = newGame.counter() / 100;
            Digit1.setRect(hundreds);
            Digit1.TSprite.setPosition(0, newBoard.getHeight() - 88);
            window.draw(Digit1.getSprite());
            Digit2.setRect(tens);
            Digit2.TSprite.setPosition(21, newBoard.getHeight() - 88);
            window.draw(Digit2.getSprite());
            Digit3.setRect(ones);
            Digit3.TSprite.setPosition(40, newBoard.getHeight() - 88);
            window.draw(Digit3.getSprite());
        }
        else if (newGame.counter() < 0) {
            Digit1.setRect(10);
            int tens = abs(newGame.counter()) / 10;
            int ones = abs(newGame.counter()) % 10;

            Digit1.setRect(10);
            Digit1.TSprite.setPosition(0, newBoard.getHeight() - 88);
            window.draw(Digit1.getSprite());
            Digit2.setRect(tens);
            Digit2.TSprite.setPosition(21, newBoard.getHeight() - 88);
            window.draw(Digit2.getSprite());
            Digit3.setRect(ones);
            Digit3.TSprite.setPosition(40, newBoard.getHeight() - 88);
            window.draw(Digit3.getSprite());
        }
        for (int i = 0; i < TileVector.size(); i++) {

            if (TileVector[i].type == "mine" && TileVector[i].reveal == true) {
                loss = true;
            }
        }

        for (int i = 0; i < TileVector.size(); i++) {

            if (TileVector[i].type != "mine" && TileVector[i].reveal != true) {
                tilesCount++;
            }
        }
        newGame.remainingTiles = tilesCount;
        tilesCount = 0;

        if (newGame.remainingTiles == 0) {
            win = true;
            for (int i = 0; i < TileVector.size(); i++) {
                if (TileVector[i].type == "mine") {
                    TileVector[i].flagged = true;
                }
            }
            window.draw(faceWin.getSprite());

        }
        else if (loss == false) {
            window.draw(faceHappy.getSprite());

        }
        else {
            window.draw(faceLose.getSprite());

        }


        window.display();


    }
    return 0;
}



vector<SpriteObject>  initializeBoard(Board newBoard, vector<SpriteObject> TileVector) {

    int i = 0;
    for (int j = 0; j < newBoard.height; j++) {
        for (int k = 0; k < newBoard.width; k++) {
            //top left
            if (i == 0) {
                if (TileVector[i + 1].type == "mine") {

                    TileVector[i].mineCount += 1;

                }
                if (TileVector[newBoard.width].type == "mine") {

                    TileVector[i].mineCount += 1;
                }
                if (TileVector[newBoard.width + 1].type == "mine") {

                    TileVector[i].mineCount += 1;

                }



                TileVector[i].tiles.push_back(&TileVector[i + 1]);


                TileVector[i].tiles.push_back(&TileVector[newBoard.width]);


                TileVector[i].tiles.push_back(&TileVector[newBoard.width + 1]);


            }
            // top middle
            else if (i > 0 && i < newBoard.width - 1) {
                if (TileVector[i + 1].type == "mine") {
                    TileVector[i].mineCount += 1;

                }
                if (TileVector[i - 1].type == "mine") {
                    TileVector[i].mineCount += 1;

                }
                if (TileVector[i + newBoard.width].type == "mine") {
                    TileVector[i].mineCount += 1;

                }
                if (TileVector[i + newBoard.width - 1].type == "mine") {
                    TileVector[i].mineCount += 1;

                }
                if (TileVector[i + newBoard.width + 1].type == "mine") {
                    TileVector[i].mineCount += 1;

                }


                TileVector[i].tiles.push_back(&TileVector[i + 1]);

                TileVector[i].tiles.push_back(&TileVector[i - 1]);


                TileVector[i].tiles.push_back(&TileVector[i + newBoard.width + 1]);

                TileVector[i].tiles.push_back(&TileVector[i + newBoard.width - 1]);


                TileVector[i].tiles.push_back(&TileVector[i + newBoard.width]);

            }
            // top right
            else if (i == newBoard.width - 1) {
                if (TileVector[i - 1].type == "mine") {
                    TileVector[i].mineCount += 1;

                }
                if (TileVector[i + newBoard.width].type == "mine") {
                    TileVector[i].mineCount += 1;

                }
                if (TileVector[i + newBoard.width - 1].type == "mine") {
                    TileVector[i].mineCount += 1;

                }

                TileVector[i].tiles.push_back(&TileVector[i - 1]);



                TileVector[i].tiles.push_back(&TileVector[i + newBoard.width - 1]);


                TileVector[i].tiles.push_back(&TileVector[i + newBoard.width]);

            }
            if (i >= newBoard.width && i < (newBoard.height * newBoard.width) - (newBoard.width)) {
                // middle left

                if (i == j * newBoard.width) {
                    if (TileVector[i + 1].type == "mine") {
                        TileVector[i].mineCount += 1;
                    }
                    if (TileVector[i - newBoard.width].type == "mine") {
                        TileVector[i].mineCount += 1;
                    }

                    if (TileVector[i - newBoard.width + 1].type == "mine") {
                        TileVector[i].mineCount += 1;
                    }
                    if (TileVector[i + newBoard.width].type == "mine") {
                        TileVector[i].mineCount += 1;
                    }

                    if (TileVector[i + newBoard.width + 1].type == "mine") {
                        TileVector[i].mineCount += 1;
                    }


                    TileVector[i].tiles.push_back(&TileVector[i + 1]);


                    TileVector[i].tiles.push_back(&TileVector[i - newBoard.width]);



                    TileVector[i].tiles.push_back(&TileVector[i - newBoard.width + 1]);


                    TileVector[i].tiles.push_back(&TileVector[i + newBoard.width]);


                    TileVector[i].tiles.push_back(&TileVector[i + newBoard.width + 1]);




                }
                // middle mid

                else if (i == (j * newBoard.width) + newBoard.width - 1) {
                    if (TileVector[i - 1].type == "mine") {
                        TileVector[i].mineCount += 1;
                    }
                    if (TileVector[i - newBoard.width].type == "mine") {
                        TileVector[i].mineCount += 1;
                    }
                    if (TileVector[i - newBoard.width - 1].type == "mine") {
                        TileVector[i].mineCount += 1;
                    }

                    if (TileVector[i + newBoard.width].type == "mine") {
                        TileVector[i].mineCount += 1;
                    }
                    if (TileVector[i + newBoard.width - 1].type == "mine") {
                        TileVector[i].mineCount += 1;
                    }



                    TileVector[i].tiles.push_back(&TileVector[i - 1]);


                    TileVector[i].tiles.push_back(&TileVector[i - newBoard.width]);


                    TileVector[i].tiles.push_back(&TileVector[i - newBoard.width - 1]);


                    TileVector[i].tiles.push_back(&TileVector[i + newBoard.width]);


                    TileVector[i].tiles.push_back(&TileVector[i + newBoard.width - 1]);



                }
                // middle right

                else {
                    if (TileVector[i - newBoard.width].type == "mine") {
                        TileVector[i].mineCount += 1;
                    }
                    if (TileVector[i - newBoard.width - 1].type == "mine") {
                        TileVector[i].mineCount += 1;
                    }
                    if (TileVector[i - newBoard.width + 1].type == "mine") {
                        TileVector[i].mineCount += 1;
                    }
                    if (TileVector[i + newBoard.width].type == "mine") {
                        TileVector[i].mineCount += 1;
                    }
                    if (TileVector[i + newBoard.width - 1].type == "mine") {
                        TileVector[i].mineCount += 1;
                    }
                    if (TileVector[i + newBoard.width + 1].type == "mine") {
                        TileVector[i].mineCount += 1;
                    }
                    if (TileVector[i - 1].type == "mine") {
                        TileVector[i].mineCount += 1;
                    }
                    if (TileVector[i + 1].type == "mine") {
                        TileVector[i].mineCount += 1;
                    }




                    TileVector[i].tiles.push_back(&TileVector[i - newBoard.width]);


                    TileVector[i].tiles.push_back(&TileVector[i - newBoard.width - 1]);


                    TileVector[i].tiles.push_back(&TileVector[i - newBoard.width + 1]);


                    TileVector[i].tiles.push_back(&TileVector[i + newBoard.width]);


                    TileVector[i].tiles.push_back(&TileVector[i + newBoard.width - 1]);


                    TileVector[i].tiles.push_back(&TileVector[i + newBoard.width + 1]);


                    TileVector[i].tiles.push_back(&TileVector[i - 1]);

                    TileVector[i].tiles.push_back(&TileVector[i + 1]);


                }
            }

            if (i == (newBoard.height * newBoard.width) - newBoard.width) {
                // bottom left

                if (TileVector[i + 1].type == "mine") {
                    TileVector[i].mineCount += 1;
                }
                if (TileVector[i - newBoard.width].type == "mine") {
                    TileVector[i].mineCount += 1;
                }
                if (TileVector[i - newBoard.width + 1].type == "mine") {
                    TileVector[i].mineCount += 1;
                }



                TileVector[i].tiles.push_back(&TileVector[i + 1]);


                TileVector[i].tiles.push_back(&TileVector[i - newBoard.width]);


                TileVector[i].tiles.push_back(&TileVector[i - newBoard.width + 1]);


            }
            // bottom mid
            else if (i > (newBoard.height * newBoard.width) - newBoard.width && i < (newBoard.height * newBoard.width) - 1) {
                if (TileVector[i + 1].type == "mine") {
                    TileVector[i].mineCount += 1;
                }
                if (TileVector[i - 1].type == "mine") {
                    TileVector[i].mineCount += 1;
                }
                if (TileVector[i - newBoard.width].type == "mine") {
                    TileVector[i].mineCount += 1;
                }
                if (TileVector[i - newBoard.width - 1].type == "mine") {
                    TileVector[i].mineCount += 1;
                }
                if (TileVector[i - newBoard.width + 1].type == "mine") {
                    TileVector[i].mineCount += 1;
                }



                TileVector[i].tiles.push_back(&TileVector[i + 1]);


                TileVector[i].tiles.push_back(&TileVector[i - 1]);


                TileVector[i].tiles.push_back(&TileVector[i - newBoard.width]);


                TileVector[i].tiles.push_back(&TileVector[i - newBoard.width - 1]);


                TileVector[i].tiles.push_back(&TileVector[i - newBoard.width + 1]);


            }
            // bottom left

            else if (i == (newBoard.height * newBoard.width) - 1) {
                if (TileVector[i - 1].type == "mine") {
                    TileVector[i].mineCount += 1;
                }
                if (TileVector[i - newBoard.width].type == "mine") {
                    TileVector[i].mineCount += 1;
                }
                if (TileVector[i - newBoard.width - 1].type == "mine") {
                    TileVector[i].mineCount += 1;
                }



                TileVector[i].tiles.push_back(&TileVector[i - 1]);


                TileVector[i].tiles.push_back(&TileVector[i - newBoard.width]);


                TileVector[i].tiles.push_back(&TileVector[i - newBoard.width - 1]);

            }

            if (TileVector[i].mineCount > 0) {
                if (TileVector[i].type != "mine") {

                    int number = (int)TileVector[i].mineCount;
                    string name = "number_";
                    name += to_string(number);

                    SpriteObject num(name);
                    TileVector[i].TSprite = num.TSprite;
                    TileVector[i].type = num.type;
                    TileVector[i].isNumber = true;
                }
            }
            i++;

        }
    }

    return TileVector;
}
vector<string> initializeSprites(Board newBoard, vector<string> SpritesVector) {
    for (int i = 0; i < newBoard.MineSweeperMap.size(); i++) {
        if (newBoard.MineSweeperMap[i] == '0') {
            SpritesVector.push_back("tile_hidden");
        }
        else {
            SpritesVector.push_back("mine");
        }
    }
    return SpritesVector;
}
Board chooseBoard(Board newBoard, string file) {
    newBoard.readData();
    string fileName = "boards/";
    fileName += file;
    newBoard.loadMap(fileName);

    return newBoard;
}
vector<SpriteObject> mouseFunc(sf::Event event, sf::Vector2i mousePos, vector<SpriteObject> TileVector) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Right) {
            for (int i = 0; i < TileVector.size(); i++) {
                if (TileVector[i].getRect().contains(sf::Vector2f(mousePos.x, mousePos.y))) {
                    if (TileVector[i].reveal == true) {

                    }
                    else if (TileVector[i].flagged == false) {
                        TileVector[i].flagged = true;
                        sleep_for(nanoseconds(10));

                    }
                    else {

                        TileVector[i].flagged = false;
                        sleep_for(nanoseconds(10));

                    }



                }
            }
        }


        if (event.mouseButton.button == sf::Mouse::Left) {

            for (int i = 0; i < TileVector.size(); i++) {
                if (TileVector[i].getRect().contains(sf::Vector2f(mousePos.x, mousePos.y))) {

                    if (TileVector[i].flagged == false) {
                        TileVector[i].reveal = true;
                    }
                    vector<int> list;
                    recursionReveal(TileVector[i], list);



                }
            }

        }


    }
    return TileVector;
}

vector<SpriteObject> DebugMode(sf::Event event, sf::Vector2i mousePos, SpriteObject Debug, vector<SpriteObject> TileVector) {
    if (event.type == sf::Event::MouseButtonPressed) {


        if (event.mouseButton.button == sf::Mouse::Left) {

            if (Debug.getRect().contains(sf::Vector2f(mousePos.x, mousePos.y))) {

                sleep_for(nanoseconds(10));

                for (int i = 0; i < TileVector.size(); i++) {
                    if (TileVector[i].type == "mine") {
                        if (TileVector[i].debug == false) {
                            TileVector[i].debug = true;
                        }
                        else {
                            TileVector[i].debug = false;

                        }
                    }
                }
            }
        }



    }
    return TileVector;
}
vector<SpriteObject> buttons(sf::Event event, sf::Vector2i mousePos, SpriteObject Test1, SpriteObject Test2, SpriteObject Test3, SpriteObject faceHappy, vector<SpriteObject> TileVector) {


    if (event.type == sf::Event::MouseButtonPressed) {


        if (event.mouseButton.button == sf::Mouse::Left) {


            if (Test1.getRect().contains(sf::Vector2f(mousePos.x, mousePos.y))) {

                Board test1;
                vector<string> SpritesVector1;
                vector<SpriteObject> testVector;
                test1 = chooseBoard(test1, "testboard1.brd");
                test1.width = getWidth();
                test1.height = getHeight();
                test1.mineCount = getMineCount();

                SpritesVector1 = initializeSprites(test1, SpritesVector1);
                for (int i = 0; i < SpritesVector1.size(); i++) {
                    string name = SpritesVector1[i];
                    SpriteObject object(name);
                    testVector.push_back(object);


                }
                testVector = initializeBoard(test1, testVector);

                return testVector;
            }

            if (Test2.getRect().contains(sf::Vector2f(mousePos.x, mousePos.y))) {
                Board test2;
                vector<string> SpritesVector2;
                vector<SpriteObject> testVector2;
                test2 = chooseBoard(test2, "testboard2.brd");
                test2.width = getWidth();
                test2.height = getHeight();
                test2.mineCount = getMineCount();

                SpritesVector2 = initializeSprites(test2, SpritesVector2);
                for (int i = 0; i < SpritesVector2.size(); i++) {
                    string name = SpritesVector2[i];
                    SpriteObject object(name);
                    testVector2.push_back(object);


                }
                testVector2 = initializeBoard(test2, testVector2);


                return testVector2;



            }

            if (Test3.getRect().contains(sf::Vector2f(mousePos.x, mousePos.y))) {

                Board test3;
                vector<string> SpritesVector3;
                vector<SpriteObject> testVector3;
                test3 = chooseBoard(test3, "testboard3.brd");
                test3.width = getWidth();
                test3.height = getHeight();
                test3.mineCount = getMineCount();

                SpritesVector3 = initializeSprites(test3, SpritesVector3);
                for (int i = 0; i < SpritesVector3.size(); i++) {
                    string name = SpritesVector3[i];
                    SpriteObject object(name);
                    testVector3.push_back(object);


                }
                testVector3 = initializeBoard(test3, testVector3);



                return testVector3;


            }


            if (faceHappy.getRect().contains(sf::Vector2f(mousePos.x, mousePos.y))) {

                Board newBoard;
                vector<string> SpritesVector;
                vector<SpriteObject> newObj;
                newBoard.width = getWidth();
                newBoard.height = getHeight();
                newBoard.mineCount = getMineCount();

                newBoard.randomMap();
                SpritesVector = initializeSprites(newBoard, SpritesVector);
                for (int i = 0; i < SpritesVector.size(); i++) {
                    string name = SpritesVector[i];
                    SpriteObject object(name);
                    newObj.push_back(object);
                }
                newObj = initializeBoard(newBoard, newObj);
                return newObj;
            }
        }
    }

    return TileVector;
}
bool resetClick(sf::Event event, sf::Vector2i mousePos, SpriteObject Test1, SpriteObject Test2, SpriteObject Test3, SpriteObject Debug, SpriteObject faceLose, SpriteObject faceHappy, SpriteObject faceWin) {
    if (event.type == sf::Event::MouseButtonPressed) {


        if (event.mouseButton.button == sf::Mouse::Left) {


            if (Test1.getRect().contains(sf::Vector2f(mousePos.x, mousePos.y))) {



                return true;
            }

            if (Test2.getRect().contains(sf::Vector2f(mousePos.x, mousePos.y))) {


                return true;



            }

            if (Test3.getRect().contains(sf::Vector2f(mousePos.x, mousePos.y))) {


                return true;


            }

            if (Debug.getRect().contains(sf::Vector2f(mousePos.x, mousePos.y))) {
                return false;
            }
            if (faceLose.getRect().contains(sf::Vector2f(mousePos.x, mousePos.y))) {
                return true;
            }
            if (faceHappy.getRect().contains(sf::Vector2f(mousePos.x, mousePos.y))) {
                return true;
            }
            if (faceWin.getRect().contains(sf::Vector2f(mousePos.x, mousePos.y))) {
                return true;
            }
        }
        return false;
    }

}
void recursionReveal(SpriteObject& TileVector, vector<int> numbers) {
    for (int i = 0; i < TileVector.tiles.size(); i++) {
        if (TileVector.tiles[i]->type != "mine" && TileVector.tiles[i]->flagged == false && TileVector.tiles[i]->reveal == false) {
            if (TileVector.tiles[i]->isNumber == true) {
                cout << TileVector.tiles[i]->index << endl;
                TileVector.tiles[i]->reveal = true;
                numbers.push_back(TileVector.tiles[i]->index);
            }
            else {
                TileVector.tiles[i]->reveal = true;
                cout << TileVector.tiles[i]->index << endl;

                recursionReveal(*TileVector.tiles[i], numbers);
                numbers.push_back(TileVector.tiles[i]->index);

            }
        }
        else {
        }
    }


}
