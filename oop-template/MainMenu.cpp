#include "MainMenu.h"
#include <iostream>

//constructor
MainMenu::MainMenu(float width, float hight){
     if(!font.loadFromFile("arial.ttf")){
        std::cout << "Error loading font\n";
}

//Play
    mainMenu[0].setFont(font);
    mainMenu[0].setFillColor(sf::Color::White);
    mainMenu[0].setString("Play");
    mainMenu[0].setCharacterSize(70);
    mainMenu[0].setPosition(400,700);

//Exit
    mainMenu[1].setFont(font);
    mainMenu[1].setFillColor(sf::Color::White);
    mainMenu[1].setString("Exit");
    mainMenu[1].setCharacterSize(70);
    mainMenu[1].setPosition(400, 300);

    MainMenuSelected = -1;

}

//methods

void MainMenu::draw(sf::RenderWindow &window){
    for(int i = 0; i < 2; i++){
        window.draw(mainMenu[i]);
    }
}

void MainMenu::moveUp(){
    //verif daca nu trece peste primul element
    if(MainMenuSelected - 1 >= 0){
        //reset culoarea textului anterior
        mainMenu[MainMenuSelected].setFillColor(sf::Color::White);
        MainMenuSelected--;
        mainMenu[MainMenuSelected].setFillColor(sf::Color::Black);
    }
}

void MainMenu::moveDown(){
    if(MainMenuSelected + 1 < 2){
        mainMenu[MainMenuSelected].setFillColor(sf::Color::White);
        MainMenuSelected++;
        mainMenu[MainMenuSelected].setFillColor(sf::Color::Black);
    }
}

int MainMenu::MainMenuPressed() {
    return MainMenuSelected;
}


//destructor
MainMenu::~MainMenu() {

}