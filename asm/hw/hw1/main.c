#include <stdio.h>
#include <string.h>

void test5(char *format);
void testneg5(char *format);
void testneg4(char *format);
void test4(char *format);

// float __attribute__((__cdecl__))  arctan(float x, uint k);
//
// void append(char* output, char *str, int len, int &i) {
//     for(int j = 0; j < len; ++j) {
//         output[i++] = str[j];
//     }
// }
//
// void filling(char *output, char ch, int len, int &i) {
//     for(int j = 0; j < len; ++j) {
//         output[i++] = ch;
//     }
// }
//
// void put_sign_place(bool neg, bool p, bool s, char* output, int &i) {
//     if (neg) { // negative
//         output[i++] = '-';
//     } else {
//         if(p) {
//             output[i++] = '+';
//         } else if (s) {
//             output[i++] = ' ';
//         }
//     }
// }
//
//
// void pre_print(bool m, bool p, bool s, bool z, bool neg, int width, char* str, int len, char* output) {
//     int i = 0;
//     if (m) {
//         put_sign_place(neg, p, s, output, i);
//         append(output, str, len, i);
//         int fill = (width - i);
//         filling(output, ' ', fill, i);
//     } else {
//         if(z) {
//             put_sign_place(neg, p, s, output, i);
//             int fill = (width - i) - len;
//             filling(output, '0', fill, i);
//             append(output, str, len, i);
//         } else {
//             int fill = width - len;
//             if (neg || p || s) {
//                 --fill;
//             }
//             filling(output, ' ', fill, i);
//             put_sign_place(neg, p, s, output, i);
//             append(output, str, len, i);
//         }
//     }
//     output[i] = 0;
// }

int __cdecl print(char* out_buf, const char *format, const char* hex_number);

int main() {

    // //// 123456789
    // char hex_number[] = "75BCD15";
    //
    // char output[40];
    // for (int i = 0; i < 40; ++i) output[i] = 0;

    // char four[] = "4d2";

//     printf("%d\n", print(output, "--+07", "3039"));
//     print(output, "--+07", five);
//     printf("%s|\n", output);

    printf("# Testing format\n");
    test5("");
    // printf("%5d| 5d\n", 12345);
    test5("5");
    // printf("% 5d| _5d\n", -12345);
    testneg5(" 5");
    // printf("% 5d| _5d\n", 12345);
    test5(" 5");
    // printf("%6d| 6d\n", -12345);
    testneg5("6");
    // printf("%6d| 6d\n", 12345);
    test5("6");
    // printf("%06d| 06d\n", 12345);
    test5("06");
    // printf("% 6d| _6d\n", -12345);
    testneg5("06");
    // printf("% 6d| _6d\n", 12345);
    test5(" 6");
    testneg5(" 6");
    // printf("% 06d| _06d\n", 1234);
    test4(" 06");
    // printf("%- 06d| -_06d\n", 1234);
    test4("- 06");
    // printf("%- 06d| -_06d\n", -1234);
    testneg4("- 06");
    // printf("% 06d| _06d\n", -1234);
    testneg4(" 06");
    // printf("% +06d| _+06d\n", 1234);
    testneg4(" +06");
    // printf("% 0+6d| _+06d\n", -1234);
    test4(" +06");
    // printf("% +6d| _+6d\n", 1234);
    test4(" +6");
    // printf("%-07d|end\n\n\n", 12345);
    test5("-07");

    printf("# Big tests\n");
    // 1 = -0xFFF..
    {
        char hex_number1[34];
        hex_number1[0] = '-';
        for(int i = 0; i < 32; ++i) {
            hex_number1[i + 1] = 'F';
        }
        hex_number1[33] = 0;

        printf("test: %s = 1\n", hex_number1);
        char output1[45];
        print(output1, "", hex_number1);
        printf("your: %s\n", output1);
    }

    {
        // -1 = 0xFFFF...
        char hex_number2[34];
        for(int i = 0; i < 32; ++i) {
            hex_number2[i] = 'F';
        }
        hex_number2[32] = 0;

        printf("test: %s = -1\n", hex_number2);
        char output2[45];
        print(output2, "", hex_number2);
        printf("your: %s\n", output2);

        printf("test: 0 = 0\n");
        char output3[45];
        print(output3, "", "0");
        printf("your: %s\n", output3);
    }

   {
       // 0 = 0x00000..
       char hex_number4[34];
       for(int i = 0; i < 32; ++i) {
           hex_number4[i] = '0';
       }
       hex_number4[32] = 0;

       printf("test: %s = 0\n", hex_number4);
       char output4[45];
       print(output4, "", hex_number4);
       printf("your: %s\n", output4);
   }


     {
         // 0 = 0x00000..
         char hex_number[34];
         hex_number[0] = '-';
         for(int i = 0; i < 32; ++i) {
             hex_number[i+1] = '0';
         }
         hex_number[33] = 0;

         printf("test: %s = 0\n", hex_number);
         char output[45];
         print(output, "", hex_number);
         printf("your: %s\n", output);
     }

     printf("# Hard tests\n");
     {
          // 0 = 0x800...0 = -170141183460469231731687303715884105728
          char hex_number[34];
          hex_number[0] = '8';
          for(int i = 1; i < 32; ++i) {
              hex_number[i] = '0';
          }
          hex_number[32] = 0;

          printf("test: %s = -170141183460469231731687303715884105728\n", hex_number);
          char output[45];
          print(output, "", hex_number);
          printf("your: %s\n", output);
      }
      {
          // 0 = 0x800...0 = -170141183460469231731687303715884105727
          char hex_number[34];
          hex_number[0] = '8';
          for(int i = 1; i < 32; ++i) {
              hex_number[i] = '0';
          }
          hex_number[31] = '1';
          hex_number[32] = 0;

          printf("test: %s = -170141183460469231731687303715884105727\n", hex_number);
          char output[45];
          print(output, "", hex_number);
          printf("your: %s\n", output);
      }
     {
         // 0 = -0x800...0 = 170141183460469231731687303715884105727
         char hex_number[34];
         hex_number[0] = '-';
         hex_number[1] = '8';
         for(int i = 1; i < 32; ++i) {
             hex_number[i+1] = '0';
         }
         hex_number[33] = 0;

         printf("test: %s = -170141183460469231731687303715884105728\n", hex_number);
         char output[45];
         print(output, "", hex_number);
         printf("your: %s\n", output);
     }




    return 0;
}

