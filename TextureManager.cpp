#include "TextureManager.h"

unordered_map<string, sf::Texture> TextureManager::textures;
string TextureManager::directory;

void TextureManager::loadTexture(string textureName) {
    string path = directory;
    path += textureName;
    path += ".png";

    textures[textureName].loadFromFile(path);
}

sf::Texture &TextureManager::getTexture(string textureName) {
    if( textures.find(textureName) == textures.end() ) {
        loadTexture(textureName);
    }

    return textures[textureName];
}
void TextureManager::Clear() {
    textures.clear();
}
void TextureManager::setDirectory(string directoryName) {
    directory = directoryName;
}