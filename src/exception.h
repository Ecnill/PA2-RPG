/** @file exception.h
 * Header file and implementation of Exception class.
 *
 *  @author Julia Ostrokomorets <ostroiul@fit.cvut.cz>
*/
#ifndef EXCEPTION_H
#define EXCEPTION_H
#include <sstream>
#include <string>
using namespace std;
/**********************************************************************************************/
/**
 * @brief The Exception class
 */
class Exception{
    public:
        /**
         * @brief Exception is constructor with parameters
         * @param mess is string to show
         */
        Exception( const string &mess ) : message( mess ) {}
        /**
         * @brief operator << is overload operator for output exception message on std::cout
         * @param os is ostream var for forming output
         * @param exc is object of class Exception, it has exception message to show
         * @return ostream var
         */
        friend ostream &operator<< ( ostream &os, const Exception &exc ){
            os << exc.message << endl;
            return os;
        }
        /**
         * @brief getMessage is getter of string message
         * @return message with reason of exception
         */
        string getMessage() const{
            return message;
        }
    private:
         const string  message;
};
#endif // EXCEPTION_H
