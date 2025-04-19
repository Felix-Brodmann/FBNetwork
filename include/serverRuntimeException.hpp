#ifndef FBNETWORK_SERVER_RUNTIME_EXCEPTION_HPP
#define FBNETWORK_SERVER_RUNTIME_EXCEPTION_HPP

#include <exception>
#include <string>

namespace FBNetwork
{
    /**
     * @brief Exception thrown when a runtime error occurs in the server.
     * @details This exception is thrown when there is a runtime error in the server, such as a failure in reading or writing data.
     * @version 1.0.0
     */
    class ServerRuntimeException : public std::exception
    {
    private:
        std::string m_message;

    public:
        /**
         * @brief Constructs a ServerRuntimeException.
         * @details This constructor creates a ServerRuntimeException with a message.
         * @param t_message The error message to be associated with the exception.
         * @version 1.0.0
         */
        explicit ServerRuntimeException(const std::string &t_message)
        {
            m_message = "Server Runtime Error: " + t_message;
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