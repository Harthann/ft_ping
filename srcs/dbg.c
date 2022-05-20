#include <stdio.h>
#include <stdlib.h>


void dbg_dump_bytes(const void* data, size_t size) {
	char ascii[17];
	size_t i;
	ascii[16] = '\0';
	for (i = 0; i < size; ++i) {
		if (i % 16 == 0)
			fprintf(stderr, "%p: ", data + i);
		fprintf(stderr, "%02x ", ((unsigned char*)data)[i]);
		if (((unsigned char*)data)[i] >= ' ' && ((unsigned char*)data)[i] <= '~') {
			ascii[i % 16] = ((unsigned char*)data)[i];
		} else {
			ascii[i % 16] = '.';
		}
		if ((i+1) % 8 == 0 || i+1 == size) {
			fprintf(stderr, " ");
			if ((i+1) % 16 == 0) {
				fprintf(stderr, "|  %s \n", ascii);
			} else if (i+1 == size) {
				ascii[(i+1) % 16] = '\0';
				if ((i+1) % 16 <= 8) {
					fprintf(stderr, " ");
				}
				fprintf(stderr, "%*.0d", 3 * (16 - (((int)i + 1) % 16)), 0);
				fprintf(stderr, "|  %s \n", ascii);
			}
		}
	}
}

