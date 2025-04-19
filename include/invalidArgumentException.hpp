#ifndef FBNETWORK_INVALID_ARGUMENT_EXCEPTION_HPP
#define FBNETWORK_INVALID_ARGUMENT_EXCEPTION_HPP

#include <exception>
#include <string>

namespace FBNetwork
{
    /**
     * @brief Exception thrown when an invalid argument is encountered.
     * @details This exception is thrown when an invalid argument is passed to a function.
     * @version 1.0.0
     */
    class InvalidArgumentException : public std::exception
    {
    private:
        std::string m_message;

    public:
        /**
         * @brief Constructs an InvalidArgumentException exception.
         * @details This constructor creates an InvalidArgumentException exception with a message.
         * @param t_message The error message to be associated with the exception.
         * @version 1.0.0
         */
        explicit InvalidArgumentException(const std::string &t_message)
        {
            m_message = "Invalid Argument: " + t_message;
        }

        /**
         * @brief Returns the error message associated with the exception.
         * @details This method returns the error message associated with the exception.
         * @return A C-style string representing the error message.
         * @version 1.0.0
         */
        const char *what() const noexcept override
        {
            return m_message.c_str();
        }
    };
}  // namespace FBNetwork

#endif