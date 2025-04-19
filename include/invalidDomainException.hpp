#ifndef FBNETWORK_INVALID_DOMAIN_EXCEPTION_HPP
#define FBNETWORK_INVALID_DOMAIN_EXCEPTION_HPP

#include <exception>
#include <string>

namespace FBNetwork
{
    /**
     * @brief Exception thrown when an invalid domain is encountered.
     * @details This exception is thrown when a domain provided to the server is not valid.
     * @version 1.0.0
     */
    class InvalidDomainException : public std::exception
    {
    private:
        std::string m_message;

    public:
        /**
         * @brief Constructs an InvalidDomain exception.
         * @details This constructor creates an InvalidDomain exception with a message.
         * @param t_message The error message to be associated with the exception.
         * @version 1.0.0
         */
        explicit InvalidDomainException(const std::string &t_message)
        {
            m_message = "Invalid Domain: " + t_message;
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