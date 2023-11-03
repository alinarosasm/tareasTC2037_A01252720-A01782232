#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void leerArchivos(const vector<string> archivosTransmision, const vector<string> archivosMCode)
{
    for (size_t i = 0; i < archivosTransmision.size(); i++)
    {
        for (size_t j = 0; j < archivosMCode.size(); j++)
        {
            ifstream archivoTransmision(archivosTransmision[i]);
            ifstream archivoMCode(archivosMCode[j]);
            string lineaT, lineaM;

            string contenidoTransmision;
            while (getline(archivoTransmision, lineaT))
            {
                contenidoTransmision += lineaT;
            }

            string contenidoMCode;
            while (getline(archivoMCode, lineaM))
            {
                contenidoMCode += lineaM;
            }

            size_t posicion = contenidoTransmision.find(contenidoMCode);
            string resultado = (posicion != string::npos ? "true " + to_string(posicion) : "false");
            cout << resultado << endl;
        }
    }
    cout << endl;
}

void encontrarPalindromo(string arch)
{
    ifstream archivoTransmision(arch);
    string lineaT;

    string contenidoArchivoT;
    while (getline(archivoTransmision, lineaT))
    {
        contenidoArchivoT += lineaT;
    }

    int inicio = 0;
    int longitud = 1;

    for (int i = 1; i < contenidoArchivoT.length(); i++)
    {
        int j = 1;

        // Para substrings de longitud impar
        while (i - j >= 0 && i + j < contenidoArchivoT.length() && contenidoArchivoT[i - j] == contenidoArchivoT[i + j])
        {
            j++;
        }

        if (2 * j - 1 > longitud)
        {
            longitud = 2 * j - 1;
            inicio = i - j + 1;
        }

        j = 0;

        // Para substring de longitud par
        while (i - j - 1 >= 0 && i + j < contenidoArchivoT.length() && contenidoArchivoT[i - j - 1] == contenidoArchivoT[i + j])
        {
            j++;
        }

        if (2 * j > longitud)
        {
            longitud = 2 * j;
            inicio = i - j;
        }
    }

    if (longitud > 1)
    {
        cout << inicio << " " << inicio + longitud - 1 << endl;
    }
    else
    {
        cout << "false" << endl;
    }
}

void compararTextos(string archT1, string archT2)
{
    ifstream archivoTransmision1(archT1);
    ifstream archivoTransmision2(archT2);
    string lineaT1, lineaT2;

    string contenidoArchivoT1;
    while (getline(archivoTransmision1, lineaT1))
    {
        contenidoArchivoT1 += lineaT1;
    }

    string contenidoArchivoT2;
    while (getline(archivoTransmision2, lineaT2))
    {
        contenidoArchivoT2 += lineaT2;
    }

    int n = contenidoArchivoT1.length();
    int m = contenidoArchivoT2.length();

    vector<vector<int> > LCS(n + 1, vector<int>(m + 1, 0)); // Matriz para la programación dinámica
    int maxLongitud = 0;                                   
    int posicionInicio = -1;                              

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (contenidoArchivoT1[i - 1] == contenidoArchivoT2[j - 1])
            {
                LCS[i][j] = LCS[i - 1][j - 1] + 1;
                if (LCS[i][j] > maxLongitud)
                {
                    maxLongitud = LCS[i][j];
                    posicionInicio = i - maxLongitud;
                }
            }
        }
    }

    if (maxLongitud > 0)
    {
        int posicionFinal = posicionInicio + maxLongitud - 1;
        cout << posicionInicio + 1 << " " << posicionFinal + 1 << endl;
    }
    else
    {
        cout << "No se encontró un substring común entre los archivos" << endl;
    }
}

int main()
{
    vector<string> archivosTransmision;
    archivosTransmision.push_back("transmission1.txt");
    archivosTransmision.push_back("transmission2.txt");

    vector<string> archivosMCode;
    archivosMCode.push_back("mcode1.txt");
    archivosMCode.push_back("mcode2.txt");
    archivosMCode.push_back("mcode3.txt");

    cout << "PARTE 1" << endl;
    leerArchivos(archivosTransmision, archivosMCode);
    cout << "PARTE 2" << endl;
    encontrarPalindromo("transmission1.txt");
    encontrarPalindromo("transmission2.txt");

    cout << endl
         << "PARTE 3" << endl;
    compararTextos("transmission1.txt", "transmission2.txt");
    return 0;
}

// que lea 5 archivos de texto de nombre fijo
// los archivos de transmision contienen caracteres de texto que representan el envio de datos de un dispositivo a otro
// los archivos mcode representan codigo malicioso que se puede encontrar dentro de una transmision
// PARTE 1
// el programa debe analizar si el contenido de los archivos mcode estan contenidos en los archivos de transmision
// en caso de ser true, muestra true seguido de un espacio, seguido de la posición del archivo transmission donde inicia el codigo de mcode
// Output: (true | false) <posicion>
// PARTE 2
// PARTE 3
// el programa analiza que tan similares son los archivos de transmision y muestra la posicion inicial y posicion final
// del primer archivo en donde se encuentra el substring más largo común entre ambos archivos de tranmisión