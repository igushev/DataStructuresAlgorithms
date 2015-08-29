#ifndef KNUTH_SUBSTR_H
#define KNUTH_SUBSTR_H

#include <string>
#include <vector>

int knuth_substr( const std::string& text, const std::string& pattern )
{

  if (text.empty() || pattern.empty() || text.size() < pattern.size())
    return -1;

  std::vector<int> moves;
  moves.resize(pattern.size());

  moves[0] = -1;

  for (int pattern_i = 1; pattern_i < pattern.size(); ++pattern_i) {
    int curr_move = moves[pattern_i-1];

    while (curr_move >= 0 && pattern[curr_move] != pattern[pattern_i-1])
      curr_move = moves[curr_move];

    moves[pattern_i] = curr_move+1;
  }

  int pattern_i = 0;
  for (int text_i = 0; text_i < text.size()-pattern.size()+1;) {
    while (pattern_i < pattern.size() && text[text_i] == pattern[pattern_i]) {
      ++text_i;
      ++pattern_i;
    }

    if (pattern_i == pattern.size())
      return text_i - pattern.size();

    if (moves[pattern_i] == -1) {
      ++text_i;
      pattern_i = 0;
    }
    else {
      pattern_i = moves[pattern_i];
    }
  }

  return -1;
}

#endif
