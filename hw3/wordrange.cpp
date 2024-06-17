#include <iostream> 
#include <fstream>
#include <string>
// #include <sstream>

using namespace std;

struct TreeNode {
  std::string word;
  TreeNode* left;
  TreeNode* right;

  TreeNode(const string& w) : word(w), left(nullptr), right(nullptr) {}

};

class BST{

public:
  BST() : root(nullptr){}

  void insert(const string&word) 
  {
    // public method to insert the word into the tree
    root = insert(root, word);
  }

  int rangeQuery(const string& str1, const string& str2)
  {
    return rangeQuery(root, str1, str2);
  }

private:
  TreeNode* root;

  //recursively insert the word into the tree
  TreeNode* insert(TreeNode* node, const string& word) // pointer to the root node of the tree
  {
    if(!node){
      return new TreeNode(word);
    }
    if (word <node ->word){
      node -> left = insert(node->left, word);
    } else if (word > node->word) {
      node->right = insert(node->right, word);
    }
    return node;
  }
  int rangeQuery(TreeNode* node, const string& str1, const string& str2){
    if(!node){
      return 0;
    }
    if(node->word <str1){
      return rangeQuery(node->right, str1, str2);
    } else if(node -> word >str2){
      return rangeQuery(node->left, str1, str2);
    } else {
      return 1 +rangeQuery(node->left, str1, str2)+ rangeQuery(node -> right, str1, str2);
    }

  }
};

int main(int argc, char* argv[]){
  if(argc != 3){
    return 1;
  }

  ifstream inputFile(argv[1]);
  if(!inputFile.is_open()){
    cerr << "Error opening input file.";
    return 1;
  }
  ofstream outputFile(argv[2]);
  
  BST bst; // create our BST object

  string line;
  while(getline(inputFile, line)){
    if(line[0] == 'i'){
      string word = line.substr(2);
      bst.insert(word);
      // cout << word << endl;

    /*} else if (line[0] == 'r'){
      size_t pos = line.find(' ', 2);
      bst.insert(word);*/
    } else if(line[0] == 'r'){
      size_t pos = line.find(' ',2);
      string str1, str2;
      str1 = line.substr(2, pos -2);
      str2 = line.substr(pos +1);
      int result = bst.rangeQuery(str1, str2);
      outputFile << result << "\n";

    }
    /*
    if (command == 'i'){
      string word;
      ss >> word;
      bst.insert(word);
    } else if (command == 'r'){
      string str1, str2;
      ss >> str1 >> str2;
      int result = bst.rangeQuery(str1, str2);
      outputFile << result << '\n';
    }
    */

  }
  inputFile.close();
  outputFile.close();
  return 0;
}