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


// helper declaration
void generateWords(string& current, int index, multiset<char>& floating, const set<string>& dict, set<string>& results, int totalDashes);


// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    set<string> results;
    multiset<char> floatingSet;
    for (char c : floating) {
      floatingSet.insert(c);
    }

    string current = in;
    int dashCount = 0;
    for (char c : in) {
      if (c == '-') ++dashCount;
    }

    generateWords(current, 0, floatingSet, dict, results, dashCount);
    return results;
}

// recursive helper
void generateWords(string& current, int index, multiset<char>& floating, const set<string>& dict, set<string>& results, int totalDashes) {
  if (index == (int)current.size()) {
    if (floating.empty() && dict.find(current) != dict.end()) {
      results.insert(current);
    }
    return;
  }

  if (current[index] != '-') {
    generateWords(current, index + 1, floating, dict, results, totalDashes);
    return;
  }

  int remainingDashes = 0;
  for (int i = index; i < (int)current.size(); ++i) {
    if (current[i] == '-') remainingDashes++;
  }

  for (char c = 'a'; c <= 'z'; ++c) {
    bool isFloating = (floating.find(c) != floating.end());

    if ((int)floating.size() > remainingDashes) return;

    current[index] = c;

    if (isFloating) {
      floating.erase(floating.find(c));
      generateWords(current, index + 1, floating, dict, results, totalDashes);
      floating.insert(c);
    }
    else if ((int)floating.size() <= remainingDashes - 1) {
      generateWords(current, index + 1, floating, dict, results, totalDashes);
    }
  }

  current[index] = '-';
}