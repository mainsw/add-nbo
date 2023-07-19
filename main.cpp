#include <stdio.h>
#include <stdint.h>
#include <arpa/inet.h>
#include <cstdlib>

uint32_t read_uint32_from_file(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        perror("Error opening file");
        exit(1);
    }

    uint32_t value;
    if (fread(&value, sizeof(uint32_t), 1, file) != 1) {
        perror("Error reading from file");
        fclose(file);
        exit(1);
    }

    fclose(file);
    return ntohl(value); // Convert from network byte order (big-endian) to host byte order
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <file1> <file2>\n", argv[0]);
        return 1;
    }

    const char* file1 = argv[1];
    const char* file2 = argv[2];

    uint32_t num1 = read_uint32_from_file(file1);
    uint32_t num2 = read_uint32_from_file(file2);

    printf("%u(0x%x) + %u(0x%x) = %u(0x%x)\n", num1, num1, num2, num2, num1+num2, num1+num2);

    return 0;
}
