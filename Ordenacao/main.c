#include <stdio.h>
#include <stdlib.h>
#include <time.h>

clock_t tempoInicio, tempoFim;
FILE *gnuplot;
unsigned long  troca=0,comparacao=0;

///----------------------------------------------------------------------------------------
int *LendoArquivo(char *nomeArq, long int *tamanho)
{
    FILE *arquivo;
    int *vetor;
    long int i, LinhasdoArquivo;

    char linha[200];


    //abre arquivo e descobre quantidade de numeros para o vetor
    arquivo = fopen(nomeArq,"r");

    if (!arquivo)
    {
        printf("Arquivo nao existe\n");
        exit(0);
    }

    LinhasdoArquivo = 0;
    while (fgets(linha,200,arquivo))
    {
        LinhasdoArquivo++;
    }
    fclose(arquivo);
    *tamanho = LinhasdoArquivo;
    fprintf( gnuplot, "%d\t\t", LinhasdoArquivo);

    vetor = malloc(sizeof(int) * LinhasdoArquivo);


    arquivo = fopen(nomeArq,"r");
    i = 0;
    while (fgets(linha,200,arquivo))
    {
        //percorrer arquivo para gravar numeros no vetor

        vetor[i] = atoi(linha);
        i++;
    }

    fclose(arquivo);
    return vetor;
}

///----------------------------------------------------------------------------------------
void BubbleSort(int *vetor, long int n)
{
    unsigned long long int i, j, trocasFeitas = 0, comparacoesFeitas = 0;


    tempoInicio = clock();
    for (j=0; j<n-1; j++)
    {
        for (i=0; i<n-(j+1); i++)
        {
            comparacoesFeitas++;
            if (vetor[i]>vetor[i+1])
            {
                int aux = vetor[i+1];
                vetor[i+1] = vetor[i];
                vetor[i]= aux;
                trocasFeitas++;

            }
        }
    }
    tempoFim = clock();
    fprintf( gnuplot," %f\t", (float)(tempoFim - tempoInicio)/CLOCKS_PER_SEC);
    fprintf( gnuplot, "%ld\t\t",comparacoesFeitas);
    fprintf( gnuplot, "%ld\n", trocasFeitas);


    printf("Comparacoes: %ld\nTrocas: %ld\n", comparacoesFeitas, trocasFeitas);
    printf("Tempo: %f\n", (float)(tempoFim - tempoInicio)/CLOCKS_PER_SEC);
}
///----------------------------------------------------------------------------------------
void shellSort(int *Vetor, long int tamanho)
{
    long int i = (tamanho - 1) / 2;
    int chave, k, aux,trocasFeitas = 0, comparacoesFeitas = 0;

    tempoInicio = clock();

    while(i != 0)
    {
        do
        {
            chave = 1;
            for(k = 0; k < tamanho - i; ++k)
            {
                comparacoesFeitas++;
                if(Vetor[k] > Vetor[k + i])
                {
                    aux = Vetor[k];
                    Vetor[k] = Vetor[k + i];
                    Vetor[k + i] = aux;
                    chave = 0;
                    trocasFeitas++;
                }
            }
        }
        while(chave == 0);
        i = i / 2;
    }
     tempoFim = clock();
    fprintf( gnuplot," %f\t", (float)(tempoFim - tempoInicio)/CLOCKS_PER_SEC);
    fprintf( gnuplot, "%ld\t\t",comparacoesFeitas);
    fprintf( gnuplot, "%ld\n", trocasFeitas);

    printf("Comparacoes: %ld\nTrocas: %ld\n", comparacoesFeitas, trocasFeitas);
    printf("Tempo: %f\n", (float)(tempoFim - tempoInicio)/CLOCKS_PER_SEC);
}
///----------------------------------------------------------------------------------------
void selectSort(int *vetor,long int n)
{
    long int i, j, posMenor, trocasFeitas = 0, comparacoesFeitas = 0;
    int aux;

    tempoInicio = clock();
    for (i = 0; i < n - 1; i++)
    {
        posMenor = i;
        for (j = i + 1; j < n; j++)
        {
            comparacoesFeitas++;
            if (vetor[j] < vetor[posMenor]) posMenor = j;
        }

        if (posMenor != i)
        {
            trocasFeitas++;
            aux = vetor[i];
            vetor[i] = vetor[posMenor];
            vetor[posMenor] = aux;
        }
    }
    tempoFim = clock();
    fprintf( gnuplot," %f\t", (float)(tempoFim - tempoInicio)/CLOCKS_PER_SEC);
    fprintf( gnuplot, "%ld\t\t",comparacoesFeitas);
    fprintf( gnuplot, "%ld\n", trocasFeitas);

    printf("Comparacoes: %ld\nTrocas: %ld\n", comparacoesFeitas, trocasFeitas);
    printf("Tempo: %f\n", (float)(tempoFim - tempoInicio)/CLOCKS_PER_SEC);
}
///----------------------------------------------------------------------------------------
void insertionSort(int *vetor, long int n)
{
    long long int i, j, trocasFeitas = 0, comparacoesFeitas = 0;
    int aux;
    tempoInicio = clock();
    for (i = 1; i < n; i++)
    {
        aux = vetor[i];
        for (j = i - 1; j >= 0 && aux < vetor[j]; --j, comparacoesFeitas++)
        {
            //   printf("%d - %d\n", vetor[j+1], vetor[j]);
            // getch();
            vetor[j + 1] = vetor[j];
            trocasFeitas++;
        }
        vetor[j + 1] = aux;
        trocasFeitas++;
    }
    tempoFim = clock();
    fprintf( gnuplot," %f\t", (float)(tempoFim - tempoInicio)/CLOCKS_PER_SEC);
    fprintf( gnuplot, "%ld\t\t",comparacoesFeitas);
    fprintf( gnuplot, "%ld\n", trocasFeitas);

    printf("Comparacoes: %ld\nTrocas: %ld\n", comparacoesFeitas, trocasFeitas);
    printf("Tempo: %f\n", (float)(tempoFim - tempoInicio)/CLOCKS_PER_SEC);

}



