#include "loader.h"

char* loadFile(const char* path, size_t* length){
    // Open File
    FILE* file = fopen(path, "rb");
    if(file == NULL) return 0;

    // Calculate File Size
    fseek(file, 0, SEEK_END);
    *length = ftell(file);
    rewind(file);

    // Allocate Memory
    char* data = (char*) malloc(*length);

    // Load File
    fread(data, sizeof(char), *length, file);
    fclose(file);

    return data;
}