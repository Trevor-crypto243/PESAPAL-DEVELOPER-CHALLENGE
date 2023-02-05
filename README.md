#PESAPAL DEVELOPER CHALLENGE: Problem 2 - A Diff and a Patch
##Description
This program consists of two tools, diff and patch, that allow you to compare two files and generate the differences between them. The output from the diff tool can be used with the patch tool and one of the original files to recreate the other. The tools have been designed to work in a similar manner to the Unix diff and patch tools as described in the POSIX manual, with added flexibility in the algorithms and output format used.

##Programming Language
C++ has been used as the programming language for this project due to its efficiency, versatility, and widespread use in software development. The performance benefits of C++ allow for quick and efficient comparisons between large files, making it a suitable choice for this type of application. In addition, C++ is widely used and has a large user community, providing a wealth of resources for development and troubleshooting. The object-oriented programming features of C++ also make it easy to maintain and extend the codebase in the future.

##Running the Diff Tool
Compile the code using g++ -o diff diff.cpp
Run the tool using the following command ./diff [-c|-e|-f|-u|-C n|-U n] [-br] file1 file2
Running the Patch Tool
Compile the code using g++ -o patch patch.cpp
Run the tool using the following command ./patch [-blNR] [-c|-e|-n|-u] [-d dir] [-D define] [-i patchfile] [-o outfile] [-p num] [-r rejectfile] [file]