//=========================================================================================
void mergee (int *vetor,int v2[],int inicio1, int inicio2,int fim2)
{
    long int n1=inicio1;
    long int n2=inicio2;
    long int fim1=n2-1;
    long int aux=0,i;

    tempoInicio = clock();

    comparacao++;
    while((n1<=fim1) && (n2<=fim2))
    {

        if (vetor[n1]<vetor[n2])
        {
            troca++;
            comparacao++;
            v2[aux++] = vetor[n1++];


        }
        else
        {
            troca++;
            comparacao++;

            v2[aux++] = vetor[n2++];

        }


    }

    while(n1<=fim1)
    {
        v2[aux++] = vetor[n1++];
        troca++;
        comparacao++;


    }
    while(n2<=fim2)
    {
        v2[aux++] = vetor[n2++];
        troca++;
        comparacao++;

    }


    for(i=0; i<aux; i++)
    {
        vetor[i+inicio1]=v2[i];
         troca++;
      //  comparacao++;
    }

    tempoFim = clock();
}
void mergeSort (int *vetor, int v2[],long int esq, long int dir)
{

    long int meio,valor,valor2,res;

    if(esq<dir)
    {
        meio=(esq+dir)/2;
        mergeSort(vetor,v2,esq,meio);
        mergeSort(vetor,v2,meio+1,dir);
        mergee(vetor,v2,esq,meio+1,dir);
    }


}

///----------------------------------------------------------------------------------------

void quicksort(int *vetor, int esq, int dir) {

    int i, j, pivo, aux;

    i = esq;
    j = dir;

    tempoInicio = clock();
    //pivo = vetor[(esq + dir) / 2]; //Elemento central como pivô
    pivo = vetor[esq];
   // pivo = vetor[dir];

    while(i <= j) {
        while(vetor[i] < pivo && i < dir) {
            i++;
            comparacao++;
        }
        while(vetor[j] > pivo && j > esq) {
            j--;
            comparacao++;
        }
        if(i <= j) {
            aux = vetor[i];
            vetor[i] = vetor[j];
            vetor[j] = aux;
            i++;
            j--;
             troca++;
          //  comparacao++;
        }
    }


    if(j > esq) {
        quicksort(vetor, esq, j);
    }
    if(i < dir) {
        quicksort(vetor, i, dir);
    }
    tempoFim = clock();
}


///----------------------------------------------------------------------------------------
void GravarArquivo(int *vetor, long int tamanho)
{
    long int i;
    FILE *gravar;
    char Nome_arquivo[200];

    sprintf(Nome_arquivo, "Vetor-%ld-Ordenado.txt", tamanho);

    gravar = fopen(Nome_arquivo,"w");
    for (i = 0; i < tamanho; i++)
    {
        //printf("%d\t", vetor[i]);
        fprintf( gravar," %d\n", vetor[i]);
        fflush(gravar);
    }
    fclose(gravar);
    printf("\n");
}
void MostarVetor(int *vetor, long int tamanho)
{
    long int i;

    for (i = 0; i<tamanho; i++)
    {
        printf("%d\t", vetor[i]);
    }
    printf("\n");
}
///----------------------------------------------------------------------------------------
void printClockMergeQuick(){

    fprintf( gnuplot," %f\t", (float)(tempoFim - tempoInicio)/CLOCKS_PER_SEC);
    fprintf( gnuplot, "%ld\t\t",comparacao);
    fprintf( gnuplot, "%ld\n", troca);

     printf("comparacao: %ld\n Trocas %ld\n",comparacao,troca);
     printf("Tempo: %f\n", (float)(tempoFim - tempoInicio)/CLOCKS_PER_SEC);


}

