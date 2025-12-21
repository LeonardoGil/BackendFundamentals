#include <iostream>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    char* arquivo;
    const int BUFFER_SIZE = 64;
    
    std::cin >> arquivo;

    int fd = open(arquivo, O_RDONLY);

    if (fd == -1) {
        std::cerr << "Erro ao abrir arquivo\n";
        return 1;
    }

    char buffer[BUFFER_SIZE];
    ssize_t bytesLidos;

    while (true) {
        bytesLidos = read(fd, buffer, BUFFER_SIZE);

        if (bytesLidos <= 0) {
            break;
        }

        write(STDOUT_FILENO, buffer, bytesLidos);

        std::cout << "\n--- Pressione ENTER para continuar ou 'q' para sair ---\n";
        char opcao = std::cin.get();

        if (opcao == 'q') {
            break;
        }
    }

    close(fd);
    return 0;
}
