#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
using std::unordered_map;
using std::string;

class SpriteObject
{

public:

	sf::Sprite TSprite;
    int index;
    int x;
    int y;
	string type;
	bool reveal = false;
	bool flagged = false;
	int mineCount = 0;
    bool debug = false;
    bool isNumber = false;

	vector<SpriteObject*> tiles;
	int neighborsSize = tiles.size();
	void setRect(int number);
	sf::Sprite getSprite();
	SpriteObject(string textureName);
	void setPos(int x, int y);
	void setPos(sf::Vector2f);

	sf::FloatRect getRect();

//    SpriteObject operator=(const SpriteObject &C);
	~SpriteObject();
};

struct Tiles {
	
};