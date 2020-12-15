#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct Dependente {
    char nome[20];
    int idade;
}Dependente;

typedef struct Associado {
    int id;
    char nome[20];
    int idade;
    Dependente dep[3];
    int qtdDep;
    bool natacao;
    bool futsal;
    bool tenis;
}Associado;

//assinatura das funções
void menu();
void cadastrodependentes(Associado *associado, int quantidade);
void listaassociados(Associado *associado, int quantidade);
void listamodalidades(Associado *associado, int quantidade);
void pesquisanome(Associado *associado,int quantidade);
void relatorio(Associado *associado, int quantidade);
int leiaidade();
char verificacaracter();
bool leiaesporte();
void contaesporte(Associado associado);
void listadep(Associado associado);
void fazounao(Associado associado);
int verificaesportes(Associado associado);
int mensalidade(Associado associado);
int totaldependentes(Associado *associado, int quantidade);
int mensalidadetotal(Associado *associado, int quantidade);
int mensalidadealta(Associado *associado, int quantidade);
void maisaulas(Associado *associado, int quantidade);

int futsal=0,natacao=0,tenis=0;

int main (){
    Associado associado[100];
    int escolha,quantidade=0,j;
    //inicializando a variável,quantidade de dependentes, em todas as posições do vetor associado,atribuindo o valor 0.
    for(j=0;j<30;j++){
        associado[j].qtdDep=0;
    }

    do{
        menu();
        scanf("%d",&escolha);
        switch (escolha){
            //caso para cadastro de nome
            case 1:
                associado[quantidade].id=1+quantidade;
                printf("qual o nome do associado: \n");
                scanf(" %[^\n]s",associado[quantidade].nome);
                printf("Digite a idade do associado: \n");
                associado[quantidade].idade= leiaidade();
                printf("Faz futsal: S/N\n");
                associado[quantidade].futsal=leiaesporte();
                printf("Faz natacao: S/N\n");
                associado[quantidade].natacao=leiaesporte();
                printf("Faz tenis: S/N\n");
                associado[quantidade].tenis=leiaesporte();
                contaesporte(associado[quantidade]);
                //aumentando a quantidade de posições
                quantidade++;
                break;
            case 2:
                //caso para cadastrar os dependentes
                cadastrodependentes(associado,quantidade);
                break;
            case 3:
                // caso para listar os associados
                listaassociados(associado,quantidade);
                break;
            case 4:
                //caso para listar os praticantes de cada modalidade esportiva
                listamodalidades(associado,quantidade);
                break;
            case 5:
                // caso para pesquisar um associado
                pesquisanome(associado,quantidade);
                break;
            case 6:
                //caso para gerar um relatório sobre os dados cadastrados
                relatorio(associado,quantidade);
                break;
            case 7:
                printf("Ate mais, FIM DO PROGRAMA\n");
                break;
            
            default:
                printf("opcao invalida\n");
                break;
        }
    }while(escolha!= 7);

    return 0;
}

