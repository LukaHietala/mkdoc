#include <stdio.h>
#include <stdlib.h>
#include <md4c-html.h>

/* Writes HTML output to file */
void output_callback(const MD_CHAR *text, MD_SIZE size, void *userdata) {
	FILE *fp = (FILE *)userdata;
	fwrite(text, 1, size, fp);
}


int main(int argc, char *argv[]) {
	if (argc < 3) {
		fprintf(stderr, "Usage: %s <input.md> <output.html>\n", argv[0]);
		return 1;
	}

	FILE *md_file = fopen(argv[1], "rb");

	if (!md_file) {
		perror("Failed to open input file");
		return 1;
	}

	fseek(md_file, 0, SEEK_END);
	long file_size = ftell(md_file);
	fseek(md_file, 0, SEEK_SET);

	char *input = malloc(file_size + 1);
	if (!input) {
		fclose(md_file);
		return 1;
	}

	size_t read_size = fread(input, 1, file_size, md_file);
	if (read_size != (size_t)file_size) {
		perror("failed to read entire file");
		free(input);
		fclose(md_file);
		return 1;
	}
	input[file_size] = '\0';
	fclose(md_file);

	FILE *html_file = fopen(argv[2], "w");

	if (!html_file) {
		perror("failed to open output file");
		free(input);
		return 1;
	}

	md_html(input, (MD_SIZE)file_size, output_callback, html_file, 0, 0);

	fclose(html_file);
	free(input);
	return 0;
}