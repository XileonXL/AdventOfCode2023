#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <cctype>
#include <string>

int main(int argc, char *argv[]){
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << "<input_file>" << std::endl;
    return 1;
  }

  std::string input_file_name = argv[1];
  std::ifstream input_file(input_file_name);
  if (!input_file) {
    std::cerr << "Error opening " << argv[1] << " file." << endl;
    return 1;
  }

  std::string line;
  std::vector<std::string> lines;
  while (std::getline(input_file, line)) {
    lines.push_back(line);
  }

  if (lines.empty()) {
    std::cerr << "File " << argv[1] << " is empty.";
  }

  input_file.close();

  std::vector<int> calibration_values;
  bool digit_found = false;
  char first_digit, second_digit;
  int digit
  for (int i=0; i < lines.size(); i++) {
    std::string::iterator it_start = lines[i].start();
    std::string::iterator it_end = lines[i].end() - 1;

    for (it_start; it_start != lines[i].end()-1 && !digit_found; it_start++) {
      digit_found = std::isdigit(*it_start) ? true : false;
    }

    digit_found = true;
    
    for (it_end; it_end != lines[i].start() && !digit_found; it_start++) {
      digit_found = std::isdigit(*it_end) ? true : false;
    }




  }

  return 0;
}
