#pragma once

#include <dlfcn.h>
#include <string>
#include <stdexcept>
#include <vector>
#include <iostream>
class  DLLoader {
        std::vector<void *> handle;
        void *(*fctPtr)(std::vector<std::vector<std::string>> &);
        std::string m_jsonPath;
public:
        DLLoader() = default;
        virtual ~DLLoader() 
        {
                unload();
        };
public:
        void unload(void) 
        {
                for (uint i = 0; i < handle.size(); i++) {
                        if (handle[i])
                                dlclose(handle[i]);
                }
        }
        void load(const std::string path) 
        {
                m_jsonPath = path;
                std::cout << m_jsonPath << std::endl;
                handle.push_back(dlopen(m_jsonPath.c_str(), RTLD_LAZY));
                if (handle[handle.size()-1] == NULL)
                        throw std::runtime_error("DLLoader::load can't load this script");
        };
        void *getInstance(std::string jsonPath, std::vector<std::vector<std::string>> &vector)
        {
                void *tmp;
                char *str;

                *(void **)(&fctPtr) = dlsym(handle[handle.size()-1], jsonPath.c_str());
                if ((str = dlerror()) != NULL) {
                        printf("%s | %s\n", str, m_jsonPath.c_str());
                        throw std::runtime_error("Error on Script file");
                }
                tmp = fctPtr(vector);
                return tmp;
        };
};
