#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int day_index;
    char firm[20];
    float value_start;
    float value_end;
    float value_difference;
    int trades;
} Stock_record;

int find(char *target, int n, Stock_record stocs[]) {
    int max_index = -1;
    int max = 0;
    for (int i = 0; i < n; i++) {
        if (strcmp(target, stocs[i].firm) == 0) {
            if (stocs[i].trades > max) {
                max = stocs[i].trades;
                max_index = i;
            }
        }
    }
    return max_index;
}

void volumeToStr(int volume, char *dst) {
    char buff[100];
    sprintf(buff, "%d", volume);
    int len = (int)strlen(buff);
    int count = 0;
    for (int i = 0; i < len; i++) {
        dst[count++] = buff[i];
        int digits_left = len - i - 1;
        if (digits_left > 0 && digits_left % 3 == 0)
            dst[count++] = '_';
    }
    dst[count] = '\0';
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Wrong parameters\n");
        return 1;
    }

    char *target = argv[1];
    int n = atoi(argv[2]);
    Stock_record *stocs = malloc((size_t)((int)sizeof(Stock_record) * n));
    char buff[100];

    for (int i = 0; i < n; i++) {
        fgets(buff, 100, stdin);
        stocs[i].day_index = atoi(strtok(buff, ","));
        strcpy(stocs[i].firm, strtok(NULL, ","));
        stocs[i].value_start = (float)atof(strtok(NULL, ","));
        stocs[i].value_end = (float)atof(strtok(NULL, ","));
        stocs[i].value_difference = stocs[i].value_end - stocs[i].value_start;
        stocs[i].trades = atoi(strtok(NULL, "\n"));
    }

    printf("<html>\n<body>\n<div>\n");
    int target_index = find(target, n, stocs);
    char tmp[20];
    if (target_index < 0)
        printf("Ticker %s was not found\n", target);
    else {
        volumeToStr(stocs[target_index].trades, tmp);
        printf("<h1>%s: highest volume</h1>\n", target);
        printf("<div>Day: %d</div>\n<div>Start price: %.2f</div>\n<div>End price: %.2f</div>\n",
               stocs[target_index].day_index, stocs[target_index].value_start, stocs[target_index].value_end);
        printf("<div>Volume: %s</div>\n", tmp);
    }

    printf("</div>\n<table>\n<thead>\n<tr><th>Day</th><th>Ticker</th><th>Start</th><th>End</th><th>Diff</th><th>Volume</th></tr>\n</thead>\n<tbody>\n");

    for (int i = n-1; i >=0; i--) {
        //vypis s kontrolou pro vypis <b>
        char tmp1[10], tmp2[10], vol[20];
        volumeToStr(stocs[i].trades, vol);
        if (strcmp(stocs[i].firm, target) == 0) {
            strcpy(tmp1, "<b>");
            strcpy(tmp2, "</b>");
        } else {
            strcpy(tmp1, "");
            strcpy(tmp2, "");
        }

        printf("<tr>\n");
        printf("	<td>%s%d%s</td>\n", tmp1, stocs[i].day_index, tmp2);
        printf("	<td>%s%s%s</td>\n", tmp1, stocs[i].firm, tmp2);
        printf("	<td>%s%.2f%s</td>\n", tmp1, stocs[i].value_start, tmp2);
        printf("	<td>%s%.2f%s</td>\n", tmp1, stocs[i].value_end, tmp2);
        printf("	<td>%s%.2f%s</td>\n", tmp1, stocs[i].value_difference, tmp2);
        printf("	<td>%s%s%s</td>\n", tmp1, vol, tmp2);
        printf("</tr>\n");
    }

    printf("</tbody>\n</table>\n</body>\n</html>\n");
    free(stocs);
    return 0;
}
