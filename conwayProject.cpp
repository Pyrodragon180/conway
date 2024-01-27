#include "conwayProject.h"
#include <iostream> 
#include <vector>
#include <fstream>


//Constructors
board::board(int rows,int cols) {
    this->rows = rows;
    this->cols = cols;
    this->grid = new bool*[rows]; 
    for (int i = 0; i < rows; i++) {
        this->grid[i] = new bool[cols];
    }
}

//reads in a board from a file 
board::board(std::string filename){
    std::ifstream file(filename); 
    if(file.is_open()){
        std::vector< std::vector<bool> > temp; 
        std::string line;    

        while(std::getline(file, line)) {
            std::vector<bool> row; 
            for(int i = 0; i < line.length(); i++) {
                row.push_back(line[i] == '#'); 
            } 
            temp.push_back(row);
        } 

        //now copy it into our grid  
        this->rows = temp.size(); 
        this->cols = temp[0].size(); 
        this->grid = new bool*[this->rows]; 
        for(int i = 0; i < this->rows; i++){
            this->grid[i] = new bool[this->cols]; 
            for(int j = 0; j < this->cols; j++){
                this->grid[i][j] = temp[i][j]; 
            }
        }
    } 
    else{
        std::cout << "File not found\n";
    }   
}

std::ostream& operator<<(std::ostream& os, board &a) {
    for(int i = 0; i < a.rows; i++){
        for(int j = 0; j < a.cols; j++){
            os << ((a.grid[i][j]) ? "#" : ".");
        }
        std::cout << "\n";
    }
    return os; 
}

//Destructor
board::~board() {
    for (int i = 0; i < this->rows; i++) {
        delete[] this->grid[i];
    }
    delete[] this->grid;
}

//Get methods 
bool** board::getGrid(){
    return grid;
} 

int board::getRows(){
    return rows;
}

int board::getCols(){
    return cols;
} 


bool board::withinBounds(int row, int col){
    return !((row < 0) || (col < 0) || (row >= this->rows) || (col >= this->cols));
} 

//Functions 
int board::countNeighbor(int row, int col){
    int count = 0;
    for(int i = row - 1; i < row + 2; i++){
        for(int j = col - 1; j < col + 2; j++){
            if(withinBounds(i, j)){
                count += this->grid[i][j];
            }
        }
    }
    return count - this->grid[row][col];
} 

bool board::determineState(int row, int col){ 
    int neighbors = countNeighbor(row, col);
    bool state = this->grid[row][col];
    
    if (state) {  
        if(neighbors <= 1){
            return false;
        }
        if(neighbors >= 4){
            return false;
        } 
        if((neighbors == 3) || (neighbors == 2)){
            return true;
        } 
    } 
    
    if(neighbors == 3 && !state){
        return true;
    }
    return state;
}

void board::updateBoard(){
    std::vector<bool*> changes; 
    
    for(int i = 0; i < this->rows; i++){
        for(int j = 0; j < this->cols; j++){
            bool current = this->grid[i][j];
            if(determineState(i, j) != current){
                changes.push_back(&this->grid[i][j]);
            }
        }
    } 
     
    for(int i = 0; i <changes.size(); i++){
        *(changes[i]) = !(*changes[i]);
    }
}

void board::printBoard(bool debug){
    for(int i = 0; i < this->rows; i++){
        for(int j = 0; j < this->cols; j++){
            if (debug) {
                std::cout << this->grid[i][j];
            }
            else {
                std::cout << ((this->grid[i][j]) ? "#" : ".");
            }
        }
        std::cout << "\n";
    }
}