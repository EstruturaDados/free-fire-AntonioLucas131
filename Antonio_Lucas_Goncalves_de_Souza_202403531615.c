#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//esse código é porque o meu terminal não estava printando uns caracteres especiais como ç e acentos.
#ifdef _WIN32
	#include <windows.h>
#endif

#define MAX 20 //tamanho maximo da lista

//STRUCT DOS COMPONENTES
typedef struct Componente {
  char nome[30];
  char tipo[20];
  int prioridade;
}Componente;

//struct da lista que vai guardar os componentes.
typedef struct Mochila {
  Componente componente[MAX]; //lista
  int capacidade; //contador pra contar quantos itens estão armazenados
}Mochila;


//função pra inicializar a Lista
void abrirMochila(Mochila *mochila) {
  mochila->capacidade = 0;
}

// FUNÇÃO PARA INSERIR UM COMPONENTE NA MOCHILA
void inserirComponente(Mochila *mochila, Componente *inserirComp) {

	if (mochila->capacidade == MAX) { //checa se a mochila está cheia
		printf("Impossivel inserir. Sua mochila não tem mais espaços para itens.\n");
		return;
	}
	// Copia o componente recebido para a posição disponível
	mochila->componente[mochila->capacidade] = *inserirComp;
	mochila->capacidade++; //aumenta a quantidade de itens total
	printf("Componente %s inserido com sucesso!\n", inserirComp->nome); //printa o item inserido

}

//FUNÇÃO PRA REMOVER UM TEM DA MOCHILA
void removerComponente(Mochila *mochila, char removerComp[]) {
	int i, pos = -1;

	// procurar pelo nome
	for (i = 0; i < mochila->capacidade; i++) {
		if (strcmp(mochila->componente[i].nome, removerComp) == 0) {
			pos = i;
			break;
		}
	}

	if (pos == -1) { //caso não encontre o item
		printf("Erro: Componente \"%s\" não encontrado.\n", removerComp);
		return;
	}

	// move os elementos pra preencher os espaços vazio
	for (i = pos; i < mochila->capacidade - 1; i++) {
		mochila->componente[i] = mochila->componente[i + 1];
	}
	//diminui o total e printa o resultado
	mochila->capacidade--;
	printf("Componente \"%s\" removido com sucesso.\n", removerComp);
}

//MOSTRA A CAPACIDADE DA MOCHILA
void mostrarcapacidade(Mochila *mochila) { // printa a capacidade
	printf("\tCAPACIDADE DA MOCHILA: %d/20\n" ,mochila->capacidade);
}

//função que printa o inventário em forma de tabela
void mostrarComponentes(Mochila *mochila) {

	printf("|=====================INVENTÁRIO======================|\n");
	printf("|-----------------------------------------------------|\n");
	printf("| %-20s | %-15s | %-10s |\n", "NOME", "TIPO", "PRIORIDADE" ); //%-20s significa que esse campo estará 20 caracteres distante da parte esquerda
	printf("|-----------------------------------------------------|\n");	//e será substituido pelo valor passado depois da virgula
	for (int i = 0; i< mochila->capacidade; i++) {
		printf("| %-20s | %-15s | %-10d |\n", //printa os itens na lista
			mochila->componente[i].nome,
			mochila->componente[i].tipo,
			mochila->componente[i].prioridade);
	}
	printf("|-----------------------------------------------------|\n");
}


//ORGANIZAR POR NOME USANDO BUBBLESORT
void bubbleSortNome(Componente mochila[], int n) {
	Componente temp;
	int comparacoes = 0;

	// Loop que  controla quantas passagens serão feitas
	for (int i = 0; i < n - 1; i++) {
		// Loop interno que percorre os pares adjacentes e troca quando necessário
		for (int j = 0; j < n - i - 1; j++) {
			comparacoes ++;

			// strcmp retorna:
			// >0 se mochila[j] > mochila[j+1] (precisa trocar)
			//  0 se igual
			// <0 se mochila[j] < mochila[j+1] (já está ordenado)
			if (strcmp(mochila[j].nome, mochila[j + 1].nome) > 0) {
				// troca os dois elementos de posição
				temp = mochila[j];
				mochila[j] = mochila[j + 1];
				mochila[j+1] = temp;
			}
		}
	}
	//printa o resultado
	printf("Sua mochila foi organizada alfabeticamente.\n");
	printf("Comparações: %d\n", comparacoes);
}


