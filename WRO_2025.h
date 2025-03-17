#define tyre_diameter 6.24
#define tyre_distance 13
#define tyre_double_distance 26
#define PI 3.141592653589793238

void setL(int p) {
    setMotorSpeed(left, p);
}

void setR(int p) {
    setMotorSpeed(right, p);
}

void drive(int p) {
    setL(p);
    setR(p);
}

int getL() {
    return getColorReflected(Lcolor);
}

int getR() {
    return getColorReflected(Rcolor);
}

#include "Pid.h"

float error_4=0, f_error_4=0, p_3, d_3;
void tracE(int power_T, float Kp, float Kd){
	error_4 = getColorReflected(Rcolor) - getColorReflected(Lcolor);
	p_3 = Kp * error_4;
	d_3 = Kd * (error_4 - f_error_4);

	if(getColorReflected(Rcolor) <= 7 && getColorReflected(Lcolor) <= 7){
		setMotorSpeed(right, 0);
		setMotorSpeed(left, 0);
	}

	else{
		setMotorSpeed(right, power_T + (p_3 + d_3));
		setMotorSpeed(left, power_T - (p_3 + d_3));
	}

	f_error_4 = error_4;
}

float error_3=0, f_error_3=0, p_2, d_2;
void trace(int power_T, float Kp, float Kd){
	error_3 = getColorReflected(Rcolor) - getColorReflected(Lcolor);
	p_2 = Kp * error_3;
	d_2 = Kd * (error_3 - f_error_3);

	if(getColorReflected(Rcolor) >= 50 && getColorReflected(Lcolor) >= 50){
		setMotorSpeed(right, 0);
		setMotorSpeed(left, 0);
	}

	else{
		setMotorSpeed(right, power_T + (p_2 + d_2));
		setMotorSpeed(left, power_T - (p_2 + d_2));
	}

	f_error_3 = error_3;
}


int s;
float error=0, f_error=0, p, d;
void Trace(int power_T, float Kp, float Kd)/////line_trane
{
	error = getColorReflected(Rcolor) - getColorReflected(Lcolor);
	p = Kp * error;
	d = Kd * (error - f_error);

	setMotorSpeed(right, power_T + (p + d));
	setMotorSpeed(left, power_T - (p + d));


	f_error = error;
}

int back=0;
float angle=0;

void Straight(int power, float gain, float cm, bool go)
{

	float P_power=0, end_power=0, now_power;
	int now_angle=0, end_target=0, motor_angle=0;

	resetMotorEncoder(right);
    resetMotorEncoder(left);

	angle = (360 / (tyre_diameter * 3.14)) * cm;

	if(power < 0){
		back = -1;
	}
		else{
			back = 1;
		}

	while(getMotorEncoder(right) * back < angle){

		error = gain * (getMotorEncoder(right) - getMotorEncoder(left) * -1);

  	setMotorSpeed(right, power - error);
  	setMotorSpeed(left, power + error);

	}
	if(go == 0){
		setMotorSpeed(right, 0);
  		setMotorSpeed(left, 0);
  }
}

