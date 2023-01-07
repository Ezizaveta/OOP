#pragma once
#include <memory>
#include <sstream>
#include "Decorator.h"

class HTMLDecorator : public Decorator
{
//protected:
//	std::shared_ptr<Decorator> other_decorator;
private:
    std::string replaceCharacters(const std::string& str);
    std::vector<std::pair<std::string, std::string>> special_symbols{
        {"&",   "&#38;"},
        {"\t",  "&#8195;"},
        {"'",   "&#39;"},
        {"\"",  "&#34;"},
        {"<",   "&#60;"},
        {">",   "&#62;"}
    };
public:
	HTMLDecorator(std::shared_ptr<AbstractDecorator> component) : Decorator(component) {}
    std::string write(const std::string& str) override;
};