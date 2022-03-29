//
// Created by dingjing on 3/28/22.
//

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

bool is_utf8_1 (const char* code)
{
    int len = strlen(code);
    if (len < 1) {
        return false;
    }
    const uint8_t code1 = code[0];

    if (!(0x80 & code1)) {
        return true;
    }

    return false;
}

bool is_utf8_2 (const char* code)
{
    int len = strlen(code);
    if (len < 2) {
        return false;
    }
    const uint8_t code1 = code[0];
    const uint8_t code2 = code[1];

//    printf ("debug2: 0x%-4X\n", code);

    if (!is_utf8_1 (code) && (0xC0 == (0xE0 & code1)) && (0x80 == (0xE0 & code2))) {
//        printf ("debug: is utf8-2\n");
        if (code1 >= 0xC0 && code1 <= 0xDF && code2 >= 0x80 && code2 <= 0xBF) {
            return true;
        }
    }

    return false;
}

bool is_utf8_3 (const char* code)
{
    /**
     * 0xE0        0xA0-0XBF   0x80-0xBF
     * 0xE1-0XEC   0x80-0XBF   0x80-0xBF
     * 0xED        0x80-0x9F   0x80-0xBF
     * 0xEE-0xEF   0x80-0xBF   0x80-0xBF
     */
    int len = strlen(code);
    if (len < 3) {
        return false;
    }

    const uint8_t code1 = code[0];
    const uint8_t code2 = code[1];
    const uint8_t code3 = code[2];

    if ((0xE0 == code1) && ((code2 >= 0xA0) && (code2 <= 0XBF)) && ((code3 >= 0x80) && (code3 <= 0xBF))) {
        return true;
    } else if (((code1 >= 0xE1) && (code1 <= 0xEC)) && ((code2 >= 0x80) && (code2 <= 0xBF)) && ((code3 >= 0x80) && (code3 <= 0xBF))) {
        return true;
    } else if ((0xED == code1) && ((code2 >= 0x80) && (code2 <= 0x9F)) && ((code3 >= 0x80) && (code3 <= 0xBF))) {
        return true;
    } else if (((code1 >= 0xEE) && (code1 <= 0xEF)) && ((code2 >= 0x80) && (code2 <= 0xBF)) && ((code3 >= 0x80) && (code3 <= 0xBF))) {
        return true;
    }

    return false;
}

bool is_utf8_4 (const char* code)
{
    /**
     * 0xF0        0x90-0xBF   0x80-0xBF   0x80-0xBF
     * 0xF1-0xF3   0x80-0xBF   0x80-0xBF   0x80-0xBF
     * 0xF4        0x80-0x8F   0x80-0xBF   0x80-0xBF
     */
    int len = strlen(code);
    if (len < 4) {
        return false;
    }

    const uint8_t code1 = code[0];
    const uint8_t code2 = code[1];
    const uint8_t code3 = code[2];
    const uint8_t code4 = code[3];

//    printf ("debug4: 0x%-4X %-4X\n", code1H, code1L);

    if (!is_utf8_1 (code) && !is_utf8_2 (code) && !is_utf8_3 (code)) {
        if ((0xF0 == code1)
            && ((code2 >= 0x90) && (code2 <= 0xBF))
            && ((code3 >= 0x80) && (code3 <= 0xBF))
            && ((code4 >= 0x80) && (code4 <= 0xBF))) {
            return true;
        } else if (((code1 >= 0xF1) && (code1 <= 0xF3))
                   && ((code2 >= 0x80) && (code2 <= 0xBF))
                   && ((code3 >= 0x80) && (code3 <= 0xBF))
                   && ((code4 >= 0x80) && (code4 <= 0xBF))) {
            return true;
        } else if ((0xF4 == code1)
                   && ((code2 >= 0x80) && (code2 <= 0x8F))
                   && ((code3 >= 0x80) && (code3 <= 0xBF))
                   && ((code4 >= 0x80) && (code4 <= 0xBF))) {
            return true;
        }
    }

    return false;
}

int main (int argc, char* argv[])
{
    // utf-8 1 - 4 字节
    const char* arr[] = {
            " ", "/", "0", "9", ":", "@", "A", "Z", "[", "`", "a", "z", "{", "~",       /* 以下都是 ASCII */
            "§", "©", "®", "Ą", "Ď", "Đ", "Ő",                                          /* 2 字节 utf8 编码 */
            "ᥕ", "一", "龥", "庄", "丽", "君",                                            /* 3 字节 */
            "契", "い", "龜"
    };

    printf ("array: %lu/%lu\n\n", sizeof arr[0], sizeof arr);

    char buf[128] = {0};
    int len = sizeof arr / sizeof arr[0];
    for (int i = 0; i < len; ++i) {
        const char* code = arr[i];

        if (is_utf8_1 (code)) {
            printf ("index: %-2d --> utf8-1 code: '%c'  --  hex code: 0x%-02X <==> dec: %d\n", i, code[0], code[0] & 0xFF, code[0] & 0xFF);
            continue;
        } else if (is_utf8_2 (code)) {
            printf ("index: %-2d --> utf8-2 code: '%s'  --  hex code: 0x%-02X 0x%-02X\n", i, code, code[0] & 0xFF, code[1] & 0xFF);
            continue;
        } else if (is_utf8_3 (code)) {
            printf ("index: %-2d --> utf8-3 code: '%s'  --  hex code: 0x%-02X 0x%-02X 0x%-02X\n", i, code, code[0] & 0xFF, code[1] & 0xFF, code[2] & 0xFF);
        } else if (is_utf8_4 (code)) {
            printf ("index: %-2d --> utf8-4 code: '%s'  --  hex code: 0x%-02X 0x%-02X 0x%-02X 0x%-02X\n", i, code, code[0] & 0xFF, code[1] & 0xFF, code[2] & 0xFF, code[3] & 0xFF);
        }
    }

    return 0;
}