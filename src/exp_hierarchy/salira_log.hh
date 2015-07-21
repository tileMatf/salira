#ifndef SALIRA_LOG_H__
#define SALIRA_LOG_H__

#include <fstream>
#include <iostream>

class SaliraLog {
public:
  static void log(std::string input){
    std::ofstream file;
    file.open("log_runtime.txt",std::ios::app);
    file << input << std::endl;
    file.close();
  }
  static void tree(std::string input){
		std::ofstream file;
    file.open("tree.txt",std::ios::app);
    file << input << std::endl;
    file.close();
  }
private:
  SaliraLog() {}
};

#endif // SALIRA_LOG_H__