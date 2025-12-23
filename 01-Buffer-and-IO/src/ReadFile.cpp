#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <string>


using namespace std;

int main(int argc, char* argv[]) {
    
    if (argc != 3) {
        cerr << "Uso: ./teste <arquivo> <buffer>" << endl;
        return 1;
    }
    
    vector<string> args(argv, argv + argc);
    
    std::string arquivo = args[1];
    int BUFFER_SIZE = stoi(args[2]);

    int fd = open(arquivo.c_str(), O_RDONLY);
    if (fd == -1) {
        std::cerr << "Erro ao abrir arquivo\n";
        return 1;
    }

    char buffer[BUFFER_SIZE];
    ssize_t bytesLidos;

    while ((bytesLidos = read(fd, buffer, BUFFER_SIZE)) > 0) {
        write(STDOUT_FILENO, buffer, bytesLidos);

        std::cout << "\n--- ENTER para continuar | q para sair ---\n";
        char opcao = std::cin.get();

        if (opcao == 'q') {
            break;
        }
    }

    close(fd);
    return 0;
}
