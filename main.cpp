#include <iostream>
#include <string>

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
    Acervo *ant;
};

// FUNÇÕES UTILITÁRIAS

Acervo * criar_Acervo() {
    return NULL;
}

string ** criar_menu() {
    string **mat = new string *[6];

    string opcoes_menu[] = {
        "Sair do sistema",
        "Cadastrar um novo livro", 
        "Listar todos os livros", 
        "Buscar um livro",
        "Editar um livro",
        "Excluir um livro",
    };

    for (int i = 0; i < 6; i++) {
        mat[i] = new string[2];
        mat[i][0] = to_string(i);
        mat[i][1] = opcoes_menu[i];
    }

    return mat;
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

    Livro livro_inexistente;
    livro_inexistente.quant = -1;

    return livro_inexistente;
}

Acervo * buscar_endereco(Acervo *estoque, string titulo) {
    Acervo *pos = estoque;

    while (pos->livro.titulo != titulo)
        pos = pos->prox;
    
    return pos;
}

// FUNÇÕES

void mostrar_menu() {
    string **mat = criar_menu();

    cout << endl << "---------- Sistema Bibliotecário ----------" << endl;

    for (int i = 0; i < 6; i++) {
        cout << mat[i][0] << " - " << mat[i][1] << endl; 
    }

    cout << "-------------------------------------------" << endl;
}


void anexar_livro(Acervo *&estoque, Livro livro) {
    Acervo *novo_livro = new Acervo;
    novo_livro->livro = livro;
    novo_livro->prox = NULL;
    novo_livro->ant = NULL;

    if (estoque == NULL) 
        estoque = novo_livro;

    else {
        Acervo *pos = estoque;

        while(pos->prox != NULL) 
            pos = pos->prox;

        pos->prox = novo_livro;
        novo_livro->ant = pos;    
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
        cout << "Nenhum Livro cadastrado." << endl;

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


void editar_livro(Acervo *estoque, string titulo) {
    Livro checar_livro = livro_existe(estoque, titulo);

    if (checar_livro.quant < 0)
        cout << endl << "O livro não existe no estoque." << endl;

    else {
        Acervo *end_livro = buscar_endereco(estoque, titulo);
        char op;

        cout << "Editar livro" << endl;

        cout << "Quer editar o titulo? (s/n): ";
        cin >> op;

        if (op == 's') {
            cout<<"Informe um novo titulo: ";
            cin >> end_livro->livro.titulo;
        }

        cout << "Quer editar o autor? (s/n): ";
        cin >> op;

        if (op == 's') {
            cout << "Informe um novo autor: ";
            cin >> end_livro->livro.autor;
        }

        cout << "Quer editar o preço? (s/n): ";
        cin >> op;

        if (op == 's') {
            cout << "Informe um novo preço: ";
            cin >> end_livro->livro.preco;
        }

        cout << "Quer editar a quantidade? (s/n): ";
        cin >> op;

        if (op == 's') {
            cout << "Informe uma nova quantidade de livros disponíveis: ";
            cin >> end_livro->livro.quant;
        }

        cout << endl << "Livro editado com sucesso." << endl;
    }
}


Acervo *excluir_livro(Acervo *&estoque, string titulo) {
    Livro checar_livro = livro_existe(estoque, titulo);

    if(checar_livro.quant < 0)
        return NULL;
        
    else {
        Acervo *pos = buscar_endereco(estoque, titulo);

        if (pos->ant == NULL && pos->prox == NULL) {
            estoque = NULL;

            return pos;
        } 
        else if (pos->ant == NULL) {
            estoque = estoque->prox;
            estoque->ant = NULL;
            
            return pos;
        } 
        else if (pos->prox == NULL) {
            pos->ant->prox = NULL;
            
            return pos;
        } 
        else {
            pos->ant->prox = pos->prox;
            pos->prox->ant = pos->ant;
            
            return pos;
        } 
    }

    return NULL;
}


int main() {
    Acervo *estoque = criar_Acervo();
    int op;
    string titulo;

    cout << endl << "Bem-vindo ao controle bibliotecário" << endl;

    do {
        mostrar_menu();
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
            editar_livro(estoque, titulo);
        
            break;

        case 5:
            if (estoque == NULL)
                cout << endl << "Estoque vazio." << endl;

            else {
                cout << endl << "Por favor, informe o titulo do livro: ";
                cin >> titulo;
                Acervo *livro_excluido = excluir_livro(estoque, titulo);
                
                if (livro_excluido == NULL)
                    cout << "O livro não existe no estoque";
                
                else {
                    cout << endl << "Livro: " << titulo << " Exclído com sucesso. " << endl;
                    delete livro_excluido;
                }
            }

            break;
        }

    } while (op != 0);

    cout << "Encerrando a execução do programa...";

    delete estoque;  

    return 0;
}