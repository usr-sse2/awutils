//
//  main.c
//  xor_checksum
//
//  Created by usrsse2 on 02.03.2023.
//

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

int main(int argc, const char * argv[]) {
    if (argc != 3) {
        printf("Usage:\n");
        printf("    add_checksum source destination\n");
        return 0;
    }
    FILE *src = fopen(argv[1], "rb");
    if (!src) {
        fprintf(stderr, "Failed to open source file %s\n", argv[1]);
        return 1;
    }
    uint32_t checksum = 0;
    uint32_t data = 0;
    
    while (true) {
        data = 0;
        size_t bytes_read = fread(&data, 1, sizeof(uint32_t), src);
        if (bytes_read == 0)
            break;
        if (bytes_read != sizeof(uint32_t))
            fprintf(stderr, "Warning: file size is not round to 4 bytes\n");
        checksum += data;
    }
    fclose(src);
    
    FILE *dst = fopen(argv[2], "wb");
    if (!dst) {
        fprintf(stderr, "Failed to create destination file %s\n", argv[2]);
        return 1;
    }
    if (fwrite(&checksum, sizeof(uint32_t), 1, dst) != 1) {
        fprintf(stderr, "Failed write checksum to the destination file %s\n", argv[2]);
        fclose(dst);
        return 1;
    }
    fclose(dst);
    return 0;
}
