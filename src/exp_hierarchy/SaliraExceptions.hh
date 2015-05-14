/*
 * Exception hierarchy which could be possible to use inside project.
 * Reason why I started to build exception hierarchy so it can be used to 
 * report errors instead of if/else branches. Can be useful.
 */

#ifndef SALIRAEXCEPTIONS_H
#define SALIRAEXCEPTIONS_H

#include <exception>
#include <stdexcept>
#include <string>

class SaliraException : public std::runtime_error {
private:
  std::string _message;
public:
  SaliraException(std::string m) : runtime_error(m), _message(m) {}
  
  virtual const char* what() const throw()
  {
    return _message.c_str();
  }
};

 
#endif /* SALIRAEXCEPTIONS_H */