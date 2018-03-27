#include "counter.h"

void eightbit_counter::register_store() {

	mycounter = 0;
	wait();

	while (true) {
		if (!synch_reset.read()){
			if (!load.read()) {
				mycounter = mycounter.read() + 1;
				cout << "@" << sc_time_stamp() << ":Value -> " << mycounter << endl;
				wait();
			}
			else
			{
				mycounter = mycounter.read();
				cout << "@" << sc_time_stamp() << ":Load -> " << mycounter << endl;
				wait();
			}

		}
		else {
			mycounter = 0;
			wait();
		}
	}
}

void eightbit_counter::data_out_method() {
	register_out = mycounter;
}


