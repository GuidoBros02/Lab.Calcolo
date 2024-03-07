#include <stdio.h>
#include <math.h>

// Prototipi delle funzioni
float f(float x);
float midpoint(float (*)(float), float, float, int);
float trapez(float (*)(float), float, float, int);

int main()
{
    float a, b, acc;

    printf("Programma per il calcolo dell'integrale definito\n");

    // Input dell'utente per gli estremi dell'intervallo di integrazione
    printf("Inserisci l'estremo inferiore dell'intervallo di integrazione: ");
    if (scanf("%f", &a) != 1)
    {
        printf("Errore di input per l'estremo inferiore.\n");
        return 1;
    }

    printf("Inserisci l'estremo superiore dell'intervallo di integrazione: ");
    if (scanf("%f", &b) != 1)
    {
        printf("Errore di input per l'estremo superiore.\n");
        return 1;
    }

    if (a >= b)
    {
        printf("Errore! L'estremo superiore deve essere maggiore dell'estremo inferiore.\n");
        return 1;
    }

    // Input dell'utente per l'accuratezza desiderata
    printf("Inserisci l'accuratezza desiderata (es. 0.0001): ");
    if (scanf("%f", &acc) != 1 || acc <= 0)
    {
        printf("Errore! L'accuratezza deve essere un valore positivo.\n");
        return 1;
    }

    // Adattamento dinamico del numero di sottointervalli
    int n = 1;
    while (1)
    {
        float midpoint_result = midpoint(f, a, b, n);
        float trapez_result = trapez(f, a, b, n);

        if (fabs(midpoint_result - trapez_result) < acc)
            break;

        n = 2 * n;
    }

    // Calcolo dell'integrale usando il metodo del punto medio
    float midpoint_result = midpoint(f, a, b, n);

    // Calcolo dell'integrale usando il metodo del trapezio
    float trapez_result = trapez(f, a, b, n);

    // Output dei risultati con 7 cifre significative
    printf("Risultato con il metodo del punto medio: %.7g\n", midpoint_result);
    printf("Risultato con il metodo del trapezio: %.7g\n", trapez_result);

    return 0;
}

// Definizione della funzione integranda
float f(float x)
{
    return sqrt(tan(x));
}

// Implementazione del metodo del punto medio
float midpoint(float func(float), float a, float b, int n)
{
    float sum = 0.;
    float h = (b - a) / n;

    for (int i = 0; i < n; i++)
    {
        float xi = a + i * h;
        sum += func(xi + h / 2);
    }

    return h * sum;
}

// Implementazione del metodo del trapezio
float trapez(float func(float), float a, float b, int n)
{
    float sum = 0.;
    float h = (b - a) / n;
    for (int i = 0; i <= n; i++)
    {
        float xi = a + i * h;
        if (i == 0 || i == n)
            sum += 0.5 * func(xi);
        else
            sum += func(xi);
    }
    return h * sum;
}
