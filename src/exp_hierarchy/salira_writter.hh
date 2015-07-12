#ifndef SALIRA_WRITTER_H__
#define SALIRA_WRITTER_H__

#include <fstream>
#include <iostream>

class SaliraWritter {
public:
  SaliraWritter()
  {
  }
  
  void write(const std::string text) const
  {
    
    std::ofstream file;
    file.open("gcode.txt",std::ios::app);
    
    file << text;
    
    file.close();
  } 
 
};

#endif // SALIRA_WRITTER_H__