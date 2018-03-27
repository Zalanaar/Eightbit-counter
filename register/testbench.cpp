#include <systemc.h>
#include "counter.h"
#include <conio.h>

#define soft_assert(signal, expected) \
	if(signal.read() != expected) { \
		cerr << "@" << sc_time_stamp() << "Check failed. Expected: " << expected << ". Actual: " << signal.read() << ".\n" << endl; \
	}


int sc_main(int argc, char* argv[]) {

	//initialization signal
	sc_clock clock("clock", 2, SC_NS);
	sc_signal<bool> reset;
	sc_signal<bool> load;
	sc_signal<bool> synch_reset;
	sc_signal<sc_uint<8> > register_in;
	sc_signal<sc_uint<8> > register_out;

	//connect the DUT
	eightbit_counter test_counter("counter testing");
	test_counter.clock(clock);
	test_counter.reset(reset);
	test_counter.load(load);
	test_counter.synch_reset(synch_reset);
	test_counter.register_in(register_in);
	test_counter.register_out(register_out);


	//create VCD file 
	sc_trace_file *wf = sc_create_vcd_trace_file("counter_waveform");

	//Dump the desired signal
	sc_trace(wf, clock, "clock");
	sc_trace(wf, reset, "reset");
	sc_trace(wf, load, "load");
	sc_trace(wf, synch_reset, "synch_reset");
	sc_trace(wf, register_in, "Din");
	sc_trace(wf, register_out, "Dout");


	synch_reset = 1; //Asserting reset
	cout << "@" << sc_time_stamp() << ":Asserting reset" << "\n" << endl;

	sc_start(8, SC_NS);

	synch_reset = 0; //De-Asserting reset
	cout << "@" << sc_time_stamp() << ":De-Asserting reset" << "\n" << endl;

	sc_start(4, SC_NS);

	load = 1;
	sc_uint<8> data = 128;
	register_in = data;
	cout << "@" << sc_time_stamp() << ":Start Loading " << "\n"<< endl;
	sc_start(32, SC_NS);

	load = 0;
	cout << "@" << sc_time_stamp() << ":End Loading" << "\n" << endl;
	sc_start(64, SC_NS);

	synch_reset = 1; //Assering reset
	cout << "@" << sc_time_stamp() << ":Asserting reset" << "\n" << endl;
	sc_start(1, SC_NS);
	assert(register_out.read() == 0);
	sc_start(5, SC_NS);
	cout << "@" << sc_time_stamp() << ":Termimate simulation" << "\n" << endl;
	_getch();

	sc_close_vcd_trace_file(wf);
	return 0;
}