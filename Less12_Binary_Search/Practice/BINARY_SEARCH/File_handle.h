/**********************************************************************************
 * @file    File_handle.h
 * @brief   Đọc dữ liệu từ file CSV chứa thông tin người dùng và lưu vào danh sách liên kết.
 * @details File này mở file CSV, đọc từng dòng thông tin và phân tích dữ liệu,
 *          sau đó lưu thông tin người dùng vào danh sách liên kết.
 * @version 1.0
 * @date    2025-03-25
 * @author  LongTruong
 **********************************************************************************/
/* =====================================================[ Guard ]====================================================*/
#ifndef FILE_HANDLE_H
#define FILE_HANDLE_H

/* ============================================[ INCLUDE FILE ]=============================================*/
#include "Binary_search_tree.h"

/* ==========================================[ MACRO DEFINITIONS ]==========================================*/
#define DATABASE_PATH "Database.csv"        /**< Đường dẫn đến file CSV chứa dữ liệu */

/* ========================================[ FUNCTION INPLEMENTATION ]======================================*/
/**
 * @brief   Giải phóng bộ nhớ cho các trường của cấu trúc User.
 * @details Hàm này giải phóng bộ nhớ đã cấp phát động cho các member của cấu trúc `User`.
 * @param   user: Con trỏ đến cấu trúc `User` cần giải phóng.
 **/
void free_user(User *user);


/**
 * @brief   Đọc dữ liệu từ file CSV và lưu thông tin người dùng vào Node.
 * @details Hàm này mở file CSV theo đường dẫn cung cấp, đọc từng dòng dữ liệu,
 *          phân tích và lưu vào cấu trúc `User`, sau đó lưu thông tin. Bộ nhớ
 *          cấp phát động sẽ được giải phóng ngay sau mỗi lần sử dụng.
 * @param   filename: Đường dẫn đến file CSV cần đọc.
 * @param   head: Con trỏ bậc 2 trỏ đến vị trí đầu danh sách liên kết.
 **/
void readCSV(const char *filename, Node **head);

/* ===================================================[ Guard End ]===================================================*/
#endif // FILE_HANDLE_H