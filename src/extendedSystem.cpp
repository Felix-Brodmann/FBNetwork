#include "../include/extendedSystem.hpp"

std::string FBNetwork::ExtendedSystem::getCurrentDate()
{
    time_t     t        = std::time(nullptr);
    struct tm *tmStruct = std::localtime(&t);
    if (tmStruct == nullptr)
    {
        throw SystemRuntimeException("Could not get current date.");
    }
    std::stringstream strStream;
    strStream << std::put_time(tmStruct, "%d.%m.%Y");
    return strStream.str();
}

std::string FBNetwork::ExtendedSystem::getCurrentTime()
{
    time_t     t        = std::time(nullptr);
    struct tm *tmStruct = std::localtime(&t);
    if (tmStruct == nullptr)
    {
        throw SystemRuntimeException("Could not get current time.");
    }
    std::stringstream strStream;
    strStream << std::put_time(tmStruct, "%H:%M:%S");
    return strStream.str();
}

std::string FBNetwork::ExtendedSystem::getCurrentErrnoError()
{
    char errorBuffer[Constants::BUFFER_SIZE] = {0};
    int  savedErrno                          = errno;
    if (savedErrno == 0)
    {
        return "No error.";
    }

    // Handle the errno value based on the platform

#ifdef __APPLE__
    int result = strerror_r(savedErrno, errorBuffer, Constants::BUFFER_SIZE);
    if (result != 0)
    {
        return "Unknown error.";
    }
    return std::string(errorBuffer);
#elif __linux__
    const char *errorMsg = strerror_r(savedErrno, errorBuffer, Constants::BUFFER_SIZE);
    if (errorMsg == nullptr)
    {
        return "Unknown error.";
    }
    return std::string(errorMsg);
#endif
}

std::string FBNetwork::ExtendedSystem::readFromFile(const std::string &t_filePath)
{
    if (t_filePath.empty())
    {
        throw InvalidArgumentException("File path cannot be empty.");
    }
    std::ifstream file(t_filePath);
    if (!file.is_open())
    {
        throw SystemRuntimeException("File could not be opened.");
    }
    std::string fileData;
    size_t      fileSize = getFileSize(t_filePath);
    fileData.resize(fileSize);
    file.read(&fileData[0], fileSize);
    file.close();
    return fileData;
}

size_t FBNetwork::ExtendedSystem::getFileSize(const std::string &t_filePath)
{
    if (t_filePath.empty())
    {
        throw InvalidArgumentException("File path cannot be empty.");
    }
    std::ifstream file(t_filePath);
    if (!file.is_open())
    {
        throw SystemRuntimeException("File could not be opened.");
    }
    file.seekg(0, file.end);
    size_t fileSize = file.tellg();
    file.close();
    return fileSize;
}

void FBNetwork::ExtendedSystem::writeToFile(const std::string &t_filePath, const std::string &t_data)
{
    if (t_filePath.empty())
    {
        throw InvalidArgumentException("File path cannot be empty.");
    }
    if (t_data.empty())
    {
        throw InvalidArgumentException("Data cannot be empty.");
    }
    std::ofstream file(t_filePath);
    if (!file.is_open())
    {
        throw SystemRuntimeException("File could not be opened.");
    }
    file << t_data;
    file.close();
}

void FBNetwork::ExtendedSystem::loadEnvironmentVariables(const std::string &t_filePath)
{
    std::string fileData = "";

    // readFromFile throws InvalidArgumentException and SystemRuntimeException

    fileData = readFromFile(t_filePath);
    std::istringstream fileStream(fileData);
    std::string        line;
    while (std::getline(fileStream, line))
    {
        std::istringstream lineStream(line);
        std::string        key;
        std::string        value;
        std::getline(lineStream, key, '=');
        if (key.empty())
        {
            continue;
        }
        std::getline(lineStream, value);
        if (value.empty())
        {
            continue;
        }
        setenv(key.c_str(), value.c_str(), 1);
    }
}