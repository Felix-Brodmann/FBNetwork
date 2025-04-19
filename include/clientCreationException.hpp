#ifndef FBNETWORK_CLIENT_CREATION_EXCEPTION_HPP
#define FBNETWORK_CLIENT_CREATION_EXCEPTION_HPP

#include <exception>
#include <string>

namespace FBNetwork
{
    /**
     * @brief Exception thrown when a client creation error is encountered.
     * @details This exception is thrown when an error occurs during the creation of a client object.
     * @version 1.0.0
     */
    class ClientCreationException : public std::exception
    {
    private:
        std::string m_message;

    public:
        /**
         * @brief Constructs a ClientCreationException exception.
         * @details This constructor creates a ClientCreationException exception with a message.
         * @param t_message The error message to be associated with the exception.
         * @version 1.0.0
         */
        explicit ClientCreationException(const std::string &t_message)
        {
            m_message = "Client Creation Error: " + t_message;
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