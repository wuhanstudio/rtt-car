#include <rtthread.h>
#include <rtdevice.h>


#define ROBOT_LEFT_UP_PIN_NUM            24  /* PB8 */
#define ROBOT_LEFT_DO_PIN_NUM            39  /* PC7 */
#define ROBOT_RIGHT_UP_PIN_NUM           25  /* PB9 */
#define ROBOT_RIGHT_DO_PIN_NUM           8  /* PA8 */

static int robot_run(int argc, char *argv[])
{
	rt_pin_mode(ROBOT_LEFT_UP_PIN_NUM, PIN_MODE_OUTPUT);
	rt_pin_write(ROBOT_LEFT_UP_PIN_NUM, PIN_HIGH);
	rt_pin_mode(ROBOT_RIGHT_UP_PIN_NUM, PIN_MODE_OUTPUT);
	rt_pin_write(ROBOT_RIGHT_UP_PIN_NUM, PIN_HIGH);

	return 0;
}
MSH_CMD_EXPORT(robot_run, robot run forward);

static int robot_back(int argc, char *argv[])
{
	rt_pin_mode(ROBOT_LEFT_DO_PIN_NUM, PIN_MODE_OUTPUT);
	rt_pin_write(ROBOT_LEFT_DO_PIN_NUM, PIN_HIGH);
	rt_pin_mode(ROBOT_RIGHT_DO_PIN_NUM, PIN_MODE_OUTPUT);
	rt_pin_write(ROBOT_RIGHT_DO_PIN_NUM, PIN_HIGH);

	return 0;
}
MSH_CMD_EXPORT(robot_back, robot run back);

static int robot_left(int argc, char *argv[])
{
	rt_pin_mode(ROBOT_LEFT_DO_PIN_NUM, PIN_MODE_OUTPUT);
	rt_pin_write(ROBOT_LEFT_DO_PIN_NUM, PIN_HIGH);
	rt_pin_mode(ROBOT_RIGHT_UP_PIN_NUM, PIN_MODE_OUTPUT);
	rt_pin_write(ROBOT_RIGHT_UP_PIN_NUM, PIN_HIGH);

	rt_pin_mode(ROBOT_LEFT_UP_PIN_NUM, PIN_MODE_OUTPUT);
	rt_pin_write(ROBOT_LEFT_UP_PIN_NUM, PIN_LOW);
	rt_pin_mode(ROBOT_RIGHT_DO_PIN_NUM, PIN_MODE_OUTPUT);
	rt_pin_write(ROBOT_RIGHT_DO_PIN_NUM, PIN_LOW);
	
	return 0;
}
MSH_CMD_EXPORT(robot_left, robot turn left);

static int robot_right(int argc, char *argv[])
{
	rt_pin_mode(ROBOT_LEFT_UP_PIN_NUM, PIN_MODE_OUTPUT);
	rt_pin_write(ROBOT_LEFT_UP_PIN_NUM, PIN_HIGH);
	rt_pin_mode(ROBOT_RIGHT_DO_PIN_NUM, PIN_MODE_OUTPUT);
	rt_pin_write(ROBOT_RIGHT_DO_PIN_NUM, PIN_HIGH);

	rt_pin_mode(ROBOT_LEFT_DO_PIN_NUM, PIN_MODE_OUTPUT);
	rt_pin_write(ROBOT_LEFT_DO_PIN_NUM, PIN_LOW);
	rt_pin_mode(ROBOT_RIGHT_UP_PIN_NUM, PIN_MODE_OUTPUT);
	rt_pin_write(ROBOT_RIGHT_UP_PIN_NUM, PIN_LOW);

	return 0;
}
MSH_CMD_EXPORT(robot_right, robot turn right);

static int robot_stop(int argc, char *argv[])
{
	rt_pin_mode(ROBOT_LEFT_UP_PIN_NUM, PIN_MODE_OUTPUT);
	rt_pin_write(ROBOT_LEFT_UP_PIN_NUM, PIN_LOW);

	rt_pin_mode(ROBOT_RIGHT_UP_PIN_NUM, PIN_MODE_OUTPUT);
	rt_pin_write(ROBOT_RIGHT_UP_PIN_NUM, PIN_LOW);

	rt_pin_mode(ROBOT_LEFT_DO_PIN_NUM, PIN_MODE_OUTPUT);
	rt_pin_write(ROBOT_LEFT_DO_PIN_NUM, PIN_LOW);

	rt_pin_mode(ROBOT_RIGHT_DO_PIN_NUM, PIN_MODE_OUTPUT);
	rt_pin_write(ROBOT_RIGHT_DO_PIN_NUM, PIN_LOW);

	return 0;
}
MSH_CMD_EXPORT(robot_stop, robot stop);
