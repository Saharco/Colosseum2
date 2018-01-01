//
// Created by sahar on 31/12/2017.
//

#ifndef COLOSSEUM2_EXCEPTIONS_H
#define COLOSSEUM2_EXCEPTIONS_H

#include <exception>

class invalidInputException : public std::exception {};
class failureException : public std::exception {};

class ElementAlreadyExists : public failureException {
};

class ElementDoesntExist : public failureException {
};
class badIdException : public invalidInputException {};
class badLevelException : public invalidInputException {};
class uninitializedColosseumException : public invalidInputException {};
class badStimulantCodeException : public invalidInputException {};
class badStimulantFactorException : public invalidInputException {};
class sameIdException : public failureException {};

#endif //COLOSSEUM2_EXCEPTIONS_H
