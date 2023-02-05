#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <getopt.h>// for getopt_long();1`  

using namespace std;

void displayUsage() {
  cout << "Usage: patch [-blNR] [-c|-e|-n|-u] [-d dir] [-D define] [-i patchfile] [-o outfile] [-p num] [file]" << endl;
}

int main(int argc, char* argv[]) {
  int c;
  int num = 0;
  char *patchfile = NULL, *outfile = NULL, *rejectfile = NULL;
  bool bFlag = false, lFlag = false, NFlag = false, RFlag = false;
  int mode = -1;
  string dir;
  
  while((c = getopt(argc, argv, "blNRcenu:d:D:i:o:p:r:")) != -1) {
    switch(c) {
      case 'b':
        bFlag = true;
        break;
      case 'l':
        lFlag = true;
        break;
      case 'N':
        NFlag = true;
        break;
      case 'R':
        RFlag = true;
        break;
      case 'c':
        mode = 0;
        break;
      case 'e':
        mode = 1;
        break;
      case 'n':
        mode = 2;
        break;
      case 'u':
        mode = 3;
        break;
      case 'd':
        dir = optarg;
        break;
      case 'D':
        // handle the -D option
        break;
      case 'i':
        patchfile = optarg;
        break;
      case 'o':
        outfile = optarg;
        break;
      case 'p':
        num = atoi(optarg);
        break;
      case 'r':
        rejectfile = optarg;
        break;
      case '?':
        displayUsage();
        return 1;
      default:
        cout << "Error: Unrecognized option" << endl;
        displayUsage();
        return 1;
    }
  }
  
  if (argc - optind < 1) {
    cout << "Error: Missing file argument" << endl;
    displayUsage();
    return 1;
  }
  
  char* file = argv[optind];
  
  if (patchfile == NULL) {
    cout << "Error: Missing -i option" << endl;
    displayUsage();
    return 1;
  }
  
  // Open both input files
  ifstream fileA(file);
  ifstream diff(patchfile);

  // Read fileA into a vector
  vector<string> linesA;
  string line;
  while (getline(fileA, line)) {
    linesA.push_back(line);
  }

  // Read the diff and modify the linesA vector accordingly
  int lineNum = 0;
  while (getline(diff, line)) {
    switch (line[0]) {
      case ' ':
        lineNum++;
        break;
      case '+':
        linesA.insert(linesA.begin() + lineNum, line.substr(2));
        lineNum++;
        break;
      case '-':
        linesA.erase(linesA.begin() + lineNum);
        break;
      case '*':
        linesA[lineNum] = line.substr(2).substr(0, line.substr(2).find("|"));
        lineNum++;
        break;
      default:
        cout << "Error: Unrecognized diff format" << endl;
        return 1;
    }
  }

  // Write the modified fileA back to disk
  ofstream output(argv[1]);
  for (string line : linesA) {
    output << line << endl;
  }

  return 0;
}


   
