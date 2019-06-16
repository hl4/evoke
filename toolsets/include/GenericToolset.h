#pragma once

#include "globaloptions.h"

#include <map>
#include <memory>
#include <set>
#include <string>
#include <vector>

#include "Toolset.h"

class GenericToolset : public Toolset
{
public:
    void CreateCommandsForUnity(Project &project) override;
    void CreateCommandsFor(Project &project) override;
    void SetParameter(const std::string &key, const std::string &value) override;

protected:
    std::string GetCompilerFor(std::string extension);
    virtual std::string getUnityCommand(const std::string &program, const std::string &compileFlags, const std::string &outputFile, const File *inputFile, const std::set<std::string> &includes, std::vector<std::vector<Component *>> linkDeps) = 0;
    virtual std::string getCompileCommand(const std::string &program, const std::string &compileFlags, const std::string &outputFile, const File *inputFile, const std::set<std::string> &includes, bool usesModules) = 0;
    virtual std::string getPrecompileCommand(const std::string &program, const std::string &compileFlags, const std::string &outputFile, const File *inputFile, const std::set<std::string> &includes, bool usesModules) = 0;
    virtual std::string getArchiverCommand(const std::string &program, const std::string &outputFile, const std::vector<File *> inputs) = 0;
    virtual std::string getLinkerCommand(const std::string &program, const std::string &outputFile, const std::vector<File *> objects, std::vector<std::vector<Component *>> linkDeps) = 0;
    virtual std::string getUnittestCommand(const std::string &program) = 0;
    std::map<std::string, std::string> parameters;
};

struct AndroidToolset : public Toolset
{
    void SetParameter(const std::string &key, const std::string &value) override;
    void CreateCommandsFor(Project &project) override;
    void CreateCommandsForUnity(Project &project) override;
    std::string getBmiNameFor(const File &file) override;
    std::string getObjNameFor(const File &file) override;
    std::string getLibNameFor(const Component &component) override;
    std::string getExeNameFor(const Component &component) override;
};

struct ClangToolset : public GenericToolset
{
    ClangToolset();
    GlobalOptions ParseGeneralOptions(const std::string &options) override;
    std::string getUnityCommand(const std::string &program, const std::string &compileFlags, const std::string &outputFile, const File *inputFile, const std::set<std::string> &includes, std::vector<std::vector<Component *>> linkDeps) override;
    std::string getCompileCommand(const std::string &program, const std::string &compileFlags, const std::string &outputFile, const File *inputFile, const std::set<std::string> &includes, bool hasModules) override;
    std::string getPrecompileCommand(const std::string &program, const std::string &compileFlags, const std::string &outputFile, const File *inputFile, const std::set<std::string> &includes, bool hasModules) override;
    std::string getArchiverCommand(const std::string &program, const std::string &outputFile, const std::vector<File *> inputs) override;
    std::string getLinkerCommand(const std::string &program, const std::string &outputFile, const std::vector<File *> objects, std::vector<std::vector<Component *>> linkDeps) override;
    std::string getUnittestCommand(const std::string &program) override;
    std::string getBmiNameFor(const File &file) override;
    std::string getObjNameFor(const File &file) override;
    std::string getLibNameFor(const Component &component) override;
    std::string getExeNameFor(const Component &component) override;
};

struct GccToolset : public GenericToolset
{
    GccToolset();
    GlobalOptions ParseGeneralOptions(const std::string &options) override;
    std::string getUnityCommand(const std::string &program, const std::string &compileFlags, const std::string &outputFile, const File *inputFile, const std::set<std::string> &includes, std::vector<std::vector<Component *>> linkDeps) override;
    std::string getCompileCommand(const std::string &program, const std::string &compileFlags, const std::string &outputFile, const File *inputFile, const std::set<std::string> &includes, bool hasModules) override;
    std::string getPrecompileCommand(const std::string &program, const std::string &compileFlags, const std::string &outputFile, const File *inputFile, const std::set<std::string> &includes, bool hasModules) override;
    std::string getArchiverCommand(const std::string &program, const std::string &outputFile, const std::vector<File *> inputs) override;
    std::string getLinkerCommand(const std::string &program, const std::string &outputFile, const std::vector<File *> objects, std::vector<std::vector<Component *>> linkDeps) override;
    std::string getUnittestCommand(const std::string &program) override;
    std::string getBmiNameFor(const File &file) override;
    std::string getObjNameFor(const File &file) override;
    std::string getLibNameFor(const Component &component) override;
    std::string getExeNameFor(const Component &component) override;
};

struct MsvcToolset : public GenericToolset
{
    MsvcToolset();
    std::string getUnityCommand(const std::string &program, const std::string &compileFlags, const std::string &outputFile, const File *inputFile, const std::set<std::string> &includes, std::vector<std::vector<Component *>> linkDeps) override;
    std::string getCompileCommand(const std::string &program, const std::string &compileFlags, const std::string &outputFile, const File *inputFile, const std::set<std::string> &includes, bool hasModules) override;
    std::string getPrecompileCommand(const std::string &program, const std::string &compileFlags, const std::string &outputFile, const File *inputFile, const std::set<std::string> &includes, bool hasModules) override;
    std::string getArchiverCommand(const std::string &program, const std::string &outputFile, const std::vector<File *> inputs) override;
    std::string getLinkerCommand(const std::string &program, const std::string &outputFile, const std::vector<File *> objects, std::vector<std::vector<Component *>> linkDeps) override;
    std::string getUnittestCommand(const std::string &program) override;
    std::string getBmiNameFor(const File &file) override;
    std::string getObjNameFor(const File &file) override;
    std::string getLibNameFor(const Component &component) override;
    std::string getExeNameFor(const Component &component) override;
};

