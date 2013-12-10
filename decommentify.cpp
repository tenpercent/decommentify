#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

void get_program_text (string & text);
void process_program_text (string & program_text);

bool c_style_comment_starts_here (string const & program_text, size_t const current_symbol_pos);
bool c_style_comment_ends_here (string const & program_text, size_t const current_symbol_pos);
bool single_line_comment_starts_here(string const & program_text, size_t const current_symbol_pos);
int search_comment_finish (string const & program_text, int const start_search_position);

int main () {
  string program_text;
  get_program_text (program_text);

  process_program_text (program_text);

  cout << program_text;

  return 0;
}

void get_program_text (string & text) {
  string line;
  while (!cin.eof()) {
    getline(cin, line);
    text += line;
    text += "\n";
  }
  text.erase(text.end() - 1);
}

int search_comment_finish (string const & program_text, int const start_search_position) {
  int answer = program_text.find('\n', start_search_position);
  while (program_text[answer - 1] == '\\') {
    answer = program_text.find('\n', answer + 1);
  }
  return answer;
}

bool single_line_comment_starts_here(string const & program_text, size_t const current_symbol_pos) {
  if ((program_text[current_symbol_pos] == '/') && (program_text[current_symbol_pos + 1] == '/')) {
    return true;
  }
  if ((program_text[current_symbol_pos] == '/') && 
      (program_text[current_symbol_pos + 1] == '\\') &&
      (program_text[current_symbol_pos + 2] == '\n') &&
      (program_text[current_symbol_pos + 3] == '/')) {
    return true;
  }
  return false;
}

bool c_style_comment_starts_here (string const & program_text, size_t const current_symbol_pos) {
  if ((program_text[current_symbol_pos] == '/') && (program_text[current_symbol_pos + 1] == '*')) {
    return true;
  }
  if ((program_text[current_symbol_pos] == '/') && 
      (program_text[current_symbol_pos + 1] == '\\') &&
      (program_text[current_symbol_pos + 2] == '\n') &&
      (program_text[current_symbol_pos + 3] == '*')) {
    return true;
  }
  return false;
}

bool c_style_comment_ends_here (string const & program_text, size_t const current_symbol_pos) {
  if ((program_text[current_symbol_pos] == '*') && (program_text[current_symbol_pos + 1] == '/')) {
    return true;
  }
  if ((program_text[current_symbol_pos] == '*') && 
      (program_text[current_symbol_pos + 1] == '\\') &&
      (program_text[current_symbol_pos + 2] == '\n') &&
      (program_text[current_symbol_pos + 3] == '/')) {
    return true;
  }
  return false;
}

void process_program_text (string & program_text) {
  bool inside_comment = false;
  bool inside_quote = false;
  size_t comment_start = 0;
  size_t comment_finish = 0;

  size_t current_symbol_pos = 0;

  while (current_symbol_pos != program_text.length()) {
    if (!inside_comment) {
      if ((program_text[current_symbol_pos] == '\"') && 
          (program_text[current_symbol_pos - 1] != '\\')) {
        inside_quote = !inside_quote;
        ++current_symbol_pos;
        continue;
      }
      if (!inside_quote) {
        if (single_line_comment_starts_here(program_text, current_symbol_pos)) {
          comment_start = current_symbol_pos;
          comment_finish = search_comment_finish (program_text, comment_start);
          if ((current_symbol_pos == 0) || 
              (program_text[current_symbol_pos - 1] == '\n')) {// erase whole line
            program_text = program_text.erase (comment_start, comment_finish - comment_start + 1);
          }
          else {// erase everything except '\n'
            program_text = program_text.erase (comment_start, comment_finish - comment_start);
          }
          continue;
        }
        if (c_style_comment_starts_here(program_text, current_symbol_pos)) {
          comment_start = current_symbol_pos;
          inside_comment = true;
          ++current_symbol_pos;
          continue;
        }
      }
    } else {
      if (c_style_comment_ends_here (program_text, current_symbol_pos)) {

        if (program_text[current_symbol_pos + 1] == '/') {// "*/"
          program_text = program_text.erase (comment_start, current_symbol_pos - comment_start + 2);
        }
        else {// "*\\\n/"
          program_text = program_text.erase (comment_start, current_symbol_pos - comment_start + 4);
        }

        current_symbol_pos = comment_start;
        if ((program_text[current_symbol_pos] == '\n') && 
            (program_text[current_symbol_pos - 1] == '\n')) {
          program_text = program_text.erase (current_symbol_pos, 1);
        }

        inside_comment = false;
        continue;
      }
    }
    ++current_symbol_pos;
  }
}
