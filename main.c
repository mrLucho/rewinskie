#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include "rewinskie.h"
#define pi 3.1415
typedef FILE* plik;



float** Gen_sin(int, float, float, float);  //prototyp(N, tp, amplituda, okres)
void RysujWykres(float**, int, char*); //prototyp
float ** wczytaj_z_pliku(plik file,int N);

int main(void){
    int i = 400;
    int N = 400;
//    N to dlugosc wykresu na osi X
    float** tab = NULL;
    float tp = 0.01;

    printf("\t\tMENU\n\n");
    printf("1. Generuj sygnal\n");
    printf("2. Rysuj wykres\n");
    printf("3. Zapisz sygnal do pliku txt\n");
    printf("4. Wczytaj sygnal z pliku\n");
    printf("5. Odszumiaj\n");
    printf("6. Zakoncz\n");

    int wybor;
    printf("Twoj wybor: ");
    scanf("%d", &wybor);

    switch (wybor)
    {
        case 1:
        {
            system("cls");
            printf("Podaj parametry sygnalu.\n");
            float amplituda = 0;
            float okres = 0;
            printf("Amplituda: ");
            scanf("%f", &amplituda);
            printf("\nDlugosc okresu: ");
            scanf("%f", &okres);
            tab = Gen_sin(N, 0.01, amplituda, okres); //przyporzadkowywanie tablicy otrzymanych danych z generatora sinusa, 0.1 to zmienna utworzona do rozdzielczosci X, wykres rosnie i maleje w punktach co 0.1
            RysujWykres(tab, N, "wykres.html"); //wywołanie funkcji
            system("wykres.html"); //uruchomienie wykresu
            break;
        }
        case 2:
        {
            RysujWykres(tab, N, "wykres.html"); //wywołanie funkcji
            system("wykres.html"); //uruchomienie wykresu
            break;
        }
        case 3:
        {

            //for gen new sin

            system("cls");
            printf("Podaj parametry sygnalu.\n");
            float amplituda = 0;
            float okres = 0;
            printf("Amplituda: ");
            scanf("%f", &amplituda);
            printf("\nDlugosc okresu: ");
            scanf("%f", &okres);
            tab = Gen_sin(N, 0.01, amplituda, okres); //przyporzadkowywanie tablicy otrzymanych danych z generatora sinusa, 0.1 to zmienna utworzona do rozdzielczosci X, wykres rosnie i maleje w punktach co 0.1

            //       maybe if with statement checking if sin was generated
            plik fp = fopen("wykres.txt", "w");
            if (fp  == NULL) {
                printf("nie moge otworzyc pliku wykres.txt do zapisu danych");
                exit(1);
            }
            else {
                for (int i = 0; i < N; i++) {
                    fprintf(fp, "%f\n", tab[0][i]);
                }
                fprintf(fp,"Y\n");
                for (int i = 0; i < N; i++){
                    fprintf(fp, "%f\n", tab[1][i]);
                }
                fclose(fp);

            }
            break;

        }
        case 4:
        {
            plik fp = fopen("wykres.txt","r");
            if(fp == NULL){
                printf("nie udalo sie wczytac pliku");
                exit(-1);
            }
            else{
                float x_v[N];
                float y_v[N];
                for (int i = 0; i<N;i++) {
                    fscanf(fp, "%f", &(x_v[i]));
//                    printf("%f ",x_v[i]);
                }
                char s[] ="";
                fscanf(fp,"%s",&s);
                for (int i = 0; i<N;i++){
                    fscanf(fp,"%f",&(y_v[i]));
//                    printf("%f ",y_v[i]);
                }
                tab = calloc(sizeof(float*), 2);        // 2 bo x i y
                tab[0] = x_v;
                tab[1] = y_v;
                system("cls");
                RysujWykres(tab, N, "wykres.html"); //wywołanie funkcji
                system("wykres.html"); //uruchomienie wykresu
                fclose(fp);
            }
//            tab = wczytaj_z_pliku(fp,N);
//            RysujWykres(tab, N, "wykres.html"); //wywołanie funkcji
//            system("wykres.html"); //uruchomienie wykresu

            break;
        }
        case 5:
        {
            //funikcja
            break;
        }
        case 6:
        {
//            roboczo 6 zaszumia
            //funikcja
            break;
        }

            break;

    }

    return 0;
}



