#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <cjson/cJSON.h>

#define MAX_BUF 1024
#define FILE_NAME "json.txt"

/* This function adds the new object to the json file */
static cJSON *create_object(int val_letter, int val_freq)
{
	cJSON *obj = NULL;
	cJSON *freq = NULL;
	cJSON *letter = NULL;

	/* create cJSON object */
	obj = cJSON_CreateObject();
	freq = cJSON_CreateNumber(val_freq);
	letter = cJSON_CreateNumber(val_letter);

	cJSON_AddItemToObject(obj, "Letter", letter);
	cJSON_AddItemToObject(obj, "Freq", freq);

	return obj;
}

/* please free allocated object with cJSON_Delete() after use */
static cJSON *read_json()
{
	char json_buf[1024];
	cJSON *obj = NULL;
	FILE *fp = NULL;
	size_t bytes_read = 0;

	/* read json string from file */
	fp = fopen(FILE_NAME, "r");
	if (!fp) {
		printf("failed to read from file\n");
		return NULL;
	}
	bytes_read = fread(json_buf, sizeof(char), sizeof(json_buf), fp);
	if (bytes_read <= 0) {
		printf("failed to read json string\n");
		fclose(fp);
		return NULL;
	}
	fclose(fp);

	obj = cJSON_Parse(json_buf);
	if (!obj) {
		printf("failed to parse json string from file");
		return NULL;
	}

	return obj;
}

static int write_json(cJSON *json)
{
	char *json_str = NULL;
	FILE *fp;
	size_t bytes_wrote = 0;
	
	json_str = cJSON_Print(json);

	fp = fopen(FILE_NAME".1", "w");
	if (!fp) {
		printf("failed to open file\n");
		return 0;
	}

	bytes_wrote = fwrite(json_str, sizeof(char), strlen(json_str), fp);
	if (bytes_wrote < 1) {
		printf("failed to write to file\n");
		return 0;
	}
	fclose(fp);

	rename(FILE_NAME".1", FILE_NAME);
	return 1;
}

static int add_object(int letter, int freq)
{
	cJSON *json = NULL;
	cJSON *new_obj = NULL;
	int rc = 0;

	json = read_json();
	if (!json) {
		printf("failed to read\n");
		return 0;
	}

	new_obj = create_object(letter, freq);

	cJSON_AddItemToArray(json, new_obj);

	rc = write_json(json);
	if (json)
		cJSON_Delete(json);

	return rc;
}

/* This is to verify our objects are there or not */
static void parse_print_json()
{
	cJSON *json = read_json();
	cJSON *obj_in_arr= NULL;
	cJSON *freq = NULL;
	cJSON *letter = NULL;

	int i;
	int array_size = 0;

	if (!json) {
		printf("json parse failed\n");
		return;
	}

	if (cJSON_IsArray(json)) {
		array_size = cJSON_GetArraySize(json);
		for (i = 0; i < array_size; i++) {
			obj_in_arr = cJSON_GetArrayItem(json, i);
			if (obj_in_arr) {
				freq = cJSON_GetObjectItem(obj_in_arr, "Freq");
				if (cJSON_IsNumber(freq)) {
					printf("Letter: %d\n", freq->valueint);
				}
				letter = cJSON_GetObjectItem(obj_in_arr, "Letter");
				if (cJSON_IsNumber(letter)) {
					printf("Freq: %d\n", letter->valueint);
				}
				printf("\n");
			}
		}

	}

	if (json)
		cJSON_Delete(json);
}

int main(int argc, char **argv)
{
	if (argc != 3) {
		printf("Usage: %s %s %s\n", argv[0], "<letter>", "<freq>");
		return 1;
	}

	add_object(atoi(argv[1]), atoi(argv[2]));

	parse_print_json();

	return 0;
}

