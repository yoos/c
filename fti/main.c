#include <stdio.h>
#include <stdint.h>

#define SCALE 1000000

int32_t fti(uint32_t flt)
{
	uint8_t sign = (flt >> 31) & 1;
	uint8_t exp  = (flt >> 23) & 0xff;
	int32_t out = 0;

	int8_t i;
	printf("Sign: %d   Exp: %d   Frac: ", sign, exp);
	for (i=1; i<=23; i++) {
		printf("%d", (flt>>(23-i))&1);
	}
	printf("\n");

	//uint32_t b = ((0x800000 + (flt & 0x7fffff)) >> 15)*SCALE;
	//int8_t bs = exp - 127;
	//if (bs > 0) b <<= bs;
	//else b >>= -bs;
	//out = b;

	for (i=0; i<=23; i++) {
		uint8_t _t = ((flt >> (23-i)) & 1);

		// Debug
		if (i==0) {
			_t = 1;
			printf("base: ");
		}
		else {
			printf("b_%2d: ", 23-i);
		}
		uint32_t b = _t * SCALE;
		printf("%d", _t);

		// Shift bit value appropriately.
		int8_t bs = -i + exp - 127;

		if (bs > 0) b <<= bs;
		else        b >>= -bs;

		// Need to cap shift value to be within width of variable being
		// shifted. Otherwise, undefined behavior.
		if (bs < -31) b = 0;

		// Debug
		printf(" * 2^%3d == %10d\n", bs, b);

		// Then add to significand.
		out += b;
	}
	
	if (sign == 1) {
		out = -out;
	}

	return out;
}

int main(int argc, char **argv)
{
	// Read
	unsigned long n;
	sscanf(argv[1], "%lx", &n);

	// Convert to integerized float and print
	long f = fti(n);
	printf("%s = %ld\n", argv[1], f);

	return 0;
}

