#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void generateWords(const std::string& current, const std::string& floating, const std::set<std::string>& dict, std::set<std::string>& results, int index) {
  if(index == current.size()) {
    string temp = current;
    for(char c : floating) {
      size_t found = temp.find(c);
      if (found != string::npos) {
        temp[found] = '*';
      }
      else {
        return;
      }
    }
    if (dict.find(current) != dict.end()) {
      results.insert(current);
    }
    return;
  }

  if (current[index] != '-') {
    generateWords(current, floating, dict, results, index + 1);
  }
  else {
    for (char c = 'a'; c <= 'z'; ++c) {
      std::string newCurrent = current;
      newCurrent[index] = c;

      std::string newFloating = floating;
      size_t fIndex = newFloating.find(c);
      if(fIndex != string::npos) {
        newFloating.erase(fIndex, 1);
      }

      generateWords(newCurrent, newFloating, dict, results, index + 1);
    }
  }
}

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    std::set<std::string> results;
    generateWords(in, floating, dict, results, 0);
    return results;
}

// Define any helper functions here
