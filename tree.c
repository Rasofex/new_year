#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>
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

// Функция, которая очищает экран терминала
void clear_screen()
{
    // Вызываем команду cls, которая очищает экран
    puts("\033[2J\033[H");
}

// Функция, которая проверяет, нажал ли пользователь какую-то клавишу
int key_pressed()
{
    // Определяем коды клавиш
    int key = 0x4B;  // K
    int key2 = 0x11; // Ctrl
    int key3 = 0x12; // Alt
    // Проверяем, нажаты ли все три клавиши
    if (GetAsyncKeyState(key) & 0x8000 && GetAsyncKeyState(key2) & 0x8000 && GetAsyncKeyState(key3) & 0x8000)
    {
        // Возвращаем 1, если да
        return 1;
    }
    else
    {
        // Возвращаем 0, если нет
        return 0;
    }
}

// Функция, которая печатает поздравление
void print_greeting()
{
    // Текст поздравления
    char *text = "\u2744 С Новым Годом \u2744";
    // Расстояние от края до текста
    int margin = ((TREE_WIDTH + 7) - strlen(text)) / 2;
    // Печатаем пустую строку
    printf("\n");
    // Печатаем текст с отступом
    printf("%*s%s\n", margin, SPACE, text);
    // Печатаем пустую строку
    printf("\n");
    // Печатаем команду для выхода
    printf("%*s%s\n", margin, SPACE, "Для выхода зажми Ctrl+Alt+K");
    printf("%*s%s\n", margin, SPACE, "Или нажми Ctrl+C");
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
    clear_screen();
    while (!key_pressed())
    {
        clear_screen();
        draw_tree();
        print_greeting();
        Sleep(1000);
    }
    exit(0);
}