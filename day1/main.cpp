#include <iostream>
#include <fstream>
#include <vector>
#include <cctype>
#include <string>
#include <map>

bool recursiveSearch(size_t index, const std::string &line, const std::string &candidate, int iteration) {
  if (iteration == candidate.size()) {
    return true; // Found
  }

  return (line[index] == candidate[iteration]) && recursiveSearch(index+1, line, candidate, iteration+1);
}

int getSpelledDigit(size_t index, const std::string &line) {
  static const std::map<std::string, int> digits = {
    {"one", 1},
    {"two", 2},
    {"three", 3},
    {"four", 4},
    {"five", 5},
    {"six", 6},
    {"seven", 7},
    {"eight", 8},
    {"nine", 9}
  };

  int digit = 0;
  for (auto it = digits.begin(); it != digits.end() && digit == 0; it++) {
    const std::string &digit_str = it->first;
    if (recursiveSearch(index, line, digit_str, 0)) {
      digit = it->second;
    }
  }

  return digit;
}

int getLineCalibration(const std::string &line) {
  size_t start = 0;
  size_t end = line.size() > 1 ? line.size() - 1 : 0; // Avoid blank or one-character lines

  int first_digit = 0;
  int second_digit = 0;
  int full_digit = 0;

  if (end != 0) {
    for (; start <= end && first_digit == 0; start++)
      first_digit = std::isdigit(line[start]) ? line[start] - '0' : getSpelledDigit(start, line);

    for (; end > start && second_digit == 0; end--)
      second_digit = std::isdigit(line[end]) ? line[end] - '0' : getSpelledDigit(end, line);

    full_digit = first_digit != 0 && second_digit != 0 ? first_digit*10 + second_digit : 0;
  }

  std::cout << line << " - " << full_digit << std::endl;

  return full_digit;
}

int main(int argc, char *argv[]){
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <inputFile>" << std::endl;
    return 1;
  }

  std::string inputFileName = argv[1];
  std::ifstream inputFile(inputFileName);
  if (!inputFile) {
    std::cerr << "Error opening " << argv[1] << " file." << std::endl;
    return 1;
  }

  std::string line;
  std::vector<std::string> lines;
  while (std::getline(inputFile, line)) {
    lines.push_back(line);
  }

  if (lines.empty()) {
    std::cerr << "File " << argv[1] << " is empty." << std::endl;
  }

  inputFile.close();

  int calibration = 0;
  for (unsigned int i=0; i < lines.size(); i++) {
    calibration += getLineCalibration(lines[i]);
  }

  std::cout << calibration << std::endl;

  return 0;
}
