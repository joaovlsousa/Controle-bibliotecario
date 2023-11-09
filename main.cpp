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

struct NoLivro {
    Livro livro;
    NoLivro *prox;
    NoLivro *ant;
};

// DESCRITOR
struct Acervo {
    NoLivro *inicio;
    NoLivro *fim;
    int tam;
};

struct NoFila {
    string nome;
    NoFila *prox;
};

struct Fila {
    NoFila *inicio;
    NoFila *fim;
    int tam;
};

struct NoHistorico {
    string nome;
    string titulo;
    int quant;
    NoHistorico *prox;
};

struct Historico {
    NoHistorico *inicio;
    int tam;
};

// FUNÇÕES UTILITÁRIAS

Acervo *criar_acervo() {
    Acervo *novo_acervo = new Acervo;
    novo_acervo->inicio = NULL;
    novo_acervo->fim = NULL;
    novo_acervo->tam = 0;

    return novo_acervo;
}

Fila *criar_fila() {
    Fila *nova_fila = new Fila;
    nova_fila->inicio = NULL;
    nova_fila->fim = NULL;
    nova_fila->tam = 0;

    return nova_fila;
}

Historico *criar_historico() {
    Historico *novo_historico = new Historico;
    novo_historico->inicio = NULL;
    novo_historico->tam = 0;

    return novo_historico;
}

