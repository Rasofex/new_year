#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <locale.h>

#define TREE_HEIGHT 10 // Высота елки
#define TREE_WIDTH 21  // Ширина елки
#define STAR "\u2605"  // Звезда
#define LEAF "\u2588"  // Листва
#define TRUNK "\u2593" // Ствол
#define LIGHT "\u25CF" // Гирлянда
#define SPACE " "      // Пробел

// Функция, которая генерирует случайное число от min до max
int random(int min, int max)
{
    return rand() % (max - min + 1) + min;
}

// Функция, которая возвращает символ гирлянды разного цвета
char *random_light()
{
    // Массив цветов
    char *colors[] = {"\033[0;31m", "\033[0;32m", "\033[0;33m", "\033[0;34m", "\033[0;35m", "\033[0;36m"};
    // Количество цветов
    int n = sizeof(colors) / sizeof(colors[0]);
    // Выбираем случайный цвет
    int i = random(0, n - 1);
    // Возвращаем символ гирлянды с цветом
    return colors[i];
}

// Функция, которая рисует елку
void draw_tree()
{
    // Инициализируем генератор случайных чисел
    srand(time(NULL));
    // Рисуем звезду
    printf("%*s%s\n", TREE_WIDTH / 2, SPACE, STAR);
    // Рисуем листву
    for (int i = 0; i < TREE_HEIGHT; i++)
    {
        // Вычисляем количество пробелов и символов листвы на каждом уровне
        int spaces = (TREE_WIDTH - 1 - 2 * i) / 2;
        int leaves = TREE_WIDTH - 2 * spaces;
        // Рисуем пробелы
        printf("%*s", spaces, SPACE);
        // Рисуем листву
        for (int j = 0; j < leaves; j++)
        {
            // С вероятностью 20% рисуем гирлянду
            if (random(1, 100) <= 20)
            {
                printf("%s%s\033[0m", random_light(), LIGHT);
            }
            else
            {
                // Иначе рисуем обычную листву
                printf("%s", LEAF);
            }
        }
        // Переходим на новую строку
        printf("\n");
    }
    // Рисуем ствол
    for (int i = 0; i < TREE_HEIGHT / 5; i++)
    {
        printf("%*s", (TREE_WIDTH - 3) / 2, SPACE);
        printf("%s%s%s\n", TRUNK, TRUNK, TRUNK);
    }
}

// Функция, которая печатает поздравление
void print_greeting()
{
    // Текст поздравления
    char *text = "С Новым Годом \u2744";
    // Расстояние от края до текста
    int margin = (TREE_WIDTH - strlen(text)) / 2;
    // Печатаем пустую строку
    printf("\n");
    // Печатаем текст с отступом
    printf("%*s%s\n", margin, SPACE, text);
}

// Функция, которая очищает консоль
void clear()
{
    printf("\033[2J\033[H");
}

// Главная функция
int main()
{
    setlocale(LC_ALL, "ru_RU.UTF-8");
    clear();
    draw_tree();
    print_greeting();
    getch();
    exit(0);
}