//ORDERNAR POR PRIORIDADE USANDO SELECTIONSORT
void selectionSortPrioridade(Componente mochila[], int n) {;
	Componente temp;   // Variável auxiliar usada para trocar dois elementos
	int i, j, min_idx;
	int comparacoes = 0;

	// Percorre todos os elementos do array, exceto o último
	for ( i = 0; i < n - 1; i++) {
		min_idx = i; // Assume que o menor elemento está na posição i

		// Procura o menor valor de prioridade no restante do array
		for (j = i + 1; j < n; j++) {
			comparacoes ++;

			if (mochila[j].prioridade < mochila[min_idx].prioridade) {
				min_idx = j;
			}
		}
		// Após achar o menor elemento, faz a troca se ele não estiver na posição correta
		if (min_idx!= i) {
			temp = mochila[i];
			mochila[i] = mochila[min_idx];
			mochila[min_idx] = temp;
		}
	}
	//printa o resultado
	printf("Mochila organizada por PRIORIDADE(1 maior prioridade).\n");
	printf("Comparações: %d\n", comparacoes);

}


//ORGANIZAR POR TIPO
void insertionSortTipo(Componente mochila[], int n){;
	Componente key;  // Guarda temporariamente o item que está sendo inserido
	int comparacoes = 0; //guarda as comparações

	// for Começando do segundo elemento, pois o primeiro já é considerado ordenado
	for (int i = 1; i < n; ++i) {
		key = mochila[i]; // Elemento atual que queremos inserir na parte já ordenada
		int j = i - 1;  // Índice do último elemento da parte ordenada

		// Move os elementos maiores que 'key' uma posição à direita
		// strcmp() > 0 significa que mochila[j].tipo vem *depois* do key.tipo no alfabeto
		while (j >= 0 && strcmp(mochila[j].tipo, key.tipo) > 0) {
			mochila[j + 1] = mochila[j]; // Move elemento para a direita
			j = j - 1;  // Anda para trás no array
			comparacoes++;
		}
		// Insere o elemento key na posição correta dentro da parte ordenada
		mochila[j + 1] = key;
	}
	//printa o resultado
	printf("Mochila organizada no TIPO(alfabeticamente)\n");
	printf("Comparações: %d\n", comparacoes);

}

// BUSCAR ITEM ESPECÍFICO
void buscaBinariaPorNome(Componente mochila[], int n,  Componente *buscarComp) {
	int inicio = 0;
	int fim = n - 1;
	int meio;
	int comparacoes = 0; //guarda as comparações

	while (inicio <= fim) {
		meio = (inicio + fim) / 2;
		comparacoes++; // aumenta a variavel de comparações realizadas

		// Compara o nome do meio com o nome buscado
		int comparacao = strcmp(mochila[meio].nome, buscarComp->nome);

		if (comparacao == 0) {
			printf("INFORMAÇÕES DO ITEM BUSCADO (%s)\n", buscarComp->nome);
			printf("|-----------------------------------------------------|\n");
			printf("| %-20s | %-15s | %-10s |\n", "NOME", "TIPO", "PRIORIDADE" );
			printf("|-----------------------------------------------------|\n");
			printf("| %-20s | %-15s | %-10d |\n",
					mochila[meio].nome,
					mochila[meio].tipo,
					mochila[meio].prioridade);
			printf("|-----------------------------------------------------|\n\n");
			return;
		}


		// Se o nome do meio vem depois do buscado,
		// o item procurado só pode estar à esquerda.

		if (comparacao > 0) {
			fim = meio - 1;
		}
		else {
			inicio = meio + 1; // ignora da metade até o inicio
		}
	}
	// Se saiu do while, a palavra não foi achada.
	printf("Item \"%s\" não encontrado na mochila.\n", buscarComp->nome);
	printf("Comparações: %d\n", comparacoes); //printa a quantidade de comparações realizadas

}

