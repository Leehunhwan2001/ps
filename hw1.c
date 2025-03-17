#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int findRoom(int persons[5]); 
void printReport(char mn[10][20], int mr[10], int mc, char wn[10][20], int wr[10], int wc);

int main(){
    char mnames[10][20]; 
    int mroom[10]; 
    char wnames[10][20]; 
    int wroom[10]; 
    int person[2][5] = {0}; 
    int mcount = 0, wcount = 0; 
    int menu;

    srand(time(0));
    printf("===========================================\n");
    printf("생활관 호실 배정 프로그램\n");
    printf("===========================================\n");

    while(1){
        printf("메뉴 : 1.남학생 등록 2.여학생 등록 0.종료 > ");
        scanf("%d", &menu);
        if(menu == 0) break;

        if(menu == 1) { 
            if(mcount >= 10) {
                printf("정원 초과입니다. 등록불가!\n");
                continue;
            }
            printf("학생 이름은? > ");
            scanf("%s", mnames[mcount]);
            int roomno = findRoom(person[0]);
            if(roomno == -1) {
                printf("배정 가능한 방이 없습니다!\n");
                continue;
            }
            mroom[mcount] = 100 + roomno;
            person[0][roomno - 1]++; 
            printf("%s 학생 %d호실 배정되었습니다.\n", mnames[mcount], mroom[mcount]);
            mcount++;
        }
        else if(menu == 2) { 
            if(wcount >= 10) {
                printf("정원 초과입니다. 등록불가!\n");
                continue;
            }
            printf("학생 이름은? > ");
            scanf("%s", wnames[wcount]);
            int roomno = findRoom(person[1]);
            if(roomno == -1) {
                printf("배정 가능한 방이 없습니다!\n");
                continue;
            }
            wroom[wcount] = 200 + roomno;
            person[1][roomno - 1]++; 
            printf("%s 학생 %d호실 배정되었습니다.\n", wnames[wcount], wroom[wcount]);
            wcount++;
        }
    }

    printf("===========================================\n");
    printf("생활관 호실 배정 결과는 다음과 같습니다.\n");
    printf("===========================================\n");
    printReport(mnames, mroom, mcount, wnames, wroom, wcount);

    return 0;
}

int findRoom(int persons[5]) {
    int available[5];
    int count = 0;

    
    for (int i = 0; i < 5; i++) {
        if (persons[i] < 2) {
            available[count++] = i + 1; 
        }
    }

    if (count == 0) return -1; 

    return available[rand() % count]; 
}

void printReport(char mn[10][20], int mr[10], int mc, char wn[10][20], int wr[10], int wc) {
    printf("남학생 명단 (총 %d명)\n", mc);
    for (int i = 0; i < mc; i++) {
        printf("%d. %s (%d호실)\n", i + 1, mn[i], mr[i]);
    }

    printf("\n여학생 명단 (총 %d명)\n", wc);
    for (int i = 0; i < wc; i++) {
        printf("%d. %s (%d호실)\n", i + 1, wn[i], wr[i]);
    }

    printf("\n호실별 배정 명단\n");
    int roomAssignments[2][5][2] = {0}; 

    for (int i = 0; i < mc; i++) {
        int roomIndex = (mr[i] % 100) - 1;
        if (roomAssignments[0][roomIndex][0] == 0)
            roomAssignments[0][roomIndex][0] = i + 1; 
        else
            roomAssignments[0][roomIndex][1] = i + 1; 
    }

    for (int i = 0; i < wc; i++) {
        int roomIndex = (wr[i] % 100) - 1;
        if (roomAssignments[1][roomIndex][0] == 0)
            roomAssignments[1][roomIndex][0] = i + 1;
        else
            roomAssignments[1][roomIndex][1] = i + 1;
    }

    for (int i = 0; i < 5; i++) {
        printf("%d호실 : ", 101 + i);
        if (roomAssignments[0][i][0]) printf("%s ", mn[roomAssignments[0][i][0] - 1]);
        if (roomAssignments[0][i][1]) printf("%s", mn[roomAssignments[0][i][1] - 1]);
        printf("\n");
    }

    for (int i = 0; i < 5; i++) {
        printf("%d호실 : ", 201 + i);
        if (roomAssignments[1][i][0]) printf("%s ", wn[roomAssignments[1][i][0] - 1]);
        if (roomAssignments[1][i][1]) printf("%s", wn[roomAssignments[1][i][1] - 1]);
        printf("\n");
    }
}
