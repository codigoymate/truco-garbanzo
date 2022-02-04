#include <ncurses.h>

void draw(WINDOW *wnd);

int main(void) {
	int bg, fg, p = 1;

    initscr();
    start_color();

    /* Init color pairs */
    for (bg = 0; bg < 8; bg ++) {
        for (fg = 0; fg < 8; fg ++) {
            init_pair(p, fg, bg); p ++;
        }
    }

    draw(stdscr);
    refresh();
    getch();
    endwin();

    return 0;
}

void draw(WINDOW *wnd) {
	int w = 10, h = 6, x, y, i = 0;
	chtype m[] = {
5257580, 5257585, 5257585, 5257585, 5257585, 5257585, 5257585, 5257585, 5257585, 5257579, 5257592, 1063200, 1063200, 1055008, 4201080, 4201080, 
1055008, 1063200, 1063200, 5257592, 5257592, 1063200, 4201073, 6688, 4201056, 4201056, 6688, 4201073, 1063200, 5257592, 5257592, 1063200, 
4201073, 6688, 4201056, 4201056, 6688, 4201073, 1063200, 5257592, 5257592, 1063200, 1063200, 1055008, 4201080, 4201080, 1055008, 1063200, 
1063200, 5257592, 5257581, 5257585, 5257585, 5257585, 5257585, 5257585, 5257585, 5257585, 5257585, 5257578	};

	for (y = 0; y < h; y ++)
		for (x = 0; x < w; x ++) {
			if (m[i]) mvwaddch(wnd, y, x, m[i]);
			i ++;
		}
}
