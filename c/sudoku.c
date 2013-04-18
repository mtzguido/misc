#include <stdio.h>
#include <stdlib.h>
#define CHK(p1,p2) if(p1!=p2 && S[p1]==S[p2] && S[p2]!=0) return 0;
#include <time.h>
//escupelachota
//kagasawa
//resuelvesudoku

void show(char* S)
{
    int i;
    for (i=0;i<81;++i)
    {

        printf("%i",S[i]);
        if (i%3==2 && i%9!=8) putchar('|');
        if (i%9==8) putchar('\n');
        if (i%27==26 && i!=80) printf("---+---+---\n");
    }
    putchar('\n');
    putchar('\n');

}

int checkPos(int i, char* Sudoku); //returns 1 iff position i is valid
int checkBoard(char* Sudoku); // returns 1 if all positions are valid

int main()
{
    char S[81];
    int i;
    char* MAP[81];
    int blanks=0;
    char c;
    time_t t1,t2;
    int x=0;

    i=0;
    while (i<81)
    {
        c=getchar();
        if (c>='0' && c<='9')
        {
            S[i++]=c-'0';
            if (c=='0')
            {
                MAP[blanks++] = &(S[i-1]);
            }
        }
    }

    t1=clock();
    if (checkBoard(S)==0) exit(98); // Si no es valido no laburemos al dope

    for (i=0;;++i)
    {
        x++;
        if (i<0)
        {
            break;
        }

        if (*MAP[i]<9)
            (*MAP[i])++; //aumenta el valor
        else
        {
            *(MAP[i])=0;
            i=i-2;
            continue;
        }

        if (checkPos(MAP[i]-S,S)==0)
        {
            i--;
            continue;
        }

        if (i==blanks-1)
        {
            show(S);//ahi esta el que la chupa
            i--;
        }
    }

    t2=clock();

    printf("Resuelto en %.2f segundos (%i iteraciones)\n",(t2-t1)*0.001,x);
    fflush(stdin);
    getchar();
    getchar();
    return 0;
}

int checkBoard(char* S)
{
    int i;
    for (i=0;i<81;++i)
    {
        if (checkPos(i,S)==0)
        {
            printf("%i",i);
            return 0;
        }
    }
    return 1;
}

int checkPos(int i, char* S)
{
    int a;

    if (S[i]==0) return 1;
    //if (S[i]>9) return 0; // manera de arreglar que ponga '10'
                          // EDIT: ahora cambie todo porque soy
                          // re loco y ya no hace falta
    CHK(i,i%9)
    CHK(i,i%9+9)
    CHK(i,i%9+18)
    CHK(i,i%9+27)
    CHK(i,i%9+36)
    CHK(i,i%9+45)
    CHK(i,i%9+54)
    CHK(i,i%9+63)
    CHK(i,i%9+72)

    CHK(i,i-i%9)
    CHK(i,i-i%9+1)
    CHK(i,i-i%9+2)
    CHK(i,i-i%9+3)
    CHK(i,i-i%9+4)
    CHK(i,i-i%9+5)
    CHK(i,i-i%9+6)
    CHK(i,i-i%9+7)
    CHK(i,i-i%9+8)

    a=i-i%3;
    if (a%27>=9) a-=9;
    if (a%27>=9) a-=9;

    CHK(i,a)
    CHK(i,a+1)
    CHK(i,a+2)
    CHK(i,a+9)
    CHK(i,a+10)
    CHK(i,a+11)
    CHK(i,a+18)
    CHK(i,a+19)
    CHK(i,a+20)

    return 1;
}
