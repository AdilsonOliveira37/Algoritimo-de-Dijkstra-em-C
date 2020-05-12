#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define VERTMAX 100


void algDijkstra(int nVert, int orig, int dest, int * custos){
    double min, dist[VERTMAX];
    int i, v, ant[VERTMAX], z[VERTMAX];
    
    for(i=0; i <  nVert; i++){
        if(custos[(orig - 1) * nVert + i] != -1){
            ant[i] = orig - 1;
            dist[i] = custos[(orig-1) * nVert + i];
        }else {
            ant[i] = -1;
            dist[i] = HUGE_VAL;
        }
        z[i] = 0;
    }
    z[orig -1] = 1;
    dist[orig -1] = 0;

    do{
        min = HUGE_VAL;
        for (i = 0; i < nVert; i++)
            if (!z[i])
                if (dist[i] >= 0 && dist[i] < min){
                    min = dist[i];
                    v = i;
                }
        if(min != HUGE_VAL && v != dest - 1){
            z[v] = 1;
            for(i = 0; i < nVert; i++)
                if(!z[i]){
                    if(custos[v * nVert + i] != -1 && dist[v] + custos[v * nVert + i] < dist[i]){
                        dist[i] = dist[v] + custos[v * nVert + i];
                        ant[i] = v;
                    }
                }
        }
        // for(i = 0; i < nVert; i++){
        //     if(!z[i]){
        //         if(custos[v * nVert + i] != -1 && dist[v] + custos[v * nVert + i] < dist[i])
        //         {
        //             dist[i] = dist[v] + custos[v * nVert + i];
        //             ant[i] = v;
        //         }
        //     }
        // }
    }while(v != dest -1 && min != HUGE_VAL);
    if(min != HUGE_VAL)
        printf("O caminho mais proximo de %d à %d é...: %d\n", orig, dest, (int) dist[dest - 1]);          
    else{
        printf("Nao ha caminho possivel...\n");
    }
}

int main(){
    int op = 0;
    int i, dist, nVert = 0, orig, dest, *custos = NULL;
   
    while(1){   
        printf("\n********-Algoritimo de busca de menor caminho entre 2 pontos utilizando o algoritimo de Dijkstra-********\n\n");
        printf("<>Escolha a opcao desejada<>\n-> [1] Criar um digrafo\n-> [2] Verificar distancia\n-> [3] Encerrar aplicação..\n");
        scanf("%d", &op);

        switch (op)
        {
            case 1:
                do{
                    printf("Digite o numero de pontos (2 a 100):\n");
                    scanf("%d", &nVert);
                }while(nVert < 2 || nVert > VERTMAX);
                custos = (int *) malloc(sizeof(int) * nVert * nVert);
                for(i = 0; i <= nVert * nVert; i++)
                    custos[i];
                printf("Trace o caminho entre os ponos\n");
                do{
                    do{
                        printf("> Ponto de origem entre 1 e %d, ou 0 pra voltar ao menu\n", nVert);
                        scanf("%d", &orig);
                    }while(orig < 0 || orig > nVert);
                    if(orig){
                        do{
                            printf("> Ponto de destino entre o ponto de origem e algum outro ponto cadastrado..\n");
                            scanf("%d", &dest);
                        }while (dest < 1 || dest > nVert || dest == orig);
                        do{
                            printf("> Distancia entre os pontos %d para %d:\n", orig, dest);
                            scanf("%d", &dist);
                        }while(dist < 0);
                        custos[(orig - 1) * nVert + dest - 1] = dist;
                    }
                }while(orig);
            break;
            case 2:
                if(nVert == 0)
                    printf("\n\n> Por favor cadastre no minimo 2 pontos na opcao anterior\n");
                else{
                    do{
                        printf("Qual o ponto de origem entre 1 e %d..?\n", nVert);
                        scanf("%d", &orig);
                    }while(orig < 1 || orig > nVert);
                    do{
                        printf("Qual o ponto de destino com exceção do %d..?\n", orig);
                        scanf("%d", &dest);
                    }while(dest < 1 || dest > nVert || dest == orig);
                    printf("alo>>>>>>>>>>>>");
                    algDijkstra(nVert, orig, dest, custos);
                }
            break;
            case 3: 
                exit(0);
            break;
        }
    }


    return 0;
}