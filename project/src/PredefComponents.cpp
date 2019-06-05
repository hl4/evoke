#include "PredefComponents.h"
#include "Component.h"
#include "json11.hpp"

#include <map>
#include <sstream>
#include <string>

static std::string readAll(std::string const &filename)
{
    std::stringstream content;
    //return (content << std::ifstream(filename).rdbuf()).str();
    content << std::ifstream(filename).rdbuf();
    return content.str();
}

using json11::Json;

const Json::array getArray(Json config, const std::string &name)
{
    auto field = config[name];
    if(field.is_array())
    {
        return field.array_items();
    }

    if(field.is_string())
    {
        return Json::array{field};
    }

    return Json::array();
}

std::map<std::string, Component *> PredefComponentList()
{
    static std::map<std::string, Component> predefs;
    static std::map<std::string, Component *> list;

    std::string err;
    auto result = Json::parse(readAll("evoke-config.json"), err);
    if(!err.empty())
    {
        std::cout << "read Json:" << err << "\n";
        return list;
    }

    for(auto [name, config] : result.object_items())
    {
        bool binary = !config["headerOnly"].bool_value();
        auto c = &predefs.insert_or_assign(name, Component(name, binary))
                      .first->second;
        for(auto f : getArray(config, "header"))
        {
            list.insert_or_assign(f.string_value(), c);
        }

        for(auto d : getArray(config, "depend"))
        {
            auto inserted = predefs.insert_or_assign(
                d.string_value(),
                Component(d.string_value(), true));
            c->privDeps.insert(&inserted.first->second);
        }
    }

    //std::cout << result.dump() << "\n";
    return list;
}

