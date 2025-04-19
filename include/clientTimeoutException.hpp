#ifndef FBNETWORK_CLIENT_TIMEOUT_EXCEPTION_HPP
#define FBNETWORK_CLIENT_TIMEOUT_EXCEPTION_HPP

#include <exception>
#include <string>

namespace FBNetwork
{
    /**
     * @brief Exception thrown when a timeout occurs in the client.
     * @details This exception is thrown when there is a timeout in the client, such as a timeout in reading or writing data.
     * @version 1.0.0
     */
    class ClientTimeoutException : public std::exception
    {
    private:
        std::string m_message;

    public:
        /**
         * @brief Constructs a ClientTimeoutException.
         * @details This constructor creates a ClientTimeoutException with a message.
         * @param t_message The error message to be associated with the exception.
         * @version 1.0.0
         */
        explicit ClientTimeoutException(const std::string &t_message)
        {
            m_message = "Client Timeout Error: " + t_message;
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