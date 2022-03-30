//
// Created by dingjing on 3/28/22.
//
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

/**
 * 总共 94 个区 94 个位
 */
bool is_gb2312 (const char* code)
{
    unsigned long len = strlen (code);
    if (len != 2 && len != 1) {
        return false;
    }

    uint8_t codeH = code[0];
    uint8_t codeL = code[1];

    uint8_t area = codeH - 0xA0;
    uint8_t pos  = codeL - 0xA0;

    if ((len == 1) && (0 == (codeL & 0x80))) {
        printf ("ascii code: '%-3c' hex code: 0x%-2X\n", *code, *code);
        return true;
    }

    if (area >= 1 && area <= 94 && pos >= 1 && pos <= 94) {
        printf ("gb2312 code: '%-3s' -- area: %-2u, pos: %-2u hex code: 0x%-2X 0x%-2X\n", code, area, pos, codeH, codeL);
        return true;
    }
}


int main (int argc, char* argv[])
{
    /**
     * https://uic.io/en/charset/show_raw/gb2312
     * http://tools.jb51.net/table/gb2312
     * 1. '残'   十六进制: B2D0
     * 2. '怖'   十六进制: B2C0
     * 3. '惭'   十六进制: B2D1
     *
     * 4. ascii 里显示的特殊符号 32(space) - 47(/)
     * 5. ascii 里数字 30(0) - 39(9)
     * 6. ascii 里显示的特殊符号 58(:) - 64(@)
     * 7. ascii 里显示的大写字母 65(A) - 90(Z)
     * 8. ascii 里显示的标号字符 91([) - 96(`)
     * 9. ascii 里显示的大写字母 97(a) - 122(z)
     * 10. ascii 其它可显示字符 123({) - 126(~)
     *
     * uint16_t 就足够了
     */
    const char* arr[] = {
            "、", "∩", "〓",                              /* 第一区 */
            "残", "怖", "惭", "庄", "丽", "君", "齄",
            " ", "/",
            "0", "9",
            ":", "@",
            "A", "Z",
            "[", "`",
            "a", "z",
            "{", "~"
    };

    printf ("array: %lu/%lu\n\n", sizeof arr[0], sizeof arr);

    int len = sizeof arr / sizeof arr[0];
    for (int i = 0; i < len; ++i) {
        const char* code = arr[i];

        if (!is_gb2312 (code)) {
            printf ("index: %d -- code '%-3s' is not gb2312\n", i, code);
        }
    }

    return 0;
}