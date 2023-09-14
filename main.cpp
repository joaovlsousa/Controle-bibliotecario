#include <iostream>
#include <vector>

using namespace std;

struct Livro
{
    string titulo;
    string autor;
    float preco;
    int quant;
};

// funções utilitárias

void mostrar_livro(Livro livro)
{
    cout << endl << "-------------------------------------------" << endl;
    cout << "Título: " << livro.titulo << endl;
    cout << "Autor: " << livro.autor << endl;
    cout << "Preço: " << livro.preco << endl;
    cout << "Disponíveis: " << livro.quant << endl;
    cout << "-------------------------------------------" << endl;
}

int livro_existe(vector<Livro> &acervo, string titulo)
{
    int tam = acervo.size();
    int index = -1;

    for(int i = 0; i < tam; i++)
    {
        if(acervo[i].titulo == titulo)
        {
            index = i;
        }
    }

    return index;
}

// funções 

void menu()
{
    cout << endl << "---------- Sistema Bibliotecário ----------" << endl;
    cout << "1 - Cadastrar um novo livro" << endl;
    cout << "2 - Listar todos os livros" << endl;
    cout << "3 - Buscar um livro" << endl;
    cout << "4 - Editar um livro" << endl;
    cout << "5 - Excluir um livro" << endl;
    cout << "0 - Sair do sistema" << endl;
    cout << "-------------------------------------------" << endl;
}

void cadastrar_livro(vector<Livro> &acervo)
{
    Livro novo_livro;

    cout << endl << "Cadastrar Livro" << endl;

    cout << "Informe o título do livro: ";
    cin >> novo_livro.titulo;
    
    cout << "Informe o autor do livro: ";
    cin >> novo_livro.autor;
    
    cout << "Informe o preço do livro: ";
    cin >> novo_livro.preco;
    
    cout << "Informe a quantidade de livros disponíveis: ";
    cin >> novo_livro.quant;

    acervo.push_back(novo_livro);

    cout << endl << "Livro cadastrado com sucesso!" << endl;
}

void listar_livros(vector<Livro> &acervo)
{
    int tam = acervo.size();

    for(int i = 0; i < tam; i++)
    {
        mostrar_livro(acervo[i]);
    }
}

void buscar_livro(vector<Livro> &acervo, string titulo)
{
    int index = livro_existe(acervo, titulo);

    if(index < 0)
    {
        cout << "O livro " << titulo << " não está no nosso acervo." << endl;
    }
    else
    {
        mostrar_livro(acervo[index]);
    }
}

void editar_livro(vector<Livro>, string)
{}

void excluir_livro(vector<Livro>, string)
{}


int main()
{
    int op;
    string titulo;
    vector<Livro> acervo;

    cout << endl << "Bem-vindo ao controle bibliotecário" << endl;

    do
    {
        menu();
        cin >> op;

        switch (op)
        {
        case 1:
            cadastrar_livro(acervo);
            break;

        case 2:
            listar_livros(acervo);
            break;

        case 3:
            cout << "Por favor, informe o titulo do livro: ";
            cin >> titulo;

            buscar_livro(acervo, titulo);
            break;

        case 4:
            cout << "Por favor, informe o titulo do livro: ";
            cin >> titulo;

            editar_livro(acervo, titulo);
            break;

        case 5:
            cout << "Por favor, informe o titulo do livro: ";
            cin >> titulo;

            excluir_livro(acervo, titulo);
            break;
        }

    } while (op != 0);

    cout << "Encerrando a execução do programa...";    

    return 0;
}