//imprime o menu na tela
void menu (){
    printf("1 - Cadastrar associado\n");
    printf("2 - Cadastrar dependente\n");
    printf("3 - Listar associados\n");
    printf("4 - Listar associados por modalidade\n");
    printf("5 - Pesquisar associados\n");
    printf("6 - Gerar relatorio de associados\n");
    printf("7 - Finalizar programa\n");
}
//cadastrar dependentes
void cadastrodependentes(Associado *associado, int quantidade){
    int id,passou,j;
    printf("Voce pode encontra o ID na opcao 3, caso nao saiba\n");
    printf("Qual o ID do associado: \n");
    scanf("%d",&id);
    passou=0;
    for(j=0;j<quantidade;j++){
        if(id==associado[j].id){
            if(associado[j].qtdDep<=2){
                printf("qual o nome do dependente: \n");
                scanf(" %[^\n]s",associado[j].dep[associado[j].qtdDep].nome);
                printf("qual a idade do dependente: \n");
                associado[j].dep[associado[j].qtdDep].idade=leiaidade();
                listadep(associado[j]);
                associado[j].qtdDep++;
            }else{
                printf("numero maximo de dependentes cadastrados\n");
            }
            //esta variável serve como variável auxiliar, para que a mensagem de erro seja apresentada.
            passou++;
        }
    }                    
    if(passou==0){
        printf("id nao cadastrado\n");
    }
}
//lista todos os associados
void listaassociados(Associado *associado,int i){
    int j;
    for(j=0;j<i; j++){
        printf("%d - %s - %d - %d",associado[j].id,associado[j].nome,associado[j].idade,associado[j].qtdDep);
        fazounao(associado[j]);
        printf("\n");
    }
    printf("\n");
}
//lista os praticantes das modalidades esportivas
void listamodalidades(Associado *associado, int quantidade){
    int escolha,j,passou;
    printf("qual modalidade gostaria de visualizar: \n");
    printf("1 - Futsal \n");
    printf("2 - Natacao \n");
    printf("3 - Tenis \n");
    scanf("%d",&escolha);
    //esta variável serve como variável auxiliar, para que a mensagem de erro seja apresentada.
    passou=0;
    switch(escolha){
        case 1:
            for(j=0;j<quantidade; j++){
                if(associado[j].futsal){
                    printf("%d - %s\n\n",associado[j].id,associado[j].nome);
                    passou++;
                }
            }
            if(passou==0){
                printf("Nenhum associado pratica este esporte\n\n");
            }
            break;
        case 2:
            for(j=0;j<quantidade; j++){
                if(associado[j].natacao){
                    printf("%d - %s\n\n",associado[j].id,associado[j].nome);
                    passou++;
                }
            }
            if(passou==0){
                printf("Nenhum associado pratica este esporte\n\n");
            }
            break;
        case 3:
            for(j=0;j<quantidade; j++){
                if(associado[j].tenis){
                    printf("%d - %s\n\n",associado[j].id,associado[j].nome);
                    passou++;
                }
            }
            if(passou==0){
                printf("Nenhum associado pratica este esporte\n\n");
            }
        break;
    }
}
//pesquisa o nome do associado e apresenta suas informações
void pesquisanome(Associado *associado, int quantidade){
    int passou,tamanho,j;
    char pesquisa_nome[20];
    passou=0;
    printf("Qual o nome que deseja buscar: \n");
    scanf(" %[^\n]s",pesquisa_nome);
    //função srtlen utilizada para que seja possível buscar um nome, mesmo que esteja incompleto.
    tamanho= strlen(pesquisa_nome);
    for(j=0;j<quantidade;j++){
        if(strncmp(pesquisa_nome,associado[j].nome,tamanho)== 0){
            printf("%d - %s - %d ",associado[j].id,associado[j].nome,associado[j].idade);
            printf("- %d - %d - R$%d\n\n",associado[j].qtdDep,verificaesportes(associado[j]),mensalidade(associado[j]));
            //esta variável serve como variável auxiliar, para que a mensagem de erro seja apresentada.
            passou++;
        }
    }
    if(passou == 0){
        printf("nome nao encontrado\n\n");
    }
}
//gera relatório sobre os dados cadastrados
void relatorio(Associado *associado,int quantidade){
    printf("A atual quantidade de dependentes e: %d\n",quantidade);
    printf("Total de dependentes cadastrados: %d\n",totaldependentes(associado,quantidade));
    printf("Numero total de associados que praticam futsal: %d\n",futsal);
    printf("Numero total de associados que praticam natacao: %d\n",natacao);
    printf("Numero total de associados que praticam tenis: %d\n",tenis);
    printf("Valor total de todas as mensalidades: R$%d\n",mensalidadetotal(associado,quantidade));
    printf("Valor medio das mensalidades dos associados: R$%.2f \n",(float) mensalidadetotal(associado,quantidade)/quantidade);
    printf("Valor mais alto pago por um associado: R$%d\n",mensalidadealta(associado,quantidade));
    maisaulas(associado,quantidade);
}
// lê a idade e verifica se é válida
int leiaidade(){
    int idade;
    scanf("%d",&idade);
    while(idade<0){
        printf("idade invalida,tente novamente \n");
        printf("digite a idade: \n");
        scanf("%d",&idade);
    }
    return idade;
}
//lê e verifica se o caracter digitado pelo usúario é válido
char verificacaracter(){
    char usuario;
    scanf(" %c",&usuario);
    while(usuario!='s' && usuario!='n' && usuario!='S' && usuario != 'N'){
        printf("invalido,tente novamente: \n");
        scanf(" %c",&usuario);
    }
    return usuario;
}
//verifica se o associado pratica algum esporte
bool leiaesporte(){
    int faz_esporte;
    faz_esporte = verificacaracter();
    if(faz_esporte=='s' || faz_esporte == 'S'){
        return true;
    }else{
        return false;
    }
}
// conta a quantidade de praticantes de cada esporte
void contaesporte(Associado associado){
    if(associado.futsal){
        futsal++;
    }
    if(associado.natacao){
        natacao++;
    }
    if(associado.tenis){
        tenis++;
    }
}
//lista todos os dependentes cadastrados de um determinado associado
void listadep( Associado associado){
    int j;
    for(j=0; j<=associado.qtdDep; j++){
        printf("dependentes cadastrados: %s - %d\n",associado.dep[j].nome,associado.dep[j].idade);
    }
}
//imprime se o associado faz ou não algum esporte
void fazounao (Associado associado){
    if(associado.futsal){
        printf(" - faz futsal");
    }else{
        printf(" - nao faz futsal");
    }
    if(associado.natacao){
        printf(" - faz natacao");
    }else{
        printf(" - nao faz natacao");
    }
    if(associado.tenis){
        printf(" - faz tenis");
    }else{
        printf(" - nao faz tenis");
    }
}
// verifica a quantidade de esportes praticados pelo associado
int verificaesportes(Associado associado){
    int esportes = 0;
    if(associado.futsal){
        esportes++;
    }
    if(associado.natacao){
        esportes++;
    }
    if(associado.tenis){
        esportes++;
    }
    return esportes;
}
// cálculo da mensalidade
int mensalidade(Associado associado){
    int mensalidade=0,esportes=0;
    esportes = verificaesportes(associado);
    mensalidade = 100+associado.qtdDep*50+esportes*30;
    return mensalidade;
}

