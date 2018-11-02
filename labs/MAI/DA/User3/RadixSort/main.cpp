#include<stdlib.h>
#include<stdio.h>
#include "Vector.h"
#include "Radix.h"

int main() {
	Vector vector;
	const int minVector = 32;
	uint64_t N = 0;
	Item tmp;
	uint64_t tmpKey = 0;
	uint64_t tmpValue = 0;
	while (scanf("%llu", &tmpKey) != EOF) {
		scanf("%llu", &tmpValue);
		if (N == 0) {
			Create(vector, minVector);

			tmp.key = tmpKey;
			tmp.value = tmpValue;
			Save(vector, 0, tmp);
			N = 1;
		}
		else {
			if (Size(vector) > N) {
				tmp.key = tmpKey;
				tmp.value = tmpValue;
				Save(vector, N, tmp);
				N++;
			}
			else {
				tmp.key = tmpKey;
				tmp.value = tmpValue;
				Resize(vector, Size(vector) * 2);
				Save(vector, N, tmp);
				N++;
			}
		}

	}

	if (N) {
		if (N > 1) {
			RadixSort(vector, N);
		}
		for (int i = 0; i < N; i++) {
			printf("%llu\t%llu\n", vector.data[i].key, vector.data[i].value);
		}
		Destroy(vector);
	}
}
