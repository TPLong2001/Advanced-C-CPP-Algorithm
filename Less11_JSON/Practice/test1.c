#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum{
    JSON_NULL,
    JSON_BOOLEAN,
    JSON_NUMBER,
    JSON_STRING,
    JSON_ARRAY,
    JSON_OBJECT
} JSONType;

typedef struct JSONValue{
    JSONType type;
    union{
        int     boolean; // 0 hoặc 1, 0 = false, 1 = true
        double  number;
        char    *string;
        struct{
            struct JSONValue *values;
            size_t count;
        } array;
        struct{
            char **keys; // ["key1", "key2", "key3"]
            struct JSONValue *values;
            size_t count;
        } object;
    } value;
} JSONValue;

/*
 * "[50.456, true, [5, "hello world"]]"
 */


int main(int argc, char const *argv[])
{
    JSONValue *json_str = (JSONValue*)malloc(sizeof(JSONValue));

    json_str->type = JSON_ARRAY;
    json_str->value.array.count = 3;
    json_str->value.array.values = (JSONValue*)malloc(json_str->value.array.count * sizeof(JSONValue));

    // phần tử 0
    json_str->value.array.values[0].type = JSON_NUMBER;
    json_str->value.array.values[0].value.number = 50.456;

    // phần tử 1
    json_str->value.array.values[1].type = JSON_BOOLEAN;
    json_str->value.array.values[1].value.boolean = true;

    // phần tử 2
    json_str->value.array.values[2].type = JSON_ARRAY;
    json_str->value.array.values[2].value.array.count = 2;
    json_str->value.array.values[2].value.array.values = (JSONValue*)malloc(json_str->value.array.values[2].value.array.count * sizeof(JSONValue));

    // phần tử 2.0
    json_str->value.array.values[2].value.array.values[0].type = JSON_NUMBER;
    json_str->value.array.values[2].value.array.values[0].value.number = 5;

    // phần tử 2.1
    json_str->value.array.values[2].value.array.values[1].type = JSON_STRING;
    json_str->value.array.values[2].value.array.values[1].value.string = "hello world";

    return 0;
}
