#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>


using namespace std;

struct ListNode{
  string word;
  int count;
  ListNode* next;
  ListNode(string word) : word(word), count(1), next(nullptr){}


};

void addword(ListNode*& head, const string& word){
  ListNode* current = head;
  ListNode* prev = nullptr;
  while (current != nullptr){
    if (current -> word == word){
      //cout << "word added: " <<word << "count: " << current ->count << endl;
      current -> count++;
      return;
    }
    prev = current;
    current = current -> next;
  }
  ListNode* newNode = new ListNode(word);
  if (prev != nullptr){
    prev -> next = newNode;
  } else {
    head = newNode;
  }

}

void insertsorted(ListNode*& sortedHead, ListNode* newNode){
  if(sortedHead == nullptr || sortedHead -> count < newNode -> count || (sortedHead -> count == newNode -> count && sortedHead -> word.compare(newNode -> word) > 0)){
    newNode -> next = sortedHead;
    sortedHead = newNode;
  } else {
    ListNode* current = sortedHead;
    while (current -> next != nullptr && 
            (current -> next -> count> newNode -> count || 
              (current -> next -> count == newNode -> count && 
                current -> next -> word.compare(newNode -> word)<0))){
      current = current -> next;
    }
    newNode -> next = current -> next;
    current -> next = newNode;
  }
}

void freeList(ListNode* head){
  while (head != nullptr){
    ListNode* nextNode = head -> next;
    delete head;
    head = nextNode;
  }
}

//void processinput(const string& inputFilePath, const  string& outputFilePath)

int main(int argc, char** argv){
  if (argc <3){
    throw invalid_argument("./bard <inputfile> <outputfile");
  }
  ifstream file("shakespeare-cleaned5.txt");
  if (!file.is_open()){
    cerr << "Error opening  file" << endl;
    return 1;
  }
  string inputFilePath = argv[1];
  string outputFilePath = argv[2];


  ifstream inputFile(inputFilePath);
  ofstream outputFile(outputFilePath);

  string word;
  ListNode* head = nullptr;
  while (file >> word){
    addword(head, word);
  }

  ListNode* sorted = nullptr;
  ListNode* current = head;
  ListNode* next = nullptr;
  while(current != nullptr){
    next = current -> next;
    insertsorted(sorted, current);
    current = next;

  }
  head = sorted;

  int length;
  int rank;
  while(inputFile >> length >> rank){
    int currentRank = 0;
    ListNode* current = head;
    string result = "-";
    cout << length <<" "<< rank << endl;

    while (current != nullptr){
      if (current-> word.length() == static_cast<size_t>(length)){
        if (currentRank == rank){
          result = current->word;
          break;
        }
        currentRank++;
      }
      current = current -> next;

    }
    //cout << result << endl;
    outputFile << result << endl;
  }

  /*
  ListNode* current = head;
  while (current != nullptr){
    cout << current -> word << " count " << current -> count << endl;
    current = current -> next;
  }
  */

  freeList(head);
  head = nullptr;
  inputFile.close();
  outputFile.close();

  return 0;
}