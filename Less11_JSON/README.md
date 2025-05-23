
---

# BÀI 11: JSON

## Tổng quan

- JSON là viết tắt của "__JavaScript Object Notation__" (Ghi chú về Đối tượng JavaScript).  

- Đây là một __định dạng truyền tải dữ liệu__ phổ biến trong lập trình và giao tiếp giữa các máy chủ và trình duyệt web, cũng như giữa các hệ thống khác nhau.  

- JSON được thiết kế để dễ đọc và dễ viết cho con người, cũng như dễ dàng để phân tích và tạo ra cho máy tính.


## Cấu Trúc 
- Định dạng JSON sử dụng các cặp __key – value__ để dữ liệu sử dụng.
- Chuỗi JSON được bao lại bởi dấu ngoặc nhọn {}.
- Các key của JSON bắt buộc phải đặt trong dấu nháy kép “".
- Nếu có nhiều dữ liệu thì dùng dấu phẩy , để ngăn cách.
- Value cho phép các kiểu dữ liệu cơ bản: numbers, String, Booleans, arrays, objects, null.

__Ví dụ:__
```c
// JSON1
{
  "name": "John Doe",
  "age": 30.1234,
  "city": "New York",
  "isStudent": true,
  "grades": [85, 90, 78]
}

// JSON2
"[50.456, true, [5, "hello world"]]"
```

## Phân tích JSON (Parse JSON)

Trong C, không có thư viện gốc hỗ trợ JSON. Vì vậy ta cần tự tạo ra 1 chương trình để có thể xử lý và phân tích các file JSON (parse JSON)

- Đầu tiên ta cần xác định kiểu dữ liệu được lưu trũ đó là gì.
- Tiếp theo xác định và lưu giá trị tương ứng với kiểu dữ liệu đó.
- Ta lặp đi lặp lại cho đến khi xử lý được hết các dữ liệu trong JSON đó.

__Cấu trúc lưu trữ JSON:__
```c
/* ===========================================[ TYPE DEFINITIONS ]==========================================*/
/**
 * @brief   Kiểu dữ liệu của JSON.
 **/
typedef enum {
    JSON_NULL,                      /**< Kiểu dữ liệu null                      >**/
    JSON_BOOLEAN,                   /**< Kiểu dữ liệu boolean  (true, false)    >**/
    JSON_NUMBER,                    /**< Kiểu dữ liệu số       (int, double     >**/
    JSON_STRING,                    /**< Kiểu dữ liệu chuỗi                     >**/
    JSON_ARRAY,                     /**< Kiểu dữ liệu mảng                      >**/
    JSON_OBJECT                     /**< Kiểu dữ liệu đối tượng                 >**/
} JsonType;

/**
 * @brief   Cấu trúc dữ liệu của JSON.
 * @details JSON là một cấu trúc dữ liệu có thể lưu trữ các kiểu dữ liệu cơ bản như 
 *          null, boolean, số, chuỗi, mảng và object.
 **/
typedef struct JsonValue {
    JsonType type;                  /**< Kiểu dữ liệu của JSONvalue             >**/
    union {                         /**< Dữ liệu của JSONvalue                  >**/
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
```

__Các hàm xử lý và phân tích từng kiểu dữ liệu JSON:__
```c
/**
 * @brief   Phân tích giá trị null từ JSON
 * @details Hàm phân tích giá trị null từ chuỗi JSON 
 *          và trả về cấu trúc JSONNULL hoặc NULL nếu lỗi.
 * @param   json   [in, out] Con trỏ trỏ đến chuỗi JSON.
 * @return  JsonValue*   Con trỏ trỏ đến cấu trúc JSON_NULL hoặc NULL nếu lỗi.
 **/
JsonValue *parse_null(const char **json);

/**
 * @brief   Phân tích giá trị boolean (true/false) từ JSON
 * @param   json   [in, out] Con trỏ trỏ đến chuỗi JSON.
 * @return  JsonValue*   Con trỏ trỏ đến cấu trúc JSON_BOOLEAN hoặc NULL nếu lỗi.
 **/
JsonValue *parse_boolean(const char **json);

/**
 * @brief   Phân tích giá trị Number từ JSON
 * @param   json   [in, out] Con trỏ trỏ đến chuỗi JSON.
 * @return  JsonValue*   Con trỏ trỏ đến cấu trúc JSON_NUMBER hoặc NULL nếu lỗi.
 **/
JsonValue *parse_number(const char **json);

/**
 * @brief   Phân tích giá trị chuỗi từ JSON
 * @param   json   [in, out] Con trỏ trỏ đến chuỗi JSON.
 * @return  JsonValue*   Con trỏ trỏ đến cấu trúc JSON_STRING hoặc NULL nếu lỗi.
 **/
JsonValue *parse_string(const char **json);

/**
 * @brief   Phân tích giá trị mảng từ JSON
 * @param   json   [in, out] Con trỏ trỏ đến chuỗi JSON.
 * @return  JsonValue*   Con trỏ trỏ đến cấu trúc JSON_ARRAY hoặc NULL nếu lỗi.
 **/
JsonValue *parse_array(const char **json);

/**
 * @brief   Phân tích giá trị object từ JSON
 * @param   json   [in, out] Con trỏ trỏ đến chuỗi JSON.
 * @return  JsonValue*   Con trỏ trỏ đến cấu trúc JSON_OBJECT hoặc NULL nếu lỗi.
 **/
JsonValue *parse_object(const char **json);

/**
 * @brief   Phân tích tổng quát một giá trị JSONvalue.
 * @details Hàm gọi các hàm parse tương ứng với từng loại JSONvalue
 *          như: null, boolean, number, string, array, object. 
 * @param   json   [in, out] Con trỏ trỏ đến chuỗi JSON.
 * @return  JsonValue*   Con trỏ trỏ đến JSONvalue đã phân tích hoặc NULL nếu lỗi.
 **/
JsonValue *parse_json(const char **json);
```

