#include <string>
/*
int a, b, c;  

int** a, b, c -> int **a, b, c; 
*/
class board{
    private:
        //member elements
        bool **grid; 
        int rows; 
        int cols; 
        
        friend std::ostream& operator<<(std::ostream& os, board &a);

        

    public:
        //constructor
        board(int rows = 10, int cols = 10); 
        board(std::string filename); 
   
        //getMethods
        bool** getGrid();
        int getRows();
        int getCols();

        //functions  
        bool withinBounds(int row, int col); 
        int countNeighbor(int row, int col);
        bool determineState(int row, int col); 
        void updateBoard(); 
        void printBoard(bool debug = false);
        
        //destructor 
        ~board();
};