void test5(char *format) {
    char five[] = "3039";
    char output[100], format_true[100];
    sprintf(format_true, "%%%sd", format);
    printf("test5: \"%s\"\n", format);
    printf("true: |"); printf(format_true, 12345); printf("|\n");
    // printf("result: %d\n", print(output, format, five));
    print(output, format, five);
    printf("your: |%s|\n", output);
}


void testneg5(char *format) {
    char five[] = "-3039";
    char output[100], format_true[100];
    sprintf(format_true, "%%%sd", format);
    printf("testneg5: \"%s\"\n", format);
    printf("true: |"); printf(format_true, -12345); printf("|\n");
    // printf("result: %d\n", print(output, format, five));
    print(output, format, five);
    printf("your: |%s|\n", output);
}


void testneg4(char *format) {
    char four[] = "-4d2";
    char output[100], format_true[100];
    sprintf(format_true, "%%%sd", format);
    printf("testneg4: \"%s\"\n", format);
    printf("true: |"); printf(format_true, -1234); printf("|\n");
    // printf("result: %d\n", print(output, format, four));
    print(output, format, four);
    printf("your: |%s|\n", output);
}



void test4(char *format) {
    char four[] = "4d2";
    char output[100], format_true[100];
    sprintf(format_true, "%%%sd", format);
    printf("test4: \"%s\"\n", format);
    printf("true: |"); printf(format_true, 1234); printf("|\n");
    // printf("result: %d\n", print(output, format, four));
    print(output, format, four);
    printf("your: |%s|\n", output);
}



// NOTE format "-5", not "%-5d"
// QUESTION Нужно ли парсить, что вне %_format_d, НЕТ
// QUESTION Нужно ли как-то обрабатывать ошибки, НЕТ
// TODO Написать ТЕСТЫ
    //TODO  проверить с помощью sprint на маленьких
    //TODO  проверить отриц. значения
    //TODO  проверить большие числа
