#include <px4_platform_common/log.h>
#include <uORB/topics/random_numbers.h>

__EXPORT int example_hellosky_main(int argc, char *argv[]);

int example_hellosky_main(int argc, char *argv[])
{
	PX4_INFO("Hello Sky!");

	for (int i = 0 ; i < 100; i++){
		PX4_INFO("Inside loop at %i", i);
		px4_usleep(1000000);
	}
	PX4_INFO("exiting");

	return 0;
}