int main()
{
    int *VetorArquivo;
    long int tamanho;
    long int vetor2[100000];
    int op;

    do
    {
        //system ("clear");
        printf("\n\t|----------| MENU DE OPCOES | ------------|");
        printf("\n\t|-----------------------------------------|");
        printf("\n\t| 1 -------| BUBBLE  SORT |---------------|");
        printf("\n\t| 2 -------| SELECT  SORT |---------------|");
        printf("\n\t| 3 -------| INSERT  SORT |---------------|");
        printf("\n\t| 4 -------| QUICK   SORT |---------------|");
        printf("\n\t| 5 -------| MERGE   SORT |---------------|");
        printf("\n\t| 6 -------| SHELL   SORT |---------------|");
        printf("\n\t|-----------------------------------------|\n");
        scanf("\t %d",&op);

        switch(op)
        {
        case 1 :

            gnuplot = fopen("bubble-sorte-rond.dat", "w");

            printf("Ordenando vetor com 100 elementos\n");
            fprintf(gnuplot, "#RANDOMICOS\n#Tamanho\t Tempo\t\t Comparacao\t trocas\n");
            VetorArquivo = LendoArquivo("vetores/N100.txt",&tamanho);
            BubbleSort(VetorArquivo, tamanho);
            GravarArquivo(VetorArquivo, tamanho);
            ///-----------------------------------------------------------------------
            printf("Ordenando vetor com 1.000 elementos\n");
            VetorArquivo = LendoArquivo("vetores/N1000.txt",&tamanho);
            BubbleSort(VetorArquivo, tamanho);
            GravarArquivo(VetorArquivo, tamanho);
            ///------------------------------------------------------------------------
            printf("Ordenando vetor com 10.000 elementos\n");
            VetorArquivo = LendoArquivo("vetores/N10000.txt",&tamanho);
            BubbleSort(VetorArquivo, tamanho);
            GravarArquivo(VetorArquivo, tamanho);
            ///------------------------------------------------------------------------
            printf("Ordenando vetor de 50.000 elementos\n");
            VetorArquivo = LendoArquivo("vetores/N50000.txt",&tamanho);
            BubbleSort(VetorArquivo, tamanho);
            GravarArquivo(VetorArquivo, tamanho);
            ///------------------------------------------------------------------------
            printf("Ordenando vetor de 100.000 elementos \n");
            VetorArquivo = LendoArquivo("vetores/N100000.txt",&tamanho);
            BubbleSort(VetorArquivo, tamanho);
            GravarArquivo(VetorArquivo, tamanho);
            fclose(gnuplot);
            ///-----------------------------------------------------------------------
            printf("|================================================================|\n");

            gnuplot = fopen("bubbleSorte-ord.dat", "w");
            printf("Vetor ja ordenado com 100\n");
            fprintf(gnuplot, "#ORDENANDOS\n#Tamanho\t Tempo\t\t Comparacao\t trocas\n");
            VetorArquivo = LendoArquivo("vetores/N100-ordenado.txt",&tamanho);
            BubbleSort(VetorArquivo, tamanho);
            GravarArquivo(VetorArquivo, tamanho);

            ///-----------------------------------------------------------------------
            printf("Vetor ja ordenado com 1.000\n");
            VetorArquivo = LendoArquivo("vetores/N1000-ordenado.txt",&tamanho);
            BubbleSort(VetorArquivo, tamanho);
            GravarArquivo(VetorArquivo, tamanho);
            ///------------------------------------------------------------------------
            printf("Vetor ja ordenado com 10.000\n");
            VetorArquivo = LendoArquivo("vetores/N10000-ordenado.txt",&tamanho);
            BubbleSort(VetorArquivo, tamanho);
            GravarArquivo(VetorArquivo, tamanho);
            ///------------------------------------------------------------------------
            printf("Vetor ja ordenado com 50.000\n");
            VetorArquivo = LendoArquivo("vetores/N50000-ordenado.txt",&tamanho);
            BubbleSort(VetorArquivo, tamanho);
            GravarArquivo(VetorArquivo, tamanho);
            ///------------------------------------------------------------------------
            printf("Vetor ja ordenado com 100.000\n");
            VetorArquivo = LendoArquivo("vetores/N100000-ordenado.txt",&tamanho);
            BubbleSort(VetorArquivo, tamanho);
            GravarArquivo(VetorArquivo, tamanho);
            fclose(gnuplot);
            ///-----------------------------------------------------------------------
             printf("|================================================================|\n");

             gnuplot = fopen("bubbleSorte-inv.dat", "w");
            printf("Vetor ordenando inverso com 100\n");
            fprintf(gnuplot, "#ORDENANDO INVERSO\n#Tamanho\t Tempo\t\t Comparacao\t trocas\n");
            VetorArquivo = LendoArquivo("vetores/N100-inverso.txt",&tamanho);
            BubbleSort(VetorArquivo, tamanho);
            GravarArquivo(VetorArquivo, tamanho);

            ///-----------------------------------------------------------------------
            printf("Vetor ordenando inverso com 1.000\n");
            VetorArquivo = LendoArquivo("vetores/N1000-inverso.txt",&tamanho);
            BubbleSort(VetorArquivo, tamanho);
            GravarArquivo(VetorArquivo, tamanho);
            ///------------------------------------------------------------------------
            printf("Vetor ordenando inverso com 10.000\n");
            VetorArquivo = LendoArquivo("vetores/N10000-inverso.txt",&tamanho);
            BubbleSort(VetorArquivo, tamanho);
            GravarArquivo(VetorArquivo, tamanho);
            ///------------------------------------------------------------------------
            printf("Vetor ordenando inverso com 50.000\n");
            VetorArquivo = LendoArquivo("vetores/N50000-inverso.txt",&tamanho);
            BubbleSort(VetorArquivo, tamanho);
            GravarArquivo(VetorArquivo, tamanho);
            ///------------------------------------------------------------------------
            printf("Vetor ordenando inverso com 10.000\n");
            VetorArquivo = LendoArquivo("vetores/N100000-inverso.txt",&tamanho);
            BubbleSort(VetorArquivo, tamanho);
            GravarArquivo(VetorArquivo, tamanho);
            fclose(gnuplot);
            ///-----------------------------------------------------------------------

            system("gnuplot -bg gray90 plota.gnu");

            break;

        case 2:

            gnuplot = fopen("Select-sort-rond.dat", "w");

            printf("Ordenando vetor com 100 elementos\n");
            fprintf(gnuplot, "#RANDOMICOS\n#Tamanho\t Tempo\t\t Comparacao\t trocas\n");
            VetorArquivo = LendoArquivo("vetores/N100.txt",&tamanho);
            selectSort(VetorArquivo, tamanho);
            GravarArquivo(VetorArquivo, tamanho);
            ///-----------------------------------------------------------------------
            printf("Ordenando vetor com 1.000 elementos\n");
            VetorArquivo = LendoArquivo("vetores/N1000.txt",&tamanho);
            selectSort(VetorArquivo, tamanho);
            GravarArquivo(VetorArquivo, tamanho);
            ///------------------------------------------------------------------------
            printf("Ordenando vetor com 10.000 elementos\n");
            VetorArquivo = LendoArquivo("vetores/N10000.txt",&tamanho);
            selectSort(VetorArquivo, tamanho);
            GravarArquivo(VetorArquivo, tamanho);
            ///------------------------------------------------------------------------
            printf("Ordenando vetor de 50.000 elementos\n");
            VetorArquivo = LendoArquivo("vetores/N50000.txt",&tamanho);
            selectSort(VetorArquivo, tamanho);
            GravarArquivo(VetorArquivo, tamanho);
            ///------------------------------------------------------------------------
            printf("Ordenando vetor de 100.000 elementos \n");
            VetorArquivo = LendoArquivo("vetores/N100000.txt",&tamanho);
            selectSort(VetorArquivo, tamanho);
            GravarArquivo(VetorArquivo, tamanho);
            fclose(gnuplot);
            ///-----------------------------------------------------------------------
            printf("|================================================================|\n");

            gnuplot = fopen("Select-sort-ord.dat", "w");
            printf("Vetor ja ordenado com 100\n");
            fprintf(gnuplot, "#ORDENANDOS\n#Tamanho\t Tempo\t\t Comparacao\t trocas\n");
            VetorArquivo = LendoArquivo("vetores/N100-ordenado.txt",&tamanho);
            selectSort(VetorArquivo, tamanho);
            GravarArquivo(VetorArquivo, tamanho);

            ///-----------------------------------------------------------------------
            printf("Vetor ja ordenado com 1.000\n");
            VetorArquivo = LendoArquivo("vetores/N1000-ordenado.txt",&tamanho);
            selectSort(VetorArquivo, tamanho);
            GravarArquivo(VetorArquivo, tamanho);
            ///------------------------------------------------------------------------
            printf("Vetor ja ordenado com 10.000\n");
            VetorArquivo = LendoArquivo("vetores/N10000-ordenado.txt",&tamanho);
            selectSort(VetorArquivo, tamanho);
            GravarArquivo(VetorArquivo, tamanho);
            ///------------------------------------------------------------------------
            printf("Vetor ja ordenado com 50.000\n");
            VetorArquivo = LendoArquivo("vetores/N50000-ordenado.txt",&tamanho);
            selectSort(VetorArquivo, tamanho);
            GravarArquivo(VetorArquivo, tamanho);
            ///------------------------------------------------------------------------
            printf("Vetor ja ordenado com 100.000\n");
            VetorArquivo = LendoArquivo("vetores/N100000-ordenado.txt",&tamanho);
            selectSort(VetorArquivo, tamanho);
            GravarArquivo(VetorArquivo, tamanho);
            fclose(gnuplot);
            ///-----------------------------------------------------------------------
             printf("|================================================================|\n");

             gnuplot = fopen("Select-sort-inv.dat", "w");
            printf("Vetor ordenando inverso com 100\n");
            fprintf(gnuplot, "#ORDENANDO INVERSO\n#Tamanho\t Tempo\t\t Comparacao\t trocas\n");
            VetorArquivo = LendoArquivo("vetores/N100-inverso.txt",&tamanho);
            selectSort(VetorArquivo, tamanho);
            GravarArquivo(VetorArquivo, tamanho);

            ///-----------------------------------------------------------------------
            printf("Vetor ordenando inverso com 1.000\n");
            VetorArquivo = LendoArquivo("vetores/N1000-inverso.txt",&tamanho);
            selectSort(VetorArquivo, tamanho);
            GravarArquivo(VetorArquivo, tamanho);
            ///------------------------------------------------------------------------
            printf("Vetor ordenando inverso com 10.000\n");
            VetorArquivo = LendoArquivo("vetores/N10000-inverso.txt",&tamanho);
            selectSort(VetorArquivo, tamanho);
            GravarArquivo(VetorArquivo, tamanho);
            ///------------------------------------------------------------------------
            printf("Vetor ordenando inverso com 50.000\n");
            VetorArquivo = LendoArquivo("vetores/N50000-inverso.txt",&tamanho);
            selectSort(VetorArquivo, tamanho);
            GravarArquivo(VetorArquivo, tamanho);
            ///------------------------------------------------------------------------
            printf("Vetor ordenando inverso com 100.000\n");
            VetorArquivo = LendoArquivo("vetores/N100000-inverso.txt",&tamanho);
            selectSort(VetorArquivo, tamanho);
            GravarArquivo(VetorArquivo, tamanho);
            fclose(gnuplot);
            ///-----------------------------------------------------------------------

            system("gnuplot -bg gray90 plota2.gnu");
            break;
        case 3:

            gnuplot = fopen("Insert-sort-rond.dat", "w");

            printf("Ordenando vetor com 100 elementos\n");
            fprintf(gnuplot, "#RANDOMICOS\n#Tamanho\t Tempo\t\t Comparacao\t trocas\n");
            VetorArquivo = LendoArquivo("vetores/N100.txt",&tamanho);
            insertionSort(VetorArquivo, tamanho);
            GravarArquivo(VetorArquivo, tamanho);
            ///-----------------------------------------------------------------------
            printf("Ordenando vetor com 1.000 elementos\n");
            VetorArquivo = LendoArquivo("vetores/N1000.txt",&tamanho);
            insertionSort(VetorArquivo, tamanho);
            GravarArquivo(VetorArquivo, tamanho);
            ///------------------------------------------------------------------------
            printf("Ordenando vetor com 10.000 elementos\n");
            VetorArquivo = LendoArquivo("vetores/N10000.txt",&tamanho);
            insertionSort(VetorArquivo, tamanho);
            GravarArquivo(VetorArquivo, tamanho);
            ///------------------------------------------------------------------------
            printf("Ordenando vetor de 50.000 elementos\n");
            VetorArquivo = LendoArquivo("vetores/N50000.txt",&tamanho);
            insertionSort(VetorArquivo, tamanho);
            GravarArquivo(VetorArquivo, tamanho);
            ///------------------------------------------------------------------------
            printf("Ordenando vetor de 100.000 elementos \n");
            VetorArquivo = LendoArquivo("vetores/N100000.txt",&tamanho);
            insertionSort(VetorArquivo, tamanho);
            GravarArquivo(VetorArquivo, tamanho);
            fclose(gnuplot);
            ///-----------------------------------------------------------------------
            printf("|================================================================|\n");

            gnuplot = fopen("Insert-sort-ord.dat", "w");

            printf("Vetor ja ordenado com 100\n");
            fprintf(gnuplot, "#ORDENANDOS\n#Tamanho\t Tempo\t\t Comparacao\t trocas\n");
            VetorArquivo = LendoArquivo("vetores/N100-ordenado.txt",&tamanho);
            insertionSort(VetorArquivo, tamanho);
            GravarArquivo(VetorArquivo, tamanho);

            ///-----------------------------------------------------------------------
            printf("Vetor ja ordenado com 1.000\n");
            VetorArquivo = LendoArquivo("vetores/N1000-ordenado.txt",&tamanho);
            insertionSort(VetorArquivo, tamanho);
            GravarArquivo(VetorArquivo, tamanho);
            ///------------------------------------------------------------------------
            printf("Vetor ja ordenado com 10.000\n");
            VetorArquivo = LendoArquivo("vetores/N10000-ordenado.txt",&tamanho);
            insertionSort(VetorArquivo, tamanho);
            GravarArquivo(VetorArquivo, tamanho);
            ///------------------------------------------------------------------------
            printf("Vetor ja ordenado com 50.000\n");
            VetorArquivo = LendoArquivo("vetores/N50000-ordenado.txt",&tamanho);
            insertionSort(VetorArquivo, tamanho);
            GravarArquivo(VetorArquivo, tamanho);
            ///------------------------------------------------------------------------
            printf("Vetor ja ordenado com 100.000\n");
            VetorArquivo = LendoArquivo("vetores/N100000-ordenado.txt",&tamanho);
            insertionSort(VetorArquivo, tamanho);
            GravarArquivo(VetorArquivo, tamanho);
            fclose(gnuplot);
            ///-----------------------------------------------------------------------
             printf("|================================================================|\n");

            gnuplot = fopen("Insert-sort-inv.dat", "w");

            printf("Vetor ordenando inverso com 100\n");
            fprintf(gnuplot, "#ORDENANDO INVERSO\n#Tamanho\t Tempo\t\t Comparacao\t trocas\n");
            VetorArquivo = LendoArquivo("vetores/N100-inverso.txt",&tamanho);
            insertionSort(VetorArquivo, tamanho);
            GravarArquivo(VetorArquivo, tamanho);

            ///-----------------------------------------------------------------------
            printf("Vetor ordenando inverso com 1.000\n");
            VetorArquivo = LendoArquivo("vetores/N1000-inverso.txt",&tamanho);
            insertionSort(VetorArquivo, tamanho);
            GravarArquivo(VetorArquivo, tamanho);
            ///------------------------------------------------------------------------
            printf("Vetor ordenando inverso com 10.000\n");
            VetorArquivo = LendoArquivo("vetores/N10000-inverso.txt",&tamanho);
            insertionSort(VetorArquivo, tamanho);
            GravarArquivo(VetorArquivo, tamanho);
            ///------------------------------------------------------------------------
            printf("Vetor ordenando inverso com 50.000\n");
            VetorArquivo = LendoArquivo("vetores/N50000-inverso.txt",&tamanho);
            insertionSort(VetorArquivo, tamanho);
            GravarArquivo(VetorArquivo, tamanho);
            ///------------------------------------------------------------------------
            printf("Vetor ordenando inverso com 100.000\n");
            VetorArquivo = LendoArquivo("vetores/N100000-inverso.txt",&tamanho);
            insertionSort(VetorArquivo, tamanho);
            GravarArquivo(VetorArquivo, tamanho);
            fclose(gnuplot);
            ///-----------------------------------------------------------------------

            system("gnuplot -bg gray90 plota3.gnu");
            //insertionSort(VetorArquivo, tamanho);

            break;
        case 4:

             gnuplot = fopen("quick-sort-rand.dat", "w");
             printf("Ordenando vetor com 100 elementos\n");
            fprintf(gnuplot, "#RANDOMICOS\n#Tamanho\t Tempo\t\t Comparacao\t trocas\n");
            VetorArquivo = LendoArquivo("vetores/N100.txt",&tamanho);
            quicksort(VetorArquivo,0,tamanho-1);
           // MostarVetor(VetorArquivo,tamanho);
            printClockMergeQuick();

            //GravarArquivo(VetorArquivo, tamanho);
            ///-----------------------------------------------------------------------
            printf("Ordenando vetor com 1.000 elementos\n");
            VetorArquivo = LendoArquivo("vetores/N1000.txt",&tamanho);
            quicksort(VetorArquivo,0,tamanho-1);
            //GravarArquivo(VetorArquivo, tamanho);
             printClockMergeQuick();
            ///------------------------------------------------------------------------
            printf("Ordenando vetor com 10.000 elementos\n");
            VetorArquivo = LendoArquivo("vetores/N10000.txt",&tamanho);
            quicksort(VetorArquivo,0,tamanho-1);
            printClockMergeQuick();
            GravarArquivo(VetorArquivo, tamanho);
            ///------------------------------------------------------------------------
            printf("Ordenando vetor de 50.000 elementos\n");
            VetorArquivo = LendoArquivo("vetores/N50000.txt",&tamanho);
            quicksort(VetorArquivo,0,tamanho-1);
            printClockMergeQuick();
            //GravarArquivo(VetorArquivo, tamanho);
            ///------------------------------------------------------------------------
            printf("Ordenando vetor de 100.000 elementos \n");
            VetorArquivo = LendoArquivo("vetores/N100000.txt",&tamanho);
            quicksort(VetorArquivo,0,tamanho-1);
            printClockMergeQuick();
            //GravarArquivo(VetorArquivo, tamanho);
            fclose(gnuplot);
            ///-----------------------------------------------------------------------
            printf("|================================================================|\n");

            gnuplot = fopen("quick-sort-ord.dat", "w");
            printf("Vetor ja ordenado com 100\n");
            fprintf(gnuplot, "#ORDENANDOS\n#Tamanho\t Tempo\t\t Comparacao\t trocas\n");
            VetorArquivo = LendoArquivo("vetores/N100-ordenado.txt",&tamanho);
            quicksort(VetorArquivo,0,tamanho-1);
            printClockMergeQuick();
            //GravarArquivo(VetorArquivo, tamanho);

            ///-----------------------------------------------------------------------
            printf("Vetor ja ordenado com 1.000\n");
            VetorArquivo = LendoArquivo("vetores/N1000-ordenado.txt",&tamanho);
            quicksort(VetorArquivo,0,tamanho-1);
            printClockMergeQuick();
            //GravarArquivo(VetorArquivo, tamanho);
            ///------------------------------------------------------------------------
            printf("Vetor ja ordenado com 10.000\n");
            VetorArquivo = LendoArquivo("vetores/N10000-ordenado.txt",&tamanho);;
            quicksort(VetorArquivo,0,tamanho-1);
            printClockMergeQuick();
            //GravarArquivo(VetorArquivo, tamanho);
            ///------------------------------------------------------------------------
            printf("Vetor ja ordenado com 50.000\n");
            VetorArquivo = LendoArquivo("vetores/N50000-ordenado.txt",&tamanho);
            quicksort(VetorArquivo,0,tamanho-1);
            printClockMergeQuick();
            //GravarArquivo(VetorArquivo, tamanho);
            ///------------------------------------------------------------------------
            printf("Vetor ja ordenado com 100.000\n");
            VetorArquivo = LendoArquivo("vetores/N100000-ordenado.txt",&tamanho);
            quicksort(VetorArquivo,0,tamanho-1);
            printClockMergeQuick();
            //GravarArquivo(VetorArquivo, tamanho);
            fclose(gnuplot);
            ///-----------------------------------------------------------------------
             printf("|================================================================|\n");

             gnuplot = fopen("quick-sort-inv.dat", "w");
            printf("Vetor ordenando inverso com 100\n");
            fprintf(gnuplot, "#ORDENANDO INVERSO\n#Tamanho\t Tempo\t\t Comparacao\t trocas\n");
            VetorArquivo = LendoArquivo("vetores/N100-inverso.txt",&tamanho);
            quicksort(VetorArquivo,0,tamanho-1);
            printClockMergeQuick();
           // GravarArquivo(VetorArquivo, tamanho);
            ///-----------------------------------------------------------------------
            printf("Vetor ordenando inverso com 1.000\n");
            VetorArquivo = LendoArquivo("vetores/N1000-inverso.txt",&tamanho);
            quicksort(VetorArquivo,0,tamanho-1);
            printClockMergeQuick();
            //GravarArquivo(VetorArquivo, tamanho);
            ///------------------------------------------------------------------------
            printf("Vetor ordenando inverso com 10.000\n");
            VetorArquivo = LendoArquivo("vetores/N10000-inverso.txt",&tamanho);
            quicksort(VetorArquivo,0,tamanho-1);
            printClockMergeQuick();
           // GravarArquivo(VetorArquivo, tamanho);
            ///------------------------------------------------------------------------
            printf("Vetor ordenando inverso com 50.000\n");
            VetorArquivo = LendoArquivo("vetores/N50000-inverso.txt",&tamanho);
            quicksort(VetorArquivo,0,tamanho-1);
            printClockMergeQuick();
          //  GravarArquivo(VetorArquivo, tamanho);
            ///------------------------------------------------------------------------
            printf("Vetor ordenando inverso com 100.000\n");
            VetorArquivo = LendoArquivo("vetores/N100000-inverso.txt",&tamanho);
            quicksort(VetorArquivo,0,tamanho-1);
            printClockMergeQuick();
           // GravarArquivo(VetorArquivo, tamanho);
            fclose(gnuplot);
            ///-----------------------------------------------------------------------

            system("gnuplot -bg gray90 plota4.gnu");


            break;
        case 5:
            gnuplot = fopen("merge-sort-rand.dat", "w");
             printf("Ordenando vetor com 100 elementos\n");
            fprintf(gnuplot, "#RANDOMICOS\n#Tamanho\t Tempo\t\t Comparacao\t trocas\n");
            VetorArquivo = LendoArquivo("vetores/N100.txt",&tamanho);
            mergeSort(VetorArquivo,vetor2,0,tamanho);
            printClockMergeQuick();
            MostarVetor(VetorArquivo,tamanho);
            //GravarArquivo(VetorArquivo, tamanho);
            ///-----------------------------------------------------------------------
            printf("Ordenando vetor com 1.000 elementos\n");
            VetorArquivo = LendoArquivo("vetores/N1000.txt",&tamanho);
             mergeSort(VetorArquivo,vetor2,0,tamanho);
            printClockMergeQuick();
            //GravarArquivo(VetorArquivo, tamanho);
            ///------------------------------------------------------------------------
            printf("Ordenando vetor com 10.000 elementos\n");
            VetorArquivo = LendoArquivo("vetores/N10000.txt",&tamanho);
             mergeSort(VetorArquivo,vetor2,0,tamanho);
            printClockMergeQuick();
            //GravarArquivo(VetorArquivo, tamanho);
            ///------------------------------------------------------------------------
            printf("Ordenando vetor de 50.000 elementos\n");
            VetorArquivo = LendoArquivo("vetores/N50000.txt",&tamanho);
             mergeSort(VetorArquivo,vetor2,0,tamanho);
            printClockMergeQuick();
           // GravarArquivo(VetorArquivo, tamanho);
            ///------------------------------------------------------------------------
            printf("Ordenando vetor de 100.000 elementos \n");
            VetorArquivo = LendoArquivo("vetores/N100000.txt",&tamanho);
            mergeSort(VetorArquivo,vetor2,0,tamanho);
            printClockMergeQuick();
           // GravarArquivo(VetorArquivo, tamanho);
            fclose(gnuplot);
            ///-----------------------------------------------------------------------
            printf("|================================================================|\n");

            gnuplot = fopen("merge-sort-ord.dat", "w");
            printf("Vetor ja ordenado com 100\n");
            fprintf(gnuplot, "#ORDENANDOS\n#Tamanho\t Tempo\t\t Comparacao\t trocas\n");
            VetorArquivo = LendoArquivo("vetores/N100-ordenado.txt",&tamanho);
             mergeSort(VetorArquivo,vetor2,0,tamanho);
            printClockMergeQuick();
            //GravarArquivo(VetorArquivo, tamanho);

            ///-----------------------------------------------------------------------
            printf("Vetor ja ordenado com 1.000\n");
            VetorArquivo = LendoArquivo("vetores/N1000-ordenado.txt",&tamanho);
             mergeSort(VetorArquivo,vetor2,0,tamanho);
           printClockMergeQuick();
           // GravarArquivo(VetorArquivo, tamanho);
            ///------------------------------------------------------------------------
            printf("Vetor ja ordenado com 10.000\n");
            VetorArquivo = LendoArquivo("vetores/N10000-ordenado.txt",&tamanho);
             mergeSort(VetorArquivo,vetor2,0,tamanho);
            printClockMergeQuick();
            //GravarArquivo(VetorArquivo, tamanho);
            ///------------------------------------------------------------------------
            printf("Vetor ja ordenado com 50.000\n");
            VetorArquivo = LendoArquivo("vetores/N50000-ordenado.txt",&tamanho);
             mergeSort(VetorArquivo,vetor2,0,tamanho);
           printClockMergeQuick();
           // GravarArquivo(VetorArquivo, tamanho);
            ///------------------------------------------------------------------------
            printf("Vetor ja ordenado com 100.000\n");
            VetorArquivo = LendoArquivo("vetores/N100000-ordenado.txt",&tamanho);
             mergeSort(VetorArquivo,vetor2,0,tamanho);
           printClockMergeQuick();
           // GravarArquivo(VetorArquivo, tamanho);
            fclose(gnuplot);
            ///-----------------------------------------------------------------------
             printf("|================================================================|\n");

             gnuplot = fopen("merge-sort-inv.dat", "w");
            printf("Vetor ordenando inverso com 100\n");
            fprintf(gnuplot, "#ORDENANDO INVERSO\n#Tamanho\t Tempo\t\t Comparacao\t trocas\n");
            VetorArquivo = LendoArquivo("vetores/N100-inverso.txt",&tamanho);
             mergeSort(VetorArquivo,vetor2,0,tamanho);
           printClockMergeQuick();
           // GravarArquivo(VetorArquivo, tamanho);

            ///-----------------------------------------------------------------------
            printf("Vetor ordenando inverso com 1.000\n");
            VetorArquivo = LendoArquivo("vetores/N1000-inverso.txt",&tamanho);
             mergeSort(VetorArquivo,vetor2,0,tamanho);
          printClockMergeQuick();
          //  GravarArquivo(VetorArquivo, tamanho);
            ///------------------------------------------------------------------------
            printf("Vetor ordenando inverso com 10.000\n");
            VetorArquivo = LendoArquivo("vetores/N10000-inverso.txt",&tamanho);
             mergeSort(VetorArquivo,vetor2,0,tamanho);
           printClockMergeQuick();
           // GravarArquivo(VetorArquivo, tamanho);
            ///------------------------------------------------------------------------
            printf("Vetor ordenando inverso com 50.000\n");
            VetorArquivo = LendoArquivo("vetores/N50000-inverso.txt",&tamanho);
             mergeSort(VetorArquivo,vetor2,0,tamanho);
            printClockMergeQuick();
            //GravarArquivo(VetorArquivo, tamanho);
            ///------------------------------------------------------------------------
            printf("Vetor ordenando inverso com 100.000\n");
            VetorArquivo = LendoArquivo("vetores/N100000-inverso.txt",&tamanho);
             mergeSort(VetorArquivo,vetor2,0,tamanho);
           printClockMergeQuick();
           // GravarArquivo(VetorArquivo, tamanho);
            fclose(gnuplot);
            ///-----------------------------------------------------------------------

            system("gnuplot -bg gray90 plota5.gnu");

            break;
        case 6:

            gnuplot = fopen("shell-sort-rond.dat", "w");

            printf("Ordenando vetor com 100 elementos\n");
            fprintf(gnuplot, "#RANDOMICOS\n#Tamanho\t Tempo\t\t Comparacao\t trocas\n");
            VetorArquivo = LendoArquivo("vetores/N100.txt",&tamanho);
            shellSort(VetorArquivo,tamanho);
            GravarArquivo(VetorArquivo, tamanho);
            ///-----------------------------------------------------------------------
            printf("Ordenando vetor com 1.000 elementos\n");
            VetorArquivo = LendoArquivo("vetores/N1000.txt",&tamanho);
            shellSort(VetorArquivo,tamanho);
            GravarArquivo(VetorArquivo, tamanho);
            ///------------------------------------------------------------------------
            printf("Ordenando vetor com 10.000 elementos\n");
            VetorArquivo = LendoArquivo("vetores/N10000.txt",&tamanho);
            shellSort(VetorArquivo,tamanho);
            GravarArquivo(VetorArquivo, tamanho);
            ///------------------------------------------------------------------------
            printf("Ordenando vetor de 50.000 elementos\n");
            VetorArquivo = LendoArquivo("vetores/N50000.txt",&tamanho);
            shellSort(VetorArquivo,tamanho);
            GravarArquivo(VetorArquivo, tamanho);
            ///------------------------------------------------------------------------
            printf("Ordenando vetor de 100.000 elementos \n");
            VetorArquivo = LendoArquivo("vetores/N100000.txt",&tamanho);
            shellSort(VetorArquivo,tamanho);
            GravarArquivo(VetorArquivo, tamanho);
            fclose(gnuplot);
            ///-----------------------------------------------------------------------
            printf("|================================================================|\n");

            gnuplot = fopen("shell-sort-ord.dat", "w");
            printf("Vetor ja ordenado com 100\n");
            fprintf(gnuplot, "#ORDENANDOS\n#Tamanho\t Tempo\t\t Comparacao\t trocas\n");
            VetorArquivo = LendoArquivo("vetores/N100-ordenado.txt",&tamanho);
            shellSort(VetorArquivo,tamanho);
            GravarArquivo(VetorArquivo, tamanho);

            ///-----------------------------------------------------------------------
            printf("Vetor ja ordenado com 1.000\n");
            VetorArquivo = LendoArquivo("vetores/N1000-ordenado.txt",&tamanho);
            shellSort(VetorArquivo,tamanho);
            GravarArquivo(VetorArquivo, tamanho);
            ///------------------------------------------------------------------------
            printf("Vetor ja ordenado com 10.000\n");
            VetorArquivo = LendoArquivo("vetores/N10000-ordenado.txt",&tamanho);
            shellSort(VetorArquivo,tamanho);
            GravarArquivo(VetorArquivo, tamanho);
            ///------------------------------------------------------------------------
            printf("Vetor ja ordenado com 50.000\n");
            VetorArquivo = LendoArquivo("vetores/N50000-ordenado.txt",&tamanho);
            shellSort(VetorArquivo,tamanho);
            GravarArquivo(VetorArquivo, tamanho);
            ///------------------------------------------------------------------------
            printf("Vetor ja ordenado com 100.000\n");
            VetorArquivo = LendoArquivo("vetores/N100000-ordenado.txt",&tamanho);
            shellSort(VetorArquivo,tamanho);
            GravarArquivo(VetorArquivo, tamanho);
            fclose(gnuplot);
            ///-----------------------------------------------------------------------
             printf("|================================================================|\n");

             gnuplot = fopen("shell-sort-inv.dat", "w");
            printf("Vetor ordenando inverso com 100\n");
            fprintf(gnuplot, "#ORDENANDO INVERSO\n#Tamanho\t Tempo\t\t Comparacao\t trocas\n");
            VetorArquivo = LendoArquivo("vetores/N100-inverso.txt",&tamanho);
            shellSort(VetorArquivo,tamanho);
            GravarArquivo(VetorArquivo, tamanho);

            ///-----------------------------------------------------------------------
            printf("Vetor ordenando inverso com 1.000\n");
            VetorArquivo = LendoArquivo("vetores/N1000-inverso.txt",&tamanho);
            shellSort(VetorArquivo,tamanho);
            GravarArquivo(VetorArquivo, tamanho);
            ///------------------------------------------------------------------------
            printf("Vetor ordenando inverso com 10.000\n");
            VetorArquivo = LendoArquivo("vetores/N10000-inverso.txt",&tamanho);
            shellSort(VetorArquivo,tamanho);
            GravarArquivo(VetorArquivo, tamanho);
            ///------------------------------------------------------------------------
            printf("Vetor ordenando inverso com 50.000\n");
            VetorArquivo = LendoArquivo("vetores/N50000-inverso.txt",&tamanho);
            shellSort(VetorArquivo,tamanho);
            GravarArquivo(VetorArquivo, tamanho);
            ///------------------------------------------------------------------------
            printf("Vetor ordenando inverso com 100.000\n");
            VetorArquivo = LendoArquivo("vetores/N100000-inverso.txt",&tamanho);
            shellSort(VetorArquivo,tamanho);
            GravarArquivo(VetorArquivo, tamanho);
            fclose(gnuplot);
            ///-----------------------------------------------------------------------

            system("gnuplot -bg gray90 plota6.gnu");


            break;
        case 0:

            printf("Obrigado por usar o programa\n");
            break;
        }
    }
    while(op!=0);

     system("gnuplot -bg gray90 plota7.gnu");
    return 1;
}
