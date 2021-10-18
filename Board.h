#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <iostream>
#include <vector>


using namespace std;
class Board {

private:
  

public:
    int width;
    int height;
    int mineCount;
    int tileCount;

    vector<char> MineSweeperMap;
    unordered_map<int, sf::Texture> MineMap;
    vector<Board*> board;
    int getWidth();
    int getHeight();
    int getMineCount();

    void randomMap();
    void loadMap(string fileName);
    void readData();

    Board();

};

