#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <string>

/** Exception class.
 *
 *  Class to act as a base class for exceptions.
 */
class Exception
{
    public:
        /** Exception constructor.
         *
         *  Initializes the internal message member variable of the class
         *  to the passed parameter. May not always have a description.
         *
         * @param message a constant std::string reference
         */
        Exception(const std::string& message, const std::string& desc);

        /** Function to get the Exception's currently held message.
         *
         * @return A constant std::string reference to the Exception's message.
         */
        const std::string& getMessage() const;

        /** Function to get the Exception's currently held description.
         *
         * @return A constant std::string reference to the Exception's description.
         */
        const std::string& getDescription() const;

    private:
        /** Member variable of type std::string to hold the Exception class' error message. */
        std::string message;

        /** Member variable of type std::string to hold the Exception class' error description. */
        std::string description;
};

#endif
