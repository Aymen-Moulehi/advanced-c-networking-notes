#include <stdio.h>
#include <stdlib.h>
#include <rpc/xdr.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        exit(1);
    }

    FILE *file = fopen(argv[1], "w");
    XDR xhandle;
    
    int i = 42;
    float f = 3.14159;

    // Initialize XDR stream to encode into the file
    xdrstdio_create(&xhandle, file, XDR_ENCODE);

    printf("Encoding data: Int=%d, Float=%.2f\n", i, f);

    // Encode an integer and a float
    if (!xdr_int(&xhandle, &i) || !xdr_float(&xhandle, &f)) {
        fprintf(stderr, "Error: Encoding failed!\n");
        return 1;
    }

    xdr_destroy(&xhandle);
    fclose(file);
    printf("Data successfully encoded in '%s'\n", argv[1]);

    return 0;
}