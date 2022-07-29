#include <stdio.h>

enum elements
{
    FIRE = 1,
    WATER,
    WIND,
    EARTH,
    THUNDER,
    ICE,
    LIGHT,
    DARK
};

//在这里选择角色属性
//最大填写4个属性
int p1[4] = {FIRE, LIGHT, -1, -1};
int p2[4] = {ICE, FIRE, EARTH, -1};
int p3[4] = {-1, -1, -1, -1};
int *attackerList[] = {p1, p2, p3};
char names[3] = {'1', '2', '3'};

#define ec1 "FIRE"
#define ec2 "WATER"
#define ec3 "WIND"
#define ec4 "EARTH"
#define ec5 "THUNDER"
#define ec6 "ICE"
#define ec7 "LIGHT"
#define ec8 "DARK"

struct chins
{
    int attacker[3];
    int elementChin[3];
    int length;
};

void tochars(int, char **);
int eleEquals(int *, int *);
int appendChin(struct chins);
int sortChins();
void printChins();
void elementlink(const int, int *);
// void start(int *, int *, int *);
void badcal();
// int iteration(int, int *, int *, int *, int *, int, int);
// void calcuT(int *, int *);
// void calcuOb(int *, int *, int *);

int matchSum = 0;
struct chins clist[100];

int main()
{
    FILE *fp = fopen("config.txt", "r");
    if(fp){
        fscanf(fp, "%c %d %d %d %d\n", &names[0], &p1[0], &p1[1], &p1[2], &p1[3]);
        fscanf(fp, "%c %d %d %d %d\n", &names[1], &p2[0], &p2[1], &p2[2], &p2[3]);
        fscanf(fp, "%c %d %d %d %d\n", &names[2], &p3[0], &p3[1], &p3[2], &p2[3]);
    }else{
        fp = fopen("config.txt", "w");
        fprintf(fp,"%s","L 1 7 3 8\nT 6 1 4 -1\nM 7 2 5 -1\n\n// 编写规范\n// 每行一个角色，首字符写名字， 每个数字以空格分开\n// 示例\n// L 1 7 3 8\n// T 6 1 4 -1\n// M 1 2 5 -1\n// 属性对照表\n// 1 火 2 水 3 风 4 土\n// 5 雷 6 冰 7 光 8 暗\n// 名字对照表\n// 	莱克斯	L   		尼娅		N\n// 	虎 		T		梅勒芙 	M\n// 	齐格 	S	\n// 如果没有使用，请填写-1\n// 如果输入错误，可能会调用默认的配置，请务必注意\n");
        printf("no config file found. i have try create it, check it out and edit it. then run this application again!.\n");
    }
    fclose(fp);
    // printf("==========\n%c %c %c\n===========",names[0],names[1],names[2]);
    // dark 和 earth尽量不要出现在同一个人身上
    badcal(p1, p2, p3);
    return 0;
}

void tochars(int e, char **p)
{
    switch (e)
    {
    case FIRE:
        *p = ec1;
        break;
    case WATER:
        *p = ec2;
        break;
    case WIND:
        *p = ec3;
        break;
    case EARTH:
        *p = ec4;
        break;
    case THUNDER:
        *p = ec5;
        break;
    case ICE:
        *p = ec6;
        break;
    case LIGHT:
        *p = ec7;
        break;
    case DARK:
        *p = ec8;
        break;
    }
}
int eleEquals(int ele1[], int ele2[])
{
    for (int i = 0; i < 3; i++)
    {
        while (ele1[i] != ele2[i])
        {
            return 0;
        }
    }
    return 1;
}
// int cpyChin(struct chins t,struct chins o){

// }
// 添加连击
// 如果元素相同，则添加更短的 ======待实现
// 最后以sortChins排序
int appendChin(struct chins c)
{
    for (int i = 0; i < matchSum; i++)
    {
        if (eleEquals(c.elementChin, clist[i].elementChin))
        {
            // 如果更短就不会return 添加
            if (c.length >= clist[i].length)
            {
                // 元素重复 不添加
                return 0;
            }
        }
    }
    clist[matchSum] = c;
    matchSum++;
    return 1;
}
// 先用冒泡 以后优化
int sortChins()
{
    struct chins c;
    for (int i = 0; i < matchSum; i++)
    {
        c = clist[i];
        for (int j = i; j < matchSum; j++)
        {
            if (clist[i].length > clist[j].length)
            {
                c = clist[i];
                clist[i] = clist[j];
                clist[j] = c;
            }
        }
    }
    for (int i = 0; i < matchSum; i++)
    {
        c = clist[i];
        for (int j = i; j < matchSum; j++)
        {
            if (clist[i].length == clist[j].length)
            {
                if (clist[i].elementChin[2] > clist[j].elementChin[2])
                {
                    c = clist[i];
                    clist[i] = clist[j];
                    clist[j] = c;
                }
            }
        }
    }
    return 0;
}

