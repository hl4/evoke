from conans import ConanFile, tools, CMake


class EvokeConan(ConanFile):
    requires = "boost/[>1.6.9]@conan/stable"
    generators = "cmake_find_package", "cmake_paths"
    build_requires = "cmake_installer/[>3.12]@conan/stable"

    def build(self):
        cmake = CMake(self) # it will find the packages by using our auto-generated FindXXX.cmake files
        cmake.configure()
        cmake.build()