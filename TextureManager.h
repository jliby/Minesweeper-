#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <iostream>
#include <string>
using namespace std;
class TextureManager{
    static string directory;

public:
    static unordered_map<string, sf::Texture> textures;

      void setDirectory(string directoryName);
     static void loadTexture(string textureName);
     static sf::Texture &getTexture(string textureName);
     static void Clear();
};