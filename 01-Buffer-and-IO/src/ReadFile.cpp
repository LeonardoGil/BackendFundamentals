#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <vector>

using namespace std;

struct arguments
{
    string file;
    int buffer_size;
    int buffer_max;
    bool skip;
};

arguments parseArguments(int argc, char *argv[])
{
    arguments args;
    args.skip = false;
    args.buffer_size = 32;
    args.buffer_max = -1;

    switch (argc)
    {
    case 1:
        cout << "Informe um arquivo " << endl;
        cin >> args.file;
        cin.ignore();
        break;

    case 6:
        args.buffer_max = stoi(argv[5]);

    case 4:
        args.skip = true;

    case 3:
        args.buffer_size = stoi(argv[2]);

    case 2:
        args.file = argv[1];
        break;
    }

    return args;
}

int main(int argc, char *argv[])
{
    arguments args = parseArguments(argc, argv);

    int fd = open(args.file.c_str(), O_RDONLY);

    if (fd == -1)
    {
        cerr << "Erro ao abrir arquivo\n";
        return 1;
    }

    vector<char> buffer(args.buffer_size);
    ssize_t bytesRead;
    int max = 0;

    while ((bytesRead = read(fd, buffer.data(), args.buffer_size)) > 0)
    {
        if (args.buffer_max == -1)
        {
            cout.write(buffer.data(), bytesRead);
        }
        else
        {
            if (max + bytesRead > args.buffer_max)
            {
                bytesRead = args.buffer_max - max;
            }

            cout.write(buffer.data(), bytesRead);
            max += bytesRead;

            if (max >= args.buffer_max)
            {
                cout.write("\n--- Limite de bytes lidos atingido ---\n", 42);
                break;
            }
        }

        if (!args.skip)
        {
            cout.write("\n--- ENTER para continuar | q para sair ---\n", 45);
            char opcao = cin.get();
            if (opcao == 'q')
            {
                break;
            }
        }
    }

    close(fd);
    return 0;
}

