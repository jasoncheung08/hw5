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
void generateWords(const string& current, const string& floating, const set<string> dict, set<string>& results, size_t index) {
  if (index == current.size()) {
    if (floating.empty() && dict.find(current) != dict.end()) {
      results.insert(current);
    }
    return;
  }

  if (current[index] != '-') {
    generateWords(current, floating, dict, results, index + 1);
  }
  else {
    set<char> used;
    for (char c = 'a'; c <= 'z'; ++c) {
      if (used.count(c)) continue;
      used.insert(c);

      string next = current;
      next[index] = c;

      string nextFloating = floating;
      size_t pos = nextFloating.find(c);
      if (pos != string::npos) {
        nextFloating.erase(pos, 1);
      }

      int remainingBlanks = 0;
      for (size_t i = index + 1; i < current.size(); ++i) {
        if (current[i] == '-') ++remainingBlanks;
      }
      if (pos != string::npos || remainingBlanks >= int(nextFloating.size())) {
        generateWords(next, nextFloating, dict, results, index + 1);
      }
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