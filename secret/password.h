//
// Created by chugang on 2020/5/27.
//

#ifndef NOTEPAD_PASSWORD_H
#define NOTEPAD_PASSWORD_H

#include <string.h>

// 生成数据指纹
char *generate_fingerprint(char *file);
// 存储密码
void save_password(char *fingerprint, char *password);
// 读取密码
char *read_password(char *file);
// 获取char
char *get_char(char *str);

#endif //NOTEPAD_PASSWORD_H
