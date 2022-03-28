//
// Created by dingjing on 3/28/22.
//
#include <stdio.h>
#include <stdint.h>

int main (int argc, char* argv[])
{
    /**
     * https://uic.io/en/charset/show_raw/gb2312
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
     */
    const uint16_t* arr[] = {"残", "怖", "惭",
                             "啊", "齄",
                             " ", "/",
                             "0", "9",
                             ":", "@",
                             "A", "Z",
                             "[", "`",
                             "a", "z",
                             "{", "~"};

    printf ("array: %d/%d\n\n", sizeof arr[0], sizeof arr);

    int len = sizeof arr / sizeof arr[0];
    for (int i = 0; i < len; ++i) {
        uint16_t code = *(arr[i]);

        // 小端，所以...
        uint8_t bL = code >> 8;
        uint8_t bH = code & 0XFF;

        printf ("index: %-2d ---> gb2312 hex code: 0X%-08X "
                "== code: %-6u "
                "== area: 0X%-08X -- pos: 0X%-08X "
                "==> character: %-6s\n",
                i, code, code, bH - 0xA0, bL - 0xA0, arr[i]);
    }

    return 0;
}