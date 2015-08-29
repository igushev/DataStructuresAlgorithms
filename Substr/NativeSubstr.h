#ifndef NATIVE_SUBSTR_H
#define NATIVE_SUBSTR_H

#include <string>

int native_substr( const std::string& text, const std::string& pattern )
{
  if (text.empty() || pattern.empty() || text.size() < pattern.size())
    return -1;

  for (int text_i = 0; text_i < text.size()-pattern.size()+1; ++text_i) {
    int pattern_i = 0;
    while (pattern_i < pattern.size() && text[text_i+pattern_i] == pattern[pattern_i])
      ++pattern_i;
    if (pattern_i == pattern.size())
      return text_i;
  }
  return -1;
}

#endif
