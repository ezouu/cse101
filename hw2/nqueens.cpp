#include <iostream> 
#include <fstream> 
#include <vector> 
#include <algorithm> 
#include <stack> 

struct Position {
  int x, y; 
  Position (int x, int y) : x(x), y(y){}
};

bool isSafe(int row, int col, const std::vector<Position>& positions){
  for (const auto& pos: positions){
    if (col == pos.x || row == pos.y || abs(row-pos.y) == abs(col - pos.x))
      return false;
  }
  return true;
}

bool solveNQueens(int col, int n, std:: vector<Position>& positions, std:: vector<Position>& solution){
  
  if (col > n){
    solution = positions;
    return true;
  }
  for (const auto& pos : positions){
    if (pos.x == col){
      return solveNQueens(col +1, n, positions, solution);
    }
  }
  for ( int row = 1; row <= n; row++){
    if(isSafe(row, col, positions)){
      positions.push_back(Position(col , row));
      if (solveNQueens(col +1, n, positions, solution)){
        return true;
      }
      positions.pop_back();
    }
  }
  return false;
}

int main(int argc, char* argv[]){
  if (argc <3){
    std::cerr <<"Usage: " << argv[0] << " <input file> <output file>\n";
    return 1;
  }
  std::ifstream infile(argv[1]);
  std::ofstream outfile(argv[2]);
  int n, x, y;

  while(infile >> n){
    std::vector<Position> initial;
    std::vector<Position> solution;
    while (infile.peek() != '\n' && infile >> x >> y){
      initial.push_back(Position(x, y));
    }
    if (solveNQueens(1, n, initial, solution)){
      std:: sort(solution.begin(), solution.end(), [](const Position& a, const Position& b){
        return a.x < b.x;
      });
      for (auto& pos : solution){
        outfile << pos.x << " " << pos.y << " ";

      }
      outfile << "\n";
    } else {
        outfile << "No solution\n";
    }
  }
  return 0;
}