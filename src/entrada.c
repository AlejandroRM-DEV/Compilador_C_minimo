
int global = 1;

void aritmeticaBasica();
int operacionX ( int a, int b );
void unarios();
void iterativas();
void selectivas();

int main() {
	int x;

	aritmeticaBasica();
	x = operacionX ( operacionX(5,6), operacionX(1,2) );
	unarios();
	iterativas();

	return 0;
}

void aritmeticaBasica() {
	int a, b, c, d, e, f, x;
	a = 1;
	b = a + 2;
	c = b - 1;
	d = c * 2;
	e = d / 1;
	f = e % 2;
	x = a = b = c = d = 0;
}

int operacionX ( int a, int b ) {
	int res = a % b * ( ( a + b ) / ( a - b ) );
	// Algo de codigo
	return res;
}

void unarios() {
	int a = +1;
	int b = -1;
	int c = !1;
	int d = !0;

	int e = ++a;
	int f = --a;
	int x = a++;
	int y = a--;
	int z = a;
}

void iterativas() {
	int a, x;
	for ( a = 0; a < 10; a++ ) {
		x = a;
	}

	while ( 1 ) {
		if ( x == 0 ) {
			break;
		}
		x--;
	}

	do {
		a--;
	} while ( a > 0 );
}

void selectivas() {
	int x;
	if ( global > 0 ) {
		x = 20;
	} else {
		x = -20;
	}
	if ( x == 20 && global >= 0 ) {
		global = x = 0;
	}
}
