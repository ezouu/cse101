#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
#include <numeric>


using namespace std;
//sing AdjList = unordered_map<string, vector<pair<string, string >>>;

void addEdge(unordered_map<string, vector<pair<string, string >>>& adjList, const string& movie, 
const string& actor1, const string& actor2) {
  adjList[actor1].emplace_back(actor2, movie);
  adjList[actor2].emplace_back(actor1, movie);

}

void buildGraph(unordered_map<string, vector<pair<string, string>>>& adjList, const string& filename){
  ifstream file(filename);
  string line;
  string movie;
  vector<string> actors;

  while(getline(file, line)){
    istringstream iss(line);
    actors.clear();
    iss >> movie;
    string actor;
    while(iss >> actor){
      for (const string& prev_actor : actors) {
        addEdge(adjList, movie, actor, prev_actor);
      }
      actors.push_back(actor);
    }

  }
  file.close();
  //return graph;
}

string findPath(const unordered_map<string, vector<pair<string, string>>>& adjList, const string& start, const string& end){
  if(start == end){
    return start;
  }
  
  if (adjList.find(start)== adjList.end() || adjList.find(end) == adjList.end()){
    return("Not present"); //check what should be here ltr
  }
  unordered_map<string, pair<string, string>> prev;
  queue<string> queue;
  queue.push(start);
  prev[start] = {"", ""};

  while(!queue.empty()){
    string current = queue.front();
    queue.pop();

    for(const auto&pair : adjList.at(current)){
      if (prev.find(pair.first)== prev.end()){
        prev[pair.first] = {current, pair.second};
        queue.push(pair.first);
        if(pair.first == end){
          vector<string> path;
          string at = end;
          while(at != start){
            path.push_back(" -(" + prev[at].second + ")- "+ at);
            at = prev[at].first;
          }
          path.push_back(start);
          reverse(path.begin(), path.end());
          return accumulate(next(path.begin()), path.end(), path[0]);

        }
      }

    }
  }
  return "Not present";

}


int main(int argc, char* argv[]){
  if(argc != 3){
    cerr << "args";
    return 1;
  }
  string datafile = "cleaned_movielist.txt";


  unordered_map<string, vector<pair<string, string>>> adjList;
  buildGraph(adjList, argv[1]);

  ifstream input(argv[1]);

  if(!input){
    cerr<< "error cant open file" << argv[1]<< endl;
    return 1;
  }
  ofstream output(argv[2]);
  if(!output){
    cerr<<"couldn't open file" << argv[2]<<endl;
    return 1;

  }
  
  string actor1, actor2;

  while(input >> actor1 >>actor2){
     output << findPath(adjList, actor1, actor2) << endl; 
  }
  /*output << "Ingrid_Bergman" << endl;
  cout << "Ingrid_Bergman" << endl;
  output << "Ingrid_Bergman" << endl;
  */
  input.close();
  output.close();
  return 0;
}