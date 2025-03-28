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

typedef struct JSONvalue
{
    JSONType type;
    
    union {
        int boolean;
        double number;
        char *string;

        struct{
            size_t count;
            JSONvalue *value;
        }array;

        struct{
            size_t count;
            char **key;
            JSONvalue *value;
        }object;
    }value;

}JSONvalue;

/*
{
  "name": "John Doe",
  "age": 30.1234,
  "city": "New York",
  "isStudent": true,
  "grades": [85, 90, 78]
}
*/

int main(){

    // cap phat dong bo nho ban dau
    JSONvalue *json_value = (JSONvalue *)malloc(sizeof(JSONvalue));

    // khoi tao bo nho cho tung phan tu
    json_value->type = JSON_OBJECT;
    json_value->value.object.count = 5;
    json_value->value.object.key = (char **)malloc(json_value->value.object.count * sizeof(char*));
    json_value->value.object.value = (JSONvalue *)malloc(json_value->value.object.count * sizeof(JSONvalue));

    // phần tử 1
    json_value->value.object.key[0] = "name";
    json_value->value.object.value[0].type = JSON_STRING;
    json_value->value.object.value[0].value.string = "John Doe";

    // phần tử 2
    json_value->value.object.key[1] = "age";
    json_value->value.object.value[1].type = JSON_NUMBER;
    json_value->value.object.value[1].value.number = 30.1234;

    // phan tu 3
    json_value->value.object.key[2] = "city";
    json_value->value.object.value[2].type = JSON_STRING;
    json_value->value.object.value[2].value.string = "New York";

    // phan tu 4
    json_value->value.object.key[3] = "isStudent";
    json_value->value.object.value[3].type = JSON_BOOLEAN;
    json_value->value.object.value[3].value.boolean = true;

    // phan tu 5
    json_value->value.object.key[4] = "grades";
    json_value->value.object.value[4].type = JSON_ARRAY;
    json_value->value.object.value[4].value.array.count = 3;  
    json_value->value.object.value[4].value.array.value = (JSONvalue *)malloc( json_value->value.object.value[4].value.array.count * sizeof(JSONvalue));

    // [85, 90, 78]
    // phan tu 5.0
    json_value->value.object.value[4].value.array.value[0].type = JSON_NUMBER;
    json_value->value.object.value[4].value.array.value[0].value.number = 85;

    // phan tu 5.1
    json_value->value.object.value[4].value.array.value[1].type = JSON_NUMBER;
    json_value->value.object.value[4].value.array.value[1].value.number = 90;

    // phan tu 5.2
    json_value->value.object.value[4].value.array.value[2].type = JSON_NUMBER;
    json_value->value.object.value[4].value.array.value[2].value.number = 78;

    return 0;
}