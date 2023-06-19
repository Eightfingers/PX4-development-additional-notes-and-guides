#include "MavLogPublisher.hpp"

extern "C" __EXPORT int monoco_controls_main(int argc, char *argv[]);

MavLogPublisher::MavLogPublisher() :
	ScheduledWorkItem(MODULE_NAME, auxillary_work_queue),
	/* performance counters */
	_loop_perf(perf_alloc(PC_ELAPSED,  MODULE_NAME": cycle"))
{
}

MavLogPublisher::~MavLogPublisher()
{
	perf_free(_loop_perf);
}

bool
MavLogPublisher::init()
{
	PX4_INFO("Work queue mavlog msg publisher starting");
	ScheduleOnInterval(1000000_us); // 1000000 us interval, 1 Hz rate

	return true;
}

void
MavLogPublisher::Run()
{
	char mavlink_data[127];
	mavlink_log_s mavlink_log;
	sprintf(mavlink_data, "Hello sky!");
	memcpy(mavlink_log.text, mavlink_data, 127);
	_mavlink_log_msg_pub.publish(mavlink_log);
}

int MavLogPublisher::task_spawn(int argc, char *argv[])
{
	MavLogPublisher *instance = new MavLogPublisher();

	if (instance) {
		_object.store(instance);
		_task_id = task_id_is_work_queue;

		if (instance->init()) {
			return PX4_OK;
		}

	} else {
		PX4_ERR("alloc failed");
	}

	delete instance;
	_object.store(nullptr);
	_task_id = -1;

	return PX4_ERROR;
}

int MavLogPublisher::custom_command(int argc, char *argv[])
{
	return print_usage("unknown command");
}

int MavLogPublisher::print_usage(const char *reason)
{
	if (reason) {
		PX4_WARN("%s\n", reason);
	}

	PRINT_MODULE_DESCRIPTION(
		R"DESCR_STR(
### Description
Publish to mavlog

### Examples
CLI usage example:
$ rover_pos_control start
$ rover_pos_control status
$ rover_pos_control stop

)DESCR_STR");

	PRINT_MODULE_USAGE_NAME("Work queue mavlog", "publisher");
	PRINT_MODULE_USAGE_COMMAND("start")
	PRINT_MODULE_USAGE_DEFAULT_COMMANDS();

	return 0;
}

extern "C" __EXPORT int example_wq_mavlog_publish_main(int argc, char *argv[])
{
	return MavLogPublisher::main(argc, argv);
}
