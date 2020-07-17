//
// Created by chugang on 2020/5/27.
//
#include "password.h"

// 生成数据指纹
// 不会写
char *generate_fingerprint(char *file) {

}

// 存储密码
void save_password(char *fingerprint, char *password) {
    int fingerprint_length = strlen(fingerprint);
    int password_length = strlen(password);

    char head[4];
    head[0]=fingerprint_length;
    head[1]=password_length;
    head[2]=0;
    head[3]=0;
}

// 读取密码
char *read_password(char *file) {

}

// 获取char
char *get_char(char *str){
    char *chars;
    for(int i=0;i<strlen(str);i++){
        chars[i]=str[i];
    }
    return chars;
}
