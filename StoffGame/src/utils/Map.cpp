#include "Map.h"

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

Map::Map()
{
}

Map::Map(const char* filePath)
{
    static std::unordered_map<char, TileType> tokenToTypes;
    tokenToTypes['D'] = DEFAULT;
    tokenToTypes['E'] = EMPTY;
    tokenToTypes['q'] = TOP_LEFT;
    tokenToTypes['w'] = TOP_MID;
    tokenToTypes['e'] = TOP_RIGHT;
    tokenToTypes['a'] = MID_LEFT;
    tokenToTypes['s'] = MID_MID;
    tokenToTypes['d'] = MID_RIGHT;
    tokenToTypes['z'] = BOT_LEFT;
    tokenToTypes['x'] = BOT_MID;
    tokenToTypes['c'] = BOT_RIGHT;

    std::ifstream mapFile;
    mapFile.open(filePath, std::ios::binary);
    if (!mapFile.is_open()) std::cout << "couldnt open map file." << std::endl;
    else
    {
        std::string rowTokens;
        while (std::getline(mapFile, rowTokens))
        {
            std::vector<TileType> rowTiles;
            for (char token : rowTokens) rowTiles.push_back(tokenToTypes[token]);
            m_tiles.push_back(rowTiles);
        }
    }
    mapFile.close();
}
std::vector<std::vector<TileType>> Map::GetTiles()
{
    return m_tiles;
}
