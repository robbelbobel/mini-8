#include "loader.h"

char* loadFile(const char* path){
    // Open File
    FILE* file = fopen(path, "rb");
    if(file == NULL) return 0;

    // Calculate File Size
    fseek(file, 0, SEEK_END);
    uint16_t fSize = ftell(file);
    rewind(file);

    // Allocate Memory
    char* data = (char*) malloc(fSize);

    // Load File
    fgets(data, sizeof(char) * fSize, file);
    fclose(file);

    return data;
}