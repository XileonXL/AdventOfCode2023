/*
* Part 1 --> Check if the game is valid with 12 red cubes, 13 green cubes and 14 blue cubes.
*            Sum the ID of the game to get the total addition of ids.
* Part 2 --> Get the power of fewest cubes needed to play the game.
*            Sum the power of the game to get the total power value.
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>
#include <cctype>

const std::string getOnlyGameCombination(const std::string &line) {
  const char delimiter = ':';
  size_t delimiterPos = line.find(delimiter);
  const std::string game = delimiterPos != std::string::npos ? line.substr(delimiterPos+1) : "";

  return game;
}

// Part 1
bool isGamePossible(const std::string &line) {
  bool isPossible = true;
  static const std::map<std::string, int> cubes = {
    {"red", 12},
    {"green", 13},
    {"blue", 14}
  };
  
  std::istringstream iss(line);
  std::string color;
  int count;

  while (iss >> count >> color && isPossible) {
    if (!std::isalpha(color.back()))
      color.pop_back();

    isPossible = count <= cubes.at(color) ? true : false;
  }

  return isPossible;
}

// Part 2
int getPowerCubes(const std::string &line) {
  std::istringstream iss(line);
  std::string color;
  int count;

  std::map<std::string, int> fewestCubes;

  while (iss >> count >> color) {
    if (!std::isalpha(color.back()))
      color.pop_back();

    if (fewestCubes.find(color) == fewestCubes.end() || fewestCubes.find(color)->second < count)
      fewestCubes[color] = count;
  }

  int powerCubes = 1;
  for (auto it = fewestCubes.begin(); it != fewestCubes.end(); it++)
    powerCubes *= it->second;

  return powerCubes;
}

int main() {
  std::string inputFileName = "input.txt";
  std::ifstream inputFile(inputFileName);

  if (!inputFile) {
    std::cerr << "Error opening " << inputFileName << " file." << std::endl;
    return 1;
  }

  std::string line;
  std::vector<std::string> lines;
  while (std::getline(inputFile, line)) {
    lines.push_back(line);
  }

  if (lines.empty()) {
    std::cerr << "File " << inputFileName << " is empty." << std::endl;
  }

  inputFile.close();

  int sumIds = 0;
  int powerCubes = 0;

  for (unsigned int i = 0; i < lines.size(); i++) {
    const std::string game = getOnlyGameCombination(lines[i]);

    // Part 1
    if (game != "" && isGamePossible(game))
      sumIds += i+1;

    // Part 2
    if (game != "")
      powerCubes += getPowerCubes(game);
  }

  std::cout << sumIds << std::endl;
  std::cout << powerCubes << std::endl;

  return 0;
}
