#ifndef FBNETWORK_EXTENDEDSYSTEM_HPP
#define FBNETWORK_EXTENDEDSYSTEM_HPP

#include <cerrno>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <errno.h>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <string>
#include "constants.hpp"
#include "exceptions.hpp"

namespace FBNetwork
{
    /**
     * @brief The ExtendedSystem class provides additional system functionality.
     * @details This class provides additional system functionality such as getting the current date and time, reading and
     * writing to files and loading environment variables from a file.
     * @version 1.0.0
     */
    class ExtendedSystem
    {
    public:
        /**
         * @brief Get the current date as a string.
         * @return The current date in the format "dd.mm.yyyy".
         * @throws SystemRuntimeException If the current date could not be retrieved.
         * @version 1.0.0
         */
        static std::string getCurrentDate();

        /**
         * @brief Returns the current time as a string.
         * @return The current time as a string in the format "hh:mm:ss".
         * @throws SystemRuntimeException If the current time could not be retrieved.
         * @version 1.0.0
         */
        static std::string getCurrentTime();

        /**
         * @brief Retrieves the current error message associated with the value of `errno`.
         * @return A string containing the error message.
         * @version 1.0.0
         */
        static std::string getCurrentErrnoError();

        /**
         * @brief Reads the contents of a file located at the specified file path.
         * @param t_filePath The path to the file to be read.
         * @return A string containing the contents of the file.
         * @throws `InvalidArgumentException` If the file path is empty.
         * @throws `SystemRuntimeException` If the file could not be opened.
         * @version 1.0.0
         */
        static std::string readFromFile(const std::string &t_filePath);

        /**
         * @brief Retrieves the size of a file.
         * @details This function takes a file path as input and returns the size of the file in bytes.
         * @param t_filePath The path of the file to retrieve the size of.
         * @return The size of the file in bytes.
         * @throws `InvalidArgumentException` If the file path is empty.
         * @throws `SystemRuntimeException` If the file could not be opened.
         * @version 1.0.0
         */
        static size_t getFileSize(const std::string &t_filePath);

        /**
         * @brief Writes the given data to a file at the specified file path.
         * @param t_filePath The path of the file to write to.
         * @param t_data The data to write to the file.
         * @throws `InvalidArgumentException` If the file path or data is empty.
         * @throws `SystemRuntimeException` If the file could not be opened.
         * @version 1.0.0
         */
        static void writeToFile(const std::string &t_filePath, const std::string &t_data);

        /**
         * @brief Loads environment variables from a file.
         * @details This function takes a file path as input and loads the environment variables from the file. The file must be be in a
         * KEY=VALUE pattern with no spaces. It does not validate if the file is a valid environment file.
         * @param t_filePath The path of the file to load the environment variables from.
         * @throws `InvalidArgumentException` If the file path is empty.
         * @throws `SystemRuntimeException` If the file could not be opened.
         * @version 1.0.0
         */
        static void loadEnvironmentVariables(const std::string &t_filePath);
    };
}  // namespace FBNetwork

#endif