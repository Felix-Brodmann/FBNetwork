#ifndef FBNETWORK_CLIENT_RUNTIME_EXCEPTION_HPP
#define FBNETWORK_CLIENT_RUNTIME_EXCEPTION_HPP

#include <exception>
#include <string>

namespace FBNetwork
{
    /**
     * @brief Exception thrown when a client runtime error is encountered.
     * @details This exception is thrown when an error occurs during the runtime of a client object.
     * @version 1.0.0
     */
    class ClientRuntimeException : public std::exception
    {
    private:
        std::string m_message;

    public:
        /**
         * @brief Constructs a ClientRuntimeException exception.
         * @details This constructor creates a ClientRuntimeException exception with a message.
         * @param t_message The error message to be associated with the exception.
         * @version 1.0.0
         */
        explicit ClientRuntimeException(const std::string &t_message)
        {
            m_message = "Client Runtime Error: " + t_message;
        }

        /**
         * @brief Returns the error message associated with the exception.
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