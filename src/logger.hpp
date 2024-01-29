#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>
#include <array>
#include <sstream>
#include <source_location>

using std::cerr;
using std::cout;
using std::endl;
using std::ostream;
using std::string;

class Logger
{
public:
  enum LogLevel
  {
    Error = 1 << 0,
    Warning = 1 << 1,
    Info = 1 << 2,
    Debug = 1 << 3,
  };

  Logger& operator<<(std::ostream& (&)(std::ostream&));
  Logger& operator<<(const char* _logline);
  Logger& operator<<(const std::string& _logline);
  Logger& operator<<(LogLevel); // allows us to do Logger<<LogLevel::Error<<"Someline";

  void writelog(LogLevel _level, const std::string& _logline, const std::source_location _loc = std::source_location::current());

private:
  LogLevel level;

  struct ThreadLocals
  {
    ThreadLocals() :
      level(LogLevel::Info)
    {}
    string logline;
    LogLevel level;
  };
  ThreadLocals& getThreadLocal();
  static thread_local Logger::ThreadLocals tl;
};

#endif
