#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 255

int valuesBox[MAX] = {0};
int current_box_position = 0;

void inputTaker(int pos)
{
    char temp;
    scanf(" %c", &temp);
    valuesBox[pos] = (int)temp;
}

void decoder(char *p)
{
    int loopStartPositions[1000];
    int loopTop = -1;

    for (int i = 0; p[i] != '\0'; i++)
    {
        switch (p[i])
        {
        case '+':
            valuesBox[current_box_position] += 1;
            break;
        case '-':
            valuesBox[current_box_position] -= 1;
            break;
        case '>':
            current_box_position += 1;
            if (current_box_position >= MAX)
            {
                printf("Error: Data pointer out of bounds (too far right)\n");
                return;
            }
            break;
        case '<':
            current_box_position -= 1;
            if (current_box_position < 0)
            {
                printf("Error: Data pointer out of bounds (too far left)\n");
                return;
            }
            break;
        case '.':
            printf("%c", valuesBox[current_box_position]);
            break;
        case ',':
            inputTaker(current_box_position);
            break;
        case '[':
            if (valuesBox[current_box_position] == 0)
            {
                int bracket_flag = 1;
                while (bracket_flag > 0)
                {
                    i++;
                    if (p[i] == '[')
                        bracket_flag++;
                    else if (p[i] == ']')
                        bracket_flag--;
                    if (p[i] == '\0')
                    {
                        printf("Error: Mismatched '['\n");
                        return;
                    }
                }
            }
            else
            {
                loopTop++;
                loopStartPositions[loopTop] = i;
            }
            break;
        case ']':
            if (loopTop < 0)
            {
                printf("Error: Mismatched ']'\n");
                return;
            }
            if (valuesBox[current_box_position] != 0)
                i = loopStartPositions[loopTop];
            else
                loopTop--;
            break;
        default:
            break;
        }
    }
    printf("\n");
}

void main()
{
    char input[30000];
    scanf("%[^\n]s", input);
    decoder(input);
}
