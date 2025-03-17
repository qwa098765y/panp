struct Pid {
    float p;
    float i;
    float d;
    float f_error;
    /// @brief -1 left(1), 0 center(2), 1 right(1)
    int type;
    /// @brief sikiiti
    int threshold;
};

void initPid(struct Pid& data, float p, float i, float d) {
    data.p = p;
    data.i = i;
    data.d = d;
    data.f_error = 0;
    data.type = 0;
    data.threshold = 50;
}

void initTraceType(struct Pid& data, int type, int threshold) {
    data.type = type;
    data.threshold = threshold;
}

void initTrace(struct Pid& data, float p, float i, float d, int type, int threshold) {
    initPid(data, p, i, d);
    initTraceType(data, type, threshold);
}

void clonePid(struct Pid& data, struct Pid& target) {
    initTrace(target, data.p, data.i, data.d, data.type, data.threshold);
}

void reset_f_error(struct Pid& data) {
    data.f_error = 0;
}

int calcPid(struct Pid& data, int error) {
    int p = data.p * error;
    int i = data.i * (error + data.f_error);
	int d = data.d * (error - data.f_error);

    data.f_error = error;
    return p + i + d;
}

void pidTrace(struct Pid& data, int power) {
    int error;
    if (data.type == 0)
        error = getL() - getR();
    else if (data.type == -1)
        error = data.threshold - getL();
    else if (data.type == 1)
        error = getR() - data.threshold;

	int pid_ = calcPid(data, error);

	setL(power + pid_ );
	setR(power - pid_ );
}


