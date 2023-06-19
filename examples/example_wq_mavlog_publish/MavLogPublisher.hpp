#include <px4_platform_common/module.h>
#include <px4_platform_common/px4_work_queue/ScheduledWorkItem.hpp>
#include <drivers/drv_hrt.h>
#include <lib/perf/perf_counter.h>
#include <uORB/Publication.hpp>
#include <uORB/topics/mavlink_log.h>

using namespace time_literals;
// custom auxillary_work_queue queue group
static constexpr px4::wq_config_t auxillary_work_queue{"wq:auxillary_work_queue", 2392, -1};

class MavLogPublisher : public ModuleBase<MavLogPublisher>, public px4::ScheduledWorkItem
{
public:
	MavLogPublisher();
	~MavLogPublisher();
	MavLogPublisher(const MavLogPublisher &) = delete;
	MavLogPublisher operator=(const MavLogPublisher &other) = delete;

	/** @see ModuleBase */
	static int task_spawn(int argc, char *argv[]);

	/** @see ModuleBase */
	static int custom_command(int argc, char *argv[]);

	/** @see ModuleBase */
	static int print_usage(const char *reason = nullptr);

	bool init();

private:
	void Run() override;

	// Publishers
	uORB::Publication<mavlink_log_s>	_mavlink_log_msg_pub{ORB_ID(mavlink_log)};

	// Performance (perf) counters
	perf_counter_t	_loop_perf{perf_alloc(PC_ELAPSED, MODULE_NAME": cycle")};
	perf_counter_t	_loop_interval_perf{perf_alloc(PC_INTERVAL, MODULE_NAME": interval")};

};
