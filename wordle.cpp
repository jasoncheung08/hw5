#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>

#include <string>

#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// helper
int countChar(const string& s, char c) {
  int count = 0;
  for(char ch : s) {
    if(ch == c) count++;
  }
  return count;
}

void helper(string& current, int idx, string floating, const set<string>& dict, set<string>& results) {
  if (idx == current.size()) {
    bool valid = true;
    for(char c : floating) {
      if(countChar(current, c) < countChar(floating, c)) {
        valid = false;
        break;
      }
    }
    if(valid && dict.find(current) != dict.end()) {
      results.insert(current);
    }
    return;
  }

  if(current[idx] != '-') {
    helper(current, idx + 1, floating, dict, results);
  }
  else {
    for(char c = 'a'; c <= 'z'; ++c) {
      current[idx] = c;

      int pos = -1;
      for(size_t i = 0; i < floating.size(); ++i) {
        if(floating[i] == c) {
          pos = i;
          break;
        }
      }

      string newFloating = floating;
      if(pos != -1) {
        newFloating.erase(pos, 1);
      }

      helper(current, idx + 1, newFloating, dict, results);
    }
    current[idx] = '-';
  }
}

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    set<string> results;
    string current = in;
    helper(current, 0, floating, dict, results);
    return results;
}