/**********************************************************************************
 * @file    json.h
 * @brief   Thư viện phân tích cú pháp json đơn giản
 * @details Cung cấp các chức năng để phân tích và quản lý dữ liệu JSON có sẵn, 
 *          bao gồm các kiểu dữ liệu cơ bản như null, boolean, số, chuỗi, 
 *          mảng và object.
 * @version 1.0
 * @date    2025-03-19
 * @author  LongTruong
 **********************************************************************************/

 /* =====================================================[ Guard ]====================================================*/
#ifndef JSON_H
#define JSON_H

/* ============================================[ INCLUDE FILE ]============================================*/
#include <stdio.h>                  /**< Thư viện chứa hàm in ra màn hình   >**/
#include <stdlib.h>                 /**< Thư viện chứa hàm malloc, free      >**/
#include <string.h>                 /**< Thư viện chứa hàm xử lý chuỗi      >**/
#include <stddef.h>                 /**< Thư viện chứa hằng số NULL         >**/
#include <ctype.h>                  /**< Thư viện chứa hàm kiểm tra ký tự   >**/
#include <stdbool.h>                /**< Thư viện chứa kiểu dữ liệu bool    >**/

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


/* ========================================[ FUNCTION INPLEMENTATION ]======================================*/
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

/**
 * @brief   Giải phóng bộ nhớ của cấu trúc JSONvalue.
 * @details Hàm giải phóng toàn bộ bộ nhớ đã được cấp phát động 
 *          trong cấu trúc JSONvalue, bao gồm: mảng, chuỗi, object.
 * @param   json_value   [in] Con trỏ trỏ đến cấu trúc JSONvalue cần giải phóng.
 * @return  void
 **/
void free_json_value(JsonValue *json_value);

/**
 * @brief   In ra cấu trúc đã được phân tích của JSONvalue.
 * @param   json_value   [in] Con trỏ trỏ đến cấu trúc JSONvalue cần in ra.
 * @return  void
 **/
void test(JsonValue* json_value);

/* ===================================================[ Guard End ]===================================================*/
#endif // JSON_H