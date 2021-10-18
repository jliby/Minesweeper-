#include "SpriteObject.h"
#include "TextureManager.h"


SpriteObject::SpriteObject(string textureName){

    TextureManager textures;


    textures.setDirectory("images/");
    textures.loadTexture("debug");
    textures.loadTexture("digits");
    textures.loadTexture("face_happy");
    textures.loadTexture("face_lose");
    textures.loadTexture("face_win");
    textures.loadTexture("face_lose");
    textures.loadTexture("tile_hidden");
    textures.loadTexture("tile_revealed");
    textures.loadTexture("mine");
    textures.loadTexture("test_1");
    textures.loadTexture("test_2");
    textures.loadTexture("test_3");
    textures.loadTexture("flag");
    textures.loadTexture("number_1");
    textures.loadTexture("number_2");
    textures.loadTexture("number_3");
    textures.loadTexture("number_4");
    textures.loadTexture("number_5");
    textures.loadTexture("number_6");
    textures.loadTexture("number_7");
    textures.loadTexture("number_8");

    if (textureName == "debug") {
        TSprite.setTexture(TextureManager::getTexture("debug"));
        type = "debug";
        cout << "debug set" << endl;
    }
    if (textureName == "face_happy") {
        TSprite.setTexture(textures.getTexture("face_happy"));
        type = "face_happy";
    }

    if (textureName == "face_lose") {
        TSprite.setTexture(textures.getTexture("face_lose"));
        type = "face_lose";
    }
    if (textureName == "face_win") {
        TSprite.setTexture(textures.getTexture("face_win"));
        type = "face_win";
    }
    if (textureName == "tile_hidden") {
        TSprite.setTexture(textures.getTexture("tile_hidden"));
        type = "tile_hidden";
    }
    if (textureName == "tile_revealed") {
        TSprite.setTexture(textures.getTexture("tile_revealed"));
        type = "tile_revealed";
    } 
    if (textureName == "mine") {
        TSprite.setTexture(textures.getTexture("mine"));
        type = "mine";
    }
    if (textureName == "test_1") {
        TSprite.setTexture(textures.getTexture("test_1"));
        type = "test_1";
    }
    if (textureName == "test_2") {
        TSprite.setTexture(textures.getTexture("test_2"));
        type = "test_2";
    }
    if (textureName == "test_3") {
        TSprite.setTexture(textures.getTexture("test_3"));
        type = "test_3";
    }
    if (textureName == "flag") {
        TSprite.setTexture(textures.getTexture("flag"));
        type = "flag";
    }
    if (textureName == "number_1") {
        TSprite.setTexture(textures.getTexture("number_1"));
        type = "number_1";
    }
    if (textureName == "number_2") {
        TSprite.setTexture(textures.getTexture("number_2"));
        type = "number_2";
    }
    if (textureName == "number_3") {
        TSprite.setTexture(textures.getTexture("number_3"));
        type = "number_3";
    }
    if (textureName == "number_4") {
        TSprite.setTexture(textures.getTexture("number_4"));
        type = "number_4";
    }
    if (textureName == "number_5") {
        TSprite.setTexture(textures.getTexture("number_5"));
        type = "number_5";
    }
    if (textureName == "number_6") {
        TSprite.setTexture(textures.getTexture("number_6"));
        type = "number_6";
    }
    if (textureName == "number_7") {
        TSprite.setTexture(textures.getTexture("number_7"));
        type = "number_7";
    }    
    if (textureName == "number_8") {
        TSprite.setTexture(textures.getTexture("number_8"));
        type = "number_8";
    }

    if (textureName == "digits") {
        TSprite.setTexture(textures.getTexture("digits"));


    }
}


sf::Sprite SpriteObject::getSprite() {
    return TSprite;
}

sf::FloatRect SpriteObject::getRect() {
   return this->TSprite.getGlobalBounds();
}

void SpriteObject::setRect(int number) {
    TSprite.setTextureRect(sf::IntRect (21*number, 0, 21, 32));
}

SpriteObject::~SpriteObject() {

}
//SpriteObject SpriteObject::operator=(const SpriteObject &C) {
//    this->TSprite = C.TSprite;
//    this->flagged = C.flagged;
//    this->reveal = C.reveal;
//    this->debug = C.debug;
//    this->mineCount = C.mineCount;
//    this->x = C.x;
//    this->y = C.y;
//    this->neighborsSize = C.neighborsSize;
//}