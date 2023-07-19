#include <stdio.h>
#include <stdint.h>
#include <netinet/in.h>  // ntohl 함수를 사용하기 위해 추가

uint32_t read_uint32(FILE* file) {
    uint32_t num = 0;
    fread(&num, sizeof(uint32_t), 1, file);
    return ntohl(num);  // network byte order에서 host byte order로 변환
}

void print_hex_and_decimal(uint32_t num) {
    printf("%u(0x%08x)", num, num);  // 숫자를 8자리로 출력하기 위해 수정
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("syntax: add-nbo <file1> <file2>\n");
        printf("sample: add-nbo a.bin b.bin\n");
        return 1;
    }

    FILE* file1 = fopen(argv[1], "rb");
    FILE* file2 = fopen(argv[2], "rb");

    if (file1 == NULL || file2 == NULL) {
        printf("파일을 열 수 없습니다.\n");
        return 1;
    }

    uint32_t num1 = read_uint32(file1);
    uint32_t num2 = read_uint32(file2);

    fclose(file1);
    fclose(file2);

    uint32_t sum = num1 + num2;

    print_hex_and_decimal(num1);
    printf(" + ");
    print_hex_and_decimal(num2);
    printf(" = ");
    print_hex_and_decimal(sum);
    printf("\n");

    return 0;
}

