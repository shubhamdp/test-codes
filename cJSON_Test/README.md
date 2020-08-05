# cJSON_Test

Please refer https://stackoverflow.com/questions/55901690/json-parser-using-c/55901766#55901766 for more details.

Install cJSON library from below
	
	https://github.com/DaveGamble/cJSON

How to compile

	gcc test_cjson.c `pkg-config --libs --cflags libcjson`

Usage:

	$ ./a.out <letter> <freq>

Descipriton:

This will add an extra object to the json array and updates it to a file. Also at the end it prints the json file. json file should be present, empty file is not handled. Full error checks are not performed int this code. So please do it if you want to use this code.