/*void Pivotturn_M(int power, int min_power, float gain, int target, float time)/////wro_kakamigahara_sannkou_ni_suru
{
	float P_power=0, end_power=0, now_power;
	int now_angle=0, end_target=0, motor_angle=0;

	resetMotorEncoder(right);
    resetMotorEncoder(left);

  	if(target < 0){
  		end_target = target * -1;
  	}
    else{
  		end_target = target;
  	}

   now_angle = 0;
   motor_angle = 0;
   time = time * 1000;

   clearTimer(T1);

    while(now_angle != end_target && time1[T1] < time){

		now_angle = (tyre_diameter * motor_angle) / tyre_double_distance;/////now_robot_angle

		if(end_target < now_angle){
			end_power = min_power * -1;
		}
		else{
			end_power = min_power;
		}

		P_power = (end_target - now_angle) * gain + end_power;/////culculated_power

		if(P_power < power){
			now_power = P_power;
		}
		else{
			if(end_target < now_angle){
				now_power = power * -1;
			}
			else{
				now_power = power;
			}
		}

			if(target < 0){
				if(power < 0){
					motor_angle = getMotorEncoder(left) * 1;/////now_getMotor_angle
					setMotorSpeed(left, now_power);
				}
				else{
					motor_angle = getMotorEncoder(right) * 1;/////now_getMotor_angle
					setMotorSpeed(right, now_power);
				}
			}
			else{
				if(power < 0){
					motor_angle = getMotorEncoder(right) * -1;
					setMotorSpeed(right, now_power);
				}
				else{
					motor_angle = getMotorEncoder(left) * -1;
					setMotorSpeed(left, now_power);
				}
			}
	}
	setMotorSpeed(right, 0);
    setMotorSpeed(left, 0);
}

void Spinturn_M(int power, int min_power, float gain, int target, float time)
{

  float P_power=0, end_power=0, now_power;
  int now_angle=0, end_target=0, motor_angle=0;

  resetMotorEncoder(right);
  resetMotorEncoder(left);

  if(target < 0){
  	end_target = target * -1;
  }
  else{
  	end_target = target;
  }

  now_angle = 0;
  motor_angle = 0;
  time = time * 1000;

  clearTimer(T1);

  while(now_angle != end_target && time1[T1] < time){

  	now_angle = (tyre_diameter * motor_angle) / tyre_distance;/////now_robot_angle

  	if(end_target < now_angle){
  		end_power = min_power * -1;
  	}
  	else{
  		end_power = min_power;
  	}

  	P_power = (end_target - now_angle) * gain + end_power;/////culculated_power

  	if(P_power < power){
  		now_power = P_power;
  	}
  	else{
  		if(end_target < now_angle){
  			now_power = power * -1;
  		}
  		else{
  			now_power = power;
  		}
  	}

		if(target < 0){
			motor_angle = (getMotorEncoder(left) + (getMotorEncoder(right))) / 2;/////now_getMotor_angle
			setMotorSpeed(right, now_power);
			setMotorSpeed(left, now_power * -1);
		}
			else{
				motor_angle = (getMotorEncoder(right) * -1 + (getMotorEncoder(left) * -1)) / 2;
				setMotorSpeed(left, now_power);
				setMotorSpeed(right, now_power * -1);
			}
	}
  setMotorSpeed(right, 0);
  setMotorSpeed(left, 0);
  wait1Msec(100);

}

float error_2 = 0;
int back_2 = 0;
float mokuhyou = 0;
void streat_M(float cm, float gain, int p){

	resetMotorEncoder(right);
	resetMotorEncoder(left);

	mokuhyou = (360 / (6.24 * 3.14)) * cm;
	if(p < 0){
		back_2 = -1;
	}
	else{
		back_2 = 1;
	}
	while(getMotorEncoder(right) * back_2 < mokuhyou){
		error_2 = gain * (getMotorEncoder(right) - getMotorEncoder(left) * -1);

  		setMotorSpeed(right, p - error_2);
  		setMotorSpeed(left, p + error_2);

		displayTextLine(2, "right=%d", getMotorEncoder(right));
  		displayTextLine(3, "left=%d", getMotorEncoder(left));

	}

}*/



void streat(int power, float gain, float cm, int go)
{
	float error = 0;
	int back=0;
	float angle=0;

	resetMotorEncoder(right);
  	resetMotorEncoder(left);

	angle = (360 / (tyre_diameter * 3.14)) * cm;

	if(power < 0){
		back = 1;
	}
		else{
			back = -1;
		}

	while(getMotorEncoder(right) * back < angle){

		error = gain * (getMotorEncoder(right) - getMotorEncoder(left));

  	setMotorSpeed(right, power + error);
  	setMotorSpeed(left, power - error);

  	displayTextLine(2, "right=%d", getMotorEncoder(right));
  	displayTextLine(3, "left=%d", getMotorEncoder(left));

	}
	if(go == 0){
		setMotorSpeed(right, 0);
  		setMotorSpeed(left, 0);
  }
}

void streat_s(float gain, float cm, int go){
	int power = 50;
	


}


