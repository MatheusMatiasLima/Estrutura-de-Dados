#include <iostream>

using namespace std;

// A função intercala recebe vetores crescentes v[p..q-1] 
// e v[q..r] e rearranja v[p..r] em ordem crescente
void intercala(int v[], int p, int q, int r){
    int i = p;
    int j = q;
    int tamanho = r - p + 1;
    int w[tamanho]; // vetor auxiliar
    int k = 0;
    
    while ((i < q) and (j <= r)) {                
        if (v[i] <= v[j])  {
            w[k++] = v[i++]; 
            /*  w[k] = v[i]; 
                k++;
                i++;
            */
        } else  {
            w[k++] = v[j++];
            /*  w[k] = v[j]; 
                k++;
                j++;
            */
        }
    } 
    
    // terminou um dos vetores, agora copia o outro                           
    while (i < q) {
        w[k++] = v[i++];
    }   
    while (j <= r) {
        w[k++] = v[j++]; 
    }
    
    // agora copiamos do vetor auxiliar aux[] em v[p:r]
    for (int m = 0; m < tamanho; m++){ 
        v[p + m] = w[m];
    }
}

// mergesort iterativo, considera que está ordenado um a um e vai ordenando,
// usando intercalação, em blocos cada vez maiores, 
// até que o bloco seja maior ou do mesmo tamanho do vetor 
void mergeiterativo (int v[], int tam) {
    int p, r;
    int b = 1;
    while (b < tam) {
        p = 0;
        while (p + b < tam) {
            r = p + 2*b - 1;
            if (r >= tam) {
                r = tam - 1;
            }
            intercala(v, p, p+b, r);
            p = p + 2*b; 
        }
        b = 2*b;
    }
}


void mergesort(int a[], int inicio, int fim){
    int meio;
    if (inicio < fim) {
        meio = (inicio + fim)/2; // acha meio de a[inicio:fim]
        // chama recursivamente mergesort nas duas metades
        mergesort(a, inicio, meio);
        mergesort(a, meio+1, fim);      
        intercala(a,inicio,meio+1,fim);
    }
}

int main(){
    int n;

    // recebendo o tamanho do vetor a ser ordenado
    cin >> n;
    
    // criando o vetor usando VLA 
    // http://en.wikipedia.org/wiki/Variable-length_array
    // http://stackoverflow.com/questions/1887097/variable-length-arrays-in-c
    
    int a[n];
    
    // lendo o vetor a
    for (int i=0; i < n; i++){
        cin >> a[i];
    }   
    
    // chamando mergesort no vetor a inteiro
    mergeiterativo(a, n);
    // mergesort(a, 0, n-1);
    
    // imprimindo a[]
    for (int i=0; i < n; i++){
        cout << a[i] << " ";
    }
    
    cout << endl;
    
    return 0;
}
