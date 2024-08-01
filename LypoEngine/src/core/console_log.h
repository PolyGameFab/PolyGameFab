//
// Created by samuel on 7/24/24.
//

#ifndef CONSOLE_LOG_H
#define CONSOLE_LOG_H

#include <string>

class ConsoleLogger {
public:

    explicit ConsoleLogger(const std::string &prefix);
    void info(const std::string &msg) const;
    void warn(const std::string &msg) const;
    void error(const std::string &msg) const;

private:
    std::string _prefix;
};


static ConsoleLogger core_logger("CORE");
static ConsoleLogger client_logger("CLIENT");


#define LYPO_CORE_INFO(msg) \
    core_logger.info(msg);

#define LYPO_CORE_WARN(msg) \
    core_logger.warn(msg);

#define LYPO_CORE_ERROR(msg) \
    core_logger.error(msg);

#define LYPO_CLIENT_INFO(msg) \
    client_logger.info(msg);

#define LYPO_CLIENT_WARN(msg) \
    core_logger.warn(msg);

#define LYPO_CLIENT_ERROR(msg) \
    core_logger.error(msg);

#endif //CONSOLE_LOG_H
