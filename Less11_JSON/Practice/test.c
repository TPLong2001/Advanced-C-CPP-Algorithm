#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <ctype.h>
#include <stdbool.h>

typedef enum {
    JSON_NULL,
    JSON_BOOLEAN,
    JSON_NUMBER,
    JSON_STRING,
    JSON_ARRAY,
    JSON_OBJECT
} JsonType;


typedef struct JsonValue {
    JsonType type;
    union {
        int boolean;
        double number;
        char *string;
        struct {
            struct JsonValue *values;
            size_t count;
        } array;
        struct {
            char **keys;
            struct JsonValue *values;
            size_t count;
        } object;
    } value;
} JsonValue;


/*
 * "[50.456, true, [5, "hello world"]]"
 */

 int main()
 {
    JsonValue *json_value = (JsonValue *)malloc(sizeof(JsonValue));

    json_value->type = JSON_ARRAY;
    json_value->value.array.count = 3;
    json_value->value.array.values = (JsonValue *)malloc(json_value->value.array.count * sizeof(JsonValue));

    // value 0
    json_value->value.array.values[0].type = JSON_NUMBER;
    json_value->value.array.values[0].value.number = 50.456;

    // value 1
    json_value->value.array.values[1].type = JSON_BOOLEAN;
    json_value->value.array.values[1].value.boolean = true;

    // value 2
    json_value->value.array.values[2].type = JSON_ARRAY;
    json_value->value.array.values[2].value.array.count = 2;
    json_value->value.array.values[2].value.array.values = (JsonValue *)malloc(json_value->value.array.values[2].value.array.count * sizeof(JsonValue));

    // value 2.0
    json_value->value.array.values[2].value.array.values[0].type = JSON_NUMBER;
    json_value->value.array.values[2].value.array.values[0].value.number = 5;

    // value 2.1
    json_value->value.array.values[2].value.array.values[1].type = JSON_STRING;
    json_value->value.array.values[2].value.array.values[1].value.string = "hello world";

    

    return 0;
 }