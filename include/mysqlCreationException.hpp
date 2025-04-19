#ifndef FBNETWORK_MYSQL_CREATION_EXCEPTION_HPP
#define FBNETWORK_MYSQL_CREATION_EXCEPTION_HPP

#include <stdexcept>
#include <string>

namespace FBNetwork
{
    /**
     * @brief The MySQLCreationException class represents an exception that is thrown when a creation error occurs in the MySQL class.
     * @details This class represents an exception that is thrown when a creation error occurs in the MySQL class. It is a subclass of
     * std::runtime_error.
     * @version 1.0.0
     */
    class MySQLCreationException : public std::exception
    {
    private:
        std::string m_message;

    public:
        /**
         * @brief Constructs a new MySQLCreationException object with the specified message.
         * @details This constructor creates a new MySQLCreationException object with the specified message.
         * @param t_message The message to be set.
         * @version 1.0.0
         */
        explicit MySQLCreationException(const std::string &t_message)
        {
            m_message = "MySQL Creation Error: " + t_message;
        }

        /**
         * @brief Retrieves the message associated with the exception.
         * @details This function returns the message associated with the exception.
         * @return The message associated with the exception.
         * @version 1.0.0
         */
        const char *what() const noexcept override
        {
            return m_message.c_str();
        }
    };
}  // namespace FBNetwork

#endif