#pragma once

#include "globaloptions.h"

#include <map>
#include <memory>
#include <set>
#include <string>
#include <vector>

struct File;
struct Component;
class Project;

struct Toolset
{
    virtual ~Toolset()
    {
    }
    virtual void CreateCommandsFor(Project &project) = 0;
    virtual void CreateCommandsForUnity(Project &project) = 0;
    virtual void SetParameter(const std::string &key, const std::string &value) = 0;
    virtual GlobalOptions ParseGeneralOptions(const std::string &options);
    virtual std::string getBmiNameFor(const File &file) = 0;
    virtual std::string getObjNameFor(const File &file) = 0;
    virtual std::string getLibNameFor(const Component &component) = 0;
    virtual std::string getExeNameFor(const Component &component) = 0;
    std::string getNameFor(const Component &component);
};

std::unique_ptr<Toolset> GetToolsetByName(const std::string &name);