float** Gen_sin(int N, float tp, float amplituda, float okres) {
    // tp to rozdzielczosc jaka widzimy na wykresie X i Y co 0,1
    float** tab_sin;                //tworzenie nowej dynamicznej tablicy wskaznikow
    int i;



    tab_sin = calloc(sizeof(float*), 2);        // 2 bo x i y
    for (i = 0; i < 2; i++) {
        tab_sin[i] = calloc(sizeof(float), N); //tworzenie tablicy dwuwymiarowej
    }


    for (i = 0; i < N; i++) {       //wpisywanie wartosci do tej tablicy
        tab_sin[0][i] = tp * i;   //przypisywanie kolejnych wartosci X
        if (i % 100 < 50) {     //warunek gdy ma sie pojawic brzuszek
            tab_sin[1][i] = amplituda * sin(2 * pi * tab_sin[0][i]);        //dostosowanie do kolejnych komorek igrekowych iksa
        }
        else {      //warunek ze brzuszek ma sie nie pokazywac
            tab_sin[1][i] = 0; //i to x
        }
    }


    return tab_sin;
}



void RysujWykres(float** dane, int l_linii, char* nazwa) {



    FILE* Wsk_do_pliku;   //tworzenie pliku o nazwie Wsk_do_pliku
    int i;



    Wsk_do_pliku = fopen(nazwa, "w");



    fprintf(Wsk_do_pliku, "<html>\n");
    fprintf(Wsk_do_pliku, "<head>\n");
    fprintf(Wsk_do_pliku, "<script type=\"text/javascript\" src=\"https://www.google.com/jsapi\"></script>\n");
    fprintf(Wsk_do_pliku, "<script type=\"text/javascript\">\n");
    fprintf(Wsk_do_pliku, "google.load(\"visualization\", \"1\", {packages:[\"corechart\"]});\n");
    fprintf(Wsk_do_pliku, "google.setOnLoadCallback(drawChart);\n");
    fprintf(Wsk_do_pliku, "function drawChart() {\n");
    fprintf(Wsk_do_pliku, "var data = google.visualization.arrayToDataTable([\n");
    fprintf(Wsk_do_pliku, "['t', 'sin']");



    for (i = 0; i < l_linii; i++) { //l_linii???            //wypisywanie wykresu na stronie internetowej
        fprintf(Wsk_do_pliku, ",\n[%f, %f]", dane[0][i], dane[1][i]);
    }



    fprintf(Wsk_do_pliku, "\n]);\n");



    fprintf(Wsk_do_pliku, "var options = {\n");
    fprintf(Wsk_do_pliku, "title: 'S19'\n");
    fprintf(Wsk_do_pliku, "};\n");
    fprintf(Wsk_do_pliku, "var chart = new google.visualization.LineChart(document.getElementById('chart_div'));\n");
    fprintf(Wsk_do_pliku, "chart.draw(data, {\n");
    fprintf(Wsk_do_pliku, "colors: ['red','blue','green','yellow']\n");
    fprintf(Wsk_do_pliku, "}\n");
    fprintf(Wsk_do_pliku, ");\n");
    fprintf(Wsk_do_pliku, "}\n");
    fprintf(Wsk_do_pliku, "</script>\n");
    fprintf(Wsk_do_pliku, "</head>\n");
    fprintf(Wsk_do_pliku, "<body>\n");
    fprintf(Wsk_do_pliku, "<div id=\"chart_div\" style=\"width: 1280px; height: 720px;\"></div>\n");
    fprintf(Wsk_do_pliku, "</body>\n");
    fprintf(Wsk_do_pliku, "</html>\n");



    fclose(Wsk_do_pliku);
}