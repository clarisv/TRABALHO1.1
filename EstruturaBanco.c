/*O programa a ser construído deve ler dados de cada aluno, identificando o nome e as notas para, a seguir, 
determinar a nota média e a situação final do aluno (APROVADO, caso a nota média seja maior ou igual a 7.0 ou REPROVADO, 
caso a nota média seja menor do que 7.0). Por fim, deve ser gerado um arquivo chamado SituacaoFinal.cvs 
em que cada linha deverá ter o nome do aluno, a nota média com duas casas decimais e a situação do aluno. 
Por exemplo, para a aluna Maria Oliveira, cujas notas foram 9.0 e 9.3, deverá ser gravado no arquivo de saída*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_ALUNOS 100

typedef struct{
    char nomeAluno[50];
    float Nota1;
    float Nota2;
    char telefone[20];
    char curso [25];
    float mediaAluno;
    char situacadoAluno[20];
}infoAluno;

/*determinar a nota média*/ //-> para isso a seguir utilizaremos uma funcao
void calcularMedia(infoAluno *aluno) {
    aluno->mediaAluno = (aluno->Nota1 + aluno->Nota2) / 2.0;
}
/*situação final do aluno (APROVADO, caso a nota média seja maior ou igual a 7.0 ou REPROVADO caso a nota média seja menor do que 7.0)*/
void situacaoDoAluno(infoAluno *aluno){
    if(aluno->mediaAluno >= 7.0){
        strcpy(aluno ->situacadoAluno, "APROVADO");
    } else {
        strcpy(aluno ->situacadoAluno,"REPROVADO");
    }
}

/*O programa a ser construído deve ler dados de cada aluno, identificando o nome e as notas para*/
void lerDadosDoAluno(infoAluno alunos[], int *numAlunos){
    FILE *arquivo;
    char linhaLida[100];
    int i = 0; 
    arquivo = fopen("DadosEntrada.csv", "r");
    if(arquivo == NULL){
        printf("Erro ao abrir o arquivo!\n");
        exit(1);
    }
    
    if (fgets(linhaLida, sizeof(linhaLida), arquivo) == NULL) {
        printf("\nErro ao ler a linha de cabeçalho ou o arquivo está vazio.");
        fclose(arquivo);
        return;
        }
    while(fgets(linhaLida, sizeof(linhaLida), arquivo)){
        sscanf(linhaLida,"%[^,],%[^,], %[^,], %f, %f ", alunos[i].nomeAluno, alunos[i].telefone, alunos[i].curso, &alunos[i].Nota1, &alunos[i].Nota2);
        calcularMedia(&alunos[i]);
        situacaoDoAluno(&alunos[i]);
        i++;
    }

    *numAlunos = i;
    fclose(arquivo);

}

/* deve ser gerado um arquivo chamado SituacaoFinal.csv em que cada linha deverá ter o nome do aluno, 
a nota média com duas casas decimais e a situação do aluno.
Por exemplo,Maria Oliveira, 9.15, APROVADO*/

void arquivoGerado(infoAluno alunos[], int numAlunos){
    FILE *arquivo;
    arquivo = fopen("SituacaoFinal.csv", "w");
    if(arquivo == NULL){
        printf("Erro ao abrir o arquivo!\n");
        exit(1);
    }
    fprintf(arquivo,"Nome, Media, Situacao\n");
    for(int i = 0; i<numAlunos; i++){
        fprintf(arquivo,"%s, %.2f, %s\n", alunos[i].nomeAluno, alunos[i].mediaAluno, alunos[i].situacadoAluno);
    }
    fclose(arquivo);
}

int main(){
    infoAluno alunos[MAX_ALUNOS];
    int numeAlunos = 0;

    lerDadosDoAluno(alunos, &numeAlunos);
    arquivoGerado(alunos, numeAlunos);

    printf("Arquivo 'SituacaoFinal.csv' foi gerada com suceso.\n");
}