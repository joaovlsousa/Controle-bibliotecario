#include <iostream>

using namespace std;

// ESTRUTURAS

struct Livro {
    string titulo;
    string autor;
    float preco;
    int quant;
};

struct Acervo {
    Livro livro;
    Acervo *prox;
};

//  FUNÇÕES UTILITÁRIAS

Acervo * criar_Acervo() {
    return NULL;
}

void imprimir_livro(Livro livro) {
    cout << endl << "-------------------------------------------" << endl;
    cout << "Título: " << livro.titulo << endl;
    cout << "Autor: " << livro.autor << endl;
    cout << "Preço: " << livro.preco << endl;
    cout << "Disponíveis: " << livro.quant << endl;
    cout << "-------------------------------------------" << endl;
}

Livro livro_existe(Acervo *estoque, string titulo) {
    Acervo *pos = estoque;
    
    do {
        if (pos->livro.titulo == titulo) 
            return pos->livro;
        else 
            pos = pos->prox; 
        
    } while (pos != NULL);
    
    Livro livro_inexistente = { .quant = -1 };

    return livro_inexistente;
}

//FUNÇÕES

void menu() {
    cout << endl << "---------- Sistema Bibliotecário ----------" << endl;
    cout << "1 - Cadastrar um novo livro" << endl;
    cout << "2 - Listar todos os livros" << endl;
    cout << "3 - Buscar um livro" << endl;
    cout << "4 - Editar um livro" << endl;
    cout << "5 - Excluir um livro" << endl;
    cout << "0 - Sair do sistema" << endl;
    cout << "-------------------------------------------" << endl;
}


void anexar_livro(Acervo *&estoque, Livro livro) {
    Acervo *novo_livro = new Acervo;
    novo_livro->livro = livro;
    novo_livro->prox = NULL;
    
    if (estoque == NULL) 
        estoque = novo_livro;

    else {
        Acervo *pos = estoque;

        while(pos->prox != NULL) 
            pos = pos->prox;

        pos->prox = novo_livro;     
    }
}


void cadastrar_livro(Acervo *&estoque) {
    Livro novo_livro;

    cout << "Cadastrar livro" << endl;

    cout<<"Informe o titulo do livro: ";
    cin >> novo_livro.titulo;

    cout << "Informe o nome do autor: ";
    cin >> novo_livro.autor;

    cout << "Informe o preço do livro: ";
    cin >> novo_livro.preco;

    cout << "Informe a quantidade de livros disponíveis: ";
    cin >> novo_livro.quant;

    anexar_livro(estoque, novo_livro);

    cout << endl << "Livro cadastrado com sucesso." << endl;

}


void listar_livros(Acervo *estoque) {
    if (estoque == NULL)
        cout << endl << "Nenhum Livro cadastrado." << endl;

    else {
        Acervo *pos = estoque;

        while (pos != NULL) {
            imprimir_livro(pos->livro);

            pos = pos -> prox;
        }    
    }
}


void buscar_livro(Acervo *estoque, string titulo) {
    Livro checar_Livro = livro_existe(estoque, titulo);

    if(checar_Livro.quant < 0)
        cout << endl << "O livro não existe no estoque." << endl;

    else
        imprimir_livro(checar_Livro); 
}

void editar_livro() {

}

void excluir_livro() {

}


int main() {
    Acervo *estoque = criar_Acervo();
    int op;
    string titulo;

    cout << endl << "Bem-vindo ao controle bibliotecário" << endl;

    do {
        menu();
        cin >> op;

        switch (op)
        {
        case 1:
            cout << endl;
            cadastrar_livro(estoque);
            break;

        case 2:
            cout << endl;
            listar_livros(estoque);
            break;

        case 3:
            cout << endl << "Por favor, informe o titulo do livro: ";
            cin >> titulo;
            buscar_livro(estoque, titulo);
            
            break;

        case 4:
            cout << endl << "Por favor, informe o titulo do livro: ";
            cin >> titulo;
        
            break;

        case 5:
            cout << endl << "Por favor, informe o titulo do livro: ";
            cin >> titulo;

            break;
        }

    } while (op != 0);

    cout << "Encerrando a execução do programa...";    

    return 0;
}