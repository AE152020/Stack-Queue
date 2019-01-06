//Kevin Florio CSM20 Fall 2016 Project B
#ifndef PrecondViolatedExcept_H
#define PrecondViolatedExcept_H
#include<string>
#include<stdexcept>

class PrecondViolatedExcept : public std::logic_error
{
public:
	PrecondViolatedExcept(const std::string& message = "");
};
// Constructor definition
PrecondViolatedExcept::PrecondViolatedExcept(const std::string& message)
	:std::logic_error("Precondition Violated Exception: " + message) {}

#endif
