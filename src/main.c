#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/pwm.h>

#include <zephyr/drivers/gpio.h>
LOG_MODULE_REGISTER(Switch, LOG_LEVEL_INF);

#if !DT_NODE_EXISTS(DT_NODELABEL(valve_switch))
# error "compiler: device node <switch0> not define"
#endif

#if !DT_NODE_EXISTS(DT_ALIAS(servo0))
# error "compiler: define node <servo0> not define"
#else
# define SEVER0_NODE DT_ALIAS(servo0)
#endif

//static const struct pwm_dt_spec servo_st = PWM_DT_SPEC_GET(DT_NODELABEL(servo));
static const struct pwm_dt_spec servo_st = PWM_DT_SPEC_GET(SEVER0_NODE);
static const uint32_t min_pulse = DT_PROP(SEVER0_NODE,min_pulse);
static const uint32_t max_pulse = DT_PROP(SEVER0_NODE,max_pulse);



//#define SWITCH0_NODE DT_ALIAS(switch0)
//#define LED0_NODE    DT_ALIAS(led0)

static const struct gpio_dt_spec valve_switch = 
  GPIO_DT_SPEC_GET_OR(DT_NODELABEL(valve_switch),gpios,{0});

int main(void){
  //if (!gpio_is_ready_dt(&valve_switch)){
  //  LOG_ERR("gpio8 output ready failed");
  //  return 0;
  //}

  //if (gpio_pin_configure_dt(&valve_switch,GPIO_OUTPUT_INACTIVE) != 0){
  //////if (gpio_pin_configure_dt(&valve_switch,GPIO_OUTPUT_ACTIVE) != 0){
  //////if (gpio_pin_configure_dt(&valve_switch,GPIO_PULL_UP) != 0){
  //  LOG_ERR("gpio8 output configure failed");
  //  return 0;
  //}

  if (!pwm_is_ready_dt(&servo_st)){
    LOG_ERR("pwm device not ready: %s",servo_st.dev->name);
    return 0;
  }
  LOG_INF("pwd device ready: %s",servo_st.dev->name);
  LOG_INF("%d, %d",min_pulse,max_pulse);


  //LOG_INF("%d",pwm_set_pulse_dt(&servo_st,max_pulse));
  //return 0;
  for (int i=0; i<1000; i++){
  if (pwm_set_pulse_dt(&servo_st,PWM_USEC(40)) < 0){
    LOG_ERR("pwm device set pluse failed: %s",servo_st.dev->name);
    return 0;
  }
  k_sleep(K_MSEC(3000));
  
  }
  LOG_INF("pwm device set pluse OK: %s",servo_st.dev->name);

  //for (int i=0; i<5; ++i){
  //  gpio_pin_configure_dt(&valve_switch,GPIO_OUTPUT_INACTIVE);
  //  k_sleep(K_MSEC(5000));
  //  gpio_pin_configure_dt(&valve_switch,GPIO_OUTPUT_ACTIVE);
  //  k_sleep(K_MSEC(5000));
  //}
  //k_sleep(K_MSEC(1000));
 // 
  //if (gpio_pin_set_dt(&valve_switch,0) != 0){
  //  LOG_ERR("gpio8 output set active failed");
  //  return 0;
  //}
  //int NUM_STEPS = 5;
	//uint32_t pulse_width = 0U;
	//uint32_t step = servo_st.period / NUM_STEPS;
	//uint8_t dir = 1U;
	//int ret;
	//	ret = pwm_set_pulse_dt(&servo_st,PWM_USEC(25));
	//	if (ret) {
	//		printk("Error %d: failed to set pulse width\n", ret);
	//		return 0;
	//	}
  //LOG_INF("PWM_USEC(40): %d",PWM_USEC(40));
  //LOG_INF("PWM_USEC(10): %d",PWM_USEC(10));

  //int i = 0;
  //while(true){
  //  pwm_set_pulse_dt(&servo_st,PWM_USEC(5)); k_sleep(K_MSEC(2000));
  //  pwm_set_pulse_dt(&servo_st,PWM_USEC(45)); k_sleep(K_MSEC(2000));
  //}



  //int i = 0;
	//while (1) {
  //  LOG_INF("index: %d, curr_plus: %d",i++,pulse_width);
	//	ret = pwm_set_pulse_dt(&servo_st, pulse_width);
	//	if (ret) {
	//		printk("Error %d: failed to set pulse width\n", ret);
	//		return 0;
	//	}

	//	if (dir) {
	//		pulse_width += step;
	//		if (pulse_width >= servo_st.period) {
	//			pulse_width = servo_st.period - step;
	//			dir = 0U;
	//		}
	//	} else {
	//		if (pulse_width >= step) {
	//			pulse_width -= step;
	//		} else {
	//			pulse_width = step;
	//			dir = 1U;
	//		}
	//	}

	//	k_sleep(K_MSEC(2000));
	//}


  return 0;
}