void printChins()
{
    char *e1, *e2, *e3;
    for (int i = 0; i < matchSum; i++)
    {
        tochars(clist[i].elementChin[0], &e1);
        tochars(clist[i].elementChin[1], &e2);
        tochars(clist[i].elementChin[2], &e3);
        printf("%c:%-7s\t%c:%-7s\t%c:%-7s\tlen=%d \n", names[clist[i].attacker[0]], e1, names[clist[i].attacker[1]], e2, names[clist[i].attacker[2]], e3, clist[i].length);
    }
}

void elementlink(const int input, int *next)
{
    next[0] = input;
    next[6] = -1;
    switch (input)
    {
    case FIRE:
        next[1] = FIRE;
        next[2] = WATER;
        next[3] = FIRE;
        next[4] = LIGHT;
        next[5] = FIRE;
        next[6] = ICE;
        break;
    case WATER:
        next[1] = WATER;
        next[2] = EARTH;
        next[3] = WATER;
        next[4] = DARK;
        next[5] = WIND;
        break;
    case EARTH:
        next[1] = FIRE;
        next[2] = EARTH;
        next[3] = WIND;
        next[4] = EARTH;
        next[5] = THUNDER;
        break;
    case THUNDER:
        next[1] = FIRE;
        next[2] = THUNDER;
        next[3] = WIND;
        next[4] = ICE;
        next[5] = WATER;
        break;
    case WIND:
        next[1] = WIND;
        next[2] = ICE;
        next[3] = EARTH;
        next[4] = THUNDER;
        next[5] = ICE;
        break;
    case ICE:
        next[1] = ICE;
        next[2] = WATER;
        next[3] = EARTH;
        next[4] = DARK;
        next[5] = WIND;
        break;
    case LIGHT:
        next[1] = LIGHT;
        next[2] = THUNDER;
        next[3] = LIGHT;
        next[4] = WATER;
        next[5] = FIRE;
        break;
    case DARK:
        next[1] = DARK;
        next[2] = LIGHT;
        next[3] = DARK;
        next[4] = EARTH;
        next[5] = THUNDER;
        break;
    default:
        break;
    }
}
int next(int a)
{
    if (a > 3)
    {
        a -= 3;
    }
    return a;
}

void start(int *p1, int *p2, int *p3)
{
}
// 虽然不好看 但是好写性能好
void badcal()
{
    int attacker[3];
    int elementChin[3];
    int eletree[7];
    for (int ele = 1; ele <= 8; ele++)
    {
        elementlink(ele, eletree);
        for (int p = 0; p < 3; p++)
        {
            for (int pe = 0; pe < 4; pe++)
            {
                if (attackerList[p][pe] < 1 || attackerList[p][pe] > 8)
                    continue;
                if (attackerList[p][pe] == ele)
                {
                    for (int l = 1; l <= 2; l++)
                    {
                        for (int p2 = 0; p2 < 3; p2++)
                        {
                            for (int p2e = 0; p2e < 4; p2e++)
                            {
                                if (attackerList[p2][p2e] < 1 || attackerList[p2][p2e] > 8)
                                    continue;
                                if (attackerList[p2][p2e] == eletree[l])
                                {
                                    for (int n = 1; n <= 2; n++)
                                    {
                                        for (int p3 = 0; p3 < 3; p3++)
                                        {
                                            for (int p3e = 0; p3e < 4; p3e++)
                                            {
                                                if (attackerList[p3][p3e] < 1 || attackerList[p3][p3e] > 8)
                                                    continue;
                                                if (attackerList[p3][p3e] == eletree[l * 2 + n])
                                                {
                                                    int sum = 1;
                                                    if (p != p2)
                                                        sum += 1;
                                                    else
                                                        // 如果认为112=3就+1，如果认为112>3就+2
                                                        // sum += 1;
                                                        sum += 2;
                                                    if (p2 != p3)
                                                        sum += 1;
                                                    else
                                                        sum += 3;
                                                    if (sum < 6 && p == p3)
                                                        sum += 2;
                                                    struct chins c = {{p, p2, p3}, {eletree[0], eletree[l], eletree[l * 2 + n]}, sum};
                                                    appendChin(c);
                                                    // printf("at:%d %d %d el: %d %d %d len = %d\n", p, p2, p3, eletree[0], eletree[l], eletree[l * 2 + n], sum);
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    sortChins();
    printChins();
    printf("%d match available", matchSum);
}