## Ví Dụ và Kết Quả của parse JSON

__Ví dụ:__
```c
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

JsonValue *parse_json(const char **json);

void free_json_value(JsonValue *json_value);

static void skip_whitespace(const char **json) {
    while (isspace(**json)) {
        (*json)++;
    }
}

JsonValue *parse_null(const char **json) {
    skip_whitespace(json);
    if (strncmp(*json, "null", 4) == 0) {
        JsonValue *value = (JsonValue *) malloc(sizeof(JsonValue));
        value->type = JSON_NULL;
        *json += 4;
        return value;
    }
    return NULL;
}

JsonValue *parse_boolean(const char **json) {
    skip_whitespace(json);
    JsonValue *value = (JsonValue *) malloc(sizeof(JsonValue));
    if (strncmp(*json, "true", 4) == 0) {
        value->type = JSON_BOOLEAN;
        value->value.boolean = true;
        *json += 4;
    } else if (strncmp(*json, "false", 5) == 0) {
        value->type = JSON_BOOLEAN;
        value->value.boolean = false;
        *json += 5;
    } else {
        free(value);
        return NULL;
    }
    return value;
}

JsonValue *parse_number(const char **json) {
    skip_whitespace(json);
    char *end;

    double num = strtod(*json, &end);   // string to double: double strtod(const *char str, char **endptr)
                                        // str là chuỗi cần đọc lấy số, endptr là vị trí số cuối cùng đọc đươc +1
    // nếu lỗi không đọc được số => end = *json => kiểm tra xem lỗi không
    if (end != *json) {
        JsonValue *value = (JsonValue *) malloc(sizeof(JsonValue));
        value->type = JSON_NUMBER;
        value->value.number = num;
        *json = end;
        return value;
    }
    return NULL;
}

JsonValue *parse_string(const char **json) {
    skip_whitespace(json);

    // đánh dáu điểm bắt đầu chuỗi
    // duyệt tìm điểm kết thúc chuỗi => trừ đi điểm đánh dáu = độ lớn
    // cấp phát động và gán giá trị chuỗi
    if (**json == '\"') {
        (*json)++;
        const char *start = *json;
        while (**json != '\"' && **json != '\0') {
            (*json)++;
        }
        if (**json == '\"') {
            size_t length = *json - start; // 3
            char *str = (char *) malloc((length + 1) * sizeof(char));
            strncpy(str, start, length);
            str[length] = '\0';


            JsonValue *value = (JsonValue *) malloc(sizeof(JsonValue));
            value->type = JSON_STRING;
            value->value.string = str;
            (*json)++;
            return value;
        }
    }
    return NULL;
}

JsonValue *parse_array(const char **json) {
    skip_whitespace(json);

    // Bắt đầu tại đầu mảng => khởi tạo sẵn bộ nhớ cho array
    // Duyệt từng phần tử của mảng cho đến khi kết thúc mảng "]"
    // dùng while gọi hàm parse_json để lấy từng phần tử cho đến hết.

    if (**json == '[') {
        (*json)++;
        skip_whitespace(json);

        JsonValue *array_value = (JsonValue *)malloc(sizeof(JsonValue));
        array_value->type = JSON_ARRAY;
        array_value->value.array.count = 0;
        array_value->value.array.values = NULL;

        /*
        double arr[2] = {};
        arr[0] = 30;
        arr[1] = 70;
        */

        while (**json != ']' && **json != '\0') {
            JsonValue *element = parse_json(json); // 70
            if (element) {
                array_value->value.array.count++;
                array_value->value.array.values = (JsonValue *)realloc(array_value->value.array.values, array_value->value.array.count * sizeof(JsonValue));
                array_value->value.array.values[array_value->value.array.count - 1] = *element;
                free(element);
            } else {
                break;
            }
            skip_whitespace(json);
            if (**json == ',') {
                (*json)++;
            }
        }
        if (**json == ']') {
            (*json)++;
            return array_value;
        } else {
            free_json_value(array_value);
            return NULL;
        }
    }
    return NULL;
}

JsonValue *parse_object(const char **json) {
    skip_whitespace(json);

    // Bắt đầu tại đầu object => khởi tạo sẵn bộ nhớ cho object
    // Duyệt từng phần tử của object cho đến khi kết thúc object "}"
    // dùng while:
    //  gọi parse_String để lấy key - nếu lấy thành công key => lấy value
    //  nếu sau key có ':' => gọi hàm parse_json để lấy từng value của key.
    // tiếp tục như vậy cho đến khi hết phần tử trong obj '}'.

    if (**json == '{') {
        (*json)++;
        skip_whitespace(json);

        JsonValue *object_value = (JsonValue *)malloc(sizeof(JsonValue));
        object_value->type = JSON_OBJECT;
        object_value->value.object.count = 0;
        object_value->value.object.keys = NULL;
        object_value->value.object.values = NULL;

        while (**json != '}' && **json != '\0') {
            JsonValue *key = parse_string(json);
            if (key) {
                skip_whitespace(json);
                if (**json == ':') {
                    (*json)++;
                    JsonValue *value = parse_json(json);
                    if (value) {
                        object_value->value.object.count++;
                        object_value->value.object.keys = (char **)realloc(object_value->value.object.keys, object_value->value.object.count * sizeof(char *));
                        object_value->value.object.keys[object_value->value.object.count - 1] = key->value.string;

                        object_value->value.object.values = (JsonValue *)realloc(object_value->value.object.values, object_value->value.object.count * sizeof(JsonValue));
                        object_value->value.object.values[object_value->value.object.count - 1] = *value;
                        free(value);
                    } else {
                        free_json_value(key);
                        break;
                    }
                } else {
                    free_json_value(key);
                    break;
                }
            } else {
                break;
            }
            skip_whitespace(json);
            if (**json == ',') {
                (*json)++;
            }
        }
        if (**json == '}') {
            (*json)++;
            return object_value;
        } else {
            free_json_value(object_value);
            return NULL;
        }
    }
    return NULL;
}

JsonValue *parse_json(const char **json) { 
    while (isspace(**json)) {
        (*json)++;
    }

    switch (**json) {
        case 'n':
            return parse_null(json);
        case 't':
        case 'f':
            return parse_boolean(json);
        case '\"':
            return parse_string(json);
        case '[':
            return parse_array(json);
        case '{':
            return parse_object(json);
        default:    
            // isdigit() kiểm tra xem có phải ký tự số không
            // '-' là số âm
            if (isdigit(**json) || **json == '-') {

                return parse_number(json);
            } else {
                // Lỗi phân tích cú pháp
                return NULL;
            }
    }
}
////////////


/////////////
void free_json_value(JsonValue *json_value) {
    if (json_value == NULL) {
        return;
    }

    switch (json_value->type) {
        case JSON_STRING:
            free(json_value->value.string);
            break;

        case JSON_ARRAY:
            for (size_t i = 0; i < json_value->value.array.count; i++) {
                free_json_value(&json_value->value.array.values[i]);
            }
            free(json_value->value.array.values);
            break;

        case JSON_OBJECT:
            for (size_t i = 0; i < json_value->value.object.count; i++) {
                free(json_value->value.object.keys[i]);
                free_json_value(&json_value->value.object.values[i]);
            }
            free(json_value->value.object.keys);
            free(json_value->value.object.values);
            break;

        default:
            break;
    }
}

void test(JsonValue* json_value){
    if (json_value != NULL && json_value->type == JSON_OBJECT) {
        // Truy cập giá trị của các trường trong đối tượng JSON
        size_t num_fields = json_value->value.object.count;
        size_t num_fields2 = json_value->value.object.values->value.object.count;
        for (size_t i = 0; i < num_fields; ++i) {

            char* key = json_value->value.object.keys[i];
            JsonValue* value = &json_value->value.object.values[i];

            JsonType type = (int)(json_value->value.object.values[i].type);

            if(type == JSON_STRING){
                printf("%s: %s\n", key, value->value.string);
            }

            if(type == JSON_NUMBER){
                printf("%s: %f\n", key, value->value.number);
            }

            if(type == JSON_BOOLEAN){
                printf("%s: %s\n", key, value->value.boolean ? "True":"False");
            }

            if(type == JSON_OBJECT){
                printf("%s: \n", key);
                test(value);
            }

            if(type == JSON_ARRAY){
                printf("%s: ", key);
                for (int i = 0; i < value->value.array.count; i++)
                {
                   test(value->value.array.values + i);
                } 
                printf("\n");
            }
        }
    }
    else 
    {
            if(json_value->type == JSON_STRING){
                printf("%s ", json_value->value.string);
            }

            if(json_value->type == JSON_NUMBER){
                printf("%f ", json_value->value.number);
            }

            if(json_value->type == JSON_BOOLEAN){
                printf("%s ", json_value->value.boolean ? "True":"False");
            }

            if(json_value->type == JSON_OBJECT){
                printf("%s: \n", json_value->value.object.keys);
                test(json_value->value.object.values);
                           
            }
    }
}

int main(int argc, char const *argv[])
{
     // Chuỗi JSON đầu vào
    
    const char* json_str = "{"
                        "\"1001\":{"
                          "\"SoPhong\":3,"
                          "\"NguoiThue\":{"
                            "\"Ten\":\"Nguyen Van A\","
                            "\"CCCD\":\"1920517781\","
                            "\"Tuoi\":26,"
                            "\"ThuongTru\":{"
                              "\"Duong\":\"73 Ba Huyen Thanh Quan\","
                              "\"Phuong_Xa\":\"Phuong 6\","
                              "\"Tinh_TP\":\"Ho Chi Minh\""
                            "}"
                          "},"
                          "\"SoNguoiO\":{"
                            "\"1\":\"Nguyen Van A\","
                            "\"2\":\"Nguyen Van B\","
                            "\"3\":\"Nguyen Van C\""
                          "},"
                          "\"TienDien\": [24, 56, 98],"
                          "\"TienNuoc\":30.000"
                        "},"
                        "\"1002\":{"
                          "\"SoPhong\":5,"
                          "\"NguoiThue\":{"
                            "\"Ten\":\"Phan Hoang Trung\","
                            "\"CCCD\":\"012345678912\","
                            "\"Tuoi\":24,"
                            "\"ThuongTru\":{"
                              "\"Duong\":\"53 Le Dai Hanh\","
                              "\"Phuong_Xa\":\"Phuong 11\","
                              "\"Tinh_TP\":\"Ho Chi Minh\""
                            "}"
                          "},"
                          "\"SoNguoiO\":{"
                            "\"1\":\"Phan Van Nhat\","
                            "\"2\":\"Phan Van Nhi\","
                            "\"2\":\"Phan Van Tam\","
                            "\"3\":\"Phan Van Tu\""
                          "},"
                          "\"TienDien\":23.000,"
                          "\"TienNuoc\":40.000"
                        "}"
                      "}";

    // Phân tích cú pháp chuỗi JSON
    JsonValue* json_value = parse_json(&json_str);

    // Kiểm tra kết quả phân tích cú pháp
    test(json_value);

    // Giải phóng bộ nhớ được cấp phát cho JsonValue
    free_json_value(json_value);
    
        //printf("test = %x", '\"');
       // hienthi(5);
    return 0;
}
```

__Kết quả:__
```c
1001: 
SoPhong: 3.000000
NguoiThue: 
Ten: Nguyen Van A
CCCD: 1920517781
Tuoi: 26.000000
ThuongTru: 
Duong: 73 Ba Huyen Thanh Quan
Phuong_Xa: Phuong 6
Tinh_TP: Ho Chi Minh
SoNguoiO: 
1: Nguyen Van A
2: Nguyen Van B
3: Nguyen Van C
TienDien: 24.000000 56.000000 98.000000 
TienNuoc: 30.000000
1002: 
SoPhong: 5.000000
NguoiThue:
Ten: Phan Hoang Trung
CCCD: 012345678912
Tuoi: 24.000000
ThuongTru:
Duong: 53 Le Dai Hanh
Phuong_Xa: Phuong 11
Tinh_TP: Ho Chi Minh
SoNguoiO:
1: Phan Van Nhat
2: Phan Van Nhi
2: Phan Van Tam
3: Phan Van Tu
TienDien: 23.000000
TienNuoc: 40.000000
```
