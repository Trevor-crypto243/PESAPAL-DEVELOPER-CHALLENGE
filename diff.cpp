#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <cstdlib>

using namespace std;

// Utility function to compare two lines and return a string indicating the difference
string compareLines(string lineA, string lineB) {
  if (lineA == lineB) {
    return " ";
  } else {
    return lineA + "|" + lineB;
  }
}

int main(int argc, char* argv[]) {
  // Parse the options
  int option = 0;
  int contextLines = 3;
  bool showLineNumbers = false;
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-') {
      switch (argv[i][1]) {
        case 'c':
          option = 1;
          break;
        case 'e':
          option = 2;
          break;
        case 'f':
          option = 3;
          break;
        case 'u':
          option = 4;
          break;
        case 'C':
        case 'U':
          if (strlen(argv[i]) > 2) {
            contextLines = atoi(argv[i] + 2);
          } else {
            contextLines = atoi(argv[++i]);
          }
          option = (argv[i - 1][1] == 'C') ? 5 : 6;
          break;
        case 'b':
          showLineNumbers = true;
          break;
        case 'r':
          break;
        default:
          cout << "diff: illegal option -- " << argv[i][1] << endl;
          cout << "Usage: diff [-c|-e|-f|-u|-C n|-U n] [-br] file1 file2" << endl;
          return 1;
      }
    } else {
      break;
    }
  }

  // Check if there are exactly two input files
  if (argc - option < 4) {
    cout << "Usage: diff [-c|-e|-f|-u|-C n|-U n] [-br] file1 file2" << endl;
    return 1;
  }

  // Open both input files
  ifstream fileA(argv[argc - 2]);
  ifstream fileB(argv[argc - 1]);

  // Read both files into separate vectors
  vector<string> linesA, linesB;
  string line;
  while (getline(fileA, line)) {
    linesA.push_back(line);
  }
  while (getline(fileB, line)) {
    linesB.push_back(line);
  }

  // Compare both vectors and print the result
  int lines = max(linesA.size(), linesB.size());
  for (int i = 0; i < lines; i++) {
    if (i >= linesA.size()) {
      cout << "+ " << linesB[i] << endl;
    } else if (i >= linesA.size()) {
      cout << "+ " << linesB[i] << endl;
    } else if (i >= linesB.size()) {
      cout << "- " << linesA[i] << endl;
    } else {
      string diff = compareLines(linesA[i], linesB[i]);
      if (diff[0] == ' ') {
        cout << "  " << linesA[i] << endl;
      } else {
        cout << "* " << diff << endl;
      }
    }
  }

  return 0;
}
