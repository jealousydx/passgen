#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>


void print_help() {
    printf("Usage: passgen [OPTIONS]\n");
    printf("Generate random passwords.\n\n");

    printf("Options:\n");
    printf("  -L <length>    Set password length\n");
    printf("  -N <count>     Generate multiple passwords\n");
    printf("  -h             Show this help message\n");
}

int main(int argc, char* argv[]) {
	int length = 20;
	int count = 1;
	
	int opt;
	while ((opt = getopt(argc, argv, "L:N:h")) != -1) {
		switch (opt) {
			case 'L':
				length = strtol(optarg, NULL, 10);
				break;
			case 'N':
				count = strtol(optarg, NULL, 10);
				break;
			case 'h':
				print_help();
				return 0;
			default:
				print_help();
				return 1;
		}
	}

	if (length < 1 || length > 128) {
    	fprintf(stderr, "Error: invalid password length %d. It must be between 1 and 128.\n", length);
    	return 1;
	}

	int fd = open("/dev/urandom", O_RDONLY);
	if (fd < 0) {
    	perror("passgen: cannot open /dev/urandom");
    	return 1;
	}

	uint8_t buf[length];
	ssize_t n;
	char c;
	for (int i = 0; i < count; i++) {
		n = read(fd, buf, sizeof(buf));		
		if (n != sizeof(buf)) {
			perror("read");
			close(fd);
			return 1;
		}

		for (int j = 0; j < length; j++) {
			c = (char)(33 + (buf[j] % 94)); 	
			printf("%c", c);
		}

		printf("\n");
	}

	close(fd);
	
	return 0;
}