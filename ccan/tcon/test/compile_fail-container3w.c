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

int main(void)
{
	TCON_WRAP(struct info_base,
		  TCON_CONTAINER(concan, struct outer, inner)) info;
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
