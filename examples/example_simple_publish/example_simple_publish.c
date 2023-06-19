#include <px4_platform_common/log.h>
#include <uORB/topics/mavlink_log.h>
#include <uORB/uORB.h>

__EXPORT int example_simple_publish_main(int argc, char *argv[]);

int example_simple_publish_main(int argc, char *argv[])
{
    PX4_INFO("Publishing to mavlink log!");

    /* advertise mavlink log topic */
    struct mavlink_log_s mavlink_log_msg;
    orb_advert_t mavlink_log_pub = orb_advertise(ORB_ID(mavlink_log), &mavlink_log_msg);

    char mavlink_data[127];
    sprintf(mavlink_data, "Hello Sky!");
    memcpy(mavlink_log_msg.text, mavlink_data, 127);

    for (int i = 0; i < 5; i++)
    {
        orb_publish(ORB_ID(mavlink_log), mavlink_log_pub, &mavlink_log_msg);
		px4_usleep(1000000);

    }

    return 0;
}