//função pra medir o tempo de execução, recebe o vetor, seu tamanho, o algoritimo que vai ser aplicado e o seu nome.
void medirTempo(Componente vetor[], int n, void (*algoritmo)(Componente[], int), const char *nomeAlgoritmo) {
	clock_t inicio, fim; //variavel do começo e fim da contagem
	double tempo_gasto; //tempo total gasto

	inicio = clock(); // começo da contagem

	// Passamos o vetor e o tamanho para o algoritmo
	algoritmo(vetor, n);

	fim = clock(); // término da contagem

	tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC; //calculo do tempo gasto entre o começo e o fim
	printf("(%s) Tempo de execução: %f segundos\n", nomeAlgoritmo, tempo_gasto);// printa o tempo de execução
}

int main(void) {
	//esse código é porque o meu terminal não estava printando uns caracteres especiais como ç e acentos.
#ifdef _WIN32
	SetConsoleOutputCP(CP_UTF8);  // Muda a Code Page de saída do Windows para UTF-8
	SetConsoleCP(CP_UTF8);  // Muda a Code Page de entrada do Windows para UTF-8
#endif
//----------------------------------------------------------------------------------------
	int escolha; //variavel d escolha
	// int ordenadoPorNome= 0; //variavel permitir a busca binaria
	int ordenado=0; //variavel do estatus de ordenação
	char entrada[32];
	//inicializa o vetor
	Mochila mochila;
	abrirMochila(&mochila);

	Componente loot; //declaração do componente

do {
	//essas duas fuções são pra mostrar o inventário e sua capacidade total a todo momento
	mostrarComponentes(&mochila);
	mostrarcapacidade(&mochila);


	//switch case pra checar o status de ordenação
	//quando as funções de ordenação são chamadas, elas mudam o valor da variavel ordenado pra o seu tipo de ordenação
	//ex: função bubblesort foi chamada, variavel ordenado = 1. insertion chamada, ordenado = 2, etc.
	switch (ordenado) {
		case 1:
			printf("\t|Status de ordenação: NOME|\n");
			break;
		case 2:
			printf("\t|Status de ordenação: TIPO|\n");
			break;
		case 3:
			printf("\t|Status de ordenação: PRIORIDADE|\n");
			break;
		default:
			printf("\t|Status de ordenação: Não ordenado|\n");
			break;
	}

	//menu de opções
	printf("\t|=====MENU PRINCIPAL=====|\n");
	printf("\tESCOLHA UMA DAS OPÇÕES ABAIXO\n");
	printf("\t1 - Inserir Componente.\n");
	printf("\t2 - Remover Componente.\n");
	printf("\t3 - Mostrar Mochila.\n");
	printf("\t4 - Organizar mochila por NOME(bubbleSort).\n");
	printf("\t5 - Organizar mochila por TIPO(insertionSort).\n");
	printf("\t6 - Organizar mochila por PRIORIDADE(selectionSort).\n");
	printf("\t7 - Buscar item específico(buscaBinária).\n");
	printf("\t0 - Ativar torre de fuga(sair).\n");
	printf("|-----------------------------------------------------|\n");
	printf("\tSua escolha: ");

	//tratamento de erros pro input por causa do uso de scanf e fgets juntos
	if (!fgets(entrada, sizeof(entrada), stdin)) {
		printf("Erro de leitura!\n");
		continue;
	}
	if (sscanf(entrada, "%d", &escolha) != 1) {
		printf("Entrada inválida! Digite apenas números.\n");
		continue;
	}


	switch (escolha) {

		case 1: //caso 1, inserir item
			if (mochila.capacidade == MAX) { //checa se a mochila está cheia
				printf("Impossivel inserir. Sua mochila não tem mais espaços para itens.\n");
				break;
			}
			printf("|=====INSERIR NOVO COMPONENTE=====|\n");
			printf("Digite o nome do componente: \n"); //input do nome
			fgets(loot.nome, sizeof(loot.nome), stdin); //pega o input pelo fgets
			loot.nome[strcspn(loot.nome, "\n")] = '\0';// ignora espaçços

			printf("Digite o tipo do componente: \n"); //input do tipo
			fgets(loot.tipo, sizeof(loot.tipo), stdin); //pega o input pelo fgets
			loot.tipo[strcspn(loot.tipo, "\n")] = '\0'; // ignora espaços

			printf("Digite a prioridade do componente: \n"); //input da prioridade
			fgets(entrada, sizeof(entrada), stdin);
			sscanf(entrada, "%d", &loot.prioridade);

			// scanf("%d", &loot.prioridade);
			//chama a função
			inserirComponente(&mochila, &loot);
			ordenado = 0; //sinaliza que não está ordenada
			break;

		case 2: //case 2 PRA RETIRAR UM ITEM
			if (mochila.capacidade  == 0) { //checa se a mochila está vazia
				printf("    IMPOSSÍVEL RETIRAR ITEM, SUA MOCHILA ESTÁ VAZIA\n");
				break; //se estiver vazia, volta pro menu
			}
			//caso contrario, pega o input
			printf("|===========REMOVER COMPONENTE===========|\n");
			printf("Digite o nome do componente a ser removido: \n");
			fgets(loot.nome, sizeof(loot.nome), stdin); //pega o input pelo fgets
			loot.nome[strcspn(loot.nome, "\n")] = '\0'; //ignora espaços
			//chama a função de remover componentes
			removerComponente(&mochila, loot.nome);
			ordenado = 0; //sinaliza que não está ordenado
			break;

		case 3: //caso 3 pra mostrar inventário, apesar de já aparecer sempre.
			mostrarComponentes(&mochila);
			break;

		case 4: //caso 4 organizar item por nome
			if (mochila.capacidade <= 1) {// checa se tem no minimo 1 ou mais itens na mochila
				printf("impossível organizar por nome, sua mochila tem apenas 1 ou nenhum item.\n");
				break;
			}
			//caso contrario, chama função bubblesort e ordena por nome
			medirTempo(mochila.componente, mochila.capacidade, bubbleSortNome, "bubbleSort");
			ordenado = 1; // 1 sinaliza que está ordenado por nome.
			break;

		case 5: // caso 5 pra ordernar por tipo.
			if (mochila.capacidade <= 1) { // checa se tem no minimo 1 ou mais itens na mochila
				printf("impossível organizar por tipo, sua mochila tem apenas 1 ou nenhum item.\n");
				break;
			}// se tiver mais de 1 item, chama a função passando o vetor, seu tamanho, a função de ordenação e seu nome.
			medirTempo(mochila.componente, mochila.capacidade, insertionSortTipo, "insertionSort");
			ordenado = 2; //2 sinaliza que está ordenada por tipo
			break;

		case 6: //caso 6, organiza por prioridade
			if (mochila.capacidade <= 1) { // checa se tem no minimo 1 ou mais itens na mochila
				printf("impossível organizar por Prioridade, sua mochila tem apenas 1 ou nenhum item.\n");
				break;
			}//caso contrairo, chama a função
			medirTempo(mochila.componente, mochila.capacidade, selectionSortPrioridade, "selectionSort");
			ordenado = 3; //sinaliza que está ordenada por prioridade
			break;

		case 7:// caso 7 para busca binária de itens
			if (ordenado != 1) { //checa se a lista está ordenada por nome
				printf("A mochila não está ordenada por nome!\n");
				printf("Use a opção (4) para ordenar com bubble sort.\n");
				break;
			}//caso contrario pede o input do nome do item a ser buscado
			printf("|===========BUSCA DE COMPONENTE===========|\n");
			printf("Digite o nome do componente a ser buscado:\n");
			fgets(loot.nome, sizeof(loot.nome), stdin); //fgets pra pegar o input
			loot.nome[strcspn(loot.nome, "\n")] = '\0'; // ignora espaçoes do input
			//chama a função de busca passando o vetor, o tamanho do vetor e o Componente a ser buscado.
			buscaBinariaPorNome(mochila.componente, mochila.capacidade, &loot);
			break;

		case 0: //caso 0, sai do programa
			printf("Você saiu do programa.\n");
			break;

		default: // caso não digite nenhuma opção válida
			printf("Digite uma opção válida. (1, 2, 3, 4, 5, 6, 7 ou 0)\n");
	}
}while (escolha != 0);


	return 0;
}