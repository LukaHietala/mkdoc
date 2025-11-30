#include <stdio.h>
#include <stdlib.h>
#include <md4c-html.h>

/* Writes HTML output to file */
void output_callback(const MD_CHAR *text, MD_SIZE size, void *userdata) {
	FILE *fp = (FILE *)userdata;
	fwrite(text, 1, size, fp);
}


int main() {
	FILE *md_file = fopen("test.md", "rb");

	if (!md_file) {
		perror("Failed to open test.md");
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

	/* TODO: check that file size is same as fread result */
	fread(input, 1, file_size, md_file);
	input[file_size] = '\0';
	fclose(md_file);

	FILE *html_file = fopen("test.html", "w");

	if (!html_file) {
		perror("Failed to open test.html");
		free(input);
		return 1;
	}

	md_html(input, (MD_SIZE)file_size, output_callback, html_file, 0, 0);
	
	fclose(html_file);
	free(input);
	return 0;
}