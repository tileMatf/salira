#ifndef SALIRADEV_H__
#define SALIRADEV_H__

#include "expression.hh"
#include "functor.hh"
#include "metafunc.hh" 
#include <fstream>
/*
 * Dev purpose tools.
 * NOTE: Return functions in Functor.hh and _declarations in MetaFunc.hh to private.
 */
class SaliraDev{
public:
  // Generate txt file with function map contents.
  static void MapPrint(){
    std::ofstream file;
    file.open("map_content.txt");
    file << "Map contents!" << std::endl;
    // iterate through map
    for(auto item : Functor::functions){
      file <<'\t' << item.first << " " << "Num: " << item.second._declarations.size() << std::endl;
      // iterate through declarations
      for(auto item1 : item.second._declarations){
	file << "\t\t"<<"Declaration: " << std::endl;
	file << "\t\t\t" <<"Arguments" << std::endl;
	// iterate through arguments
	for(auto item2 : item1.args){
	  file << "\t\t\t\t";
	  file << item2->print() << std::endl;
	}
      }
    }
    file.close();
  }

  
};

#endif //SaliraDev_H__