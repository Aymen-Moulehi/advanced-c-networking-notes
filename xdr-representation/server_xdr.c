#include <stdio.h>
#include <stdlib.h>
#include <rpc/xdr.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        exit(1);
    }

    FILE *file = fopen(argv[1], "r");
    XDR xhandle;
    
    int i;
    float f;

    // Initialize XDR stream to decode from the file
    xdrstdio_create(&xhandle, file, XDR_DECODE);

    // Decode in the exact same order as encoded
    if (xdr_int(&xhandle, &i) && xdr_float(&xhandle, &f)) {
        printf("Decoded values from XDR stream:\n");
        printf("Integer: %d\n", i);
        printf("Float:   %.5f\n", f);
    } else {
        fprintf(stderr, "Error: Decoding failed!\n");
    }

    xdr_destroy(&xhandle);
    fclose(file);

    return 0;
}