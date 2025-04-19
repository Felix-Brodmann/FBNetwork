#ifndef FBNETWORK_SYSTEM_RUNTIME_EXCEPTION_HPP
#define FBNETWORK_SYSTEM_RUNTIME_EXCEPTION_HPP

#include <stdexcept>
#include <string>

namespace FBNetwork
{
    /**
     * @brief The SystemRuntimeException class represents runtime exceptions thrown by the system.
     * @details This class is used to represent runtime exceptions thrown by the system. It extends the `std::runtime_error` class and
     * provides additional functionality to store the error code associated with the exception.
     * @version 1.0.0
     */
    class SystemRuntimeException : public std::exception
    {
    private:
        std::string m_message;

    public:
        /**
         * @brief Construct a new System Runtime Exception object.
         * @details This constructor creates a new SystemRuntimeException object with the specified error message.
         * @param t_message The error message associated with the exception.
         * @version 1.0.0
         */
        explicit SystemRuntimeException(const std::string &t_message)
        {
            m_message = "System Runtime Error: " + t_message;
        }

        /**
         * @brief Get the error message associated with the exception.
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