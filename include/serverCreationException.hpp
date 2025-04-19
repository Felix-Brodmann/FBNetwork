#ifndef FBNETWORK_SERVER_CREATION_EXCEPTION_HPP
#define FBNETWORK_SERVER_CREATION_EXCEPTION_HPP

#include <exception>
#include <string>

namespace FBNetwork
{
    /**
     * @brief Exception thrown when a server creation fails.
     * @details This exception is thrown when there is an error during the creation of a server.
     * @version 1.0.0
     */
    class ServerCreationException : public std::exception
    {
    private:
        std::string m_message;

    public:
        /**
         * @brief Constructs a ServerCreationException.
         * @details This constructor creates a ServerCreationException with a message.
         * @param t_message The error message to be associated with the exception.
         * @version 1.0.0
         */
        explicit ServerCreationException(const std::string &t_message)
        {
            m_message = "Server Creation Error: " + t_message;
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