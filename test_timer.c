
#include <platform.h>
#include <timer.h>

int main() {
	core_timer_t timer;
	core_timer(&timer);

	for (;;) {
		Sleep(1000);
		float time = core_time(&timer);
		printf("time %f \n", time);
	}
}
