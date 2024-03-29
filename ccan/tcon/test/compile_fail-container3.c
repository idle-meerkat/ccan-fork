#include <stdlib.h>

#include <ccan/tcon/tcon.h>
#include <ccan/build_assert/build_assert.h>
#include <ccan/tap/tap.h>

struct inner {
	int inner_val;
};

struct outer {
	int outer_val;
	struct inner inner;
};

struct info_base {
	char *infop;
};

struct info_tcon {
	struct info_base base;
	TCON(TCON_CONTAINER(concan, struct outer, inner));
};

int main(void)
{
	struct info_tcon info;
	struct outer ovar = { 0, { 0 } };
#ifdef FAIL
#if !HAVE_TYPEOF
#error We cannot detect type problems without HAVE_TYPEOF
#endif
	int *outerp;
#else
	struct outer *outerp;
#endif

	outerp = tcon_container_of(&info, concan, &ovar.inner);
	return outerp != NULL;
}