//calcula o total de dependentes cadastrados
int totaldependentes(Associado *associado,int i){
    int totaldep=0,j;
    for(j=0;j<i;j++){
        totaldep += associado[j].qtdDep;
    }
    return totaldep;
}
//calcula a mensalidade total,ou seja, a soma da mensalidade de todos os associados
int mensalidadetotal( Associado *associado,int i){
    int mensalidad=0,j;
    for(j=0;j<i;j++){
        mensalidad+= mensalidade(associado[j]);
    }
    return mensalidad;
}
// calcula qual é a mensalidade mais alta
int mensalidadealta(Associado *associado, int i){
    int alta=0,j,maior=0;
    for(j=0; j<i;j++){
        alta = mensalidade(associado[j]);
        if(alta>maior){
            maior=alta;
        }
    }
    return maior;
}
//função para verificar quais associados praticam mais esportes
void maisaulas(Associado *associado,int i){
    int j,esportes,maior=0;
    printf("Nome do(s) associado(s) que fazem mais aulas:\n");
    // verifica qual o maior numero de esportes, que um único associado pratica.
    for(j=0;j<i;j++){
        esportes = verificaesportes(associado[j]);
        if(esportes>maior){
            maior=esportes;
        }
    }
    // verifica quais associados praticam o maior numero de esportes e imprime o nome deles.
    for(j=0;j<i;j++){
        if(verificaesportes(associado[j])==maior){
            printf("%s\n",associado[j].nome);
        }
    }
}