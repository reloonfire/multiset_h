#ifndef ELEMENT_NOT_FOUND_EXCEPTION_H
#define ELEMENT_NOT_FOUND_EXCEPTION_H

#include <stdexcept>
#include <string>
/**
 * @brief Classe eccezione custom che deriva da std::runtime_error
 */
class element_not_found_exception : public std::runtime_error
{
public:
    /**
     * @brief Construttore che riceve un messaggio d'errore
     *
     * @param msg
     */
    element_not_found_exception(const std::string &msg) : std::runtime_error(msg)
    {
    }
};

#endif