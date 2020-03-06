#pragma once

#include <exception>
#include <string>

enum class CException
{
    NetworkException,
    dataBaseException,
    ScriptLoading,
    SceneGeneration
};

template <enum CException>
class EngineException : public std::exception
{
private:
    std::string _errorMess;
public:
    EngineException(const std::string &mess) : _errorMess(mess) {};
    virtual ~EngineException() = default;
    virtual const char *what() const noexcept override { return _errorMess.c_str(); };
};


