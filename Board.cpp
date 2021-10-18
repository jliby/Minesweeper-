#include "Board.h"
#include <fstream>
#include <string>
#include "Random.h"
void Board::readData() {

    ifstream file("boards/config.cfg");
    string width_str;
    getline(file, width_str);
    this->width = stoi(width_str);
    string height_str;
    getline(file, height_str);
    this->height = stoi(height_str);
    string mineCount_str;
    getline(file, mineCount_str);
    this->mineCount = stoi(mineCount_str);

    file.close();
}

int Board::getMineCount() {
    return this->mineCount;
}

int Board::getHeight() {
    return (this->height * 32) + 88;;
}

int Board::getWidth() {
    return width * 32;
}

Board::Board() {
    this->width = 0;
    this->height = 0;
    this->mineCount = 0;
    this->tileCount = 0;

}

void Board::loadMap(string fileName) {
    ifstream file(fileName);
    string line;
    char value;
    while(getline(file, line)){
        for(int i = 0; i < line.size(); i++) {
            value =  (char) line[i];
            MineSweeperMap.push_back(value);
        }
    }


}

void Board::randomMap() {
    int size = height * width;
    for(int i = 0; i < size; i++) {
        MineSweeperMap.push_back('0');
    }
    int count =0;
    while( count < this->mineCount) {
        int pos = Random::Number(0, size - 1);
        if(MineSweeperMap[pos] == '1') {

        } else {
            MineSweeperMap[pos] = '1';
            count++;
        }
    }
 }