void pivotturn(int power, int min_power, float gain, int target, float time)/////wro_kakamigahara_sannkou_ni_suru
{
	float error = 0;
	float now_power=0, P_power=0, end_power=0;
	int now_angle=0, end_target=0, motor_angle=0;

	resetMotorEncoder(right);
  resetMotorEncoder(left);

  if(target < 0){
  	end_target = target * -1;
  }
  else{
  	end_target = target;
  }

  now_angle = 0;
  motor_angle = 0;
  time = time * 1000;

  clearTimer(T1);

  while(now_angle != end_target && time1[T1] < time){

  	now_angle = (tyre_diameter * motor_angle) / tyre_double_distance;/////now_robot_angle

  	if(end_target < now_angle){
  		end_power = min_power * -1;
  	}
  	else{
  		end_power = min_power;
  	}

  	P_power = (end_target - now_angle) * gain + end_power;/////culculated_power

  	if(P_power < power){
  		now_power = P_power;
  	}
  	else{
  		if(end_target < now_angle){
  			now_power = power * -1;
  		}
  		else{
  			now_power = power;
  		}
  	}

		if(target < 0){
			motor_angle = getMotorEncoder(right) * -1;/////now_getMotor_angle
			setMotorSpeed(right, now_power);
		}
		else{
			motor_angle = getMotorEncoder(left) * -1;
			setMotorSpeed(left, now_power);
		}

		displayTextLine(1, "angle=%d", now_angle);
	}
	setMotorSpeed(right, 0);
  setMotorSpeed(left, 0);
}

void spinturn(int power, int min_power, float gain, int target, int time)
{
	float error = 0;
	float now_power=0, P_power=0, end_power=0;
	int now_angle=0, end_target=0, motor_angle=0;

  resetMotorEncoder(right);
  resetMotorEncoder(left);

  if(target < 0){
  	end_target = target * -1;
  }
  else{
  	end_target = target;
  }

  now_angle = 0;
  motor_angle = 0;
  time = time * 1000;

  clearTimer(T1);

  while(now_angle != end_target && time1[T1] < time){

  	now_angle = (tyre_diameter * motor_angle) / tyre_distance;/////now_robot_angle

  	if(end_target < now_angle){
  		end_power = min_power * -1;
  	}
  	else{
  		end_power = min_power;
  	}

  	P_power = (end_target - now_angle) * gain + end_power;/////culculated_power

  	if(P_power < power){
  		now_power = P_power;
  	}
  	else{
  		if(end_target < now_angle){
  			now_power = power * -1;
  		}
  		else{
  			now_power = power;
  		}
  	}

		if(target < 0){
			motor_angle = (getMotorEncoder(left) + (getMotorEncoder(right) * -1)) / 2;/////now_getMotor_angle
			setMotorSpeed(right, now_power);
			setMotorSpeed(left, now_power * -1);
		}
		else{
			motor_angle = (getMotorEncoder(right) + (getMotorEncoder(left) * -1)) / 2;
			setMotorSpeed(left, now_power);
			setMotorSpeed(right, now_power * -1);
		}
	}
	setMotorSpeed(right, 0);
  setMotorSpeed(left, 0);
}



/*float Y;
float X;
void streat(int pa, int cm){
	X = 0;

	while(1){
		Y = pa / (( X / cm ) ^ 4 + 1);
		X = X + 1;

		delay(500);
		setMotorSpeed(left, Y);
		setMotorSpeed(right, Y);

		if( Y <= 0.5 ){
			break;
		}
	}
}*/

void spinturn_L(int power, int min_power, float gain, int target, int time)
{
	float error = 0;
	float now_power=0, P_power=0, end_power=0;
	int now_angle=0, end_target=0, motor_angle=0;

	resetMotorEncoder(right);
  	resetMotorEncoder(left);

  if(target < 0){
  	end_target = target * -1;
  }
  else{
  	end_target = target;
  }

  now_angle = 0;
  motor_angle = 0;
  time = time * 1000;

  clearTimer(T1);

  while(now_angle != end_target && time1[T1] < time){

  	now_angle = (tyre_diameter * motor_angle) / tyre_distance;/////now_robot_angle

  	if(end_target < now_angle){
  		end_power = min_power * -1;
  	}
  	else{
  		end_power = min_power;
  	}

  	P_power = (end_target - now_angle) * gain + end_power;/////culculated_power

  	if(P_power < power){
  		now_power = P_power;
  	}
  	else{
  		if(end_target < now_angle){
  			now_power = power * -1;
  		}
  		else{
  			now_power = power;
  		}
  	}

		if(target < 0){
			motor_angle = (getMotorEncoder(left) + (getMotorEncoder(right) * -1)) / 2;/////now_getMotor_angle
			setMotorSpeed(right, now_power);
			setMotorSpeed(left, now_power * -1);
		}
		else{
			motor_angle = (getMotorEncoder(right) + (getMotorEncoder(left) * -1)) / 2;
			setMotorSpeed(left, now_power);
			setMotorSpeed(right, now_power * -1);
		}
	}
	setMotorSpeed(right, 0);
  setMotorSpeed(left, 0);
}
