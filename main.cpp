#include <iostream>
#include <string> 
#include "conwayProject.h" 

int main() { 
    std::string filename; 
    std::cout << "Enter Filename: " << std::endl;
    std::cin >> filename; 

    board game(filename); 
    std::cout << "Press 'q' to quit" << std::endl;

    while(std::cin.get() != 'q') {
       std::cout << "\n";
       game.updateBoard(); 
       std::cout << game; 
    } 
    
    return 0;
}