string **criar_menu() {
    string **mat = new string *[7];

    const string opcoes_menu[] = {
        "Sair do sistema",
        "Cadastrar um novo livro", 
        "Listar todos os livros", 
        "Buscar um livro",
        "Editar um livro",
        "Excluir um livro",
        "Menu de atendimentos",
    };

    for (int i = 0; i < 7; i++) {
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

NoLivro *livro_existe(Acervo *estoque, string titulo) {
    NoLivro *pos = estoque->inicio;
    
    do {
        if (pos->livro.titulo == titulo) 
            return pos;

        pos = pos->prox;   
    } while (pos != NULL);

    return NULL;
}

NoLivro *buscar_endereco(Acervo *estoque, string titulo) {
    NoLivro *pos = estoque->inicio;

    while (pos->livro.titulo != titulo)
        pos = pos->prox;
    
    return pos;
}

// FUNÇÕES

void mostrar_menu() {
    string **mat = criar_menu();

    cout << endl << "---------- Sistema Bibliotecário ----------" << endl;

    for (int i = 0; i < 7; i++) {
        cout << mat[i][0] << " - " << mat[i][1] << endl; 
    }

    cout << "-------------------------------------------" << endl;
}


void anexar_livro(Acervo *estoque, Livro livro) {
    NoLivro *novo_livro = new NoLivro;
    novo_livro->livro = livro;
    novo_livro->prox = NULL;
    novo_livro->ant = NULL;

    if (estoque->tam == 0) {
        estoque->inicio = novo_livro;
        estoque->fim = novo_livro;
        estoque->tam++;
    }

    else {
        novo_livro->ant = estoque->fim;
        estoque->fim->prox = novo_livro;
        estoque->fim = novo_livro;    
        estoque->tam++;
    }
}


void cadastrar_livro(Acervo *estoque) {
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


void listar_livros(NoLivro *livro) {
    if (livro != NULL) {
        imprimir_livro(livro->livro);
        listar_livros(livro->prox);
    }
}


void buscar_livro(Acervo *estoque, string titulo) {
    NoLivro * checar_livro = livro_existe(estoque, titulo);

    if(checar_livro == NULL)
        cout << endl << "O livro não existe no estoque." << endl;
    else
        imprimir_livro(checar_livro->livro); 
}


void editar_livro(Acervo *estoque, string titulo) {
    NoLivro * checar_livro = livro_existe(estoque, titulo);

    if (checar_livro == NULL)
        cout << endl << "O livro não existe no estoque." << endl;

    else {
        NoLivro *end_livro = buscar_endereco(estoque, titulo);
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


NoLivro *excluir_livro(Acervo *estoque, string titulo) {
    NoLivro * checar_livro = livro_existe(estoque, titulo);

    if(checar_livro == NULL)
        return NULL;
    
    NoLivro *pos = buscar_endereco(estoque, titulo);

    if (estoque->tam <= 1) {
        estoque->inicio = NULL;
        estoque->fim = NULL;
        estoque->tam = 0;

        return pos;
    } 
    else if (pos->ant == NULL) {
        estoque->inicio = estoque->inicio->prox;
        estoque->inicio->ant = NULL;
        estoque->tam--;
        
        return pos;
    } 
    else if (pos->prox == NULL) {
        estoque->fim = estoque->fim->ant;
        estoque->fim->prox = NULL;
        estoque->tam--;
        
        return pos;
    } 
    else {
        pos->ant->prox = pos->prox;
        pos->prox->ant = pos->ant;
        estoque->tam--;
        
        return pos;
    } 

    return NULL;
}


void add_fila(Fila *fila, string nome) {
    NoFila *nova_pessoa = new NoFila;
    nova_pessoa->nome = nome;
    nova_pessoa->prox = NULL;

    if (fila->tam == 0) {
        fila->inicio = nova_pessoa;
        fila->fim = nova_pessoa;
        fila->tam++;
    }
    else {
        fila->fim->prox = nova_pessoa;
        fila->fim = nova_pessoa;
        fila->tam++;
    }
}


void mostrar_fila(NoFila *fila) {
    if (fila != NULL) {
        fila->prox != NULL
            ? cout << fila->nome << " - ";
            : cout << fila->nome;

        mostrar_fila(fila->prox);
    }
}


NoFila *chamar_pessoa(Fila *fila) {
    if (fila->tam == 0)
        return NULL;
    
    NoFila *pessoa = fila->inicio;
    fila->inicio = fila->inicio->prox;
    fila->tam--;

    return pessoa;
}


void add_historico(Historico *historico, string nome, string titulo, int quant) {
    NoHistorico *novo_historico = new NoHistorico;
    novo_historico->nome = nome;
    novo_historico->titulo = titulo;
    novo_historico->quant = quant;
    novo_historico->prox = historico->inicio;

    historico->inicio = novo_historico;
    historico->tam++;
}


void mostrar_historico(NoHistorico *historico) {
    if (historico != NULL) {
        cout << endl << "-------------------------------------------" << endl;
        cout << "Cliente: " << historico->nome << endl;
        cout << "Livro: " << historico->titulo << endl;
        cout << "Quantidade: " << historico->quant << endl;
        cout << "-------------------------------------------" << endl;

        mostrar_historico(historico->prox);
    }
}


bool nova_venda(Fila *fila, Historico *historico, Acervo *estoque) {
    if (fila->tam == 0 || estoque->tam == 0)
        return false;
    
    string titulo;
    int quant;

    NoFila *pessoa = chamar_pessoa(fila);

    cout << "Olá " << pessoa->nome << ", por favor informe o título do livro: ";
    cin >> titulo;
    cout << "Quanto cópias deseja comprar? ";
    cin >> quant;

    NoLivro *livro = livro_existe(estoque, titulo);

    if (livro == NULL || livro->livro.quant < quant)
        return false;
    
    livro->livro.quant -= quant;
    add_historico(historico, pessoa->nome, titulo, quant);

    return true;
}


void menu_atendimentos(Acervo *estoque, Fila *fila, Historico *historico) {
    int op;
    string nome;

    cout << endl << "Bem-vindo menu de atendimentos" << endl;

    do {
        cout << endl << "-------------------------------------------" << endl;
        cout << "1 - Mostar fila de clientes" << endl;
        cout << "2 - Adicionar uma pessoa na fila" << endl;
        cout << "3 - Mostar histórico de vendas" << endl;
        cout << "4 - Chamar o próximo cliente e iniciar uma nova venda" << endl;
        cout << "0 - Voltar ao menu principal" << endl;
        cout << "-------------------------------------------" << endl;
        cin >> op;

        cout << endl;

        switch (op)
        {
        case 1:
            if (fila->tam == 0)
                cout << "Não há pessoas na fila" << endl;
            else
                mostrar_fila(fila->inicio);

            break;

        case 2:
            cout << "Informe o nome do cliente: ";
            cin >> nome;

            add_fila(fila, nome);

            cout << endl << "Cliente adicionado a fila";

            break;

        case 3:
            if (historico->tam == 0)
                cout << "Nenhuma venda cadastrada" << endl;
            else
                mostrar_historico(historico->inicio);
            
            break;
        
        case 4:
            cout << endl;

            nova_venda(fila, historico, estoque)
                ? cout << "Venda efetuada com sucesso!"
                : cout << "Operação inválida";
            
            break;
        }
    } while (op != 0);
}


int main() {
    Acervo *estoque = criar_acervo();
    Fila *fila = criar_fila();
    Historico *historico = criar_historico();

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
            if (estoque->tam == 0)
                cout << "Estoque vazio" << endl;
            else
                listar_livros(estoque->inicio);

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
            if (estoque->tam == 0)
                cout << endl << "Estoque vazio." << endl;

            else {
                cout << endl << "Por favor, informe o titulo do livro: ";
                cin >> titulo;
                NoLivro *livro_excluido = excluir_livro(estoque, titulo);
                
                if (livro_excluido == NULL)
                    cout << "O livro não existe no estoque";
                
                else 
                    cout << endl << "Livro: " << titulo << " Excluído com sucesso. " << endl;

                delete livro_excluido;
            }

            break;
        
        case 6:
            menu_atendimentos(estoque, fila, historico);

            break;
        }

    } while (op != 0);

    cout << "Encerrando a execução do programa...";

    delete estoque;
    delete fila;
    delete historico;

    return 0;
}