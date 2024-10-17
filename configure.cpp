#include <string>
#include <iostream>

bool getPath(int argc, char** argv, std::string& path, std::string& folder_name)
{
    std::string m_path(argv[0]);
    size_t position = m_path.find_last_of("/\\");
    folder_name = m_path.substr(0, position);
    position = folder_name.find_last_of("/\\");
    folder_name = folder_name.substr(position + 1);

    std::string arg;
    std::string arg_ex = "path=";
    for (int i = 1; i < argc; ++i)
    {
        arg = argv[i];
        if (arg.substr(0, arg_ex.size()) == arg_ex)
        {
            size_t i = arg.find_last_of('=');
            path = arg.substr(i + 1);
            return true;
        }
    }
    return false;
}

bool generateEntry(std::string& file_name, std::string& folder_name)
{
    FILE* pFile = fopen(file_name.c_str(), "w");

    if (!pFile)
    {
        printf("ERROR: file wasn't opened");
        return false;
    }



    fprintf(pFile, "#include \"Structs/AGState.h\"\n");
    fprintf(pFile, "#include \"Game.h\"\n\n");

    fprintf(pFile, "class A%sGame : public AGame\n", folder_name.c_str());
    fprintf(pFile, "{\n");
    fprintf(pFile, "public:\n");
    fprintf(pFile, "    A%sGame()\n", folder_name.c_str());
    fprintf(pFile, "    {\n");
    fprintf(pFile, "        // add Levels.push_back(your_level);\n");
    fprintf(pFile, "    }\n");

    fprintf(pFile, "} %sGame;\n\n", folder_name.c_str());

    fprintf(pFile, "AGGame AGGameController = {\n");
    fprintf(pFile, "    .Game = reinterpret_cast<AGame*>(&%sGame),\n", folder_name.c_str());
    fprintf(pFile, "};");

    fclose(pFile);

    return true;
}

bool generateCmake(std::string& file_name, std::string& folder_name, std::string& path)
{
    FILE* pFile = fopen("CMakeLists.txt", "w");
    if (!pFile)
    {
        printf("ERROR: file wasn't opened");
        return false;
    }
    fprintf(pFile, "cmake_minimum_required(VERSION 3.10)\n\n");

    fprintf(pFile, "set(CMAKE_CXX_STANDARD 20)\n");
    fprintf(pFile, "set(CMAKE_CXX_STANDARD_REQUIRED ON)\n\n");

    fprintf(pFile, "set(AENGINE_BUILD FALSE CACHE BOOL \"\")\n\n");

    fprintf(pFile, "set(ProjName %s)\n\n", folder_name.c_str());

    fprintf(pFile, "project(${ProjName})\n\n");

    fprintf(pFile, "add_subdirectory(%s/AEngine)\n\n", path.c_str());

    fprintf(pFile, "add_executable(${ProjName} %s)\n\n", file_name.c_str());

    fprintf(pFile, "target_include_directories(${ProjName}\n");
    fprintf(pFile, "    PRIVATE\n");
    fprintf(pFile, "        %s/AEngine/src\n", path.c_str());
    fprintf(pFile, ")\n");

    fprintf(pFile, "target_link_libraries(${ProjName} AEngine)\n\n");
    fclose(pFile);

    return true;
}

int main(int argc, char** argv) {
    std::string path, folder_name;
    if (argc < 2 || !getPath(argc, argv, path, folder_name))
    {
        std::cout << "You should pass relative path like \"path=include\\\"" << std::endl;
        return 1;
    }


    std::string file_name = folder_name + ".cpp";
    
    if (!generateEntry(file_name, folder_name))
        return 1;
    
    if (!generateCmake(file_name, folder_name, path))
        return 1;

    

    return 0;
}