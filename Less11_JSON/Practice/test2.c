#include <stdio.h>
#include <stdbool.h>

typedef enum
{
    JSON_NULL,
    JSON_BOOLEAN,
    JSON_NUMBER,
    JSON_STRING,
    JSON_ARRAY,
    JSON_OBJECT
} JSONType;

typedef struct JSONValue
{
    JSONType type;
    
    union
    {
        int     boolean; // 0 hoặc 1, 0 = false, 1 = true
        double  number;
        char    *string;

        struct
        {
            struct JSONValue *values;
            size_t count;
        } array;

        struct
        {
            char **keys; // ["key1", "key2", "key3"]
            struct JSONValue *values;
            size_t count;
        } object;

    } value;
} JSONValue;

/*
{
  "name": "John Doe",
  "age": 30.1234,
  "city": "New York",
  "isStudent": true,
  "grades": [85, 90, 78]
}
*/

void create()
{
    JSONValue *json_str = (JSONValue*)malloc(sizeof(JSONValue));

    json_str->type = JSON_OBJECT;
    json_str->value.object.count = 5;

    json_str->value.object.keys = (char**)malloc(json_str->value.object.count * sizeof(char*));
    json_str->value.object.values = (JSONValue*)malloc(json_str->value.object.count * sizeof(JSONValue));

    // tạo cặp key-value 1
    json_str->value.object.keys[0] = "name";
    json_str->value.object.values[0].type = JSON_STRING;
    json_str->value.object.values[0].value.string = "John Doe";

    // tạo cặp key-value 2
    json_str->value.object.keys[1] = "age";
    json_str->value.object.values[1].type = JSON_NUMBER;
    json_str->value.object.values[1].value.number = 30.1234;

    // tạo cặp key-value 3

    // tạo cặp key-value 4

    // tạo cặp key-value 5
    json_str->value.object.keys[4] = "grades";
    json_str->value.object.values[4].type = JSON_ARRAY;
    json_str->value.object.values[4].value.array.count = 3;

    json_str->value.object.values[4].value.array.values = (JSONValue*)malloc(json_str->value.object.values[4].value.array.count * sizeof(JSONValue));
    json_str->value.object.values[4].value.array.values[0].type = JSON_NUMBER;

    // phần tử đầu tiên trong mảng
    json_str->value.object.values[4].value.array.values[0].value.number = 85;
    
}
