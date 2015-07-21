#ifndef SALIRA_WRITER_H__
#define SALIRA_WRITER_H__
#include <fstream>
#include <iostream>

/* 
 * Reimplementation of SaliraWriter as Singleton. Reason for this is to avoid
 * unneccessary argument refrencing to utility for storing results.
 */

class SaliraWriter {
public:
  static SaliraWriter& getInstance(){
		static SaliraWriter instance;
		return instance;
	}
  // write result;
  void write(const std::string text)
  {
    file << text + ";\n";
  }
private:
	std::ofstream file;
  // Singleton
	SaliraWriter(){
		file.open("gcode.txt",std::ios::app);    
	}
	// Ensuring that there won't be more than one instance of SaliraWriter.
	SaliraWriter(SaliraWriter const&)    = delete;
  void operator=(SaliraWriter const&)  = delete;
	~SaliraWriter(){
		file.close();
	}
};

#endif // SALIRA_WRITER_H__