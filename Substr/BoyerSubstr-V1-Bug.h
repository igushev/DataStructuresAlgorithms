#ifndef BOYER_SUBSTR
#define BOYER_SUBSTR

#include <string>
#include <algorithm>
#include <vector>

const int char_size = 256;

int boyer_substr( const std::string& text, const std::string& pattern )
{
  if (text.empty() || pattern.empty() || text.size() < pattern.size())
    return -1;

  //slide array
  //how to move pattern to fit the text with the last entry of a symbol
  std::vector<int> slide(char_size);
  for (int i = 0; i < char_size; ++i)
    slide[i] = pattern.length();

  for (int i = 0; i < pattern.size(); ++i)
    slide[pattern[i]] = pattern.size() - i - 1;

  //jump
  //how to move pattern considering previous match
  std::vector<int> jump(pattern.size());
  for (int i = 0; i < pattern.size(); ++i)
    jump[i] = 2*pattern.size() - i - 1;

  std::vector<int> matches(pattern.size());
  int curr = pattern.size() - 1;
  int match = curr + 1; //doesn't match anything
  while (curr >= 0) {
    while (match < pattern.size() && pattern[curr] != pattern[match]) {
      jump[match] = std::min(jump[match], int(pattern.size() - curr - 1));
      match = matches[match];
    }
    matches[curr] = match;
    --curr;
    --match;
  }

  int curr_match = matches[0];
  for (int i = 0; i < pattern.size(); ++i) {
    jump[i] = std::min(jump[i], int(pattern.size() + curr_match - i));
    if (curr_match == i)
      curr_match = matches[curr_match];
  }

  //check for match using slide and jump
  int text_i = pattern.size() - 1;
  while (text_i < text.size()) {
    int pattern_i = pattern.size() - 1;
    while (pattern_i >= 0 && text[text_i] == pattern[pattern_i]) {
      --text_i;
      --pattern_i;
    }

    if (pattern_i < 0)
      return text_i + 1;

    text_i += std::max(slide[pattern[pattern_i]], jump[pattern_i]);
  }
  return -1;
}

#endif
