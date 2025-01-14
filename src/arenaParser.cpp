#include <bits/stdc++.h>

#include "../include/arenaParser.h"
#include "../include/arena.h"
#include "../include/player.h"
#include "../include/tinyxml2.h"

#define BACKGROUND_COLOR "blue"
#define PLAYER_COLOR "green"

void parserXmlFile(const char* path, Arena* &arena, Player* &player){
    FILE * fp;
    fp = fopen(path , "r");
    if (fp == NULL) {
        perror ("Error opening file");
        exit(1);
    }

    tinyxml2::XMLDocument doc;

    if (doc.LoadFile(fp) != tinyxml2::XML_SUCCESS) {
        std::cerr << "Erro ao carregar o arquivo XML: " << doc.ErrorStr() << std::endl;
        exit(1);
    }

    tinyxml2::XMLElement* root = doc.RootElement();
    if (!root) {
        std::cerr << "Erro ao obter o elemento raiz." << std::endl;
        exit(1);
    }

    tinyxml2::XMLElement* background = NULL;
    std::vector<tinyxml2::XMLElement*> obstacles;
    for (tinyxml2::XMLElement* rectElement = root->FirstChildElement("rect");
        rectElement != nullptr;
        rectElement = rectElement->NextSiblingElement("rect")){
            
        const char* fill = rectElement->Attribute("fill");

        if(strcmp(fill, BACKGROUND_COLOR) == 0) background = rectElement;
        else obstacles.push_back(rectElement);
    }

    float bgWidth = background->FloatAttribute("width");
    float bgHeight = background->FloatAttribute("height");

    float diffCenterX = 0.0 - (background->FloatAttribute("x") + (bgWidth/2));
    float diffCenterY = 0.0 + (background->FloatAttribute("y") + (bgHeight/2));

    // cout << "diff x " << diffCenterX << " diff y " << diffCenterY << endl;

    arena = new Arena(
        bgWidth/bgHeight,
        1.0,
        -(bgWidth/bgHeight)/2,
        0.5
    );

    float attributeX, attributeY; 
    for(auto rect : obstacles){
        attributeX = (rect->FloatAttribute("x") + diffCenterX)/bgHeight;
        attributeY = (-rect->FloatAttribute("y") + diffCenterY)/bgHeight;

        arena->addObstacles(
            Rectangle(
                rect->FloatAttribute("width")/bgHeight,
                rect->FloatAttribute("height")/bgHeight,
                attributeX,
                attributeY,
                1,
                1.0,
                0.0,
                0.0
            )
        );
    }

    for (tinyxml2::XMLElement* circleElement = root->FirstChildElement("circle");
        circleElement != nullptr;
        circleElement = circleElement->NextSiblingElement("circle")){

        const char* fill = circleElement->Attribute("fill");

        if(strcmp(fill, PLAYER_COLOR) == 0){
            player = new Player(
                (circleElement->FloatAttribute("cx") + diffCenterX)/bgHeight,
                (-circleElement->FloatAttribute("cy") + diffCenterY)/bgHeight,
                2,
                circleElement->FloatAttribute("r")*2/bgHeight
            );
        }
        else {
            arena->addEnemy(
                Player(
                    (circleElement->FloatAttribute("cx") + diffCenterX)/bgHeight,
                    (-circleElement->FloatAttribute("cy") + diffCenterY)/bgHeight,
                    2,
                    circleElement->FloatAttribute("r")*2/bgHeight
                )
            );
        }
    }
}