#include <ncurses.h>
#include <stdio.h>

#define WIDTH 80
#define HEIGHT 26

// проверка на то, что ракетка не выходит за поле
int rocket_check_border(int rocket) {
    if (rocket <= 1) {
        rocket += 1;
    } else if (rocket >= 25) {
        rocket -= 1;
    }
    return rocket;
}

// проверка на то, то мяч не сольется с ракеткой 1
int check_ball_on_rocket_1(int ball_x, int ball_y, int rocket) {
    if (ball_x == 0 && (ball_y >= rocket - 1 && ball_y <= rocket + 1)) {
        return 1;
    }
    return 0;
}

// проверка на то, то мяч не сольется с ракеткой 2
int check_ball_on_rocket_2(int ball_x, int ball_y, int rocket) {
    if (ball_x == WIDTH - 1 && (ball_y >= rocket - 1 && ball_y <= rocket + 1)) {
        return 1;
    }
    return 0;
}

void print_counter(int count_1p, int count_2p) {
    for (int i = 0; i < WIDTH / 2 - 3; i++) {
        printw(" ");
    }
    printw("%2d     %2d", count_1p, count_2p);
    for (int i = 0; i < WIDTH / 2 - 2; i++) {
        printw(" ");
    }
    printw("\n");
}
// отрисовка карты, мяча и ракеток
void create_map(int player1_place, int player2_place, int ball_x, int ball_y, int count_1p, int count_2p) {
    clear();

    print_counter(count_1p, count_2p);

    for (int i = 0; i <= HEIGHT; i++) {
        if (i != 0 && i != HEIGHT) {
            printw("|");
        }
        for (int j = 0; j < WIDTH; j++) {
            if ((j == 0 && i == 0) || (j == 0 && i == HEIGHT)) {  // отрисовка пустоты на краях
                printw(" ");
            } else if (i == 0) {  // отрисовка верхней границы поля
                printw("_");
            } else if (i == HEIGHT && j != 0) {  // отрисовка нижней границы поля
                printw("¯");
            } else if ((i == player1_place || i == player1_place - 1 || i == player1_place + 1) && j == 0) {
                printw("|");
            } else if ((i == player2_place || i == player2_place - 1 || i == player2_place + 1) &&
                       j == WIDTH - 1) {
                printw("|");
            } else if (j == ball_x && i == ball_y) {
                printw("O");
            } else {  // отрисовка пустоты
                printw(" ");
            }
        }
        if (i == 0) {
            printw("_\n");
            continue;
        } else if (i == HEIGHT) {
            printw("¯\n");
            continue;
        }
        printw("|\n");
    }

    refresh();
}

// считывание движения ракеток
void player_move() {
    int player1_place = HEIGHT / 2;
    int player2_place = HEIGHT / 2;

    int ball_x = WIDTH / 2;
    int ball_y = HEIGHT / 2;
    int speed_x = 1;
    int speed_y = 1;
    int count_1p = 0;
    int count_2p = 0;
    int flag = 0;  // для обработки прилипания мяча к ребру ракетки

    // старт режима ncurses
    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);

    create_map(player1_place, player2_place, ball_x, ball_y, count_1p, count_2p);

    while (1) {  // запуск игры
        int start = getch();
        if (start != EOF) {
            break;
        }
    }

    while (1) {
        // ввод символа
        int input = getch();

        // счётчик
        if (ball_x == WIDTH) {
            ball_x = WIDTH / 2;
            ball_y = HEIGHT / 2;
            ++count_1p;
            if (count_1p == 21) {
                create_map(player1_place, player2_place, ball_x, ball_y, count_1p, count_2p);
                printw("1 PLAYER WON\n");
                refresh();
                nodelay(stdscr, FALSE);
                getch();
                break;
            }
        } else if (ball_x == -1) {
            ball_x = WIDTH / 2;
            ball_y = HEIGHT / 2;
            ++count_2p;
            if (count_2p == 21) {
                create_map(player1_place, player2_place, ball_x, ball_y, count_1p, count_2p);
                printw("2 PLAYER WON\n");
                refresh();
                nodelay(stdscr, FALSE);
                getch();
                break;
            }
        }

        // отскок по Y
        if (ball_y == HEIGHT - 1 || ball_y == 1) {
            speed_y *= -1;
        }
        // отскок по X
        if ((ball_x == 1) && (ball_y >= player1_place - 1 && ball_y <= player1_place + 1) && (flag == 0)) {
            speed_x *= -1;
        } else if ((ball_x == WIDTH - 2) && (ball_y >= player2_place - 1 && ball_y <= player2_place + 1) &&
                   (flag == 0)) {
            speed_x *= -1;
        }

        flag = 0;

        ball_x += speed_x;
        ball_y += speed_y;

        if (check_ball_on_rocket_1(ball_x, ball_y, player1_place) == 1) {
            ball_x++;
            speed_x *= -1;
            flag = 1;
        }
        if (check_ball_on_rocket_2(ball_x, ball_y, player2_place) == 1) {
            ball_x--;
            speed_x *= -1;
            flag = 1;
        }

        if (input == 'k') {
            player2_place--;
            player2_place = rocket_check_border(player2_place);
        } else if (input == 'm') {
            player2_place++;
            player2_place = rocket_check_border(player2_place);
        } else if (input == 'a') {
            player1_place--;
            player1_place = rocket_check_border(player1_place);
        } else if (input == 'z') {
            player1_place++;
            player1_place = rocket_check_border(player1_place);
        }
        create_map(player1_place, player2_place, ball_x, ball_y, count_1p, count_2p);

        napms(100);  // delay
    }
    endwin();
}

int main() {
    player_move();
    return 0;
}
